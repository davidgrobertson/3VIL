/* Code for evaluating H0xxyzy and subordinate integrals. */

#include "internal.h"

/* Globals: */
TVIL_REAL _xx, _yy, _zz;
TVIL_REAL _lnbarx, _lnbary, _sqrtx, _sqrty, _sqrtxy;
TVIL_REAL _r4x, _r4y, _rplus, _rminus;
TVIL_REAL _I0xy, _Fxxyy, _Fyyxx;

TVIL_COMPLEX *_Gzxxyy, *_Gx0yxz, *_Gy0xyz;
TVIL_COMPLEX *_Fbar0xyz, *_Fx0yz, *_Fy0xz, *_Fz0xy;
TVIL_COMPLEX *_IIxxz, *_IIyyz, *_IIxyz;

/* **************************************************************** */

void TVIL_SetupI_3sB (TVIL_ITYPE *foo)
{
  TVIL_REAL x, y;

  if (foo->which == _xyz) {

    x = foo->arg[0];
    y = foo->arg[1];

    /* These are all just the same as in 3sA */
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

    /* Also just the same as in 3sA */
    /* cIxxzL1 */
    foo->coeff[0] = 2*x*(_lnbarx-2);

    /* cIxxz1 */
    foo->coeff[1] = x*(15 - 4 * _lnbarx - _lnbarx*_lnbarx)/2.;

    /* cIxxz0 */
    foo->coeff[2] = x*(5 - 4 * _lnbarx + _lnbarx*_lnbarx)/2.;
  }
  else if (foo->which == _yyz) {

    y = foo->arg[0];

    /* cIyyzL1 */
    foo->coeff[0] = 2*y*(_lnbary-2);

    /* cIyyz1 */
    foo->coeff[1] = y*(15 - 4 * _lnbary - _lnbary*_lnbary)/2.;

    /* cIyyz0 */
    foo->coeff[2] = y*(5 - 4 * _lnbary + _lnbary*_lnbary)/2.;
  }
  else
    TVIL_Error ("ConstructI_3sB", "Invalid function type.", 888);

  return;
}

/* **************************************************************** */
/* These coefficients (and derivatives) are just the same as for case
   3sA, so for now just wrap it. */

void TVIL_SetupFBAR_3sB (TVIL_FBARTYPE *foo)
{
  TVIL_SetupFBAR_3sA (foo);

  return;
}

/* **************************************************************** */

void TVIL_SetupG_3sB (TVIL_GTYPE *foo)
{
  TVIL_REAL x, y;

  if (foo->which == _zxxyy) {

    x = foo->arg[1];
    y = foo->arg[3];

    /* cGzxxyyIxxz4y */
    foo->coeff[0] = _lnbary/2 - 1;

    /* cGzxxyyIxxz0 */
    foo->coeff[1] = -_lnbary/2;

    /* cGzxxyyIyyz4x */
    foo->coeff[2] = _lnbarx/2 - 1;

    /* cGzxxyyIyyz0 */
    foo->coeff[3] = -_lnbarx/2;

    /* cGzxxyy4x */
    foo->coeff[4] = _Fxxyy/2 + (1 - _lnbarx)*x/8. + y*(7./3. - _lnbary);

    /* cGzxxyy4y */
    foo->coeff[5] = _Fyyxx/2 + (1 - _lnbary)*y/8. + x*(7./3. - _lnbarx);

    /* cGzxxyy0 */
    foo->coeff[6] = -_Fxxyy/2 -_Fyyxx/2 + (53./24.)*(x+y) - (7./8.)*(x*_lnbarx + y*_lnbary);
  }
  else if (foo->which == _x0yxz) {
    x = foo->arg[0];
    y = foo->arg[2];

    /* The same as in 3sA */
    /* cGx0yxzL1 */
    foo->coeff[0] = _I0xy - x;

    /* cGx0yxz1 */
    foo->coeff[1] = (31. + _lnbarx)*x/8. + (7. - 3.*_lnbary)*y/6. - (1. + _lnbarx/2)*_I0xy;

    /* cGx0yxz0 */
    foo->coeff[2] = (11. - 3.*_lnbarx)*x/24. + (7. - 3.*_lnbary)*y/6. + (_lnbarx/2. - 1.)*_I0xy;
  }
  else if (foo->which == _y0xyz) {
    x = foo->arg[2];
    y = foo->arg[0];

    /* cGy0xyzL1 */
    foo->coeff[0] = _I0xy - y;

    /* cGy0xyz1 */
    foo->coeff[1] = (31. + _lnbary)*y/8. + (7. - 3.*_lnbarx)*x/6. - (1. + _lnbary/2)*_I0xy;

    /* cGy0xyz0 */
    foo->coeff[2] = (11. - 3.*_lnbary)*y/24. + (7. - 3.*_lnbarx)*x/6. + (_lnbary/2. - 1.)*_I0xy;
  }
  else
    TVIL_Error ("ConstructG_3sB", "Invalid function type.", 888);

  return;
}

