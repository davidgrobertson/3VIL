/* ******************************************************************* */
/*              EVALUATION DRIVER PROGRAM FOR SUBSET CASES             */
/* ******************************************************************* */

#include "internal.h"
#include "3vil_params.h"

/* ******************************************************************* */
/* New evaluatione routine... */

int TVIL_EvaluateEFG (TVIL_REAL a1,
		      TVIL_REAL a2,
		      TVIL_REAL a3,
		      TVIL_REAL a4,
		      TVIL_REAL a5,
		      TVIL_REAL a6,
		      TVIL_RESULT *foo)
{
  char funcname[] = "TVIL_EvaluateEFG";
  /* int status = 1; */
  int isAnalytic = NO;
  int i, j, tmpWarns;

  if (_isAligned == NO) TVIL_Setup ();

  /* Basic setup in struct: */
  foo->u = _u = a1;
  foo->v = _v = a2;
  foo->w = _w = a3;
  foo->x = _x = a4;
  foo->y = _y = a5;
  foo->z = _z = TVIL_Infinity;
  foo->qq = _qq = a6;

  _evalMode = foo->evalMode = EFG;

  /* Define functions to be evaluated */
  TVIL_EvaluateAllFunctions (foo, NO);

  foo->evaluateII[uvx] = YES;
  foo->evaluateII[uxy] = YES;
  foo->evaluateII[vwy] = YES;
  foo->evaluateII[uwy] = YES;
  foo->evaluateII[wxy] = YES;
  foo->evaluateII[uwx] = YES;
  foo->nIfuns = 6;

  foo->evaluateFBAR[wuxy] = YES;
  foo->evaluateFBAR[xuwy] = YES;
  foo->evaluateFBAR[uwxy] = YES;
  foo->evaluateFBAR[yuwx] = YES;
  foo->nFBARfuns = 4;

  foo->evaluateE[Ewuxy] = YES;
  foo->nEfuns = 1;

  foo->evaluateG[vuxwy] = YES;
  foo->nGfuns = 1;

  /* Temporarily disable WARNs */
  tmpWarns = _print3VILWarns;
  _print3VILWarns = NO;

  /* First, check if this is an analytic case: */
  TVIL_SetArguments (foo);

  if (_doAnalytic == YES &&
      (isAnalytic = TVIL_CaseSpecial (foo)) == YES) {

    /* In this case, it was analytic and we are done with evaluating
       the main functions... */
    foo->status = ANALYTIC;
  }
  /* If we get here, then generic evaluation */
  else {

    TVIL_IntegrateAllFunctions (foo, YES);
    TVIL_CaseGeneric ();
  }

  /* The following puts in the analytic results for I, FBAR, G, and H,
     if available. However, leaving it out allows debugging of the RK
     evaluation of analytic cases, which is quite useful. */
  if (_doAnalytic && !isAnalytic)
    TVIL_CaseSpecial (foo);

  /* Set additional functions: */
  TVIL_SetAllEs (foo);
  TVIL_SetBold (foo);

  /* Now transfer results back to foo... */
  for (i=0; i<NUM_I_FUNCS; i++) {
    if (foo->evaluateII[i]) {
      foo->II[i] = _II[i].value;
      for (j=0; j<3; j++)
	foo->IIbold[i][j] = _II[i].bold[j];
    }
  }
  for (i=0; i<NUM_F_FUNCS; i++) {
    if (foo->evaluateFBAR[i]) {
      foo->FBAR[i] = _FBAR[i].value;
      foo->F[i] = _FBAR[i].fValue;
      for (j=0; j<4; j++)
	foo->Fbold[i][j] = _FBAR[i].boldF[j];
    }
  }
  for (i=0; i<NUM_E_FUNCS; i++) {
    if (foo->evaluateE[i]) {
      foo->E[i] = _E[i].value;
      for (j=0; j<4; j++)
	foo->Ebold[i][j] = _E[i].bold[j];
    }
  }
  for (i=0; i<NUM_G_FUNCS; i++) {
    if (foo->evaluateG[i]) {
      foo->G[i] = _G[i].value;
      for (j=0; j<4; j++)
	foo->Gbold[i][j] = _G[i].bold[j];
    }
  }

  /* Set status indicators in struct: */
  foo->status = _status;
  foo->evalMode = _evalMode;

  /* Restore initial warning status */
  _print3VILWarns = tmpWarns;

  /* Implement status codes eventually */
  return _status;
}

