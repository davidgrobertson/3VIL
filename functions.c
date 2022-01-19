/* Miscellaneous and general functions */

#include "internal.h"
#include <string.h>

/* Here are the global declarations: */

/* ================================ */
/*          GLOBAL DATA             */
/* ================================ */

int _isAligned = NO;     /* Indicates whether the data sub-objects
			   have been constructed. */

int _isInitialized = NO; /* Indicates whether initial values have
			   been set. */

int _evalMode;           /* Indicates which set of functions is to be
			   evaluated (i.e., ALL=EFGH, EFG, EF).  See
			   3vil_global.h for details */

int _reAxisOK;           /* YES/NO depending on whether there is a
			   pole on the real-t axis between t=0 and
			   t=1. */

int _poleAt1;            /* YES/NO depending on whether there is a
			   pole near t=1. */

int _doAnalytic;         /* If YES (NO), put in (don't put in) all
			   analytically known functions after
			   generic evaulation. */

int _forceContour;       /* If YES, force evaulation by integration
			   along contour in complex plane, even if
			   integration along real t-axis is
			   possible. */

int _forceDefault;       /* If YES, force default evaluation,
			   ignoring special 3-scale cases. */

int _status;             /* Current evaluation status: whether
			   evaluated and, if so, how (see
			   3vil_global.h for value definitions). */

/* Parameters and basis fuctions: */
TVIL_REAL _u, _v, _w, _x, _y, _z, _qq;
TVIL_ITYPE      _II[NUM_I_FUNCS];
TVIL_FBARTYPE _FBAR[NUM_F_FUNCS];
TVIL_ETYPE       _E[NUM_E_FUNCS];
TVIL_GTYPE       _G[NUM_G_FUNCS];
TVIL_HTYPE       _H;

/* For testing argument permutations: */
TVIL_REAL _arglist[6];

/* The actual functions to be integrated... */
int _integrateII[NUM_I_FUNCS];
int _integrateFBAR[NUM_F_FUNCS];
int _integrateE[NUM_E_FUNCS];
int _integrateG[NUM_G_FUNCS];
int _integrateH;

/* ...and pointers thereto: */
int _nIfuns;
int _nFBARfuns;
int _nEfuns;
int _nGfuns;
int _nHfuns;
TVIL_ITYPE    *_ifun[NUM_I_FUNCS];
TVIL_FBARTYPE *_fbarfun[NUM_F_FUNCS];
TVIL_ETYPE    *_efun[NUM_E_FUNCS];
TVIL_GTYPE    *_gfun[NUM_G_FUNCS];
TVIL_HTYPE    *_hfun;

/* Pointers to derivative evaluators: */
TVIL_COMPLEX (*_Iderivative) (TVIL_ITYPE *, TVIL_COMPLEX, TVIL_REAL);
TVIL_COMPLEX (*_FBARderivative) (TVIL_FBARTYPE *, TVIL_COMPLEX, TVIL_REAL);
TVIL_COMPLEX (*_Gderivative) (TVIL_GTYPE *, TVIL_COMPLEX, TVIL_REAL);
TVIL_COMPLEX (*_Hderivative) (TVIL_HTYPE *, TVIL_COMPLEX, TVIL_REAL);

TVIL_REAL *_tPole;
int        _nPoles;

/* Parameters for numerical integration; defaults are defined in
   3vil_params.h: */
TVIL_REAL _imDispl;
TVIL_REAL _tInit;
TVIL_REAL _aParameter;

/* Parameters for automatic step-size control in Runge-Kutta: */
TVIL_REAL _precisionGoal;
int       _nStepsStart, _nStepsMaxCon, _nStepsMaxVar, _nStepsMin;

/* Pointers to RK stepper functions: */
int  (*_RKstepper6) ();
void (*_RKstepper5) ();

/* Global parameters */
TVIL_REAL _a, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9;
TVIL_REAL _maxerr, _err_H, _maxerr_noH; /* From the rk6 stepper. */

TVIL_COMPLEX _Ug, _Vg, _Wg, _Xg, _Yg, _Zg;
TVIL_COMPLEX _lnbarUg, _lnbarVg, _lnbarWg, _lnbarXg, _lnbarYg, _lnbarZg;

/* Default values: */
int _print3VILWarns = PRINTWARNS_DEFAULT;
int _printBold  = PRINTBOLD_DEFAULT;
int _printStyle = PRINTSTYLE_DEFAULT;

