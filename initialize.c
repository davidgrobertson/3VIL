/*
  Initialization (pointer alignment) of function structs.

  This is everything that is independent of the values of the
  arguments; everything that *does* depend on u,v,w,x,y,z,qq is set in
  TVIL_SetParameters below.  This routine only ever needs to be called
  once.
*/

#include "internal.h"

/* ******************************************************************* */
/* This should be called once, before anything else is done. */

void TVIL_Setup (void)
{
  int i, j;

  /* These define which functions go where in the evolution
     equations: */
  static int FrefF[NUM_F_FUNCS][3] = {
    {uwxy, xuwy, yuwx}, 
    {vwxz, xvwz, zvwx},
    {uwxy, wuxy, yuwx},
    {vwxz, wvxz, zvwx},
    {vuyz, yuvz, zuvy},
    {wuxy, xuwy, yuwx}, 
    {uvyz, vuyz, zuvy},
    {uwxy, wuxy, xuwy},
    {uvyz, yuvz, zuvy},
    {wvxz, xvwz, zvwx},
    {uvyz, vuyz, yuvz},
    {vwxz, wvxz, xvwz}
  };

  /* In the following the 4 elements correspond (in order) to the four
     F terms in dFbar/dt (eq. 6.20 of current preprint): */
  static int FrefI[NUM_F_FUNCS][4] = {
    {uxy, wxy, uwy, uwx}, 
    {vxz, wxz, vwz, vwx},
    {uwy, wxy, uxy, uwx},
    {vwz, wxz, vxz, vwx},
    {vyz, uyz, uvz, uvy},
    {wxy, uxy, uwy, uwx},
    {uvz, vyz, uyz, uvy},
    {uwx, wxy, uxy, uwy},
    {uyz, vyz, uvz, uvy},
    {wxz, vxz, vwz, vwx},
    {uvy, vyz, uyz, uvz},
    {vwx, wxz, vxz, vwz}
  };

  static int ErefF[NUM_E_FUNCS][4] = {
    {wuxy, uwxy, xuwy, yuwx}, 
    {vwxz, wvxz, xvwz, zvwx},
    {uvyz, vuyz, yuvz, zuvy}
  };

  static int GrefF[NUM_G_FUNCS][4] = {
    {uvyz, zuvy, vuyz, yuvz},
    {uvyz, vuyz, yuvz, zuvy},
    {vwxz, xvwz, wvxz, zvwx},
    {vwxz, wvxz, xvwz, zvwx},
    {uwxy, xuwy, wuxy, yuwx},
    {uwxy, wuxy, xuwy, yuwx}
  };

  static int GrefI[NUM_G_FUNCS][10] = {
    {uwz, vwy, vyz, uvy, uyz, uvz, vwy, vwy, uwz, uwz},
    {uvx, xyz, vyz, uyz, uvz, uvy, xyz, xyz, uvx, uvx},
    {uvx, uwz, wxz, vwz, vxz, vwx, uwz, uwz, uvx, uvx},
    {vwy, xyz, wxz, vxz, vwz, vwx, xyz, xyz, vwy, vwy},
    {uvx, vwy, wxy, uwy, uxy, uwx, vwy, vwy, uvx, uvx},
    {uwz, xyz, wxy, uxy, uwy, uwx, xyz, xyz, uwz, uwz}
  };

  static int HrefG[6] = {
    xuvyz, wuzvy, zuwxy, vuxwy, yvwxz, uvxwz
  };

  static int HrefF[6][2] = {
    {xvwz, xuwy},
    {wvxz, wuxy},
    {zvwx, zuvy},
    {vwxz, vuyz},
    {yuvz, yuwx},
    {uvyz, uwxy}
  };

  /* First 2 (of 4) are for the Fs, last 2 are the explicit Is */
  static int HrefI[6][4] = {
    {vwz, uwy, uwz, vwy},
    {vxz, uxy, uvx, xyz},
    {vwx, uvy, uvx, vwy},
    {wxz, uyz, uwz, xyz},
    {uvz, uwx, uwz, uvx},
    {vyz, wxy, xyz, vwy}
  };

  /* Set function types and scratch pointers: */
  for (i=0; i<NUM_I_FUNCS; i++) {
    _II[i].coeff = &(_II[i].cII[0]);
    _II[i].type = ITYPE;
  }
  for (i=0; i<NUM_F_FUNCS; i++) {
    _FBAR[i].coeff = &(_FBAR[i].cFF11);
    _FBAR[i].type = FBARTYPE;
  }
  for (i=0; i<NUM_G_FUNCS; i++) {
    _G[i].coeff = &(_G[i].cGF1[0]);
    _G[i].type = GTYPE;
  }
  for (i=0; i<NUM_E_FUNCS; i++)
    _E[i].type = ETYPE;

  _H.coeff = &(_H.cHGnum[0][0]);
  _H.type = HTYPE;

  /* Align pointers: */

  /* Fbar-type objects */
  for (i=0; i<NUM_F_FUNCS; i++)
    for (j=0; j<3; j++)
      _FBAR[i].fval[j] = &(_FBAR[FrefF[i][j]].value);

  for (i=0; i<NUM_F_FUNCS; i++)
    for (j=0; j<4; j++)
      _FBAR[i].ival[j] = &(_II[FrefI[i][j]].value);

  /* E-type objects (these point to values of F, not FBAR!) */
  for (i=0; i<NUM_E_FUNCS; i++)
    for (j=0; j<4; j++)
      _E[i].fval[j] = &(_FBAR[ErefF[i][j]].fValue);

  /* G-type objects */
  for (i=0; i<NUM_G_FUNCS; i++)
    for (j=0; j<4; j++)
      _G[i].fval[j] = &(_FBAR[GrefF[i][j]].value);

  for (i=0; i<NUM_G_FUNCS; i++)
    for (j=0; j<10; j++)
      _G[i].ival[j] = &(_II[GrefI[i][j]].value);

  for (i=0; i<6; i++) {
    _H.gval[i] = &(_G[HrefG[i]].value);
    for (j=0; j<2; j++) {
      _H.fval[i][j] = &(_FBAR[HrefF[i][j]].value);
      _H.ival[i][j] = &(_II[HrefI[i][j]].value);
      _H.ival[i][j+2] = &(_II[HrefI[i][j+2]].value);
    }
  }

  _tPole = calloc (sizeof(TVIL_REAL), NUM_POLES);

  /* Later a is set to 2.0*MAX(u,v,w,x,y,z) */
  _a = _a2 = _a3 = _a4 = _a5 = _a6 = _a7 = _a8 = _a9 = 1.0L;

  /* Set default Runge-Kutta parameters.  */
  /* Evaluation routines: */
  _RKstepper6 = &TVIL_rk6;
  _RKstepper5 = &TVIL_rk5;

  /* These can be reset by calling TVIL_ResetStepSizeParams */
  _precisionGoal = TVIL_PRECISION_GOAL;
  _nStepsStart   = TVIL_NSTEPS_START;
  _nStepsMin     = TVIL_NSTEPS_MIN;
  _nStepsMaxCon  = TVIL_NSTEPS_MAX_CON;
  _nStepsMaxVar  = TVIL_NSTEPS_MAX_VAR;
  /* This can be reset by calling TVIL_SetContourDisplacement: */
  _imDispl       = IM_DISPL;
  /* This can be reset by calling TVIL_Set__tInitial: */
  _tInit         = T_INIT;
  /* This can be toggled by TVIL_(Set/Unset)DoAnalytic: */
  _doAnalytic    = DOANALYTIC;
  /* This can be toggled with TVIL_(Set/Unset)ForceContour */
  _forceContour  = NO;
  _forceDefault  = NO;

  _isAligned     = YES;
  _status        = UNEVALUATED;

  return;
}

