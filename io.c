/* I/O functions */

#include "internal.h"
#include <string.h>

/* ******************************************************************* */
/* Generic printing of complexes                                       */

void TVIL_cprintf (TVIL_COMPLEX z)
{
  TVIL_cfprintf (stdout, (double complex) z);
  return;
}

/* ******************************************************************* */
/* Generic printing of complexes                                       */

void TVIL_cfprintf (FILE *fp, TVIL_COMPLEX z)
{
  TVIL_REAL log10z, temp;
  int rightdigits; /* Number of digits to right of decimal. */
  char zformat[21]; /* Format for z */

  if (TVIL_IsInfinite (z)) {
    fprintf(fp, " ComplexInfinity");
    if (_printStyle == MATH)
      fprintf(fp, ";");
  }
  else {
    log10z = TVIL_LOG(TVIL_FABS(creal(z)));
    temp = TVIL_LOG(TVIL_FABS(cimag(z)));
    if (temp > log10z) log10z = temp;
    log10z *= 0.43429448190325176L;
    rightdigits = 17 - ceil (log10z);
    if (rightdigits > 16) rightdigits = 16;
    if (rightdigits < 1) rightdigits = 1;

    if (_printStyle == MATH)
      sprintf(zformat, "%% .%dlf + %% .%dlf I;",rightdigits,rightdigits);
    else
      sprintf(zformat, "%% .%dlf, %% .%dlf",rightdigits,rightdigits);

  /* UNCOMMENT FOLLOWING THREE LINES ONLY WHEN CREATING TestData FILES! 
  sprintf(zformat, "%% .%dlf + 0.0 I;",rightdigits);
  fprintf(fp, zformat, creal(z));
  return;
  */

    fprintf(fp, zformat, creal(z), cimag(z));
  }

  return;
}

/* ******************************************************************* */

void TVIL_PrintData (TVIL_RESULT *foo)
{
  TVIL_WriteData (stdout, foo);
  return;
}

/* ******************************************************************* */

