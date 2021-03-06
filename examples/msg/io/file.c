/* Copyright (c) 2008, 2009, 2010. The SimGrid Team.
 * All rights reserved.                                                     */

/* This program is free software; you can redistribute it and/or modify it
 * under the terms of the license (GNU LGPL) which comes with this package. */

/** @addtogroup MSG_examples
 * 
 * @subsection MSG_ex_resources Other resource kinds
 * 
 * This section contains some sparse examples of how to use the other
 * kind of resources, such as disk or GPU. These resources are quite
 * experimental for now, but here we go anyway.
 * 
 * - <b>io/file.c</b> Example with the disk resource
 */

#define FILENAME1 "./doc/simgrid/examples/platforms/g5k.xml"
#define FILENAME2 "./doc/simgrid/examples/platforms/One_cluster_no_backbone.xml"
#define FILENAME3 "./doc/simgrid/examples/platforms/g5k_cabinets.xml"
#define FILENAME4 "./doc/simgrid/examples/platforms/nancy.xml"

#include <stdio.h>
#include <stdlib.h>
#include "msg/msg.h"
#include "surf/surf_private.h"

int host(int argc, char *argv[]);

XBT_LOG_NEW_DEFAULT_CATEGORY(io_file,
                             "Messages specific for this io example");

int host(int argc, char *argv[])
{
  msg_file_t file = NULL;
  void *ptr = NULL;
  char* mount = xbt_strdup("/home");
  size_t read,write;

  if(!strcmp(MSG_process_get_name(MSG_process_self()),"0"))
    file = MSG_file_open(mount,FILENAME1,"rw");
  else if(!strcmp(MSG_process_get_name(MSG_process_self()),"1"))
    file = MSG_file_open(mount,FILENAME2,"rw");
  else if(!strcmp(MSG_process_get_name(MSG_process_self()),"2"))
    file = MSG_file_open(mount,FILENAME3,"rw");
  else if(!strcmp(MSG_process_get_name(MSG_process_self()),"3"))
    file = MSG_file_open(mount,FILENAME4,"rw");
  else xbt_die("FILENAME NOT DEFINED %s",MSG_process_get_name(MSG_process_self()));

  XBT_INFO("\tOpen file '%s'",file->name);

  read = MSG_file_read(ptr,10000000,sizeof(char*),file);     // Read for 10MB
  XBT_INFO("\tHave read    %zu on %s",read,file->name);

  write = MSG_file_write(ptr,100000,sizeof(char*),file);  // Write for 100KB
  XBT_INFO("\tHave written %zu on %s",write,file->name);

  read = MSG_file_read(ptr,110000,sizeof(char*),file);     // Read for 110KB
  XBT_INFO("\tHave read    %zu on %s",read,file->name);

  XBT_INFO("\tClose file '%s'",file->name);
  MSG_file_close(file);

  free(mount);
  return 0;
}

int main(int argc, char **argv)
{
  int i,res;
  MSG_init(&argc, argv);
  MSG_create_environment(argv[1]);
  xbt_dynar_t hosts =  MSG_hosts_as_dynar();
  MSG_function_register("host", host);
  unsigned long nb_hosts = xbt_dynar_length(hosts);
  XBT_INFO("Number of host '%lu'",nb_hosts);
  for(i = 0 ; i<nb_hosts; i++)
  {
    char* name_host = bprintf("%d",i);
    MSG_process_create( name_host, host, NULL, xbt_dynar_get_as(hosts,i,msg_host_t) );
    free(name_host);
  }
  xbt_dynar_free(&hosts);

  res = MSG_main();
  XBT_INFO("Simulation time %g", MSG_get_clock());
  if (res == MSG_OK)
    return 0;
  else
    return 1;

}