/* ====== END OF GLOBAL DATA ========== */

/* ******************************************************************* */
/* This sets the arguments in the function structs, to prepare them
   for possible analytic evaluation. If we need to integrate, a
   further routine will construct the integration coefficients, etc.

   This should work for any evaluation subset, assuming the evaluate*
   arrays have all been set properly.
*/

void TVIL_SetArguments (TVIL_RESULT *foo)
{
  if (foo->evaluateII[uvx]) TVIL_SetParamsI (&(_II[uvx]), uvx, _u, _v, _x);
  if (foo->evaluateII[xyz]) TVIL_SetParamsI (&(_II[xyz]), xyz, _x, _y, _z);
  if (foo->evaluateII[uxy]) TVIL_SetParamsI (&(_II[uxy]), uxy, _u, _x, _y);
  if (foo->evaluateII[vxz]) TVIL_SetParamsI (&(_II[vxz]), vxz, _v, _x, _z);
  if (foo->evaluateII[uwz]) TVIL_SetParamsI (&(_II[uwz]), uwz, _u, _w, _z);
  if (foo->evaluateII[vwy]) TVIL_SetParamsI (&(_II[vwy]), vwy, _v, _w, _y);
  if (foo->evaluateII[uwy]) TVIL_SetParamsI (&(_II[uwy]), uwy, _u, _w, _y);
  if (foo->evaluateII[vwz]) TVIL_SetParamsI (&(_II[vwz]), vwz, _v, _w, _z);
  if (foo->evaluateII[vyz]) TVIL_SetParamsI (&(_II[vyz]), vyz, _v, _y, _z);
  if (foo->evaluateII[wxy]) TVIL_SetParamsI (&(_II[wxy]), wxy, _w, _x, _y);
  if (foo->evaluateII[uvz]) TVIL_SetParamsI (&(_II[uvz]), uvz, _u, _v, _z);
  if (foo->evaluateII[uwx]) TVIL_SetParamsI (&(_II[uwx]), uwx, _u, _w, _x);
  if (foo->evaluateII[uyz]) TVIL_SetParamsI (&(_II[uyz]), uyz, _u, _y, _z);
  if (foo->evaluateII[wxz]) TVIL_SetParamsI (&(_II[wxz]), wxz, _w, _x, _z);
  if (foo->evaluateII[uvy]) TVIL_SetParamsI (&(_II[uvy]), uvy, _u, _v, _y);
  if (foo->evaluateII[vwx]) TVIL_SetParamsI (&(_II[vwx]), vwx, _v, _w, _x);

  if (foo->evaluateFBAR[wuxy]) TVIL_SetParamsFBAR (&(_FBAR[wuxy]), wuxy, _w, _u, _x, _y);
  if (foo->evaluateFBAR[wvxz]) TVIL_SetParamsFBAR (&(_FBAR[wvxz]), wvxz, _w, _v, _x, _z);
  if (foo->evaluateFBAR[xuwy]) TVIL_SetParamsFBAR (&(_FBAR[xuwy]), xuwy, _x, _u, _w, _y);
  if (foo->evaluateFBAR[xvwz]) TVIL_SetParamsFBAR (&(_FBAR[xvwz]), xvwz, _x, _v, _w, _z);
  if (foo->evaluateFBAR[uvyz]) TVIL_SetParamsFBAR (&(_FBAR[uvyz]), uvyz, _u, _v, _y, _z);
  if (foo->evaluateFBAR[uwxy]) TVIL_SetParamsFBAR (&(_FBAR[uwxy]), uwxy, _u, _w, _x, _y);
  if (foo->evaluateFBAR[yuvz]) TVIL_SetParamsFBAR (&(_FBAR[yuvz]), yuvz, _y, _u, _v, _z);
  if (foo->evaluateFBAR[yuwx]) TVIL_SetParamsFBAR (&(_FBAR[yuwx]), yuwx, _y, _u, _w, _x);
  if (foo->evaluateFBAR[vuyz]) TVIL_SetParamsFBAR (&(_FBAR[vuyz]), vuyz, _v, _u, _y, _z);
  if (foo->evaluateFBAR[vwxz]) TVIL_SetParamsFBAR (&(_FBAR[vwxz]), vwxz, _v, _w, _x, _z);
  if (foo->evaluateFBAR[zuvy]) TVIL_SetParamsFBAR (&(_FBAR[zuvy]), zuvy, _z, _u, _v, _y);
  if (foo->evaluateFBAR[zvwx]) TVIL_SetParamsFBAR (&(_FBAR[zvwx]), zvwx, _z, _v, _w, _x);

  if (foo->evaluateE[Ewuxy]) TVIL_SetParamsE (&(_E[Ewuxy]), Ewuxy, _w, _u, _x, _y);
  if (foo->evaluateE[Evwxz]) TVIL_SetParamsE (&(_E[Evwxz]), Evwxz, _v, _w, _x, _z);
  if (foo->evaluateE[Euvyz]) TVIL_SetParamsE (&(_E[Euvyz]), Euvyz, _u, _v, _y, _z);

  if (foo->evaluateG[wuzvy]) TVIL_SetParamsG (&(_G[wuzvy]), wuzvy, _w, _u, _z, _v, _y);
  if (foo->evaluateG[xuvyz]) TVIL_SetParamsG (&(_G[xuvyz]), xuvyz, _x, _u, _v, _y, _z);
  if (foo->evaluateG[uvxwz]) TVIL_SetParamsG (&(_G[uvxwz]), uvxwz, _u, _v, _x, _w, _z);
  if (foo->evaluateG[yvwxz]) TVIL_SetParamsG (&(_G[yvwxz]), yvwxz, _y, _v, _w, _x, _z);
  if (foo->evaluateG[vuxwy]) TVIL_SetParamsG (&(_G[vuxwy]), vuxwy, _v, _u, _x, _w, _y);
  if (foo->evaluateG[zuwxy]) TVIL_SetParamsG (&(_G[zuwxy]), zuwxy, _z, _u, _w, _x, _y);

  if (foo->evaluateH) TVIL_SetParamsH (&_H, _u, _v, _w, _x, _y, _z);

  return;
}

