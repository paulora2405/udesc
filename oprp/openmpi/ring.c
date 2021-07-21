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
    printf("SEND( P0 -> P%d, x=%d )\n", next, x);
    MPI_Send(&x, 1, MPI_INT, next, tag, MPI_COMM_WORLD);
    MPI_Recv(&x, 1, MPI_INT, prev, tag, MPI_COMM_WORLD, &status);
    printf("RECV( P0 <- P%d, x=%d ) // Execution Ending\n", prev, x);
  } else {
    MPI_Recv(&x, 1, MPI_INT, prev, tag, MPI_COMM_WORLD, &status);
    printf("RECV( P%d <- P%d, x=%d )\n", rank, prev, x);
    x += rank;
    printf("SEND( P%d -> P%d, x=%d )\n", rank, next, x);
    MPI_Send(&x, 1, MPI_INT, next, tag, MPI_COMM_WORLD);
  }

  MPI_Finalize();

  return 0;
}