void TVIL_WriteData (FILE *fp, TVIL_RESULT *foo)
{
#include "3vil_names.h"

  int i, j;
  char rformat[20];

  if (foo->status == UNEVALUATED) {
    TVIL_Warn ("Write/PrintDataM",
	       "This case has not yet been evaluated!");
    return;
  }

  if (_printStyle == MATH)
    sprintf(rformat, "%%.12Lf;\n");
  else
    sprintf(rformat, "%%.12Lf\n");

  /* fprintf(fp, "u  = "); fprintf(fp, rformat, (long double) (foo->u)); */
  /* fprintf(fp, "v  = "); fprintf(fp, rformat, (long double) (foo->v)); */
  /* fprintf(fp, "w  = "); fprintf(fp, rformat, (long double) (foo->w)); */
  /* fprintf(fp, "x  = "); fprintf(fp, rformat, (long double) (foo->x)); */
  /* fprintf(fp, "y  = "); fprintf(fp, rformat, (long double) (foo->y)); */
  /* fprintf(fp, "z  = "); fprintf(fp, rformat, (long double) (foo->z));  */
  /* fprintf(fp, "qq = "); fprintf(fp, rformat, (long double) (foo->qq)); */

  fprintf(fp, "u  = "); fprintf(fp, rformat, (long double) (foo->u));
  if (foo->evalMode != EF) {
    fprintf(fp, "v  = "); fprintf(fp, rformat, (long double) (foo->v));
  }
  fprintf(fp, "w  = "); fprintf(fp, rformat, (long double) (foo->w));
  fprintf(fp, "x  = "); fprintf(fp, rformat, (long double) (foo->x));
  fprintf(fp, "y  = "); fprintf(fp, rformat, (long double) (foo->y));
  if (foo->evalMode != EF && foo->evalMode != EFG) {
    fprintf(fp, "z  = "); fprintf(fp, rformat, (long double) (foo->z));
  }
  fprintf(fp, "qq = "); fprintf(fp, rformat, (long double) (foo->qq));

  if (_printBold) {
    fprintf(fp, "\n");
    fprintf(fp, "(* Bold Functions: *)\n");

    for (j=0; j<NUM_E_FUNCS; j++) {
      if (foo->evaluateE[j]) {
	for (i=0; i<4; i++) {
	  fprintf(fp, "%s[%d]  = ", ename[j][0], i);
	  TVIL_cprintf (foo->Ebold[j][i]); fprintf(fp, "\n");
	}
	fprintf(fp, "\n");
      }
    }

    if (foo->nFBARfuns) printf("\n");
    for (j=0; j<NUM_F_FUNCS; j++) {
      if (foo->evaluateFBAR[j]) {
	for (i=0; i<4; i++) {
	  fprintf(fp, "%s[%d] = ", fname[j][0], i);
	  TVIL_cprintf (foo->Fbold[j][i]); fprintf(fp, "\n");
	}
	fprintf(fp, "\n");
      }
    }

    if (foo->nGfuns)  printf("\n");
    for (j=0; j<NUM_G_FUNCS; j++) {
      if (foo->evaluateG[j]) {
	for (i=0; i<4; i++) {
	  fprintf(fp, "%s[%d]   = ", gname[j][0], i);
	  /* DGRDGR figure out how to trap this eventually... */
	  /* if (i == 0 && foo->G[j]->hasNegativeArg) */
	  /*   printf("Not yet implemented for negative mass^2 arguments!\n"); */
	  /* else */
	  {TVIL_cprintf (foo->Gbold[j][i]); fprintf(fp, "\n");}
	}
	fprintf(fp, "\n");
      }
    }

    if (foo->evaluateH) printf("\n");
    for (i=0; i<2; i++) {
      fprintf(fp, "Huvwxyz[%d]  = ", i);
      TVIL_cprintf (foo->Hbold[i]); fprintf(fp, "\n");
    }
  }

  fprintf(fp, "\n");
  fprintf(fp, "(* Basis Functions: *)\n");

  for (j=0; j<NUM_I_FUNCS; j++) {
    if (foo->evaluateII[j]) {
      fprintf(fp, "%s     = ", iname[j][0]);
      TVIL_cprintf (foo->II[j]); fprintf(fp, "\n");
    }
  }
  if (foo->nEfuns) fprintf(fp, "\n");
  for (j=0; j<NUM_E_FUNCS; j++) {
    if (foo->evaluateE[j]) {
      fprintf(fp, "%s    = ", ename[j][0]);
      TVIL_cprintf (foo->E[j]); fprintf(fp, "\n");
    }
  }
  if (foo->nFBARfuns) fprintf(fp, "\n");
  for (j=0; j<NUM_F_FUNCS; j++) {
    if (foo->evaluateFBAR[j]) {
      fprintf(fp, "%s    = ", fname[j][0]);
      TVIL_cprintf (foo->F[j]); fprintf(fp, "\n");
    }
  }
  if (foo->nFBARfuns) fprintf(fp, "\n");
  for (j=0; j<NUM_F_FUNCS; j++) {
    if (foo->evaluateFBAR[j]) {
      fprintf(fp, "%s = ", fbarname[j][0]);
      TVIL_cprintf (foo->FBAR[j]); fprintf(fp, "\n");
    }
  }
  if (foo->nGfuns) fprintf(fp, "\n");
  for (j=0; j<NUM_G_FUNCS; j++) {
    if (foo->evaluateG[j]) {
      fprintf(fp, "%s   = ", gname[j][0]);
      TVIL_cprintf (foo->G[j]); fprintf(fp, "\n");
    }
  }
  if (foo->evaluateH) {
    fprintf(fp, "\n");
    fprintf(fp, "Huvwxyz  = ");
    TVIL_cprintf (foo->H); fprintf(fp, "\n");
  }

  return;
}

/* ******************************************************************* */

int TVIL_GetStatus (TVIL_RESULT *foo)
{
  return foo->status;
}

/* ******************************************************************* */
/* Prints the evaluation status of the specified data object: whether
   unevaluated, or evaluaed analytically, numerically by integration
   along the real s axis, or numerically by integration along the
   displaced contour. */

void TVIL_PrintStatus (TVIL_RESULT *foo)
{
  if (foo->status == UNEVALUATED)
    TVIL_Warn("TVIL_PrintStatus", "Functions not yet evaluated!");
  else {
    if (foo->evalMode == THREESCALE_A)
      printf("(* 3-scale evaluation mode A. *)\n");
    if (foo->evalMode == THREESCALE_B)
      printf("(* 3-scale evaluation mode B. *)\n");
    if (foo->evalMode == THREESCALE_C)
      printf("(* 3-scale evaluation mode C. *)\n");

    printf("(* Evaluation method: ");
    if (foo->status == ANALYTIC)
      printf("Analytic");
    else if (foo->status == REAXIS)
      printf("Integration along real t-axis");
    else if (foo->status == CONTOUR)
      printf("Integration along displaced contour");
    printf(" *)\n");

    if (foo->poleAt1 && foo->status != ANALYTIC)
      printf("(* Pole at or near t = 1 *)\n");
    
    if (foo->status != ANALYTIC && 
	foo->evalMode != THREESCALE_A &&
	foo->evalMode != THREESCALE_B &&
	foo->evalMode != THREESCALE_C)
      printf("(* a = %Lf *)\n", _a);
  }
  return;
}

/* ******************************************************************* */

void TVIL_PrintVersion (void)
{
  printf("(* 3VIL Version: %s *)\n", TVIL_VERSION);
  return;
}

/* ******************************************************************* */
