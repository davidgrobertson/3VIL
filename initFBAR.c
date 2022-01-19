#define CONDITIONAL ((TVIL_FABS(deltaxyzu/(x*x + y*y + z*z + u*u + 1e-99)) > TVIL_TOL) && ((TVIL_FABS((x-y)/(x+y + 1e-99)) > TVIL_TOL) || (TVIL_FABS((z-u)/(z+u + 1e-99)) > TVIL_TOL)) && ((TVIL_FABS((x-z)/(x+z + 1e-99)) > TVIL_TOL) || (TVIL_FABS((y-u)/(y+u + 1e-99)) > TVIL_TOL)) && ((TVIL_FABS((x-u)/(x-u + 1e-99)) > TVIL_TOL) || (TVIL_FABS((y-z)/(y+z + 1e-99)) > TVIL_TOL)) )

/* Routines for setup and initialization of Fbar-type functions */

#include "internal.h"

TVIL_REAL TVIL_cFF22 (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL u)
{
  TVIL_REAL deltaxyzu = TVIL_Delta (x,y,z,u);

  if CONDITIONAL 
    return ((x - y)*(u - x - y + z))/deltaxyzu;
  else 
    return 0.25L;
}

/* **************************************************************** */

TVIL_REAL TVIL_cFF23 (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL u)
{
  TVIL_REAL deltaxyzu = TVIL_Delta (x,y,z,u);

  if CONDITIONAL
    return 0.25L - TVIL_cFF22 (x,y,z,u);
  else
    return 0.0L;
}

/* **************************************************************** */

TVIL_REAL TVIL_cFLLL12 (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL u)
{
  TVIL_REAL deltaxyzu = TVIL_Delta (x,y,z,u);

  if CONDITIONAL
    return (2*_a*(u - x)*(x - y)*(x - z))/((_a - x)*deltaxyzu);
  else 
    return _a*(3*x - u - y - z)/(8*(_a - x));
}

/* **************************************************************** */

TVIL_REAL TVIL_cFLLL13 (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL u)
{
  TVIL_REAL deltaxyzu = TVIL_Delta (x,y,z,u);
  TVIL_REAL phixyzu = TVIL_Phi (x,y,z,u);
  TVIL_REAL deltazxyu, deltauxyz, deltayxzu;

  if CONDITIONAL {
    deltazxyu = TVIL_Delta(z,x,y,u);
    deltauxyz = TVIL_Delta(u,x,y,z);
    deltayxzu = TVIL_Delta(y,x,z,u);

    return (_a*deltazxyu*deltauxyz*deltayxzu)/(4*deltaxyzu*phixyzu);
  }
  else
    return 0.0L;
}

/* **************************************************************** */

TVIL_REAL TVIL_cFLLL23 (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL u)
{
  TVIL_REAL deltaxyzu = TVIL_Delta (x,y,z,u);
  TVIL_REAL phixyzu = TVIL_Phi (x,y,z,u);
  TVIL_REAL deltazxyu, deltayxzu;

  if CONDITIONAL {
    deltazxyu = TVIL_Delta(z,x,y,u);
    deltayxzu = TVIL_Delta(y,x,z,u);

    return _a*deltazxyu*deltayxzu/(4*phixyzu);
  }
  else
    return (_a*(u + x - y - z))/(8*(_a - x));
}

/* **************************************************************** */

TVIL_REAL TVIL_cFLLL24 (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL u)
{
  return 0.25L*(_a + TVIL_Rplus (y,z,u)*(-_a - u + y + z));
}

/* **************************************************************** */

TVIL_REAL TVIL_cFLLL25 (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL u)
{
  return 0.25L*(_a + TVIL_Rminus (y,z,u)*(-_a - u + y + z));
}

/* **************************************************************** */

TVIL_REAL TVIL_cFLL12 (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL u)
{
  TVIL_REAL deltaxyzu = TVIL_Delta (x,y,z,u);

  if CONDITIONAL
    return 4*_a*(x - u)*(x - y)*(x - z)/((_a - x) * deltaxyzu);
  else
    return (_a*(y + z - 2*x))/(2*(_a - x));
}