/* **************************************************************** */

void TVIL_SetupH_3sB (TVIL_HTYPE *foo)
{
  TVIL_REAL x, y;
  
  x = foo->arg[1];
  y = foo->arg[3];

  /* cH0xxyzyG */
  foo->coeff[0] = 1./(2.*(x-y));

  /* cH0xxyzyIx */
  foo->coeff[1] = (1 - _lnbary/2)/(x-y);

  /* cH0xxyzyIy */
  foo->coeff[2] = (1 - _lnbarx/2)/(y-x);

  /* cH0xxyzyL4x */
  foo->coeff[3] = (x - _I0xy)/(x-y);

  /* cH0xxyzyL4y */
  foo->coeff[4] = (y - _I0xy)/(y-x);

  /* cH0xxyzy4x */
  foo->coeff[5] = (_Fxxyy/2. + _I0xy*(1 + _lnbarx/2) - (15. + _lnbarx)*x/4. + 
		  y*(7./6. - _lnbary/2))/(x-y);

  /* cH0xxyzy4y */
  foo->coeff[6] = (_Fyyxx/2. + _I0xy*(1 + _lnbary/2) - (15. + _lnbary)*y/4. + 
		  x*(7./6. - _lnbarx/2))/(y-x);

  /* cH0xxyzy0 */
  foo->coeff[7] = (_Fyyxx - _Fxxyy + _I0xy*(_lnbary - _lnbarx) - x*_lnbarx/2 + 
              y*_lnbary/2)/(2.*(x-y)) - 2*Zeta3 - 1./12.;

  return;
}

/* **************************************************************** */
/* Same as for 3sA */

int TVIL_InitialI_3sB (TVIL_ITYPE *foo, 
		       TVIL_REAL qq,
		       TVIL_COMPLEX tinit)
{
  foo->value = TVIL_I2 (foo->arg[0], foo->arg[1], tinit, qq);
  foo->deriv = TVIL_dIdt_3sB (foo, tinit, qq);

  return 0;
}

/* **************************************************************** */
/* Same as for 3sA */

int TVIL_InitialFBAR_3sB (TVIL_FBARTYPE *foo, 
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
    TVIL_Error ("InitialFBAR_3sB", "Impossible, invalid function type.", 888);

  return 0;
}

/* **************************************************************** */

int TVIL_InitialG_3sB (TVIL_GTYPE *foo, 
		       TVIL_REAL qq,
		       TVIL_COMPLEX tinit)
{
  if (foo->which == _zxxyy) {

    TVIL_Ganalytic (tinit, foo->arg[1], foo->arg[2], foo->arg[3], foo->arg[4], qq, &(foo->value));
  }
  else if (foo->which == _x0yxz) {

    TVIL_Ganalytic (foo->arg[0], foo->arg[1], foo->arg[2], foo->arg[3], tinit, qq, &(foo->value));
  }
  else if (foo->which == _y0xyz) {

    TVIL_Ganalytic (foo->arg[0], foo->arg[1], foo->arg[2], foo->arg[3], tinit, qq, &(foo->value));
  }
  else
    TVIL_Error ("InitialG_3sB", "Wrong specifier; impossible!", 333);

  return 0;
}

/* **************************************************************** */

int TVIL_InitialH_3sB (TVIL_HTYPE *foo, 
		       TVIL_REAL qq,
		       TVIL_COMPLEX tinit)
{
  return TVIL_Hanalytic (0., foo->arg[1], foo->arg[2], foo->arg[3], tinit, foo->arg[5],
			 qq, &(foo->value));
}

/* **************************************************************** */

