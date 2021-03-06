/* Copyright (c) 2007, 2008, 2009, 2010. The SimGrid Team.
 * All rights reserved.                                                     */

/* This program is free software; you can redistribute it and/or modify it
 * under the terms of the license (GNU LGPL) which comes with this package. */

#ifndef SMPI_H
#define SMPI_H

#include <stddef.h>
#include <sys/time.h>
#include <xbt/misc.h>
#include <xbt/function_types.h>


#ifdef _WIN32
#define MPI_CALL(type,name,args) \
  type name args; \
  type P##name args
#else
#define MPI_CALL(type,name,args) \
  type name args __attribute__((weak)); \
  type P##name args
#endif

SG_BEGIN_DECL()
#define MPI_THREAD_SINGLE     0
#define MPI_THREAD_FUNNELED   1
#define MPI_THREAD_SERIALIZED 2
#define MPI_THREAD_MULTIPLE   3
//FIXME: check values
#define MPI_MAX_PROCESSOR_NAME 100
#define MPI_MAX_NAME_STRING    100
#define MPI_MAX_ERROR_STRING   100
#define MPI_MAX_DATAREP_STRIN  100
#define MPI_MAX_INFO_KEY       100
#define MPI_MAX_INFO_VAL       100
#define MPI_MAX_OBJECT_NAME    100
#define MPI_MAX_PORT_NAME      100
#define SMPI_RAND_SEED 5
#define MPI_ANY_SOURCE -1
#define MPI_BOTTOM (void *)0
#define MPI_PROC_NULL -2
#define MPI_ANY_TAG -1
#define MPI_UNDEFINED -3
// errorcodes
#define MPI_SUCCESS       0
#define MPI_ERR_COMM      1
#define MPI_ERR_ARG       2
#define MPI_ERR_TYPE      3
#define MPI_ERR_REQUEST   4
#define MPI_ERR_INTERN    5
#define MPI_ERR_COUNT     6
#define MPI_ERR_RANK      7
#define MPI_ERR_TAG       8
#define MPI_ERR_TRUNCATE  9
#define MPI_ERR_GROUP    10
#define MPI_ERR_OP       11
#define MPI_ERR_OTHER    12
#define MPI_ERR_IN_STATUS 13
#define MPI_ERR_PENDING   14
#define MPI_IDENT     0
#define MPI_SIMILAR   1
#define MPI_UNEQUAL   2
#define MPI_CONGRUENT 3
#define MPI_WTIME_IS_GLOBAL 1
#define MPI_TAG_UB           1000000
#define MPI_HOST             0
#define MPI_IO               0
#define MPI_BSEND_OVERHEAD   0

typedef enum MPIR_Topo_type {
  MPI_GRAPH=1,
  MPI_CART=2,
  MPI_DIST_GRAPH=3
} MPIR_Topo_type;

typedef ptrdiff_t MPI_Aint;
typedef long long MPI_Offset;

struct s_smpi_mpi_datatype;
typedef struct s_smpi_mpi_datatype *MPI_Datatype;

typedef struct {
  int MPI_SOURCE;
  int MPI_TAG;
  int MPI_ERROR;
  int count;
} MPI_Status;

#define MPI_STATUS_IGNORE NULL
#define MPI_STATUSES_IGNORE NULL

