/*
#define VERBOSE 1
#define VERBOSE (TVIL_CABS(t-1) < 0.001L)
*/
#define VERBOSE 0

#define MAX_ALLOWED_ERR 1e6

/* ****************************************************************
   TVIL_rk6
   ========

   Implements a 6-stage, 5th-order Cash-Karp-Fehlberg Runge-Kutta
   step.  The purpose of this (as opposed to classical 4-stage
   4th-order Runge-Kutta) is to enable efficient adaptive step size
   control.

   The criterion for deciding whether the step size is small enough is
   presently:

   |(5th order change) - (4th order embedded change)|
   < (precision_goal)*|5th order change|

   This is required for all dependent variables, unless the left-hand
   side is less than TVIL_TOL times the magnitude of the variable.
   Otherwise, the step is rejected, unless force_step == 1.

   Provided it finds the step size to be small enough, OR the argument
   force_step==1, then TVIL_rk6 will return 1 and *RKindvar=t is
   incremented by an amount *RKdelta.

   The dependent variables and their derivatives are also
   updated in preparation for the next step.

   If the step size needs to be decreased, then TVIL_rk6 will return
   0, and not increment the independent variable and not change the
   dependent variables or their derivatives.

   TVIL_rk6 also replaces *RKdelta with an estimate of the optimal
   step size, regardless of whether that is going to be a retry of
   this step if it failed, or the next step if this one passed. But,
   it never tries to increase or decrease the step size by more than a
   factor of 2. And, the calling function TVIL_Integrate() can and
   will reject the suggested step size if it gets to be too small or
   too large.

   ******************************************************************** */

#include "internal.h"

#define SafetyFactor 0.9L
#define TVIL_TINY    TVIL_TOL
#define TVIL_DIMLESS 1e-5
#define err_goal     0.01L*precision_goal /* This can be adjusted. */

/* Here are the Butcher coefficients for Cash-Karp-Fehlberg:*/

/* Confusingly, these are Numerical Recipes a_i */
#define ButchCKFc2 0.2L
#define ButchCKFc3 0.3L
#define ButchCKFc4 0.6L
#define ButchCKFc5 1.0L
#define ButchCKFc6 0.875L

/* Confusingly, these are Numerical Recipes b_ij */
#define ButchCKFa21 0.2L
#define ButchCKFa31 0.075L
#define ButchCKFa32 0.225L
#define ButchCKFa41 0.3L
#define ButchCKFa42 -0.9L
#define ButchCKFa43 1.2L
#define ButchCKFa51 -0.203703703703703703703703703704L
#define ButchCKFa52 2.5L
#define ButchCKFa53 -2.59259259259259259259259259259L
#define ButchCKFa54 1.29629629629629629629629629630L
#define ButchCKFa61 0.0294958043981481481481481481481L
#define ButchCKFa62 0.341796875L
#define ButchCKFa63 0.0415943287037037037037037037037L
#define ButchCKFa64 0.400345413773148148148148148148L
#define ButchCKFa65 0.061767578125L

/* Confusingly, these are Numerical Recipes c_i */
#define ButchCKFb1 0.0978835978835978835978835978836L
#define ButchCKFb2 0.0L
#define ButchCKFb3 0.402576489533011272141706924316L 
#define ButchCKFb4 0.210437710437710437710437710438L
#define ButchCKFb5 0.0L
#define ButchCKFb6 0.289102202145680406549971767363L

/* These are Numerical Recipes c_i - c_i^* */
#define ButchCKFe1 -0.00429377480158730158730158730159L
#define ButchCKFe2 0.0L 
#define ButchCKFe3 0.0186685860938578329882677708765L 
#define ButchCKFe4 -0.0341550268308080808080808080808L 
#define ButchCKFe5 -0.0193219866071428571428571428571L 
#define ButchCKFe6 0.0391022021456804065499717673631L 

/* **************************************************************** */
/* NEW VERSION */

