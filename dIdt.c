/* Derivative of an I function with respect to t. */
/* Checked by comparison to derivative via Taylor exp at TINIT */

#include "internal.h"

/* **************************************************************** */

TVIL_COMPLEX TVIL_dIdt (TVIL_ITYPE *foo, TVIL_COMPLEX t, TVIL_REAL Q2)
{
  int i;
  TVIL_COMPLEX result = 0.0L + 0.0L*I;
  TVIL_COMPLEX lnbarX, lnbarY, lnbarZ;

  lnbarX = *(foo->lnbarA1);
  lnbarY = *(foo->lnbarA2);
  lnbarZ = *(foo->lnbarA3);

  for (i=0; i<2; i++)
    result += (foo->cII[i]*foo->value +
	       foo->cILL_012[i]*lnbarX*lnbarY +
	       foo->cILL_021[i]*lnbarX*lnbarZ +
	       foo->cILL_120[i]*lnbarY*lnbarZ +
	       foo->cIL_012[i]*lnbarX +
	       foo->cIL_102[i]*lnbarY +
	       foo->cIL_201[i]*lnbarZ +
	       foo->cI[i]
	       )/(t - foo->p[i]);

  result += foo->cIL_012[2]*lnbarX + 
            foo->cIL_102[2]*lnbarY + 
            foo->cIL_201[2]*lnbarZ + 
            foo->cI[2];

  return result;
}
