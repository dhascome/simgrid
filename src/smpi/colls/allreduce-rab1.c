#include "colls_private.h"
//#include <star-reduction.c>

// NP pow of 2 for now
int smpi_coll_tuned_allreduce_rab1(void *sbuff, void *rbuff,
                                   int count, MPI_Datatype dtype,
                                   MPI_Op op, MPI_Comm comm)
{
  MPI_Status status;
  MPI_Aint extent;
  int tag = 4321, rank, nprocs, send_size, newcnt, share;
  int pof2 = 1, mask, send_idx, recv_idx, dst, send_cnt, recv_cnt;

  void *recv, *tmp_buf;

  rank = smpi_comm_rank(comm);
  nprocs = smpi_comm_size(comm);

  extent = smpi_datatype_get_extent(dtype);

  pof2 = 1;
  while (pof2 <= nprocs)
    pof2 <<= 1;
  pof2 >>= 1;

  mask = 1;
  send_idx = recv_idx = 0;

  // uneven count
  if ((count % nprocs)) {
    send_size = (count + nprocs) / nprocs;
    newcnt = send_size * nprocs;

    recv = (void *) xbt_malloc(extent * newcnt);
    tmp_buf = (void *) xbt_malloc(extent * newcnt);
    memcpy(recv, sbuff, extent * count);


    mask = pof2 / 2;
    share = newcnt / pof2;
    while (mask > 0) {
      dst = rank ^ mask;
      send_cnt = recv_cnt = newcnt / (pof2 / mask);

      if (rank < dst)
        send_idx = recv_idx + (mask * share);
      else
        recv_idx = send_idx + (mask * share);

      smpi_mpi_sendrecv((char *) recv + send_idx * extent, send_cnt, dtype, dst, tag,
                   tmp_buf, recv_cnt, dtype, dst, tag, comm, &status);

      smpi_op_apply(op, tmp_buf, (char *) recv + recv_idx * extent, &recv_cnt,
                     &dtype);

      // update send_idx for next iteration 
      send_idx = recv_idx;
      mask >>= 1;
    }

    memcpy(tmp_buf, (char *) recv + recv_idx * extent, recv_cnt * extent);
    mpi_coll_allgather_fun(tmp_buf, recv_cnt, dtype, recv, recv_cnt, dtype, comm);

    memcpy(rbuff, recv, count * extent);
    free(recv);
    free(tmp_buf);

  }

  else {
    tmp_buf = (void *) xbt_malloc(extent * count);
    memcpy(rbuff, sbuff, count * extent);
    mask = pof2 / 2;
    share = count / pof2;
    while (mask > 0) {
      dst = rank ^ mask;
      send_cnt = recv_cnt = count / (pof2 / mask);

      if (rank < dst)
        send_idx = recv_idx + (mask * share);
      else
        recv_idx = send_idx + (mask * share);

      smpi_mpi_sendrecv((char *) rbuff + send_idx * extent, send_cnt, dtype, dst,
                   tag, tmp_buf, recv_cnt, dtype, dst, tag, comm, &status);

      smpi_op_apply(op, tmp_buf, (char *) rbuff + recv_idx * extent, &recv_cnt,
                     &dtype);

      // update send_idx for next iteration 
      send_idx = recv_idx;
      mask >>= 1;
    }

    memcpy(tmp_buf, (char *) rbuff + recv_idx * extent, recv_cnt * extent);
    mpi_coll_allgather_fun(tmp_buf, recv_cnt, dtype, rbuff, recv_cnt, dtype, comm);
    free(tmp_buf);
  }

  return MPI_SUCCESS;
}
