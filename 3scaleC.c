/* Code for evaluating H0xyxzy and subordinate integrals. */

#include "internal.h"

/* Globals: */
TVIL_REAL _xx, _yy, _zz;
TVIL_REAL _lnbarx, _lnbary, _sqrtx, _sqrty, _sqrtxy;
TVIL_REAL _rplus, _rminus;
TVIL_REAL _Fxxyy, _Fyyxx, _G0xxyy;

TVIL_COMPLEX *_Gzxyxy;
TVIL_COMPLEX *_Fbar0xyz, *_Fx0yz, *_Fy0xz, *_Fz0xy;
TVIL_COMPLEX *_IIxyz;

/* **************************************************************** */

void TVIL_SetupI_3sC (TVIL_ITYPE *foo)
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
  else
    TVIL_Error ("ConstructI_3sC", "Invalid function type.", 888);

  return;
}

/* **************************************************************** */
/* These coefficients (and derivatives) are just the same as for case
   3sA, so for now just wrap it. */

void TVIL_SetupFBAR_3sC (TVIL_FBARTYPE *foo)
{
  TVIL_SetupFBAR_3sA (foo);

  return;
}

/* **************************************************************** */

void TVIL_SetupG_3sC (TVIL_GTYPE *foo)
{
  TVIL_REAL x, y;

  if (foo->which == _zxyxy) {

    x = foo->arg[1];
    y = foo->arg[2];

    /* cGzxyxyIplus   */
    foo->coeff[0] = -2 + (_lnbarx * _sqrtx + _lnbary * _sqrty)/(_sqrtx + _sqrty);

    /* cGzxyxyIminus  */
    foo->coeff[1] = -2 + (_lnbarx * _sqrtx - _lnbary * _sqrty)/(_sqrtx - _sqrty);

    /* cGzxyxyI0  */
    foo->coeff[2] = 2 * (1 - (x * _lnbarx - y * _lnbary)/(x-y));

    /* cGzxyxyplus  */
    foo->coeff[3] = (_sqrtx * (_Fxxyy + 13.*x/4. - 5.*_lnbarx*x/4. + 5.*y/3. - _lnbary*y) + 
		     _sqrty * (_Fyyxx + 5.*x/3. - _lnbarx*x + 13.*y/4. - 5.*_lnbary*y/4.))/(_sqrtx+_sqrty);
    
    /* cGzxyxyminus */
    foo->coeff[4] = (_sqrtx * (_Fxxyy + 13.*x/4. - 5.*_lnbarx*x/4. + 5.*y/3. - _lnbary*y) + 
		     -_sqrty * (_Fyyxx + 5.*x/3. - _lnbarx*x + 13.*y/4. - 5.*_lnbary*y/4.))/(_sqrtx-_sqrty);

    /* cGzxyxy0  */
    foo->coeff[5] = -11.*(x+y)/6. + (2*(y*_Fyyxx - x*_Fxxyy) + 
				   (_lnbarx*x*x - _lnbary*y*y)/2.)/(x-y);
  }
  else
    TVIL_Error ("ConstructG_3sC", "Invalid function type.", 888);

  return;
}

/* **************************************************************** */

void TVIL_SetupH_3sC (TVIL_HTYPE *foo)
{
  TVIL_REAL x, y, temp;
  
  x = foo->arg[1];
  y = foo->arg[2];

  /* cH0xyxzyG  */
  foo->coeff[0] = 1./(2.*_sqrtxy);

  /* cH0xyxzyI  */
  foo->coeff[1] = (2. - _lnbarx - _lnbary)/(2.*_sqrtxy);

  temp = (x*(9 - 8*_lnbarx + 2*_lnbarx*_lnbarx) +
          y*(9 - 8*_lnbary + 2*_lnbary*_lnbary))/(8.*_sqrtxy);

  /* cH0xyxzyLplus   */
  foo-> coeff[2] = 1./4. - temp;

  /* cH0xyxzyLminus  */
  foo->coeff[3] = 1./4. + temp;

  temp = (-_Fxxyy - _Fyyxx - _G0xxyy + 
	  x * (-95./12. + 11.*_lnbarx/4. + 5*_lnbary - 4*_lnbarx*_lnbary + _lnbarx*_lnbarx*_lnbary) + 
	  y * (-95./12. + 5*_lnbarx + 11.*_lnbary/4. - 4*_lnbarx*_lnbary + _lnbarx*_lnbary*_lnbary) 
	  )/(4*_sqrtxy);

  /* cH0xyxzyplus  */
  foo->coeff[4] = 1./12. - 4*Zeta3 + temp;

  /* cH0xyxzyminus  */
  foo->coeff[5] = 1./12. - 4*Zeta3 - temp;

  return;
}

