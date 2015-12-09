#ifndef _CHRONO__H__
#define _CHRONO__H__

#include <sys/times.h>
#include <sys/resource.h>
#include <time.h>
#include <string.h>

#include <stdint.h>

/**
   Measures elapsed time in ns; usr & system in us (real resolution: 1ms)
   @code
   chrono_s chro;
   chrono_hit(&chro);
   // Do somehting...
   chrono_hit(&chro);
   uint64_t elapsed_ns = chrono_elapsed_ns(&chro);
   uint64_t user_time_us = chrono_user_us(&chro);
   uint64_t sys_time_us = chrono_sys_us(&chro);
   @endcode
*/


/////////////////////////////////////////////////////////////////////////
// Interface
/////////////////////////////////////////////////////////////////////////
typedef struct utstamp utstamp_s;
typedef struct chrono chrono_s;

static inline int64_t 
chrono_elapsed_ns(chrono_s *self);

static inline void
chrono_hit(chrono_s *self);

static inline int64_t 
chrono_user_us(chrono_s *self);

static inline int64_t 
chrono_sys_us(chrono_s *self);

/////////////////////////////////////////////////////////////////////////
// Implementation
/////////////////////////////////////////////////////////////////////////
struct utstamp {
  uint64_t realtime;
  uint64_t utime;
  uint64_t stime;
  uint64_t reserved;
};

struct chrono {
  utstamp_s zero;
  utstamp_s one;
  struct rusage usage_scr;
  struct timespec time_scr;
};

static inline void
chrono_hit(chrono_s *self) {
  const uint64_t OneMillion = 1000000;
  const uint64_t OneBillion = 1000000000;
  
  if (getrusage(RUSAGE_SELF, &self->usage_scr) != 0 ||
      clock_gettime(CLOCK_REALTIME, &self->time_scr) != 0) { // On error
    memset(&self->zero, 0,  sizeof(utstamp_s));
    memset(&self->one, 0,  sizeof(utstamp_s));
  }
  else {
    memcpy(&self->one, &self->zero, sizeof(utstamp_s));
    struct rusage *cs = &self->usage_scr;
    self->zero.utime = 
      cs->ru_utime.tv_sec*OneMillion + cs->ru_utime.tv_usec;
    self->zero.stime = 
      cs->ru_stime.tv_sec*OneMillion + cs->ru_stime.tv_usec;

    self->zero.realtime = 
      self->time_scr.tv_sec*OneBillion + self->time_scr.tv_nsec;
  }
}

static inline int64_t 
chrono_elapsed_ns(chrono_s *self) {
  return self->zero.realtime - self->one.realtime;
}

static inline int64_t 
chrono_user_us(chrono_s *self) {
  return self->zero.utime - self->one.utime;
}

static inline int64_t 
chrono_sys_us(chrono_s *self) {
  return self->zero.stime - self->one.stime;
}

#endif
