/* Contains the two-loop vacuum integral function I(x,y,z) (eq. 2.20
   in hep-ph/0307101), and derivatives of it. */

#include "internal.h"

/* ***************************************************************** */
/* This is copied from TSIL v1.4. Should work with negative squared  */
/* mass arguments.                                                   */

TVIL_COMPLEX TVIL_I2 (TVIL_REAL X, TVIL_REAL Y, TVIL_REAL Z, TVIL_REAL QQ)
{
  TVIL_REAL tmp, absX, absY, absZ;
  TVIL_COMPLEX DeltaXYZ, sqDeltaXYZ, rp, rm, xiXYZ;
  TVIL_COMPLEX lnbarX, lnbarY, lnbarZ;
  TVIL_COMPLEX lnrp, lnrm, dilogrp, dilogrm;
  TVIL_COMPLEX x, y, z, result;

  if (X < Y) {tmp = Y; Y = X; X = tmp;}
  if (Y < Z) {tmp = Z; Z = Y; Y = tmp;}
  if (X < Y) {tmp = Y; Y = X; X = tmp;}

  absX = TVIL_FABS(X);
  if (absX < TVIL_TOL) return TVIL_I20xy (Y, Z, QQ);

  absY = TVIL_FABS(Y);
  if (absY < TVIL_TOL) return TVIL_I20xy (X, Z, QQ);

  absZ = TVIL_FABS(Z);
  if (absZ < TVIL_TOL) return TVIL_I20xy (X, Y, QQ);

  lnbarX = TVIL_LOG(absX/QQ);
  lnbarY = TVIL_LOG(absY/QQ);
  lnbarZ = TVIL_LOG(absZ/QQ);

  x = X; y = Y; z = Z;

  if (X<0) {lnbarX -= I*PI; x -= I*TVIL_EPSILON;}
  if (Y<0) {lnbarY -= I*PI; y -= I*TVIL_EPSILON;}
  if (Z<0) {lnbarZ -= I*PI; z -= I*TVIL_EPSILON;}

  DeltaXYZ = x*x + y*y + z*z - 2.0L*(x*y + x*z + y*z);
  sqDeltaXYZ = TVIL_CSQRT(DeltaXYZ);
  rp = (x + z - y - sqDeltaXYZ)/(2.0L * x);
  rm = (x + y - z - sqDeltaXYZ)/(2.0L * x);

  lnrp = TVIL_CLOG(rp);
  lnrm = TVIL_CLOG(rm);
  dilogrp = TVIL_Dilog(rp);
  dilogrm = TVIL_Dilog(rm);

  xiXYZ = sqDeltaXYZ*(2.0L * (lnrp * lnrm - dilogrp - dilogrm + Zeta2)
                - (lnbarY - lnbarX) * (lnbarZ - lnbarX));

  result = 0.5L*((X - Y - Z) * lnbarY * lnbarZ +
                 (Y - X - Z) * lnbarX * lnbarZ +
                 (Z - X - Y) * lnbarX * lnbarY -xiXYZ)
          + 2.0L * (X * lnbarX + Y * lnbarY + Z * lnbarZ)
          - 2.5L * (X + Y + Z);

  if (Z>0) result = TVIL_CREAL(result);

  return(result);
}

/* ***************************************************************** */
/* This is copied from TSIL v1.4. Should work with negative squared  */
/* mass arguments.                                                   */

TVIL_COMPLEX TVIL_I20xy (TVIL_REAL X, TVIL_REAL Y, TVIL_REAL QQ)
{
  TVIL_COMPLEX lnbarX, lnbarY, result;
  TVIL_REAL tmp, absX, absY;

  if (X < Y) {tmp = Y; Y = X; X = tmp;}

  absX = TVIL_FABS(X);
  if (absX < TVIL_TOL) return TVIL_I200x (Y,QQ);

  absY = TVIL_FABS(Y);
  if (absY < TVIL_TOL) return TVIL_I200x (X,QQ);

  lnbarX = TVIL_LOG(absX/QQ);
  if (X<0) lnbarX -= I*PI;

  if (TVIL_FABS(X-Y) < TVIL_TOL)
    return (X * (-lnbarX*lnbarX + 4.0L * lnbarX - 5.0L));

  lnbarY = TVIL_LOG(absY/QQ);
  if (Y<0) lnbarY -= I*PI;

  if (X*Y > 0) {
    result = (Y-X) * (TVIL_Dilog(1 - Y/X) + 0.5L * lnbarX * lnbarX)
      - Y * lnbarX * lnbarY + 2.0L * (X * lnbarX + Y * lnbarY)
      - 2.5L * (X + Y);
  } else {
    result = ((X - Y) * (TVIL_Dilog(Y/X)
      + (lnbarY - lnbarX) * TVIL_CLOG((X - Y)/QQ)
      + 0.5L * lnbarX * lnbarX - Zeta2) - 2.5L * (X+Y)
      + 2.0L * (X * lnbarX +  Y * lnbarY) - X * lnbarX * lnbarY);
  }

  return (result);
}

/* ***************************************************************** */
/* This is copied from TSIL v1.4. Should work with negative squared  */
/* mass arguments.                                                   */

TVIL_COMPLEX TVIL_I200x (TVIL_REAL X,  TVIL_REAL QQ)
{
  TVIL_COMPLEX lnbarX;
  TVIL_REAL absX;

  absX = TVIL_FABS(X);
  if (absX < TVIL_TOL) return 0.0L + I*0.0L;
  lnbarX = TVIL_LOG(absX/QQ);
  if (X < 0) lnbarX -= I*PI;

  return (X * (-0.5L*lnbarX*lnbarX + 2.0L * lnbarX - 2.5L - Zeta2));
}

/* ***************************************************************** */
/* This version of I2 works with complex squared mass arguments.     */
/* However, it is ONLY approved for use if all of the complex        */
/* squared mass arguments are non-zero and have negative-definite    */
/* imaginary parts. This should hold everywhere on the contour in    */
/* the upper-half complex t plane, except at the t=1 endpoint.       */

TVIL_COMPLEX TVIL_I2_complex_args (TVIL_COMPLEX X,
				   TVIL_COMPLEX Y, 
                                   TVIL_COMPLEX Z,
				   TVIL_REAL QQ)
{
  TVIL_COMPLEX DeltaXYZ, sqDeltaXYZ, rp, rm, xiXYZ;
  TVIL_COMPLEX lnbarX, lnbarY, lnbarZ;
  TVIL_COMPLEX lnrp, lnrm, dilogrp, dilogrm;
  TVIL_COMPLEX x, y, z, tmp, result;

  /* Sort arguments the same way Mathematica does, to ease comparison. */ 
  if ((TVIL_CREAL(X) < TVIL_CREAL(Y)) ||
      ((TVIL_FABS(TVIL_CREAL(X-Y)) < TVIL_EPSILON) && 
       (TVIL_FABS(TVIL_CIMAG(X)) < TVIL_FABS(TVIL_CIMAG(Y))))
     ) {tmp = Y; Y = X; X = tmp;}

  if ((TVIL_CREAL(Y) < TVIL_CREAL(Z)) ||
      ((TVIL_FABS(TVIL_CREAL(Y-Z)) < TVIL_EPSILON) && 
       (TVIL_FABS(TVIL_CIMAG(Y)) < TVIL_FABS(TVIL_CIMAG(Z))))
     ) {tmp = Z; Z = Y; Y = tmp;}

  if ((TVIL_CREAL(X) < TVIL_CREAL(Y)) ||
      ((TVIL_FABS(TVIL_CREAL(X-Y)) < TVIL_EPSILON) && 
       (TVIL_FABS(TVIL_CIMAG(X)) < TVIL_FABS(TVIL_CIMAG(Y))))
     ) {tmp = Y; Y = X; X = tmp;}

  /* This shouldn't be necessary, but just to make extra sure. */
  x = X - I*TVIL_EPSILON;
  y = Y - I*TVIL_EPSILON;
  z = Z - I*TVIL_EPSILON;

  lnbarX = TVIL_CLOG(x/QQ);
  lnbarY = TVIL_CLOG(y/QQ);
  lnbarZ = TVIL_CLOG(z/QQ);

  DeltaXYZ = x*x + y*y + z*z - 2.0L*(x*y + x*z + y*z);
  sqDeltaXYZ = TVIL_CSQRT(DeltaXYZ);
  rp = (x + z - y - sqDeltaXYZ)/(2.0L * x);
  rm = (x + y - z - sqDeltaXYZ)/(2.0L * x);

  lnrp = TVIL_CLOG(rp);
  lnrm = TVIL_CLOG(rm);
  dilogrp = TVIL_Dilog(rp);
  dilogrm = TVIL_Dilog(rm);

  xiXYZ = sqDeltaXYZ*(2.0L * (lnrp * lnrm - dilogrp - dilogrm + Zeta2)
                - (lnbarY - lnbarX) * (lnbarZ - lnbarX));

  result = 0.5L*((X - Y - Z) * lnbarY * lnbarZ +
                 (Y - X - Z) * lnbarX * lnbarZ +
                 (Z - X - Y) * lnbarX * lnbarY -xiXYZ)
          + 2.0L * (X * lnbarX + Y * lnbarY + Z * lnbarZ)
          - 2.5L * (X + Y + Z);

  return(result);
}