/* **************************************************************** */
/* Same as for 3sA */

int TVIL_InitialI_3sC (TVIL_ITYPE *foo, 
		       TVIL_REAL Q2,
		       TVIL_COMPLEX tinit)
{
  foo->value = TVIL_I2 (foo->arg[0], foo->arg[1], tinit, Q2);
  foo->deriv = TVIL_dIdt_3sC (foo, tinit, Q2);

  return 0;
}

/* **************************************************************** */
/* Same as for 3sA */

int TVIL_InitialFBAR_3sC (TVIL_FBARTYPE *foo, 
			  TVIL_REAL Q2,
			  TVIL_COMPLEX tinit)
{
  if (foo->which == _y0xz) {

    TVIL_FBARanalytic (foo->arg[0], foo->arg[1], foo->arg[2], tinit, Q2, &(foo->value));

    /* Then make it into an F: */
    foo->value -= TVIL_CLOG (foo->arg[0]/Q2)*TVIL_I2 (foo->arg[1], foo->arg[2], tinit, Q2);
  }
  else if (foo->which == _z0xy) {

    TVIL_FBARanalytic (tinit, foo->arg[1], foo->arg[2], foo->arg[3], Q2, &(foo->value));
    /* Then make it into an F: */
    foo->value -= TVIL_CLOG (tinit/Q2)*TVIL_I2 (foo->arg[1], foo->arg[2], foo->arg[3], Q2);
  }
  else if (foo->which == _0xyz) {

    /* This one is an FBAR */
    TVIL_FBARanalytic (foo->arg[0], foo->arg[1], foo->arg[2], tinit, Q2, &(foo->value));
  }
  else if (foo->which == _x0yz) {

    TVIL_FBARanalytic (foo->arg[0], foo->arg[1], foo->arg[2], tinit, Q2, &(foo->value));

    /* Then make it into an F: */
    foo->value -= TVIL_CLOG (foo->arg[0]/Q2)*TVIL_I2 (foo->arg[1], foo->arg[2], tinit, Q2);
  }
  else
    TVIL_Error ("InitialFBAR_3sC", "Impossible, invalid function type.", 888);

  return 0;
}

/* **************************************************************** */

int TVIL_InitialG_3sC (TVIL_GTYPE *foo, 
		       TVIL_REAL Q2,
		       TVIL_COMPLEX tinit)
{
  if (foo->which == _zxyxy) {

    TVIL_Ganalytic (tinit, foo->arg[1], foo->arg[2], foo->arg[3], foo->arg[4], Q2, &(foo->value));
  }
  else
    TVIL_Error ("InitialG_3sC", "Wrong specifier; impossible!", 333);

  return 0;
}

/* **************************************************************** */

int TVIL_InitialH_3sC (TVIL_HTYPE *foo, 
		       TVIL_REAL Q2,
		       TVIL_COMPLEX tinit)
{
  return TVIL_Hanalytic (0., foo->arg[1], foo->arg[2], foo->arg[3], tinit, foo->arg[5],
			 Q2, &(foo->value));
}

/* **************************************************************** */

TVIL_COMPLEX TVIL_dIdt_3sC (TVIL_ITYPE *foo, TVIL_COMPLEX t, TVIL_REAL Q2)
{
  TVIL_COMPLEX result;

  if (foo->which == _xyz) {

    result = 0.5L * (1./(_Zg - _rplus) + 1./(_Zg - _rminus)) * (foo->value) +
      (foo->coeff[0]/(_Zg - _rplus) + foo->coeff[1]/(_Zg - _rminus) - 1) * _lnbarZg +
      foo->coeff[2]/(_Zg - _rplus) + foo->coeff[3]/(_Zg - _rminus) + 2;
  }
  else
    TVIL_Error ("dIdt_3sC", "Impossible, wrong function type.", 909);

  return result;
}

/* **************************************************************** */
/* Just the same as for case 3sA. */

TVIL_COMPLEX TVIL_dFBARdt_3sC (TVIL_FBARTYPE *foo, TVIL_COMPLEX t, TVIL_REAL Q2)
{
  return TVIL_dFBARdt_3sA (foo, t, Q2);
}

/* **************************************************************** */