int TVIL_rk6 (int           nData,
	      TVIL_COMPLEX *RKindvar,
	      TVIL_COMPLEX *RKdelta,
	      TVIL_REAL     precision_goal,
	      int           force_step)
{
  char funcname[] = "TVIL_rk6";

  static TVIL_COMPLEX startingI[NUM_I_FUNCS];
  TVIL_COMPLEX k1I[NUM_I_FUNCS], k2I[NUM_I_FUNCS], k3I[NUM_I_FUNCS],
               k4I[NUM_I_FUNCS], k5I[NUM_I_FUNCS], k6I[NUM_I_FUNCS];
  TVIL_COMPLEX deltaI[NUM_I_FUNCS];
  TVIL_REAL    errorI[NUM_I_FUNCS];
  TVIL_REAL    sumargsI[NUM_I_FUNCS];

  static TVIL_COMPLEX startingFBAR[NUM_F_FUNCS];
  TVIL_COMPLEX k1FBAR[NUM_F_FUNCS], k2FBAR[NUM_F_FUNCS], k3FBAR[NUM_F_FUNCS],
               k4FBAR[NUM_F_FUNCS], k5FBAR[NUM_F_FUNCS], k6FBAR[NUM_F_FUNCS];
  TVIL_COMPLEX deltaFBAR[NUM_F_FUNCS];
  TVIL_REAL    errorFBAR[NUM_F_FUNCS];
  TVIL_REAL    sumargsFBAR[NUM_F_FUNCS];

  static TVIL_COMPLEX startingG[NUM_G_FUNCS];
  TVIL_COMPLEX k1G[NUM_G_FUNCS], k2G[NUM_G_FUNCS], k3G[NUM_G_FUNCS],
               k4G[NUM_G_FUNCS], k5G[NUM_G_FUNCS], k6G[NUM_G_FUNCS];
  TVIL_COMPLEX deltaG[NUM_G_FUNCS];
  TVIL_REAL    errorG[NUM_G_FUNCS];
  TVIL_REAL    sumargsG[NUM_G_FUNCS];

  static TVIL_COMPLEX startingH;
  TVIL_COMPLEX k1H, k2H, k3H,
               k4H, k5H, k6H;
  TVIL_COMPLEX deltaH;
  TVIL_REAL    errorH;

  int i;
  TVIL_COMPLEX t, dt;
  TVIL_COMPLEX next_step_size;
  TVIL_REAL temp; 
  TVIL_REAL step_rescale = 0.19L; /* This can only increase. */
  int status = 0;

  /* Relate t, dt to the independent variable. */
  t = *RKindvar;
  dt = *RKdelta;

  for (i=0; i<_nIfuns; i++) {

      startingI[i] = (_ifun[i])->value;
      sumargsI[i] = _a +
	TVIL_CABS(_a + t * (-_a + ((_ifun[i])->arg[0]))) +
	TVIL_CABS(_a + t * (-_a + ((_ifun[i])->arg[1]))) +
	TVIL_CABS(_a + t * (-_a + ((_ifun[i])->arg[2])));
  }
  for (i=0; i<_nFBARfuns; i++) {

    startingFBAR[i] = (_fbarfun[i])->value;
      sumargsFBAR[i] = _a +
	TVIL_CABS(_a + t * (-_a + ((_fbarfun[i])->arg[0]))) +
	TVIL_CABS(_a + t * (-_a + ((_fbarfun[i])->arg[1]))) +
	TVIL_CABS(_a + t * (-_a + ((_fbarfun[i])->arg[2]))) +
	TVIL_CABS(_a + t * (-_a + ((_fbarfun[i])->arg[3])));
  }
  for (i=0; i<_nGfuns; i++) {

      startingG[i] = (_gfun[i])->value;
      sumargsG[i] = _a +
	TVIL_CABS(_a + t * (-_a + ((_gfun[i])->arg[0]))) +
	TVIL_CABS(_a + t * (-_a + ((_gfun[i])->arg[1]))) +
	TVIL_CABS(_a + t * (-_a + ((_gfun[i])->arg[2]))) +
	TVIL_CABS(_a + t * (-_a + ((_gfun[i])->arg[3]))) +
	TVIL_CABS(_a + t * (-_a + ((_gfun[i])->arg[4])));
  }

  if (_nHfuns)
    startingH = (_hfun)->value;

  /* Fill up k1 arrays using existing values for derivatives: */
  for (i=0; i<_nIfuns; i++)
    k1I[i] = dt * ((_ifun[i])->deriv);

  for (i=0; i<_nFBARfuns; i++)
    k1FBAR[i] = dt * ((_fbarfun[i])->deriv);

  for (i=0; i<_nGfuns; i++)
    k1G[i] = dt * ((_gfun[i])->deriv);

  if (_nHfuns)
    k1H = dt * ((_hfun)->deriv);

  /* BEGIN STAGE 2. */

  /* Update t, dt */
  t = *RKindvar + ButchCKFc2 * (*RKdelta);

  /* Adjust data values */
  for (i=0; i<_nIfuns; i++)
    (_ifun[i])->value = startingI[i] + ButchCKFa21 * k1I[i];

  for (i=0; i<_nFBARfuns; i++)
    (_fbarfun[i])->value = startingFBAR[i] + ButchCKFa21 * k1FBAR[i];

  for (i=0; i<_nGfuns; i++)
    (_gfun[i])->value = startingG[i] + ButchCKFa21 * k1G[i];

  if (_nHfuns)
    (_hfun)->value = startingH + ButchCKFa21 * k1H;

  TVIL_SetGlobalVars (t);

  /* Fill up k2 arrays: */
  for (i=0; i<_nIfuns; i++)
    k2I[i] = (_Iderivative) (_ifun[i], t, _qq) * dt;

  for (i=0; i<_nFBARfuns; i++)
    k2FBAR[i] = (_FBARderivative) (_fbarfun[i], t, _qq) * dt;

  for (i=0; i<_nGfuns; i++)
    k2G[i] = dt * (_Gderivative) (_gfun[i], t, _qq);

  if (_nHfuns)
    k2H = dt * (_Hderivative) (_hfun, t, _qq);

  /* BEGIN STAGE 3. */

  /* Update independent variable. */
  t = *RKindvar + ButchCKFc3 * (*RKdelta);

  /* Adjust data values */
  for (i=0; i<_nIfuns; i++)
    (_ifun[i])->value = startingI[i] + ButchCKFa31 * k1I[i]
                                  + ButchCKFa32 * k2I[i];

  for (i=0; i<_nFBARfuns; i++)
    (_fbarfun[i])->value = startingFBAR[i] + ButchCKFa31 * k1FBAR[i]
                                     + ButchCKFa32 * k2FBAR[i];

  for (i=0; i<_nGfuns; i++)
    (_gfun[i])->value = startingG[i] + ButchCKFa31 * k1G[i]
                                  + ButchCKFa32 * k2G[i];

  if (_nHfuns)
    (_hfun)->value = startingH + ButchCKFa31 * k1H
                            + ButchCKFa32 * k2H;

  TVIL_SetGlobalVars (t);

  /* Fill up k3 arrays: */
  for (i=0; i<_nIfuns; i++)
    k3I[i] = dt * (_Iderivative) (_ifun[i], t, _qq);

  /* Iderivative ((_ifun[i]), t, _qq); */

  for (i=0; i<_nFBARfuns; i++)
    k3FBAR[i] = (_FBARderivative) (_fbarfun[i], t, _qq) * dt;

  for (i=0; i<_nGfuns; i++)
    k3G[i] = dt * (_Gderivative) (_gfun[i], t, _qq);

  if (_nHfuns)
    k3H = dt * (_Hderivative) (_hfun, t, _qq);

  /* BEGIN STAGE 4. */

  /* Update independent variable. */
  t = *RKindvar + ButchCKFc4 * (*RKdelta);

  /* Adjust data values */
  for (i=0; i<_nIfuns; i++)
    (_ifun[i])->value = startingI[i] + ButchCKFa41 * k1I[i]
                                  + ButchCKFa42 * k2I[i]
                                  + ButchCKFa43 * k3I[i];

  for (i=0; i<_nFBARfuns; i++)
    (_fbarfun[i])->value = startingFBAR[i] + ButchCKFa41 * k1FBAR[i]
                                     + ButchCKFa42 * k2FBAR[i]
                                     + ButchCKFa43 * k3FBAR[i];

  for (i=0; i<_nGfuns; i++)
    (_gfun[i])->value = startingG[i] + ButchCKFa41 * k1G[i]
                                  + ButchCKFa42 * k2G[i]
                                  + ButchCKFa43 * k3G[i];

  if (_nHfuns)
    (_hfun)->value = startingH + ButchCKFa41 * k1H
                            + ButchCKFa42 * k2H
                            + ButchCKFa43 * k3H;

  TVIL_SetGlobalVars (t);

  /* Fill up k4 arrays: */
  for (i=0; i<_nIfuns; i++)
    k4I[i] = dt * (_Iderivative) (_ifun[i], t, _qq);

  /* Iderivative ((_ifun[i]), t, _qq); */

  for (i=0; i<_nFBARfuns; i++)
    k4FBAR[i] = (_FBARderivative) (_fbarfun[i], t, _qq) * dt;

  for (i=0; i<_nGfuns; i++)
    k4G[i] = dt * (_Gderivative) (_gfun[i], t, _qq);

  if (_nHfuns)
    k4H = dt * (_Hderivative) (_hfun, t, _qq);

  /* BEGIN STAGE 5. */

  /* Update independent variable. */
  t = *RKindvar + ButchCKFc5 * (*RKdelta);

  /* Adjust data values */
  for (i=0; i<_nIfuns; i++)
    (_ifun[i])->value = startingI[i] + ButchCKFa51 * k1I[i]
                                  + ButchCKFa52 * k2I[i]
                                  + ButchCKFa53 * k3I[i]
                                  + ButchCKFa54 * k4I[i];

  for (i=0; i<_nFBARfuns; i++)
    (_fbarfun[i])->value = startingFBAR[i] + ButchCKFa51 * k1FBAR[i]
                                     + ButchCKFa52 * k2FBAR[i]
                                     + ButchCKFa53 * k3FBAR[i]
                                     + ButchCKFa54 * k4FBAR[i];

  for (i=0; i<_nGfuns; i++)
    (_gfun[i])->value = startingG[i] + ButchCKFa51 * k1G[i]
                                  + ButchCKFa52 * k2G[i]
                                  + ButchCKFa53 * k3G[i]
                                  + ButchCKFa54 * k4G[i];

  if (_nHfuns)
    (_hfun)->value = startingH + ButchCKFa51 * k1H
                            + ButchCKFa52 * k2H
                            + ButchCKFa53 * k3H
                            + ButchCKFa54 * k4H;

  TVIL_SetGlobalVars (t);

  /* Fill up k5 arrays: */
  for (i=0; i<_nIfuns; i++)
    k5I[i] = dt * (_Iderivative) (_ifun[i], t, _qq);

/* Iderivative ((_ifun[i]), t, _qq); */

  for (i=0; i<_nFBARfuns; i++)
    k5FBAR[i] = (_FBARderivative) (_fbarfun[i], t, _qq) * dt;

  for (i=0; i<_nGfuns; i++)
    k5G[i] = dt * (_Gderivative) (_gfun[i], t, _qq);

  if (_nHfuns)
    k5H = dt * (_Hderivative) (_hfun, t, _qq);

  /* BEGIN STAGE 6. */

  /* Update independent variable. */
  t = *RKindvar + ButchCKFc6 * (*RKdelta);

  /* Adjust data values */
  for (i=0; i<_nIfuns; i++)
    (_ifun[i])->value = startingI[i] + ButchCKFa61 * k1I[i]
                                  + ButchCKFa62 * k2I[i]
                                  + ButchCKFa63 * k3I[i]
                                  + ButchCKFa64 * k4I[i]
                                  + ButchCKFa65 * k5I[i];

  for (i=0; i<_nFBARfuns; i++)
    (_fbarfun[i])->value = startingFBAR[i] + ButchCKFa61 * k1FBAR[i]
                                     + ButchCKFa62 * k2FBAR[i]
                                     + ButchCKFa63 * k3FBAR[i]
                                     + ButchCKFa64 * k4FBAR[i]
                                     + ButchCKFa65 * k5FBAR[i];

  for (i=0; i<_nGfuns; i++)
    (_gfun[i])->value = startingG[i] + ButchCKFa61 * k1G[i]
                                  + ButchCKFa62 * k2G[i]
                                  + ButchCKFa63 * k3G[i]
                                  + ButchCKFa64 * k4G[i]
                                  + ButchCKFa65 * k5G[i];

  if (_nHfuns)
    (_hfun)->value = startingH + ButchCKFa61 * k1H
                            + ButchCKFa62 * k2H
                            + ButchCKFa63 * k3H
                            + ButchCKFa64 * k4H
                            + ButchCKFa65 * k5H;

  TVIL_SetGlobalVars (t);

  /* Fill up k6 arrays: */
  for (i=0; i<_nIfuns; i++)
    k6I[i] = dt * (_Iderivative) (_ifun[i], t, _qq);

/* Iderivative ((_ifun[i]), t, _qq); */

  for (i=0; i<_nFBARfuns; i++)
    k6FBAR[i] = (_FBARderivative) (_fbarfun[i], t, _qq) * dt;

  for (i=0; i<_nGfuns; i++)
    k6G[i] = dt * (_Gderivative) (_gfun[i], t, _qq);

  if (_nHfuns)
    k6H = dt * (_Hderivative) (_hfun, t, _qq);

  /* DONE WITH STAGES. */

  /* Compute 5th-order result changes in data values */
  for (i=0; i<_nIfuns; i++)
    deltaI[i] =   ButchCKFb1 * k1I[i] + ButchCKFb2 * k2I[i] 
                + ButchCKFb3 * k3I[i] + ButchCKFb4 * k4I[i] 
                + ButchCKFb5 * k5I[i] + ButchCKFb6 * k6I[i];

  for (i=0; i<_nFBARfuns; i++)
    deltaFBAR[i] =   ButchCKFb1 * k1FBAR[i] + ButchCKFb2 * k2FBAR[i]
                   + ButchCKFb3 * k3FBAR[i] + ButchCKFb4 * k4FBAR[i]
                   + ButchCKFb5 * k5FBAR[i] + ButchCKFb6 * k6FBAR[i];

  for (i=0; i<_nGfuns; i++)
    deltaG[i] =   ButchCKFb1 * k1G[i] + ButchCKFb2 * k2G[i]
                + ButchCKFb3 * k3G[i] + ButchCKFb4 * k4G[i]
                + ButchCKFb5 * k5G[i] + ButchCKFb6 * k6G[i];

  if (_nHfuns)
    deltaH =   ButchCKFb1 * k1H + ButchCKFb2 * k2H
             + ButchCKFb3 * k3H + ButchCKFb4 * k4H
             + ButchCKFb5 * k5H + ButchCKFb6 * k6H;

  /* Compute estimated error of each dependent variable, and keep
     track of the maximum estimated step rescaling found. */

  _maxerr = 0.0;

  for (i=0; i<_nIfuns; i++) {
    errorI[i] = TVIL_CABS(ButchCKFe1 * k1I[i] + ButchCKFe2 * k2I[i] 
			+ ButchCKFe3 * k3I[i] + ButchCKFe4 * k4I[i] 
                        + ButchCKFe5 * k5I[i] + ButchCKFe6 * k6I[i]);
    temp = errorI[i]/(err_goal * sumargsI[i]);
/*
printf("    II %d error = %Le = (%Le / (%Le * %Le))\n", i, temp, errorI[i],err_goal,II[i].sumargs);
*/
    if (_maxerr < temp) _maxerr = temp;
  }

  for (i=0; i<_nFBARfuns; i++) {
    errorFBAR[i] = TVIL_CABS(ButchCKFe1 * k1FBAR[i] + ButchCKFe2 * k2FBAR[i]
  			   + ButchCKFe3 * k3FBAR[i] + ButchCKFe4 * k4FBAR[i]
                           + ButchCKFe5 * k5FBAR[i] + ButchCKFe6 * k6FBAR[i]);
    temp = errorFBAR[i]/(err_goal * sumargsFBAR[i]);
/*
printf("    Fbar %d error = %Le = (%Le / (%Le * %Le))\n", i, temp, errorFBAR[i],err_goal, FBAR[i].sumargs);
*/
    if (_maxerr < temp) _maxerr = temp;
  }

  for (i=0; i<_nGfuns; i++) {
    errorG[i] = TVIL_CABS(ButchCKFe1 * k1G[i] + ButchCKFe2 * k2G[i]
   		        + ButchCKFe3 * k3G[i] + ButchCKFe4 * k4G[i]
                        + ButchCKFe5 * k5G[i] + ButchCKFe6 * k6G[i]);
    temp = errorG[i]/(err_goal * sumargsG[i]);
/*
printf("    G %d error = %Le = (%Le / (%Le * %Le))\n", i,temp,errorG[i],err_goal,G[i].sumargs);
*/
    if (_maxerr < temp) _maxerr = temp;
  }

  _maxerr_noH = _maxerr;

  if (_nHfuns) {
    errorH = TVIL_CABS(ButchCKFe1 * k1H + ButchCKFe2 * k2H
                     + ButchCKFe3 * k3H + ButchCKFe4 * k4H
                     + ButchCKFe5 * k5H + ButchCKFe6 * k6H);

    _err_H = errorH/(err_goal);
    if (_maxerr < _err_H) _maxerr = _err_H;
  }

  if (VERBOSE) {
    printf("    _maxerr = %Le,  _maxerr_noH = %Le,  _err_H = %Le\n",
           _maxerr, _maxerr_noH, _err_H);
  }

  if (_nHfuns)
    if (1 == TVIL_IsInfinite(deltaH)) _maxerr = 10.L * MAX_ALLOWED_ERR;

  for (i=0; i<_nGfuns; i++)
    if (1 == TVIL_IsInfinite(deltaG[i])) _maxerr = 10.L * MAX_ALLOWED_ERR;

  for (i=0; i<_nFBARfuns; i++)
    if (1 == TVIL_IsInfinite(deltaFBAR[i])) _maxerr = 10.L * MAX_ALLOWED_ERR;

  for (i=0; i<_nIfuns; i++)
    if (1 == TVIL_IsInfinite(deltaI[i])) _maxerr = 10.L * MAX_ALLOWED_ERR;

  /* Now, if the errors are acceptable, OR the step is being forced, 
     we increment the independent variable and the data values and 
     the derivatives, and get set to report status so that the calling
     program TVIL_Integrate know what to do next. 
     status = 1 for no problem
              -1 if _err_H was too large but _maxerr_noH was OK
              -2 if _maxerr_noH was too large

     Otherwise, set the data back to their original values.  
  */

  if ((_maxerr < 1.0L) || (1 == force_step)) 
    {
      status = 1;
      if ((1 == force_step) && (_err_H > MAX_ALLOWED_ERR)) status = -1;
      if ((1 == force_step) && (_maxerr_noH > MAX_ALLOWED_ERR)) status = -2;

      /* Update data values */
      for (i=0; i<_nIfuns; i++)
      	(_ifun[i])->value = startingI[i] + deltaI[i];

      for (i=0; i<_nFBARfuns; i++)
      	(_fbarfun[i])->value = startingFBAR[i] + deltaFBAR[i];

      for (i=0; i<_nGfuns; i++)
      	(_gfun[i])->value = startingG[i] + deltaG[i];

      if (_nHfuns)
	(_hfun)->value = startingH + deltaH;

      /* Set independent variable up for next step. */
      *RKindvar += *RKdelta;

      /* Update independent variable. */
      t = *RKindvar;

      TVIL_SetGlobalVars (t);
      
      /* Set derivatives for next step */
      for (i=0; i<_nIfuns; i++)
	(_ifun[i])->deriv = (_Iderivative) (_ifun[i], t, _qq);

      for (i=0; i<_nFBARfuns; i++)
      	(_fbarfun[i])->deriv = (_FBARderivative) (_fbarfun[i], t, _qq);

      for (i=0; i<_nGfuns; i++)
      	(_gfun[i])->deriv = (_Gderivative) (_gfun[i], t, _qq);

      if (_nHfuns)
	(_hfun)->deriv = (_Hderivative) (_hfun, t, _qq);
    }
  else {
    /* Set data back to original values, and don't touch the
       independent variable or the derivatives, since we failed to
       step. */
    status = 0;

    for (i=0; i<_nIfuns; i++) 
      (_ifun[i])->value = startingI[i];

    for (i=0; i<_nFBARfuns; i++)
      (_fbarfun[i])->value = startingFBAR[i];

    for (i=0; i<_nGfuns; i++)
      (_gfun[i])->value = startingG[i];

    if (_nHfuns)
      (_hfun)->value = startingH;
  }

  /* Predict the appropriate next step size. */
  step_rescale = TVIL_SQRT(TVIL_SQRT(1.0L/_maxerr));
  
  next_step_size = (*RKdelta) * SafetyFactor * step_rescale;

  /* Don't let the next step size be bigger than the present size by
     more than a factor of 1.5, or smaller than the present step size
     by more than a factor of 2. It isn't worth the risk. */
  
  if (TVIL_CABS(next_step_size) > 1.5L*TVIL_CABS(*RKdelta))
    next_step_size = 1.5L* (*RKdelta);

  if (TVIL_CABS(next_step_size) < 0.5L*TVIL_CABS(*RKdelta))
    next_step_size = 0.5L* (*RKdelta);

  /* Recommend the new step size to the calling function TVIL_Integrate (). */
  *RKdelta = next_step_size;

  return status;
}
