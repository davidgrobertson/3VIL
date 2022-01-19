/* Analytic results for E-type functions */

#include "internal.h"

/* ****************************************************************** */

TVIL_COMPLEX TVIL_E0xyy (TVIL_REAL X, TVIL_REAL Y, TVIL_REAL qq)
{
  TVIL_COMPLEX k, lnk, lnk2, result;
  TVIL_COMPLEX lnbarx;
  TVIL_COMPLEX lnbary, lnbary2;
  TVIL_COMPLEX x = X;
  TVIL_COMPLEX y = Y;

  if (X<0) x = x * (1.L +  I * TVIL_EPSILON);
  if (Y<0) y = y * (1.L +  I * TVIL_EPSILON);

  /* DGR */
  k = (1 - TVIL_CSQRT((x-4*y)/x))/(1 + TVIL_CSQRT((x-4*y)/x));
  lnk = TVIL_CLOG (k);
  lnk2 = lnk*lnk;
  lnbarx = TVIL_CLOG (x/qq);
  lnbary = TVIL_CLOG (y/qq);
  lnbary2 = lnbary*lnbary;

  result = y*(y-x)*(4*TVIL_Trilog(-k)  + (1./3.)*lnk*lnk2 - (1./3.)*lnbary*lnbary2 + 
    (PI2/3.)*lnk - 4*Zeta3/3.) - (x+2*y)*TVIL_CSQRT(x*x - 4*x*y)*(TVIL_Dilog(-k) + 
    (1./4.)*lnk2 + PI2/12.) + ((x*x + 6*y*y)/4)*lnbary2 - 
    x*y*lnbarx*lnbary2 + (x*(8*y-x)/2)*lnbarx*lnbary + 
    (x*(13*x - 32*y)/8)*lnbarx - (y*(16*x + 3*y)/4)*lnbary  +
    -133*x*x/48 + 11*x*y/3 - 89*y*y/24;

  return result;
}

/* ****************************************************************** */

TVIL_COMPLEX TVIL_Exxyy (TVIL_REAL X, TVIL_REAL Y, TVIL_REAL qq)
{
  TVIL_COMPLEX result;
  TVIL_COMPLEX lnbarx, lnbarx2;
  TVIL_COMPLEX lnbary, lnbary2;
  TVIL_COMPLEX x = X;
  TVIL_COMPLEX y = Y;
  if (X<0) x = x * (1.L +  I * TVIL_EPSILON);
  if (Y<0) y = y * (1.L +  I * TVIL_EPSILON);

  lnbarx = TVIL_CLOG (x/qq);
  lnbarx2 = lnbarx*lnbarx;
  lnbary = TVIL_CLOG (y/qq);
  lnbary2 = lnbary*lnbary;

  result = -2*(x-y)*(x-y)*(TVIL_Trilog(1-x/y) + TVIL_Trilog(1-y/x) +
			   TVIL_LOG(y/x)*TVIL_Dilog(1-x/y) +
    -(1./6.)*lnbarx*lnbarx2 + (1./3.)*lnbary*lnbary2 - (7./3.)*Zeta3) +
    (-89*x*x + 176*x*y - 89*y*y)/24 - (x*(3*x + 32*y)*lnbarx)/4 + 
    (x*(3*x - 2*y)*lnbarx2)/2 - (y*(32*x + 3*y)*lnbary)/4 + 
    10*x*y*lnbarx*lnbary + (-2*x*x + 2*x*y - y*y)*lnbarx2*lnbary + 
    (y*(-2*x + 3*y)*lnbary2)/2 + (2*x*x - 4*x*y + y*y)*lnbarx*lnbary2;

  return result;
}

/* ****************************************************************** */

TVIL_COMPLEX TVIL_E00xy (TVIL_REAL X, TVIL_REAL Y, TVIL_REAL qq)
{
  TVIL_COMPLEX result;
  TVIL_COMPLEX lnbarx, lnbarx2;
  TVIL_COMPLEX lnbary, lnbary2;
  TVIL_COMPLEX x = X;
  TVIL_COMPLEX y = Y;
  if (X<0) x = x * (1.L +  I * TVIL_EPSILON);
  if (Y<0) y = y * (1.L +  I * TVIL_EPSILON);

  lnbarx = TVIL_CLOG (x/qq);
  lnbary = TVIL_CLOG (y/qq);
  lnbarx2 = lnbarx*lnbarx;
  lnbary2 = lnbary*lnbary;

  result = x*y*(-2*TVIL_Trilog(1-x/y) - 2*TVIL_Trilog(1-y/x) + 8*Zeta3/3. +
  + (1./3.)*lnbarx*lnbarx2 - (1./6.)*lnbary*lnbary2 + (11./6.) - 2*lnbarx - 2*lnbary + 
		2*lnbarx*lnbary - lnbarx2*lnbary + (lnbarx*lnbary2)/2 ) + 
    ((x*x-y*y)/2 + x*y*TVIL_LOG(x/y))*TVIL_Dilog(1-x/y) + (-133*(x*x + y*y))/48 + 
    (13*x*x*lnbarx)/8 + (13*y*y*lnbary)/8 - (x*x*lnbarx*lnbary)/2 + 
    ((x - y)*(x + y)*lnbary2)/4;

  return result;
}

/* ****************************************************************** */
/* Necessary F values *must* have been set previously! */

int TVIL_SetE (TVIL_ETYPE *foo, TVIL_REAL qq)
{
  TVIL_REAL u, v, y, z;
  TVIL_COMPLEX Au, Av, Ay, Az;
  TVIL_COMPLEX Fu, Fv, Fy, Fz;
  
  /* For convenience: */
  u = foo->arg[0];
  v = foo->arg[1];
  y = foo->arg[2];
  z = foo->arg[3];

  if (SAME2(0,u)) Fu = 0; else Fu = *(foo->fval[0]); 
  if (SAME2(0,v)) Fv = 0; else Fv = *(foo->fval[1]);
  if (SAME2(0,y)) Fy = 0; else Fy = *(foo->fval[2]);
  if (SAME2(0,z)) Fz = 0; else Fz = *(foo->fval[3]);

  Au = TVIL_A (u, qq);
  Av = TVIL_A (v, qq);
  Ay = TVIL_A (y, qq);
  Az = TVIL_A (z, qq);

  foo->value = 
    (u*v + u*y + v*y + u*z + v*z + y*z - (9.L*(u*u + v*v + y*y + z*z))/8.L + 
     (u/2.L - v - y - z)*Au + (-u + v/2.L - y - z)*Av + Au*Av + 
     (-u - v + y/2.L - z)*Ay + Au*Ay + Av*Ay + (-u - v - y + z/2.L)*Az + 
     Au*Az + Av*Az + Ay*Az 
     - u * Fu - v * Fv - y * Fy - z * Fz)/2.L;

  return 0;
}

/* ****************************************************************** */

int TVIL_SetAllEs (TVIL_RESULT *foo)
{
  int i;

  /* For safety: */
  TVIL_SetAllFs (foo);

  for (i=0; i<NUM_E_FUNCS; i++)
    if (foo->evaluateE[i])
      TVIL_SetE (&(_E[i]), _qq);

  /* Make this meaningful eventually... */
  return 0;
}
