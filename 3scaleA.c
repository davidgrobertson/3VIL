/* Code for evaulating H00yzxx and subordinate integrals. */

#include "internal.h"

/* Globals: */
TVIL_REAL _xx, _yy, _zz;
TVIL_REAL _lnbarx, _lnbary, _sqrtx, _sqrty, _sqrtxy;
TVIL_REAL _I0xy, _Gy0x0x;
TVIL_REAL _r4x, _r2, _rplus, _rminus;

TVIL_COMPLEX *_Gz00xx, *_Gx0yxz; 
TVIL_COMPLEX *_Fbar0xyz, *_Fx0yz, *_Fy0xz, *_Fz0xy;
TVIL_COMPLEX *_IIxxz, *_IIxyz;

/* **************************************************************** */

void TVIL_SetupI_3sA (TVIL_ITYPE *foo)
{
  TVIL_REAL x, y;

  if (foo->which == _xyz) {

    x = foo->arg[0];
    y = foo->arg[1];

    /* cIxyzLplus */
    foo->coeff[0] =  ((_sqrtx + _sqrty)*((_lnbarx - 2)*_sqrtx + (_lnbary - 2)*_sqrty))/2.;

    /* cIxyzLminus */
    foo->coeff[1] = ((_sqrtx - _sqrty)*((_lnbarx - 2)*_sqrtx - (_lnbary - 2)*_sqrty))/2.;

    /* cIxyzplus */ 
    foo->coeff[2] = ((5 - 2*_lnbarx)*x + (5 - _lnbarx*_lnbary)*_sqrtxy + (5 - 2*_lnbary)*y)/2.;

    /* cIxyzminus */
    foo->coeff[3] = ((5 - 2*_lnbarx)*x - (5 - _lnbarx*_lnbary)*_sqrtxy + (5 - 2*_lnbary)*y)/2.;
  }
  else if (foo->which == _xxz) {

    x = foo->arg[0];
    y = foo->arg[0];

    /* cIxxzL1 */
    foo->coeff[0] = 2*x*(_lnbarx-2);

    /* cIxxz1 */
    foo->coeff[1] = x*(15 - 4 * _lnbarx - _lnbarx*_lnbarx)/2.;

    /* cIxxz0 */
    foo->coeff[2] = x*(5 - 4 * _lnbarx + _lnbarx*_lnbarx)/2.;
  }
  else
    TVIL_Error ("ConstructI_3sA", "Invalid function type.", 888);

  return;
}

/* **************************************************************** */

