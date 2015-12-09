#include "ran64_gsl.h"
#include "chrono.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int
main() {
  ran64_t *rng = ran64_open(172);
  int64_t a = 1;
  //  double a = 0.0;
  chrono_s chro;
  chrono_hit(&chro);
  for (uintptr_t i = 0; i < 1000000000; i++) {
    //    int64_t rn = ran64_urange(rng, 1000);
    int64_t rn = ran64_u(rng);
    //    double rn = ran64_gauss(rng);
    a += rn;
  }
  chrono_hit(&chro);
  printf("%ld ns %ld us %ld us\n", 
	 chrono_elapsed_ns(&chro),
	 chrono_user_us(&chro),
	 chrono_sys_us(&chro)
	 );

  ran64_close(rng);

  return 0;
}
