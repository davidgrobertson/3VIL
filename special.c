/* Analytic evaluations where possible. */

#include "internal.h"

/* ******************************************************************* */
/* This is now supposed to work as is for any case, including subset
   cases. The evaluate* arrays have been set to indicate the functions
   to be evaluated. */

int TVIL_CaseSpecial (TVIL_RESULT *foo)
{
  int success = 1;
  int i, tmpWarns;
  char funcname[] = "CaseSpecial";

  /* Temporarily disable WARNs */
  tmpWarns = _print3VILWarns;
  _print3VILWarns = NO;

  /* DGRDGR Could remove qq argument in these... */
  if (foo->evaluateH)
    success *= TVIL_AnalyticHTYPE (&_H, _qq);

  for (i=0; i<NUM_G_FUNCS; i++)
    if (foo->evaluateG[i])
      success *= TVIL_AnalyticGTYPE (&(_G[i]), _qq);

  for (i=0; i<NUM_F_FUNCS; i++)
    if (foo->evaluateFBAR[i])
      success *= TVIL_AnalyticFBARTYPE (&(_FBAR[i]), _qq);

  for (i=0; i<NUM_I_FUNCS; i++)
    if (foo->evaluateII[i])
      success *= TVIL_AnalyticITYPE (&(_II[i]), _qq);

  /* Don't need this: H has already been evaluated any time we
     call this routine, or else it is already known not to be
     analytic. */
  /* success *= TVIL_AnalyticHTYPE (&(foo->H), foo->qq); */

  /* Restore previous warnings setting: */
  _print3VILWarns = tmpWarns;

  return success;
}
