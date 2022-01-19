/*
#define VERBOSE 1
#define VERBOSE (TVIL_CABS(t-1) < 0.01L)
*/
#define VERBOSE 0

/* Evaluation for the generic case. */

#include "internal.h"
#include "3vil_params.h"

/* **************************************************************** */

int TVIL_MaxSteps (TVIL_COMPLEX z)
{
  return (_nStepsMaxCon 
          + floor((double) (TVIL_CABS(z) * _nStepsMaxVar)));
}

/* **************************************************************** */

void TVIL_InitialValue (TVIL_COMPLEX tinit)
{
  int i;

  /* Set initial values for integration... */
  if (_evalMode == ALL || 
      _evalMode == EFG ||
      _evalMode == EF) {

    for (i=0; i<_nIfuns; i++)
      TVIL_InitialI (_ifun[i], _qq, tinit);

    for (i=0; i<_nFBARfuns; i++)
      TVIL_InitialFBAR (_fbarfun[i], _qq, tinit);

    for (i=0; i<_nGfuns; i++)
      TVIL_InitialG (_gfun[i], _qq, tinit);

    if (_nHfuns)
      TVIL_InitialH (_hfun, _qq, tinit);
  }

  /* DGRDGR THIS ALL NEEDS TO BE PUT BACK!!!! */
  else if (_evalMode == THREESCALE_A) {

    /* DGRDGR might want to just pass an argument to a single version
       of each function. Or we could set a function pointer? */

    /* This is necessary for using the derivative routines: */
    TVIL_SetGlobalVars (tinit);

    for (i=0; i<_nIfuns; i++)
      TVIL_InitialI_3sA (_ifun[i], _qq, tinit);

    for (i=0; i<_nFBARfuns; i++)
      TVIL_InitialFBAR_3sA (_fbarfun[i], _qq, tinit);

    for (i=0; i<_nGfuns; i++)
      TVIL_InitialG_3sA (_gfun[i], _qq, tinit);

    if (_nHfuns)
      TVIL_InitialH_3sA (_hfun, _qq, tinit);

    /* Do derivatives after all function values are set: */
    for (i=0; i<_nFBARfuns; i++)
      _fbarfun[i]->deriv = TVIL_dFBARdt_3sA (_fbarfun[i], tinit, _qq);

    for (i=0; i<_nGfuns; i++)
      _gfun[i]->deriv = TVIL_dGdt_3sA (_gfun[i], tinit, _qq);

    if (_nHfuns)
      _hfun->deriv = TVIL_dHdt_3sA (_hfun, tinit, _qq);
  }
  else if (_evalMode == THREESCALE_B) {

    /* This is necessary for using the derivative routines: */
    TVIL_SetGlobalVars (tinit);

    for (i=0; i<_nIfuns; i++)
      TVIL_InitialI_3sB (_ifun[i], _qq, tinit);

    for (i=0; i<_nFBARfuns; i++)
      TVIL_InitialFBAR_3sB (_fbarfun[i], _qq, tinit);

    for (i=0; i<_nGfuns; i++)
      TVIL_InitialG_3sB (_gfun[i], _qq, tinit);

    if (_nHfuns)
      TVIL_InitialH_3sB (_hfun, _qq, tinit);

    /* Do derivatives after all function values are set: */
    for (i=0; i<_nFBARfuns; i++)
      _fbarfun[i]->deriv = TVIL_dFBARdt_3sB (_fbarfun[i], tinit, _qq);

    for (i=0; i<_nGfuns; i++)
      _gfun[i]->deriv = TVIL_dGdt_3sB (_gfun[i], tinit, _qq);

    if (_nHfuns)
      _hfun->deriv = TVIL_dHdt_3sB (_hfun, tinit, _qq);
  }
  else if (_evalMode == THREESCALE_C) {

    /* This is necessary for using the derivative routines: */
    TVIL_SetGlobalVars (tinit);

    for (i=0; i<_nIfuns; i++)
      TVIL_InitialI_3sC (_ifun[i], _qq, tinit);

    for (i=0; i<_nFBARfuns; i++)
      TVIL_InitialFBAR_3sC (_fbarfun[i], _qq, tinit);

    for (i=0; i<_nGfuns; i++)
      TVIL_InitialG_3sC (_gfun[i], _qq, tinit);

    if (_nHfuns)
      TVIL_InitialH_3sC (_hfun, _qq, tinit);

    /* Do derivatives after all function values are set: */
    for (i=0; i<_nFBARfuns; i++)
      _fbarfun[i]->deriv = TVIL_dFBARdt_3sC (_fbarfun[i], tinit, _qq);

    for (i=0; i<_nGfuns; i++)
      _gfun[i]->deriv = TVIL_dGdt_3sC (_gfun[i], tinit, _qq);

    if (_nHfuns)
      _hfun->deriv = TVIL_dHdt_3sC (_hfun, tinit, _qq);

    /* printf("CHECK OF INITIAL VALUES:\n"); */
    /* status = ANALYTIC; */
    /* TVIL_PrintData (foo); */
    /* status = UNEVALUATED; */

    /* printf("\nDerivatives:\n"); */
    /* for (i=0; i<foo->_nIfuns; i++) */
    /*   {printf("dI[%d]/dz = ", i); TVIL_cprintf(foo->ifun[i]->deriv); printf("\n");} */

    /* printf("\n"); */
    /* for (i=0; i<foo->_nFBARfuns; i++) */
    /*   {printf("dF[%d]/dz = ", i); TVIL_cprintf(foo->_fbarfun[i]->deriv); printf("\n");} */

    /* printf("\n"); */
    /* for (i=0; i<foo->_nGfuns; i++) */
    /*   {printf("dG[%d]/dz = ", i); TVIL_cprintf(foo->gfun[i]->deriv); printf("\n");} */

    /* printf("\n"); */
    /* if (foo->_nHfuns) */
    /*   {printf("dH/dz = "); TVIL_cprintf(foo->hfun->deriv); printf("\n");} */

    /* exit(0); */

  }
  else
    TVIL_Error ("InitialValue", "Impossible, invalid _evalMode.", 909);


  return;
}

