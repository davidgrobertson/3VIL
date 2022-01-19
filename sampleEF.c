/*   === sampleEF.c ===
 *
 *   Sample code for calculation of the EF subset of 3-loop vacuum
 *   basis integrals with (u, w, x, y) = (t, b, h, W) at the
 *   renormalization scale Q = 150 GeV.
 *
 *   To compile:
 *
 *   gcc -o sampleEF sampleEF.c -L<dir> -l3vil -lm
 *
 *   where <dir> is the directory containing lib3vil.a. 
 *
 *   Run as: ./sampleEF
 */

#include <stdio.h>
#include "3vil.h"  /* Required 3VIL header file */

#define mt 173.
#define mb 5.
#define mW 80.
#define mh 125.
#define Q 150.

int main (int argc, char *argv[])
{
  TVIL_RESULT result; /* Top-level 3VIL data object */

  TVIL_REAL t = mt*mt;
  TVIL_REAL h = mh*mh;
  TVIL_REAL W = mW*mW;
  TVIL_REAL b = mb*mb;
  TVIL_REAL Q2 = Q*Q;

  /* These are the finite (non-bold-faced) basis integrals. */
  TVIL_REAL E_tbhW;
  TVIL_REAL F_bthW, F_htbW, F_tbhW, F_Wtbh;
  TVIL_REAL FBAR_bthW, FBAR_htbW, FBAR_tbhW, FBAR_Wtbh;
  TVIL_REAL I_thW, I_tbW, I_bhW, I_ttW, I_tbh;
  /* TVIL_REAL H_ttbhWW; */

  /* Evaluate all integrals for this subset: */

  TVIL_EvaluateEF (t, b, h, W, Q2, &result);

  /* Read the integral results from the result struct into real long
     double variables. For the EF subset, recall that only functions
     *not* involving the variables v or z are defined. */

  E_tbhW = TVIL_CREAL(TVIL_GetFunction (&result, "Ewuxy"));

  FBAR_bthW = TVIL_CREAL(TVIL_GetFunction (&result, "FBARwuxy"));
  FBAR_htbW = TVIL_CREAL(TVIL_GetFunction (&result, "FBARxuwy"));
  FBAR_tbhW = TVIL_CREAL(TVIL_GetFunction (&result, "FBARuwxy"));
  FBAR_Wtbh = TVIL_CREAL(TVIL_GetFunction (&result, "FBARyuwx"));

  F_bthW = TVIL_CREAL(TVIL_GetFunction (&result, "Fwuxy"));
  F_htbW = TVIL_CREAL(TVIL_GetFunction (&result, "Fxuwy"));
  F_tbhW = TVIL_CREAL(TVIL_GetFunction (&result, "Fuwxy"));
  F_Wtbh = TVIL_CREAL(TVIL_GetFunction (&result, "Fyuwx"));

  I_thW = TVIL_CREAL(TVIL_GetFunction (&result, "Iuxy"));
  I_tbW = TVIL_CREAL(TVIL_GetFunction (&result, "Iuwy"));
  I_bhW = TVIL_CREAL(TVIL_GetFunction (&result, "Iwxy"));
  I_tbh = TVIL_CREAL(TVIL_GetFunction (&result, "Iuwx"));

  /* Note that the following would produce an error since Huvwxyz is
     not defined for this subset: */
  /* H_ttbhWW = TVIL_CREAL(TVIL_GetFunction (&result, "H")); */

  /* Now print out all of the above results: */
  
  printf("\nResults for:\n");
  printf("  Mt = %10.8lf\n",(double) mt);
  printf("  Mb = %10.8lf\n",(double) mb);
  printf("  Mh = %10.8lf\n",(double) mh);
  printf("  MW = %10.8lf\n",(double) mW);
  printf("   Q = %10.8lf\n\n",(double) Q);

  /* printf("I[t,t,h]       = %12.10lf;\n", (double) I_tth); */
  printf("I[t,h,W]       = %12.10lf;\n", (double) I_thW);
  printf("I[t,b,W]       = %12.10lf;\n", (double) I_tbW);
  printf("I[b,h,W]       = %12.10lf;\n", (double) I_bhW);
  printf("I[t,b,h]       = %12.10lf;\n", (double) I_tbh);

  printf("\n");

  printf("E[t,b,h,W]     = %12.10lf;\n", (double) E_tbhW);

  printf("\n");

  printf("F[b,t,h,W]     = %12.10lf;\n", (double) F_bthW);
  printf("F[h,t,b,W]     = %12.10lf;\n", (double) F_htbW);
  printf("F[t,b,h,W]     = %12.10lf;\n", (double) F_tbhW);
  printf("F[W,t,b,h]     = %12.10lf;\n", (double) F_Wtbh);

  printf("\n");

  printf("FBAR[b,t,h,W]  = %12.10lf;\n", (double) FBAR_bthW);
  printf("FBAR[h,t,b,W]  = %12.10lf;\n", (double) FBAR_htbW);
  printf("FBAR[t,b,h,W]  = %12.10lf;\n", (double) FBAR_tbhW);
  printf("FBAR[W,t,b,h]  = %12.10lf;\n", (double) FBAR_Wtbh);

  /* Alternatively, TVIL_PrintData prints appropriate subset
     automatically: */
  printf("\nHere is the result of TVIL_PrintData:\n\n");
  TVIL_PrintData (&result);

  return 0;
}
