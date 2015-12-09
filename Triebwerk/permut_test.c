#include "ran64_gsl.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


int
main() {
  const uintptr_t n = 20;
  ran64_t *rng = ran64_open(107);
  uintptr_t *a = (uintptr_t *)malloc(sizeof(uintptr_t)*n);
  for (uintptr_t i = 0; i < n; i++) {
    a[i] = i;
    printf("%3ld,", a[i]);
  }
  printf("\n");
  ran64_shuffle(rng, n, a);
  for (uintptr_t i = 0; i < n; i++) {
    printf("%3ld,", a[i]);
  }
  printf("\n");
  free(a);
  ran64_close(rng);
  return 0;
}