#define MPI_DATATYPE_NULL NULL
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_CHAR;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_SHORT;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_INT;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_LONG;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_LONG_LONG;
#define MPI_LONG_LONG_INT MPI_LONG_LONG
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_SIGNED_CHAR;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_UNSIGNED_CHAR;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_UNSIGNED_SHORT;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_UNSIGNED;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_UNSIGNED_LONG;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_UNSIGNED_LONG_LONG;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_FLOAT;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_DOUBLE;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_LONG_DOUBLE;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_WCHAR;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_C_BOOL;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_INT8_T;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_INT16_T;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_INT32_T;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_INT64_T;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_UINT8_T;
#define MPI_BYTE MPI_UINT8_T
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_UINT16_T;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_UINT32_T;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_UINT64_T;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_C_FLOAT_COMPLEX;
#define MPI_C_COMPLEX MPI_C_FLOAT_COMPLEX
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_C_DOUBLE_COMPLEX;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_C_LONG_DOUBLE_COMPLEX;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_AINT;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_OFFSET;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_LB;
XBT_PUBLIC_DATA( MPI_Datatype ) MPI_UB;
//The following are datatypes for the MPI functions MPI_MAXLOC  and MPI_MINLOC.
XBT_PUBLIC_DATA(MPI_Datatype) MPI_FLOAT_INT;
XBT_PUBLIC_DATA(MPI_Datatype) MPI_LONG_INT;
XBT_PUBLIC_DATA(MPI_Datatype) MPI_DOUBLE_INT;
XBT_PUBLIC_DATA(MPI_Datatype) MPI_SHORT_INT;
XBT_PUBLIC_DATA(MPI_Datatype) MPI_2INT;
XBT_PUBLIC_DATA(MPI_Datatype) MPI_LONG_DOUBLE_INT;
XBT_PUBLIC_DATA(MPI_Datatype) MPI_2FLOAT;
XBT_PUBLIC_DATA(MPI_Datatype) MPI_2DOUBLE;

typedef void MPI_User_function(void *invec, void *inoutvec, int *len,
                               MPI_Datatype * datatype);
struct s_smpi_mpi_op;
typedef struct s_smpi_mpi_op *MPI_Op;

#define MPI_OP_NULL NULL
XBT_PUBLIC_DATA( MPI_Op ) MPI_MAX;
XBT_PUBLIC_DATA( MPI_Op ) MPI_MIN;
XBT_PUBLIC_DATA( MPI_Op ) MPI_MAXLOC;
XBT_PUBLIC_DATA( MPI_Op ) MPI_MINLOC;
XBT_PUBLIC_DATA( MPI_Op ) MPI_SUM;
XBT_PUBLIC_DATA( MPI_Op ) MPI_PROD;
XBT_PUBLIC_DATA( MPI_Op ) MPI_LAND;
XBT_PUBLIC_DATA( MPI_Op ) MPI_LOR;
XBT_PUBLIC_DATA( MPI_Op ) MPI_LXOR;
XBT_PUBLIC_DATA( MPI_Op ) MPI_BAND;
XBT_PUBLIC_DATA( MPI_Op ) MPI_BOR;
XBT_PUBLIC_DATA( MPI_Op ) MPI_BXOR;

struct s_smpi_mpi_group;
typedef struct s_smpi_mpi_group *MPI_Group;

#define MPI_GROUP_NULL NULL

XBT_PUBLIC_DATA( MPI_Group ) MPI_GROUP_EMPTY;

struct s_smpi_mpi_communicator;
typedef struct s_smpi_mpi_communicator *MPI_Comm;

#define MPI_COMM_NULL NULL
XBT_PUBLIC_DATA( MPI_Comm ) MPI_COMM_WORLD;
#define MPI_COMM_SELF smpi_process_comm_self()

struct s_smpi_mpi_request;
typedef struct s_smpi_mpi_request *MPI_Request;

#define MPI_REQUEST_NULL NULL

MPI_CALL(XBT_PUBLIC(int), MPI_Init, (int *argc, char ***argv));
MPI_CALL(XBT_PUBLIC(int), MPI_Finalize, (void));
MPI_CALL(XBT_PUBLIC(int), MPI_Init_thread,
                            (int *argc, char ***argv, int required,
                             int *provided));
MPI_CALL(XBT_PUBLIC(int), MPI_Query_thread, (int *provided));
MPI_CALL(XBT_PUBLIC(int), MPI_Is_thread_main, (int *flag));
MPI_CALL(XBT_PUBLIC(int), MPI_Abort, (MPI_Comm comm, int errorcode));
MPI_CALL(XBT_PUBLIC(double), MPI_Wtime, (void));
MPI_CALL(XBT_PUBLIC(double), MPI_Wtick,(void));
MPI_CALL(XBT_PUBLIC(int), MPI_Address, (void *location, MPI_Aint * address));

MPI_CALL(XBT_PUBLIC(int), MPI_Type_free, (MPI_Datatype * datatype));
MPI_CALL(XBT_PUBLIC(int), MPI_Type_size, (MPI_Datatype datatype, int *size));
MPI_CALL(XBT_PUBLIC(int), MPI_Type_get_extent,
                            (MPI_Datatype datatype, MPI_Aint * lb,
                             MPI_Aint * extent));
