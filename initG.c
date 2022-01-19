/* Routines for setup and initialization of G-type functions */

#include "internal.h"

TVIL_REAL TVIL_cGF1 (TVIL_REAL w, TVIL_REAL u, TVIL_REAL z)
{
  if (TVIL_NonZero (u - z))
    return -(u - w)/(u - z);
  else
    return 0.0L;
}

/* **************************************************************** */

TVIL_REAL TVIL_cGF4 (TVIL_REAL w, TVIL_REAL u, TVIL_REAL z)
{
  if (TVIL_NonZero (u - z))
    return (u - w + TVIL_SQRT(u*u + w*w + z*z - u*w - u*z - w*z))/(2*(u - z));
  else
    return TVIL_Sign (w - u)/4.0L;
}

/* **************************************************************** */

TVIL_REAL TVIL_cGF5 (TVIL_REAL w, TVIL_REAL u, TVIL_REAL z)
{
  if (TVIL_NonZero (u - z))
    return (u - w - TVIL_SQRT(u*u + w*w + z*z - u*w - u*z - w*z))/(2*(u - z));
  else
    return -TVIL_Sign (w - u)/4.0L;
}

/* **************************************************************** */
/* **************************************************************** */

TVIL_GTYPE *TVIL_SetParamsG (TVIL_GTYPE *foo,
			     int         whichfun,
			     TVIL_REAL   w, 
			     TVIL_REAL   u, 
			     TVIL_REAL   z,
			     TVIL_REAL   x,
			     TVIL_REAL   y)
{
  if (whichfun == Gwuzvy) {
    foo->A1 = &_Wg;
    foo->A2 = &_Ug;
    foo->A3 = &_Zg;
    foo->A4 = &_Vg;
    foo->A5 = &_Yg;
    foo->lnbarA1 = &_lnbarWg;
    foo->lnbarA2 = &_lnbarUg;
    foo->lnbarA3 = &_lnbarZg;
    foo->lnbarA4 = &_lnbarVg;
    foo->lnbarA5 = &_lnbarYg;
  }
  else if (whichfun == Gxuvyz) {
    foo->A1 = &_Xg;
    foo->A2 = &_Ug;
    foo->A3 = &_Vg;
    foo->A4 = &_Yg;
    foo->A5 = &_Zg;
    foo->lnbarA1 = &_lnbarXg;
    foo->lnbarA2 = &_lnbarUg;
    foo->lnbarA3 = &_lnbarVg;
    foo->lnbarA4 = &_lnbarYg;
    foo->lnbarA5 = &_lnbarZg;
  }
  else if (whichfun == Guvxwz) {
    foo->A1 = &_Ug;
    foo->A2 = &_Vg;
    foo->A3 = &_Xg;
    foo->A4 = &_Wg;
    foo->A5 = &_Zg;
    foo->lnbarA1 = &_lnbarUg;
    foo->lnbarA2 = &_lnbarVg;
    foo->lnbarA3 = &_lnbarXg;
    foo->lnbarA4 = &_lnbarWg;
    foo->lnbarA5 = &_lnbarZg;
  }
  else if (whichfun == Gyvwxz) {
    foo->A1 = &_Yg;
    foo->A2 = &_Vg;
    foo->A3 = &_Wg;
    foo->A4 = &_Xg;
    foo->A5 = &_Zg;
    foo->lnbarA1 = &_lnbarYg;
    foo->lnbarA2 = &_lnbarVg;
    foo->lnbarA3 = &_lnbarWg;
    foo->lnbarA4 = &_lnbarXg;
    foo->lnbarA5 = &_lnbarZg;
  }
  else if (whichfun == Gvuxwy) {
    foo->A1 = &_Vg;
    foo->A2 = &_Ug;
    foo->A3 = &_Xg;
    foo->A4 = &_Wg;
    foo->A5 = &_Yg;
    foo->lnbarA1 = &_lnbarVg;
    foo->lnbarA2 = &_lnbarUg;
    foo->lnbarA3 = &_lnbarXg;
    foo->lnbarA4 = &_lnbarWg;
    foo->lnbarA5 = &_lnbarYg;
  }
  else if (whichfun == Gzuwxy) {
    foo->A1 = &_Zg;
    foo->A2 = &_Ug;
    foo->A3 = &_Wg;
    foo->A4 = &_Xg;
    foo->A5 = &_Yg;
    foo->lnbarA1 = &_lnbarZg;
    foo->lnbarA2 = &_lnbarUg;
    foo->lnbarA3 = &_lnbarWg;
    foo->lnbarA4 = &_lnbarXg;
    foo->lnbarA5 = &_lnbarYg;
  }
  else
    TVIL_Error ("SetParamsG", "Invalid function type (variable which)", 55);

  if (w < 0.0 || u < 0.0 || z < 0.0 || x < 0.0 || y < 0.0)
    foo->hasNegativeArg = YES;
  else
    foo->hasNegativeArg = NO;

  foo->which = whichfun;
  foo->arg[0] = w;
  foo->arg[1] = u;
  foo->arg[2] = z;
  foo->arg[3] = x;
  foo->arg[4] = y;

  return foo;
}

