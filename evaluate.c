/* ******************************************************************* */
/*              EVALUATION DRIVER PROGRAM                              */
/* ******************************************************************* */

#include "internal.h"
#include "3vil_params.h"

/* ******************************************************************* */
/* New evaluatione routine... */

int TVIL_Evaluate (TVIL_REAL a1,
		   TVIL_REAL a2,
		   TVIL_REAL a3,
		   TVIL_REAL a4,
		   TVIL_REAL a5,
		   TVIL_REAL a6,
		   TVIL_REAL a7,
		   TVIL_RESULT *foo)
{
  char funcname[] = "TVIL_Evaluate";
  int isAnalytic = NO;
  int i, j, tmpWarns, whichOne, whichPerm;
  /* TVIL_REAL arg[6]; */

  foo->status = UNEVALUATED;
  if (_isAligned == NO) TVIL_Setup ();

  /* Basic setup: */
  _arglist[0] = foo->u = _u = a1;
  _arglist[1] = foo->v = _v = a2;
  _arglist[2] = foo->w = _w = a3;
  _arglist[3] = foo->x = _x = a4;
  _arglist[4] = foo->y = _y = a5;
  _arglist[5] = foo->z = _z = a6;
  foo->qq = _qq = a7;

  /* In this case we will evaluate everything */
  _evalMode = ALL;
  TVIL_EvaluateAllFunctions (foo, YES);

  /* Temporarily disable WARNs */
  tmpWarns = _print3VILWarns;
  _print3VILWarns = NO;

  /* First, check if this is an analytic case: */
  TVIL_SetArguments (foo);

  if (_doAnalytic == YES &&
      (isAnalytic = TVIL_CaseSpecial (foo)) == YES) {

    /* In this case, it was analytic and we are done with evaluating
       the main functions... */
    _status = ANALYTIC;
  }
  /* Otherwise check if one of the 3-scale cases: */
  else if (TVIL_IsThreeScaleCase (&whichOne, &whichPerm) &&
	   (_forceDefault != YES)) {

    /* printf ("(* This is a 3-scale case: "); */
    /* if      (whichOne == THREESCALE_A) printf ("A *)"); */
    /* else if (whichOne == THREESCALE_B) printf ("B"); */
    /* else if (whichOne == THREESCALE_C) printf ("C"); */
    /* printf("\n"); */
    /* printf("(* The needed permutation is %d *)\n", whichPerm); */

    _evalMode = whichOne;

    TVIL_PermuteArgs (_arglist, whichPerm, _arglist);

    /* Reset everything in the structs, too: */
    foo->u = _u = _arglist[0];
    foo->v = _v = _arglist[1];
    foo->w = _w = _arglist[2];
    foo->x = _x = _arglist[3];
    foo->y = _y = _arglist[4];
    foo->z = _z = _arglist[5];
    TVIL_SetArguments (foo);

    TVIL_IntegrateAllFunctions (foo, NO);
    TVIL_CaseGeneric_3s ();
  }
  /* If we get here, then generic evaluation */
  else {
    TVIL_IntegrateAllFunctions (foo, YES);
    TVIL_CaseGeneric ();
  }

  /* The following puts in the analytic results for I, FBAR, G, and H,
     if available. However, leaving it out allows debugging of the RK
     evaluation of analytic cases, which is quite useful. But no need
     to re-do it if the case was already evaluated analytically. */
  if (_doAnalytic && !isAnalytic)
    TVIL_CaseSpecial (foo);

  /* Set additional functions: */
  TVIL_SetAllEs (foo);
  TVIL_SetBold (foo);

  /* Now everything should be all set in the function
     structs. Transfer the results back to foo... */
  for (i=0; i<NUM_I_FUNCS; i++) {
    foo->II[i] = _II[i].value;
    for (j=0; j<3; j++)
      foo->IIbold[i][j] = _II[i].bold[j];
  }
  for (i=0; i<NUM_F_FUNCS; i++) {
    foo->FBAR[i] = _FBAR[i].value;
    foo->F[i] = _FBAR[i].fValue;
    for (j=0; j<4; j++)
      foo->Fbold[i][j] = _FBAR[i].boldF[j];
  }
  for (i=0; i<NUM_E_FUNCS; i++) {
    foo->E[i] = _E[i].value;
    for (j=0; j<4; j++)
      foo->Ebold[i][j] = _E[i].bold[j];
  }
  for (i=0; i<NUM_G_FUNCS; i++) {
    foo->G[i] = _G[i].value;
    for (j=0; j<4; j++)
      foo->Gbold[i][j] = _G[i].bold[j];
  }
  foo->H = _H.value;
  for (j=0; j<2; j++)
    foo->Hbold[j] = _H.bold[j];

  if (_evalMode == THREESCALE_A ||
      _evalMode == THREESCALE_B ||
      _evalMode == THREESCALE_C)
    TVIL_PermuteResult (foo, -whichPerm, foo);

  /* Set status indicators in struct: */
  foo->status = _status;
  foo->evalMode = _evalMode;

  /* Restore initial warning status */
  _print3VILWarns = tmpWarns;

  /* Implement status codes eventually */
  return _status;
}
