#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
  int rank, size, next, prev, tag = 0;
  int x;
  MPI_Status status;

  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  next = (rank + 1) % size;
  prev = (rank - 1 + size) % size;

  if(rank == 0) {
    x = 0;
    printf("BCAST( root=P0, x=%d )\n", x);
    MPI_Bcast(&x, 1, MPI_INT, rank, MPI_COMM_WORLD);
    MPI_Bcast(&x, 1, MPI_INT, prev, MPI_COMM_WORLD);
    printf("BCAST_RECV( P0, root=P%d, x=%d ) // Execution Ending\n", prev, x);
  } else {
    MPI_Bcast(&x, 1, MPI_INT, prev, MPI_COMM_WORLD);
    printf("BCAST_RECV( P%d, root=P%d, x=%d )\n", rank, prev, x);
    x += rank;
    printf("BCAST( root=P%d, x=%d )\n", rank, x);
    MPI_Bcast(&x, 1, MPI_INT, rank, MPI_COMM_WORLD);
  }

  MPI_Finalize();

  return 0;
}
