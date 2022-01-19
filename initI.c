/* Routines for setup and initialization of I-type functions */

#include "internal.h"

/* **************************************************************** */

TVIL_ITYPE *TVIL_SetParamsI (TVIL_ITYPE *foo,
	                     int whichfun,
			     TVIL_REAL x,
			     TVIL_REAL y,
			     TVIL_REAL z)
{
  if (whichfun == Iuvx) {
    foo->lnbarA1 = &_lnbarUg;
    foo->lnbarA2 = &_lnbarVg;
    foo->lnbarA3 = &_lnbarXg;
  }
  else if (whichfun == Ixyz) {
    foo->lnbarA1 = &_lnbarXg;
    foo->lnbarA2 = &_lnbarYg;
    foo->lnbarA3 = &_lnbarZg;
  }
  else if (whichfun == Iuxy) {
    foo->lnbarA1 = &_lnbarUg;
    foo->lnbarA2 = &_lnbarXg;
    foo->lnbarA3 = &_lnbarYg;
  }
  else if (whichfun == Ivxz) {
    foo->lnbarA1 = &_lnbarVg;
    foo->lnbarA2 = &_lnbarXg;
    foo->lnbarA3 = &_lnbarZg;
  }
  else if (whichfun == Iuwz) {
    foo->lnbarA1 = &_lnbarUg;
    foo->lnbarA2 = &_lnbarWg;
    foo->lnbarA3 = &_lnbarZg;
  }
  else if (whichfun == Ivwy) {
    foo->lnbarA1 = &_lnbarVg;
    foo->lnbarA2 = &_lnbarWg;
    foo->lnbarA3 = &_lnbarYg;
  }
  else if (whichfun == Iuwy) {
    foo->lnbarA1 = &_lnbarUg;
    foo->lnbarA2 = &_lnbarWg;
    foo->lnbarA3 = &_lnbarYg;
  }
  else if (whichfun == Ivwz) {
    foo->lnbarA1 = &_lnbarVg;
    foo->lnbarA2 = &_lnbarWg;
    foo->lnbarA3 = &_lnbarZg;
  }
  else if (whichfun == Ivyz) {
    foo->lnbarA1 = &_lnbarVg;
    foo->lnbarA2 = &_lnbarYg;
    foo->lnbarA3 = &_lnbarZg;
  }
  else if (whichfun == Iwxy) {
    foo->lnbarA1 = &_lnbarWg;
    foo->lnbarA2 = &_lnbarXg;
    foo->lnbarA3 = &_lnbarYg;
  }
  else if (whichfun == Iuvz) {
    foo->lnbarA1 = &_lnbarUg;
    foo->lnbarA2 = &_lnbarVg;
    foo->lnbarA3 = &_lnbarZg;
  }
  else if (whichfun == Iuwx) {
    foo->lnbarA1 = &_lnbarUg;
    foo->lnbarA2 = &_lnbarWg;
    foo->lnbarA3 = &_lnbarXg;
  }
  else if (whichfun == Iuyz) {
    foo->lnbarA1 = &_lnbarUg;
    foo->lnbarA2 = &_lnbarYg;
    foo->lnbarA3 = &_lnbarZg;
  }
  else if (whichfun == Iwxz) {
    foo->lnbarA1 = &_lnbarWg;
    foo->lnbarA2 = &_lnbarXg;
    foo->lnbarA3 = &_lnbarZg;
  }
  else if (whichfun == Iuvy) {
    foo->lnbarA1 = &_lnbarUg;
    foo->lnbarA2 = &_lnbarVg;
    foo->lnbarA3 = &_lnbarYg;
  }
  else if (whichfun == Ivwx) {
    foo->lnbarA1 = &_lnbarVg;
    foo->lnbarA2 = &_lnbarWg;
    foo->lnbarA3 = &_lnbarXg;
  }
  else
    TVIL_Error ("SetParamsI", "Invalid function type (variable which)", 55);

  foo->which = whichfun;
  foo->arg[0] = x;
  foo->arg[1] = y;
  foo->arg[2] = z;

  return foo;
}

/* **************************************************************** */

TVIL_ITYPE *TVIL_SetupI (TVIL_ITYPE *foo)
{
  int i;
  TVIL_REAL x, y, z;

  x = foo->arg[0];
  y = foo->arg[1];
  z = foo->arg[2];

  /* 
     For these arrays, the indices mean: 
     0 <-> +
     1 <-> -
     2 <-> 0
  */

  foo->p[0] = TVIL_Rplus (x, y, z);
  foo->p[1] = TVIL_Rminus (x, y, z);

  foo->cII[0] = foo->cII[1] = 0.5L;

  for (i=0; i<2; i++) {
    foo->cILL_012[i] = 0.25L*(_a + (foo->arg[0] + foo->arg[1] - foo->arg[2] - _a)*foo->p[i]);
    foo->cILL_021[i] = 0.25L*(_a + (foo->arg[0] + foo->arg[2] - foo->arg[1] - _a)*foo->p[i]);
    foo->cILL_120[i] = 0.25L*(_a + (foo->arg[1] + foo->arg[2] - foo->arg[0] - _a)*foo->p[i]);
  }

  for (i=0; i<2; i++) {
    foo->cIL_012[i] = (_a - foo->arg[0])*(foo->p[i]) - _a;
    foo->cIL_102[i] = (_a - foo->arg[1])*(foo->p[i]) - _a;
    foo->cIL_201[i] = (_a - foo->arg[2])*(foo->p[i]) - _a;
  }

  foo->cIL_012[2] = _a - foo->arg[0];
  foo->cIL_102[2] = _a - foo->arg[1];
  foo->cIL_201[2] = _a - foo->arg[2];

  for (i=0; i<2; i++)
    foo->cI[i] = 5.L*(3.L*_a + (foo->arg[0] + foo->arg[1] + foo->arg[2] - 3.L*_a)*foo->p[i])/4.L;

  foo->cI[2] = 2.L*(foo->arg[0] + foo->arg[1] + foo->arg[2]) - 6.0L*_a;

  return foo;
}

/* **************************************************************** */
