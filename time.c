/* $Id: time.c,v 1.1 2005/03/01 16:10:14 greg Exp $ */

#include <time.h>
#include <sys/timeb.h>
#include "a.h"
#include "spew.h"
#include "time.h"

double elapsed( void )
{
  static int first = 1;
  static struct timeb t0, now;
  time_t seconds;
  short milliseconds;

  ftime( &now );

  if (first) {
    t0 = now;
    first = 0;
  }

  A(t0.timezone == now.timezone);
  A(t0.dstflag == now.dstflag);

  seconds = now.time - t0.time;
  milliseconds = now.millitm - t0.millitm;

  return seconds + milliseconds / 1000.0;
}

void timespew( void )
{
  spew(( "ELAPSED %f\n", elapsed() ));
}
