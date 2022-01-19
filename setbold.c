/* Evaluation of "bold" (UV divergent) forms of E,F,G,H functions. */

#include "internal.h"

/* **************************************************************** */
/* Sets bold function values in an I object. */

void TVIL_SetBoldI (TVIL_ITYPE *foo)
{
  foo->bold[0] = TVIL_II0 (foo->arg[0], foo->arg[1], foo->arg[2], _qq);
  foo->bold[1] = TVIL_II1 (foo->arg[0], foo->arg[1], foo->arg[2], _qq);
  foo->bold[2] = TVIL_II2 (foo->arg[0], foo->arg[1], foo->arg[2], _qq);

  return;
}

/* **************************************************************** */
/* Sets bold F function values in an FBARTYPE object. Requires that
   the F value for this object is already set! */

void TVIL_SetBoldF (TVIL_FBARTYPE *foo)
{
  TVIL_REAL u, v, y, z;
  TVIL_COMPLEX Au, Av, Ay, Az;
  TVIL_COMPLEX Aepsu, Aepsv, Aepsy, Aepsz;

  if (TVIL_FABS(foo->arg[0]) < TVIL_TOL) {
    foo->boldF[0] = foo->boldF[1] 
      = foo->boldF[2] = foo->boldF[3] = TVIL_ComplexInfinity;
    return;
  }

  /* For convenience */
  u = foo->arg[0];
  v = foo->arg[1];
  y = foo->arg[2];
  z = foo->arg[3];

  Au = TVIL_A (u, _qq);
  Av = TVIL_A (v, _qq);
  Ay = TVIL_A (y, _qq);
  Az = TVIL_A (z, _qq);

  Aepsu = TVIL_Aeps (u, _qq);
  Aepsv = TVIL_Aeps (v, _qq);
  Aepsy = TVIL_Aeps (y, _qq);
  Aepsz = TVIL_Aeps (z, _qq);

  /* 1/eps^3 term: */
  foo->boldF[3] = (-v - y - z)/3.L;
 
  /* 1/eps^2 term: */
  foo->boldF[2] = (u + v + y + z)/6 + ((v + y + z)*Au)/(2*u) + Av/2 + 
    Ay/2 + Az/2;
 
  /* 1/eps^1 term: */
  foo->boldF[1] = (3*u + v + y + z)/6 - Au/2 - Av/2 - (Au*Av)/u - 
    Ay/2 - (Au*Ay)/u - Az/2 - (Au*Az)/u + 
    ((v + y + z)*Aepsu)/(2*u) + Aepsv/2 + Aepsy/2 + Aepsz/2;
  
  /* 1/eps^0 term: */
  foo->boldF[0] = ((u - 2*v - 2*y - 2*z)*Au)/(4*u) + (Au*Av)/u + 
    (Au*Ay)/u + (Au*Az)/u - Aepsu/2 - (Av*Aepsu)/u - 
    (Ay*Aepsu)/u - (Az*Aepsu)/u - Aepsv/2 - (Au*Aepsv)/u - 
    Aepsy/2 - (Au*Aepsy)/u - Aepsz/2 - (Au*Aepsz)/u + 
    ((v + y + z)*TVIL_Aeps2 (u,_qq))/(2*u) + TVIL_Aeps2 (v,_qq)/2 +
    TVIL_Aeps2 (y,_qq)/2 + TVIL_Aeps2 (z,_qq)/2 + 
    (foo->fValue);

  return;
}

/* **************************************************************** */
/* Sets bold E function values in an ETYPE object. Requires that E
   values have already been set! */

void TVIL_SetBoldE (TVIL_ETYPE *foo)
{
  TVIL_REAL u, v, y, z;
  TVIL_COMPLEX Au, Av, Ay, Az;
  TVIL_COMPLEX Aepsu, Aepsv, Aepsy, Aepsz;

  /* For convenience */
  u = foo->arg[0];
  v = foo->arg[1];
  y = foo->arg[2];
  z = foo->arg[3];

  Au = TVIL_A (u, _qq);
  Av = TVIL_A (v, _qq);
  Ay = TVIL_A (y, _qq);
  Az = TVIL_A (z, _qq);

  Aepsu = TVIL_Aeps (u, _qq);
  Aepsv = TVIL_Aeps (v, _qq);
  Aepsy = TVIL_Aeps (y, _qq);
  Aepsz = TVIL_Aeps (z, _qq);

  foo->bold[3] = (1.L/3.L)*(u*v + u*y + u*z + v*y + v*z + y*z);
 
  foo->bold[2] = (u*v + u*y + v*y + u*z + v*z + y*z)/3.L + 
    (-u*u - v*v - y*y - z*z)/12.L + (-((v + y + z)*Au) - (u + y + z)*Av +
				     - (u + v + z)*Ay - (u + v + y)*Az)/2.L;
 
  foo->bold[1] = (u*v + u*y + v*y + u*z + v*z + y*z)/3.L +
    - (3*(u*u + v*v + y*y + z*z))/8.L + Au*Av + 
    Au*Ay + Av*Ay + Au*Az + Av*Az + Ay*Az + 
    (u*Au + v*Av + y*Ay + z*Az)/4.L - ((v + y + z)*(Au + Aepsu))/2.L - 
    ((u + y + z)*(Av + Aepsv))/2.L - ((u + v + z)*(Ay + Aepsy))/2.L - 
    ((u + v + y)*(Az + Aepsz))/2.L;
 
  foo->bold[0] = (foo->value) + 
    Az*(Aepsu + Aepsv + Aepsy) + Ay*(Aepsu + Aepsv + Aepsz) + 
    Av*(Aepsu + Aepsy + Aepsz) + Au*(Aepsv + Aepsy + Aepsz) + 
    (u*Aepsu + v*Aepsv + y*Aepsy + z*Aepsz)/4.L -
    ((v + y + z)*(Aepsu + TVIL_Aeps2 (u,_qq)))/2.L - 
    ((u + y + z)*(Aepsv + TVIL_Aeps2 (v,_qq)))/2.L -
    ((u + v + z)*(Aepsy + TVIL_Aeps2 (y,_qq)))/2.L - 
    ((u + v + y)*(Aepsz + TVIL_Aeps2 (z,_qq)))/2.L;

 return;
}