MPI_CALL(XBT_PUBLIC(int), MPI_Type_extent, (MPI_Datatype datatype, MPI_Aint * extent));
MPI_CALL(XBT_PUBLIC(int), MPI_Type_lb, (MPI_Datatype datatype, MPI_Aint * disp));
MPI_CALL(XBT_PUBLIC(int), MPI_Type_ub, (MPI_Datatype datatype, MPI_Aint * disp));
MPI_CALL(XBT_PUBLIC(int), MPI_Type_commit, (MPI_Datatype* datatype));
MPI_CALL(XBT_PUBLIC(int), MPI_Type_hindexed,
                            (int count, int* blocklens, MPI_Aint* indices,
                            MPI_Datatype old_type, MPI_Datatype* newtype));
MPI_CALL(XBT_PUBLIC(int), MPI_Type_hvector,
                            (int count, int blocklen, MPI_Aint stride,
                             MPI_Datatype old_type, MPI_Datatype* newtype));
MPI_CALL(XBT_PUBLIC(int), MPI_Type_indexed,
                            (int count, int* blocklens, int* indices,
                             MPI_Datatype old_type, MPI_Datatype* newtype));
MPI_CALL(XBT_PUBLIC(int), MPI_Type_struct,
                            (int count, int* blocklens, MPI_Aint* indices,
                             MPI_Datatype* old_types, MPI_Datatype* newtype));
MPI_CALL(XBT_PUBLIC(int), MPI_Type_vector,
                            (int count, int blocklen, int stride,
                             MPI_Datatype old_type, MPI_Datatype* newtype));
MPI_CALL(XBT_PUBLIC(int), MPI_Type_contiguous,
                            (int count, MPI_Datatype old_type,
                             MPI_Datatype* newtype));
MPI_CALL(XBT_PUBLIC(int), MPI_Testall,
                            (int count, MPI_Request* requests, int* flag,
                             MPI_Status* statuses));
MPI_CALL(XBT_PUBLIC(int), MPI_Op_create,
                            (MPI_User_function * function, int commute,
                             MPI_Op * op));
MPI_CALL(XBT_PUBLIC(int), MPI_Op_free, (MPI_Op * op));

MPI_CALL(XBT_PUBLIC(int), MPI_Group_free, (MPI_Group * group));
MPI_CALL(XBT_PUBLIC(int), MPI_Group_size, (MPI_Group group, int *size));
MPI_CALL(XBT_PUBLIC(int), MPI_Group_rank, (MPI_Group group, int *rank));
MPI_CALL(XBT_PUBLIC(int), MPI_Group_translate_ranks,
                            (MPI_Group group1, int n,
                             int *ranks1, MPI_Group group2,
                             int *ranks2));
MPI_CALL(XBT_PUBLIC(int), MPI_Group_compare,
                            (MPI_Group group1, MPI_Group group2,
                             int *result));
MPI_CALL(XBT_PUBLIC(int), MPI_Group_union,
                            (MPI_Group group1, MPI_Group group2,
                             MPI_Group * newgroup));
MPI_CALL(XBT_PUBLIC(int), MPI_Group_intersection,
                            (MPI_Group group1, MPI_Group group2,
                             MPI_Group * newgroup));
MPI_CALL(XBT_PUBLIC(int), MPI_Group_difference,
                            (MPI_Group group1, MPI_Group group2,
                             MPI_Group * newgroup));
MPI_CALL(XBT_PUBLIC(int), MPI_Group_incl,
                            (MPI_Group group, int n, int *ranks,
                             MPI_Group * newgroup));
MPI_CALL(XBT_PUBLIC(int), MPI_Group_excl,
                            (MPI_Group group, int n, int *ranks,
                             MPI_Group * newgroup));
MPI_CALL(XBT_PUBLIC(int), MPI_Group_range_incl,
                            (MPI_Group group, int n, int ranges[][3],
                             MPI_Group * newgroup));
MPI_CALL(XBT_PUBLIC(int), MPI_Group_range_excl,
                            (MPI_Group group, int n, int ranges[][3],
                             MPI_Group * newgroup));

