/* Derivative of an H function with respect to t. */

#include "internal.h"

/* **************************************************************** */

TVIL_COMPLEX TVIL_dHdt (TVIL_HTYPE *foo, TVIL_COMPLEX t, TVIL_REAL Q2)
{
  int i, j;
  TVIL_COMPLEX result = 0.0L + 0.0L*I;
  /* TVIL_COMPLEX U, V, W, X, Y, Z; */
  /* TVIL_COMPLEX lnbarU, lnbarV, lnbarW, lnbarX, lnbarY, lnbarZ; */
  TVIL_COMPLEX temp1[6], temp2[6], fac1[6], fac2[6];
  TVIL_COMPLEX tToThe[8];
  TVIL_COMPLEX numHG, numH, denHG, denH;

  tToThe[0] = 1.0;
  for (j=1; j<8; j++)
    tToThe[j] = tToThe[j-1]*t;

  /* U = a + t*(foo->arg[0] - a); */
  /* V = a + t*(foo->arg[1] - a); */
  /* W = a + t*(foo->arg[2] - a); */
  /* X = a + t*(foo->arg[3] - a); */
  /* Y = a + t*(foo->arg[4] - a); */
  /* Z = a + t*(foo->arg[5] - a); */

  /* lnbarU = TVIL_CLOG (U/Q2); */
  /* lnbarV = TVIL_CLOG (V/Q2); */
  /* lnbarW = TVIL_CLOG (W/Q2); */
  /* lnbarX = TVIL_CLOG (X/Q2); */
  /* lnbarY = TVIL_CLOG (Y/Q2); */
  /* lnbarZ = TVIL_CLOG (Z/Q2); */

  temp1[0] = _lnbarXg; temp2[0] = _lnbarWg;
  temp1[1] = _lnbarWg; temp2[1] = _lnbarXg;
  temp1[2] = _lnbarZg; temp2[2] = _lnbarVg;
  temp1[3] = _lnbarVg; temp2[3] = _lnbarZg;
  temp1[4] = _lnbarYg; temp2[4] = _lnbarUg;
  temp1[5] = _lnbarUg; temp2[5] = _lnbarYg;

  fac1[0] = _Xg; fac2[0] = _Wg;
  fac1[1] = _Wg; fac2[1] = _Xg;
  fac1[2] = _Zg; fac2[2] = _Vg;
  fac1[3] = _Vg; fac2[3] = _Zg;
  fac1[4] = _Yg; fac2[4] = _Ug;
  fac1[5] = _Ug; fac2[5] = _Yg;

  for (i=0; i<6; i++) {

    numHG = foo->cHGnum[i][0];
    denHG = foo->cHGden[i][0];

    for (j=1; j<5; j++) {
      numHG += (foo->cHGnum[i][j]) * tToThe[j];
      denHG += (foo->cHGden[i][j]) * tToThe[j];
    }

    for (j=5; j<8; j++)
      denHG += (foo->cHGden[i][j]) * tToThe[j];

    result += (numHG/denHG) *
      (*(foo->gval[i]) - 
       (*(foo->fval[i][0]) - *(foo->ival[i][0]) * temp1[i]) - 
       (*(foo->fval[i][1]) - *(foo->ival[i][1]) * temp1[i]) +
       (2 - temp1[i]) * (*(foo->ival[i][2]) + *(foo->ival[i][3])) +
       fac2[i]*temp2[i] + fac1[i]*temp1[i]/2 - 5*fac1[i]/2 - 7*fac2[i]/3);
  }

  numH  = foo->cHnum[0];
  denH  = foo->cHden[0];

  for (j=1; j<3; j++) {
    numH += foo->cHnum[j]*tToThe[j];
    denH += foo->cHden[j]*tToThe[j];
  }

  denH += foo->cHden[3]*tToThe[3];

  result += Zeta3*numH/denH;

  return result;
}
