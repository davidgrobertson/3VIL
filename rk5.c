/* 
  Implements a general 5-stage, 4th-order Runge-Kutta step.  The
  purpose of this (as opposed to classical 4-substep 4th order
  Runge-Kutta) is to never have to evaluate anything at the endpoint.
  Butcher coefficients a[i,j], b[i], c[i] have to be selected
  according to theory; for our purposes it is important that c[5] < 1.

  This code can be made more efficient by removing terms in the code
  involving coefficient a[i,j] that are 0. However, efficiency is not
  a big concern, because the function TVIL_rk5 should only be called
  once in each run. So all of the 0 coefficients are left in as a nod
  to generality.

  If RKmode = 0, then RKindvar = s is incremented by an amount
  RKdelta.  (Here tthresh is ignored.)

  If RKmode = 1, then RKindvar = ln(1-s/tthresh) is incremented by
  RKdelta.  (Here tthresh is the nearest threshold.)

  The function objects and *RKindvar are updated at the end. The
  derivatives are NOT updated, because they might diverge causing a
  major speed hit, and because they are not needed (since this is ONLY
  to be used for the last step!)

  NOTE: do NOT call rk4 AFTER calling TVIL_rk5, because rk4 expects
  the derivatives to be up-to-date in the struct, and TVIL_rk5 doesn't
  update them!  It is permitted to call TVIL_rk5 repeatedly as a test,
  because TVIL_rk5 doesn't assume that the derivatives in the struct
  are updated. But that would be needlessly inefficient.  

*/

#include "internal.h"

/* Here is a nice set of Butcher coefficients. Others are possible.*/
#define Butcherc2 0.25L
#define Butcherc3 0.375L
#define Butcherc4 0.5L
#define Butcherc5 0.625L

#define Butchera21 0.25L
#define Butchera31 0.0L
#define Butchera32 0.375L
#define Butchera41 0.0L
#define Butchera42 0.5L
#define Butchera43 0.0L
#define Butchera51 0.0L
#define Butchera52 35.0L/72.0L
#define Butchera53 0.0L
#define Butchera54 (5.0L/36.0L)

#define Butcherb1 (-1.0L/15.0L)
#define Butcherb2 (2.0L/3.0L)
#define Butcherb3 (4.0L/3.0L)
#define Butcherb4 (-10.0L/3.0L)
#define Butcherb5 (12.0L/5.0L)

/* **************************************************************** */

