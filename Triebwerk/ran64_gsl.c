#include "ran64_gsl.h"

/**
   Temporary interface to GSL RNG services
*/

ran64_t *
ran64_open(uint64_t seed) {
  gsl_rng *r;
  const gsl_rng_type *T = gsl_rng_mt19937;
  r = gsl_rng_alloc(T);
  gsl_rng_set(r, (unsigned long)seed);
  return (ran64_t *)r;
}

void
ran64_close(ran64_t *rng) {
  gsl_rng *r = (gsl_rng *)rng;
  gsl_rng_free(r);
}