/* **************************************************************** */

TVIL_REAL TVIL_cFLL13 (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL u)
{
  TVIL_REAL deltaxyzu = TVIL_Delta (x,y,z,u);
  TVIL_REAL phixyzu = TVIL_Phi (x,y,z,u);
  TVIL_REAL deltazxyu,  deltayxzu;

  if CONDITIONAL {
    deltazxyu = TVIL_Delta(z,x,y,u);
    deltayxzu = TVIL_Delta(y,x,z,u);

    return (_a*(u - x + y - z)*(u - x - y + z)*deltazxyu*deltayxzu)/
      (deltaxyzu*phixyzu);
  }
  else
    return 0.0L;
}

/* **************************************************************** */

TVIL_REAL TVIL_cFLL23 (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL u)
{
  TVIL_REAL deltaxyzu = TVIL_Delta (x,y,z,u);
  TVIL_REAL phixyzu = TVIL_Phi (x,y,z,u);
  TVIL_REAL deltayxzu;

  if CONDITIONAL {
    deltayxzu = TVIL_Delta(y,x,z,u);
    return _a*(u + x - y - z)*(u - x + y - z)*deltayxzu/phixyzu;
  }
  else
    return _a*(y - x)/(2*(_a - x));
}

/* **************************************************************** */

TVIL_REAL TVIL_cFLL24 (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL u)
{
  return -_a + TVIL_Rplus (y,z,u)*(_a - y);
}

/* **************************************************************** */

TVIL_REAL TVIL_cFLL25 (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL u)
{
  return -_a + TVIL_Rminus (y,z,u)*(_a - y);
}

/* **************************************************************** */

TVIL_REAL TVIL_cFL10 (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL u)
{
  return x - _a;
}

/* **************************************************************** */

TVIL_REAL TVIL_cFL13 (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL u)
{
  TVIL_REAL deltaxyzu = TVIL_Delta (x,y,z,u);
  TVIL_REAL phixyzu = TVIL_Phi (x,y,z,u);
  TVIL_REAL x2, x3, x4;
  TVIL_REAL y2, y3, y4;
  TVIL_REAL z2, z3, z4;
  TVIL_REAL u2, u3, u4;

  if CONDITIONAL {
    x2 = x*x; x3 = x2*x; x4 = x2*x2;
    y2 = y*y; y3 = y2*y; y4 = y2*y2;
    z2 = z*z; z3 = z2*z; z4 = z2*z2;
    u2 = u*u; u3 = u2*u; u4 = u2*u2;

    return -(_a*(101*u4 - 236*u3*x + 118*u2*x2 + 68*u*x3 - 51*x4 -
		84*u3*y + 236*u2*x*y - 220*u*x2*y + 68*x3*y - 34*u2*y2 +
		236*u*x*y2 + 118*x2*y2 - 84*u*y3 - 236*x*y3 + 101*y4 - 84*u3*z +
		236*u2*x*z - 220*u*x2*z + 68*x3*z + 84*u2*y*z - 504*u*x*y*z -
		220*x2*y*z + 84*u*y2*z + 236*x*y2*z - 84*y3*z - 34*u2*z2 +
		236*u*x*z2 + 118*x2*z2 + 84*u*y*z2 + 236*x*y*z2 - 34*y2*z2 -
		84*u*z3 - 236*x*z3 - 84*y*z3 + 101*z4))/(16*phixyzu);
  }
  else
    return 5*_a*(3*x - u - y - z)/(8*(_a - x));
}

/* **************************************************************** */

TVIL_REAL TVIL_cFL14 (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL u)
{
  return 15*_a/4 + TVIL_Rplus (y,z,u)*5*(u + y + z - 3*_a)/4;
}

/* **************************************************************** */