MPI_CALL(XBT_PUBLIC(int), MPI_Comm_rank, (MPI_Comm comm, int *rank));
MPI_CALL(XBT_PUBLIC(int), MPI_Comm_size, (MPI_Comm comm, int *size));
MPI_CALL(XBT_PUBLIC(int), MPI_Comm_get_name, (MPI_Comm comm, char* name, int* len));
MPI_CALL(XBT_PUBLIC(int), MPI_Get_processor_name, (char *name, int *resultlen));
MPI_CALL(XBT_PUBLIC(int), MPI_Get_count,
                            (MPI_Status * status, MPI_Datatype datatype,
                             int *count));

MPI_CALL(XBT_PUBLIC(int), MPI_Comm_group, (MPI_Comm comm, MPI_Group * group));
MPI_CALL(XBT_PUBLIC(int), MPI_Comm_compare,
                            (MPI_Comm comm1, MPI_Comm comm2, int *result));
MPI_CALL(XBT_PUBLIC(int), MPI_Comm_dup, (MPI_Comm comm, MPI_Comm * newcomm));
MPI_CALL(XBT_PUBLIC(int), MPI_Comm_create,
                            (MPI_Comm comm, MPI_Group group, MPI_Comm * newcomm));
MPI_CALL(XBT_PUBLIC(int), MPI_Comm_free, (MPI_Comm * comm));
MPI_CALL(XBT_PUBLIC(int), MPI_Comm_disconnect, (MPI_Comm * comm));
MPI_CALL(XBT_PUBLIC(int), MPI_Comm_split, (MPI_Comm comm, int color, int key, MPI_Comm* comm_out));

MPI_CALL(XBT_PUBLIC(int), MPI_Send_init,
                            (void *buf, int count, MPI_Datatype datatype,
                             int dst, int tag, MPI_Comm comm,
                             MPI_Request * request));
MPI_CALL(XBT_PUBLIC(int), MPI_Recv_init,
                            (void *buf, int count, MPI_Datatype datatype,
                             int src, int tag, MPI_Comm comm,
                             MPI_Request * request));
MPI_CALL(XBT_PUBLIC(int), MPI_Start, (MPI_Request * request));
MPI_CALL(XBT_PUBLIC(int), MPI_Startall, (int count, MPI_Request * requests));
MPI_CALL(XBT_PUBLIC(int), MPI_Request_free, (MPI_Request * request));
MPI_CALL(XBT_PUBLIC(int), MPI_Irecv,
                            (void *buf, int count, MPI_Datatype datatype,
                             int src, int tag, MPI_Comm comm,
                             MPI_Request * request));
MPI_CALL(XBT_PUBLIC(int), MPI_Isend,
                            (void *buf, int count, MPI_Datatype datatype,
                             int dst, int tag, MPI_Comm comm,
                             MPI_Request * request));
MPI_CALL(XBT_PUBLIC(int), MPI_Recv,
                            (void *buf, int count, MPI_Datatype datatype,
                             int src, int tag, MPI_Comm comm,
                             MPI_Status * status));
MPI_CALL(XBT_PUBLIC(int), MPI_Send,
                            (void *buf, int count, MPI_Datatype datatype,
                             int dst, int tag, MPI_Comm comm));
MPI_CALL(XBT_PUBLIC(int), MPI_Sendrecv,
                            (void *sendbuf, int sendcount,
                             MPI_Datatype sendtype, int dst, int sendtag,
                             void *recvbuf, int recvcount,
                             MPI_Datatype recvtype, int src, int recvtag,
                             MPI_Comm comm, MPI_Status * status));
MPI_CALL(XBT_PUBLIC(int), MPI_Sendrecv_replace,
                            (void *buf, int count,
                             MPI_Datatype datatype, int dst,
                             int sendtag, int src, int recvtag,
                             MPI_Comm comm, MPI_Status * status));

MPI_CALL(XBT_PUBLIC(int), MPI_Test,
                            (MPI_Request * request, int *flag, MPI_Status* status));
MPI_CALL(XBT_PUBLIC(int), MPI_Testany,
                            (int count, MPI_Request requests[], int *index,
                             int *flag, MPI_Status * status));