TVIL_COMPLEX TVIL_dIdt_3sB (TVIL_ITYPE *foo, TVIL_COMPLEX t, TVIL_REAL Q2)
{
  TVIL_COMPLEX result;

  if (foo->which == _xxz) {

    result = 
      0.5L * (1./(_Zg - _r4x) + 1./_Zg) * (foo->value)
      + (foo->coeff[0]/(_Zg - _r4x) - 1) * _lnbarZg
      + foo->coeff[1]/(_Zg - _r4x) + foo->coeff[2]/_Zg + 2;
  }
  else if (foo->which == _yyz) {

    result = 0.5L * (1./(_Zg - _r4y) + 1./_Zg) * (foo->value) 
      + (foo->coeff[0]/(_Zg - _r4y) - 1) * _lnbarZg 
      + foo->coeff[1]/(_Zg - _r4y) + foo->coeff[2]/_Zg + 2;
  }
  else if (foo->which == _xyz) {

    result = 0.5L * (1./(_Zg - _rplus) + 1./(_Zg - _rminus)) * (foo->value) +
      (foo->coeff[0]/(_Zg - _rplus) + foo->coeff[1]/(_Zg - _rminus) - 1) * _lnbarZg +
      foo->coeff[2]/(_Zg - _rplus) + foo->coeff[3]/(_Zg - _rminus) + 2;
  }
  else
    TVIL_Error ("dIdt_3sB", "Impossible, wrong function type.", 909);

  return result;
}

/* **************************************************************** */
/* Just the same as for case 3sA. */

TVIL_COMPLEX TVIL_dFBARdt_3sB (TVIL_FBARTYPE *foo, TVIL_COMPLEX t, TVIL_REAL Q2)
{
  return TVIL_dFBARdt_3sA (foo, t, Q2);
}

/* **************************************************************** */

TVIL_COMPLEX TVIL_dGdt_3sB (TVIL_GTYPE *foo, TVIL_COMPLEX t, TVIL_REAL Q2)
{
  TVIL_COMPLEX result;

  if (foo->which == _zxxyy) {

    result = 0.5L * (1/(_Zg - _r4x) + 1/(_Zg - _r4y)) * (*_Gzxxyy) +
      (foo->coeff[0]/(_Zg - _r4y) + foo->coeff[1]/_Zg) * (*_IIxxz) +
      (foo->coeff[2]/(_Zg - _r4x) + foo->coeff[3]/_Zg) * (*_IIyyz) +
      foo->coeff[4]/(_Zg - _r4x) + foo->coeff[5]/(_Zg - _r4y) + foo->coeff[6]/_Zg - 1.;
  }
  else if (foo->which == _x0yxz) {

    result = 0.5L * (1/(_Zg - _r4x) + 1/_Zg) * (*_Gx0yxz) +
      (-0.5L) * (1/(_Zg - _r4x) - 1/_Zg) * (*_Fx0yz) + 1/(_Zg - _r4x) * (*_Fz0xy) +
      (foo->coeff[0]/(_Zg - _r4x) - 1./4.) * _lnbarZg + 
      (foo->coeff[1]/(_Zg - _r4x) + foo->coeff[2]/_Zg + 19./12.);
  }
  else if (foo->which == _y0xyz) {

    result = 0.5L * (1/(_Zg - _r4y) + 1/_Zg) * (*_Gy0xyz) +
      (-0.5L) * (1/(_Zg - _r4y) - 1/_Zg) * (*_Fy0xz) + 1/(_Zg - _r4y) * (*_Fz0xy) +
      (foo->coeff[0]/(_Zg - _r4y) - 1./4.) * _lnbarZg + 
      (foo->coeff[1]/(_Zg - _r4y) + foo->coeff[2]/_Zg + 19./12.);
  }
  else
    TVIL_Error ("dGdt_3sB", "Impossible, wrong function type.", 909);

  return result;
}

/* **************************************************************** */