/* ******************************************************************* */

int TVIL_Integrate (TVIL_COMPLEX  t0,
		    TVIL_COMPLEX  t1,
		    TVIL_REAL    *dt_start) 
{
  TVIL_COMPLEX t, dt;
  TVIL_REAL pre_error = _precisionGoal;

  TVIL_RESULT save_point[65];
  TVIL_COMPLEX t_save[65];
  TVIL_COMPLEX H_save[65];
  TVIL_COMPLEX bestH;
  int saved[65];
  int num_saved = 0;
  int err_bin;
  TVIL_REAL Hscore, best_Hscore;

  int i;
  int force_step;
  int rk6status = 1; /* 1 for success or forced; 
                        0 for need retry, 
		       -1 when the H error is big and step was forced. 
		       -2 when the non-H error is big and step was forced. */

  int status_others = 1; /* Set to 0 when other function errors get big.   */

  int numfuns = _nIfuns + _nFBARfuns + _nGfuns + _nHfuns;

  for (i=0; i<65; i++) saved[i] = 0;

  t  = t0;
  dt = TVIL_FABS(*dt_start) * (t1 - t0)/TVIL_CABS(t1 - t0);

  /* Continue taking steps until we are less than 2 steps away from
     the endpoint. However, if the error reported by rk6 gets bigger
     than MAX_ALLOWED_ERR defined in rk6.c, and we're near the
     endpoint, then things probably aren't going to get any
     better. So, also in that case we will take only one more step. */
  while ( (TVIL_CABS(dt) < 0.5*TVIL_CABS(t1 - t)) && (1 == status_others) )
  {
    force_step = 0;

    for (;;) {

      if (TVIL_CABS(dt) < TVIL_MIN_STEP_SIZE) {
        force_step = 1;
        dt = TVIL_MIN_STEP_SIZE * dt/TVIL_CABS(dt);
      }

      if (VERBOSE) {
        printf("force = %d: t = %Le + %Le I,  deltat = %Le + %Le I\n",
        force_step, TVIL_CREAL(t), TVIL_CIMAG(t), TVIL_CREAL(dt), TVIL_CIMAG(dt));
      }

      rk6status = _RKstepper6 (numfuns, &t, &dt, pre_error, force_step);
      if (0 != rk6status) break;
    }

    /* If H error reported by rk6 got big, save a bunch of points so
       that for each we can do just one more step from here to find
       H.  */

    /* If H is NaN, and we aren't close to t=1, something is very
       wrong. */
    if ((1 == TVIL_IsInfinite(_H.value)) && (TVIL_CABS(t-1) > 0.01L)) 
      TVIL_Error ("TVIL_Integrate", "H is non-numeric; evaluation terminated. This should never happen. Please contact the authors with details of this case.", -666);

    err_bin = floor((double) (3.0L * TVIL_CLOG(_err_H))) - 12;

    if ((0 < err_bin) && (err_bin < 65) && (saved[err_bin] == 0) && (TVIL_CABS(t-1) < 0.01L)) {
      num_saved++;
      TVIL_Backup (&(save_point[num_saved]));
      t_save[num_saved] = t;
      for (i=1; i <= err_bin; i++) saved[i] = 1;
      /* printf("SAVE t = 1 + %Le I, err_H = %Le, err_noH = %Le\n", */
        /* TVIL_CIMAG(t), err_H, maxerr_noH); */
    }

    /* If the errors in non-H functions got too big, just do one more
       step.  Set status_others to 0 so that the while loop knows to
       stop. */
    if ((_maxerr_noH > 1e9) && (TVIL_CABS(t-1) < 0.01L)) {
      status_others = 0;
    }
  }

  t_save[0] = t;
  TVIL_Backup (&(save_point[0]));

  /* Save the step size magnitude, to be used at start of the next
     leg, if there is one. */
  *dt_start = TVIL_CABS(dt);

  /* The remaining distance is less than twice the step size. So, take
     one more step arranged to land exactly on t1, and force it.  Do
     it for each saved point, running backwards through the list of
     saved points, so that the last point run is the one that should
     have the best non-H functions. */

  for (i=num_saved; i >= 0; i--) {
    TVIL_Restore (&(save_point[i]));
    t = t_save[i];
    dt = t1 - t;

    if ((_poleAt1) && (TVIL_CABS(t-1) < 0.01L))
      _RKstepper5 (numfuns, &t, dt); 
    else 
      _RKstepper6 (numfuns, &t, &dt, pre_error, 1); 

    H_save[i] = _H.value;
  }

  /* Now we need to choose the best H. If there were no saved points
     with large err_H, then our course is clear... */
  if (0 == num_saved) 
    bestH = H_save[0];
  else 
    /* printf("Number of points saved for retry = %d\n",num_saved); */

  /* ... and if we have 1 to 3 saved points with large err_H, which
     should almost never happen, the best we can do is just take the
     one with the smallest Im[H] ... */
  if ((1 <= num_saved) && (num_saved <= 3) && (TVIL_CABS(t-1) < 0.01L)){
    bestH = H_save[1];
    /* printf("Point 1: H = %Le + I %Le\n", TVIL_CREAL(H_save[1]), TVIL_CIMAG(H_save[1])); */
    for (i=2; i <= num_saved; i++) {
      if (TVIL_FABS(TVIL_CIMAG(H_save[i])) < TVIL_FABS(TVIL_CIMAG(bestH)))
       bestH = H_save[i];
    /* printf("Point %d: H = %Le + I %Le\n", i, TVIL_CREAL(H_save[i]), TVIL_CIMAG(H_save[i])); */
    }
  }

  /* ... and if more than 3 saved points, we take into account both
     Im[H] and closeness to its neighbors... */
  if ((4 <= num_saved) && (num_saved <= 65) && (TVIL_CABS(t-1) < 0.01L)){
    bestH = H_save[2];
    best_Hscore = 666;
    /* printf("Point 1: H = %Le + I %Le\n", TVIL_CREAL(H_save[1]), TVIL_CIMAG(H_save[1])); */
    for (i=2; i < num_saved; i++) {
      /* The following metric is up for debate. */
      Hscore = 2.L*TVIL_FABS(TVIL_CIMAG(H_save[i])) +
               TVIL_FABS(TVIL_CREAL(H_save[i]) - TVIL_CREAL(H_save[i-1]))+
               TVIL_FABS(TVIL_CREAL(H_save[i]) - TVIL_CREAL(H_save[i+1]));

      if (Hscore < best_Hscore) {
        best_Hscore = Hscore;
        bestH = H_save[i];
      }
      /* printf("Point %d: H = %Le + I %Le\n", i, TVIL_CREAL(H_save[i]), TVIL_CIMAG(H_save[i])); */
    }
    /* printf("Point %d: H = %Le + I %Le\n", num_saved, TVIL_CREAL(H_save[num_saved]), TVIL_CIMAG(H_save[num_saved])); */
  }

  _H.value = bestH;

  return 0;
}

/* ******************************************************************** */
/* Handling of all generic (i.e. non-analytic) cases.                   */

void TVIL_CaseGeneric (void)
{
  TVIL_COMPLEX ti, tf;
  TVIL_REAL deltat_start;

  /* Since we will be integrating, set up derivative coefficients,
     etc., in all function objects, along with global a parameter and
     powers: */
  TVIL_SetupFunctions ();

  deltat_start = 0.0001L;

  if (_reAxisOK && _forceContour == NO) {

    ti = _tInit;
    TVIL_InitialValue (ti);
    tf = 1.0L;
    TVIL_Integrate (ti, tf, &deltat_start);
    _status = REAXIS;

  } else {

    ti = (_tInit)*I;
    TVIL_InitialValue (ti);

    /* First leg: */
    tf = (_imDispl)*I;
    TVIL_Integrate (ti, tf, &deltat_start);

    /* Second leg: */
    ti = tf;
    tf = 1.0L + (_imDispl)*I;
    TVIL_Integrate (ti, tf, &deltat_start);

    /* Last leg: */
    ti = tf;
    tf = 1.0L + 0.0L*I;
    TVIL_Integrate (ti, tf, &deltat_start);

    _status = CONTOUR;
  }

  return;
}
