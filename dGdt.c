/* Derivative of a G function with respect to t. */

#include "internal.h"

/* **************************************************************** */

TVIL_COMPLEX TVIL_dGdt (TVIL_GTYPE *foo, TVIL_COMPLEX t, TVIL_REAL Q2)
{
  int i;
  TVIL_COMPLEX result = 0.0L + 0.0L*I;
  TVIL_COMPLEX U, Z, V, Y, lnbarU, lnbarZ, lnbarV, lnbarY;
  TVIL_COMPLEX temp[4];

  /* U = a + t*(foo->arg[1] - a); */
  /* Z = a + t*(foo->arg[2] - a); */
  /* V = a + t*(foo->arg[3] - a); */
  /* Y = a + t*(foo->arg[4] - a); */

  /* lnbarU = TVIL_CLOG(U/Q2); */
  /* lnbarZ = TVIL_CLOG(Z/Q2); */
  /* lnbarV = TVIL_CLOG(V/Q2); */
  /* lnbarY = TVIL_CLOG(Y/Q2); */

  U = *(foo->A2);
  Z = *(foo->A3);
  V = *(foo->A4);
  Y = *(foo->A5);

  lnbarU = *(foo->lnbarA2);
  lnbarZ = *(foo->lnbarA3);
  lnbarV = *(foo->lnbarA4);
  lnbarY = *(foo->lnbarA5);

  /* GG */
  result += (-1.0L/(t - foo->p1) +
  	      0.5L/(t - foo->p2) +
  	      0.5L/(t - foo->p3) +
  	      0.5L/(t - foo->p4) +
  	      0.5L/(t - foo->p5))*(foo->value);

  temp[0] = lnbarU;
  temp[1] = lnbarZ;
  temp[2] = lnbarV;
  temp[3] = lnbarY;

  /* GF */
  for (i=0; i<4; i++)
    result += (foo->cGF1[i]/(t - foo->p1) +
  	       foo->cGF4[i]/(t - foo->cGF_p4[i]) +
  	       foo->cGF5[i]/(t - foo->cGF_p5[i])) *
      (*(foo->fval[i]) + temp[i]*(-(*foo->ival[i+2]) + (*foo->ival[i+6])));

  temp[0] = lnbarU*U;
  temp[1] = lnbarZ*Z;
  temp[2] = lnbarV*V;
  temp[3] = lnbarY*Y;

  /* GL */
  for (i=0; i<4; i++)
    result += (-0.5L/(t - foo->cGL_p2[i]) +
  	       -0.5L/(t - foo->cGL_p3[i]) -
  	       (foo->cGF1[i]/(t - foo->p1) +
  		foo->cGF4[i]/(t - foo->cGF_p4[i]) +
  		foo->cGF5[i]/(t - foo->cGF_p5[i]))/4.0L)*temp[i];

  /* GI */
  for (i=0; i<2; i++)
    result += (1.0L/(t - foo->p1) +
  	      -1.0L/(t - foo->cGI_p2[i]) +
              -1.0L/(t - foo->cGI_p3[i])) * (*foo->ival[i]);

  /* G */
  result += foo->cG0 +
            foo->cG1/(t - foo->p1) +
            foo->cG2/(t - foo->p2) +
            foo->cG3/(t - foo->p3) +
            foo->cG4/(t - foo->p4) +
            foo->cG5/(t - foo->p5);

  return result;
}