TVIL_REAL TVIL_cFL15 (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL u)
{
  return 15*_a/4 + TVIL_Rminus (y,z,u)*5*(u + y + z - 3*_a)/4;
}

/* **************************************************************** */

TVIL_REAL TVIL_cFL20 (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL u)
{
  return _a - y;
}

/* **************************************************************** */

TVIL_REAL TVIL_cFL22 (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL u)
{
  TVIL_REAL deltaxyzu = TVIL_Delta (x,y,z,u);

  if CONDITIONAL
    return (_a*(y - x)*(4*u*u - 33*u*x + 29*x*x - 7*u*y + 8*x*y + 3*y*y 
      + 32*u*z - 33*x*z - 7*y*z + 4*z*z))/(4*(_a - x)*deltaxyzu);
  else
    return (5*_a*(7*x - 2*u - 3*y - 2*z))/(16*(_a - x));
}

/* **************************************************************** */

TVIL_REAL TVIL_cFL23 (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL u)
{
  TVIL_REAL deltaxyzu = TVIL_Delta (x,y,z,u);
  TVIL_REAL phixyzu = TVIL_Phi (x,y,z,u);
  TVIL_REAL deltayxzu;
  TVIL_REAL x2, x3, x4;
  TVIL_REAL y2, y3, y4;
  TVIL_REAL z2, z3, z4;
  TVIL_REAL u2, u3, u4;

  if CONDITIONAL {
    deltayxzu = TVIL_Delta (y,x,z,u);
    x2 = x*x; x3 = x2*x; x4 = x2*x2;
    y2 = y*y; y3 = y2*y; y4 = y2*y2;
    z2 = z*z; z3 = z2*z; z4 = z2*z2;
    u2 = u*u; u3 = u2*u; u4 = u2*u2;

    return -(_a*(101*u4 - 84*u3*x - 34*u2*x2 - 84*u*x3 + 101*x4 -
		236*u3*y + 236*u2*x*y + 236*u*x2*y - 236*x3*y + 118*u2*y2 -
		220*u*x*y2 + 118*x2*y2 + 68*u*y3 + 68*x*y3 - 51*y4 - 84*u3*z +
		84*u2*x*z + 84*u*x2*z - 84*x3*z + 236*u2*y*z - 504*u*x*y*z +
		236*x2*y*z - 220*u*y2*z - 220*x*y2*z + 68*y3*z - 34*u2*z2 +
		84*u*x*z2 - 34*x2*z2 + 236*u*y*z2 + 236*x*y*z2 + 118*y2*z2 -
		84*u*z3 - 84*x*z3 - 236*y*z3 +
		101*z4))*deltayxzu/(16*deltaxyzu*phixyzu);
  }
  else
    return 0.0L;
}

/* **************************************************************** */

TVIL_REAL TVIL_cF0 (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL u)
{
  return (-13*_a - 11*x + 8*u + 8*y + 8*z)/4;
}

/* **************************************************************** */

TVIL_REAL TVIL_cF2 (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL u)
{
  TVIL_REAL deltaxyzu = TVIL_Delta (x,y,z,u);
  TVIL_REAL x2, x3;
  TVIL_REAL y2, y3;
  TVIL_REAL z2, z3;
  TVIL_REAL u2, u3;

  if CONDITIONAL {
    x2 = x*x; x3 = x2*x;
    y2 = y*y; y3 = y2*y;
    z2 = z*z; z3 = z2*z;
    u2 = u*u; u3 = u2*u;

    return (_a*(-17*u3 + 17*u2*x - 117*u*x2 + 117*x3 + 17*u2*y + 100*u*x*y -
	       117*x2*y + 17*u*y2 + 17*x*y2 - 17*y3 + 17*u2*z + 100*u*x*z -
	       117*x2*z - 168*u*y*z + 100*x*y*z + 17*y2*z + 17*u*z2 + 17*x*z2 +
	       17*y*z2 - 17*z3))/(12*(_a - x)*deltaxyzu);
  }
  else
    return 67*_a*(u + y + z - 3*x)/(48*(_a - x));
}