/* ******************************************************************* */
/* Does this work with negative squared mass arguments? Needs testing. */

TVIL_COMPLEX TVIL_Ieps (TVIL_REAL X, TVIL_REAL Y, TVIL_REAL Z, TVIL_REAL QQ)
{
  TVIL_REAL tmp;
  TVIL_COMPLEX x,y,z;
  TVIL_COMPLEX rx, ry, rz, s, eta;
  TVIL_COMPLEX lnbarx, lnbary, lnbarz;
  TVIL_COMPLEX lnbarx2, lnbary2, lnbarz2;
  TVIL_COMPLEX lnbarx3, lnbary3, lnbarz3;
  TVIL_COMPLEX lnrx, lnry, lnrz;
  TVIL_COMPLEX result;

  if (Z < Y) {tmp = Y; Y = Z; Z = tmp;}
  if (Y < X) {tmp = X; X = Y; Y = tmp;}
  if (Z < Y) {tmp = Y; Y = Z; Z = tmp;}

  if (X < 0) 
    TVIL_Error ("TVIL_Ieps",
		"At this time, Ieps is not supported for negative squared mass arguments.", 22);

  if (TVIL_FABS(X) < TVIL_TOL) return TVIL_Ieps0xy (Y, Z, QQ);
  if (TVIL_FABS(Y) < TVIL_TOL) return TVIL_Ieps0xy (X, Z, QQ);
  if (TVIL_FABS(Z) < TVIL_TOL) return TVIL_Ieps0xy (X, Y, QQ);
  if (SAME3(X, Y, Z)) return TVIL_Iepsxxx (X, QQ);

  if (TVIL_FABS(Z-X-Y) < TVIL_EPSILON) Z = (X + Y) * (1.L - I * TVIL_EPSILON);

  lnbarx = TVIL_LOG(TVIL_FABS(X));
  if (X < 0) lnbarx = lnbarx - I * PI;;

  lnbary = TVIL_LOG(TVIL_FABS(Y));
  if (Y < 0) lnbary = lnbary - I * PI;;

  lnbarz = TVIL_LOG(TVIL_FABS(Z));
  if (Z < 0) lnbarz = lnbarz - I * PI;;

  lnbarx2 = lnbarx * lnbarx;
  lnbary2 = lnbary * lnbary;
  lnbarz2 = lnbarz * lnbarz;

  lnbarx3 = lnbarx2 * lnbarx;
  lnbary3 = lnbary2 * lnbary;
  lnbarz3 = lnbarz2 * lnbarz;

  x = X * (1 - I * TVIL_EPSILON); 
  y = Y * (1 - I * TVIL_EPSILON); 
  z = Z * (1 - I * TVIL_EPSILON);

  s = TVIL_CSQRT(x*x + y*y + z*z - 2.0L * (x*y + x*z + y*z));
  rx = (s+X-Y-Z)*(s+X-Y-Z)/(4.L * Y * Z);
  ry = (s+Y-X-Z)*(s+Y-X-Z)/(4.L * X * Z);
  rz = (s+Z-X-Y)*(s+Z-X-Y)/(4.L * X * Y);
  lnrx = TVIL_CLOG(rx);
  lnry = TVIL_CLOG(ry);
  lnrz = TVIL_CLOG(rz);
  eta = lnrx + lnry + lnrz;

  /*
  printf("x          = "); TVIL_cprintf(x); printf("\n");
  printf("y          = "); TVIL_cprintf(y); printf("\n");
  printf("z          = "); TVIL_cprintf(z); printf("\n");
  printf("s          = "); TVIL_cprintf(s); printf("\n");
  printf("z-x-y      = "); TVIL_cprintf(z-x-y); printf("\n");
  printf("eta        = "); TVIL_cprintf(eta); printf("\n");
  printf("rx*ry*rz   = "); TVIL_cprintf(rx*ry*rz); printf("\n");
  */

  result = (3.L - lnbarx - lnbary) * TVIL_I2(X,Y,Z,QQ) +
           (X * lnbarx3 + Y * lnbary3 + Z * lnbarz3)/6.L +
           (X * lnbarx2 + Y * lnbary2 -3.L * Z * lnbarz2)/2.L +
           ((Y-X-Z)/4.L) * lnbarx * lnbarz * TVIL_CLOG(x/z) +          
           ((X-Y-Z)/4.L) * lnbary * lnbarz * TVIL_CLOG(y/z) +          
           ((Z-X-Y)/4.L) * lnbarx * lnbary * (lnbarx + lnbary) +
           (2.L*X + 2.L*Y - Z * lnbarz) * lnbarx * lnbary  +
           2.L * Z * lnbarz * (lnbarx + lnbary) + 
           (Zeta2 + 1.L) * Z * lnbarz +
           (Zeta2 - 1.5L) * (X * lnbarx + Y * lnbary) +
           -2.5L * ((Y+Z) * lnbarx + (X+Z) * lnbary) +
           (Zeta3/3.L - 1.5L*Zeta2) * (X+Y+Z);

  if (TVIL_CABS(s) > TVIL_TOL) 
    result += s * (TVIL_Trilog(1.L - rx) + TVIL_Trilog(1.L - ry)
              + TVIL_Trilog(1.L - rz) - TVIL_Trilog(1.L - 1.L/rx)
              -	TVIL_Trilog(1.L - 1.L/ry) - TVIL_Trilog(1.L - 1.L/rz)
              + TVIL_CLOG(z/x) * TVIL_Dilog(1.L - rx)
              + TVIL_CLOG(z/y) * TVIL_Dilog(1.L - ry)
              + 0.25L * lnrx * lnry * lnrz 
              + 0.25L * TVIL_CLOG(z/x) * lnrx * TVIL_CLOG(x*rx/z)            
              + 0.25L * TVIL_CLOG(z/y) * lnry * TVIL_CLOG(y*ry/z)            
              + 0.25L * eta * (TVIL_CLOG(-s*s/(x*y)) * TVIL_CLOG(-s*s/(x*y)) 
                - lnrx * lnry +
                0.25L * (lnrx + lnry - lnrz) * (lnrx + lnry - lnrz)));  
  /*
  printf("Ieps   = "); TVIL_cprintf(result); printf("\n\n");
  */

  if (X > 0) result = TVIL_CREAL(result);

  return(result);
}

/* ******************************************************************* */
/* Does this work with negative squared mass arguments? Needs testing. */