void TVIL_SetupFBAR_3sA (TVIL_FBARTYPE *foo)
{
  TVIL_REAL x, y;

  if (foo->which == _y0xz) {

    x = foo->arg[2];
    y = foo->arg[0];

    foo->coeff[0] = 
    /* c_Fy0xzFx =  */
      _sqrtx/(2*_sqrty);

    foo->coeff[1] = 
      /* c_Fy0xzFzplus  = */
      -(1. + _sqrtx/_sqrty)/2.;

    foo->coeff[2] = 
      /* c_Fy0xzFzminus =  */
      (_sqrtx/_sqrty - 1.)/2.;

    foo->coeff[3] = 
      /* c_Fy0xzLplus  =  */
      (1 + _sqrtx/_sqrty) * 
      (x + y + _sqrtxy*(-18 + 8*_lnbarx + 8*_lnbary - 4*_lnbarx*_lnbary))/8;

    foo->coeff[4] = 
      /* c_Fy0xzLminus = */ 
      (1 - _sqrtx/_sqrty) * 
      (x + y - _sqrtxy*(-18 + 8*_lnbarx + 8*_lnbary - 4*_lnbarx*_lnbary))/8;

    foo->coeff[5] = 
      /* c_Fy0xzL =  */
      _lnbary - 7./4.;

    foo->coeff[6] = 
      /* c_Fy0xzplus =  */
      (45./8. - (5./2.)*(_lnbarx + _lnbary) + _lnbarx*_lnbary) * _sqrtxy -_lnbary*y/8. + 
      45.*x/8. - 5.*_lnbary*x/2. - 5.*_lnbarx*x/2. + _lnbarx*_lnbary*x - _lnbarx*_sqrtx*x/(8*_sqrty);

    foo->coeff[7] = 
      /* c_Fy0xzminus =  */
      -(45./8. - (5./2.)*(_lnbarx + _lnbary) + _lnbarx*_lnbary) * _sqrtxy -_lnbary*y/8 + 
      45.*x/8. - 5*_lnbary*x/2 - 5*_lnbarx*x/2 + _lnbarx*_lnbary*x + _lnbarx*_sqrtx*x/(8*_sqrty);

    foo->coeff[8] = 
      /* c_Fy0xz = */ 
      41./12. - 2 * _lnbary;

  } else if (foo->which == _z0xy) {

    x = foo->arg[2];
    y = foo->arg[3];

    foo->coeff[0] =
      /* c_Fz0xyFxplus = */
      -_sqrtx/(2*(_sqrtx + _sqrty));

    foo->coeff[1] =
      /* c_Fz0xyFxminus =  */
      -_sqrtx/(2*(_sqrtx - _sqrty));

    foo->coeff[2] =
      /* c_Fz0xyFx0 = */
      x/(x-y);

    foo->coeff[3] =
      /* c_Fz0xyFyplus  = */
      -_sqrty/(2*(_sqrty + _sqrtx));

    foo->coeff[4] =
      /* c_Fz0xyFyminus =  */
      -_sqrty/(2*(_sqrty - _sqrtx));

    foo->coeff[5] =
      /* c_Fz0xyFy0 = */ 
      y/(y-x);

    foo->coeff[6] =
      /* c_Fz0xyLplus  = */
      -(x+y)/8 + _sqrtxy * (9./4. - _lnbarx - _lnbary + _lnbarx*_lnbary/2.);

    foo->coeff[7] =
      /* c_Fz0xyLminus = */
      -(x+y)/8 - _sqrtxy * (9./4. - _lnbarx - _lnbary + _lnbarx*_lnbary/2.);

    foo->coeff[8] =
      /* c_Fz0xyplus = */
      (_lnbarx*_sqrtx*x - 45*_sqrty*x + 20*_lnbarx*_sqrty*x + 
       20*_lnbary*_sqrty*x - 8*_lnbarx*_lnbary*_sqrty*x - 45*_sqrtx*y + 
       20*_lnbarx*_sqrtx*y + 20*_lnbary*_sqrtx*y - 8*_lnbarx*_lnbary*_sqrtx*y + 
       _lnbary*_sqrty*y)/(8*(_sqrtx + _sqrty));

    foo->cF2 =
      /* c_Fz0xyminus = */ 
      (_lnbarx*_sqrtx*x + 45*_sqrty*x - 20*_lnbarx*_sqrty*x - 20*_lnbary*_sqrty*x + 
       8*_lnbarx*_lnbary*_sqrty*x - 45*_sqrtx*y + 20*_lnbarx*_sqrtx*y + 
       20*_lnbary*_sqrtx*y - 8*_lnbarx*_lnbary*_sqrtx*y - _lnbary*_sqrty*y)/(8*(_sqrtx - _sqrty));
  
    foo->cF3 =
      /* c_Fz0xy0 = */
      ((-17. + 9.*_lnbarx)*x*x - 12*(_lnbarx - _lnbary)*x*y + 
       (17. - 9.*_lnbary)*y*y)/(12*(x - y));

  } else if (foo->which == _0xyz) {

    /* This one is really an FBAR function (the others are Fs). */
    x = foo->arg[1];
    y = foo->arg[2];

    foo->coeff[0] =
      /* cFbar0xyzFx =  */
      -_sqrtx/(2*_sqrty);

    foo->coeff[1] =
      /* cFbar0xyzFy =  */
      -_sqrty/(2*_sqrtx);

    foo->coeff[2] =
      /* cFbar0xyzFzplus  = */
      (3. + _sqrtx/_sqrty + _sqrty/_sqrtx)/2;

    foo->coeff[3] =
      /* cFbar0xyzFzminus = */
      (3. - _sqrtx/_sqrty - _sqrty/_sqrtx)/2;

    foo->coeff[4] =
      /* cFbar0xyzLplus  = */
      -9.*(x+y)/8. + x*_lnbarx + y*_lnbary + 
      (-x*x + 4*x*y -y*y + 4*_lnbarx*_lnbary*x*y )/(8*_sqrtxy);

    foo->coeff[5] =
      /* cFbar0xyzLminus = */
      -9.*(x+y)/8. + x*_lnbarx + y*_lnbary - 
      (-x*x + 4*x*y -y*y + 4*_lnbarx*_lnbary*x*y )/(8*_sqrtxy);

    foo->coeff[6] =
      /* cFbar0xyzplus  = */
      (-17./3. + (5./2.)*(_lnbarx + _lnbary) - 2*_lnbarx*_lnbary) * _sqrtxy + 
      -(x+y)/24. -(x*_lnbarx + y*_lnbary)/2 + (x*_sqrtx*_lnbarx/_sqrty + y*_sqrty*_lnbary/_sqrtx)/8;

    foo->coeff[7] =
      /* cFbar0xyzminus =  */
      (17./3. - (5./2.)*(_lnbarx + _lnbary) + 2*_lnbarx*_lnbary) * _sqrtxy + 
      -(x+y)/24. -(x*_lnbarx + y*_lnbary)/2. - (x*_sqrtx*_lnbarx/_sqrty + y*_sqrty*_lnbary/_sqrtx)/8.;

  } else if (foo->which == _x0yz) {

    x = foo->arg[0];
    y = foo->arg[2];

    foo->coeff[0] =
      /* c_Fx0yzFy = */
      _sqrty/(2*_sqrtx);

    foo->coeff[1] =
      /* c_Fx0yzFzplus  = */
      -(1 + _sqrty/_sqrtx)/2.;

    foo->coeff[2] =
      /* c_Fx0yzFzminus = */
      (_sqrty/_sqrtx -1)/2.;

    foo->coeff[3] =
      /* c_Fx0yzLplus  = */
      (1 + _sqrty/_sqrtx) * 
      (x + y + _sqrtxy*(-18. + 8.*_lnbarx + 8.*_lnbary - 4.*_lnbarx*_lnbary))/8;

    foo->coeff[4] =
      /* c_Fx0yzLminus = */
      (1 - _sqrty/_sqrtx) * 
      (x + y - _sqrtxy*(-18. + 8*_lnbarx + 8*_lnbary - 4*_lnbarx*_lnbary))/8.;

    foo->coeff[5] =
      /* c_Fx0yzL = */
      _lnbarx - 7./4.;

    foo->coeff[6] =
      /* c_Fx0yzplus =  */
      (45./8. - (5./2.)*(_lnbarx + _lnbary) + _lnbarx*_lnbary) * _sqrtxy -_lnbarx*x/8. + 
      45.*y/8. - 5.*_lnbarx*y/2. - 5.*_lnbary*y/2. + _lnbarx*_lnbary*y - _lnbary*_sqrty*y/(8*_sqrtx);

    foo->coeff[7] =
      /* c_Fx0yzminus = */
      -(45./8. - (5./2.)*(_lnbarx + _lnbary) + _lnbarx*_lnbary) * _sqrtxy -_lnbarx*x/8 + 
      45.*y/8. - 5.*_lnbarx*y/2. - 5.*_lnbary*y/2. + _lnbarx*_lnbary*y + _lnbary*_sqrty*y/(8*_sqrtx);

    foo->coeff[8] =
      /* c_Fx0yz = */
      41./12. - 2.*_lnbarx;
  }
  else
    TVIL_Error ("ConstructFBAR_3sA", "Invalid function type.", 888);

  return;
}