/* **************************************************************** */

TVIL_REAL TVIL_cF3 (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL u)
{
  TVIL_REAL deltaxyzu = TVIL_Delta (x,y,z,u);
  TVIL_REAL phixyzu = TVIL_Phi (x,y,z,u);

  if CONDITIONAL {
    return (45*_a*TVIL_POW((u + x - y - z)*(u - x + y - z)*(u - x - y + z),2))/
      (2*deltaxyzu*phixyzu);
  }
  else
    return 0.0L;
}

/* **************************************************************** */
/* **************************************************************** */

TVIL_FBARTYPE *TVIL_SetParamsFBAR (TVIL_FBARTYPE *foo,
				   int  whichfun,
				   TVIL_REAL x,
				   TVIL_REAL y,
				   TVIL_REAL z,
				   TVIL_REAL u)
{
  if (whichfun == Fwuxy) {
    /* foo->A1 = &Wg; */
    /* foo->A2 = &Ug; */
    /* foo->A3 = &Xg; */
    /* foo->A4 = &Yg; */
    foo->lnbarA1 = &_lnbarWg;
    foo->lnbarA2 = &_lnbarUg;
    foo->lnbarA3 = &_lnbarXg;
    foo->lnbarA4 = &_lnbarYg;
  }
  else if (whichfun == Fwvxz) {
    /* foo->A1 = &Wg; */
    /* foo->A2 = &Vg; */
    /* foo->A3 = &Xg; */
    /* foo->A4 = &Zg; */
    foo->lnbarA1 = &_lnbarWg;
    foo->lnbarA2 = &_lnbarVg;
    foo->lnbarA3 = &_lnbarXg;
    foo->lnbarA4 = &_lnbarZg;
  }
  else if (whichfun == Fxuwy) {
    /* foo->A1 = &Xg; */
    /* foo->A2 = &Ug; */
    /* foo->A3 = &Wg; */
    /* foo->A4 = &Yg; */
    foo->lnbarA1 = &_lnbarXg;
    foo->lnbarA2 = &_lnbarUg;
    foo->lnbarA3 = &_lnbarWg;
    foo->lnbarA4 = &_lnbarYg;
  }
  else if (whichfun == Fxvwz) {
    /* foo->A1 = &Xg; */
    /* foo->A2 = &Vg; */
    /* foo->A3 = &Wg; */
    /* foo->A4 = &Zg; */
    foo->lnbarA1 = &_lnbarXg;
    foo->lnbarA2 = &_lnbarVg;
    foo->lnbarA3 = &_lnbarWg;
    foo->lnbarA4 = &_lnbarZg;
  }
  else if (whichfun == Fuvyz) {
    /* foo->A1 = &Ug; */
    /* foo->A2 = &Vg; */
    /* foo->A3 = &Yg; */
    /* foo->A4 = &Zg; */
    foo->lnbarA1 = &_lnbarUg;
    foo->lnbarA2 = &_lnbarVg;
    foo->lnbarA3 = &_lnbarYg;
    foo->lnbarA4 = &_lnbarZg;
  }
  else if (whichfun == Fuwxy) {
    /* foo->A1 = &Ug; */
    /* foo->A2 = &Wg; */
    /* foo->A3 = &Xg; */
    /* foo->A4 = &Yg; */
    foo->lnbarA1 = &_lnbarUg;
    foo->lnbarA2 = &_lnbarWg;
    foo->lnbarA3 = &_lnbarXg;
    foo->lnbarA4 = &_lnbarYg;
  }
  else if (whichfun == Fyuvz) {
    /* foo->A1 = &Yg; */
    /* foo->A2 = &Ug; */
    /* foo->A3 = &Vg; */
    /* foo->A4 = &Zg; */
    foo->lnbarA1 = &_lnbarYg;
    foo->lnbarA2 = &_lnbarUg;
    foo->lnbarA3 = &_lnbarVg;
    foo->lnbarA4 = &_lnbarZg;
  }
  else if (whichfun == Fyuwx) {
    /* foo->A1 = &Yg; */
    /* foo->A2 = &Ug; */
    /* foo->A3 = &Wg; */
    /* foo->A4 = &Xg; */
    foo->lnbarA1 = &_lnbarYg;
    foo->lnbarA2 = &_lnbarUg;
    foo->lnbarA3 = &_lnbarWg;
    foo->lnbarA4 = &_lnbarXg;
  }
  else if (whichfun == Fvuyz) {
    /* foo->A1 = &Vg; */
    /* foo->A2 = &Ug; */
    /* foo->A3 = &Yg; */
    /* foo->A4 = &Zg; */
    foo->lnbarA1 = &_lnbarVg;
    foo->lnbarA2 = &_lnbarUg;
    foo->lnbarA3 = &_lnbarYg;
    foo->lnbarA4 = &_lnbarZg;
  }
  else if (whichfun == Fvwxz) {
    /* foo->A1 = &Vg; */
    /* foo->A2 = &Wg; */
    /* foo->A3 = &Xg; */
    /* foo->A4 = &Zg; */
    foo->lnbarA1 = &_lnbarVg;
    foo->lnbarA2 = &_lnbarWg;
    foo->lnbarA3 = &_lnbarXg;
    foo->lnbarA4 = &_lnbarZg;
  }
  else if (whichfun == Fzuvy) {
    /* foo->A1 = &Zg; */
    /* foo->A2 = &Ug; */
    /* foo->A3 = &Vg; */
    /* foo->A4 = &Yg; */
    foo->lnbarA1 = &_lnbarZg;
    foo->lnbarA2 = &_lnbarUg;
    foo->lnbarA3 = &_lnbarVg;
    foo->lnbarA4 = &_lnbarYg;
  }
  else if (whichfun == Fzvwx) {
    /* foo->A1 = &Zg; */
    /* foo->A2 = &Vg; */
    /* foo->A3 = &Wg; */
    /* foo->A4 = &Xg; */
    foo->lnbarA1 = &_lnbarZg;
    foo->lnbarA2 = &_lnbarVg;
    foo->lnbarA3 = &_lnbarWg;
    foo->lnbarA4 = &_lnbarXg;
  }
  else
    TVIL_Error ("SetParamsFBAR", "Invalid function type (variable which)", 55);

  foo->which = whichfun;
  foo->arg[0] = x;
  foo->arg[1] = y;
  foo->arg[2] = z;
  foo->arg[3] = u;

  return foo;
}

