/* Copyright (c) 2009. The SimGrid Team.
 * All rights reserved.                                                     */

/* This program is free software; you can redistribute it and/or modify it
 * under the terms of the license (GNU LGPL) which comes with this package. */

#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
  int i, size, rank;
  int count = 2048;
  int *values;
  int status;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  values = (int *) xbt_malloc(count * sizeof(int));  

  for (i = 0; i < count; i++)
    values[i] = (0 == rank) ? 17 : 3;

  status = MPI_Bcast(values, count, MPI_INT, 0, MPI_COMM_WORLD);

  int good = 0;
  for (i = 0; i < count; i++)
    if (values[i]==17) good++;
  printf("[%d] number of values equals to 17: %d\n", rank, good);

  MPI_Barrier(MPI_COMM_WORLD);

  if (rank == 0) {
    if (status != MPI_SUCCESS) {
      printf("bcast returned %d\n", status);
      fflush(stdout);
    }
  }

  MPI_Finalize();
  return 0;
}