/* **************************************************************** */

void TVIL_SetupG_3sA (TVIL_GTYPE *foo)
{
  TVIL_REAL x, y;

  if (foo->which == _z00xx) {

    x = foo->arg[3];

    /* cGz00xxL */
    foo->coeff[0] =  x * (2 - _lnbarx);

    /* cGz00xx1 */
    foo->coeff[1] =  x*(73. - 33.*_lnbarx - 3*_lnbarx*_lnbarx + _lnbarx*_lnbarx*_lnbarx + 
		   4*PI2 - 2.*_lnbarx*PI2 - 8*Zeta3)/6.; 

    /* cGz00xx0 */
    foo->coeff[2] = x*(15. - 9*_lnbarx + 3*_lnbarx*_lnbarx - _lnbarx*_lnbarx*_lnbarx + 8*Zeta3)/6.;

    /* cGz00xx */
    foo->coeff[3] = 3./2. + PI2/6;
  }
  else if (foo->which == _x0yxz) {
    x = foo->arg[0];
    y = foo->arg[2];

    /* cGx0yxzL1 */
    foo->coeff[0] = _I0xy - x;

    /* cGx0yxz1 */
    foo->coeff[1] = (31. + _lnbarx)*x/8. + (7. - 3.*_lnbary)*y/6. - (1. + _lnbarx/2)*_I0xy;

    /* cGx0yxz0 */
    foo->coeff[2] = (11. - 3.*_lnbarx)*x/24. + (7. - 3.*_lnbary)*y/6. + (_lnbarx/2. - 1.)*_I0xy;
  }
  else
    TVIL_Error ("ConstructG_3sA", "Invalid function type.", 888);

  return;
}