TVIL_COMPLEX TVIL_dGdt_3sC (TVIL_GTYPE *foo, TVIL_COMPLEX t, TVIL_REAL Q2)
{
  TVIL_COMPLEX result;

  if (foo->which == _zxyxy) {

    result = (1/(_Zg - _rplus) + 1/(_Zg - _rminus) - 1/_Zg) * (foo->value) + 
      (foo->coeff[0]/(_Zg - _rplus) + foo->coeff[1]/(_Zg - _rminus) + 
       foo->coeff[2]/_Zg) * (*_IIxyz) + 
      foo->coeff[3]/(_Zg - _rplus) + foo->coeff[4]/(_Zg - _rminus) + foo->coeff[5]/_Zg - 1;
  }
  else
    TVIL_Error ("dGdt_3sC", "Impossible, wrong function type.", 909);

  return result;
}

/* **************************************************************** */

TVIL_COMPLEX TVIL_dHdt_3sC (TVIL_HTYPE *foo, TVIL_COMPLEX t, TVIL_REAL Q2)
{
  return (foo->coeff[0]) * (1/(_Zg - _rplus) - 1/(_Zg - _rminus)) * 
    (-0.5L*(*_Gzxyxy) + *_Fz0xy + *_Fbar0xyz - *_Fx0yz - *_Fy0xz) +
    (foo->coeff[1]) * (1/(_Zg - _rplus) - 1/(_Zg - _rminus)) * (*_IIxyz) +
    (foo->coeff[2]/(_Zg - _rplus) + foo->coeff[3]/(_Zg - _rminus))*_lnbarZg +
    (foo->coeff[4]/(_Zg - _rplus) + foo->coeff[5]/(_Zg - _rminus));
}

/* ******************************************************************** */
/* Handling of all generic (i.e. non-analytic) cases.                   */