/* **************************************************************** */

TVIL_GTYPE *TVIL_SetupG (TVIL_GTYPE *foo)
{
  TVIL_REAL w, u, z, x, y;

  w = foo->arg[0];
  u = foo->arg[1];
  z = foo->arg[2];
  x = foo->arg[3];
  y = foo->arg[4];

  foo->p1 = _a/(_a - w);
  foo->p2 = TVIL_Rplus (x,y,w);
  foo->p3 = TVIL_Rminus (x,y,w);
  foo->p4 = TVIL_Rplus (u,z,w);
  foo->p5 = TVIL_Rminus (u,z,w);

  /* GF */
  /* Tolerable redundancy here... */
  foo->cGF1[0] = TVIL_cGF1 (w,u,z);
  foo->cGF4[0] = TVIL_cGF4 (w,u,z);
  foo->cGF5[0] = TVIL_cGF5 (w,u,z);
  foo->cGF_p4[0] = foo->p4;
  foo->cGF_p5[0] = foo->p5;

  foo->cGF1[1] = TVIL_cGF1 (w,z,u);
  foo->cGF4[1] = TVIL_cGF4 (w,z,u);
  foo->cGF5[1] = TVIL_cGF5 (w,z,u);
  foo->cGF_p4[1] = foo->p4; 
  foo->cGF_p5[1] = foo->p5;

  foo->cGF1[2] = TVIL_cGF1 (w,x,y);
  foo->cGF4[2] = TVIL_cGF4 (w,x,y);
  foo->cGF5[2] = TVIL_cGF5 (w,x,y);
  foo->cGF_p4[2] = foo->p2;
  foo->cGF_p5[2] = foo->p3;

  foo->cGF1[3] = TVIL_cGF1 (w,y,x);
  foo->cGF4[3] = TVIL_cGF4 (w,y,x);
  foo->cGF5[3] = TVIL_cGF5 (w,y,x);
  foo->cGF_p4[3] = foo->p2;
  foo->cGF_p5[3] = foo->p3;

  /* GI */
  foo->cGI_p2[0] = foo->p2;
  foo->cGI_p3[0] = foo->p3;

  foo->cGI_p2[1] = foo->p4;
  foo->cGI_p3[1] = foo->p5;

  /* GL */
  foo->cGL_p2[0] = foo->p2;
  foo->cGL_p3[0] = foo->p3;

  foo->cGL_p2[1] = foo->p2;
  foo->cGL_p3[1] = foo->p3;

  foo->cGL_p2[2] = foo->p4;
  foo->cGL_p3[2] = foo->p5;

  foo->cGL_p2[3] = foo->p4;
  foo->cGL_p3[3] = foo->p5;

  /* G */
  foo->cG0 = -11*_a - w + 3*u + 3*x + 3*y + 3*z;
  foo->cG1 = 11*_a*(4*w - u - x - y - z)/(12*(_a - w));
  foo->cG2 = 175*_a/48 + (foo->p2)*(-175*_a - 19*w + 56*u + 56*z + 41*x + 41*y)/48;
  foo->cG3 = 175*_a/48 + (foo->p3)*(-175*_a - 19*w + 56*u + 56*z + 41*x + 41*y)/48;
  foo->cG4 = 175*_a/48 + (foo->p4)*(-175*_a - 19*w + 56*x + 56*y + 41*u + 41*z)/48;
  foo->cG5 = 175*_a/48 + (foo->p5)*(-175*_a - 19*w + 56*x + 56*y + 41*u + 41*z)/48;

  return foo;
}