/* **************************************************************** */

void TVIL_SetupH_3sA (TVIL_HTYPE *foo)
{
  TVIL_REAL x, y;

  x = foo->arg[4];
  y = foo->arg[2];

  /* cH00yzxxGx1 = cH00yzxxGz3  */
  foo->coeff[0] = foo->coeff[1] = -1./(2.*(x+y));

  /* cH00yzxxGx3 = cH00yzxxGz1 = -cH00yzxxGx1; */
  foo->coeff[2] = foo->coeff[3] = -foo->coeff[0];

  /* cH00yzxxGx2 */
  foo->coeff[4] = (y+x)/(2*y);

  /* cH00yzxxGz2  */
  foo->coeff[5] = (y-x)/(2*y); 

  /* cH00yzxxI */
  foo->coeff[6]  = _lnbary - 2.;

  /* cH00yzxxL21 */
  foo->coeff[7] = x * (2 - _lnbarx)/(x+y);

  /* cH00yzxxL22 */
  foo->coeff[8] = (y - x + x * _lnbarx - (x + y) * _lnbary/2.)/(x+y);

  /* cH00yzxxL11  */
  foo->coeff[9] = (4 * _lnbarx * x - 7 * x - _I0xy)/(x+y);

  /* cH00yzxxL12  */
  foo->coeff[10] = (x/y - 1.) * _I0xy;

  /* cH00yzxxL13  */
  foo->coeff[11] = ((5. - 8*_lnbarx + 4*_lnbary)*x + (4*_lnbary - 9)*y + 
		  2*_I0xy)/(2.*(x + y));

  /* cH00yzxx1 */
  foo->coeff[12]  = (x * (199./24. + 2*PI2/3. - (45./8. + PI2/3)*_lnbarx - _lnbarx*_lnbarx/2 + 
			_lnbarx*_lnbarx*_lnbarx/6 - 4.*Zeta3/3.) + y * (_lnbary/2. - 7./6.) + 
		   (1. + _lnbarx/2)*_I0xy)/(x+y);
  
  /* cH00yzxx2  */
  foo->coeff[13] = -_Gy0x0x + _I0xy*(3 - _lnbarx/2 -x*(1+_lnbarx/2)/y) +
    Zeta3 * (16.*x/3. - 2*y - 2.*x*x/(3.*y)) + x * (7./6. - _lnbary/2) +
    (x + x*x/y) * (-79./24. + 5.*_lnbarx/8. + _lnbarx*_lnbarx/2 - _lnbarx*_lnbarx*_lnbarx/6) + 4.*y/3.;
 
  /* cH00yzxx3 */
  foo->coeff[14]  = (-(1 + _lnbarx/2)*_I0xy - (4*y + 8*x/3)*Zeta3 +
		   x*(-83./24. + 45.*_lnbarx/8. + _lnbarx*_lnbarx/2 - _lnbarx*_lnbarx*_lnbarx/6 +
		      -5.*_lnbary/2. + (2*_lnbarx - _lnbary - 2)*PI2/6) +
		   y*(6 - 3*_lnbary + (2 - _lnbary) * PI2/6))/(x+y);

  return;
}

/* **************************************************************** */

int TVIL_InitialI_3sA (TVIL_ITYPE *foo, 
		       TVIL_REAL qq,
		       TVIL_COMPLEX tinit)
{
  foo->value = TVIL_I2 (foo->arg[0], foo->arg[1], tinit, qq);
  foo->deriv = TVIL_dIdt_3sA (foo, tinit, qq);

  return 0;
}

/* **************************************************************** */

int TVIL_InitialFBAR_3sA (TVIL_FBARTYPE *foo, 
			  TVIL_REAL qq,
			  TVIL_COMPLEX tinit)
{
  if (foo->which == _y0xz) {

    TVIL_FBARanalytic (foo->arg[0], foo->arg[1], foo->arg[2], tinit, qq, &(foo->value));

    /* Then make it into an F: */
    foo->value -= TVIL_CLOG (foo->arg[0]/qq)*TVIL_I2 (foo->arg[1], foo->arg[2], tinit, qq);
  }
  else if (foo->which == _z0xy) {

    TVIL_FBARanalytic (tinit, foo->arg[1], foo->arg[2], foo->arg[3], qq, &(foo->value));
    /* Then make it into an F: */
    foo->value -= TVIL_CLOG (tinit/qq)*TVIL_I2 (foo->arg[1], foo->arg[2], foo->arg[3], qq);
  }
  else if (foo->which == _0xyz) {

    /* This one is an FBAR */
    TVIL_FBARanalytic (foo->arg[0], foo->arg[1], foo->arg[2], tinit, qq, &(foo->value));
  }
  else if (foo->which == _x0yz) {

    TVIL_FBARanalytic (foo->arg[0], foo->arg[1], foo->arg[2], tinit, qq, &(foo->value));

    /* Then make it into an F: */
    foo->value -= TVIL_CLOG (foo->arg[0]/qq)*TVIL_I2 (foo->arg[1], foo->arg[2], tinit, qq);
  }
  else
    TVIL_Error ("InitialFBAR_3sA", "Impossible, invalid function type.", 888);

  return 0;
}