TVIL_COMPLEX TVIL_Ieps0xy (TVIL_REAL X, TVIL_REAL Y, TVIL_REAL QQ)
{
  TVIL_COMPLEX tmp, result;
  TVIL_COMPLEX lnbarx, lnbary;
  TVIL_COMPLEX lnbarx2, lnbary2;

  if (Y < X) {tmp = X; X = Y; Y = tmp;}
  if (X < 0) 
    TVIL_Error ("TVIL_Ieps0xy",
		"At this time, Ieps is not supported for negative squared mass arguments.", 22);

  if (TVIL_FABS(X) < TVIL_TOL) return TVIL_Ieps00x (Y, QQ);
  if (TVIL_FABS(Y) < TVIL_TOL) return TVIL_Ieps00x (X, QQ);
  if (SAME2(X,Y)) return TVIL_Ieps0xx (X, QQ);

  lnbarx = TVIL_LOG(TVIL_FABS(X));
  if (X < 0) lnbarx = lnbarx - I * PI;;

  lnbary = TVIL_LOG(TVIL_FABS(Y));
  if (Y < 0) lnbary = lnbary - I * PI;;

  lnbarx2 = lnbarx * lnbarx;
  lnbary2 = lnbary * lnbary;

  result = (Y-X) * (TVIL_Trilog(1.L - X/Y) - TVIL_Trilog(1.L - Y/X) +
           (lnbarx + lnbary - 3.L) * TVIL_Dilog (1.L - X/Y) ) +
           (Y/6.L) * lnbarx2 * lnbarx + (X - Y/2.L) * lnbarx2 * lnbary +
           (Y/2.L) * lnbarx * lnbary2 + (Y/2.L - X/3.L) * lnbary2 * lnbary +
           -1.5L * X * lnbarx2 - 3.L * X * lnbarx * lnbary +
           (1.5L * X - 3.L * Y) * lnbary2 + 
           (7.L + Zeta2) * (X * lnbarx + Y * lnbary) +
           (Zeta3/3.L - 7.5L - 1.5L * Zeta2) * (X + Y);

  if (X > 0) result = TVIL_CREAL(result);

  return result;
}

/* ******************************************************************* */
/* This one should work with negative X.                               */

TVIL_COMPLEX TVIL_Iepsxxx (TVIL_REAL X, TVIL_REAL QQ)
{
  TVIL_COMPLEX lnbarx, result;

  if (TVIL_FABS(X) < TVIL_TOL) return 0;

  lnbarx = TVIL_LOG(TVIL_FABS(X));
  if (X < 0) lnbarx = lnbarx - I * PI;;
  
  result = X * (2.L * lnbarx * lnbarx * lnbarx - 9.L * lnbarx * lnbarx +
           (21.L + 0.5L * PI * PI - 6.L * SQRT3 * LS2) * lnbarx +
           -22.5L - 3.L * PI * PI/4.L + 
           (3.L - TVIL_LOG(3.L)) * 3 * SQRT3 * LS2 + 3 * SQRT3 * LS3 +
           Zeta3 + PI * PI * PI/(2.L * SQRT3));

  return result;
}

/* ******************************************************************* */
/* This one should work with negative X.                               */

TVIL_COMPLEX TVIL_Ieps0xx (TVIL_REAL X, TVIL_REAL QQ)
{
  TVIL_COMPLEX lnbarx, result;

  if (TVIL_FABS(X) < TVIL_TOL) return 0;

  lnbarx = TVIL_LOG(TVIL_FABS(X));
  if (X < 0) lnbarx = lnbarx - I * PI;;

  result = X * ((4.L/3.L) * lnbarx * lnbarx * lnbarx +
           -6.L * lnbarx * lnbarx + (14.L + 2.L * Zeta2) * lnbarx +
           -15.L - 3.L * Zeta2 + 2.L * Zeta3/3.L);

  return result;
}

/* ******************************************************************* */
/* This one should work with negative X.                               */

TVIL_COMPLEX TVIL_Ieps00x (TVIL_REAL X, TVIL_REAL QQ)
{
  TVIL_COMPLEX lnbarx, result;

  if (TVIL_FABS(X) < TVIL_TOL) return 0;

  lnbarx = TVIL_LOG(TVIL_FABS(X));
  if (X < 0) lnbarx = lnbarx - I * PI;;

  result = X * ((2.L/3.L) * lnbarx * lnbarx * lnbarx +
           -3.L * lnbarx * lnbarx + (7.L + 3.L * Zeta2) * lnbarx +
           -7.5L - 3.L * PI * PI/4.L + 4.L * Zeta3/3.L);

  return result;
}
  
/* ****************************************************************** */

TVIL_COMPLEX TVIL_II2 (TVIL_REAL X, TVIL_REAL Y, TVIL_REAL Z, TVIL_REAL QQ)
{
  return (-0.5L * (X+Y+Z));
}

/* ****************************************************************** */

TVIL_COMPLEX TVIL_II1 (TVIL_REAL X, TVIL_REAL Y, TVIL_REAL Z, TVIL_REAL QQ)
{
  return (TVIL_A(X,QQ) + TVIL_A(Y,QQ) + TVIL_A(Z,QQ) - 0.5L * (X+Y+Z));
}

/* ****************************************************************** */

TVIL_COMPLEX TVIL_II0 (TVIL_REAL X, TVIL_REAL Y, TVIL_REAL Z, TVIL_REAL QQ)
{
  return (TVIL_I2(X,Y,Z,QQ) +TVIL_Aeps(X,QQ) +TVIL_Aeps(Y,QQ) +TVIL_Aeps(Z,QQ));
}

/* ****************************************************************** */

int TVIL_AnalyticITYPE (TVIL_ITYPE *foo, TVIL_REAL qq)
{
  foo->value = TVIL_I2 (foo->arg[0], foo->arg[1], foo->arg[2], qq);

  return 1;
}

/* ****************************************************************** */

int TVIL_SetAllIs (void)
{
  int i;
  for (i=0; i<_nIfuns; i++)
    TVIL_AnalyticITYPE (_ifun[i], _qq);

  /* Make this meaningful eventually? */
  return 0;
}

/* ****************************************************************** */

TVIL_COMPLEX TVIL_TestI (TVIL_ITYPE *foo, TVIL_REAL qq)
{
  return TVIL_I2 (foo->arg[0], foo->arg[1], foo->arg[2], qq);
}

/* ****************************************************************** */

int TVIL_TestAllIs (void)
{
  int i;
  TVIL_COMPLEX ANALresult, RKresult, diff;

  printf("\nTesting I functions at t=1:\n");

  for (i=0; i<_nIfuns; i++) {
    ANALresult = TVIL_TestI (_ifun[i], _qq);
    RKresult = _ifun[i]->value;
    diff = RKresult - ANALresult;
    printf("Analytic value = "); TVIL_cprintf(ANALresult); printf("\n");
    printf("RK       value = "); TVIL_cprintf(RKresult); printf("\n");
    printf("diff           = "); TVIL_cprintf(diff); printf("\n\n");
  }

  return 0;
}

/* ****************************************************************** */

int TVIL_SetI_complex (TVIL_ITYPE *foo, TVIL_REAL qq, TVIL_COMPLEX t)
{
  foo->value = TVIL_I2_complex_args (_a + t * (foo->arg[0] - _a),
				     _a + t * (foo->arg[1] - _a),
				     _a + t * (foo->arg[2] - _a),
				     qq);

  /* Make this meaningful eventually? */
  return 0;
}

/* ****************************************************************** */

int TVIL_SetAllIs_complex (TVIL_COMPLEX t)
{
  int i;
  for (i=0; i<_nIfuns; i++)
    TVIL_SetI_complex (_ifun[i], _qq, t);

  /* Make this meaningful eventually? */
  return 0;
}

/* ****************************************************************** */