void TVIL_rk5 (int           nData,
	       TVIL_COMPLEX *RKindvar,
	       TVIL_COMPLEX  RKdelta)
{
  char funcname[] = "TVIL_rk5";

  TVIL_COMPLEX k1I[NUM_I_FUNCS], k2I[NUM_I_FUNCS], k3I[NUM_I_FUNCS];
  TVIL_COMPLEX k4I[NUM_I_FUNCS], k5I[NUM_I_FUNCS];
  TVIL_COMPLEX startingI[NUM_I_FUNCS];

  TVIL_COMPLEX k1FBAR[NUM_F_FUNCS], k2FBAR[NUM_F_FUNCS], k3FBAR[NUM_F_FUNCS];
  TVIL_COMPLEX k4FBAR[NUM_F_FUNCS], k5FBAR[NUM_F_FUNCS];
  TVIL_COMPLEX startingFBAR[NUM_F_FUNCS];

  TVIL_COMPLEX k1G[NUM_G_FUNCS], k2G[NUM_G_FUNCS], k3G[NUM_G_FUNCS];
  TVIL_COMPLEX k4G[NUM_G_FUNCS], k5G[NUM_G_FUNCS];
  TVIL_COMPLEX startingG[NUM_G_FUNCS];

  TVIL_COMPLEX k1H, k2H, k3H;
  TVIL_COMPLEX k4H, k5H;
  TVIL_COMPLEX startingH;

  TVIL_COMPLEX t, dt;
  int i;

  /* Relate t, dt to the independent variable. */
  t = *RKindvar;
  dt = RKdelta;

  for (i=0; i<_nIfuns; i++)
      startingI[i] = (_ifun[i])->value;

  for (i=0; i<_nFBARfuns; i++)
    startingFBAR[i] = (_fbarfun[i])->value;

  for (i=0; i<_nGfuns; i++)
    startingG[i] = (_gfun[i])->value;

  if (_nHfuns)
    startingH = (_hfun)->value;

  TVIL_SetGlobalVars (t);

  /* Fill up k1 arrays: */
  for (i=0; i<_nIfuns; i++)
    k1I[i] = dt * (_Iderivative) (_ifun[i], t, _qq);

  for (i=0; i<_nFBARfuns; i++)
    k1FBAR[i] = (_FBARderivative) (_fbarfun[i], t, _qq) * dt;

  for (i=0; i<_nGfuns; i++)
    k1G[i] = dt * (_Gderivative) (_gfun[i], t, _qq);

  if (_nHfuns)
    k1H = dt * (_Hderivative) (_hfun, t, _qq);

  /* for (i=0; i<NUM_I_FUNCS; i++) */
  /*   k1I[i] = dt * Iderivative (II[i], t, _qq); */

  /* for (i=0; i<NUM_F_FUNCS; i++) */
  /*   k1FBAR[i] = dt * TVIL_dFBARdt (FBAR[i], t, _qq); */

  /* for (i=0; i<NUM_G_FUNCS; i++) */
  /*   k1G[i] = dt * (_Gderivative) (G[i], t, _qq); */

  /* k1H = dt * TVIL_dHdt (H, t, _qq); */

  /* Update independent variable. */
  t = *RKindvar + Butcherc2 * RKdelta;

  /* Adjust data values */
  for (i=0; i<_nIfuns; i++)
    (_ifun[i])->value = startingI[i] + Butchera21 * k1I[i];

  for (i=0; i<_nFBARfuns; i++)
    (_fbarfun[i])->value = startingFBAR[i] + Butchera21 * k1FBAR[i];

  for (i=0; i<_nGfuns; i++)
    (_gfun[i])->value = startingG[i] + Butchera21 * k1G[i];

  if (_nHfuns)
    (_hfun)->value = startingH + Butchera21 * k1H;

  TVIL_SetGlobalVars (t);

  /* Fill up k2 arrays: */
  for (i=0; i<_nIfuns; i++)
    k2I[i] = dt * (_Iderivative) ((_ifun[i]), t, _qq);

  for (i=0; i<_nFBARfuns; i++)
    k2FBAR[i] = (_FBARderivative) (_fbarfun[i], t, _qq) * dt;

  for (i=0; i<_nGfuns; i++)
    k2G[i] = dt * (_Gderivative) (_gfun[i], t, _qq);

  if (_nHfuns)
    k2H = dt * (_Hderivative) (_hfun, t, _qq);

  /* for (i=0; i<NUM_I_FUNCS; i++) */
  /*   k2I[i] = dt * Iderivative (II[i], t, _qq); */

  /* for (i=0; i<NUM_F_FUNCS; i++) */
  /*   k2FBAR[i] = dt * TVIL_dFBARdt (FBAR[i], t, _qq); */

  /* for (i=0; i<NUM_G_FUNCS; i++) */
  /*   k2G[i] = dt * TVIL_dGdt (G[i], t, _qq); */

  /* k2H = dt * TVIL_dHdt (H, t, _qq); */

  /* Update independent variabl. */
  t = *RKindvar + Butcherc3 * RKdelta;

  /* Adjust data values */
  for (i=0; i<_nIfuns; i++)
    (_ifun[i])->value = startingI[i] + Butchera31 * k1I[i]
                                  + Butchera32 * k2I[i];

  for (i=0; i<_nFBARfuns; i++)
    (_fbarfun[i])->value = startingFBAR[i] + Butchera31 * k1FBAR[i]
                                     + Butchera32 * k2FBAR[i];

  for (i=0; i<_nGfuns; i++)
    (_gfun[i])->value = startingG[i] + Butchera31 * k1G[i]
                                  + Butchera32 * k2G[i];

  if (_nHfuns)
    (_hfun)->value = startingH + Butchera31 * k1H
                            + Butchera32 * k2H;

  TVIL_SetGlobalVars (t);

  /* Fill up k3 arrays: */
  for (i=0; i<_nIfuns; i++)
    k3I[i] = dt * (_Iderivative) ((_ifun[i]), t, _qq);

  for (i=0; i<_nFBARfuns; i++)
    k3FBAR[i] = (_FBARderivative) (_fbarfun[i], t, _qq) * dt;

  for (i=0; i<_nGfuns; i++)
    k3G[i] = dt * (_Gderivative) (_gfun[i], t, _qq);

  if (_nHfuns)
    k3H = dt * (_Hderivative) (_hfun, t, _qq);

  /* for (i=0; i<NUM_I_FUNCS; i++) */
  /*   k3I[i] = dt * Iderivative (II[i], t, _qq); */

  /* for (i=0; i<NUM_F_FUNCS; i++) */
  /*   k3FBAR[i] = dt * TVIL_dFBARdt (FBAR[i], t, _qq); */

  /* for (i=0; i<NUM_G_FUNCS; i++) */
  /*   k3G[i] = dt * TVIL_dGdt (G[i], t, _qq); */

  /* k3H = dt * TVIL_dHdt (H, t, _qq); */

  /* Update independent variable. */
  t = *RKindvar + Butcherc4 * RKdelta;

  /* Adjust data values */
  for (i=0; i<_nIfuns; i++)
    (_ifun[i])->value = startingI[i] + Butchera41 * k1I[i]
                                  + Butchera42 * k2I[i]
                                  + Butchera43 * k3I[i];

  for (i=0; i<_nFBARfuns; i++)
    (_fbarfun[i])->value = startingFBAR[i] + Butchera41 * k1FBAR[i]
                                     + Butchera42 * k2FBAR[i]
                                     + Butchera43 * k3FBAR[i];

  for (i=0; i<_nGfuns; i++)
    (_gfun[i])->value = startingG[i] + Butchera41 * k1G[i]
                                  + Butchera42 * k2G[i]
                                  + Butchera43 * k3G[i];
  if (_nHfuns)
    (_hfun)->value = startingH + Butchera41 * k1H
                            + Butchera42 * k2H
                            + Butchera43 * k3H;

  TVIL_SetGlobalVars (t);

  /* Fill up k4 arrays: */
  for (i=0; i<_nIfuns; i++)
    k4I[i] = dt * (_Iderivative) ((_ifun[i]), t, _qq);

  for (i=0; i<_nFBARfuns; i++)
    k4FBAR[i] = (_FBARderivative) (_fbarfun[i], t, _qq) * dt;

  for (i=0; i<_nGfuns; i++)
    k4G[i] = dt * (_Gderivative) (_gfun[i], t, _qq);

  if (_nHfuns)
    k4H = dt * (_Hderivative) (_hfun, t, _qq);

  /* for (i=0; i<NUM_I_FUNCS; i++) */
  /*   k4I[i] = dt * Iderivative (II[i], t, _qq); */

  /* for (i=0; i<NUM_F_FUNCS; i++) */
  /*   k4FBAR[i] = dt * TVIL_dFBARdt (FBAR[i], t, _qq); */

  /* for (i=0; i<NUM_G_FUNCS; i++) */
  /*   k4G[i] = dt * TVIL_dGdt (G[i], t, _qq); */

  /* k4H = dt * TVIL_dHdt (H, t, _qq); */

  /* Update independent variable. */
  t = *RKindvar + Butcherc5 * RKdelta;

  /* Adjust data values */
  for (i=0; i<_nIfuns; i++)
    (_ifun[i])->value = startingI[i] + Butchera51 * k1I[i]
                                  + Butchera52 * k2I[i]
                                  + Butchera53 * k3I[i]
                                  + Butchera54 * k4I[i];

  for (i=0; i<_nFBARfuns; i++)
    (_fbarfun[i])->value = startingFBAR[i] + Butchera51 * k1FBAR[i]
                                     + Butchera52 * k2FBAR[i]
                                     + Butchera53 * k3FBAR[i]
                                     + Butchera54 * k4FBAR[i];

  for (i=0; i<_nGfuns; i++)
    (_gfun[i])->value = startingG[i] + Butchera51 * k1G[i]
                                  + Butchera52 * k2G[i]
                                  + Butchera53 * k3G[i]
                                  + Butchera54 * k4G[i];

  if (_nHfuns)
    (_hfun)->value = startingH + Butchera51 * k1H
                            + Butchera52 * k2H
                            + Butchera53 * k3H
                            + Butchera54 * k4H;

  TVIL_SetGlobalVars (t);

  /* Fill up k5 arrays: */
  for (i=0; i<_nIfuns; i++)
    k5I[i] = dt * (_Iderivative) ((_ifun[i]), t, _qq);

  for (i=0; i<_nFBARfuns; i++)
    k5FBAR[i] = (_FBARderivative) (_fbarfun[i], t, _qq) * dt;

  for (i=0; i<_nGfuns; i++)
    k5G[i] = dt * (_Gderivative) (_gfun[i], t, _qq);

  if (_nHfuns)
    k5H = dt * (_Hderivative) (_hfun, t, _qq);

  /* for (i=0; i<NUM_I_FUNCS; i++) */
  /*   k5I[i] = dt * Iderivative (II[i], t, _qq); */

  /* for (i=0; i<NUM_F_FUNCS; i++) */
  /*   k5FBAR[i] = dt * TVIL_dFBARdt (FBAR[i], t, _qq); */

  /* for (i=0; i<NUM_G_FUNCS; i++) */
  /*   k5G[i] = dt * TVIL_dGdt (G[i], t, _qq); */

  /* k5H = dt * TVIL_dHdt (H, t, _qq); */

  /* Increment data values */
  for (i=0; i<_nIfuns; i++)
    (_ifun[i])->value =   startingI[i]
                     + Butcherb1 * k1I[i] + Butcherb2 * k2I[i] 
                     + Butcherb3 * k3I[i] + Butcherb4 * k4I[i] 
                     + Butcherb5 * k5I[i];

  for (i=0; i<_nFBARfuns; i++)
    (_fbarfun[i])->value =   startingFBAR[i]
                     + Butcherb1 * k1FBAR[i] + Butcherb2 * k2FBAR[i]
                     + Butcherb3 * k3FBAR[i] + Butcherb4 * k4FBAR[i]
                     + Butcherb5 * k5FBAR[i];

  for (i=0; i<_nGfuns; i++)
    (_gfun[i])->value =   startingG[i]
                     + Butcherb1 * k1G[i] + Butcherb2 * k2G[i]
                     + Butcherb3 * k3G[i] + Butcherb4 * k4G[i]
                     + Butcherb5 * k5G[i];
  
  if (_nHfuns)
    (_hfun)->value = startingH
                + Butcherb1 * k1H + Butcherb2 * k2H
                + Butcherb3 * k3H + Butcherb4 * k4H
                + Butcherb5 * k5H;

  /* Update independent variable for next step, if there is one. */
  *RKindvar += RKdelta;

  return;
}