/* **************************************************************** */

int TVIL_InitialG_3sA (TVIL_GTYPE *foo, 
		       TVIL_REAL qq,
		       TVIL_COMPLEX tinit)
{
  if (foo->which == _z00xx) {

    TVIL_Ganalytic (tinit, foo->arg[1], foo->arg[2], foo->arg[3], foo->arg[4], qq, &(foo->value));
  }
  else if (foo->which == _x0yxz) {

    TVIL_Ganalytic (foo->arg[0], foo->arg[1], foo->arg[2], foo->arg[3], tinit, qq, &(foo->value));
  }

  return 0;
}

/* **************************************************************** */

int TVIL_InitialH_3sA (TVIL_HTYPE *foo, 
		       TVIL_REAL qq,
		       TVIL_COMPLEX tinit)
{
  return TVIL_Hanalytic (0., 0., foo->arg[2], tinit, foo->arg[4], foo->arg[5],
			 qq, &(foo->value));
}

/* **************************************************************** */

TVIL_COMPLEX TVIL_dIdt_3sA (TVIL_ITYPE *foo, TVIL_COMPLEX t, TVIL_REAL Q2)
{
  TVIL_COMPLEX result;

  if (foo->which == _xxz) {

    result = 0.5L * (1./(_Zg - _r4x) + 1./_Zg) * (foo->value) +
      (foo->coeff[0]/(_Zg - _r4x) - 1) * _lnbarZg + foo->coeff[1]/(_Zg - _r4x) + foo->coeff[2]/_Zg  + 2;
  }
  else if (foo->which == _xyz) {

    result = 0.5L * (1./(_Zg - _rplus) + 1./(_Zg - _rminus)) * (foo->value) +
      (foo->coeff[0]/(_Zg - _rplus) + foo->coeff[1]/(_Zg - _rminus) - 1) * _lnbarZg +
      foo->coeff[2]/(_Zg - _rplus) + foo->coeff[3]/(_Zg - _rminus) + 2;
  }
  else
    TVIL_Error ("dIdt_3sA", "Impossible, wrong function type.", 909);

  return result;
}

/* **************************************************************** */