TVIL_COMPLEX TVIL_TestI_complex (TVIL_ITYPE *foo, TVIL_REAL qq, TVIL_COMPLEX t)
{
  return TVIL_I2_complex_args (_a + t * (foo->arg[0] - _a),
                               _a + t * (foo->arg[1] - _a),
                               _a + t * (foo->arg[2] - _a),
                               qq);
}

/* ****************************************************************** */

int TVIL_TestAllIs_complex (TVIL_COMPLEX t)
{
  int i;
  TVIL_COMPLEX ANALresult, RKresult, diff;

  printf("\nTesting I functions at t = ");TVIL_cprintf(t); printf("\n");

  for (i=0; i<_nIfuns; i++) {
    ANALresult = TVIL_TestI_complex (_ifun[i], _qq, t);
    RKresult = _ifun[i]->value;
    diff = RKresult - ANALresult;
    printf("Analytic value = "); TVIL_cprintf(ANALresult); printf("\n");
    printf("RK       value = "); TVIL_cprintf(RKresult); printf("\n");
    printf("diff           = "); TVIL_cprintf(diff); printf("\n\n");
  }

  return 0;
}

/* ****************************************************************** */
/* Sets initial value for an I function at a point near t = 0. */

int TVIL_InitialI (TVIL_ITYPE *foo, 
		   TVIL_REAL qq,
		   TVIL_COMPLEX tinit)
{
  TVIL_REAL x = (foo->arg[0])/_a;
  TVIL_REAL y = (foo->arg[1])/_a;
  TVIL_REAL z = (foo->arg[2])/_a;
  TVIL_REAL Iexp[10];
  TVIL_REAL x2, x3, x4, x5, x6, x7, x8, x9;
  TVIL_REAL y2, y3, y4, y5, y6, y7, y8, y9;
  TVIL_REAL z2, z3, z4, z5, z6, z7, z8, z9;
  TVIL_REAL lnbara, lnbara2;
  TVIL_COMPLEX ttothei, result;
  int i, nTerms = 10;

  lnbara = TVIL_LOG (_a/qq);
  lnbara2 = lnbara * lnbara;

  x2 = x*x;
  x3 = x2*x;
  x4 = x2*x2;
  x5 = x2*x3;
  x6 = x3*x3;
  x7 = x4*x3;
  x8 = x4*x4;
  x9 = x4*x5;

  y2 = y*y;
  y3 = y2*y;
  y4 = y2*y2;
  y5 = y2*y3;
  y6 = y3*y3;
  y7 = y4*y3;
  y8 = y4*y4;
  y9 = y4*y5;

  z2 = z*z;
  z3 = z2*z;
  z4 = z2*z2;
  z5 = z2*z3;
  z6 = z3*z3;
  z7 = z4*z3;
  z8 = z4*z4;
  z9 = z4*z5;

  Iexp[0] = -3.984139141965812 + 6.*lnbara - 1.5*lnbara2;
 
  Iexp[1] = -2.015860858034188 - 3.*lnbara + 1.5*lnbara2 + 
     0.6719536193447294*x + lnbara*x - 0.5*lnbara2*x + 
     0.6719536193447294*y + lnbara*y - 0.5*lnbara2*y + 
     0.6719536193447294*z + lnbara*z - 0.5*lnbara2*z;
 
  Iexp[2] = 1.5 - 1.5*lnbara - 1.*x + lnbara*x - 0.2813024128964863*x2 - 
     0.5*lnbara*x2 - 1.*y + lnbara*y + 0.7813024128964863*x*y - 
     0.2813024128964863*y2 - 0.5*lnbara*y2 - 1.*z + lnbara*z + 
     0.7813024128964863*x*z + 0.7813024128964863*y*z - 
     0.2813024128964863*z2 - 0.5*lnbara*z2;
 
  Iexp[3] = 1. - 0.5*lnbara - 1.*x + 0.5*lnbara*x + 0.2186975871035137*x2 - 
     0.5*lnbara*x2 + 0.03821191540993988*x3 + 0.16666666666666666*lnbara*
      x3 - 1.*y + 0.5*lnbara*y + 0.7813024128964863*x*y - 
     0.16666666666666666*x2*y + 0.2186975871035137*y2 - 0.5*lnbara*y2 - 
     0.16666666666666666*x*y2 + 0.03821191540993988*y3 + 
     0.16666666666666666*lnbara*y3 - 1.*z + 0.5*lnbara*z + 
     0.7813024128964863*x*z - 0.16666666666666666*x2*z + 
     0.7813024128964863*y*z - 0.11463574622981963*x*y*z - 
     0.16666666666666666*y2*z + 0.2186975871035137*z2 - 0.5*lnbara*z2 - 
     0.16666666666666666*x*z2 - 0.16666666666666666*y*z2 + 
     0.03821191540993988*z3 + 0.16666666666666666*lnbara*z3;
 
  Iexp[4] = 0.625 - 0.25*lnbara - 0.8333333333333334*x + 
     0.3333333333333333*lnbara*x + 0.4686975871035137*x2 - 0.5*lnbara*x2 - 
     0.09024283584678691*x3 + 0.3333333333333333*lnbara*x3 - 
     0.011585721384404363*x4 - 0.08333333333333333*lnbara*x4 - 
     0.8333333333333334*y + 0.3333333333333333*lnbara*y + 
     0.7813024128964863*x*y - 0.3333333333333333*x2*y + 
     0.06829286069220218*x3*y + 0.4686975871035137*y2 - 0.5*lnbara*y2 - 
     0.3333333333333333*x*y2 + 0.045121417923393456*x2*y2 - 
     0.09024283584678691*y3 + 0.3333333333333333*lnbara*y3 + 
     0.06829286069220218*x*y3 - 0.011585721384404363*y4 - 
     0.08333333333333333*lnbara*y4 - 0.8333333333333334*z + 
     0.3333333333333333*lnbara*z + 0.7813024128964863*x*z - 
     0.3333333333333333*x2*z + 0.06829286069220218*x3*z + 
     0.7813024128964863*y*z - 0.22927149245963926*x*y*z + 
     0.03821191540993988*x2*y*z - 0.3333333333333333*y2*z + 
     0.03821191540993988*x*y2*z + 0.06829286069220218*y3*z + 
     0.4686975871035137*z2 - 0.5*lnbara*z2 - 0.3333333333333333*x*z2 + 
     0.045121417923393456*x2*z2 - 0.3333333333333333*y*z2 + 
     0.03821191540993988*x*y*z2 + 0.045121417923393456*y2*z2 - 
     0.09024283584678691*z3 + 0.3333333333333333*lnbara*z3 + 
     0.06829286069220218*x*z3 + 0.06829286069220218*y*z3 - 
     0.011585721384404363*z4 - 0.08333333333333333*lnbara*z4;
 
  Iexp[5] = 0.425 - 0.15*lnbara - 0.7083333333333334*x + 0.25*lnbara*x + 
     0.6353642537701804*x2 - 0.5*lnbara*x2 - 0.30203092043684704*x3 + 
     0.5*lnbara*x3 + 0.04857616918012025*x4 - 0.25*lnbara*x4 + 
     0.004946036478491797*x5 + 0.05*lnbara*x5 - 0.7083333333333334*y + 
     0.25*lnbara*y + 0.7813024128964863*x*y - 0.5*x2*y + 
     0.20487858207660653*x3*y - 0.03665317578628961*x4*y + 
     0.6353642537701804*y2 - 0.5*lnbara*y2 - 0.5*x*y2 + 
     0.13536425377018038*x2*y2 - 0.020053963521508202*x3*y2 - 
     0.30203092043684704*y3 + 0.5*lnbara*y3 + 0.20487858207660653*x*y3 - 
     0.020053963521508202*x2*y3 + 0.04857616918012025*y4 - 
     0.25*lnbara*y4 - 0.03665317578628961*x*y4 + 0.004946036478491797*y5 + 
     0.05*lnbara*y5 - 0.7083333333333334*z + 0.25*lnbara*z + 
     0.7813024128964863*x*z - 0.5*x2*z + 0.20487858207660653*x3*z - 
     0.03665317578628961*x4*z + 0.7813024128964863*y*z - 
     0.3439072386894589*x*y*z + 0.11463574622981963*x2*y*z - 
     0.018157951888431674*x3*y*z - 0.5*y2*z + 0.11463574622981963*x*y2*z - 
     0.015040472641131153*x2*y2*z + 0.20487858207660653*y3*z - 
     0.018157951888431674*x*y3*z - 0.03665317578628961*y4*z + 
     0.6353642537701804*z2 - 0.5*lnbara*z2 - 0.5*x*z2 + 
     0.13536425377018038*x2*z2 - 0.020053963521508202*x3*z2 - 0.5*y*z2 + 
     0.11463574622981963*x*y*z2 - 0.015040472641131153*x2*y*z2 + 
     0.13536425377018038*y2*z2 - 0.015040472641131153*x*y2*z2 - 
     0.020053963521508202*y3*z2 - 0.30203092043684704*z3 + 
     0.5*lnbara*z3 + 0.20487858207660653*x*z3 - 0.020053963521508202*x2*
      z3 + 0.20487858207660653*y*z3 - 0.018157951888431674*x*y*z3 - 
     0.020053963521508202*y2*z3 + 0.04857616918012025*z4 - 
     0.25*lnbara*z4 - 0.03665317578628961*x*z4 - 0.03665317578628961*y*
      z4 + 0.004946036478491797*z5 + 0.05*lnbara*z5;
 
  Iexp[6] = 0.30833333333333335 - 0.1*lnbara - 0.6166666666666667*x + 
     0.2*lnbara*x + 0.7603642537701804*x2 - 0.5*lnbara*x2 - 
     0.5693745605824627*x3 + 0.6666666666666666*lnbara*x3 + 
     0.22215233836024048*x4 - 0.5*lnbara*x4 - 0.030215854086032813*x5 + 
     0.2*lnbara*x5 - 0.0025521199514614403*x6 - 0.03333333333333333*lnbara*
      x6 - 0.6166666666666667*y + 0.2*lnbara*y + 0.7813024128964863*x*y - 
     0.6666666666666666*x2*y + 0.40975716415321306*x3*y - 
     0.14661270314515845*x4*y + 0.02276428689740073*x5*y + 
     0.7603642537701804*y2 - 0.5*lnbara*y2 - 0.6666666666666666*x*y2 + 
     0.27072850754036076*x2*y2 - 0.08021585408603281*x3*y2 + 
     0.011178565512996366*x4*y2 - 0.5693745605824627*y3 + 
     0.6666666666666666*lnbara*y3 + 0.40975716415321306*x*y3 - 
     0.08021585408603281*x2*y3 + 0.009259259259259259*x3*y3 + 
     0.22215233836024048*y4 - 0.5*lnbara*y4 - 0.14661270314515845*x*y4 + 
     0.011178565512996366*x2*y4 - 0.030215854086032813*y5 + 
     0.2*lnbara*y5 + 0.02276428689740073*x*y5 - 0.0025521199514614403*y6 - 
     0.03333333333333333*lnbara*y6 - 0.6166666666666667*z + 0.2*lnbara*z + 
     0.7813024128964863*x*z - 0.6666666666666666*x2*z + 
     0.40975716415321306*x3*z - 0.14661270314515845*x4*z + 
     0.02276428689740073*x5*z + 0.7813024128964863*y*z - 
     0.45854298491927853*x*y*z + 0.22927149245963926*x2*y*z - 
     0.0726318075537267*x3*y*z + 0.010434137632162098*x4*y*z - 
     0.6666666666666666*y2*z + 0.22927149245963926*x*y2*z - 
     0.06016189056452461*x2*y2*z + 0.007723814256269575*x3*y2*z + 
     0.40975716415321306*y3*z - 0.0726318075537267*x*y3*z + 
     0.007723814256269575*x2*y3*z - 0.14661270314515845*y4*z + 
     0.010434137632162098*x*y4*z + 0.02276428689740073*y5*z + 
     0.7603642537701804*z2 - 0.5*lnbara*z2 - 0.6666666666666666*x*z2 + 
     0.27072850754036076*x2*z2 - 0.08021585408603281*x3*z2 + 
     0.011178565512996366*x4*z2 - 0.6666666666666666*y*z2 + 
     0.22927149245963926*x*y*z2 - 0.06016189056452461*x2*y*z2 + 
     0.007723814256269575*x3*y*z2 + 0.27072850754036076*y2*z2 - 
     0.06016189056452461*x*y2*z2 + 0.00690950251345358*x2*y2*z2 - 
     0.08021585408603281*y3*z2 + 0.007723814256269575*x*y3*z2 + 
     0.011178565512996366*y4*z2 - 0.5693745605824627*z3 + 
     0.6666666666666666*lnbara*z3 + 0.40975716415321306*x*z3 - 
     0.08021585408603281*x2*z3 + 0.009259259259259259*x3*z3 + 
     0.40975716415321306*y*z3 - 0.0726318075537267*x*y*z3 + 
     0.007723814256269575*x2*y*z3 - 0.08021585408603281*y2*z3 + 
     0.007723814256269575*x*y2*z3 + 0.009259259259259259*y3*z3 + 
     0.22215233836024048*z4 - 0.5*lnbara*z4 - 0.14661270314515845*x*z4 + 
     0.011178565512996366*x2*z4 - 0.14661270314515845*y*z4 + 
     0.010434137632162098*x*y*z4 + 0.011178565512996366*y2*z4 - 
     0.030215854086032813*z5 + 0.2*lnbara*z5 + 0.02276428689740073*x*z5 + 
     0.02276428689740073*y*z5 - 0.0025521199514614403*z6 - 
     0.03333333333333333*lnbara*z6;
 
  Iexp[7] = 0.23452380952380952 - 0.07142857142857142*lnbara - 
     0.5472222222222223*x + 0.16666666666666666*lnbara*x + 
     0.8603642537701803*x2 - 0.5*lnbara*x2 - 0.8783848673947451*x3 + 
     0.8333333333333334*lnbara*x3 + 0.5369205639337341*x4 - 
     0.8333333333333334*lnbara*x4 - 0.17553963521508203*x5 + 
     0.5*lnbara*x5 + 0.020572733576026132*x6 - 0.16666666666666666*lnbara*
      x6 + 0.0014852761292083983*x7 + 0.023809523809523808*lnbara*x7 - 
     0.5472222222222223*y + 0.16666666666666666*lnbara*y + 
     0.7813024128964863*x*y - 0.8333333333333334*x2*y + 
     0.6829286069220218*x3*y - 0.36653175786289616*x4*y + 
     0.11382143448700363*x5*y - 0.01548483324024246*x6*y + 
     0.8603642537701803*y2 - 0.5*lnbara*y2 - 0.8333333333333334*x*y2 + 
     0.4512141792339346*x2*y2 - 0.20053963521508203*x3*y2 + 
     0.055892827564981824*x4*y2 - 0.00709100055854524*x5*y2 - 
     0.8783848673947451*y3 + 0.8333333333333334*lnbara*y3 + 
     0.6829286069220218*x*y3 - 0.20053963521508203*x2*y3 + 
     0.046296296296296294*x3*y3 - 0.005269398380875331*x4*y3 + 
     0.5369205639337341*y4 - 0.8333333333333334*lnbara*y4 - 
     0.36653175786289616*x*y4 + 0.055892827564981824*x2*y4 - 
     0.005269398380875331*x3*y4 - 0.17553963521508203*y5 + 
     0.5*lnbara*y5 + 0.11382143448700363*x*y5 - 0.00709100055854524*x2*
      y5 + 0.020572733576026132*y6 - 0.16666666666666666*lnbara*y6 - 
     0.01548483324024246*x*y6 + 0.0014852761292083983*y7 + 
     0.023809523809523808*lnbara*y7 - 0.5472222222222223*z + 
     0.16666666666666666*lnbara*z + 0.7813024128964863*x*z - 
     0.8333333333333334*x2*z + 0.6829286069220218*x3*z - 
     0.36653175786289616*x4*z + 0.11382143448700363*x5*z - 
     0.01548483324024246*x6*z + 0.7813024128964863*y*z - 
     0.5731787311490981*x*y*z + 0.3821191540993988*x2*y*z - 
     0.18157951888431673*x3*y*z + 0.0521706881608105*x4*y*z - 
     0.006730433928458395*x5*y*z - 0.8333333333333334*y2*z + 
     0.3821191540993988*x*y2*z - 0.15040472641131153*x2*y2*z + 
     0.03861907128134787*x3*y2*z - 0.004629629629629629*x4*y2*z + 
     0.6829286069220218*y3*z - 0.18157951888431673*x*y3*z + 
     0.03861907128134787*x2*y3*z - 0.004141109249293644*x3*y3*z - 
     0.36653175786289616*y4*z + 0.0521706881608105*x*y4*z - 
     0.004629629629629629*x2*y4*z + 0.11382143448700363*y5*z - 
     0.006730433928458395*x*y5*z - 0.01548483324024246*y6*z + 
     0.8603642537701803*z2 - 0.5*lnbara*z2 - 0.8333333333333334*x*z2 + 
     0.4512141792339346*x2*z2 - 0.20053963521508203*x3*z2 + 
     0.055892827564981824*x4*z2 - 0.00709100055854524*x5*z2 - 
     0.8333333333333334*y*z2 + 0.3821191540993988*x*y*z2 - 
     0.15040472641131153*x2*y*z2 + 0.03861907128134787*x3*y*z2 - 
     0.004629629629629629*x4*y*z2 + 0.4512141792339346*y2*z2 - 
     0.15040472641131153*x*y2*z2 + 0.0345475125672679*x2*y2*z2 - 
     0.003838612507474211*x3*y2*z2 - 0.20053963521508203*y3*z2 + 
     0.03861907128134787*x*y3*z2 - 0.003838612507474211*x2*y3*z2 + 
     0.055892827564981824*y4*z2 - 0.004629629629629629*x*y4*z2 - 
     0.00709100055854524*y5*z2 - 0.8783848673947451*z3 + 
     0.8333333333333334*lnbara*z3 + 0.6829286069220218*x*z3 - 
     0.20053963521508203*x2*z3 + 0.046296296296296294*x3*z3 - 
     0.005269398380875331*x4*z3 + 0.6829286069220218*y*z3 - 
     0.18157951888431673*x*y*z3 + 0.03861907128134787*x2*y*z3 - 
     0.004141109249293644*x3*y*z3 - 0.20053963521508203*y2*z3 + 
     0.03861907128134787*x*y2*z3 - 0.003838612507474211*x2*y2*z3 + 
     0.046296296296296294*y3*z3 - 0.004141109249293644*x*y3*z3 - 
     0.005269398380875331*y4*z3 + 0.5369205639337341*z4 - 
     0.8333333333333334*lnbara*z4 - 0.36653175786289616*x*z4 + 
     0.055892827564981824*x2*z4 - 0.005269398380875331*x3*z4 - 
     0.36653175786289616*y*z4 + 0.0521706881608105*x*y*z4 - 
     0.004629629629629629*x2*y*z4 + 0.055892827564981824*y2*z4 - 
     0.004629629629629629*x*y2*z4 - 0.005269398380875331*y3*z4 - 
     0.17553963521508203*z5 + 0.5*lnbara*z5 + 0.11382143448700363*x*z5 - 
     0.00709100055854524*x2*z5 + 0.11382143448700363*y*z5 - 
     0.006730433928458395*x*y*z5 - 0.00709100055854524*y2*z5 + 
     0.020572733576026132*z6 - 0.16666666666666666*lnbara*z6 - 
     0.01548483324024246*x*z6 - 0.01548483324024246*y*z6 + 
     0.0014852761292083983*z7 + 0.023809523809523808*lnbara*z7;
 
  Iexp[8] = 0.18482142857142858 - 0.05357142857142857*lnbara - 
     0.4928571428571429*x + 0.14285714285714285*lnbara*x + 
     0.9436975871035137*x2 - 0.5*lnbara*x2 - 1.2207285075403607*x3 + 
     lnbara*x3 + 1.0137141792339346*x4 - 1.25*lnbara*x4 - 
     0.5177459370968307*x5 + lnbara*x5 + 0.14505153406141172*x6 - 
     0.5*lnbara*x6 - 0.01489786703427342*x7 + 0.14285714285714285*lnbara*
      x7 - 0.0009393908297169524*x8 - 0.017857142857142856*lnbara*x8 - 
     0.4928571428571429*y + 0.14285714285714285*lnbara*y + 
     0.7813024128964863*x*y - 1.*x2*y + 1.0243929103830327*x3*y - 
     0.7330635157257923*x4*y + 0.3414643034610109*x5*y - 
     0.09290899944145475*x6*y + 0.011206496836004519*x7*y + 
     0.9436975871035137*y2 - 0.5*lnbara*y2 - 1.*x*y2 + 
     0.6768212688509019*x2*y2 - 0.40107927043016406*x3*y2 + 
     0.16767848269494548*x4*y2 - 0.04254600335127144*x5*y2 + 
     0.004887855481301699*x6*y2 - 1.2207285075403607*y3 + lnbara*y3 + 
     1.0243929103830327*x*y3 - 0.40107927043016406*x2*y3 + 
     0.1388888888888889*x3*y3 - 0.03161639028525199*x4*y3 + 
     0.003384978503667747*x5*y3 + 1.0137141792339346*y4 - 
     1.25*lnbara*y4 - 0.7330635157257923*x*y4 + 0.16767848269494548*x2*
      y4 - 0.03161639028525199*x3*y4 + 0.0030360036294498475*x4*y4 - 
     0.5177459370968307*y5 + lnbara*y5 + 0.3414643034610109*x*y5 - 
     0.04254600335127144*x2*y5 + 0.003384978503667747*x3*y5 + 
     0.14505153406141172*y6 - 0.5*lnbara*y6 - 0.09290899944145475*x*y6 + 
     0.004887855481301699*x2*y6 - 0.01489786703427342*y7 + 
     0.14285714285714285*lnbara*y7 + 0.011206496836004519*x*y7 - 
     0.0009393908297169524*y8 - 0.017857142857142856*lnbara*y8 - 
     0.4928571428571429*z + 0.14285714285714285*lnbara*z + 
     0.7813024128964863*x*z - 1.*x2*z + 1.0243929103830327*x3*z - 
     0.7330635157257923*x4*z + 0.3414643034610109*x5*z - 
     0.09290899944145475*x6*z + 0.011206496836004519*x7*z + 
     0.7813024128964863*y*z - 0.6878144773789178*x*y*z + 
     0.5731787311490981*x2*y*z - 0.36315903776863345*x3*y*z + 
     0.1565120644824315*x4*y*z - 0.040382603570750374*x5*y*z + 
     0.004687810626819727*x6*y*z - 1.*y2*z + 0.5731787311490981*x*y2*z - 
     0.30080945282262306*x2*y2*z + 0.11585721384404363*x3*y2*z - 
     0.027777777777777776*x4*y2*z + 0.0030639349524580017*x5*y2*z + 
     1.0243929103830327*y3*z - 0.36315903776863345*x*y3*z + 
     0.11585721384404363*x2*y3*z - 0.024846655495761868*x3*y3*z + 
     0.0025474832491138625*x4*y3*z - 0.7330635157257923*y4*z + 
     0.1565120644824315*x*y4*z - 0.027777777777777776*x2*y4*z + 
     0.0025474832491138625*x3*y4*z + 0.3414643034610109*y5*z - 
     0.040382603570750374*x*y5*z + 0.0030639349524580017*x2*y5*z - 
     0.09290899944145475*y6*z + 0.004687810626819727*x*y6*z + 
     0.011206496836004519*y7*z + 0.9436975871035137*z2 - 0.5*lnbara*z2 - 
     1.*x*z2 + 0.6768212688509019*x2*z2 - 0.40107927043016406*x3*z2 + 
     0.16767848269494548*x4*z2 - 0.04254600335127144*x5*z2 + 
     0.004887855481301699*x6*z2 - 1.*y*z2 + 0.5731787311490981*x*y*z2 - 
     0.30080945282262306*x2*y*z2 + 0.11585721384404363*x3*y*z2 - 
     0.027777777777777776*x4*y*z2 + 0.0030639349524580017*x5*y*z2 + 
     0.6768212688509019*y2*z2 - 0.30080945282262306*x*y2*z2 + 
     0.10364253770180369*x2*y2*z2 - 0.023031675044845268*x3*y2*z2 + 
     0.0024078266340730905*x4*y2*z2 - 0.40107927043016406*y3*z2 + 
     0.11585721384404363*x*y3*z2 - 0.023031675044845268*x2*y3*z2 + 
     0.002233394751425484*x3*y3*z2 + 0.16767848269494548*y4*z2 - 
     0.027777777777777776*x*y4*z2 + 0.0024078266340730905*x2*y4*z2 - 
     0.04254600335127144*y5*z2 + 0.0030639349524580017*x*y5*z2 + 
     0.004887855481301699*y6*z2 - 1.2207285075403607*z3 + lnbara*z3 + 
     1.0243929103830327*x*z3 - 0.40107927043016406*x2*z3 + 
     0.1388888888888889*x3*z3 - 0.03161639028525199*x4*z3 + 
     0.003384978503667747*x5*z3 + 1.0243929103830327*y*z3 - 
     0.36315903776863345*x*y*z3 + 0.11585721384404363*x2*y*z3 - 
     0.024846655495761868*x3*y*z3 + 0.0025474832491138625*x4*y*z3 - 
     0.40107927043016406*y2*z3 + 0.11585721384404363*x*y2*z3 - 
     0.023031675044845268*x2*y2*z3 + 0.002233394751425484*x3*y2*z3 + 
     0.1388888888888889*y3*z3 - 0.024846655495761868*x*y3*z3 + 
     0.002233394751425484*x2*y3*z3 - 0.03161639028525199*y4*z3 + 
     0.0025474832491138625*x*y4*z3 + 0.003384978503667747*y5*z3 + 
     1.0137141792339346*z4 - 1.25*lnbara*z4 - 0.7330635157257923*x*z4 + 
     0.16767848269494548*x2*z4 - 0.03161639028525199*x3*z4 + 
     0.0030360036294498475*x4*z4 - 0.7330635157257923*y*z4 + 
     0.1565120644824315*x*y*z4 - 0.027777777777777776*x2*y*z4 + 
     0.0025474832491138625*x3*y*z4 + 0.16767848269494548*y2*z4 - 
     0.027777777777777776*x*y2*z4 + 0.0024078266340730905*x2*y2*z4 - 
     0.03161639028525199*y3*z4 + 0.0025474832491138625*x*y3*z4 + 
     0.0030360036294498475*y4*z4 - 0.5177459370968307*z5 + lnbara*z5 + 
     0.3414643034610109*x*z5 - 0.04254600335127144*x2*z5 + 
     0.003384978503667747*x3*z5 + 0.3414643034610109*y*z5 - 
     0.040382603570750374*x*y*z5 + 0.0030639349524580017*x2*y*z5 - 
     0.04254600335127144*y2*z5 + 0.0030639349524580017*x*y2*z5 + 
     0.003384978503667747*y3*z5 + 0.14505153406141172*z6 - 
     0.5*lnbara*z6 - 0.09290899944145475*x*z6 + 0.004887855481301699*x2*
      z6 - 0.09290899944145475*y*z6 + 0.004687810626819727*x*y*z6 + 
     0.004887855481301699*y2*z6 - 0.01489786703427342*z7 + 
     0.14285714285714285*lnbara*z7 + 0.011206496836004519*x*z7 + 
     0.011206496836004519*y*z7 - 0.0009393908297169524*z8 - 
     0.017857142857142856*lnbara*z8;
 
  Iexp[9] = 0.14970238095238095 - 0.041666666666666664*lnbara - 
     0.44910714285714287*x + 0.125*lnbara*x + 1.0151261585320852*x2 - 
     0.5*lnbara*x2 - 1.5908499254637543*x3 + 1.1666666666666667*lnbara*
      x3 + 1.6691998509275083*x4 - 1.75*lnbara*x4 - 
     1.1560553899194537*x5 + 1.75*lnbara*x5 + 0.505120246143294*x6 - 
     1.1666666666666667*lnbara*x6 - 0.12357110604852839*x7 + 
     0.5*lnbara*x7 + 0.011281407049124191*x8 - 0.125*lnbara*x8 + 
     0.0006314866025416194*x9 + 0.013888888888888888*lnbara*x9 - 
     0.44910714285714287*y + 0.125*lnbara*y + 0.7813024128964863*x*y - 
     1.1666666666666667*x2*y + 1.4341500745362459*x3*y - 
     1.2828611525201365*x4*y + 0.7967500414090255*x5*y - 
     0.32518149804509167*x6*y + 0.07844547785203164*x7*y - 
     0.008482393235999383*x8*y + 1.0151261585320852*y2 - 0.5*lnbara*y2 - 
     1.1666666666666667*x*y2 + 0.9475497763912626*x2*y2 - 
     0.7018887232527871*x3*y2 + 0.3912497929548728*x4*y2 - 
     0.14891101172945004*x5*y2 + 0.034214988369111896*x6*y2 - 
     0.0035694255405763686*x7*y2 - 1.5908499254637543*y3 + 
     1.1666666666666667*lnbara*y3 + 1.4341500745362459*x*y3 - 
     0.7018887232527871*x2*y3 + 0.32407407407407407*x3*y3 - 
     0.11065736599838195*x4*y3 + 0.02369484952567423*x5*y3 - 
     0.0023528108443965027*x6*y3 + 1.6691998509275083*y4 - 
     1.75*lnbara*y4 - 1.2828611525201365*x*y4 + 0.3912497929548728*x2*
      y4 - 0.11065736599838195*x3*y4 + 0.02125202540614893*x4*y4 - 
     0.001965839940596915*x5*y4 - 1.1560553899194537*y5 + 
     1.75*lnbara*y5 + 0.7967500414090255*x*y5 - 0.14891101172945004*x2*
      y5 + 0.02369484952567423*x3*y5 - 0.001965839940596915*x4*y5 + 
     0.505120246143294*y6 - 1.1666666666666667*lnbara*y6 - 
     0.32518149804509167*x*y6 + 0.034214988369111896*x2*y6 - 
     0.0023528108443965027*x3*y6 - 0.12357110604852839*y7 + 
     0.5*lnbara*y7 + 0.07844547785203164*x*y7 - 0.0035694255405763686*x2*
      y7 + 0.011281407049124191*y8 - 0.125*lnbara*y8 - 
     0.008482393235999383*x*y8 + 0.0006314866025416194*y9 + 
     0.013888888888888888*lnbara*y9 - 0.44910714285714287*z + 
     0.125*lnbara*z + 0.7813024128964863*x*z - 1.1666666666666667*x2*z + 
     1.4341500745362459*x3*z - 1.2828611525201365*x4*z + 
     0.7967500414090255*x5*z - 0.32518149804509167*x6*z + 
     0.07844547785203164*x7*z - 0.008482393235999383*x8*z + 
     0.7813024128964863*y*z - 0.8024502236087374*x*y*z + 
     0.8024502236087374*x2*y*z - 0.6355283160951086*x3*y*z + 
     0.3651948171256735*x4*y*z - 0.1413391124976263*x5*y*z + 
     0.032814674387738094*x6*y*z - 0.003447480882883837*x7*y*z - 
     1.1666666666666667*y2*z + 0.8024502236087374*x*y2*z - 
     0.5264165424395904*x2*y2*z + 0.2703334989694351*x3*y2*z - 
     0.09722222222222222*x4*y2*z + 0.02144754466720601*x5*y2*z - 
     0.002170577051887808*x6*y2*z + 1.4341500745362459*y3*z - 
     0.6355283160951086*x*y3*z + 0.2703334989694351*x2*y3*z - 
     0.08696329423516654*x3*y3*z + 0.01783238274379704*x4*y3*z - 
     0.0017146246969075556*x5*y3*z - 1.2828611525201365*y4*z + 
     0.3651948171256735*x*y4*z - 0.09722222222222222*x2*y4*z + 
     0.01783238274379704*x3*y4*z - 0.001593626000179782*x4*y4*z + 
     0.7967500414090255*y5*z - 0.1413391124976263*x*y5*z + 
     0.02144754466720601*x2*y5*z - 0.0017146246969075556*x3*y5*z - 
     0.32518149804509167*y6*z + 0.032814674387738094*x*y6*z - 
     0.002170577051887808*x2*y6*z + 0.07844547785203164*y7*z - 
     0.003447480882883837*x*y7*z - 0.008482393235999383*y8*z + 
     1.0151261585320852*z2 - 0.5*lnbara*z2 - 1.1666666666666667*x*z2 + 
     0.9475497763912626*x2*z2 - 0.7018887232527871*x3*z2 + 
     0.3912497929548728*x4*z2 - 0.14891101172945004*x5*z2 + 
     0.034214988369111896*x6*z2 - 0.0035694255405763686*x7*z2 - 
     1.1666666666666667*y*z2 + 0.8024502236087374*x*y*z2 - 
     0.5264165424395904*x2*y*z2 + 0.2703334989694351*x3*y*z2 - 
     0.09722222222222222*x4*y*z2 + 0.02144754466720601*x5*y*z2 - 
     0.002170577051887808*x6*y*z2 + 0.9475497763912626*y2*z2 - 
     0.5264165424395904*x*y2*z2 + 0.24183258797087528*x2*y2*z2 - 
     0.08061086265695844*x3*y2*z2 + 0.016854786438511633*x4*y2*z2 - 
     0.0016401041325782484*x5*y2*z2 - 0.7018887232527871*y3*z2 + 
     0.2703334989694351*x*y3*z2 - 0.08061086265695844*x2*y3*z2 + 
     0.015633763259978388*x3*y3*z2 - 0.0014423776292700654*x4*y3*z2 + 
     0.3912497929548728*y4*z2 - 0.09722222222222222*x*y4*z2 + 
     0.016854786438511633*x2*y4*z2 - 0.0014423776292700654*x3*y4*z2 - 
     0.14891101172945004*y5*z2 + 0.02144754466720601*x*y5*z2 - 
     0.0016401041325782484*x2*y5*z2 + 0.034214988369111896*y6*z2 - 
     0.002170577051887808*x*y6*z2 - 0.0035694255405763686*y7*z2 - 
     1.5908499254637543*z3 + 1.1666666666666667*lnbara*z3 + 
     1.4341500745362459*x*z3 - 0.7018887232527871*x2*z3 + 
     0.32407407407407407*x3*z3 - 0.11065736599838195*x4*z3 + 
     0.02369484952567423*x5*z3 - 0.0023528108443965027*x6*z3 + 
     1.4341500745362459*y*z3 - 0.6355283160951086*x*y*z3 + 
     0.2703334989694351*x2*y*z3 - 0.08696329423516654*x3*y*z3 + 
     0.01783238274379704*x4*y*z3 - 0.0017146246969075556*x5*y*z3 - 
     0.7018887232527871*y2*z3 + 0.2703334989694351*x*y2*z3 - 
     0.08061086265695844*x2*y2*z3 + 0.015633763259978388*x3*y2*z3 - 
     0.0014423776292700654*x4*y2*z3 + 0.32407407407407407*y3*z3 - 
     0.08696329423516654*x*y3*z3 + 0.015633763259978388*x2*y3*z3 - 
     0.0013649140752726215*x3*y3*z3 - 0.11065736599838195*y4*z3 + 
     0.01783238274379704*x*y4*z3 - 0.0014423776292700654*x2*y4*z3 + 
     0.02369484952567423*y5*z3 - 0.0017146246969075556*x*y5*z3 - 
     0.0023528108443965027*y6*z3 + 1.6691998509275083*z4 - 
     1.75*lnbara*z4 - 1.2828611525201365*x*z4 + 0.3912497929548728*x2*
      z4 - 0.11065736599838195*x3*z4 + 0.02125202540614893*x4*z4 - 
     0.001965839940596915*x5*z4 - 1.2828611525201365*y*z4 + 
     0.3651948171256735*x*y*z4 - 0.09722222222222222*x2*y*z4 + 
     0.01783238274379704*x3*y*z4 - 0.001593626000179782*x4*y*z4 + 
     0.3912497929548728*y2*z4 - 0.09722222222222222*x*y2*z4 + 
     0.016854786438511633*x2*y2*z4 - 0.0014423776292700654*x3*y2*z4 - 
     0.11065736599838195*y3*z4 + 0.01783238274379704*x*y3*z4 - 
     0.0014423776292700654*x2*y3*z4 + 0.02125202540614893*y4*z4 - 
     0.001593626000179782*x*y4*z4 - 0.001965839940596915*y5*z4 - 
     1.1560553899194537*z5 + 1.75*lnbara*z5 + 0.7967500414090255*x*z5 - 
     0.14891101172945004*x2*z5 + 0.02369484952567423*x3*z5 - 
     0.001965839940596915*x4*z5 + 0.7967500414090255*y*z5 - 
     0.1413391124976263*x*y*z5 + 0.02144754466720601*x2*y*z5 - 
     0.0017146246969075556*x3*y*z5 - 0.14891101172945004*y2*z5 + 
     0.02144754466720601*x*y2*z5 - 0.0016401041325782484*x2*y2*z5 + 
     0.02369484952567423*y3*z5 - 0.0017146246969075556*x*y3*z5 - 
     0.001965839940596915*y4*z5 + 0.505120246143294*z6 - 
     1.1666666666666667*lnbara*z6 - 0.32518149804509167*x*z6 + 
     0.034214988369111896*x2*z6 - 0.0023528108443965027*x3*z6 - 
     0.32518149804509167*y*z6 + 0.032814674387738094*x*y*z6 - 
     0.002170577051887808*x2*y*z6 + 0.034214988369111896*y2*z6 - 
     0.002170577051887808*x*y2*z6 - 0.0023528108443965027*y3*z6 - 
     0.12357110604852839*z7 + 0.5*lnbara*z7 + 0.07844547785203164*x*z7 - 
     0.0035694255405763686*x2*z7 + 0.07844547785203164*y*z7 - 
     0.003447480882883837*x*y*z7 - 0.0035694255405763686*y2*z7 + 
     0.011281407049124191*z8 - 0.125*lnbara*z8 - 0.008482393235999383*x*
      z8 - 0.008482393235999383*y*z8 + 0.0006314866025416194*z9 + 
     0.013888888888888888*lnbara*z9;

  ttothei = 1.0L;
  result = Iexp[0];

  for (i=1; i<nTerms; i++) {
    ttothei *= tinit;
    result += Iexp[i]*ttothei;
  }
  foo->value = _a * result;

  ttothei = 1.0L;
  result = Iexp[1];

  for (i=2; i<nTerms; i++) {
    ttothei *= tinit;
    result += i*Iexp[i]*ttothei;
  }
  foo->deriv = _a * result;

  return 0;
}

/* **************************************************************** */