/* **************************************************************** */

int TVIL_Atest (TVIL_REAL u, TVIL_REAL w, TVIL_REAL x, TVIL_REAL y)
{
  if ( (0 == TVIL_TestDelta(u,w,x,y)) &&
       (TVIL_FABS(TVIL_Phi (u,w,x,y)) < 
        TVIL_FABS(8 * _a * (u+w-x-y) * (u-w+x-y) * (u-w-x+y)) * TVIL_TOL) )
    return 1;
  else
    return 0;
}

/* **************************************************************** */
/* Determines and sets the default value for a in the specified data
   object. Note that foo->_evalMode must be set before this is
   called! */

void TVIL_SetDefault_a (void)
{
  TVIL_REAL tmp[7], largestArg, tmpabs;
  TVIL_REAL aMult[] = {2.0, 1.9, 1.95, 2.05};
  int i, nArgs, atest;
  char funcname[] = "SetDefault_a";

  if (_evalMode == ALL) {
    nArgs = 6;
    tmp[0] = _u;
    tmp[1] = _v;
    tmp[2] = _w;
    tmp[3] = _x;
    tmp[4] = _y;
    tmp[5] = _z;
  }
  else if (_evalMode == EFG) {
    nArgs = 5;
    tmp[0] = _u;
    tmp[1] = _v;
    tmp[2] = _w;
    tmp[3] = _x;
    tmp[4] = _y;
  }
  else if (_evalMode == EF) {
    nArgs = 4;
    tmp[0] = _u;
    tmp[1] = _w;
    tmp[2] = _x;
    tmp[3] = _y;
  }

  largestArg = TVIL_FABS(tmp[0]);
  for (i=1; i<nArgs; i++)
    if ((tmpabs = TVIL_FABS(tmp[i])) > largestArg) largestArg = tmpabs;

  for (i=0; i<4; i++) {

    _a = aMult[i]*largestArg;

    /* printf("Testing a multiplier %Lf...", aMult[i]); */

    atest = TVIL_Atest (_u,_w,_x,_y);

    if (_evalMode == ALL)
      atest += TVIL_Atest (_w,_v,_x,_z) + TVIL_Atest (_u,_v,_y,_z);

    if (atest != 0) {
      /* printf ("problematic! Moving on...\n"); */
      ;
    }
    else {
      /* printf ("good value.\n"); */
      break;
    }
  }
  if (i==4)
    TVIL_Error (funcname, "This should never happen! No valid a found.", 45);

  /* User can change this later if desired: */
  _aParameter = _a;

  return;
}

