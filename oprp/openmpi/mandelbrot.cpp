#include <mpi.h>

#include <complex>
#include <iostream>

int main(int argc, char **argv) {
  int max_row, max_column, max_n;
  int rank, size;
  int config[3];

  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if(rank == 0) {
    std::cin >> max_row, config[0] = max_row;
    std::cin >> max_column, config[1] = max_column;
    std::cin >> max_n, config[2] = max_n;
  }

  MPI_Bcast(config, 3, MPI_INT, 0, MPI_COMM_WORLD);

  if(rank != 0) {
    max_row = config[0];
    max_column = config[1];
    max_n = config[2];
  }

  char **mat = (char **)malloc(sizeof(char *) * max_row);
  /* aloca um bloco contiguo na memoria para ser usado como matriz */
  char *dados = (char *)malloc(sizeof(char) * max_row * max_column);
  for(int i = 0; i < max_row; i++)
    mat[i] = &dados[i * max_column];

  int start = rank * max_row / size;
  int end = (rank + 1) * max_row / size;
  int data_length = end - start;
  // std::cout << "rank=" << rank << " max_row=" << max_row << " max_column=" << max_column
  //           << " max_n=" << max_n << " start=" << start << " end=" << end << std::endl;

  char *temp = (char *)malloc(sizeof(char) * data_length * max_column);
  int i = 0;
  for(int r = start; r < end; ++r) {
    for(int c = 0; c < max_column; ++c) {
      std::complex<float> z;
      int n = 0;
      while(std::abs(z) < 2 && ++n < max_n)
        z = std::pow(z, 2) +
            decltype(z)((float)c * 2 / max_column - 1.5, (float)r * 2 / max_row - 1);
      temp[i++] = (n == max_n ? '#' : '.');
    }
  }

  // MPI_Send(temp, data_length, MPI_CHAR, 0, 0, MPI_COMM_WORLD);

  // if(rank == 0) {
  //   for(int i = 1; i < size; i++) {
  //     MPI_Recv(mat[data_length * i], data_length, MPI_CHAR, i, 0, MPI_COMM_WORLD,
  //              MPI_STATUS_IGNORE);
  //   }
  // }

  MPI_Gather(temp, max_column * data_length, MPI_CHAR, mat[0], max_column * data_length, MPI_CHAR,
             0, MPI_COMM_WORLD);

  if(rank == 0) {
    for(int r = 0; r < max_row; ++r) {
      for(int c = 0; c < max_column; ++c)
        std::cout << mat[r][c];
      std::cout << '\n';
    }
  }

  // MPI_Free_mem(temp);
  // for(int i = 0; i < max_row; i++) {
  //   MPI_Free_mem(mat[i]);
  // }
  // MPI_Free_mem(mat);
  // MPI_Free_mem(dados);

  // free(temp);
  // for(int i = 0; i < max_row; i++) {
  //   free(mat[i]);
  // }
  // free(mat);
  // free(dados);

  MPI_Finalize();
  return 0;
}
