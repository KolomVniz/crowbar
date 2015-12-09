#ifndef _RAN64_GSL__H_
#define _RAN64_GSL__H_

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <stdint.h>

/**
   Temporary interface to GSL Random Number Generation services
   Provides raw64, uniform_double, normal, exponential, and int range RNG.

   @code
   ran64_t *rng = ran64_open(YOUR_SEED);

   int64_t raw_unsigned_random = ran64_u(rng);
   double uniform_standard_random = ran64_flat(rng);
   double uniform_normal_random = ran64_gauss(rng);
   double uniform_exponential_random = ran64_expo(rng);
   int64_t range_int = ran64_urange(rng, YOUR_LIMIT); // 32-bit; limit < 2^32
   
   ran64_close(rng);
   @endcode

   Performance, Time to Billion: 8.4, 4.9, 8.9, 20.6, 17.6s on 4GHz Haswell
   
 */

/////////////////////////////////////////////////////////////////////////
// Interface
/////////////////////////////////////////////////////////////////////////

typedef void ran64_t;

ran64_t *
ran64_open(uint64_t seed);

void
ran64_close(ran64_t *rng);

/**
   Full 64-bit range integer
 */
static inline uint64_t
ran64_u(ran64_t *rng);

/**
   Random double in [0.0, 1.0)
 */
static inline double
ran64_flat(ran64_t *rng);


/**
   Normal distribution with sigma=1.0, mu=0.0
 */
static inline double
ran64_gauss(ran64_t *rng);

/**
   Exponenttial distribution with mu=1.0
 */
static inline double
ran64_expo(ran64_t *rng);

/**
   Equal probabilities integers for [0..limit-1]
   @warning In current implementation, only to 32-bit MAX limit allowed!
 */
static inline uint64_t
ran64_urange(ran64_t *rng, uint64_t limit);

/**
   Generate a random permutation of n index_sized entities in array a
 */
static inline void
ran64_shuffle(ran64_t *rng, uint64_t n, uintptr_t *a);

/////////////////////////////////////////////////////////////////////////
// Implementation
/////////////////////////////////////////////////////////////////////////

static inline uint64_t
ran64_u(ran64_t *rng) {
  uint64_t ret;
  gsl_rng *r = (gsl_rng *)rng;
  ret = gsl_rng_get(r);
  ret <<= 32;
  ret |= gsl_rng_get(r);
  return ret;
}

static inline double
ran64_flat(ran64_t *rng) {
  return gsl_rng_uniform((gsl_rng *)rng);
}

static inline double
ran64_gauss(ran64_t *rng) {
  return gsl_ran_gaussian_ziggurat((gsl_rng *)rng, 1.0);
}

static inline double
ran64_expo(ran64_t *rng) {
  return gsl_ran_exponential((gsl_rng *)rng, 1.0);
}

static inline uint64_t
ran64_urange(ran64_t *rng, uint64_t limit) {
  return gsl_rng_uniform_int((gsl_rng *)rng, (unsigned long)limit);
}

static inline void
ran64_shuffle(ran64_t *rng, uint64_t n, uintptr_t *a) {
  gsl_ran_shuffle(rng, a, n, sizeof(uintptr_t));
}

#endif