/* ******************************************************************* */
/* Preparation for generic evaluation (integration). Sets derivative
   coefficients in all sub-objects and determines pole
   locations. Derivative function pointers are set according to
   evaluation mode. This should be called immediately prior to generic
   evaluation. */

int TVIL_SetupFunctions (void)
{
  int i, j;

  TVIL_SetDefault_a ();

  /* Not all of these need to be set for what happens in this routine,
     but they are needed for the generic evaulation which should be
     about to happen. */
  _a = _aParameter;
  _a2 = _a*_a;
  _a3 = _a2*_a;
  _a4 = _a2*_a2;
  _a5 = _a2*_a3;
  _a6 = _a3*_a3;
  _a7 = _a4*_a3;
  _a8 = _a4*_a4;
  _a9 = _a4*_a5;

  /* Set values in all sub-objects: */
  _nIfuns = 0;
  for (i=0; i<NUM_I_FUNCS; i++)
    if (_integrateII[i])
      _ifun[_nIfuns++] = TVIL_SetupI (&(_II[i]));

  _nFBARfuns = 0;
  for (i=0; i<NUM_F_FUNCS; i++)
    if (_integrateFBAR[i])
      _fbarfun[_nFBARfuns++] = TVIL_SetupFBAR (&(_FBAR[i]));

  /* nEfuns = 0; */
  /* for (i=0; i<NUM_E_FUNCS; i++) */
  /*   if (integrateE[i]) */
  /*     efun[nEfuns++] = TVIL_SetupE (&(E[i])); */

  _nGfuns = 0;
  for (i=0; i<NUM_G_FUNCS; i++)
    if (_integrateG[i])
      _gfun[_nGfuns++] = TVIL_SetupG (&(_G[i]));

  if (_integrateH) {
    _nHfuns = 1;
    _hfun = TVIL_SetupH (&_H);
  }
  else
    _nHfuns = 0;

  /* Set up derviative pointers for generic evaluation: */
  _Iderivative = &TVIL_dIdt;
  _FBARderivative = &TVIL_dFBARdt;
  _Gderivative = &TVIL_dGdt;
  _Hderivative = &TVIL_dHdt;

  /* Now calculate pole locations... */
  j = 0;

  /* Poles associated with I functions: */
  for (i=0; i<_nIfuns; i++) {
    if (_ifun[i]->p[0] > 0 && _ifun[i]->p[0] < 1.0L + THRESH_CUTOFF) {
      _tPole[j++] = _ifun[i]->p[0];
      /* printf("Pole added, j=%d now\n", j); */
    }
    if (_ifun[i]->p[1] > 0 && _ifun[i]->p[1] < 1.0L + THRESH_CUTOFF) {
      _tPole[j++] = _ifun[i]->p[1];
      /* printf("Pole added, j=%d now\n", j); */
    }
  }

  /* Poles associated with FBAR functions: */
  for (i=0; i<_nFBARfuns; i++) {
    if ((i % 2 == 0) && _fbarfun[i]->p2 > 0 && _fbarfun[i]->p2 < 1.0L + THRESH_CUTOFF) {
      _tPole[j++] = _fbarfun[i]->p2;
      /* printf("Pole added, j=%d now\n", j); */
    }
    if (_fbarfun[i]->p3 > 0 && _fbarfun[i]->p3 < 1.0L + THRESH_CUTOFF) {
      _tPole[j++] = _fbarfun[i]->p3;
      /* printf("Pole added, j=%d now\n", j); */
    }
  }

  /* Poles associated with H function: */
  if (_nHfuns)
    for (i=0; i<3; i++) {
      if (_hfun->cHd1roots[i] > 0 && _hfun->cHd1roots[i] < 1.0L + THRESH_CUTOFF) {
	_tPole[j++] = _hfun->cHd1roots[i];
	/* printf("Pole added, j=%d now\n", j); */
      }
    }

  _nPoles = j;

  qsort (_tPole, _nPoles, sizeof(TVIL_REAL), TVIL_Compare);

  if (_nPoles > 0 && _tPole[0] < 1.0L)
    _reAxisOK = NO;
  else
    _reAxisOK = YES;

  _poleAt1 = NO;
  for (i=0; i<_nPoles; i++)
    if (TVIL_FABS (_tPole[i] - 1.0L) < THRESH_CUTOFF) {
      _poleAt1 = YES;
      break;
    }

  return 0;
}