TVIL_COMPLEX TVIL_dFBARdt_3sA (TVIL_FBARTYPE *foo, TVIL_COMPLEX t, TVIL_REAL Q2)
{
  TVIL_COMPLEX result;

  if (foo->which == _y0xz) {

    result = (1./2.) * (1./(_Zg - _rplus) + 1./(_Zg - _rminus)) * (foo->value) /* _Fy0xz[s] */ 
      + (foo->coeff[0]) * (1./(_Zg - _rplus) - 1./(_Zg - _rminus)) * (*_Fx0yz)
      + ((foo->coeff[1])/(_Zg - _rplus) + (foo->coeff[2])/(_Zg - _rminus)) * (*_Fz0xy)
      + ((foo->coeff[3])/(_Zg - _rplus) + (foo->coeff[4])/(_Zg - _rminus) + (foo->coeff[5])) * _lnbarZg
      + (foo->coeff[6]) /(_Zg - _rplus) + (foo->coeff[7])/(_Zg - _rminus) + (foo->coeff[8]);
  }
  else if (foo->which == _z0xy) {

    result = (1./2.) * (1./(_Zg - _rplus) + 1./(_Zg - _rminus)) * (foo->value)
      + ((foo->coeff[0])/(_Zg - _rplus) + (foo->coeff[1])/(_Zg - _rminus) 
	 + (foo->coeff[2])/_Zg) * (*_Fx0yz)
      + ((foo->coeff[3])/(_Zg - _rplus) + (foo->coeff[4])/(_Zg - _rminus)
	 + (foo->coeff[5])/_Zg) * (*_Fy0xz)
      + ((foo->coeff[6])/(_Zg - _rplus) + (foo->coeff[7])/(_Zg - _rminus) + 1) * _lnbarZg 
      + (foo->coeff[8])/(_Zg - _rplus) + (foo->cF2)/(_Zg - _rminus) + (foo->cF3)/_Zg - 11./4.;
  }
  else if (foo->which == _0xyz) {

    result = (1./(_Zg - _rplus) + 1./(_Zg - _rminus)) * ((1./2.) * (foo->value) /* _Fbar0xyz[s] */ 
						   + 2. * (*_IIxyz)) 
      + (foo->coeff[0]) * (1./(_Zg - _rplus) - 1./(_Zg - _rminus)) * (*_Fx0yz)
      + (foo->coeff[1]) * (1./(_Zg - _rplus) - 1./(_Zg - _rminus)) * (*_Fy0xz)
      + ((foo->coeff[2])/(_Zg - _rplus)
	 + (foo->coeff[3])/(_Zg - _rminus)) * (*_Fz0xy)
      + ((foo->coeff[4])/(_Zg - _rplus) + (foo->coeff[5])/(_Zg - _rminus) + 5./4.) * _lnbarZg 
      + (foo->coeff[6])/(_Zg - _rplus) + (foo->coeff[7])/(_Zg - _rminus) - 9./4.;
  }
  else if (foo->which == _x0yz) {

    result = (1./2.) * (1./(_Zg - _rplus) + 1./(_Zg - _rminus)) * (foo->value) /* _Fx0yz[s] */ 
      + (foo->coeff[0]) * (1./(_Zg - _rplus) - 1./(_Zg - _rminus)) * (*_Fy0xz)
      + ((foo->coeff[1])/(_Zg - _rplus) + (foo->coeff[2])/(_Zg - _rminus)) * (*_Fz0xy)
      + ((foo->coeff[3])/(_Zg - _rplus) + (foo->coeff[4])/(_Zg - _rminus) + (foo->coeff[5])) * _lnbarZg
      + (foo->coeff[6])/(_Zg - _rplus) + (foo->coeff[7])/(_Zg - _rminus) + (foo->coeff[8]);
  }
  else
    TVIL_Error ("dFBARdt_3sA", "Impossible, wrong function type.", 909);

  return result;
}

/* **************************************************************** */

TVIL_COMPLEX TVIL_dGdt_3sA (TVIL_GTYPE *foo, TVIL_COMPLEX t, TVIL_REAL Q2)
{
  TVIL_COMPLEX result;

  if (foo->which == _z00xx) {

    result = (1./2.) * (1./(_Zg - _r4x) + 1./_Zg) * (foo->value)
      - (1./_Zg) * (*_IIxxz)
      + ((foo->coeff[0])/(_Zg - _r4x) + 0.5) * (_lnbarZg*_lnbarZg - 4. * _lnbarZg)
      + (foo->coeff[1])/(_Zg - _r4x) + (foo->coeff[2])/_Zg + foo->coeff[3];
  }
  else if (foo->which == _x0yxz) {

    result = (1./2.) * (1./(_Zg - _r4x) + 1./_Zg) * (foo->value) 
      + (-1./2.) * (1/(_Zg - _r4x) - 1/_Zg) * (*_Fx0yz)
      + 1./(_Zg - _r4x) * (*_Fz0xy)
      + ((foo->coeff[0])/(_Zg - _r4x) - 1./4.) * _lnbarZg
      + ((foo->coeff[1])/(_Zg - _r4x) + (foo->coeff[2])/_Zg + 19./12.);
  }
  else
    TVIL_Error ("dGdt_3sA", "Impossible, wrong function type.", 909);

  return result;
}

/* **************************************************************** */

TVIL_COMPLEX TVIL_dHdt_3sA (TVIL_HTYPE *foo, TVIL_COMPLEX t, TVIL_REAL Q2)
{
  return (foo->coeff[0]/(_Zg - _r4x) 
	  + (foo->coeff[4] + foo->coeff[2]*_Zg)/(_Zg * (_Zg + _r2))) * 
    ((*_Gx0yxz) - (*_Fx0yz))
    + (foo->coeff[3]/(_Zg - _r4x) + (foo->coeff[5] + foo->coeff[1]*_Zg)/(_Zg * (_Zg + _r2))) *
    ((*_Gz00xx) - 2. * (*_Fz0xy))
    + 2./(_Zg * (_Zg + _r2)) * (*_Fy0xz)
    + foo->coeff[6]/(_Zg * (_Zg + _r2)) * (*_IIxxz)
    + (foo->coeff[7]/(_Zg - _r4x) + foo->coeff[8]/(_Zg + _r2)) * _lnbarZg*_lnbarZg
    + (foo->coeff[9]/(_Zg - _r4x) + (foo->coeff[10] + foo->coeff[11]*_Zg)/(_Zg * (_Zg + _r2)) ) *
    _lnbarZg
    + foo->coeff[12]/(_Zg - _r4x) + (foo->coeff[13] + foo->coeff[14]*_Zg)/(_Zg * (_Zg + _r2));
}

