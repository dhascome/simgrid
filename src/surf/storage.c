/* Copyright (c) 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012. The SimGrid Team.
 * All rights reserved.                                                                 */

/* This program is free software; you can redistribute it and/or modify it
 * under the terms of the license (GNU LGPL) which comes with this package.             */

#include "xbt/ex.h"
#include "xbt/dict.h"
#include "portable.h"
#include "surf_private.h"
#include "surf/surf_resource.h"

XBT_LOG_NEW_DEFAULT_SUBCATEGORY(surf_storage, surf,
                                "Logging specific to the SURF storage module");

surf_model_t surf_storage_model = NULL;

typedef struct surf_storage {
  s_surf_resource_t generic_resource;
  const char* type;
  const char* content; /*should be a dict */
} s_surf_storage_t, *surf_storage_t;

static surf_action_t storage_action_open(void *storage, const char* path, const char* mode)
{
  return NULL;
}

static surf_action_t storage_action_close(void *storage, surf_file_t fp)
{
  return NULL;
}

static surf_action_t storage_action_read(void *storage, void* ptr, size_t size, size_t nmemb, surf_file_t stream)
{
  return NULL;
}

static surf_action_t storage_action_write(void *storage, const void* ptr, size_t size, size_t nmemb, surf_file_t stream)
{
  return NULL;
}

static surf_action_t storage_action_stat(void *storage, int fd, void* buf)
{
  return NULL;
}

static void* storage_create_resource(const char* id, const char* type,
                                    const char* content, xbt_dict_t storage_properties)
{
  xbt_assert(!surf_storage_resource_by_name(id),
      "Storage '%s' declared several times in the platform file",
      id);
  XBT_DEBUG("Storage_create_resource '%s' at level SURF_STORAGE_LEVEL",id);
  surf_storage_t storage = NULL;
  storage = (surf_storage_t) surf_resource_new(sizeof(s_surf_storage_t),
      surf_storage_model, id, storage_properties);
  storage->type = type;
  storage->content = content;
  xbt_lib_set(storage_lib, id, SURF_STORAGE_LEVEL, storage);

  return storage;
}

static void storage_finalize(void)
{
  surf_model_exit(surf_storage_model);
  surf_storage_model = NULL;
}

static void storage_update_actions_state(double now, double delta)
{

}

static double storage_share_resources(double NOW)
{
  double min_action_duration = -1;
  return min_action_duration;
}

static int storage_resource_used(void *resource_id)
{
  THROW_UNIMPLEMENTED;
  return 0;
}

static void storage_resources_state(void *id, tmgr_trace_event_t event_type,
                                 double value, double time)
{
  THROW_UNIMPLEMENTED;
}

static int storage_action_unref(surf_action_t action)
{
  THROW_UNIMPLEMENTED;
  return 0;
}

static void storage_action_cancel(surf_action_t action)
{
  THROW_UNIMPLEMENTED;
}

static void storage_action_state_set(surf_action_t action, e_surf_action_state_t state)
{
  THROW_UNIMPLEMENTED;
}

static void storage_action_suspend(surf_action_t action)
{
  THROW_UNIMPLEMENTED;
}

static void storage_action_resume(surf_action_t action)
{
  THROW_UNIMPLEMENTED;
}

static int storage_action_is_suspended(surf_action_t action)
{
  THROW_UNIMPLEMENTED;
  return 0;
}

static void storage_action_set_max_duration(surf_action_t action, double duration)
{
  THROW_UNIMPLEMENTED;
}

static void storage_action_set_priority(surf_action_t action, double priority)
{
  THROW_UNIMPLEMENTED;
}

static void parse_storage_init(sg_platf_storage_cbarg_t storage)
{
  XBT_INFO("parse_storage_init");
}

static void parse_mstorage_init(sg_platf_mstorage_cbarg_t mstorage)
{
  XBT_INFO("parse_mstorage_init");
}

static void parse_storage_type_init(sg_platf_storage_type_cbarg_t storagetype_)
{
  XBT_INFO("parse_storage_type_init");
}

static void parse_mount_init(sg_platf_mount_cbarg_t mount)
{
  XBT_INFO("parse_mount_init");
}

static void storage_define_callbacks()
{
  sg_platf_storage_add_cb(parse_storage_init);
  sg_platf_mstorage_add_cb(parse_mstorage_init);
  sg_platf_storage_type_add_cb(parse_storage_type_init);
  sg_platf_mount_add_cb(parse_mount_init);
}

static void surf_storage_model_init_internal(void)
{
  XBT_DEBUG("surf_storage_model_init_internal");
  surf_storage_model = surf_model_init();

  surf_storage_model->name = "Storage";
  surf_storage_model->action_unref = storage_action_unref;
  surf_storage_model->action_cancel = storage_action_cancel;
  surf_storage_model->action_state_set = storage_action_state_set;

  surf_storage_model->model_private->finalize = storage_finalize;
  surf_storage_model->model_private->update_actions_state = storage_update_actions_state;
  surf_storage_model->model_private->share_resources = storage_share_resources;
  surf_storage_model->model_private->resource_used = storage_resource_used;
  surf_storage_model->model_private->update_resource_state = storage_resources_state;

  surf_storage_model->suspend = storage_action_suspend;
  surf_storage_model->resume = storage_action_resume;
  surf_storage_model->is_suspended = storage_action_is_suspended;
  surf_storage_model->set_max_duration = storage_action_set_max_duration;
  surf_storage_model->set_priority = storage_action_set_priority;

  surf_storage_model->extension.storage.open = storage_action_open;
  surf_storage_model->extension.storage.close = storage_action_close;
  surf_storage_model->extension.storage.read = storage_action_read;
  surf_storage_model->extension.storage.write = storage_action_write;
  surf_storage_model->extension.storage.stat = storage_action_stat;
  surf_storage_model->extension.storage.create_resource = storage_create_resource;
}

void surf_storage_model_init_default(void)
{
  surf_storage_model_init_internal();
  storage_define_callbacks();

  xbt_dynar_push(model_list, &surf_storage_model);
}