TVIL_COMPLEX TVIL_dHdt_3sB (TVIL_HTYPE *foo, TVIL_COMPLEX t, TVIL_REAL Q2)
{
  return foo->coeff[0] * 
    ((1./(_Zg - _r4x) - 1/(_Zg - _r4y)) * (*_Gzxxyy - 2. * (*_Fz0xy)) +
     (-1./(_Zg - _r4x) + 1/_Zg) * (*_Gx0yxz - *_Fx0yz) +
     (1./(_Zg - _r4y) - 1/_Zg) * (*_Gy0xyz - *_Fy0xz) ) +
    foo->coeff[1] * (1/(_Zg - _r4y) - 1/_Zg) * (*_IIxxz) +
    foo->coeff[2] * (1/(_Zg - _r4x) - 1/_Zg) * (*_IIyyz) +
    (foo->coeff[3]/(_Zg - _r4x) + foo->coeff[4]/(_Zg - _r4y)) * _lnbarZg +
    foo->coeff[5]/(_Zg - _r4x) + foo->coeff[6]/(_Zg - _r4y) + foo->coeff[7]/_Zg;
}

/* ******************************************************************** */
/* Handling of all generic (i.e. non-analytic) cases.                   */

void TVIL_CaseGeneric_3sB (void)
{
  TVIL_COMPLEX ti, tf, temp;
  TVIL_REAL deltat_start;
  /* This is local! Global value remains unchanged. */
  TVIL_REAL imDispl;
  int i;
  TVIL_RESULT bar;

  _Gzxxyy = &(_G[_zxxyy].value);
  _Gx0yxz = &(_G[_x0yxz].value);
  _Gy0xyz = &(_G[_y0xyz].value);

  _Fbar0xyz = &(_FBAR[_0xyz].value);
  _Fy0xz = &(_FBAR[_y0xz].value);
  _Fz0xy = &(_FBAR[_z0xy].value);
  _Fx0yz = &(_FBAR[_x0yz].value);

  _IIxxz = &(_II[_xxz].value);
  _IIyyz = &(_II[_yyz].value);
  _IIxyz = &(_II[_xyz].value);

  /* Set parameter values: */
  _xx = _v;
  _yy = _x;
  _zz = _y;

  _nIfuns = 0;
  _ifun[_nIfuns++] = TVIL_SetParamsI (&(_II[_yyz]), _yyz, _yy, _yy, _zz);
  _ifun[_nIfuns++] = TVIL_SetParamsI (&(_II[_xxz]), _xxz, _xx, _xx, _zz);
  _ifun[_nIfuns++] = TVIL_SetParamsI (&(_II[_xyz]), _xyz, _xx, _yy, _zz);

  _nFBARfuns = 0;
  _fbarfun[_nFBARfuns++] = TVIL_SetParamsFBAR (&(_FBAR[_x0yz]), _x0yz, _xx, 0.0, _yy, _zz);
  _fbarfun[_nFBARfuns++] = TVIL_SetParamsFBAR (&(_FBAR[_y0xz]), _y0xz, _yy, 0.0, _xx, _zz);
  _fbarfun[_nFBARfuns++] = TVIL_SetParamsFBAR (&(_FBAR[_0xyz]), _0xyz, 0.0, _xx, _yy, _zz);
  _fbarfun[_nFBARfuns++] = TVIL_SetParamsFBAR (&(_FBAR[_z0xy]), _z0xy, _zz, 0.0, _xx, _yy);

  _nEfuns = 0;

  _nGfuns = 0;
  _gfun[_nGfuns++] = TVIL_SetParamsG (&(_G[_zxxyy]), _zxxyy, _zz, _xx, _xx, _yy, _yy);
  _gfun[_nGfuns++] = TVIL_SetParamsG (&(_G[_x0yxz]), _x0yxz, _xx, 0.0, _yy, _xx, _zz);
  _gfun[_nGfuns++] = TVIL_SetParamsG (&(_G[_y0xyz]), _y0xyz, _yy, 0.0, _xx, _yy, _zz);

  /* _nHfuns = 0; */
  _nHfuns = 1;
  _hfun = TVIL_SetParamsH (&_H, 0.0, _xx, _xx, _yy, _zz, _yy);

  /* Set up globals: */
  _r4x = 4*_xx;
  _r4y = 4*_yy;
  _lnbarx = TVIL_LOG (_xx/_qq);
  _lnbary = TVIL_LOG (_yy/_qq);
  _sqrtx = TVIL_SQRT (_xx);
  _sqrty = TVIL_SQRT (_yy);
  _sqrtxy = _sqrtx*_sqrty;
  _rplus = (_sqrtx + _sqrty)*(_sqrtx + _sqrty);
  _rminus = (_sqrtx - _sqrty)*(_sqrtx - _sqrty);
  _I0xy = (TVIL_REAL) TVIL_I2 (0.0, _xx, _yy, _qq);
  TVIL_FBARanalytic (_xx, _xx, _yy, _yy, _qq, &temp);
  _Fxxyy = (TVIL_REAL) (temp - _lnbarx * TVIL_I2 (_xx, _yy, _yy, _qq));
  TVIL_FBARanalytic (_yy, _yy, _xx, _xx, _qq, &temp);
  _Fyyxx = (TVIL_REAL) (temp - _lnbary * TVIL_I2 (_yy, _xx, _xx, _qq));

  /* Last bits: */
  _isInitialized = TRUE;
  _status        = UNEVALUATED;
  /* This is basically the end of SetParameters. */

  /* Then set up derivative coefficients in all sub-objects: */
  TVIL_SetupFunctions_3sB ();

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

  /* Now copy everything back to foo... */
  /* I functions will anyway be put in analytically: */
  /* foo->II[_xxz].value = bar.II[_xxz].value; */
  /* foo->II[_yyz].value = bar.II[_yyz].value; */
  /* foo->II[_xyz].value = bar.II[_xyz].value; */

  /* This is slightly wasteful but transparent: */
  TVIL_Backup (&bar);

  _FBAR[2].value = bar.FBAR[_y0xz];
  _FBAR[6].value = bar.FBAR[_z0xy];
  _FBAR[5].value = bar.FBAR[_0xyz];
  _FBAR[0].value = bar.FBAR[_x0yz];

  _G[3].value = bar.G[_zxxyy];
  _G[0].value = bar.G[_x0yxz];
  _G[5].value = bar.G[_y0xyz];

  _H.value = bar.H;

  /* Some functions are just the same: */
  _FBAR[10].value = _FBAR[2].value;
  _FBAR[7].value = _FBAR[6].value;
  _FBAR[4].value = _FBAR[5].value;
  _FBAR[8].value = _FBAR[0].value;

  _G[4].value = _G[0].value;
  _G[1].value = _G[5].value;

  /* The rest will be filled in analytically, but we have to reset
     arguments of the functions we used... */
  TVIL_SetParamsI (&(_II[uvx]), uvx, _u, _v, _x);
  TVIL_SetParamsI (&(_II[xyz]), xyz, _x, _y, _z);
  TVIL_SetParamsI (&(_II[uxy]), uxy, _u, _x, _y);

  TVIL_SetParamsFBAR (&(_FBAR[wuxy]), wuxy, _w, _u, _x, _y);
  TVIL_SetParamsFBAR (&(_FBAR[wvxz]), wvxz, _w, _v, _x, _z);
  TVIL_SetParamsFBAR (&(_FBAR[xuwy]), xuwy, _x, _u, _w, _y);
  TVIL_SetParamsFBAR (&(_FBAR[xvwz]), xvwz, _x, _v, _w, _z);

  TVIL_SetParamsG (&(_G[wuzvy]), wuzvy, _w, _u, _z, _v, _y);
  TVIL_SetParamsG (&(_G[xuvyz]), xuvyz, _x, _u, _v, _y, _z);
  TVIL_SetParamsG (&(_G[uvxwz]), uvxwz, _u, _v, _x, _w, _z);

  return;
}

/* **************************************************************** */
/* This should be called immediately prior to generic evaluation. */

int TVIL_SetupFunctions_3sB (void)
{
  int i;

  /* Set values in all sub-objects: */
  for (i=0; i<_nIfuns; i++)
    TVIL_SetupI_3sB (_ifun[i]);

  for (i=0; i<_nFBARfuns; i++)
    TVIL_SetupFBAR_3sB (_fbarfun[i]);

  for (i=0; i<_nGfuns; i++)
    TVIL_SetupG_3sB (_gfun[i]);

  if (_nHfuns)
    TVIL_SetupH_3sB (_hfun);

  _Iderivative = &TVIL_dIdt_3sB;
  _FBARderivative = &TVIL_dFBARdt_3sB;
  _Gderivative = &TVIL_dGdt_3sB;
  _Hderivative = &TVIL_dHdt_3sB;

  /* Decide how to integrate: */
  if ((_rminus < _zz) && (_zz < _rplus) && (_zz < _r4x) && (_zz < _r4y))
    _reAxisOK = YES;
  else
    _reAxisOK = NO;

  return 0;
}