/* ******************************************************************** */
/* Handling of all generic (i.e. non-analytic) cases.                   */

void TVIL_CaseGeneric_3sA (void)
{
  TVIL_COMPLEX ti, tf, temp;
  TVIL_REAL deltat_start;
  /* This is a local parameter, the global value is unchanged. */
  TVIL_REAL imDispl;
  int i;
  TVIL_RESULT bar;

  _Gz00xx = &(_G[_z00xx].value);
  _Gx0yxz = &(_G[_x0yxz].value);

  _Fbar0xyz = &(_FBAR[_0xyz].value);
  _Fy0xz = &(_FBAR[_y0xz].value);
  _Fz0xy = &(_FBAR[_z0xy].value);
  _Fx0yz = &(_FBAR[_x0yz].value);

  _IIxxz = &(_II[_xxz].value);
  _IIxyz = &(_II[_xyz].value);

  /* Set parameter values: */
  _yy = _w;
  _zz = _x;
  _xx = _y;

  _nIfuns = 0;
  _ifun[_nIfuns++] = TVIL_SetParamsI (&(_II[_xxz]), _xxz, _xx, _xx, _zz);
  _ifun[_nIfuns++] = TVIL_SetParamsI (&(_II[_xyz]), _xyz, _xx, _yy, _zz);

  _nFBARfuns = 0;
  _fbarfun[_nFBARfuns++] = TVIL_SetParamsFBAR (&(_FBAR[_y0xz]), _y0xz, _yy, 0.0, _xx, _zz);
  _fbarfun[_nFBARfuns++] = TVIL_SetParamsFBAR (&(_FBAR[_z0xy]), _z0xy, _zz, 0.0, _xx, _yy);
  _fbarfun[_nFBARfuns++] = TVIL_SetParamsFBAR (&(_FBAR[_0xyz]), _0xyz, 0.0, _xx, _yy, _zz);
  _fbarfun[_nFBARfuns++] = TVIL_SetParamsFBAR (&(_FBAR[_x0yz]), _x0yz, _xx, 0.0, _yy, _zz);

  _nEfuns = 0;

  _nGfuns = 0;
  _gfun[_nGfuns++] = TVIL_SetParamsG (&(_G[_z00xx]), _z00xx, _zz, 0.0, 0.0, _xx, _xx);
  _gfun[_nGfuns++] = TVIL_SetParamsG (&(_G[_x0yxz]), _x0yxz, _xx, 0.0, _yy, _xx, _zz);

  _nHfuns = 1;
  _hfun = TVIL_SetParamsH (&_H, 0.0, 0.0, _yy, _zz, _xx, _xx);

  /* Set up globals: */
  _r4x = 4*_xx;
  _r2 = (_xx-_yy)*(_xx-_yy)/_yy;
  _lnbarx = TVIL_LOG (_xx/_qq);
  _lnbary = TVIL_LOG (_yy/_qq);
  _sqrtx = TVIL_SQRT (_xx);
  _sqrty = TVIL_SQRT (_yy);
  _sqrtxy = _sqrtx*_sqrty;
  _rplus = (_sqrtx + _sqrty)*(_sqrtx + _sqrty);
  _rminus = (_sqrtx - _sqrty)*(_sqrtx - _sqrty);
  _I0xy = (TVIL_REAL) TVIL_I2 (0.0, _xx, _yy, _qq);
  TVIL_Ganalytic (_yy, 0, _xx, 0, _xx, _qq, &temp);
  _Gy0x0x = TVIL_CREAL (temp);

  /* Last bits: */
  _isInitialized = TRUE;
  _status        = UNEVALUATED;
  /* This is basically the end of SetParameters. */

  /* Then set up derivative coefficients in all sub-objects: */
  TVIL_SetupFunctions_3sA ();

  deltat_start = 0.0001L;

  if (_reAxisOK && _forceContour == NO) {

    ti = _xx;
    TVIL_InitialValue (ti);
    tf = _zz;

    TVIL_Integrate (ti, tf, &deltat_start);
    _status = REAXIS;

  } else {

    ti = _xx;
    TVIL_InitialValue (ti);

    imDispl = 0.5*TVIL_FABS (_xx - _zz);

    /* First leg: */
    tf = ti + (imDispl)*I;
    TVIL_Integrate (ti, tf, &deltat_start);

    /* Second leg: */
    ti = tf;
    tf = _zz + (imDispl)*I;
    TVIL_Integrate (ti, tf, &deltat_start);

    /* Last leg: */
    ti = tf;
    tf = _zz + (THREESCALE_ENDPOINT)*I;
    TVIL_Integrate (ti, tf, &deltat_start);

    _status = CONTOUR;
  }

  /* Finally, restore Fbar values where appropriate: */
  for (i=0; i<_nFBARfuns; i++) {
    if (_fbarfun[i]->which == _0xyz)
      ;
    else {
      _fbarfun[i]->fValue = _fbarfun[i]->value;
      _fbarfun[i]->value += TVIL_LOG (_fbarfun[i]->arg[0]/_qq)
	* TVIL_I2 (_fbarfun[i]->arg[1], _fbarfun[i]->arg[2], _fbarfun[i]->arg[3], _qq);
    }
  }

  /* Now copy everything back to the structs, but in the right
     place! */
  /* I functions will anyway be put in analytically: */
  /* foo->II[1].value = II[_xxz].value; */
  /* foo->II[13].value = II[_xyz].value; */

  /* This is slightly wasteful but transparent: */
  TVIL_Backup (&bar);

  _FBAR[1].value = bar.FBAR[_y0xz];
  _FBAR[3].value = bar.FBAR[_z0xy];
  _FBAR[9].value = bar.FBAR[_0xyz];
  _FBAR[11].value = bar.FBAR[_x0yz];

  _G[1].value = bar.G[_z00xx];
  _G[3].value = bar.G[_x0yxz];

  _H.value = bar.H;

  /* Some functions are just the same: */
  _FBAR[0].value = _FBAR[1].value;
  _FBAR[2].value = _FBAR[3].value;
  _FBAR[5].value = _FBAR[9].value;
  _FBAR[7].value = _FBAR[11].value;

  _G[5].value = _G[3].value;

  /* The rest will be filled in analytically, but we have to reset
     arguments of the functions we used... */
  TVIL_SetParamsI (&(_II[uvx]), uvx, _u, _v, _x);
  TVIL_SetParamsI (&(_II[uxy]), uxy, _u, _x, _y);

  TVIL_SetParamsFBAR (&(_FBAR[wuxy]), wuxy, _w, _u, _x, _y);
  TVIL_SetParamsFBAR (&(_FBAR[wvxz]), wvxz, _w, _v, _x, _z);
  TVIL_SetParamsFBAR (&(_FBAR[xuwy]), xuwy, _x, _u, _w, _y);
  TVIL_SetParamsFBAR (&(_FBAR[xvwz]), xvwz, _x, _v, _w, _z);

  TVIL_SetParamsG (&(_G[wuzvy]), wuzvy, _w, _u, _z, _v, _y);
  TVIL_SetParamsG (&(_G[xuvyz]), xuvyz, _x, _u, _v, _y, _z);

  return;
}

/* **************************************************************** */
/* This should be called immediately prior to generic evaluation. */

int TVIL_SetupFunctions_3sA (void)
{
  int i;

  /* Set values in all sub-objects: */
  for (i=0; i<_nIfuns; i++)
    TVIL_SetupI_3sA (_ifun[i]);

  for (i=0; i<_nFBARfuns; i++)
    TVIL_SetupFBAR_3sA (_fbarfun[i]);

  for (i=0; i<_nGfuns; i++)
    TVIL_SetupG_3sA (_gfun[i]);

  if (_nHfuns)
    TVIL_SetupH_3sA (_hfun);

  _Iderivative = &TVIL_dIdt_3sA;
  _FBARderivative = &TVIL_dFBARdt_3sA;
  _Gderivative = &TVIL_dGdt_3sA;
  _Hderivative = &TVIL_dHdt_3sA;

  /* Decide how to integrate: */
  if ((_rminus < _zz) && (_zz < _rplus) && (_zz < _r4x))
    _reAxisOK = YES;
  else
    _reAxisOK = NO;

  return 0;
}