MPI_CALL(XBT_PUBLIC(int), MPI_Wait, (MPI_Request * request, MPI_Status * status));
MPI_CALL(XBT_PUBLIC(int), MPI_Waitany,
                            (int count, MPI_Request requests[], int *index,
                             MPI_Status * status));
MPI_CALL(XBT_PUBLIC(int), MPI_Waitall,
                            (int count, MPI_Request requests[],
                             MPI_Status status[]));
MPI_CALL(XBT_PUBLIC(int), MPI_Waitsome,
                            (int incount, MPI_Request requests[],
                             int *outcount, int *indices,
                             MPI_Status status[]));
MPI_CALL(XBT_PUBLIC(int), MPI_Testsome,
                            (int incount, MPI_Request requests[],
                             int *outcount, int *indices,
                             MPI_Status status[]));
MPI_CALL(XBT_PUBLIC(int), MPI_Bcast,
                            (void *buf, int count, MPI_Datatype datatype,
                             int root, MPI_Comm comm));
MPI_CALL(XBT_PUBLIC(int), MPI_Barrier, (MPI_Comm comm));
MPI_CALL(XBT_PUBLIC(int), MPI_Gather,
                            (void *sendbuf, int sendcount,
                             MPI_Datatype sendtype, void *recvbuf,
                             int recvcount, MPI_Datatype recvtype, int root,
                             MPI_Comm comm));
MPI_CALL(XBT_PUBLIC(int), MPI_Gatherv,
                            (void *sendbuf, int sendcount,
                             MPI_Datatype sendtype, void *recvbuf,
                             int *recvcounts, int *displs,
                             MPI_Datatype recvtype, int root,
                             MPI_Comm comm));
MPI_CALL(XBT_PUBLIC(int), MPI_Allgather,
                            (void *sendbuf, int sendcount,
                             MPI_Datatype sendtype, void *recvbuf,
                             int recvcount, MPI_Datatype recvtype,
                             MPI_Comm comm));
MPI_CALL(XBT_PUBLIC(int), MPI_Allgatherv,
                            (void *sendbuf, int sendcount,
                             MPI_Datatype sendtype, void *recvbuf,
                             int *recvcounts, int *displs,
                             MPI_Datatype recvtype, MPI_Comm comm));
MPI_CALL(XBT_PUBLIC(int), MPI_Scatter,
                            (void *sendbuf, int sendcount,
                             MPI_Datatype sendtype, void *recvbuf,
                             int recvcount, MPI_Datatype recvtype, int root,
                             MPI_Comm comm));
MPI_CALL(XBT_PUBLIC(int), MPI_Scatterv,
                            (void *sendbuf, int *sendcounts, int *displs,
                             MPI_Datatype sendtype, void *recvbuf,
                             int recvcount, MPI_Datatype recvtype,
                             int root, MPI_Comm comm));
MPI_CALL(XBT_PUBLIC(int), MPI_Reduce,
                            (void *sendbuf, void *recvbuf, int count,
                             MPI_Datatype datatype, MPI_Op op, int root,
                             MPI_Comm comm));
MPI_CALL(XBT_PUBLIC(int), MPI_Allreduce,
                            (void *sendbuf, void *recvbuf, int count,
                             MPI_Datatype datatype, MPI_Op op,
                             MPI_Comm comm));
MPI_CALL(XBT_PUBLIC(int), MPI_Scan,
                            (void *sendbuf, void *recvbuf, int count,
                             MPI_Datatype datatype, MPI_Op op, MPI_Comm comm));
MPI_CALL(XBT_PUBLIC(int), MPI_Reduce_scatter,
                            (void *sendbuf, void *recvbuf,
                             int *recvcounts, MPI_Datatype datatype,
                             MPI_Op op, MPI_Comm comm));
MPI_CALL(XBT_PUBLIC(int), MPI_Alltoall,
                            (void *sendbuf, int sendcount,
                             MPI_Datatype sendtype, void *recvbuf,
                             int recvcount, MPI_Datatype recvtype,
                             MPI_Comm comm));
MPI_CALL(XBT_PUBLIC(int), MPI_Alltoallv,
                            (void *sendbuf, int *sendcounts,
                             int *senddisps, MPI_Datatype sendtype,
                             void *recvbuf, int *recvcounts,
                             int *recvdisps, MPI_Datatype recvtype,
                             MPI_Comm comm));