/* ******************************************************************* */
/* A quick way to set evaluation of all functions (or none). yesOrNo
   should be YES or NO, natch. */

void TVIL_EvaluateAllFunctions (TVIL_RESULT *foo, int yesOrNo)
{
  int i;

  if (yesOrNo == NO) {
    foo->nIfuns = foo->nFBARfuns = foo->nEfuns = foo->nGfuns = foo->nHfuns = 0;
  }
  else {
    foo->nIfuns = NUM_I_FUNCS;
    foo->nFBARfuns = NUM_F_FUNCS;
    foo->nEfuns = NUM_E_FUNCS;
    foo->nGfuns = NUM_G_FUNCS;
    foo->nHfuns = 1;
  }

  for (i=0; i<NUM_I_FUNCS; i++)
    foo->evaluateII[i] = yesOrNo;

  for (i=0; i<NUM_F_FUNCS; i++)
    foo->evaluateFBAR[i] = yesOrNo;

  for (i=0; i<NUM_E_FUNCS; i++)
    foo->evaluateE[i] = yesOrNo;

  for (i=0; i<NUM_G_FUNCS; i++)
    foo->evaluateG[i] = yesOrNo;

  foo->evaluateH = yesOrNo;

  return;
}

/* ******************************************************************* */
/* A quick way to set integration of all functions (or none). yesOrNo
   should be YES or NO. */

void TVIL_IntegrateAllFunctions (TVIL_RESULT *foo, int yesOrNo)
{
  int i;

  if (yesOrNo == NO) {

    for (i=0; i<NUM_I_FUNCS; i++)
      _integrateII[i] = NO;

    for (i=0; i<NUM_F_FUNCS; i++)
      _integrateFBAR[i] = NO;

    for (i=0; i<NUM_E_FUNCS; i++)
      _integrateE[i] = NO;

    for (i=0; i<NUM_G_FUNCS; i++)
      _integrateG[i] = NO;

    _integrateH = NO;
  }
  else {
    for (i=0; i<NUM_I_FUNCS; i++)
      _integrateII[i] = foo->evaluateII[i];

    for (i=0; i<NUM_F_FUNCS; i++)
      _integrateFBAR[i] = foo->evaluateFBAR[i];

    for (i=0; i<NUM_E_FUNCS; i++)
      _integrateE[i] = foo->evaluateE[i];

    for (i=0; i<NUM_G_FUNCS; i++)
      _integrateG[i] = foo->evaluateG[i];

    _integrateH = foo->evaluateH;
  }

  return;
}

/* ******************************************************************* */
/* Sets the global integration variables. */

