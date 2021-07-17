#include <omp.h>
#include <stdio.h>

#include "timer.hpp"

int main() {
  const int n = 1000000;
  int i, a[n];
  long long sum;

  for(i = 0; i < n; i++) {
    a[i] = i;
  }

  sum = 0;

  {
    TIMER::precise_stopwatch sp;

    for(i = 0; i < n; i++) {
      sum += a[i] - (i & 1) * a[i];
    }
    printf("sum = %lld. ", sum);
  }

  return 0;
}