MPI_CALL(XBT_PUBLIC(int), MPI_Iprobe,
                            (int source, int tag, MPI_Comm comm,
                             int* flag, MPI_Status* status));
MPI_CALL(XBT_PUBLIC(int), MPI_Probe,
                            (int source, int tag, MPI_Comm comm,
                             MPI_Status* status));


//FIXME: these are not yet implemented

typedef void MPI_Handler_function(MPI_Comm*, int*, ...);
typedef int MPI_Win;
typedef int MPI_Info;
typedef void* MPI_Errhandler;
typedef int MPI_Copy_function(MPI_Comm oldcomm, int keyval, void* extra_state, void* attribute_val_in,
                              void* attribute_val_out, int* flag);
typedef int MPI_Delete_function(MPI_Comm comm, int keyval, void* attribute_val, void* extra_state);

XBT_PUBLIC_DATA(MPI_Datatype)  MPI_PACKED;
XBT_PUBLIC_DATA(MPI_Errhandler*)  MPI_ERRORS_RETURN;
XBT_PUBLIC_DATA(MPI_Errhandler*)  MPI_ERRORS_ARE_FATAL;
XBT_PUBLIC_DATA(MPI_Errhandler*)  MPI_ERRHANDLER_NULL;


MPI_CALL(XBT_PUBLIC(int), MPI_Pack_size, (int incount, MPI_Datatype datatype, MPI_Comm comm, int* size));
MPI_CALL(XBT_PUBLIC(int), MPI_Cart_coords, (MPI_Comm comm, int rank, int maxdims, int* coords));
MPI_CALL(XBT_PUBLIC(int), MPI_Cart_create, (MPI_Comm comm_old, int ndims, int* dims, int* periods, int reorder, MPI_Comm* comm_cart));
MPI_CALL(XBT_PUBLIC(int), MPI_Cart_get, (MPI_Comm comm, int maxdims, int* dims, int* periods, int* coords));
MPI_CALL(XBT_PUBLIC(int), MPI_Cart_map, (MPI_Comm comm_old, int ndims, int* dims, int* periods, int* newrank));
MPI_CALL(XBT_PUBLIC(int), MPI_Cart_rank, (MPI_Comm comm, int* coords, int* rank));
MPI_CALL(XBT_PUBLIC(int), MPI_Cart_shift, (MPI_Comm comm, int direction, int displ, int* source, int* dest));
MPI_CALL(XBT_PUBLIC(int), MPI_Cart_sub, (MPI_Comm comm, int* remain_dims, MPI_Comm* comm_new));
MPI_CALL(XBT_PUBLIC(int), MPI_Cartdim_get, (MPI_Comm comm, int* ndims));
MPI_CALL(XBT_PUBLIC(int), MPI_Graph_create, (MPI_Comm comm_old, int nnodes, int* index, int* edges, int reorder, MPI_Comm* comm_graph));
MPI_CALL(XBT_PUBLIC(int), MPI_Graph_get, (MPI_Comm comm, int maxindex, int maxedges, int* index, int* edges));
MPI_CALL(XBT_PUBLIC(int), MPI_Graph_map, (MPI_Comm comm_old, int nnodes, int* index, int* edges, int* newrank));
MPI_CALL(XBT_PUBLIC(int), MPI_Graph_neighbors, (MPI_Comm comm, int rank, int maxneighbors, int* neighbors));
MPI_CALL(XBT_PUBLIC(int), MPI_Graph_neighbors_count, (MPI_Comm comm, int rank, int* nneighbors));
MPI_CALL(XBT_PUBLIC(int), MPI_Graphdims_get, (MPI_Comm comm, int* nnodes, int* nedges));
MPI_CALL(XBT_PUBLIC(int), MPI_Topo_test, (MPI_Comm comm, int* top_type));
MPI_CALL(XBT_PUBLIC(int), MPI_Error_class, (int errorcode, int* errorclass));
MPI_CALL(XBT_PUBLIC(int), MPI_Errhandler_create, (MPI_Handler_function* function, MPI_Errhandler* errhandler));
MPI_CALL(XBT_PUBLIC(int), MPI_Errhandler_free, (MPI_Errhandler* errhandler));
MPI_CALL(XBT_PUBLIC(int), MPI_Errhandler_get, (MPI_Comm comm, MPI_Errhandler* errhandler));
MPI_CALL(XBT_PUBLIC(int), MPI_Error_string, (int errorcode, char* string, int* resultlen));
MPI_CALL(XBT_PUBLIC(int), MPI_Errhandler_set, (MPI_Comm comm, MPI_Errhandler errhandler));
MPI_CALL(XBT_PUBLIC(int), MPI_Cancel, (MPI_Request* request));
MPI_CALL(XBT_PUBLIC(int), MPI_Buffer_attach, (void* buffer, int size));
MPI_CALL(XBT_PUBLIC(int), MPI_Buffer_detach, (void* buffer, int* size));
MPI_CALL(XBT_PUBLIC(int), MPI_Comm_test_inter, (MPI_Comm comm, int* flag));
MPI_CALL(XBT_PUBLIC(int), MPI_Comm_get_attr, (MPI_Comm comm, int comm_keyval, void *attribute_val, int *flag));
MPI_CALL(XBT_PUBLIC(int), MPI_Unpack, (void* inbuf, int insize, int* position, void* outbuf, int outcount, MPI_Datatype type, MPI_Comm comm));
MPI_CALL(XBT_PUBLIC(int), MPI_Ssend, (void* buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm));
MPI_CALL(XBT_PUBLIC(int), MPI_Ssend_init, (void* buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request* request));
MPI_CALL(XBT_PUBLIC(int), MPI_Intercomm_create, (MPI_Comm local_comm, int local_leader, MPI_Comm peer_comm, int remote_leader, int tag, MPI_Comm* comm_out));
MPI_CALL(XBT_PUBLIC(int), MPI_Intercomm_merge, (MPI_Comm comm, int high, MPI_Comm* comm_out));
MPI_CALL(XBT_PUBLIC(int), MPI_Bsend, (void* buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm));
MPI_CALL(XBT_PUBLIC(int), MPI_Bsend_init, (void* buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request* request));
MPI_CALL(XBT_PUBLIC(int), MPI_Ibsend, (void* buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request* request));
MPI_CALL(XBT_PUBLIC(int), MPI_Comm_remote_group, (MPI_Comm comm, MPI_Group* group));
MPI_CALL(XBT_PUBLIC(int), MPI_Comm_remote_size, (MPI_Comm comm, int* size));
MPI_CALL(XBT_PUBLIC(int), MPI_Issend, (void* buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request* request));
MPI_CALL(XBT_PUBLIC(int), MPI_Attr_delete, (MPI_Comm comm, int keyval));
MPI_CALL(XBT_PUBLIC(int), MPI_Attr_get, (MPI_Comm comm, int keyval, void* attr_value, int* flag));
MPI_CALL(XBT_PUBLIC(int), MPI_Attr_put, (MPI_Comm comm, int keyval, void* attr_value));
MPI_CALL(XBT_PUBLIC(int), MPI_Rsend, (void* buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm));
MPI_CALL(XBT_PUBLIC(int), MPI_Rsend_init, (void* buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request* request));
MPI_CALL(XBT_PUBLIC(int), MPI_Irsend, (void* buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request* request));
MPI_CALL(XBT_PUBLIC(int), MPI_Keyval_create, (MPI_Copy_function* copy_fn, MPI_Delete_function* delete_fn, int* keyval, void* extra_state));
MPI_CALL(XBT_PUBLIC(int), MPI_Keyval_free, (int* keyval));
MPI_CALL(XBT_PUBLIC(int), MPI_Test_cancelled, (MPI_Status* status, int* flag));
MPI_CALL(XBT_PUBLIC(int), MPI_Pack, (void* inbuf, int incount, MPI_Datatype type, void* outbuf, int outcount, int* position, MPI_Comm comm));
MPI_CALL(XBT_PUBLIC(int), MPI_Get_elements, (MPI_Status* status, MPI_Datatype datatype, int* elements));
MPI_CALL(XBT_PUBLIC(int), MPI_Dims_create, (int nnodes, int ndims, int* dims));
MPI_CALL(XBT_PUBLIC(int), MPI_Initialized, (int* flag));
MPI_CALL(XBT_PUBLIC(int), MPI_Pcontrol, (const int level ));
MPI_CALL(XBT_PUBLIC(int), MPI_Win_fence,( int assert,  MPI_Win win));
MPI_CALL(XBT_PUBLIC(int), MPI_Win_free,( MPI_Win* win));
MPI_CALL(XBT_PUBLIC(int), MPI_Win_create,( void *base, MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win));
MPI_CALL(XBT_PUBLIC(int), MPI_Info_create,( MPI_Info *info));
MPI_CALL(XBT_PUBLIC(int), MPI_Info_set,( MPI_Info *info, char *key, char *value));
MPI_CALL(XBT_PUBLIC(int), MPI_Info_free,( MPI_Info *info));
MPI_CALL(XBT_PUBLIC(int), MPI_Get,( void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank,
    MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win));