void TVIL_SetGlobalVars (TVIL_COMPLEX tt)
{
  if (_evalMode == ALL ||
      _evalMode == EFG ||
      _evalMode == EF) {
    _Ug = _a + tt*(_u - _a);
    _Vg = _a + tt*(_v - _a);
    _Wg = _a + tt*(_w - _a);
    _Xg = _a + tt*(_x - _a);
    _Yg = _a + tt*(_y - _a);
    _Zg = _a + tt*(_z - _a);

    _lnbarUg = TVIL_CLOG (_Ug/_qq);
    _lnbarVg = TVIL_CLOG (_Vg/_qq);
    _lnbarWg = TVIL_CLOG (_Wg/_qq);
    _lnbarXg = TVIL_CLOG (_Xg/_qq);
    _lnbarYg = TVIL_CLOG (_Yg/_qq);
    _lnbarZg = TVIL_CLOG (_Zg/_qq);
  }
  else {
    _Zg = tt;
    _lnbarZg = TVIL_CLOG (_Zg/_qq);
  }

  return;
}

/* ******************************************************************* */
/* This was Delta in TSIL... */

TVIL_REAL TVIL_Lambda (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z)
{
  return x*x + y*y + z*z - 2.0L*x*y - 2.0L*x*z - 2.0L*y*z;
}

/* ******************************************************************* */

TVIL_REAL TVIL_Kappa (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z)
{
  return x*x + y*y + z*z - x*y - x*z - y*z;
}

/* ******************************************************************* */

TVIL_REAL TVIL_Delta (TVIL_REAL w, 
		      TVIL_REAL x,
		      TVIL_REAL y,
		      TVIL_REAL z)
{
  return TVIL_Lambda(x,y,z) + 2.L*w*(x + y + z) - 3*w*w;
}

/* ******************************************************************* */

int TVIL_TestDelta (TVIL_REAL w,
                    TVIL_REAL x,
                    TVIL_REAL y,
                    TVIL_REAL z)
{
  int result = 0;

  if ( (TVIL_FABS(TVIL_Delta(w,x,y,z)/(w*w + x*x + y*y + z*z + 1e-99)) < 
        TVIL_TOL) ||
       ((TVIL_FABS((w-x)/(w+x + 1e-99)) < TVIL_TOL) && 
        (TVIL_FABS((y-z)/(y+z + 1e-99)) < TVIL_TOL)) ||        
       ((TVIL_FABS((w-y)/(w+y + 1e-99)) < TVIL_TOL) && 
        (TVIL_FABS((x-z)/(x+z + 1e-99)) < TVIL_TOL)) ||        
       ((TVIL_FABS((w-z)/(w+z + 1e-99)) < TVIL_TOL) && 
        (TVIL_FABS((x-y)/(x+y + 1e-99)) < TVIL_TOL)) ) result = 1;

  return result; 
}

/* ******************************************************************* */
TVIL_REAL TVIL_Phi (TVIL_REAL w, 
		    TVIL_REAL x,
		    TVIL_REAL y,
		    TVIL_REAL z)
{
  TVIL_REAL W, X, Y, Z, temp;
  TVIL_REAL WmX, YmZ, XmZ;

  W = w; X = x; Y = y; Z = z;
  /* Sort to ensure that W < X < Y < Z, using 5 swaps. Helps to avoid 
     roundoff error in pathological cases when W-X and Y-Z are very small. */
  if (W > X) {temp = W; W = X; X = temp;} 
  if (Y > Z) {temp = Y; Y = Z; Z = temp;} 
  if (W > Y) {temp = W; W = Y; Y = temp;} 
  if (X > Z) {temp = X; X = Z; Z = temp;} 
  if (X > Y) {temp = X; X = Y; Y = temp;} 

  WmX = W-X;
  YmZ = Y-Z;
  XmZ = X-Z;
  temp = (WmX - YmZ) * (WmX - YmZ) - 4*XmZ*YmZ;

  return (temp * temp + 
    8 * (_a - Z) * (WmX - YmZ) * (WmX + 2 * XmZ - YmZ) * (WmX + YmZ));
}
/* ******************************************************************* */

TVIL_REAL TVIL_Rplus (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z)
{
  return (-3*_a*_a + _a*(x + y + z) +
	  2*_a*TVIL_SQRT(TVIL_FABS(TVIL_Kappa(x,y,z))))/TVIL_Lambda(_a-x,_a-y,_a-z);
}

/* ******************************************************************* */

