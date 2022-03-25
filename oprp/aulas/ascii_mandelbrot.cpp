#include <complex>
#include <iostream>

#include "timer.hpp"

int main() {
  int max_row, max_column, max_n;

#if 0
  std::cin >> max_row;
  std::cin >> max_column;
  std::cin >> max_n;
#else
  max_row = 32;
  max_column = 80;
  max_n = 240;
#endif

  char **mat = (char **)malloc(sizeof(char *) * max_row);

  for(int i = 0; i < max_row; i++) {
    mat[i] = (char *)malloc(sizeof(char *) * max_column);
  }

  //
  {
    TIMER::precise_stopwatch sp;

    for(int r = 0; r < max_row; r++) {
      for(int c = 0; c < max_column; c++) {
        std::complex<float> z;
        int n = 0;

        while(std::abs(z) < 2 && ++n < max_n) {
          z = std::pow(z, 2) +                      //
              decltype(z)(                          //
                  (float)c * 2 / max_column - 1.5,  //
                  (float)r * 2 / max_row - 1);
        }
        mat[r][c] = (n == max_n ? '#' : '.');
      }
    }
  }

  for(int r = 0; r < max_row; r++) {
    for(int c = 0; c < max_column; c++) {
      std::cout << mat[r][c];
    }
    std::cout << '\n';
  }
  std::cout << std::flush;

  //

  for(int i = 0; i < max_row; i++) {
    free(mat[i]);
  }
  free(mat);

  return 0;
}