void TVIL_CaseGeneric_3sC (void)
{
  TVIL_COMPLEX ti, tf, temp;
  TVIL_REAL deltat_start, lnbarz;
  TVIL_REAL imDispl;
  int i;
  TVIL_RESULT bar;

  _Gzxyxy = &(_G[_zxyxy].value);

  _Fbar0xyz = &(_FBAR[_0xyz].value);
  _Fy0xz = &(_FBAR[_y0xz].value);
  _Fz0xy = &(_FBAR[_z0xy].value);
  _Fx0yz = &(_FBAR[_x0yz].value);

  _IIxyz = &(_II[_xyz].value);

  /* Set parameter values: */
  _xx = _v;
  _yy = _w;
  _zz = _y;

  _nIfuns = 0;
  _ifun[_nIfuns++] = TVIL_SetParamsI (&(_II[_xyz]), _xyz, _xx, _yy, _zz);

  _integrateII[_xyz] = YES;

  _nFBARfuns = 0;
  _fbarfun[_nFBARfuns++] = TVIL_SetParamsFBAR (&(_FBAR[_x0yz]), _x0yz, _xx, 0.0, _yy, _zz);
  _fbarfun[_nFBARfuns++] = TVIL_SetParamsFBAR (&(_FBAR[_y0xz]), _y0xz, _yy, 0.0, _xx, _zz);
  _fbarfun[_nFBARfuns++] = TVIL_SetParamsFBAR (&(_FBAR[_0xyz]), _0xyz, 0.0, _xx, _yy, _zz);
  _fbarfun[_nFBARfuns++] = TVIL_SetParamsFBAR (&(_FBAR[_z0xy]), _z0xy, _zz, 0.0, _xx, _yy);

  _integrateFBAR[_x0yz] = YES;
  _integrateFBAR[_y0xz] = YES;
  _integrateFBAR[_0xyz] = YES;
  _integrateFBAR[_z0xy] = YES;

  _nEfuns = 0;

  _nGfuns = 0;
  _gfun[_nGfuns++] = TVIL_SetParamsG (&(_G[_zxyxy]), _zxyxy, _zz, _xx, _yy, _xx, _yy);

  _integrateG[_zxyxy] = YES;

  _nHfuns = 0;
  _nHfuns = 1;
  _hfun = TVIL_SetParamsH (&_H, 0.0, _xx, _yy, _xx, _zz, _yy);

  _integrateH = YES;

  /* Set up globals: */
  _lnbarx = TVIL_LOG (_xx/_qq);
  _lnbary = TVIL_LOG (_yy/_qq);
  _sqrtx = TVIL_SQRT (_xx);
  _sqrty = TVIL_SQRT (_yy);
  _sqrtxy = _sqrtx*_sqrty;
  _rplus = (_sqrtx + _sqrty)*(_sqrtx + _sqrty);
  _rminus = (_sqrtx - _sqrty)*(_sqrtx - _sqrty);
  TVIL_FBARanalytic (_xx, _xx, _yy, _yy, _qq, &temp);
  _Fxxyy = (TVIL_REAL) (temp - _lnbarx * TVIL_I2 (_xx, _yy, _yy, _qq));
  TVIL_FBARanalytic (_yy, _yy, _xx, _xx, _qq, &temp);
  _Fyyxx = (TVIL_REAL) (temp - _lnbary * TVIL_I2 (_yy, _xx, _xx, _qq));
  TVIL_Ganalytic (0, _xx, _xx, _yy, _yy, _qq, &temp);
  _G0xxyy = TVIL_CREAL (temp);

  /* Last bits: */
  _isInitialized = TRUE;
  _status        = UNEVALUATED;
  /* This is basically the end of SetParameters. */

  /* Then set up derivative coefficients in all sub-objects: */
  TVIL_SetupFunctions_3sC ();

  /* TVIL_PrintIntegratedFunctions (); */
  /* exit(0); */

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
  /* foo->II[_xyz].value = bar.II[_xyz].value; */
  
  /* This is slightly wasteful but transparent: */
  TVIL_Backup (&bar);

  _FBAR[0].value = bar.FBAR[_y0xz];
  _FBAR[6].value = bar.FBAR[_z0xy];
  _FBAR[5].value = bar.FBAR[_0xyz];
  _FBAR[2].value = bar.FBAR[_x0yz];

  _G[3].value = bar.G[_zxyxy];

  /* A couple of "pseudo-analytic" results: */
  lnbarz = TVIL_LOG (_zz/_qq);

  /* GX0XYZ (remember we need the F value, not FBAR!) */
  _G[1].value = -7.*(_yy + _zz)/3. - 11.*_xx/12. + _yy*_lnbary + _zz*lnbarz + 
    _xx*_lnbarx/4 + (*_IIxyz)*(2. - _lnbarx) - 
    (*_Fx0yz - _lnbarx*TVIL_I2(0.,_yy,_zz,_qq));

  /* GY0YXZ */
  _G[0].value = -7.*(_xx + _zz)/3. - 11.*_yy/12. + _xx*_lnbarx + _zz*lnbarz +
    _yy*_lnbary/4 + (*_IIxyz)*(2. - _lnbary) - 
    (*_Fy0xz - _lnbary*TVIL_I2(0.,_xx,_zz,_qq)); 

  _H.value = bar.H;

  /* Some functions are just the same: */
  _FBAR[10].value = _FBAR[0].value;
  _FBAR[7].value = _FBAR[6].value;
  _FBAR[4].value = _FBAR[5].value;
  _FBAR[8].value = _FBAR[2].value;

  _G[4].value = _G[1].value;
  _G[5].value = _G[0].value;

  /* The rest will be filled in analytically, but we have to reset
     arguments of the functions we used... */
  TVIL_SetParamsI (&(_II[uxy]), uxy, _u, _x, _y);

  TVIL_SetParamsFBAR (&(_FBAR[wuxy]), wuxy, _w, _u, _x, _y);
  TVIL_SetParamsFBAR (&(_FBAR[wvxz]), wvxz, _w, _v, _x, _z);
  TVIL_SetParamsFBAR (&(_FBAR[xuwy]), xuwy, _x, _u, _w, _y);
  TVIL_SetParamsFBAR (&(_FBAR[xvwz]), xvwz, _x, _v, _w, _z);

  TVIL_SetParamsG (&(_G[wuzvy]), wuzvy, _w, _u, _z, _v, _y);

  return;
}

/* **************************************************************** */
/* This should be called immediately prior to generic evaluation. */

int TVIL_SetupFunctions_3sC (void)
{
  int i;

  /* Set values in all sub-objects: */
  for (i=0; i<_nIfuns; i++)
    TVIL_SetupI_3sC (_ifun[i]);

  for (i=0; i<_nFBARfuns; i++)
    TVIL_SetupFBAR_3sC (_fbarfun[i]);

  for (i=0; i<_nGfuns; i++)
    TVIL_SetupG_3sC (_gfun[i]);

  if (_nHfuns)
    TVIL_SetupH_3sC (_hfun);

  _Iderivative = &TVIL_dIdt_3sC;
  _FBARderivative = &TVIL_dFBARdt_3sC;
  _Gderivative = &TVIL_dGdt_3sC;
  _Hderivative = &TVIL_dHdt_3sC;

  /* Decide how to integrate: */
  if ((_rminus < _zz) && (_zz < _rplus))
    _reAxisOK = YES;
  else
    _reAxisOK = NO;

  return 0;
}