/* **************************************************************** */

TVIL_FBARTYPE *TVIL_SetupFBAR (TVIL_FBARTYPE *foo)
{
  TVIL_REAL x, y, z, u;

  x = foo->arg[0];
  y = foo->arg[1];
  z = foo->arg[2];
  u = foo->arg[3];

  foo->p2 = _a/(_a - x);
  foo->p3 = TVIL_R4 (x,y,z,u);
  foo->p4 = TVIL_Rplus (y,z,u);
  foo->p5 = TVIL_Rminus (y,z,u);

  /* FF1 */
  foo->cFF11 = 0.75L;
  foo->cFF13 = 0.25L;

  /* FLLL1 */
  foo->cFLLL11 = 0.75L*_a;
  foo->cFLLL12 = TVIL_cFLLL12 (x,y,z,u);
  foo->cFLLL13 = TVIL_cFLLL13 (x,y,z,u);

  /* FIL */
  foo->cFIL4 = 0.5L;
  foo->cFIL5 = 0.5L;

  /* FI2 */
  foo->cFI22 = 1.0L;

  /* FL1 */
  foo->cFL10 = TVIL_cFL10 (x,y,z,u);
  foo->cFL11 = -63*_a/16;
  foo->cFL13 = TVIL_cFL13 (x,y,z,u);
  foo->cFL14 = TVIL_cFL14 (x,y,z,u);
  foo->cFL15 = TVIL_cFL15 (x,y,z,u);

  /* F */
  foo->cF0 = TVIL_cF0 (x,y,z,u);
  foo->cF2 = TVIL_cF2 (x,y,z,u);
  foo->cF3 = TVIL_cF3 (x,y,z,u);

  /* Next three sets get one ordering... */
  /* FF2 */
  foo->cFF21    = -0.25L;
  foo->cFF22[0] = TVIL_cFF22 (x,y,z,u);
  foo->cFF23[0] = TVIL_cFF23 (x,y,z,u);

  foo->cFF22[1] = TVIL_cFF22 (x,z,y,u);
  foo->cFF23[1] = TVIL_cFF23 (x,z,y,u);

  foo->cFF22[2] = TVIL_cFF22 (x,u,y,z);
  foo->cFF23[2] = TVIL_cFF23 (x,u,y,z);

  /* FLL2 */
  foo->cFLL21    = _a;
  foo->cFLL23[0] = TVIL_cFLL23 (x,y,z,u);
  foo->cFLL24[0] = TVIL_cFLL24 (x,y,z,u);
  foo->cFLL25[0] = TVIL_cFLL25 (x,y,z,u);

  foo->cFLL23[1] = TVIL_cFLL23 (x,z,y,u);
  foo->cFLL24[1] = TVIL_cFLL24 (x,z,y,u);
  foo->cFLL25[1] = TVIL_cFLL25 (x,z,y,u);

  foo->cFLL23[2] = TVIL_cFLL23 (x,u,y,z);
  foo->cFLL24[2] = TVIL_cFLL24 (x,u,y,z);
  foo->cFLL25[2] = TVIL_cFLL25 (x,u,y,z);

  /* FL2 */
  foo->cFL20[0] = TVIL_cFL20 (x,y,z,u);
  foo->cFL21    = 21*_a/16;
  foo->cFL22[0] = TVIL_cFL22 (x,y,z,u);
  foo->cFL23[0] = TVIL_cFL23 (x,y,z,u);

  foo->cFL20[1] = TVIL_cFL20 (x,z,y,u);
  foo->cFL22[1] = TVIL_cFL22 (x,z,y,u);
  foo->cFL23[1] = TVIL_cFL23 (x,z,y,u);

  foo->cFL20[2] = TVIL_cFL20 (x,u,y,z);
  foo->cFL22[2] = TVIL_cFL22 (x,u,y,z);
  foo->cFL23[2] = TVIL_cFL23 (x,u,y,z);

  /* Last two sets get the other ordering... */
  /* FLLL2 */
  foo->cFLLL21    = -0.25L*_a;
  foo->cFLLL23[0] = TVIL_cFLLL23 (x,y,z,u);
  foo->cFLLL24[0] = TVIL_cFLLL24 (x,y,z,u);
  foo->cFLLL25[0] = TVIL_cFLLL25 (x,y,z,u);

  foo->cFLLL23[1] = TVIL_cFLLL23 (x,y,u,z);
  foo->cFLLL24[1] = TVIL_cFLLL24 (x,y,u,z);
  foo->cFLLL25[1] = TVIL_cFLLL25 (x,y,u,z);

  foo->cFLLL23[2] = TVIL_cFLLL23 (x,z,u,y);
  foo->cFLLL24[2] = TVIL_cFLLL24 (x,z,u,y);
  foo->cFLLL25[2] = TVIL_cFLLL25 (x,z,u,y);

  /* FLL1 */
  foo->cFLL11    = -_a;
  foo->cFLL12[0] = TVIL_cFLL12 (x,y,z,u);
  foo->cFLL13[0] = TVIL_cFLL13 (x,y,z,u);

  foo->cFLL12[1] = TVIL_cFLL12 (x,y,u,z);
  foo->cFLL13[1] = TVIL_cFLL13 (x,y,u,z);

  foo->cFLL12[2] = TVIL_cFLL12 (x,z,u,y);
  foo->cFLL13[2] = TVIL_cFLL13 (x,z,u,y);

  return foo;
}