//FIXME: End of all the not yet implemented stuff

// smpi functions
XBT_PUBLIC(MPI_Comm) smpi_process_comm_self(void);
/*
XBT_PUBLIC(void) smpi_exit(int);
*/

XBT_PUBLIC(unsigned int) smpi_sleep(unsigned int secs);
XBT_PUBLIC(int) smpi_gettimeofday(struct timeval *tv);
XBT_PUBLIC(unsigned long long) smpi_rastro_resolution (void);
XBT_PUBLIC(unsigned long long) smpi_rastro_timestamp (void);
XBT_PUBLIC(void) smpi_sample_1(int global, const char *file, int line,
                              int iters, double threshold);
XBT_PUBLIC(int) smpi_sample_2(int global, const char *file, int line);
XBT_PUBLIC(void) smpi_sample_3(int global, const char *file, int line);

#define SMPI_SAMPLE_LOCAL(iters,thres) for(smpi_sample_1(0, __FILE__, __LINE__, iters, thres); \
                                           smpi_sample_2(0, __FILE__, __LINE__);      \
                                           smpi_sample_3(0, __FILE__, __LINE__))

#define SMPI_SAMPLE_GLOBAL(iters,thres) for(smpi_sample_1(1, __FILE__, __LINE__, iters, thres); \
                                            smpi_sample_2(1, __FILE__, __LINE__);      \
                                            smpi_sample_3(1, __FILE__, __LINE__))

