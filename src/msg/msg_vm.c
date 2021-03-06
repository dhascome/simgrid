/* Copyright (c) 2012. The SimGrid Team. All rights reserved.               */

/* This program is free software; you can redistribute it and/or modify it
 * under the terms of the license (GNU LGPL) which comes with this package. */

#include "msg_private.h"
#include "xbt/sysdep.h"
#include "xbt/log.h"

XBT_LOG_NEW_DEFAULT_SUBCATEGORY(msg_vm, msg,
                                "Cloud-oriented parts of the MSG API");

/** @brief Create a new (empty) VMs.
 *  @ingroup msg_VMs
 *
 *  @bug it is expected that in the future, the coreAmount parameter will be used
 *  to add extra constraints on the execution, but the argument is ignored for now.
 */

msg_vm_t MSG_vm_start(msg_host_t location, const char *name, int coreAmount) {
  msg_vm_t res = xbt_new0(s_msg_vm_t,1);
  res->all_vms_hookup.prev = NULL;
  res->host_vms_hookup.prev = NULL;
  res->state = msg_vm_state_running;
  res->location = location;
  res->coreAmount = coreAmount;
  res->name = xbt_strdup(name);
  res->processes = xbt_dynar_new(sizeof(msg_process_t),NULL);

  xbt_swag_insert(res,msg_global->vms);
  xbt_swag_insert(res, MSG_host_priv(location)->vms);

  #ifdef HAVE_TRACING
  TRACE_msg_vm_create(name, location);
  #endif


  return res;
}
/** @brief Returns a newly constructed dynar containing all existing VMs in the system.
 *  @ingroup msg_VMs
 *
 * Don't forget to free the dynar after use.
 */
xbt_dynar_t MSG_vms_as_dynar(void) {
  xbt_dynar_t res = xbt_dynar_new(sizeof(msg_vm_t),NULL);
  msg_vm_t vm;
  xbt_swag_foreach(vm,msg_global->vms) {
    xbt_dynar_push(res,&vm);
  }
  return res;
}

/** @brief Returns whether the given VM is currently suspended
 *  @ingroup msg_VMs
 */
int MSG_vm_is_suspended(msg_vm_t vm) {
  return vm->state == msg_vm_state_suspended;
}
/** @brief Returns whether the given VM is currently running
 *  @ingroup msg_VMs
 */
int MSG_vm_is_running(msg_vm_t vm) {
  return vm->state == msg_vm_state_running;
}
/** @brief Add the given process into the VM.
 *  @ingroup msg_VMs
 *
 * Afterward, when the VM is migrated or suspended or whatever, the process will have the corresponding handling, too.
 *
 */
void MSG_vm_bind(msg_vm_t vm, msg_process_t process) {
  /* check if the process is already in a VM */
  simdata_process_t simdata = simcall_process_get_data(process);
  if (simdata->vm) {
    msg_vm_t old_vm = simdata->vm;
    int pos = xbt_dynar_search(old_vm->processes,&process);
    xbt_dynar_remove_at(old_vm->processes,pos, NULL);
  }
  /* check if the host is in the right host */
  if (simdata->m_host != vm->location) {
    MSG_process_migrate(process,vm->location);
  }
  simdata->vm = vm;

  XBT_DEBUG("binding Process %s to %p",MSG_process_get_name(process),vm);

  xbt_dynar_push_as(vm->processes,msg_process_t,process);
}
/** @brief Removes the given process from the given VM, and kill it
 *  @ingroup msg_VMs
 *
 *  Will raise a not_found exception if the process were not bound to that VM
 */
void MSG_vm_unbind(msg_vm_t vm, msg_process_t process) {
  int pos = xbt_dynar_search(vm->processes,process);
  xbt_dynar_remove_at(vm->processes,pos, NULL);
  MSG_process_kill(process);
}

/** @brief Immediately change the host on which all processes are running.
 *  @ingroup msg_VMs
 *
 * No migration cost occurs. If you want to simulate this too, you want to use a
 * MSG_task_send() before or after, depending on whether you want to do cold or hot
 * migration.
 */
