/* Routine for setup and initialization of E-type functions. */

#include "internal.h"

/* **************************************************************** */

TVIL_ETYPE *TVIL_SetParamsE (TVIL_ETYPE *foo,
			     int whichfun,
			     TVIL_REAL x,
			     TVIL_REAL y,
			     TVIL_REAL z,
			     TVIL_REAL u)
{
  foo->which = whichfun;
  foo->arg[0] = x;
  foo->arg[1] = y;
  foo->arg[2] = z;
  foo->arg[3] = u;

  return foo;
}