TVIL_REAL TVIL_Rminus (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z)
{
  return (-3*_a*_a + _a*(x + y + z) -
	  2*_a*TVIL_SQRT(TVIL_FABS(TVIL_Kappa(x,y,z))))/TVIL_Lambda(_a-x,_a-y,_a-z);
}

/* ******************************************************************* */

TVIL_REAL TVIL_R4 (TVIL_REAL w, 
		   TVIL_REAL x,
		   TVIL_REAL y,
		   TVIL_REAL z)
{
  if (1 == TVIL_TestDelta(w,x,y,z)) 
    return _a/(_a - w);
  else
    return 8*_a*(w + x - y - z)*(w - x + y - z)*(w - x - y + z)/TVIL_Phi(w,x,y,z);
}

/* ******************************************************************* */

int TVIL_Compare (const void * a, const void * b)
{
    TVIL_REAL f = *((TVIL_REAL *)a);
    TVIL_REAL s = *((TVIL_REAL *)b);

    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

/* ******************************************************************* */
/* Returns true/false indicating if z is TVIL_Infinity                 */
/* Requires that compiler implement the C99 standard.                  */

int TVIL_IsInfinite (TVIL_COMPLEX z)
{
  return (isinf(TVIL_CREAL(z)) || isinf(TVIL_CIMAG(z)) ||
	  isnan(TVIL_CREAL(z)) || isnan(TVIL_CIMAG(z)));
}

/* ******************************************************************* */

int TVIL_NonZero (TVIL_REAL x)
{
  if (TVIL_FABS (x) > TVIL_TOL)
    return TRUE;
  else
    return FALSE;
}

/* ******************************************************************* */

int TVIL_Sign (TVIL_REAL x)
{
  if (x > TVIL_TOL)
    return +1;
  else if (x < TVIL_TOL)
    return -1;
  else
    return 0;
}

/* ******************************************************************* */

void TVIL_Warn (const char *func, const char *msg)
{
  if (_print3VILWarns == YES) {
    fprintf (stderr, "WARNING (%s): %s\n", func, msg);
    fflush (stderr);
  }
  return;
}

/* ******************************************************************* */
/* Prints error message, stack trace, and exits. */

#include <execinfo.h>

void TVIL_Error (const char *func, const char *msg, int val)
{
  void *callstack[128];
  int i, frames = backtrace(callstack, 128);
  char **strs = backtrace_symbols(callstack, frames);

  fprintf (stderr, "ERROR (%s): %s\n", func, msg);

  for (i=0; i<frames; i++)
    fprintf(stderr, "%s\n", strs[i]);

  fflush (stderr);
  exit (val);
}

/* ******************************************************************* */

void TVIL_Set_aParameter (TVIL_REAL newval)
{
  _aParameter = newval;
  return;
}

/* ******************************************************************* */

void TVIL_SetContourDisplacement (TVIL_REAL d)
{
  _imDispl = d;
  return;
}

/* ******************************************************************* */

void TVIL_Set_tInitial (TVIL_REAL newval)
{
  _tInit = newval;
  return;
}

/* ******************************************************************* */

void TVIL_SetDoAnalytic (void)
{
  _doAnalytic = YES;
  return;
}

/* ******************************************************************* */

void TVIL_UnsetDoAnalytic (void)
{
  _doAnalytic = NO;
  return;
}

/* ******************************************************************* */

void TVIL_SetForceContour (void)
{
  _forceContour = YES;
  return;
}

/* ******************************************************************* */

void TVIL_UnsetForceContour (void)
{
  _forceContour = NO;
  return;
}

/* ******************************************************************* */

void TVIL_SetForceDefault (void)
{
  _forceDefault = YES;
  return;
}

/* ******************************************************************* */

void TVIL_UnsetForceDefault (void)
{
  _forceDefault = NO;
  return;
}

/* ******************************************************************* */

void TVIL_SetPrintStyle (int style)
{
  if (style < 0 || style > 1)
    TVIL_Warn ("PrintStyle", "Invalid style selection.");
  else 
    _printStyle = style;

  return;
}

/* ******************************************************************* */

void TVIL_WarnsOn (void)
{
  _print3VILWarns = YES;
  return;
}

/* ******************************************************************* */

void TVIL_WarnsOff (void)
{
  _print3VILWarns = NO;
  return;
}

/* ******************************************************************* */

void TVIL_SetPrintBold (void)
{
  _printBold = YES;
  return;
}

/* ******************************************************************* */

void TVIL_UnsetPrintBold (void)
{
  _printBold = NO;
  return;
}

/* **************************************************************** */

void TVIL_ResetStepSizeParams (TVIL_REAL precisionGoal,
                               int nstepsStart,
                               int nstepsMaxCon,
                               int nstepsMaxVar,
                               int nstepsMin)
{
  _precisionGoal = precisionGoal;
  _nStepsStart   = nstepsStart;
  _nStepsMaxCon  = nstepsMaxCon;
  _nStepsMaxVar  = nstepsMaxVar;
  _nStepsMin     = nstepsMin;

  return;
}

/* **************************************************************** */

void TVIL_ResetStepSizeParamDefaults (void)
{
  _precisionGoal = TVIL_PRECISION_GOAL;
  _nStepsStart   = TVIL_NSTEPS_START;
  _nStepsMaxCon  = TVIL_NSTEPS_MAX_CON;
  _nStepsMaxVar  = TVIL_NSTEPS_MAX_VAR;
  _nStepsMin     = TVIL_NSTEPS_MIN;

  return;
}

/* ******************************************************************* */
/* Returns 1 (TRUE) if there is a pole within minDistance of 1.0, and
  sets *npole to the pole value nearest to 1.0.  Returns 0 (FALSE) if
  we are further away than minDistance from all poles. */

int TVIL_NearPole (TVIL_REAL *nearestPole,
		   TVIL_REAL  minDistance)
{
  TVIL_REAL distance;
  int i;
  int areWeCloseToAPole = NO;

  *nearestPole = 0.0L; /* This should be ignored if it survives. */

  for (i=0; i<_nPoles; i++) {
    distance = TVIL_FABS(1.0L - _tPole[i]);
    if (distance < minDistance) {
      minDistance = distance;
      *nearestPole = _tPole[i];
      areWeCloseToAPole = YES;
    }
  }
  return areWeCloseToAPole;
}

/* **************************************************************** */
/* For internal use; this saves the current functions and their
   derivatives to a TVIL_RESULT so that integration can be restarted
   from this point if desired. */

void TVIL_Backup (TVIL_RESULT *r)
{
  int i;

  r->u = _u;
  r->v = _v;
  r->w = _w;
  r->x = _x;
  r->y = _y;
  r->z = _z;

  for (i=0; i<NUM_I_FUNCS; i++)
    r->II[i] = _II[i].value;
  for (i=0; i<NUM_F_FUNCS; i++)
    r->FBAR[i] = _FBAR[i].value;
  for (i=0; i<NUM_G_FUNCS; i++)
    r->G[i] = _G[i].value;
  r->H = _H.value;

  /* These are needed for testing: */
  for (i=0; i<NUM_E_FUNCS; i++)
    r->E[i] = _E[i].value;
  for (i=0; i<NUM_F_FUNCS; i++)
    r->F[i] = _FBAR[i].fValue;

  for (i=0; i<NUM_I_FUNCS; i++)
    r->IIderiv[i] = _II[i].deriv;
  for (i=0; i<NUM_F_FUNCS; i++)
    r->FBARderiv[i] = _FBAR[i].deriv;
  for (i=0; i<NUM_G_FUNCS; i++)
    r->Gderiv[i] = _G[i].deriv;
  r->Hderiv = _H.deriv;

  return;
}

/* **************************************************************** */

void TVIL_Restore (TVIL_RESULT *r)
{
  int i;

  _u = r->u;
  _v = r->v;
  _w = r->w;
  _x = r->x;
  _y = r->y;
  _z = r->z;

  for (i=0; i<NUM_I_FUNCS; i++)
    _II[i].value = r->II[i];
  for (i=0; i<NUM_F_FUNCS; i++)
    _FBAR[i].value = r->FBAR[i];
  for (i=0; i<NUM_G_FUNCS; i++)
    _G[i].value = r->G[i];
  _H.value = r->H;

  /* These are needed for testing: */
  for (i=0; i<NUM_E_FUNCS; i++)
    _E[i].value = r->E[i];
  for (i=0; i<NUM_F_FUNCS; i++)
    _FBAR[i].fValue = r->F[i];

  for (i=0; i<NUM_I_FUNCS; i++)
    _II[i].deriv = r->IIderiv[i];
  for (i=0; i<NUM_F_FUNCS; i++)
    _FBAR[i].deriv = r->FBARderiv[i];
  for (i=0; i<NUM_G_FUNCS; i++)
    _G[i].deriv = r->Gderiv[i];
  _H.deriv = r->Hderiv;

  return;
}

/* ******************************************************************* */
/* Check to see if a string represents a floating-point value. */

int TVIL_IsNumeric (const char * s)
{
  if (s == NULL || *s == '\0' || isspace(*s))
    return 0;
  char *p;
  strtod (s, &p);
  return *p == '\0';
}

/* ******************************************************************* */
/* Check input function identifier for sanity */

int TVIL_ValidIdentifier (const char* which)
{ 
#include "3vil_names.h"

  int i,j;

  if (!strncmp(which, "H", 1)) return YES;

  for (i=0; i<NUM_G_FUNCS; i++)
    for (j=0; j<NUM_G_PERMS; j++)
      if (!strcmp(which, gname[i][j])) return YES;

  for (i=0; i<NUM_F_FUNCS; i++)
    for (j=0; j<NUM_F_PERMS; j++)
      if (!strcmp(which, fname[i][j])) return YES;

  for (i=0; i<NUM_F_FUNCS; i++)
    for (j=0; j<NUM_F_PERMS; j++)
      if (!strcmp(which, fbarname[i][j])) return YES;

  for (i=0; i<NUM_E_FUNCS; i++)
    for (j=0; j<NUM_E_PERMS; j++)
      if (!strcmp(which, ename[i][j])) return YES;

  for (i=0; i<NUM_I_FUNCS; i++)
    for (j=0; j<NUM_I_PERMS; j++)
      if (!strcmp(which, iname[i][j])) return YES;

  /* If we get here the identifier is invalid: */
  return NO;
}

/* **************************************************************** */

TVIL_COMPLEX TVIL_ReturnValue (const char *which, TVIL_COMPLEX res)
{
  char funcname[] = "TVIL_ReturnValue";
  char errmsg[55] = "Function not defined for these parameters: ";

  if (TVIL_IsInfinite (res))
    TVIL_Warn (funcname, strncat (errmsg, which, 7));

  return res;
}

/* **************************************************************** */
/* Extract a single function value from the data object             */

TVIL_COMPLEX TVIL_GetFunction (TVIL_RESULT *foo, const char *which)
{
#include "3vil_names.h"

  int i,j;

  char funcname[] = "TVIL_GetFunction";
  char errmsg[55] = "Function not defined for these parameters: ";
  char errmsg2[60] = "This function not part of evaluation subset: ";

  if (!TVIL_ValidIdentifier (which))
    TVIL_Error (funcname, "Invalid function identifier specified.", 23);

  if (foo->status == UNEVALUATED)
    TVIL_Error (funcname, "This case has not yet been evaluated!", 22);

  if (!strncmp(which, "H", 1)) {
    if (foo->evaluateH)
      return TVIL_ReturnValue (which, foo->H);
  }
  else if (!strncmp(which, "G", 1)) {
    for (i=0; i<NUM_G_FUNCS; i++) 
      if (foo->evaluateG[i]) {
	for (j=0; j<NUM_G_PERMS; j++)
	  if (!strcmp(which, gname[i][j]))
	    return TVIL_ReturnValue (which, foo->G[i]);
      }
  }
  else if (!strncmp(which, "FBAR", 4)) {
    for (i=0; i<NUM_F_FUNCS; i++)
      if (foo->evaluateFBAR[i]) {
	for (j=0; j<NUM_F_PERMS; j++)
	  if (!strcmp(which, fbarname[i][j]))
	    return TVIL_ReturnValue (which, foo->FBAR[i]);
      }
  }
  else if (!strncmp(which, "F", 1)) {
    for (i=0; i<NUM_F_FUNCS; i++)
      if (foo->evaluateFBAR[i]) {
	for (j=0; j<NUM_F_PERMS; j++)
	  if (!strcmp(which, fname[i][j]))
	    return TVIL_ReturnValue (which, foo->F[i]);
      }
  }
  else if (!strncmp(which, "E", 1)) {
    for (i=0; i<NUM_E_FUNCS; i++)
      if (foo->evaluateE[i]) {
	for (j=0; j<NUM_E_PERMS; j++) 
	  if (!strcmp(which, ename[i][j]))
	    return TVIL_ReturnValue (which, foo->E[i]);
      }
  }
  else if (!strncmp(which, "I", 1)) {
    for (i=0; i<NUM_I_FUNCS; i++)
      if (foo->evaluateII[i]) {
	for (j=0; j<NUM_I_PERMS; j++)
	  if (!strcmp(which, iname[i][j]))
	    return TVIL_ReturnValue (which, foo->II[i]);
      }
  }
  else {
    /* Should never get here, but... */
    TVIL_Error (funcname, "Invalid identifier specified.", 1);
  }

  /* If we get *here* the specifier was valid but no match was found,
     so this must be a function that is not part of the set being
     evaluated. */
  TVIL_Error (funcname, strncat (errmsg2, which, 8), 88);

  /* Can never reach here, but avoids compiler warning. */
  return 666; 
}

/* **************************************************************** */
/* Extract a single function value from the data object             */

TVIL_COMPLEX TVIL_GetBoldFunction (TVIL_RESULT *foo,
				   const char *which,
				   int n)
{
#include "3vil_names.h"

  int i,j;

  /* TVIL_COMPLEX result = (TVIL_COMPLEX) 0.0; */
  char funcname[] = "TVIL_GetBoldFunction";
  char errmsg[65] = "Function not defined for these parameters: ";
  char errmsg2[75] = "This function not evaluated, or bold version not defined: ";

  if (!TVIL_ValidIdentifier (which))
    TVIL_Error (funcname, "Invalid function identifier specified.", 23);

  if (foo->status == UNEVALUATED)
    TVIL_Error (funcname, "This case has not yet been evaluated!", 22);

  if (!strncmp(which, "H", 1)) {
    if (n < 0 || n > 1)
      TVIL_Error (funcname, "Invalid pole specification for bold H.", 24);
    if (foo->evaluateH)
      return TVIL_ReturnValue (which, foo->Hbold[n]);
  }
  else if (!strncmp(which, "G", 1)) {
    if (n < 0 || n > 3)
      TVIL_Error (funcname, "Invalid pole specification for bold G.", 24);

    for (i=0; i<NUM_G_FUNCS; i++)
      if (foo->evaluateG[i]) {
	for (j=0; j<NUM_G_PERMS; j++)
	  if (!strcmp(which, gname[i][j])) {
	    /* DGR figure this out later... */
	    /* if (foo->gfun[i]->hasNegativeArg && n == 0) */
	    /*   TVIL_Warn (funcname, */
	    /* 		 "eps^0 term in bold G not yet implemented for negative argument(s)! Do not use this value."); */
	    return TVIL_ReturnValue (which, foo->Gbold[i][n]);
	  }
      }
  }
  else if (!strncmp(which, "F", 1)) {
    if (n < 0 || n > 3)
      TVIL_Error (funcname, "Invalid pole specification for bold F.", 24);

    for (i=0; i<NUM_F_FUNCS; i++)
      if (foo->evaluateFBAR[i]) {
	for (j=0; j<NUM_F_PERMS; j++)
	  if (!strcmp(which, fname[i][j]))
	    return TVIL_ReturnValue (which, foo->Fbold[i][n]);
      }
  }
  else if (!strncmp(which, "E", 1)) {
    if (n < 0 || n > 3)
      TVIL_Error (funcname, "Invalid pole specification for bold E.", 24);

    for (i=0; i<NUM_E_FUNCS; i++)
      if (foo->evaluateE[i]) {
	for (j=0; j<NUM_E_PERMS; j++)
	  if (!strcmp(which, ename[i][j]))
	    return TVIL_ReturnValue (which, foo->Ebold[i][n]);
      }
  }
  else if (!strncmp(which, "I", 1)) {
    if (n < 0 || n > 2)
      TVIL_Error (funcname, "Invalid pole specification for bold I.", 24);

    for (i=0; i<NUM_I_FUNCS; i++)
      if (foo->evaluateII[i]) {
  	for (j=0; j<NUM_I_PERMS; j++)
  	  if (!strcmp(which, iname[i][j])) 
	    return TVIL_ReturnValue (which, foo->IIbold[i][n]);
      }
  }
  else {
    /* Should never get here, but... */
    TVIL_Error (funcname, "Invalid identifier specified.", 1);
  }

  /* If we get *here* the specifier was valid but no match was found,
     so this must be a function that is not part of the set being
     evaluated. */
  TVIL_Error (funcname, strncat (errmsg2, which, 8), 88);

  /* Can never reach here, but avoids compiler warning. */
  return 666; 
}

/* **************************************************************** */
