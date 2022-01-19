/* Derivative of an Fbar function with respect to t. */

#include "internal.h"

/* **************************************************************** */

TVIL_COMPLEX TVIL_dFBARdt (TVIL_FBARTYPE *foo, TVIL_COMPLEX t, TVIL_REAL Q2)
{
  int i;
  TVIL_COMPLEX result = 0.0L + 0.0L*I;
  TVIL_COMPLEX lnbarW, lnbarX, lnbarY, lnbarZ;
  TVIL_COMPLEX temp[3];

  lnbarW = *(foo->lnbarA1);
  lnbarX = *(foo->lnbarA2);
  lnbarY = *(foo->lnbarA3);
  lnbarZ = *(foo->lnbarA4);

  result += (foo->cFF11/t + foo->cFF13/(t - foo->p3))*(foo->value - lnbarW*(*foo->ival[0]));

  temp[0] = lnbarX;
  temp[1] = lnbarY;
  temp[2] = lnbarZ;

  for (i=0; i<3; i++)
    result += (foo->cFF21/t +
      	       foo->cFF22[i]/(t - foo->p2) +
      	       foo->cFF23[i]/(t - foo->p3))
      *(*(foo->fval[i]) - temp[i]*(*(foo->ival[i+1])));

  result += (foo->cFLLL11/t + foo->cFLLL12/(t - foo->p2) + foo->cFLLL13/(t - foo->p3)) 
    *lnbarX*lnbarY*lnbarZ;

  temp[0] = lnbarW*lnbarX*lnbarY;
  temp[1] = lnbarW*lnbarX*lnbarZ;
  temp[2] = lnbarW*lnbarY*lnbarZ;

  for (i=0; i<3; i++)
    result += (foo->cFLLL21/t + 
	       foo->cFLLL23[i]/(t - foo->p3) + 
	       foo->cFLLL24[i]/(t - foo->p4) + 
	       foo->cFLLL25[i]/(t - foo->p5)) * temp[i];

  temp[0] = lnbarX*lnbarY;
  temp[1] = lnbarX*lnbarZ;
  temp[2] = lnbarY*lnbarZ;

  for (i=0; i<3; i++)
    result += (foo->cFLL11/t + 
	       foo->cFLL12[i]/(t - foo->p2) + 
	       foo->cFLL13[i]/(t - foo->p3)) * temp[i];

  temp[0] = lnbarW*lnbarX;
  temp[1] = lnbarW*lnbarY;
  temp[2] = lnbarW*lnbarZ;

  for (i=0; i<3; i++)
    result += (foo->cFLL21/t + 
	       foo->cFLL23[i]/(t - foo->p3) + 
	       foo->cFLL24[i]/(t - foo->p4) + 
	       foo->cFLL25[i]/(t - foo->p5)) * temp[i];

  result += ((foo->cFIL4/(t - foo->p4) + foo->cFIL5/(t - foo->p5))*lnbarW
	     + foo->cFI22/(t - foo->p2)) * (*(foo->ival[0]));

  result += (foo->cFL10 + 
	     foo->cFL11/t + 
	     foo->cFL13/(t - foo->p3) + 
	     foo->cFL14/(t - foo->p4) + 
	     foo->cFL15/(t - foo->p5)) * lnbarW;

  temp[0] = lnbarX;
  temp[1] = lnbarY;
  temp[2] = lnbarZ;

  for (i=0; i<3; i++)
    result += (foo->cFL20[i] + 
	       foo->cFL21/t + 
	       foo->cFL22[i]/(t - foo->p2) + 
	       foo->cFL23[i]/(t - foo->p3)) * temp[i];

  result += foo->cF0 + foo->cF2/(t - foo->p2) + foo->cF3/(t - foo->p3);

  return result;
}
