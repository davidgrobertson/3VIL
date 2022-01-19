/* Analytic results for A-type and B-type one-loop functions */

#include "internal.h"

/* ******************************************************************* */
/* Implements Eq. 2.10 of hep-ph/0307101                               */
/* Accepts negative squared mass arg                                   */

TVIL_COMPLEX TVIL_A (TVIL_REAL x, TVIL_REAL qq)
{
  if (TVIL_FABS(x) < TVIL_TOL)
    return 0.0;
  if (x > 0)
    return (x * (TVIL_LOG(x/qq) - 1.));
  return (x * (TVIL_LOG(-x/qq) - 1. + I*PI));
}

/* ******************************************************************* */
/* A'(x), aka Logbar (x)                                               */

TVIL_COMPLEX TVIL_Ap (TVIL_REAL x, TVIL_REAL qq)
{
  if (TVIL_FABS(x) < TVIL_TOL) 
    return 0.0;
  if (x > 0) 
    return (TVIL_LOG(x/qq));  
  return (TVIL_LOG(-x/qq) + I*PI);
}

/* ******************************************************************** */

TVIL_COMPLEX TVIL_Aeps (TVIL_REAL x, TVIL_REAL qq)
{
  TVIL_COMPLEX lnbarx = TVIL_Ap (x, qq);
  
  if (TVIL_FABS(x) < TVIL_TOL) return 0.0L;
  else return x * (-1.0L - 0.5L*Zeta2 + lnbarx - 0.5L*lnbarx*lnbarx);
}

/* ******************************************************************** */

TVIL_COMPLEX TVIL_Aeps2 (TVIL_REAL x, TVIL_REAL qq)
{
  TVIL_COMPLEX lnbarx = TVIL_Ap (x, qq);
  TVIL_COMPLEX lnbarx2;

  lnbarx2 = lnbarx*lnbarx;

  if (TVIL_FABS(x) < TVIL_TOL) return 0.0L;
  else return x*(Zeta3/3.L - Zeta2/2.L - 1.L + (1.L + Zeta2/2.L)*lnbarx 
	    - (0.5L)*lnbarx2 + (1.L/6.L)*lnbarx2*lnbarx);
}
