/*   === sample.c ===
 *
 *   Sample code for calculation of all 3-loop vacuum basis integrals with 
 *   (u, v, w, x, y, z) = (t, t, b, h, W, W) at the renormalization scale
 *   Q = 150 GeV.
 *
 *   To compile:
 *
 *   cc -o sample sample.c -L<dir> -l3vil -lm
 *
 *   where <dir> is the directory containing lib3vil.a. 
 *
 *    Run as: ./sample
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
  int j;

  TVIL_REAL t = mt*mt;
  TVIL_REAL h = mh*mh;
  TVIL_REAL W = mW*mW;
  TVIL_REAL b = mb*mb;
  TVIL_REAL Q2 = Q*Q;

  /* These are the finite (non-bold-faced) basis integrals. */
  TVIL_REAL H_ttbhWW;
  TVIL_REAL G_btWtW, G_httWW, G_tthbW, G_WtbhW;
  TVIL_REAL E_tbhW, E_ttWW;
  TVIL_REAL F_bthW, F_htbW, F_tbhW, F_Wtbh, F_ttWW, F_WWtt;
  TVIL_REAL FBAR_bthW, FBAR_htbW, FBAR_tbhW, FBAR_Wtbh, FBAR_ttWW, FBAR_WWtt;
  TVIL_REAL I_tth, I_hWW, I_thW, I_tbW, I_tWW, I_bhW, I_ttW, I_tbh;
  TVIL_REAL A_t, A_b, A_h, A_W;

  /* These are the bold-faced basis integrals, expanded in epsilon,
     with the array element n=0,1,2,3 corresponding to the term with 
     1/epsilon^n. */
  TVIL_REAL HH_ttbhWW[2];
  TVIL_REAL GG_btWtW[4], GG_httWW[4], GG_tthbW[4], GG_WtbhW[4];
  TVIL_REAL EE_tbhW[4], EE_ttWW[4];
  TVIL_REAL FF_bthW[4], FF_htbW[4], FF_tbhW[4], FF_Wtbh[4], 
            FF_ttWW[4], FF_WWtt[4];

  TVIL_REAL I2_tth, I2_hWW, I2_thW, I2_tbW, I2_tWW, I2_bhW, I2_ttW, I2_tbh;
  TVIL_REAL I1_tth, I1_hWW, I1_thW, I1_tbW, I1_tWW, I1_bhW, I1_ttW, I1_tbh;
  TVIL_REAL I0_tth, I0_hWW, I0_thW, I0_tbW, I0_tWW, I0_bhW, I0_ttW, I0_tbh;
  TVIL_REAL Ieps_tth, Ieps_hWW, Ieps_thW, Ieps_tbW, Ieps_tWW, Ieps_bhW, 
            Ieps_ttW, Ieps_tbh;

  TVIL_REAL Aeps_t, Aeps_b, Aeps_h, Aeps_W;
  TVIL_REAL Aeps2_t, Aeps2_b, Aeps2_h, Aeps2_W;

  /* Set the parameters and evaluate all of the integrals: */

  TVIL_Evaluate (t, t, b, h, W, W, Q2, &result);

  /* Read the integral results from the result struct into 
     real long double variables: */

  H_ttbhWW = TVIL_CREAL(TVIL_GetFunction (&result, "H"));

  G_btWtW  = TVIL_CREAL(TVIL_GetFunction (&result, "Gwuzvy"));
  G_httWW  = TVIL_CREAL(TVIL_GetFunction (&result, "Gxuvyz"));
  G_tthbW  = TVIL_CREAL(TVIL_GetFunction (&result, "Guvxwz"));
  G_WtbhW  = TVIL_CREAL(TVIL_GetFunction (&result, "Gyvwxz"));

  FBAR_bthW = TVIL_CREAL(TVIL_GetFunction (&result, "FBARwuxy"));
  FBAR_htbW = TVIL_CREAL(TVIL_GetFunction (&result, "FBARxuwy"));
  FBAR_tbhW = TVIL_CREAL(TVIL_GetFunction (&result, "FBARuwxy"));
  FBAR_Wtbh = TVIL_CREAL(TVIL_GetFunction (&result, "FBARyuwx"));
  FBAR_ttWW = TVIL_CREAL(TVIL_GetFunction (&result, "FBARuvyz"));
  FBAR_WWtt = TVIL_CREAL(TVIL_GetFunction (&result, "FBARyuvz"));

  F_bthW = TVIL_CREAL(TVIL_GetFunction (&result, "Fwuxy"));
  F_htbW = TVIL_CREAL(TVIL_GetFunction (&result, "Fxuwy"));
  F_tbhW = TVIL_CREAL(TVIL_GetFunction (&result, "Fuwxy"));
  F_Wtbh = TVIL_CREAL(TVIL_GetFunction (&result, "Fyuwx"));
  F_ttWW = TVIL_CREAL(TVIL_GetFunction (&result, "Fuvyz"));
  F_WWtt = TVIL_CREAL(TVIL_GetFunction (&result, "Fyuvz"));

  E_tbhW = TVIL_CREAL(TVIL_GetFunction (&result, "Euwxy"));
  E_ttWW = TVIL_CREAL(TVIL_GetFunction (&result, "Euvyz"));

  I_tth = TVIL_CREAL(TVIL_GetFunction (&result, "Iuvx"));
  I_hWW = TVIL_CREAL(TVIL_GetFunction (&result, "Ixyz"));
  I_thW = TVIL_CREAL(TVIL_GetFunction (&result, "Iuxy"));
  I_tbW = TVIL_CREAL(TVIL_GetFunction (&result, "Iuwy"));
  I_tWW = TVIL_CREAL(TVIL_GetFunction (&result, "Iuyz"));
  I_bhW = TVIL_CREAL(TVIL_GetFunction (&result, "Iwxy"));
  I_ttW = TVIL_CREAL(TVIL_GetFunction (&result, "Iuvy"));
  I_tbh = TVIL_CREAL(TVIL_GetFunction (&result, "Iuwx"));

  I2_tth = TVIL_CREAL(TVIL_II2(t,t,h,Q2));
  I2_hWW = TVIL_CREAL(TVIL_II2(h,W,W,Q2));
  I2_thW = TVIL_CREAL(TVIL_II2(t,h,W,Q2));
  I2_tbW = TVIL_CREAL(TVIL_II2(t,b,W,Q2));
  I2_tWW = TVIL_CREAL(TVIL_II2(t,W,W,Q2));
  I2_bhW = TVIL_CREAL(TVIL_II2(b,h,W,Q2));
  I2_ttW = TVIL_CREAL(TVIL_II2(t,t,W,Q2));
  I2_tbh = TVIL_CREAL(TVIL_II2(t,b,h,Q2));

  I1_tth = TVIL_CREAL(TVIL_II1(t,t,h,Q2));
  I1_hWW = TVIL_CREAL(TVIL_II1(h,W,W,Q2));
  I1_thW = TVIL_CREAL(TVIL_II1(t,h,W,Q2));
  I1_tbW = TVIL_CREAL(TVIL_II1(t,b,W,Q2));
  I1_tWW = TVIL_CREAL(TVIL_II1(t,W,W,Q2));
  I1_bhW = TVIL_CREAL(TVIL_II1(b,h,W,Q2));
  I1_ttW = TVIL_CREAL(TVIL_II1(t,t,W,Q2));
  I1_tbh = TVIL_CREAL(TVIL_II1(t,b,h,Q2));

  I0_tth = TVIL_CREAL(TVIL_II0(t,t,h,Q2));
  I0_hWW = TVIL_CREAL(TVIL_II0(h,W,W,Q2));
  I0_thW = TVIL_CREAL(TVIL_II0(t,h,W,Q2));
  I0_tbW = TVIL_CREAL(TVIL_II0(t,b,W,Q2));
  I0_tWW = TVIL_CREAL(TVIL_II0(t,W,W,Q2));
  I0_bhW = TVIL_CREAL(TVIL_II0(b,h,W,Q2));
  I0_ttW = TVIL_CREAL(TVIL_II0(t,t,W,Q2));
  I0_tbh = TVIL_CREAL(TVIL_II0(t,b,h,Q2));

  Ieps_tth = TVIL_CREAL(TVIL_Ieps(t,t,h,Q2));
  Ieps_hWW = TVIL_CREAL(TVIL_Ieps(h,W,W,Q2));
  Ieps_thW = TVIL_CREAL(TVIL_Ieps(t,h,W,Q2));
  Ieps_tbW = TVIL_CREAL(TVIL_Ieps(t,b,W,Q2));
  Ieps_tWW = TVIL_CREAL(TVIL_Ieps(t,W,W,Q2));
  Ieps_bhW = TVIL_CREAL(TVIL_Ieps(b,h,W,Q2));
  Ieps_ttW = TVIL_CREAL(TVIL_Ieps(t,t,W,Q2));
  Ieps_tbh = TVIL_CREAL(TVIL_Ieps(t,b,h,Q2));

  A_t = TVIL_CREAL(TVIL_A(t,Q2));
  A_b = TVIL_CREAL(TVIL_A(b,Q2));
  A_h = TVIL_CREAL(TVIL_A(h,Q2));
  A_W = TVIL_CREAL(TVIL_A(W,Q2));

  Aeps_t = TVIL_CREAL(TVIL_Aeps(t,Q2));
  Aeps_b = TVIL_CREAL(TVIL_Aeps(b,Q2));
  Aeps_h = TVIL_CREAL(TVIL_Aeps(h,Q2));
  Aeps_W = TVIL_CREAL(TVIL_Aeps(W,Q2));

  Aeps2_t = TVIL_CREAL(TVIL_Aeps2(t,Q2));
  Aeps2_b = TVIL_CREAL(TVIL_Aeps2(b,Q2));
  Aeps2_h = TVIL_CREAL(TVIL_Aeps2(h,Q2));
  Aeps2_W = TVIL_CREAL(TVIL_Aeps2(W,Q2));

  for (j=0; j<4; j++) {
    EE_tbhW[j] = TVIL_CREAL(TVIL_GetBoldFunction (&result, "Euwxy", j));
    EE_ttWW[j] = TVIL_CREAL(TVIL_GetBoldFunction (&result, "Euvyz", j));

    FF_bthW[j] = TVIL_CREAL(TVIL_GetBoldFunction (&result, "Fwuxy", j));
    FF_htbW[j] = TVIL_CREAL(TVIL_GetBoldFunction (&result, "Fxuwy", j));
    FF_tbhW[j] = TVIL_CREAL(TVIL_GetBoldFunction (&result, "Fuwxy", j));
    FF_Wtbh[j] = TVIL_CREAL(TVIL_GetBoldFunction (&result, "Fyuwx", j));
    FF_ttWW[j] = TVIL_CREAL(TVIL_GetBoldFunction (&result, "Fuvyz", j));
    FF_WWtt[j] = TVIL_CREAL(TVIL_GetBoldFunction (&result, "Fyuvz", j));

    GG_btWtW[j]  = TVIL_CREAL(TVIL_GetBoldFunction (&result, "Gwuzvy", j));
    GG_httWW[j]  = TVIL_CREAL(TVIL_GetBoldFunction (&result, "Gxuvyz", j));
    GG_tthbW[j]  = TVIL_CREAL(TVIL_GetBoldFunction (&result, "Guvxwz", j));
    GG_WtbhW[j]  = TVIL_CREAL(TVIL_GetBoldFunction (&result, "Gyvwxz", j));
  }

  for (j=0; j<2; j++) {
    HH_ttbhWW[j] = TVIL_CREAL(TVIL_GetBoldFunction (&result, "H", j));
  }


  /* Now print out all of the above results. */
  
  printf("\nResults for:\n");
  printf("  Mt = %10.8lf\n",(double) mt);
  printf("  Mb = %10.8lf\n",(double) mb);
  printf("  Mh = %10.8lf\n",(double) mh);
  printf("  MW = %10.8lf\n",(double) mW);
  printf("   Q = %10.8lf\n\n",(double) Q);

  printf("Expansions of the bold-faced integrals:\n\n");

  printf("Aeps[t]        = %12.10lf;\n", (double) Aeps_t);
  printf("Aeps2[t]       = %12.10lf;\n", (double) Aeps2_t);

  printf("\n");

  printf("Aeps[b]        = %12.10lf;\n", (double) Aeps_b);
  printf("Aeps2[b]       = %12.10lf;\n", (double) Aeps2_b);

  printf("\n");

  printf("Aeps[h]        = %12.10lf;\n", (double) Aeps_h);
  printf("Aeps2[h]       = %12.10lf;\n", (double) Aeps2_h);

  printf("\n");

  printf("Aeps[W]        = %12.10lf;\n", (double) Aeps_W);
  printf("Aeps2[W]       = %12.10lf;\n", (double) Aeps2_W);

  printf("\n");

  printf("I2[t,t,h]      = %12.10lf;\n", (double) I2_tth);
  printf("I1[t,t,h]      = %12.10lf;\n", (double) I1_tth);
  printf("I0[t,t,h]      = %12.10lf;\n", (double) I0_tth);
  printf("Ieps[t,t,h]    = %12.10lf;\n", (double) Ieps_tth);

  printf("\n");

  printf("I2[h,W,W]      = %12.10lf;\n", (double) I2_hWW);
  printf("I1[h,W,W]      = %12.10lf;\n", (double) I1_hWW);
  printf("I0[h,W,W]      = %12.10lf;\n", (double) I0_hWW);
  printf("Ieps[h,W,W]    = %12.10lf;\n", (double) Ieps_hWW);

  printf("\n");

  printf("I2[t,h,W]      = %12.10lf;\n", (double) I2_thW);
  printf("I1[t,h,W]      = %12.10lf;\n", (double) I1_thW);
  printf("I0[t,h,W]      = %12.10lf;\n", (double) I0_thW);
  printf("Ieps[t,h,W]    = %12.10lf;\n", (double) Ieps_thW);

  printf("\n");

  printf("I2[t,b,W]      = %12.10lf;\n", (double) I2_tbW);
  printf("I1[t,b,W]      = %12.10lf;\n", (double) I1_tbW);
  printf("I0[t,b,W]      = %12.10lf;\n", (double) I0_tbW);
  printf("Ieps[t,b,W]    = %12.10lf;\n", (double) Ieps_tbW);

  printf("\n");

  printf("I2[t,W,W]      = %12.10lf;\n", (double) I2_tWW);
  printf("I1[t,W,W]      = %12.10lf;\n", (double) I1_tWW);
  printf("I0[t,W,W]      = %12.10lf;\n", (double) I0_tWW);
  printf("Ieps[t,W,W]    = %12.10lf;\n", (double) Ieps_tWW);

  printf("\n");

  printf("I2[b,h,W]      = %12.10lf;\n", (double) I2_bhW);
  printf("I1[b,h,W]      = %12.10lf;\n", (double) I1_bhW);
  printf("I0[b,h,W]      = %12.10lf;\n", (double) I0_bhW);
  printf("Ieps[b,h,W]    = %12.10lf;\n", (double) Ieps_bhW);

  printf("\n");

  printf("I2[t,t,W]      = %12.10lf;\n", (double) I2_ttW);
  printf("I1[t,t,W]      = %12.10lf;\n", (double) I1_ttW);
  printf("I0[t,t,W]      = %12.10lf;\n", (double) I0_ttW);
  printf("Ieps[t,t,W]    = %12.10lf;\n", (double) Ieps_ttW);

  printf("\n");

  printf("I2[t,b,h]      = %12.10lf;\n", (double) I2_tbh);
  printf("I1[t,b,h]      = %12.10lf;\n", (double) I1_tbh);
  printf("I0[t,b,h]      = %12.10lf;\n", (double) I0_tbh);
  printf("Ieps[t,b,h]    = %12.10lf;\n", (double) Ieps_tbh);

  printf("\n");

  for (j=0; j<4; j++) {
    printf("E%d[t,b,h,W]     = %12.10lf;\n", j, (double) EE_tbhW[j]);
  }

  printf("\n");

  for (j=0; j<4; j++) {
    printf("E%d[t,t,W,W]     = %12.10lf;\n", j, (double) EE_ttWW[j]);
  }

  printf("\n");

  for (j=0; j<4; j++) {
    printf("F%d[b,t,h,W]     = %12.10lf;\n", j, (double) FF_bthW[j]);
  }

  printf("\n");

  for (j=0; j<4; j++) {
    printf("F%d[h,t,b,W]     = %12.10lf;\n", j, (double) FF_htbW[j]);
  }

  printf("\n");

  for (j=0; j<4; j++) {
    printf("F%d[t,b,h,W]     = %12.10lf;\n", j, (double) FF_tbhW[j]);
  }

  printf("\n");

  for (j=0; j<4; j++) {
    printf("F%d[W,t,b,h]     = %12.10lf;\n", j, (double) FF_Wtbh[j]);
  }

  printf("\n");

  for (j=0; j<4; j++) {
    printf("F%d[t,t,W,W]     = %12.10lf;\n", j, (double) FF_ttWW[j]);
  }

  printf("\n");

  for (j=0; j<4; j++) {
    printf("F%d[W,W,t,t]     = %12.10lf;\n", j, (double) FF_WWtt[j]);
  }

  printf("\n");

  for (j=0; j<4; j++) {
    printf("G%d[b,t,W,t,W]   = %12.10lf;\n", j, (double) GG_btWtW[j]);
  }

  printf("\n");

  for (j=0; j<4; j++) {
    printf("G%d[h,t,t,W,W    = %12.10lf;\n", j, (double) GG_httWW[j]);
  }

  printf("\n");

  for (j=0; j<4; j++) {
    printf("G%d[t,t,h,b,W]   = %12.10lf;\n", j, (double) GG_tthbW[j]);
  }

  printf("\n");

  for (j=0; j<4; j++) {
    printf("G%d[W,t,b,h,W]   = %12.10lf;\n", j, (double) GG_WtbhW[j]);
  }

  printf("\n");

  for (j=0; j<2; j++) {
    printf("H%d[t,t,b,h,W,W] = %12.10lf;\n", j, (double) HH_ttbhWW[j]);
  }

  printf("\n\n");

  printf("The finite basis integrals:\n\n");

  printf("A[t]           = %12.10lf;\n", (double) A_t);
  printf("A[b]           = %12.10lf;\n", (double) A_b);
  printf("A[h]           = %12.10lf;\n", (double) A_h);
  printf("A[W]           = %12.10lf;\n", (double) A_W);

  printf("\n");

  printf("I[t,t,h]       = %12.10lf;\n", (double) I_tth);
  printf("I[h,W,W]       = %12.10lf;\n", (double) I_hWW);
  printf("I[t,h,W]       = %12.10lf;\n", (double) I_thW);
  printf("I[t,b,W]       = %12.10lf;\n", (double) I_tbW);
  printf("I[t,W,W]       = %12.10lf;\n", (double) I_tWW);
  printf("I[b,h,W]       = %12.10lf;\n", (double) I_bhW);
  printf("I[t,t,W]       = %12.10lf;\n", (double) I_ttW);
  printf("I[t,b,h]       = %12.10lf;\n", (double) I_tbh);

  printf("\n");

  printf("E[t,b,h,W]     = %12.10lf;\n", (double) E_tbhW);
  printf("E[t,t,W,W]     = %12.10lf;\n", (double) E_ttWW);

  printf("\n");

  printf("F[b,t,h,W]     = %12.10lf;\n", (double) F_bthW);
  printf("F[h,t,b,W]     = %12.10lf;\n", (double) F_htbW);
  printf("F[t,b,h,W]     = %12.10lf;\n", (double) F_tbhW);
  printf("F[W,t,b,h]     = %12.10lf;\n", (double) F_Wtbh);
  printf("F[t,t,W,W]     = %12.10lf;\n", (double) F_ttWW);
  printf("F[W,W,t,t]     = %12.10lf;\n", (double) F_WWtt);

  printf("\n");

  printf("FBAR[b,t,h,W]  = %12.10lf;\n", (double) FBAR_bthW);
  printf("FBAR[h,t,b,W]  = %12.10lf;\n", (double) FBAR_htbW);
  printf("FBAR[t,b,h,W]  = %12.10lf;\n", (double) FBAR_tbhW);
  printf("FBAR[W,t,b,h]  = %12.10lf;\n", (double) FBAR_Wtbh);
  printf("FBAR[t,t,W,W]  = %12.10lf;\n", (double) FBAR_ttWW);
  printf("FBAR[W,W,t,t]  = %12.10lf;\n", (double) FBAR_WWtt);

  printf("\n");

  printf("G[b,t,W,t,W]   = %12.10lf;\n", (double) G_btWtW);
  printf("G[h,t,t,W,W]   = %12.10lf;\n", (double) G_httWW);
  printf("G[t,t,h,b,W]   = %12.10lf;\n", (double) G_tthbW);
  printf("G[W,t,b,h,W]   = %12.10lf;\n", (double) G_WtbhW);

  printf("\n");

  printf("H[t,t,b,h,W,W] = %12.10lf;\n", (double) H_ttbhWW);

  printf("\n");

  return 0;
} 