void MSG_vm_migrate(msg_vm_t vm, msg_host_t destination) {
  unsigned int cpt;
  msg_process_t process;
  xbt_dynar_foreach(vm->processes,cpt,process) {
    MSG_process_migrate(process,destination);
  }
  xbt_swag_remove(vm, MSG_host_priv(vm->location)->vms);
  xbt_swag_insert_at_tail(vm, MSG_host_priv(destination)->vms);
  
  #ifdef HAVE_TRACING
  TRACE_msg_vm_change_host(vm,vm->location,destination);
  #endif

  vm->location = destination;
}

/** @brief Immediately suspend the execution of all processes within the given VM.
 *  @ingroup msg_VMs
 *
 * No suspension cost occurs. If you want to simulate this too, you want to
 * use a \ref MSG_file_write() before or after, depending on the exact semantic
 * of VM suspend to you.
 */
void MSG_vm_suspend(msg_vm_t vm) {
  unsigned int cpt;
  msg_process_t process;
  xbt_dynar_foreach(vm->processes,cpt,process) {
    XBT_DEBUG("suspend process %s of host %s",MSG_process_get_name(process),MSG_host_get_name(MSG_process_get_host(process)));
    MSG_process_suspend(process);
  }

  #ifdef HAVE_TRACING
  TRACE_msg_vm_suspend(vm);
  #endif
}

/** @brief Immediately resumes the execution of all processes within the given VM.
 *  @ingroup msg_VMs
 *
 * No resume cost occurs. If you want to simulate this too, you want to
 * use a \ref MSG_file_read() before or after, depending on the exact semantic
 * of VM resume to you.
 */
void MSG_vm_resume(msg_vm_t vm) {
  unsigned int cpt;
  msg_process_t process;
  xbt_dynar_foreach(vm->processes,cpt,process) {
    XBT_DEBUG("resume process %s of host %s",MSG_process_get_name(process),MSG_host_get_name(MSG_process_get_host(process)));
    MSG_process_resume(process);
  }

  #ifdef HAVE_TRACING
  TRACE_msg_vm_resume(vm);
  #endif
}

/** @brief Immediately kills all processes within the given VM. Any memory that they allocated will be leaked.
 *  @ingroup msg_VMs
 *
 * No extra delay occurs. If you want to simulate this too, you want to
 * use a #MSG_process_sleep() or something. I'm not quite sure.
 */
void MSG_vm_shutdown(msg_vm_t vm)
{
  msg_process_t process;
  XBT_DEBUG("%lu processes in the VM", xbt_dynar_length(vm->processes));
  while (!xbt_dynar_is_empty(vm->processes)) {
    process = xbt_dynar_get_as(vm->processes,0,msg_process_t);
    MSG_process_kill(process);
  }

  #ifdef HAVE_TRACING
  TRACE_msg_vm_kill(vm);
  #endif

}

/**
 * \ingroup msg_VMs
 * \brief Reboot the VM, restarting all the processes in it.
 */
void MSG_vm_reboot(msg_vm_t vm)
{
  xbt_dynar_t process_list = xbt_dynar_new(sizeof(msg_process_t), NULL);
  msg_process_t process;
  unsigned int cpt;

  xbt_dynar_foreach(vm->processes, cpt, process) {
    xbt_dynar_push_as(process_list, msg_process_t, process);
  }

  xbt_dynar_foreach(process_list, cpt, process) {
    msg_process_t new_process = MSG_process_restart(process);
    MSG_vm_bind(vm, new_process);
  }

  xbt_dynar_free(&process_list);
}

/** @brief Destroy a msg_vm_t.
 *  @ingroup msg_VMs
 */
void MSG_vm_destroy(msg_vm_t vm) {
  unsigned int cpt;
  msg_process_t process;
  xbt_dynar_foreach(vm->processes,cpt,process) {
    //FIXME: Slow ?
    simdata_process_t simdata = simcall_process_get_data(process);
    simdata->vm = NULL;
  }

  #ifdef HAVE_TRACING
  TRACE_msg_vm_end(vm);
  #endif

  xbt_free(vm->name);
  xbt_dynar_free(&vm->processes);
  xbt_free(vm);
}