#define SMPI_SAMPLE_DELAY(duration) for(smpi_execute(duration); 0; )
#define SMPI_SAMPLE_FLOPS(flops) for(smpi_execute_flops(flops); 0; )

XBT_PUBLIC(void *) smpi_shared_malloc(size_t size, const char *file,
                                      int line);
#define SMPI_SHARED_MALLOC(size) smpi_shared_malloc(size, __FILE__, __LINE__)

XBT_PUBLIC(void) smpi_shared_free(void *data);
#define SMPI_SHARED_FREE(data) smpi_shared_free(data)

XBT_PUBLIC(int) smpi_shared_known_call(const char* func, const char* input);
XBT_PUBLIC(void*) smpi_shared_get_call(const char* func, const char* input);
XBT_PUBLIC(void*) smpi_shared_set_call(const char* func, const char* input, void* data);
#define SMPI_SHARED_CALL(func, input, ...) \
   (smpi_shared_known_call(#func, input) ? smpi_shared_get_call(#func, input) \
                                         : smpi_shared_set_call(#func, input, func(__VA_ARGS__)))

/* Fortran specific stuff */
XBT_PUBLIC(int) __attribute__((weak)) smpi_simulated_main_(int argc, char** argv);
XBT_PUBLIC(int) __attribute__((weak)) MAIN__(void);
XBT_PUBLIC(int) smpi_main(int (*realmain) (int argc, char *argv[]),int argc, char *argv[]);
XBT_PUBLIC(void) __attribute__((weak)) user_main_(void);

XBT_PUBLIC(int) smpi_process_index(void);

/* Trace replay specific stuff */
XBT_PUBLIC(void) smpi_replay_init(int *argc, char***argv);
XBT_PUBLIC(void) smpi_action_trace_run(char *);
XBT_PUBLIC(int) smpi_replay_finalize(void);

SG_END_DECL()
#endif
