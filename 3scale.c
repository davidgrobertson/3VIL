/* 
   Code for detecting 3-scale cases:
   00yzxx (A)
   0xxyzy (B)
   0xyxzy (C)
*/

#include "internal.h"

/* **************************************************************** */

int TVIL_NumZeroArgs (void)
{
  int i, num = 0;

  for (i=0; i<6; i++) {
    if (SAME2 (_arglist[i], 0))
      num++;
  }

  return num;
}

/* **************************************************************** */
/* Detects the presence of a 3-scale case, and returns which case it
   is, and the the perm needed to get to the standard argument
   ordering. */

int TVIL_IsThreeScaleCase (int *which, int *perm)
{
  TVIL_REAL test[6];
  int i;
  int numZeros = TVIL_NumZeroArgs ();

  /* In this case, definitely not: */
  if (numZeros < 1 || numZeros > 2)
    return NO;

  if (numZeros == 1) {

    for (i=0; i<24; i++) {
      TVIL_PermuteArgs (_arglist, i, test);

      if (SAME2 (test[0], 0) && SAME2 (test[1], test[2]) && SAME2 (test[3], test[5])) {
	/* We have case B */
	*which = THREESCALE_B;
	*perm = i;
	return YES;
      }
      else if (SAME2 (test[0], 0) && SAME2 (test[1], test[3]) && SAME2 (test[2], test[5])) {
	/* We have case C */
	*which = THREESCALE_C;
	*perm = i;
	return YES;
      }
    }
  }
  else {
    /* numZeros is 2, so maybe case A */
    for (i=0; i<24; i++) {
      TVIL_PermuteArgs (_arglist, i, test);

      if (SAME3 (test[0], test[1], 0) && SAME2 (test[4], test[5])) {
	/* We have case A */
	*which = THREESCALE_A;
	*perm = i;
	return YES;
      }
    }
  }
  return NO;
}

/* **************************************************************** */
/* Just a dumb interface routine... */

void TVIL_CaseGeneric_3s (void)
{
  if      (_evalMode == THREESCALE_A) TVIL_CaseGeneric_3sA ();
  else if (_evalMode == THREESCALE_B) TVIL_CaseGeneric_3sB ();
  else if (_evalMode == THREESCALE_C) TVIL_CaseGeneric_3sC ();
  else
    TVIL_Error ("CaseGeneric_3s", "This can't happen!", 636);
}