/* ******************************************************************* */
/* New evaluatione routine... */

int TVIL_EvaluateEF (TVIL_REAL a1,
		     TVIL_REAL a2,
		     TVIL_REAL a3,
		     TVIL_REAL a4,
		     TVIL_REAL a5,
		     TVIL_RESULT *foo)
{
  char funcname[] = "TVIL_EvaluateEF";
  int status = 1;
  int isAnalytic = NO;
  int i, j, tmpWarns;

  if (_isAligned == NO) TVIL_Setup ();

  /* Basic setup in struct: */
  foo->u = _u = a1;
  foo->v = _v = TVIL_Infinity;
  foo->w = _w = a2;
  foo->x = _x = a3;
  foo->y = _y = a4;
  foo->z = _z = TVIL_Infinity;
  foo->qq = _qq = a5;

  _evalMode = foo->evalMode = EF;

  /* Define functions to be evaluated */
  TVIL_EvaluateAllFunctions (foo, NO);

  foo->evaluateII[uxy] = YES;
  foo->evaluateII[uwy] = YES;
  foo->evaluateII[wxy] = YES;
  foo->evaluateII[uwx] = YES;
  foo->nIfuns = 4;

  foo->evaluateFBAR[wuxy] = YES;
  foo->evaluateFBAR[xuwy] = YES;
  foo->evaluateFBAR[uwxy] = YES;
  foo->evaluateFBAR[yuwx] = YES;
  foo->nFBARfuns = 4;

  foo->evaluateE[Ewuxy] = YES;
  foo->nEfuns = 1;

  /* Temporarily disable WARNs */
  tmpWarns = _print3VILWarns;
  _print3VILWarns = NO;

  /* First, check if this is an analytic case: */
  TVIL_SetArguments (foo);

  if (_doAnalytic == YES &&
      (isAnalytic = TVIL_CaseSpecial (foo)) == YES) {

    /* In this case, it was analytic and we are done with evaluating
       the main functions... */
    foo->status = ANALYTIC;
  }
  else {

    TVIL_IntegrateAllFunctions (foo, YES);
    TVIL_CaseGeneric ();
  }

  /* The following puts in the analytic results for I, FBAR, G, and H,
     if available. However, leaving it out allows debugging of the RK
     evaluation of analytic cases, which is quite useful. */
  if (_doAnalytic && !isAnalytic)
    TVIL_CaseSpecial (foo);

  /* Set additional functions: */
  TVIL_SetAllEs (foo);
  TVIL_SetBold (foo);

  /* Now transfer results back to foo... */
  for (i=0; i<NUM_I_FUNCS; i++) {
    if (foo->evaluateII[i]) {
      foo->II[i] = _II[i].value;
      for (j=0; j<3; j++)
	foo->IIbold[i][j] = _II[i].bold[j];
    }
  }
  for (i=0; i<NUM_F_FUNCS; i++) {
    if (foo->evaluateFBAR[i]) {
      foo->FBAR[i] = _FBAR[i].value;
      foo->F[i] = _FBAR[i].fValue;
      for (j=0; j<4; j++)
	foo->Fbold[i][j] = _FBAR[i].boldF[j];
    }
  }
  for (i=0; i<NUM_E_FUNCS; i++) {
    if (foo->evaluateE[i]) {
      foo->E[i] = _E[i].value;
      for (j=0; j<4; j++)
	foo->Ebold[i][j] = _E[i].bold[j];
    }
  }

  /* Set status indicators in struct: */
  foo->status = _status;
  foo->evalMode = _evalMode;

  /* Restore initial warning status */
  _print3VILWarns = tmpWarns;

  /* Implement status codes eventually */
  return status;
}