/* **************************************************************** */
/* Sets bold function values in an GTYPE object. */

void TVIL_SetBoldG (TVIL_GTYPE *foo)
{
  TVIL_REAL w, u, z, v, y;
  TVIL_COMPLEX Aw, Au, Az, Av, Ay;
  TVIL_COMPLEX Aepsw, Aepsu, Aepsz, Aepsv, Aepsy;

  /* For convenience */
  w = foo->arg[0];
  u = foo->arg[1];
  z = foo->arg[2];
  v = foo->arg[3];
  y = foo->arg[4];

  Aw = TVIL_A (w, _qq);
  Au = TVIL_A (u, _qq);
  Az = TVIL_A (z, _qq);
  Av = TVIL_A (v, _qq);
  Ay = TVIL_A (y, _qq);

  Aepsw = TVIL_Aeps (w, _qq);
  Aepsu = TVIL_Aeps (u, _qq);
  Aepsz = TVIL_Aeps (z, _qq);
  Aepsv = TVIL_Aeps (v, _qq);
  Aepsy = TVIL_Aeps (y, _qq);

  /* 1/eps^3 term: */
  foo->bold[3] = -(2.L*w + u + v + y + z)/6.L;

  /* 1/eps^2 term: */
  foo->bold[2] = 
    0.5L*(Au + Av + Ay + Az - u - v - y - z) + Aw - (2.L/3.L)*w;

  /* 1/eps^1 term: */
  foo->bold[1] =
    TVIL_I2 (u,w,z,_qq) + TVIL_I2 (v,w,y,_qq) + Aepsw +
    + 0.5L*(Aepsu + Aepsv + Aepsy + Aepsz + Au + Av + Ay + Az) +
    (w - 2.L*u - 2.L*v - 2.L*y - 2.L*z)/3.L;

  /* 1/eps^0 term: */
  if (foo->hasNegativeArg)
    foo->bold[0] = 666.*(1+I);
  else
    foo->bold[0] = (foo->value)
      + TVIL_Ieps (u, w, z, _qq)  + TVIL_Ieps (v, w, y, _qq)
      - TVIL_Aeps2 (w, _qq) + 0.5L*(Aepsu + Aepsv + Aepsy + Aepsz -
    	     TVIL_Aeps2 (u, _qq) - TVIL_Aeps2 (v, _qq) -
    	     TVIL_Aeps2 (y, _qq) - TVIL_Aeps2 (z, _qq));

  return;
}

/* **************************************************************** */
/* Sets bold function values in an HTYPE object. */

void TVIL_SetBoldH (TVIL_HTYPE *foo)
{
  foo->bold[1] = 2.0L*Zeta3;
  foo->bold[0] = foo->value;

  return;
}

/* **************************************************************** */

void TVIL_SetBold (TVIL_RESULT *foo)
{
  int i;

  for (i=0; i<NUM_I_FUNCS; i++)
    if (foo->evaluateII[i])
      TVIL_SetBoldI (&(_II[i]));

  for (i=0; i<NUM_F_FUNCS; i++)
    if (foo->evaluateFBAR[i])
      TVIL_SetBoldF (&(_FBAR[i]));

  for (i=0; i<NUM_E_FUNCS; i++)
    if (foo->evaluateE[i])
      TVIL_SetBoldE (&(_E[i]));

  for (i=0; i<NUM_G_FUNCS; i++)
    if (foo->evaluateG[i])
      TVIL_SetBoldG (&(_G[i]));

    if (foo->evaluateH)
      TVIL_SetBoldH (&_H);

  return;
}

/* **************************************************************** */
