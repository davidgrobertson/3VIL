/*   === sample.cpp ===
 *
 *   Sample code for calculation of all 3-loop vacuum basis integrals with 
 *   (u, v, w, x, y, z) = (t, t, b, h, W, W) at the renormalization scale
 *   Q = 150 GeV.
 *
 *   To compile:
 *
 *   c++ -o samp sample.cpp -L<dir> -l3vil
 *
 *   where <dir> is the directory containing lib3vil.a. 
 *
 *    Run as: ./samp
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <complex>
#include <vector>
#include <cmath>
#include <cfloat>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "3vil_cpp.h"  /* Required 3VIL header file */

#define mt 173.
#define mb 5.
#define mW 80.
#define mh 125.
#define Q 150.

int main (int argc, char *argv[])
{
  TVIL_DATA result; /* Top-level 3VIL data object */
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
  TVIL_SetParameters_ (&result, t, t, b, h, W, W, Q2);
  TVIL_Evaluate_ (&result);

  /* Read the integral results from the result struct into 
     real long double variables: */
  H_ttbhWW = real(TVIL_GetFunction_ (&result, "H"));

  G_btWtW  = real(TVIL_GetFunction_ (&result, "Gwuzvy"));
  G_httWW  = real(TVIL_GetFunction_ (&result, "Gxuvyz"));
  G_tthbW  = real(TVIL_GetFunction_ (&result, "Guvxwz"));
  G_WtbhW  = real(TVIL_GetFunction_ (&result, "Gyvwxz"));

  FBAR_bthW = real(TVIL_GetFunction_ (&result, "FBARwuxy"));
  FBAR_htbW = real(TVIL_GetFunction_ (&result, "FBARxuwy"));
  FBAR_tbhW = real(TVIL_GetFunction_ (&result, "FBARuwxy"));
  FBAR_Wtbh = real(TVIL_GetFunction_ (&result, "FBARyuwx"));
  FBAR_ttWW = real(TVIL_GetFunction_ (&result, "FBARuvyz"));
  FBAR_WWtt = real(TVIL_GetFunction_ (&result, "FBARyuvz"));

  F_bthW = real(TVIL_GetFunction_ (&result, "Fwuxy"));
  F_htbW = real(TVIL_GetFunction_ (&result, "Fxuwy"));
  F_tbhW = real(TVIL_GetFunction_ (&result, "Fuwxy"));
  F_Wtbh = real(TVIL_GetFunction_ (&result, "Fyuwx"));
  F_ttWW = real(TVIL_GetFunction_ (&result, "Fuvyz"));
  F_WWtt = real(TVIL_GetFunction_ (&result, "Fyuvz"));

  E_tbhW = real(TVIL_GetFunction_ (&result, "Euwxy"));
  E_ttWW = real(TVIL_GetFunction_ (&result, "Euvyz"));

  I_tth = real(TVIL_GetFunction_ (&result, "Iuvx"));
  I_hWW = real(TVIL_GetFunction_ (&result, "Ixyz"));
  I_thW = real(TVIL_GetFunction_ (&result, "Iuxy"));
  I_tbW = real(TVIL_GetFunction_ (&result, "Iuwy"));
  I_tWW = real(TVIL_GetFunction_ (&result, "Iuyz"));
  I_bhW = real(TVIL_GetFunction_ (&result, "Iwxy"));
  I_ttW = real(TVIL_GetFunction_ (&result, "Iuvy"));
  I_tbh = real(TVIL_GetFunction_ (&result, "Iuwx"));

  I2_tth = real(TVIL_II2_ (t,t,h,Q2));
  I2_hWW = real(TVIL_II2_ (h,W,W,Q2));
  I2_thW = real(TVIL_II2_ (t,h,W,Q2));
  I2_tbW = real(TVIL_II2_ (t,b,W,Q2));
  I2_tWW = real(TVIL_II2_ (t,W,W,Q2));
  I2_bhW = real(TVIL_II2_ (b,h,W,Q2));
  I2_ttW = real(TVIL_II2_ (t,t,W,Q2));
  I2_tbh = real(TVIL_II2_ (t,b,h,Q2));

  I1_tth = real(TVIL_II1_ (t,t,h,Q2));
  I1_hWW = real(TVIL_II1_ (h,W,W,Q2));
  I1_thW = real(TVIL_II1_ (t,h,W,Q2));
  I1_tbW = real(TVIL_II1_ (t,b,W,Q2));
  I1_tWW = real(TVIL_II1_ (t,W,W,Q2));
  I1_bhW = real(TVIL_II1_ (b,h,W,Q2));
  I1_ttW = real(TVIL_II1_ (t,t,W,Q2));
  I1_tbh = real(TVIL_II1_ (t,b,h,Q2));

  I0_tth = real(TVIL_II0_ (t,t,h,Q2));
  I0_hWW = real(TVIL_II0_ (h,W,W,Q2));
  I0_thW = real(TVIL_II0_ (t,h,W,Q2));
  I0_tbW = real(TVIL_II0_ (t,b,W,Q2));
  I0_tWW = real(TVIL_II0_ (t,W,W,Q2));
  I0_bhW = real(TVIL_II0_ (b,h,W,Q2));
  I0_ttW = real(TVIL_II0_ (t,t,W,Q2));
  I0_tbh = real(TVIL_II0_ (t,b,h,Q2));

  Ieps_tth = real(TVIL_Ieps_ (t,t,h,Q2));
  Ieps_hWW = real(TVIL_Ieps_ (h,W,W,Q2));
  Ieps_thW = real(TVIL_Ieps_ (t,h,W,Q2));
  Ieps_tbW = real(TVIL_Ieps_ (t,b,W,Q2));
  Ieps_tWW = real(TVIL_Ieps_ (t,W,W,Q2));
  Ieps_bhW = real(TVIL_Ieps_ (b,h,W,Q2));
  Ieps_ttW = real(TVIL_Ieps_ (t,t,W,Q2));
  Ieps_tbh = real(TVIL_Ieps_ (t,b,h,Q2));

  A_t = real(TVIL_A_ (t,Q2));
  A_b = real(TVIL_A_ (b,Q2));
  A_h = real(TVIL_A_ (h,Q2));
  A_W = real(TVIL_A_ (W,Q2));

  Aeps_t = real(TVIL_Aeps_ (t,Q2));
  Aeps_b = real(TVIL_Aeps_ (b,Q2));
  Aeps_h = real(TVIL_Aeps_ (h,Q2));
  Aeps_W = real(TVIL_Aeps_ (W,Q2));

  Aeps2_t = real(TVIL_Aeps2_ (t,Q2));
  Aeps2_b = real(TVIL_Aeps2_ (b,Q2));
  Aeps2_h = real(TVIL_Aeps2_ (h,Q2));
  Aeps2_W = real(TVIL_Aeps2_ (W,Q2));

  for (j=0; j<4; j++) {
    EE_tbhW[j] = real(TVIL_GetBoldFunction_ (&result, "Euwxy", j));
    EE_ttWW[j] = real(TVIL_GetBoldFunction_ (&result, "Euvyz", j));

    FF_bthW[j] = real(TVIL_GetBoldFunction_ (&result, "Fwuxy", j));
    FF_htbW[j] = real(TVIL_GetBoldFunction_ (&result, "Fxuwy", j));
    FF_tbhW[j] = real(TVIL_GetBoldFunction_ (&result, "Fuwxy", j));
    FF_Wtbh[j] = real(TVIL_GetBoldFunction_ (&result, "Fyuwx", j));
    FF_ttWW[j] = real(TVIL_GetBoldFunction_ (&result, "Fuvyz", j));
    FF_WWtt[j] = real(TVIL_GetBoldFunction_ (&result, "Fyuvz", j));

    GG_btWtW[j]  = real(TVIL_GetBoldFunction_ (&result, "Gwuzvy", j));
    GG_httWW[j]  = real(TVIL_GetBoldFunction_ (&result, "Gxuvyz", j));
    GG_tthbW[j]  = real(TVIL_GetBoldFunction_ (&result, "Guvxwz", j));
    GG_WtbhW[j]  = real(TVIL_GetBoldFunction_ (&result, "Gyvwxz", j));
  }

  for (j=0; j<2; j++) {
    HH_ttbhWW[j] = real(TVIL_GetBoldFunction_ (&result, "H", j));
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
