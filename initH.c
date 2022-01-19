/* Routines for setup and initialization of H-type functions */

#include "internal.h"

void TVIL_cHd1Roots (TVIL_HTYPE *, TVIL_REAL *);

/* TVIL_REAL u2, u3, u4, u5, u6; */
/* TVIL_REAL v2, v3, v4, v5, v6; */
/* TVIL_REAL w2, w3, w4, w5, w6; */
/* TVIL_REAL x2, x3, x4, x5, x6; */
/* TVIL_REAL y2, y3, y4, y5, y6; */
/* TVIL_REAL z2, z3, z4, z5, z6; */

/* **************************************************************** */
/* **************************************************************** */

void TVIL_cHden (TVIL_REAL u,
		 TVIL_REAL v,
		 TVIL_REAL w,
		 TVIL_REAL x,
		 TVIL_REAL y,
		 TVIL_REAL z,
		 TVIL_REAL *result)
{
  TVIL_REAL  u2 = u*u;
  TVIL_REAL  v2 = v*v;
  TVIL_REAL  w2 = w*w;
  TVIL_REAL  x2 = x*x;
  TVIL_REAL  y2 = y*y;
  TVIL_REAL  z2 = z*z;

  if (SAME6(u,v,w,x,y,z)) 
    {
      *(result) = -_a;
      *(result+1) = _a - u;
      *(result+2) = 0;
      *(result+3) = 0;
    }
  else if (SAME4(u,v,y,z) && SAME2(w,x))
    {
      *(result) = _a2;
      *(result+1) = -2*_a2 + 2*_a*u;
      *(result+2) = _a2 - 2*_a*u + 2*u*w - w2;
      *(result+3) = 0;
    }
  else if (SAME4(u,w,x,y) && SAME2(v,z))
    {
      *(result) = _a2;
      *(result+1) = -2*_a2 + 2*_a*u;
      *(result+2) = _a2 - 2*_a*u + 2*u*v - v2;
      *(result+3) = 0;
    }
  else if (SAME4(v,w,x,z) && SAME2(u,y))
    {
      *(result) = _a2;
      *(result+1) = -2*_a2 + 2*_a*v;
      *(result+2) = _a2 - u2 - 2*_a*v + 2*u*v;
      *(result+3) = 0;
    }
  else if (SAME3(u,v,w) && SAME3(x,y,z))
    {
      *(result) = 2*_a2;
      *(result+1) = -4*_a2 + 3*_a*u + _a*x;
      *(result+2) = 2*_a2 - 3*_a*u - _a*x + 3*u*x - x2;
      *(result+3) = 0;
    }
  else if (SAME3(u,v,x) && SAME3(w,y,z))
    {
      *(result) = 2*_a2;
      *(result+1) = -4*_a2 + _a*u + 3*_a*w;
      *(result+2) = 2*_a2 - _a*u - u2 - 3*_a*w + 3*u*w;
      *(result+3) = 0;
    }
  else if (SAME3(u,w,z) && SAME3(v,x,y))
    {
      *(result) = 2*_a2;
      *(result+1) = -4*_a2 + _a*u + 3*_a*v;
      *(result+2) = 2*_a2 - _a*u - u2 - 3*_a*v + 3*u*v;
      *(result+3) = 0;
    }
  else if (SAME3(u,x,z) && SAME3(v,w,y))
    {
      *(result) = 2*_a2;
      *(result+1) = -4*_a2 + 3*_a*u + _a*v;
      *(result+2) = 2*_a2 - 3*_a*u - _a*v + 3*u*v - v2;
      *(result+3) = 0;
    }
  else 
    {
      *(result) = -2*_a3;
      *(result+1) = 6*_a3 - _a2*u - _a2*v - _a2*w - _a2*x - _a2*y - _a2*z;
      *(result+2) = -6*_a3 + 2*_a2*u + _a*u2 + 2*_a2*v - _a*u*v + _a*v2 + 2*_a2*w - _a*u*w - _a*v*w + _a*w2 + 2*_a2*x - _a*u*x - _a*v*x + _a*x2 + 2*_a2*y - _a*v*y - _a*w*y - _a*x*y + _a*y2 + 2*_a2*z - _a*u*z - _a*w*z - _a*x*z - _a*y*z + _a*z2;
      *(result+3) = 2*_a3 - _a2*u - _a*u2 - _a2*v + _a*u*v - _a*v2 - _a2*w + _a*u*w + _a*v*w - _a*w2 - _a2*x + _a*u*x + _a*v*x + u*v*x - u*w*x - v*w*x + w2*x - _a*x2 + w*x2 - _a2*y + u2*y + _a*v*y - u*v*y + _a*w*y - u*w*y + v*w*y + _a*x*y - u*x*y - w*x*y - _a*y2 + u*y2 - _a2*z + _a*u*z - u*v*z + v2*z + _a*w*z + u*w*z - v*w*z + _a*x*z - v*x*z - w*x*z + _a*y*z - u*y*z - v*y*z + x*y*z - _a*z2 + v*z2;
    }

  return;
}

/* **************************************************************** */
/* **************************************************************** */

void TVIL_cHnum (TVIL_REAL u,
		 TVIL_REAL v,
		 TVIL_REAL w,
		 TVIL_REAL x,
		 TVIL_REAL y,
		 TVIL_REAL z,
		 TVIL_REAL *result)
{
  TVIL_REAL  u2 = u*u;
  TVIL_REAL  v2 = v*v;
  TVIL_REAL  w2 = w*w;
  TVIL_REAL  x2 = x*x;
  TVIL_REAL  y2 = y*y;
  TVIL_REAL  z2 = z*z;
  
  if (SAME6(u,v,w,x,y,z))
    {
      *(result) = -6*_a + 6*u;
      *(result+1) = 0;
      *(result+2) = 0;
    }
  else if (SAME4(u,v,y,z) && SAME2(w,x))
    {
      *(result) = 6*_a2 - 4*_a*u - 2*_a*w;
      *(result+1) = -6*_a2 + 12*_a*u - 12*u*w + 6*w2;
      *(result+2) = 0;
    }
  else if (SAME4(u,w,x,y) && SAME2(v,z))
    {
      *(result) = 6*_a2 - 4*_a*u - 2*_a*v;
      *(result+1) = -6*_a2 + 12*_a*u - 12*u*v + 6*v2;
      *(result+2) = 0;
    }
  else if (SAME4(v,w,x,z) && SAME2(u,y))
    {
      *(result) = 6*_a2 - 2*_a*u - 4*_a*v;
      *(result+1) = -6*_a2 + 6*u2 + 12*_a*v - 12*u*v;
      *(result+2) = 0;
    }
  else if (SAME3(u,v,w) && SAME3(x,y,z))
    {
      *(result) = 12*_a2 - 6*_a*u - 6*_a*x;
      *(result+1) = -12*_a2 + 18*_a*u + 6*_a*x - 18*u*x + 6*x2;
      *(result+2) = 0;
    }
  else if (SAME3(u,v,x) && SAME3(w,y,z))
    {
      *(result) = 12*_a2 - 6*_a*u - 6*_a*w;
      *(result+1) = -12*_a2 + 6*_a*u + 6*u2 + 18*_a*w - 18*u*w;
      *(result+2) = 0;
    }
  else if (SAME3(u,w,z) && SAME3(v,x,y))
    {
      *(result) = 12*_a2 - 6*_a*u - 6*_a*v;
      *(result+1) = -12*_a2 + 6*_a*u + 6*u2 + 18*_a*v - 18*u*v;
      *(result+2) = 0;
    }
  else if (SAME3(u,x,z) && SAME3(v,w,y))
    {
      *(result) = 12*_a2 - 6*_a*u - 6*_a*v;
      *(result+1) = -12*_a2 + 18*_a*u + 6*_a*v - 18*u*v + 6*v2;
      *(result+2) = 0;
    }
  else 
    {
      *(result) = -12*_a3 + 2*_a2*u + 2*_a2*v + 2*_a2*w + 2*_a2*x + 2*_a2*y + 2*_a2*z;
      *(result+1) =  24*_a3 - 8*_a2*u - 4*_a*u2 - 8*_a2*v + 4*_a*u*v - 4*_a*v2 - 8*_a2*w + 4*_a*u*w + 4*_a*v*w - 4*_a*w2 - 8*_a2*x + 4*_a*u*x + 4*_a*v*x - 4*_a*x2 - 8*_a2*y + 4*_a*v*y + 4*_a*w*y + 4*_a*x*y - 4*_a*y2 - 8*_a2*z + 4*_a*u*z + 4*_a*w*z + 4*_a*x*z + 4*_a*y*z - 4*_a*z2;
      *(result+2) = -12*_a3 + 6*_a2*u + 6*_a*u2 + 6*_a2*v - 6*_a*u*v + 6*_a*v2 + 6*_a2*w - 6*_a*u*w - 6*_a*v*w + 6*_a*w2 + 6*_a2*x - 6*_a*u*x - 6*_a*v*x - 6*u*v*x + 6*u*w*x + 6*v*w*x - 6*w2*x + 6*_a*x2 - 6*w*x2 + 6*_a2*y - 6*u2*y - 6*_a*v*y + 6*u*v*y - 6*_a*w*y + 6*u*w*y - 6*v*w*y - 6*_a*x*y + 6*u*x*y + 6*w*x*y + 6*_a*y2 - 6*u*y2 + 6*_a2*z - 6*_a*u*z + 6*u*v*z - 6*v2*z - 6*_a*w*z - 6*u*w*z + 6*v*w*z - 6*_a*x*z + 6*v*x*z + 6*w*x*z - 6*_a*y*z + 6*u*y*z + 6*v*y*z - 6*x*y*z + 6*_a*z2 - 6*v*z2;
    }

  return;
}

/* **************************************************************** */
/* **************************************************************** */

void TVIL_cHGden (TVIL_REAL u,
		  TVIL_REAL v,
		  TVIL_REAL w,
		  TVIL_REAL x,
		  TVIL_REAL y,
		  TVIL_REAL z,
		  TVIL_REAL *result)
{
  TVIL_REAL  u2 = u*u;
  TVIL_REAL  u3 = u2*u;
  TVIL_REAL  u4 = u2*u2;
  TVIL_REAL  u5 = u2*u3;

  TVIL_REAL  v2 = v*v;
  TVIL_REAL  v3 = v2*v;
  TVIL_REAL  v4 = v2*v2;
  TVIL_REAL  v5 = v2*v3;

  TVIL_REAL  w2 = w*w;
  TVIL_REAL  w3 = w2*w;
  TVIL_REAL  w4 = w2*w2;

  TVIL_REAL  x2 = x*x;
  TVIL_REAL  x3 = x2*x;
  TVIL_REAL  x4 = x2*x2;
  TVIL_REAL  x5 = x2*x3;
  TVIL_REAL  x6 = x3*x3;

  TVIL_REAL  y2 = y*y;
  TVIL_REAL  y3 = y2*y;
  TVIL_REAL  y4 = y2*y2;

  TVIL_REAL  z2 = z*z;
  TVIL_REAL  z3 = z2*z;
  TVIL_REAL  z4 = z2*z2;

  if (SAME6(u,v,w,x,y,z))
    {
      *(result) = 1;
      *(result+1) = 0;
      *(result+2) = 0;
      *(result+3) = 0;
      *(result+4) = 0;
      *(result+5) = 0;
      *(result+6) = 0;
      *(result+7) = 0;
    }
  else if (SAME5(u,v,w,x,y))
    {
      *(result) = -6*_a3;
      *(result+1) = 18*_a3 - 17*_a2*u - _a2*z;
      *(result+2) = -18*_a3 + 34*_a2*u - 12*_a*u2 + 2*_a2*z - 10*_a*u*z + 4*_a*z2;
      *(result+3) = 6*_a3 - 17*_a2*u + 12*_a*u2 - _a2*z + 10*_a*u*z - 12*u2*z - 4*_a*z2 + 7*u*z2 - z3;
      *(result+4) = 0;
      *(result+5) = 0;
      *(result+6) = 0;
      *(result+7) = 0;
    }
  else if (SAME5(u,v,w,x,z))
    {
      *(result) = -6*_a3;
      *(result+1) = 18*_a3 - 17*_a2*u - _a2*y;
      *(result+2) = -18*_a3 + 34*_a2*u - 12*_a*u2 + 2*_a2*y - 10*_a*u*y + 4*_a*y2;
      *(result+3) = 6*_a3 - 17*_a2*u + 12*_a*u2 - _a2*y + 10*_a*u*y - 12*u2*y - 4*_a*y2 + 7*u*y2 - y3;
      *(result+4) = 0;
      *(result+5) = 0;
      *(result+6) = 0;
      *(result+7) = 0;
    }
  else if (SAME5(u,w,x,y,z))
    {
      *(result) = -6*_a3;
      *(result+1) = 18*_a3 - 17*_a2*u - _a2*v;
      *(result+2) = -18*_a3 + 34*_a2*u - 12*_a*u2 + 2*_a2*v - 10*_a*u*v + 4*_a*v2;
      *(result+3) = 6*_a3 - 17*_a2*u + 12*_a*u2 - _a2*v + 10*_a*u*v - 12*u2*v - 4*_a*v2 + 7*u*v2 - v3;
      *(result+4) = 0;
      *(result+5) = 0;
      *(result+6) = 0;
      *(result+7) = 0;
    }
  else if (SAME5(v,w,x,y,z))
    {
      *(result) = -6*_a3;
      *(result+1) = 18*_a3 - _a2*u - 17*_a2*v;
      *(result+2) = -18*_a3 + 2*_a2*u + 4*_a*u2 + 34*_a2*v - 10*_a*u*v - 12*_a*v2;
      *(result+3) = 6*_a3 - _a2*u - 4*_a*u2 - u3 - 17*_a2*v + 10*_a*u*v + 7*u2*v + 12*_a*v2 - 12*u*v2;
      *(result+4) = 0;
      *(result+5) = 0;
      *(result+6) = 0;
      *(result+7) = 0;
    }
  else if (SAME4(u,w,x,y) && SAME2(v,z))
    {
      *(result) = -3*_a3;
      *(result+1) = 9*_a3 - 10*_a2*u + _a2*v;
      *(result+2) = -9*_a3 + 20*_a2*u - 8*_a*u2 - 2*_a2*v - 4*_a*u*v + 3*_a*v2;
      *(result+3) = 3*_a3 - 10*_a2*u + 8*_a*u2 + _a2*v + 4*_a*u*v - 8*u2*v - 3*_a*v2 + 6*u*v2 - v3;
      *(result+4) = 0;
      *(result+5) = 0;
      *(result+6) = 0;
      *(result+7) = 0;
    }
  else if (SAME4(v,w,x,z) && SAME2(u,y))
    {
      *(result) = -3*_a3;
      *(result+1) = 9*_a3 + _a2*u - 10*_a2*v;
      *(result+2) = -9*_a3 - 2*_a2*u + 3*_a*u2 + 20*_a2*v - 4*_a*u*v - 8*_a*v2;
      *(result+3) = 3*_a3 + _a2*u - 3*_a*u2 - u3 - 10*_a2*v + 4*_a*u*v + 6*u2*v + 8*_a*v2 - 8*u*v2;
      *(result+4) = 0;
      *(result+5) = 0;
      *(result+6) = 0;
      *(result+7) = 0;
    }
  else if (SAME3(u,v,w) && SAME3(x,y,z))
    {
      *(result) = -6*_a3;
      *(result+1) = 18*_a3 - 17*_a2*u - _a2*x;
      *(result+2) = -18*_a3 + 34*_a2*u - 12*_a*u2 + 2*_a2*x - 10*_a*u*x + 4*_a*x2;
      *(result+3) = 6*_a3 - 17*_a2*u + 12*_a*u2 - _a2*x + 10*_a*u*x - 12*u2*x - 4*_a*x2 + 7*u*x2 - x3;
      *(result+4) = 0;
      *(result+5) = 0;
      *(result+6) = 0; 
      *(result+7) = 0;
    }
  else if (SAME3(u,v,x) && SAME3(w,y,z))
    {
      *(result) = -6*_a3;
      *(result+1) = 18*_a3 - _a2*u - 17*_a2*w;
      *(result+2) = -18*_a3 + 2*_a2*u + 4*_a*u2 + 34*_a2*w - 10*_a*u*w - 12*_a*w2;
      *(result+3) = 6*_a3 - _a2*u - 4*_a*u2 - u3 - 17*_a2*w + 10*_a*u*w + 7*u2*w + 12*_a*w2 - 12*u*w2;
      *(result+4) = 0;
      *(result+5) = 0;
      *(result+6) = 0; 
      *(result+7) = 0;
    }
  else if (SAME3(u,w,z) && SAME3(v,x,y))
    {
      *(result) = -6*_a3;
      *(result+1) = 18*_a3 - _a2*u - 17*_a2*v;
      *(result+2) = -18*_a3 + 2*_a2*u + 4*_a*u2 + 34*_a2*v - 10*_a*u*v - 12*_a*v2;
      *(result+3) = 6*_a3 - _a2*u - 4*_a*u2 - u3 - 17*_a2*v + 10*_a*u*v + 7*u2*v + 12*_a*v2 - 12*u*v2;
      *(result+4) = 0;
      *(result+5) = 0;
      *(result+6) = 0; 
      *(result+7) = 0;
    }
  else if (SAME3(u,x,z) && SAME3(v,w,y))
    {
      *(result) = -6*_a3;
      *(result+1) = 18*_a3 - 17*_a2*u - _a2*v;
      *(result+2) = -18*_a3 + 34*_a2*u - 12*_a*u2 + 2*_a2*v - 10*_a*u*v + 4*_a*v2;
      *(result+3) = 6*_a3 - 17*_a2*u + 12*_a*u2 - _a2*v + 10*_a*u*v - 12*u2*v - 4*_a*v2 + 7*u*v2 - v3;
      *(result+4) = 0;
      *(result+5) = 0;
      *(result+6) = 0; 
      *(result+7) = 0;
    }
  else if (SAME4(u,v,y,z))
    {
      *(result) = -6*_a3;
      *(result+1) = 18*_a3 - 20*_a2*u - 3*_a2*w + 5*_a2*x;
      *(result+2) = -18*_a3 + 40*_a2*u - 16*_a*u2 + 6*_a2*w - 16*_a*u*w + 3*_a*w2 - 10*_a2*x + 8*_a*u*x + 4*_a*w*x - _a*x2;
      *(result+3) = 6*_a3 - 20*_a2*u + 16*_a*u2 - 3*_a2*w + 16*_a*u*w - 16*u2*w - 3*_a*w2 + 4*u*w2 + 5*_a2*x - 8*_a*u*x - 4*_a*w*x + 8*u*w*x - w2*x + _a*x2 - w*x2;
      *(result+4) = 0;
      *(result+5) = 0;
      *(result+6) = 0; 
      *(result+7) = 0;
    }
  else if (SAME2(u,z) && SAME2(v,y) && SAME2(w,x))
    {
      *(result) = 6*_a4;
      *(result+1) = -24*_a4 + 10*_a3*u + 10*_a3*v + 4*_a3*w;
      *(result+2) = 36*_a4 - 30*_a3*u - _a2*u2 - 30*_a3*v + 18*_a2*u*v - _a2*v2 - 12*_a3*w + 14*_a2*u*w + 14*_a2*v*w - 8*_a2*w2;
      *(result+3) = -24*_a4 + 30*_a3*u + 2*_a2*u2 - 4*_a*u3 + 30*_a3*v - 36*_a2*u*v + 4*_a*u2*v + 2*_a2*v2 + 4*_a*u*v2 - 4*_a*v3 + 12*_a3*w - 28*_a2*u*w + 6*_a*u2*w - 28*_a2*v*w + 20*_a*u*v*w + 6*_a*v2*w + 16*_a2*w2 - 2*_a*u*w2 - 2*_a*v*w2 - 4*_a*w3;
      *(result+4) = 6*_a4 - 10*_a3*u - _a2*u2 + 4*_a*u3 + u4 - 10*_a3*v + 18*_a2*u*v - 4*_a*u2*v - 4*u3*v - _a2*v2 - 4*_a*u*v2 + 6*u2*v2 + 4*_a*v3 - 4*u*v3 + v4 - 4*_a3*w + 14*_a2*u*w - 6*_a*u2*w - 4*u3*w + 14*_a2*v*w - 20*_a*u*v*w + 4*u2*v*w - 6*_a*v2*w + 4*u*v2*w - 4*v3*w - 8*_a2*w2 + 2*_a*u*w2 + 7*u2*w2 + 2*_a*v*w2 + 2*u*v*w2 + 7*v2*w2 + 4*_a*w3 - 6*u*w3 - 6*v*w3 + 2*w4;
      *(result+5) = 0;
      *(result+6) = 0; 
      *(result+7) = 0;
    }
  else if (SAME2(u,v) && SAME2(y,z))
    {
      *(result) = 18*_a4;
      *(result+1) = -72*_a4 + 42*_a3*u + 9*_a3*w - 21*_a3*x + 42*_a3*y;
      *(result+2) = 108*_a4 - 126*_a3*u + 15*_a2*u2 - 27*_a3*w + 30*_a2*u*w - 9*_a2*w2 + 63*_a3*x - 32*_a2*u*x - 15*_a2*w*x + 8*_a2*x2 - 126*_a3*y + 98*_a2*u*y + 30*_a2*w*y - 32*_a2*x*y + 15*_a2*y2;
      *(result+3) = -72*_a4 + 126*_a3*u - 30*_a2*u2 - 12*_a*u3 + 27*_a3*w - 60*_a2*u*w + 24*_a*u2*w + 18*_a2*w2 - 12*_a*u*w2 - 63*_a3*x + 64*_a2*u*x - 2*_a*u2*x + 30*_a2*w*x - 28*_a*u*w*x + 6*_a*w2*x - 16*_a2*x2 + 6*_a*u*x2 + 7*_a*w*x2 - _a*x3 + 126*_a3*y - 196*_a2*u*y + 44*_a*u2*y - 60*_a2*w*y + 64*_a*u*w*y - 12*_a*w2*y + 64*_a2*x*y - 44*_a*u*x*y - 28*_a*w*x*y + 6*_a*x2*y - 30*_a2*y2 + 44*_a*u*y2 + 24*_a*w*y2 - 2*_a*x*y2 - 12*_a*y3;
      *(result+4) = 18*_a4 - 42*_a3*u + 15*_a2*u2 + 12*_a*u3 - 9*_a3*w + 30*_a2*u*w - 24*_a*u2*w - 9*_a2*w2 + 12*_a*u*w2 + 21*_a3*x - 32*_a2*u*x + 2*_a*u2*x + 4*u3*x - 15*_a2*w*x + 28*_a*u*w*x - 8*u2*w*x - 6*_a*w2*x + 4*u*w2*x + 8*_a2*x2 - 6*_a*u*x2 - u2*x2 - 7*_a*w*x2 + 6*u*w*x2 - w2*x2 + _a*x3 - w*x3 - 42*_a3*y + 98*_a2*u*y - 44*_a*u2*y - 16*u3*y + 30*_a2*w*y - 64*_a*u*w*y + 32*u2*w*y + 12*_a*w2*y - 16*u*w2*y - 32*_a2*x*y + 44*_a*u*x*y - 4*u2*x*y + 28*_a*w*x*y - 32*u*w*x*y + 4*w2*x*y - 6*_a*x2*y + 2*u*x2*y + 6*w*x2*y + 15*_a2*y2 - 44*_a*u*y2 + 32*u2*y2 - 24*_a*w*y2 + 32*u*w*y2 + 2*_a*x*y2 - 4*u*x*y2 - 8*w*x*y2 - x2*y2 + 12*_a*y3 - 16*u*y3 + 4*x*y3;
      *(result+5) = 0;
      *(result+6) = 0; 
      *(result+7) = 0;
    }
  else if (SAME3(u,v,x))
    {
      *(result) = 6*_a4;
      *(result+1) = -24*_a4 + 7*_a3*u + 3*_a3*w + 7*_a3*y + 7*_a3*z;
      *(result+2) = 36*_a4 - 21*_a3*u - 3*_a2*u2 - 9*_a3*w + 5*_a2*u*w - 3*_a2*w2 - 21*_a3*y + 11*_a2*u*y + 5*_a2*w*y - 3*_a2*y2 - 21*_a3*z + 11*_a2*u*z + 5*_a2*w*z + 11*_a2*y*z - 3*_a2*z2;
      *(result+3) = -24*_a4 + 21*_a3*u + 6*_a2*u2 - 3*_a*u3 + 9*_a3*w - 10*_a2*u*w + _a*u2*w + 6*_a2*w2 - 2*_a*u*w2 + 21*_a3*y - 22*_a2*u*y + _a*u2*y - 10*_a2*w*y + 6*_a*u*w*y - 2*_a*w2*y + 6*_a2*y2 + _a*u*y2 + _a*w*y2 - 3*_a*y3 + 21*_a3*z - 22*_a2*u*z + _a*u2*z - 10*_a2*w*z + 6*_a*u*w*z - 2*_a*w2*z - 22*_a2*y*z + 12*_a*u*y*z + 6*_a*w*y*z + _a*y2*z + 6*_a2*z2 + _a*u*z2 + _a*w*z2 + _a*y*z2 - 3*_a*z3;
      *(result+4) = 6*_a4 - 7*_a3*u - 3*_a2*u2 + 3*_a*u3 + u4 - 3*_a3*w + 5*_a2*u*w - _a*u2*w - u3*w - 3*_a2*w2 + 2*_a*u*w2 + u2*w2 - 7*_a3*y + 11*_a2*u*y - _a*u2*y - 3*u3*y + 5*_a2*w*y - 6*_a*u*w*y + u2*w*y + 2*_a*w2*y - 2*u*w2*y - 3*_a2*y2 - _a*u*y2 + 4*u2*y2 - _a*w*y2 + u*w*y2 + w2*y2 + 3*_a*y3 - 3*u*y3 - w*y3 + y4 - 7*_a3*z + 11*_a2*u*z - _a*u2*z - 3*u3*z + 5*_a2*w*z - 6*_a*u*w*z + u2*w*z + 2*_a*w2*z - 2*u*w2*z + 11*_a2*y*z - 12*_a*u*y*z + u2*y*z - 6*_a*w*y*z + 6*u*w*y*z - 2*w2*y*z - _a*y2*z + u*y2*z + w*y2*z - 3*y3*z - 3*_a2*z2 - _a*u*z2 + 4*u2*z2 - _a*w*z2 + u*w*z2 + w2*z2 - _a*y*z2 + u*y*z2 + w*y*z2 + 4*y2*z2 + 3*_a*z3 - 3*u*z3 - w*z3 - 3*y*z3 + z4;
      *(result+5) = 0;
      *(result+6) = 0; 
      *(result+7) = 0;
    }
  else if (SAME3(x,y,z))
    {
      *(result) = 6*_a4;
      *(result+1) = -24*_a4 + 7*_a3*u + 7*_a3*v + 3*_a3*w + 7*_a3*x;
      *(result+2) = 36*_a4 - 21*_a3*u - 3*_a2*u2 - 21*_a3*v + 11*_a2*u*v - 3*_a2*v2 - 9*_a3*w + 5*_a2*u*w + 5*_a2*v*w - 3*_a2*w2 - 21*_a3*x + 11*_a2*u*x + 11*_a2*v*x + 5*_a2*w*x - 3*_a2*x2;
      *(result+3) = -24*_a4 + 21*_a3*u + 6*_a2*u2 - 3*_a*u3 + 21*_a3*v - 22*_a2*u*v + _a*u2*v + 6*_a2*v2 + _a*u*v2 - 3*_a*v3 + 9*_a3*w - 10*_a2*u*w + _a*u2*w - 10*_a2*v*w + 6*_a*u*v*w + _a*v2*w + 6*_a2*w2 - 2*_a*u*w2 - 2*_a*v*w2 + 21*_a3*x - 22*_a2*u*x + _a*u2*x - 22*_a2*v*x + 12*_a*u*v*x + _a*v2*x - 10*_a2*w*x + 6*_a*u*w*x + 6*_a*v*w*x - 2*_a*w2*x + 6*_a2*x2 + _a*u*x2 + _a*v*x2 + _a*w*x2 - 3*_a*x3;
      *(result+4) = 6*_a4 - 7*_a3*u - 3*_a2*u2 + 3*_a*u3 + u4 - 7*_a3*v + 11*_a2*u*v - _a*u2*v - 3*u3*v - 3*_a2*v2 - _a*u*v2 + 4*u2*v2 + 3*_a*v3 - 3*u*v3 + v4 - 3*_a3*w + 5*_a2*u*w - _a*u2*w - u3*w + 5*_a2*v*w - 6*_a*u*v*w + u2*v*w - _a*v2*w + u*v2*w - v3*w - 3*_a2*w2 + 2*_a*u*w2 + u2*w2 + 2*_a*v*w2 - 2*u*v*w2 + v2*w2 - 7*_a3*x + 11*_a2*u*x - _a*u2*x - 3*u3*x + 11*_a2*v*x - 12*_a*u*v*x + u2*v*x - _a*v2*x + u*v2*x - 3*v3*x + 5*_a2*w*x - 6*_a*u*w*x + u2*w*x - 6*_a*v*w*x + 6*u*v*w*x + v2*w*x + 2*_a*w2*x - 2*u*w2*x - 2*v*w2*x - 3*_a2*x2 - _a*u*x2 + 4*u2*x2 - _a*v*x2 + u*v*x2 + 4*v2*x2 - _a*w*x2 + u*w*x2 + v*w*x2 + w2*x2 + 3*_a*x3 - 3*u*x3 - 3*v*x3 - w*x3 + x4;
      *(result+5) = 0;
      *(result+6) = 0; 
      *(result+7) = 0;
    }
  else if (SAME3(u,v,w) && SAME2(x,y))
    {
      *(result) = -18*_a5;
      *(result+1) = 90*_a5 - 51*_a4*u - 36*_a4*x - 3*_a4*z;
      *(result+2) = -180*_a5 + 204*_a4*u - 36*_a3*u2 + 144*_a4*x - 119*_a3*u*x - _a3*x2 + 12*_a4*z - 13*_a3*u*z - 23*_a3*x*z + 12*_a3*z2;
      *(result+3) = 180*_a5 - 306*_a4*u + 108*_a3*u2 - 216*_a4*x + 357*_a3*u*x - 96*_a2*u2*x + 3*_a3*x2 - 44*_a2*u*x2 + 17*_a2*x3 - 18*_a4*z + 39*_a3*u*z - 12*_a2*u2*z + 69*_a3*x*z - 77*_a2*u*x*z - 10*_a2*x2*z - 36*_a3*z2 + 31*_a2*u*z2 + 14*_a2*x*z2 - 3*_a2*z3;
      *(result+4) = -90*_a5 + 204*_a4*u - 108*_a3*u2 + 144*_a4*x - 357*_a3*u*x + 192*_a2*u2*x - 3*_a3*x2 + 88*_a2*u*x2 - 64*_a*u2*x2 - 34*_a2*x3 + 32*_a*u*x3 - 4*_a*x4 + 12*_a4*z - 39*_a3*u*z + 24*_a2*u2*z - 69*_a3*x*z + 154*_a2*u*x*z - 64*_a*u2*x*z + 20*_a2*x2*z - 56*_a*u*x2*z + 18*_a*x3*z + 36*_a3*z2 - 62*_a2*u*z2 + 20*_a*u2*z2 - 28*_a2*x*z2 + 43*_a*u*x*z2 - 9*_a*x2*z2 + 6*_a2*z3 - 7*_a*u*z3 + _a*x*z3;
      *(result+5) = 18*_a5 - 51*_a4*u + 36*_a3*u2 - 36*_a4*x + 119*_a3*u*x - 96*_a2*u2*x + _a3*x2 - 44*_a2*u*x2 + 64*_a*u2*x2 + 17*_a2*x3 - 32*_a*u*x3 + 4*_a*x4 - 3*_a4*z + 13*_a3*u*z - 12*_a2*u2*z + 23*_a3*x*z - 77*_a2*u*x*z + 64*_a*u2*x*z - 10*_a2*x2*z + 56*_a*u*x2*z - 64*u2*x2*z - 18*_a*x3*z + 32*u*x3*z - 4*x4*z - 12*_a3*z2 + 31*_a2*u*z2 - 20*_a*u2*z2 + 14*_a2*x*z2 - 43*_a*u*x*z2 + 32*u2*x*z2 + 9*_a*x2*z2 - 12*u*x2*z2 + x3*z2 - 3*_a2*z3 + 7*_a*u*z3 - 4*u2*z3 - _a*x*z3 + u*x*z3;
      *(result+6) = 0;
      *(result+7) = 0;
    }
  else if (SAME3(u,v,w) && SAME2(x,z))
    {
      *(result) = -18*_a5;
      *(result+1) = 90*_a5 - 51*_a4*u - 36*_a4*x - 3*_a4*y;
      *(result+2) = -180*_a5 + 204*_a4*u - 36*_a3*u2 + 144*_a4*x - 119*_a3*u*x - _a3*x2 + 12*_a4*y - 13*_a3*u*y - 23*_a3*x*y + 12*_a3*y2;
      *(result+3) = 180*_a5 - 306*_a4*u + 108*_a3*u2 - 216*_a4*x + 357*_a3*u*x - 96*_a2*u2*x + 3*_a3*x2 - 44*_a2*u*x2 + 17*_a2*x3 - 18*_a4*y + 39*_a3*u*y - 12*_a2*u2*y + 69*_a3*x*y - 77*_a2*u*x*y - 10*_a2*x2*y - 36*_a3*y2 + 31*_a2*u*y2 + 14*_a2*x*y2 - 3*_a2*y3;
      *(result+4) = -90*_a5 + 204*_a4*u - 108*_a3*u2 + 144*_a4*x - 357*_a3*u*x + 192*_a2*u2*x - 3*_a3*x2 + 88*_a2*u*x2 - 64*_a*u2*x2 - 34*_a2*x3 + 32*_a*u*x3 - 4*_a*x4 + 12*_a4*y - 39*_a3*u*y + 24*_a2*u2*y - 69*_a3*x*y + 154*_a2*u*x*y - 64*_a*u2*x*y + 20*_a2*x2*y - 56*_a*u*x2*y + 18*_a*x3*y + 36*_a3*y2 - 62*_a2*u*y2 + 20*_a*u2*y2 - 28*_a2*x*y2 + 43*_a*u*x*y2 - 9*_a*x2*y2 + 6*_a2*y3 - 7*_a*u*y3 + _a*x*y3;
      *(result+5) = 18*_a5 - 51*_a4*u + 36*_a3*u2 - 36*_a4*x + 119*_a3*u*x - 96*_a2*u2*x + _a3*x2 - 44*_a2*u*x2 + 64*_a*u2*x2 + 17*_a2*x3 - 32*_a*u*x3 + 4*_a*x4 - 3*_a4*y + 13*_a3*u*y - 12*_a2*u2*y + 23*_a3*x*y - 77*_a2*u*x*y + 64*_a*u2*x*y - 10*_a2*x2*y + 56*_a*u*x2*y - 64*u2*x2*y - 18*_a*x3*y + 32*u*x3*y - 4*x4*y - 12*_a3*y2 + 31*_a2*u*y2 - 20*_a*u2*y2 + 14*_a2*x*y2 - 43*_a*u*x*y2 + 32*u2*x*y2 + 9*_a*x2*y2 - 12*u*x2*y2 + x3*y2 - 3*_a2*y3 + 7*_a*u*y3 - 4*u2*y3 - _a*x*y3 + u*x*y3;
      *(result+6) = 0;
      *(result+7) = 0;
    }
  else if (SAME3(w,y,z) && SAME2(u,x))
    {
      *(result) = -18*_a5;
      *(result+1) = 90*_a5 - 36*_a4*u - 3*_a4*v - 51*_a4*w;
      *(result+2) = -180*_a5 + 144*_a4*u - _a3*u2 + 12*_a4*v - 23*_a3*u*v + 12*_a3*v2 + 204*_a4*w - 119*_a3*u*w - 13*_a3*v*w - 36*_a3*w2;
      *(result+3) = 180*_a5 - 216*_a4*u + 3*_a3*u2 + 17*_a2*u3 - 18*_a4*v + 69*_a3*u*v - 10*_a2*u2*v - 36*_a3*v2 + 14*_a2*u*v2 - 3*_a2*v3 - 306*_a4*w + 357*_a3*u*w - 44*_a2*u2*w + 39*_a3*v*w - 77*_a2*u*v*w + 31*_a2*v2*w + 108*_a3*w2 - 96*_a2*u*w2 - 12*_a2*v*w2;
      *(result+4) = -90*_a5 + 144*_a4*u - 3*_a3*u2 - 34*_a2*u3 - 4*_a*u4 + 12*_a4*v - 69*_a3*u*v + 20*_a2*u2*v + 18*_a*u3*v + 36*_a3*v2 - 28*_a2*u*v2 - 9*_a*u2*v2 + 6*_a2*v3 + _a*u*v3 + 204*_a4*w - 357*_a3*u*w + 88*_a2*u2*w + 32*_a*u3*w - 39*_a3*v*w + 154*_a2*u*v*w - 56*_a*u2*v*w - 62*_a2*v2*w + 43*_a*u*v2*w - 7*_a*v3*w - 108*_a3*w2 + 192*_a2*u*w2 - 64*_a*u2*w2 + 24*_a2*v*w2 - 64*_a*u*v*w2 + 20*_a*v2*w2;
      *(result+5) = 18*_a5 - 36*_a4*u + _a3*u2 + 17*_a2*u3 + 4*_a*u4 - 3*_a4*v + 23*_a3*u*v - 10*_a2*u2*v - 18*_a*u3*v - 4*u4*v - 12*_a3*v2 + 14*_a2*u*v2 + 9*_a*u2*v2 + u3*v2 - 3*_a2*v3 - _a*u*v3 - 51*_a4*w + 119*_a3*u*w - 44*_a2*u2*w - 32*_a*u3*w + 13*_a3*v*w - 77*_a2*u*v*w + 56*_a*u2*v*w + 32*u3*v*w + 31*_a2*v2*w - 43*_a*u*v2*w - 12*u2*v2*w + 7*_a*v3*w + u*v3*w + 36*_a3*w2 - 96*_a2*u*w2 + 64*_a*u2*w2 - 12*_a2*v*w2 + 64*_a*u*v*w2 - 64*u2*v*w2 - 20*_a*v2*w2 + 32*u*v2*w2 - 4*v3*w2;
      *(result+6) = 0;
      *(result+7) = 0;
    }
  else if (SAME3(w,y,z) && SAME2(v,x))
    {
      *(result) = -18*_a5;
      *(result+1) = 90*_a5 - 3*_a4*u - 36*_a4*v - 51*_a4*w;
      *(result+2) = -180*_a5 + 12*_a4*u + 12*_a3*u2 + 144*_a4*v - 23*_a3*u*v - _a3*v2 + 204*_a4*w - 13*_a3*u*w - 119*_a3*v*w - 36*_a3*w2;
      *(result+3) = 180*_a5 - 18*_a4*u - 36*_a3*u2 - 3*_a2*u3 - 216*_a4*v + 69*_a3*u*v + 14*_a2*u2*v + 3*_a3*v2 - 10*_a2*u*v2 + 17*_a2*v3 - 306*_a4*w + 39*_a3*u*w + 31*_a2*u2*w + 357*_a3*v*w - 77*_a2*u*v*w - 44*_a2*v2*w + 108*_a3*w2 - 12*_a2*u*w2 - 96*_a2*v*w2;
      *(result+4) = -90*_a5 + 12*_a4*u + 36*_a3*u2 + 6*_a2*u3 + 144*_a4*v - 69*_a3*u*v - 28*_a2*u2*v + _a*u3*v - 3*_a3*v2 + 20*_a2*u*v2 - 9*_a*u2*v2 - 34*_a2*v3 + 18*_a*u*v3 - 4*_a*v4 + 204*_a4*w - 39*_a3*u*w - 62*_a2*u2*w - 7*_a*u3*w - 357*_a3*v*w + 154*_a2*u*v*w + 43*_a*u2*v*w + 88*_a2*v2*w - 56*_a*u*v2*w + 32*_a*v3*w - 108*_a3*w2 + 24*_a2*u*w2 + 20*_a*u2*w2 + 192*_a2*v*w2 - 64*_a*u*v*w2 - 64*_a*v2*w2;
      *(result+5) = 18*_a5 - 3*_a4*u - 12*_a3*u2 - 3*_a2*u3 - 36*_a4*v + 23*_a3*u*v + 14*_a2*u2*v - _a*u3*v + _a3*v2 - 10*_a2*u*v2 + 9*_a*u2*v2 + 17*_a2*v3 - 18*_a*u*v3 + u2*v3 + 4*_a*v4 - 4*u*v4 - 51*_a4*w + 13*_a3*u*w + 31*_a2*u2*w + 7*_a*u3*w + 119*_a3*v*w - 77*_a2*u*v*w - 43*_a*u2*v*w + u3*v*w - 44*_a2*v2*w + 56*_a*u*v2*w - 12*u2*v2*w - 32*_a*v3*w + 32*u*v3*w + 36*_a3*w2 - 12*_a2*u*w2 - 20*_a*u2*w2 - 4*u3*w2 - 96*_a2*v*w2 + 64*_a*u*v*w2 + 32*u2*v*w2 + 64*_a*v2*w2 - 64*u*v2*w2;
      *(result+6) = 0;
      *(result+7) = 0;
    }
  else if (SAME4(u,w,x,y))
    {
      *(result) = -18*_a5;
      *(result+1) = 90*_a5 - 84*_a4*u - 3*_a4*v - 3*_a4*z;
      *(result+2) = -180*_a5 + 336*_a4*u - 128*_a3*u2 + 12*_a4*v - 40*_a3*u*v + 12*_a3*v2 + 12*_a4*z - 40*_a3*u*z + 4*_a3*v*z + 12*_a3*z2;
      *(result+3) = 180*_a5 - 504*_a4*u + 384*_a3*u2 - 64*_a2*u3 - 18*_a4*v + 120*_a3*u*v - 96*_a2*u2*v - 36*_a3*v2 + 40*_a2*u*v2 - 3*_a2*v3 - 18*_a4*z + 120*_a3*u*z - 96*_a2*u2*z - 12*_a3*v*z - 8*_a2*u*v*z + 5*_a2*v2*z - 36*_a3*z2 + 40*_a2*u*z2 + 5*_a2*v*z2 - 3*_a2*z3;
      *(result+4) = -90*_a5 + 336*_a4*u - 384*_a3*u2 + 128*_a2*u3 + 12*_a4*v - 120*_a3*u*v + 192*_a2*u2*v - 64*_a*u3*v + 36*_a3*v2 - 80*_a2*u*v2 + 32*_a*u2*v2 + 6*_a2*v3 - 4*_a*u*v3 + 12*_a4*z - 120*_a3*u*z + 192*_a2*u2*z - 64*_a*u3*z + 12*_a3*v*z + 16*_a2*u*v*z - 64*_a*u2*v*z - 10*_a2*v2*z + 28*_a*u*v2*z - 2*_a*v3*z + 36*_a3*z2 - 80*_a2*u*z2 + 32*_a*u2*z2 - 10*_a2*v*z2 + 28*_a*u*v*z2 - 6*_a*v2*z2 + 6*_a2*z3 - 4*_a*u*z3 - 2*_a*v*z3;
      *(result+5) = 18*_a5 - 84*_a4*u + 128*_a3*u2 - 64*_a2*u3 - 3*_a4*v + 40*_a3*u*v - 96*_a2*u2*v + 64*_a*u3*v - 12*_a3*v2 + 40*_a2*u*v2 - 32*_a*u2*v2 - 3*_a2*v3 + 4*_a*u*v3 - 3*_a4*z + 40*_a3*u*z - 96*_a2*u2*z + 64*_a*u3*z - 4*_a3*v*z - 8*_a2*u*v*z + 64*_a*u2*v*z - 64*u3*v*z + 5*_a2*v2*z - 28*_a*u*v2*z + 32*u2*v2*z + 2*_a*v3*z - 4*u*v3*z - 12*_a3*z2 + 40*_a2*u*z2 - 32*_a*u2*z2 + 5*_a2*v*z2 - 28*_a*u*v*z2 + 32*u2*v*z2 + 6*_a*v2*z2 - 12*u*v2*z2 + v3*z2 - 3*_a2*z3 + 4*_a*u*z3 + 2*_a*v*z3 - 4*u*v*z3 + v2*z3;
      *(result+6) = 0;
      *(result+7) = 0;
    }
  else if (SAME4(v,w,x,z))
    {
      *(result) = -18*_a5;
      *(result+1) = 90*_a5 - 3*_a4*u - 84*_a4*v - 3*_a4*y;
      *(result+2) = -180*_a5 + 12*_a4*u + 12*_a3*u2 + 336*_a4*v - 40*_a3*u*v - 128*_a3*v2 + 12*_a4*y + 4*_a3*u*y - 40*_a3*v*y + 12*_a3*y2;
      *(result+3) = 180*_a5 - 18*_a4*u - 36*_a3*u2 - 3*_a2*u3 - 504*_a4*v + 120*_a3*u*v + 40*_a2*u2*v + 384*_a3*v2 - 96*_a2*u*v2 - 64*_a2*v3 - 18*_a4*y - 12*_a3*u*y + 5*_a2*u2*y + 120*_a3*v*y - 8*_a2*u*v*y - 96*_a2*v2*y - 36*_a3*y2 + 5*_a2*u*y2 + 40*_a2*v*y2 - 3*_a2*y3;
      *(result+4) = -90*_a5 + 12*_a4*u + 36*_a3*u2 + 6*_a2*u3 + 336*_a4*v - 120*_a3*u*v - 80*_a2*u2*v - 4*_a*u3*v - 384*_a3*v2 + 192*_a2*u*v2 + 32*_a*u2*v2 + 128*_a2*v3 - 64*_a*u*v3 + 12*_a4*y + 12*_a3*u*y - 10*_a2*u2*y - 2*_a*u3*y - 120*_a3*v*y + 16*_a2*u*v*y + 28*_a*u2*v*y + 192*_a2*v2*y - 64*_a*u*v2*y - 64*_a*v3*y + 36*_a3*y2 - 10*_a2*u*y2 - 6*_a*u2*y2 - 80*_a2*v*y2 + 28*_a*u*v*y2 + 32*_a*v2*y2 + 6*_a2*y3 - 2*_a*u*y3 - 4*_a*v*y3;
      *(result+5) = 18*_a5 - 3*_a4*u - 12*_a3*u2 - 3*_a2*u3 - 84*_a4*v + 40*_a3*u*v + 40*_a2*u2*v + 4*_a*u3*v + 128*_a3*v2 - 96*_a2*u*v2 - 32*_a*u2*v2 - 64*_a2*v3 + 64*_a*u*v3 - 3*_a4*y - 4*_a3*u*y + 5*_a2*u2*y + 2*_a*u3*y + 40*_a3*v*y - 8*_a2*u*v*y - 28*_a*u2*v*y - 4*u3*v*y - 96*_a2*v2*y + 64*_a*u*v2*y + 32*u2*v2*y + 64*_a*v3*y - 64*u*v3*y - 12*_a3*y2 + 5*_a2*u*y2 + 6*_a*u2*y2 + u3*y2 + 40*_a2*v*y2 - 28*_a*u*v*y2 - 12*u2*v*y2 - 32*_a*v2*y2 + 32*u*v2*y2 - 3*_a2*y3 + 2*_a*u*y3 + u2*y3 + 4*_a*v*y3 - 4*u*v*y3;
      *(result+6) = 0;
      *(result+7) = 0;
    }
  else if (SAME2(u,y) && SAME2(v,z))
    {
      *(result) = -6*_a5;
      *(result+1) = 30*_a5 - 10*_a4*u - 10*_a4*v - 3*_a4*w - 7*_a4*x;
      *(result+2) = -60*_a5 + 40*_a4*u + 4*_a3*u2 + 40*_a4*v - 24*_a3*u*v + 4*_a3*v2 + 12*_a4*w - 8*_a3*u*w - 8*_a3*v*w + 3*_a3*w2 + 28*_a4*x - 16*_a3*u*x - 16*_a3*v*x - 2*_a3*w*x + 3*_a3*x2;
      *(result+3) = 60*_a5 - 60*_a4*u - 12*_a3*u2 + 12*_a2*u3 - 60*_a4*v + 72*_a3*u*v - 12*_a2*u2*v - 12*_a3*v2 - 12*_a2*u*v2 + 12*_a2*v3 - 18*_a4*w + 24*_a3*u*w - 6*_a2*u2*w + 24*_a3*v*w - 4*_a2*u*v*w - 6*_a2*v2*w - 9*_a3*w2 + 2*_a2*u*w2 + 2*_a2*v*w2 - 42*_a4*x + 48*_a3*u*x - 6*_a2*u2*x + 48*_a3*v*x - 20*_a2*u*v*x - 6*_a2*v2*x + 6*_a3*w*x - 12*_a2*u*w*x - 12*_a2*v*w*x + 5*_a2*w2*x - 9*_a3*x2 - 2*_a2*u*x2 - 2*_a2*v*x2 + 4*_a2*w*x2 + 3*_a2*x3;
      *(result+4) = -30*_a5 + 40*_a4*u + 12*_a3*u2 - 24*_a2*u3 + 2*_a*u4 + 40*_a4*v - 72*_a3*u*v + 24*_a2*u2*v + 8*_a*u3*v + 12*_a3*v2 + 24*_a2*u*v2 - 20*_a*u2*v2 - 24*_a2*v3 + 8*_a*u*v3 + 2*_a*v4 + 12*_a4*w - 24*_a3*u*w + 12*_a2*u2*w - 24*_a3*v*w + 8*_a2*u*v*w + 12*_a2*v2*w + 9*_a3*w2 - 4*_a2*u*w2 - _a*u2*w2 - 4*_a2*v*w2 + 2*_a*u*v*w2 - _a*v2*w2 + 28*_a4*x - 48*_a3*u*x + 12*_a2*u2*x + 8*_a*u3*x - 48*_a3*v*x + 40*_a2*u*v*x - 8*_a*u2*v*x + 12*_a2*v2*x - 8*_a*u*v2*x + 8*_a*v3*x - 6*_a3*w*x + 24*_a2*u*w*x - 10*_a*u2*w*x + 24*_a2*v*w*x - 12*_a*u*v*w*x - 10*_a*v2*w*x - 10*_a2*w2*x + 4*_a*u*w2*x + 4*_a*v*w2*x + 9*_a3*x2 + 4*_a2*u*x2 - 9*_a*u2*x2 + 4*_a2*v*x2 + 2*_a*u*v*x2 - 9*_a*v2*x2 - 8*_a2*w*x2 + _a*w2*x2 - 6*_a2*x3 + 4*_a*u*x3 + 4*_a*v*x3 + 2*_a*w*x3 - _a*x4;
      *(result+5) = 6*_a5 - 10*_a4*u - 4*_a3*u2 + 12*_a2*u3 - 2*_a*u4 - 2*u5 - 10*_a4*v + 24*_a3*u*v - 12*_a2*u2*v - 8*_a*u3*v + 6*u4*v - 4*_a3*v2 - 12*_a2*u*v2 + 20*_a*u2*v2 - 4*u3*v2 + 12*_a2*v3 - 8*_a*u*v3 - 4*u2*v3 - 2*_a*v4 + 6*u*v4 - 2*v5 - 3*_a4*w + 8*_a3*u*w - 6*_a2*u2*w + u4*w + 8*_a3*v*w - 4*_a2*u*v*w - 4*u3*v*w - 6*_a2*v2*w + 6*u2*v2*w - 4*u*v3*w + v4*w - 3*_a3*w2 + 2*_a2*u*w2 + _a*u2*w2 + 2*_a2*v*w2 - 2*_a*u*v*w2 + _a*v2*w2 - 7*_a4*x + 16*_a3*u*x - 6*_a2*u2*x - 8*_a*u3*x + 5*u4*x + 16*_a3*v*x - 20*_a2*u*v*x + 8*_a*u2*v*x - 4*u3*v*x - 6*_a2*v2*x + 8*_a*u*v2*x - 2*u2*v2*x - 8*_a*v3*x - 4*u*v3*x + 5*v4*x + 2*_a3*w*x - 12*_a2*u*w*x + 10*_a*u2*w*x - 12*_a2*v*w*x + 12*_a*u*v*w*x + 10*_a*v2*w*x + 5*_a2*w2*x - 4*_a*u*w2*x - u2*w2*x - 4*_a*v*w2*x + 2*u*v*w2*x - v2*w2*x - 3*_a3*x2 - 2*_a2*u*x2 + 9*_a*u2*x2 - 4*u3*x2 - 2*_a2*v*x2 - 2*_a*u*v*x2 + 4*u2*v*x2 + 9*_a*v2*x2 + 4*u*v2*x2 - 4*v3*x2 + 4*_a2*w*x2 - 4*u2*w*x2 - 8*u*v*w*x2 - 4*v2*w*x2 - _a*w2*x2 + 2*u*w2*x2 + 2*v*w2*x2 + 3*_a2*x3 - 4*_a*u*x3 + u2*x3 - 4*_a*v*x3 - 2*u*v*x3 + v2*x3 - 2*_a*w*x3 + 4*u*w*x3 + 4*v*w*x3 - w2*x3 + _a*x4 - w*x4;
      *(result+6) = 0;
      *(result+7) = 0;
    }
  else if (SAME2(u,z) && SAME2(v,y))
    {
      *(result) = -6*_a5;
      *(result+1) = 30*_a5 - 10*_a4*u - 10*_a4*v - 3*_a4*w - 7*_a4*x;
      *(result+2) = -60*_a5 + 40*_a4*u + _a3*u2 + 40*_a4*v - 18*_a3*u*v + _a3*v2 + 12*_a4*w - 8*_a3*u*w - 8*_a3*v*w + 3*_a3*w2 + 28*_a4*x - 16*_a3*u*x - 16*_a3*v*x - 2*_a3*w*x + 3*_a3*x2;
      *(result+3) = 60*_a5 - 60*_a4*u - 3*_a3*u2 + 4*_a2*u3 - 60*_a4*v + 54*_a3*u*v - 4*_a2*u2*v - 3*_a3*v2 - 4*_a2*u*v2 + 4*_a2*v3 - 18*_a4*w + 24*_a3*u*w + 24*_a3*v*w - 16*_a2*u*v*w - 9*_a3*w2 + 2*_a2*u*w2 + 2*_a2*v*w2 - 42*_a4*x + 48*_a3*u*x - 5*_a2*u2*x + 48*_a3*v*x - 22*_a2*u*v*x - 5*_a2*v2*x + 6*_a3*w*x - 12*_a2*u*w*x - 12*_a2*v*w*x + 5*_a2*w2*x - 9*_a3*x2 - 2*_a2*u*x2 - 2*_a2*v*x2 + 4*_a2*w*x2 + 3*_a2*x3;
      *(result+4) = -30*_a5 + 40*_a4*u + 3*_a3*u2 - 8*_a2*u3 - _a*u4 + 40*_a4*v - 54*_a3*u*v + 8*_a2*u2*v + 4*_a*u3*v + 3*_a3*v2 + 8*_a2*u*v2 - 6*_a*u2*v2 - 8*_a2*v3 + 4*_a*u*v3 - _a*v4 + 12*_a4*w - 24*_a3*u*w + 4*_a*u3*w - 24*_a3*v*w + 32*_a2*u*v*w - 4*_a*u2*v*w - 4*_a*u*v2*w + 4*_a*v3*w + 9*_a3*w2 - 4*_a2*u*w2 - _a*u2*w2 - 4*_a2*v*w2 + 2*_a*u*v*w2 - _a*v2*w2 + 28*_a4*x - 48*_a3*u*x + 10*_a2*u2*x + 4*_a*u3*x - 48*_a3*v*x + 44*_a2*u*v*x - 4*_a*u2*v*x + 10*_a2*v2*x - 4*_a*u*v2*x + 4*_a*v3*x - 6*_a3*w*x + 24*_a2*u*w*x - 6*_a*u2*w*x + 24*_a2*v*w*x - 20*_a*u*v*w*x - 6*_a*v2*w*x - 10*_a2*w2*x + 4*_a*u*w2*x + 4*_a*v*w2*x + 9*_a3*x2 + 4*_a2*u*x2 - 6*_a*u2*x2 + 4*_a2*v*x2 - 4*_a*u*v*x2 - 6*_a*v2*x2 - 8*_a2*w*x2 + _a*w2*x2 - 6*_a2*x3 + 4*_a*u*x3 + 4*_a*v*x3 + 2*_a*w*x3 - _a*x4;
      *(result+5) = 6*_a5 - 10*_a4*u - _a3*u2 + 4*_a2*u3 + _a*u4 - 10*_a4*v + 18*_a3*u*v - 4*_a2*u2*v - 4*_a*u3*v - _a3*v2 - 4*_a2*u*v2 + 6*_a*u2*v2 + 4*_a2*v3 - 4*_a*u*v3 + _a*v4 - 3*_a4*w + 8*_a3*u*w - 4*_a*u3*w - u4*w + 8*_a3*v*w - 16*_a2*u*v*w + 4*_a*u2*v*w + 4*u3*v*w + 4*_a*u*v2*w - 6*u2*v2*w - 4*_a*v3*w + 4*u*v3*w - v4*w - 3*_a3*w2 + 2*_a2*u*w2 + _a*u2*w2 + 2*_a2*v*w2 - 2*_a*u*v*w2 + _a*v2*w2 - 7*_a4*x + 16*_a3*u*x - 5*_a2*u2*x - 4*_a*u3*x + 16*_a3*v*x - 22*_a2*u*v*x + 4*_a*u2*v*x - 5*_a2*v2*x + 4*_a*u*v2*x - 4*_a*v3*x + 2*_a3*w*x - 12*_a2*u*w*x + 6*_a*u2*w*x + 4*u3*w*x - 12*_a2*v*w*x + 20*_a*u*v*w*x - 4*u2*v*w*x + 6*_a*v2*w*x - 4*u*v2*w*x + 4*v3*w*x + 5*_a2*w2*x - 4*_a*u*w2*x - u2*w2*x - 4*_a*v*w2*x + 2*u*v*w2*x - v2*w2*x - 3*_a3*x2 - 2*_a2*u*x2 + 6*_a*u2*x2 - 2*_a2*v*x2 + 4*_a*u*v*x2 + 6*_a*v2*x2 + 4*_a2*w*x2 - 6*u2*w*x2 - 4*u*v*w*x2 - 6*v2*w*x2 - _a*w2*x2 + 2*u*w2*x2 + 2*v*w2*x2 + 3*_a2*x3 - 4*_a*u*x3 - 4*_a*v*x3 - 2*_a*w*x3 + 4*u*w*x3 + 4*v*w*x3 - w2*x3 + _a*x4 - w*x4;
      *(result+6) = 0;
      *(result+7) = 0;
    }
  else if (SAME4(u,w,x,z))
    {
      *(result) = 18*_a6;
      *(result+1) = -108*_a6 + 66*_a5*u + 21*_a5*v + 21*_a5*y;
      *(result+2) = 270*_a6 - 330*_a5*u + 71*_a4*u2 - 105*_a5*v + 94*_a4*u*v - 9*_a4*v2 - 105*_a5*y + 94*_a4*u*y + 29*_a4*v*y - 9*_a4*y2;
      *(result+3) = -360*_a6 + 660*_a5*u - 284*_a4*u2 + 8*_a3*u3 + 210*_a5*v - 376*_a4*u*v + 130*_a3*u2*v + 36*_a4*v2 - 6*_a3*u*v2 - 9*_a3*v3 + 210*_a5*y - 376*_a4*u*y + 130*_a3*u2*y - 116*_a4*v*y + 128*_a3*u*v*y - 3*_a3*v2*y + 36*_a4*y2 - 6*_a3*u*y2 - 3*_a3*v*y2 - 9*_a3*y3;
      *(result+4) = 270*_a6 - 660*_a5*u + 426*_a4*u2 - 24*_a3*u3 - 16*_a2*u4 - 210*_a5*v + 564*_a4*u*v - 390*_a3*u2*v + 44*_a2*u3*v - 54*_a4*v2 + 18*_a3*u*v2 + 35*_a2*u2*v2 + 27*_a3*v3 - 30*_a2*u*v3 + 3*_a2*v4 - 210*_a5*y + 564*_a4*u*y - 390*_a3*u2*y + 44*_a2*u3*y + 174*_a4*v*y - 384*_a3*u*v*y + 188*_a2*u2*v*y + 9*_a3*v2*y + 2*_a2*u*v2*y - 9*_a2*v3*y - 54*_a4*y2 + 18*_a3*u*y2 + 35*_a2*u2*y2 + 9*_a3*v*y2 + 2*_a2*u*v*y2 + 8*_a2*v2*y2 + 27*_a3*y3 - 30*_a2*u*y3 - 9*_a2*v*y3 + 3*_a2*y4;
      *(result+5) = -108*_a6 + 330*_a5*u - 284*_a4*u2 + 24*_a3*u3 + 32*_a2*u4 + 105*_a5*v - 376*_a4*u*v + 390*_a3*u2*v - 88*_a2*u3*v - 16*_a*u4*v + 36*_a4*v2 - 18*_a3*u*v2 - 70*_a2*u2*v2 + 36*_a*u3*v2 - 27*_a3*v3 + 60*_a2*u*v3 - 24*_a*u2*v3 - 6*_a2*v4 + 4*_a*u*v4 + 105*_a5*y - 376*_a4*u*y + 390*_a3*u2*y - 88*_a2*u3*y - 16*_a*u4*y - 116*_a4*v*y + 384*_a3*u*v*y - 376*_a2*u2*v*y + 80*_a*u3*v*y - 9*_a3*v2*y - 4*_a2*u*v2*y + 34*_a*u2*v2*y + 18*_a2*v3*y - 28*_a*u*v3*y + 2*_a*v4*y + 36*_a4*y2 - 18*_a3*u*y2 - 70*_a2*u2*y2 + 36*_a*u3*y2 - 9*_a3*v*y2 - 4*_a2*u*v*y2 + 34*_a*u2*v*y2 - 16*_a2*v2*y2 + 10*_a*u*v2*y2 + _a*v3*y2 - 27*_a3*y3 + 60*_a2*u*y3 - 24*_a*u2*y3 + 18*_a2*v*y3 - 28*_a*u*v*y3 + _a*v2*y3 - 6*_a2*y4 + 4*_a*u*y4 + 2*_a*v*y4;
      *(result+6) = 18*_a6 - 66*_a5*u + 71*_a4*u2 - 8*_a3*u3 - 16*_a2*u4 - 21*_a5*v + 94*_a4*u*v - 130*_a3*u2*v + 44*_a2*u3*v + 16*_a*u4*v - 9*_a4*v2 + 6*_a3*u*v2 + 35*_a2*u2*v2 - 36*_a*u3*v2 + 9*_a3*v3 - 30*_a2*u*v3 + 24*_a*u2*v3 + 3*_a2*v4 - 4*_a*u*v4 - 21*_a5*y + 94*_a4*u*y - 130*_a3*u2*y + 44*_a2*u3*y + 16*_a*u4*y + 29*_a4*v*y - 128*_a3*u*v*y + 188*_a2*u2*v*y - 80*_a*u3*v*y - 16*u4*v*y + 3*_a3*v2*y + 2*_a2*u*v2*y - 34*_a*u2*v2*y + 36*u3*v2*y - 9*_a2*v3*y + 28*_a*u*v3*y - 24*u2*v3*y - 2*_a*v4*y + 4*u*v4*y - 9*_a4*y2 + 6*_a3*u*y2 + 35*_a2*u2*y2 - 36*_a*u3*y2 + 3*_a3*v*y2 + 2*_a2*u*v*y2 - 34*_a*u2*v*y2 + 36*u3*v*y2 + 8*_a2*v2*y2 - 10*_a*u*v2*y2 - u2*v2*y2 - _a*v3*y2 + 2*u*v3*y2 - v4*y2 + 9*_a3*y3 - 30*_a2*u*y3 + 24*_a*u2*y3 - 9*_a2*v*y3 + 28*_a*u*v*y3 - 24*u2*v*y3 - _a*v2*y3 + 2*u*v2*y3 + v3*y3 + 3*_a2*y4 - 4*_a*u*y4 - 2*_a*v*y4 + 4*u*v*y4 - v2*y4;
      *(result+7) = 0;
    }
  else if (SAME4(v,w,x,y))
    {
      *(result) = 18*_a6;
      *(result+1) = -108*_a6 + 21*_a5*u + 66*_a5*v + 21*_a5*z;
      *(result+2) = 270*_a6 - 105*_a5*u - 9*_a4*u2 - 330*_a5*v + 94*_a4*u*v + 71*_a4*v2 - 105*_a5*z + 29*_a4*u*z + 94*_a4*v*z - 9*_a4*z2;
      *(result+3) = -360*_a6 + 210*_a5*u + 36*_a4*u2 - 9*_a3*u3 + 660*_a5*v - 376*_a4*u*v - 6*_a3*u2*v - 284*_a4*v2 + 130*_a3*u*v2 + 8*_a3*v3 + 210*_a5*z - 116*_a4*u*z - 3*_a3*u2*z - 376*_a4*v*z + 128*_a3*u*v*z + 130*_a3*v2*z + 36*_a4*z2 - 3*_a3*u*z2 - 6*_a3*v*z2 - 9*_a3*z3;
      *(result+4) = 270*_a6 - 210*_a5*u - 54*_a4*u2 + 27*_a3*u3 + 3*_a2*u4 - 660*_a5*v + 564*_a4*u*v + 18*_a3*u2*v - 30*_a2*u3*v + 426*_a4*v2 - 390*_a3*u*v2 + 35*_a2*u2*v2 - 24*_a3*v3 + 44*_a2*u*v3 - 16*_a2*v4 - 210*_a5*z + 174*_a4*u*z + 9*_a3*u2*z - 9*_a2*u3*z + 564*_a4*v*z - 384*_a3*u*v*z + 2*_a2*u2*v*z - 390*_a3*v2*z + 188*_a2*u*v2*z + 44*_a2*v3*z - 54*_a4*z2 + 9*_a3*u*z2 + 8*_a2*u2*z2 + 18*_a3*v*z2 + 2*_a2*u*v*z2 + 35*_a2*v2*z2 + 27*_a3*z3 - 9*_a2*u*z3 - 30*_a2*v*z3 + 3*_a2*z4;
      *(result+5) = -108*_a6 + 105*_a5*u + 36*_a4*u2 - 27*_a3*u3 - 6*_a2*u4 + 330*_a5*v - 376*_a4*u*v - 18*_a3*u2*v + 60*_a2*u3*v + 4*_a*u4*v - 284*_a4*v2 + 390*_a3*u*v2 - 70*_a2*u2*v2 - 24*_a*u3*v2 + 24*_a3*v3 - 88*_a2*u*v3 + 36*_a*u2*v3 + 32*_a2*v4 - 16*_a*u*v4 + 105*_a5*z - 116*_a4*u*z - 9*_a3*u2*z + 18*_a2*u3*z + 2*_a*u4*z - 376*_a4*v*z + 384*_a3*u*v*z - 4*_a2*u2*v*z - 28*_a*u3*v*z + 390*_a3*v2*z - 376*_a2*u*v2*z + 34*_a*u2*v2*z - 88*_a2*v3*z + 80*_a*u*v3*z - 16*_a*v4*z + 36*_a4*z2 - 9*_a3*u*z2 - 16*_a2*u2*z2 + _a*u3*z2 - 18*_a3*v*z2 - 4*_a2*u*v*z2 + 10*_a*u2*v*z2 - 70*_a2*v2*z2 + 34*_a*u*v2*z2 + 36*_a*v3*z2 - 27*_a3*z3 + 18*_a2*u*z3 + _a*u2*z3 + 60*_a2*v*z3 - 28*_a*u*v*z3 - 24*_a*v2*z3 - 6*_a2*z4 + 2*_a*u*z4 + 4*_a*v*z4;
      *(result+6) = 18*_a6 - 21*_a5*u - 9*_a4*u2 + 9*_a3*u3 + 3*_a2*u4 - 66*_a5*v + 94*_a4*u*v + 6*_a3*u2*v - 30*_a2*u3*v - 4*_a*u4*v + 71*_a4*v2 - 130*_a3*u*v2 + 35*_a2*u2*v2 + 24*_a*u3*v2 - 8*_a3*v3 + 44*_a2*u*v3 - 36*_a*u2*v3 - 16*_a2*v4 + 16*_a*u*v4 - 21*_a5*z + 29*_a4*u*z + 3*_a3*u2*z - 9*_a2*u3*z - 2*_a*u4*z + 94*_a4*v*z - 128*_a3*u*v*z + 2*_a2*u2*v*z + 28*_a*u3*v*z + 4*u4*v*z - 130*_a3*v2*z + 188*_a2*u*v2*z - 34*_a*u2*v2*z - 24*u3*v2*z + 44*_a2*v3*z - 80*_a*u*v3*z + 36*u2*v3*z + 16*_a*v4*z - 16*u*v4*z - 9*_a4*z2 + 3*_a3*u*z2 + 8*_a2*u2*z2 - _a*u3*z2 - u4*z2 + 6*_a3*v*z2 + 2*_a2*u*v*z2 - 10*_a*u2*v*z2 + 2*u3*v*z2 + 35*_a2*v2*z2 - 34*_a*u*v2*z2 - u2*v2*z2 - 36*_a*v3*z2 + 36*u*v3*z2 + 9*_a3*z3 - 9*_a2*u*z3 - _a*u2*z3 + u3*z3 - 30*_a2*v*z3 + 28*_a*u*v*z3 + 2*u2*v*z3 + 24*_a*v2*z3 - 24*u*v2*z3 + 3*_a2*z4 - 2*_a*u*z4 - u2*z4 - 4*_a*v*z4 + 4*u*v*z4;
      *(result+7) = 0;
    }
  else if (SAME2(u,w) && SAME2(x,y))
    {
      *(result) = 18*_a6;
      *(result+1) = -108*_a6 + 30*_a5*u + 21*_a5*v + 54*_a5*x + 3*_a5*z;
      *(result+2) = 270*_a6 - 150*_a5*u - 3*_a4*u2 - 105*_a5*v + 48*_a4*u*v - 9*_a4*v2 - 270*_a5*x + 94*_a4*u*x + 76*_a4*v*x + 37*_a4*x2 - 15*_a5*z + 14*_a4*u*z - _a4*v*z + 26*_a4*x*z - 12*_a4*z2;
      *(result+3) = -360*_a6 + 300*_a5*u + 12*_a4*u2 - 12*_a3*u3 + 210*_a5*v - 192*_a4*u*v + 15*_a3*u2*v + 36*_a4*v2 + 6*_a3*u*v2 - 9*_a3*v3 + 540*_a5*x - 376*_a4*u*x + 8*_a3*u2*x - 304*_a4*v*x + 130*_a3*u*v*x - 6*_a3*v2*x - 148*_a4*x2 + 84*_a3*u*x2 + 79*_a3*v*x2 - 16*_a3*x3 + 30*_a5*z - 56*_a4*u*z + _a3*u2*z + 4*_a4*v*z + 20*_a3*u*v*z - 9*_a3*v2*z - 104*_a4*x*z + 62*_a3*u*x*z + 28*_a3*v*x*z + 33*_a3*x2*z + 48*_a4*z2 - 14*_a3*u*z2 - 17*_a3*v*z2 - 26*_a3*x*z2 + 3*_a3*z3;
      *(result+4) = 270*_a6 - 300*_a5*u - 18*_a4*u2 + 36*_a3*u3 + 3*_a2*u4 - 210*_a5*v + 288*_a4*u*v - 45*_a3*u2*v - 12*_a2*u3*v - 54*_a4*v2 - 18*_a3*u*v2 + 18*_a2*u2*v2 + 27*_a3*v3 - 12*_a2*u*v3 + 3*_a2*v4 - 540*_a5*x + 564*_a4*u*x - 24*_a3*u2*x - 28*_a2*u3*x + 456*_a4*v*x - 390*_a3*u*v*x + 32*_a2*u2*v*x + 18*_a3*v2*x + 20*_a2*u*v2*x - 24*_a2*v3*x + 222*_a4*x2 - 252*_a3*u*x2 + 34*_a2*u2*x2 - 237*_a3*v*x2 + 100*_a2*u*v*x2 + 26*_a2*v2*x2 + 48*_a3*x3 + 4*_a2*u*x3 + 8*_a2*v*x3 - 13*_a2*x4 - 30*_a5*z + 84*_a4*u*z - 3*_a3*u2*z - 8*_a2*u3*z - 6*_a4*v*z - 60*_a3*u*v*z + 13*_a2*u2*v*z + 27*_a3*v2*z - 2*_a2*u*v2*z - 3*_a2*v3*z + 156*_a4*x*z - 186*_a3*u*x*z + 8*_a2*u2*x*z - 84*_a3*v*x*z + 86*_a2*u*v*x*z - 18*_a2*v2*x*z - 99*_a3*x2*z + 72*_a2*u*x2*z + 61*_a2*v*x2*z - 8*_a2*x3*z - 72*_a4*z2 + 42*_a3*u*z2 + 3*_a2*u2*z2 + 51*_a3*v*z2 - 24*_a2*u*v*z2 + _a2*v2*z2 + 78*_a3*x*z2 - 30*_a2*u*x*z2 - 44*_a2*v*x*z2 - 5*_a2*x2*z2 - 9*_a3*z3 + 2*_a2*u*z3 + 5*_a2*v*z3 + 2*_a2*x*z3;
      *(result+5) = -108*_a6 + 150*_a5*u + 12*_a4*u2 - 36*_a3*u3 - 6*_a2*u4 + 105*_a5*v - 192*_a4*u*v + 45*_a3*u2*v + 24*_a2*u3*v + 36*_a4*v2 + 18*_a3*u*v2 - 36*_a2*u2*v2 - 27*_a3*v3 + 24*_a2*u*v3 - 6*_a2*v4 + 270*_a5*x - 376*_a4*u*x + 24*_a3*u2*x + 56*_a2*u3*x + 4*_a*u4*x - 304*_a4*v*x + 390*_a3*u*v*x - 64*_a2*u2*v*x - 16*_a*u3*v*x - 18*_a3*v2*x - 40*_a2*u*v2*x + 24*_a*u2*v2*x + 48*_a2*v3*x - 16*_a*u*v3*x + 4*_a*v4*x - 148*_a4*x2 + 252*_a3*u*x2 - 68*_a2*u2*x2 - 16*_a*u3*x2 + 237*_a3*v*x2 - 200*_a2*u*v*x2 + 16*_a*u2*v*x2 - 52*_a2*v2*x2 + 16*_a*u*v2*x2 - 16*_a*v3*x2 - 48*_a3*x3 - 8*_a2*u*x3 + 24*_a*u2*x3 - 16*_a2*v*x3 + 16*_a*u*v*x3 + 24*_a*v2*x3 + 26*_a2*x4 - 16*_a*u*x4 - 16*_a*v*x4 + 4*_a*x5 + 15*_a5*z - 56*_a4*u*z + 3*_a3*u2*z + 16*_a2*u3*z + 2*_a*u4*z + 4*_a4*v*z + 60*_a3*u*v*z - 26*_a2*u2*v*z - 8*_a*u3*v*z - 27*_a3*v2*z + 4*_a2*u*v2*z + 12*_a*u2*v2*z + 6*_a2*v3*z - 8*_a*u*v3*z + 2*_a*v4*z - 104*_a4*x*z + 186*_a3*u*x*z - 16*_a2*u2*x*z - 24*_a*u3*x*z + 84*_a3*v*x*z - 172*_a2*u*v*x*z + 32*_a*u2*v*x*z + 36*_a2*v2*x*z + 8*_a*u*v2*x*z - 16*_a*v3*x*z + 99*_a3*x2*z - 144*_a2*u*x2*z + 28*_a*u2*x2*z - 122*_a2*v*x2*z + 88*_a*u*v*x2*z + 12*_a*v2*x2*z + 16*_a2*x3*z + 8*_a*u*x3*z + 16*_a*v*x3*z - 14*_a*x4*z + 48*_a4*z2 - 42*_a3*u*z2 - 6*_a2*u2*z2 + 4*_a*u3*z2 - 51*_a3*v*z2 + 48*_a2*u*v*z2 - 3*_a*u2*v*z2 - 2*_a2*v2*z2 - 6*_a*u*v2*z2 + 5*_a*v3*z2 - 78*_a3*x*z2 + 60*_a2*u*x*z2 + 88*_a2*v*x*z2 - 42*_a*u*v*x*z2 - 10*_a*v2*x*z2 + 10*_a2*x2*z2 - 12*_a*u*x2*z2 - 19*_a*v*x2*z2 + 8*_a*x3*z2 + 9*_a3*z3 - 4*_a2*u*z3 - _a*u2*z3 - 10*_a2*v*z3 + 4*_a*u*v*z3 + _a*v2*z3 - 4*_a2*x*z3 + 2*_a*u*x*z3 + 4*_a*v*x*z3 - _a*x2*z3;
      *(result+6) = 18*_a6 - 30*_a5*u - 3*_a4*u2 + 12*_a3*u3 + 3*_a2*u4 - 21*_a5*v + 48*_a4*u*v - 15*_a3*u2*v - 12*_a2*u3*v - 9*_a4*v2 - 6*_a3*u*v2 + 18*_a2*u2*v2 + 9*_a3*v3 - 12*_a2*u*v3 + 3*_a2*v4 - 54*_a5*x + 94*_a4*u*x - 8*_a3*u2*x - 28*_a2*u3*x - 4*_a*u4*x + 76*_a4*v*x - 130*_a3*u*v*x + 32*_a2*u2*v*x + 16*_a*u3*v*x + 6*_a3*v2*x + 20*_a2*u*v2*x - 24*_a*u2*v2*x - 24*_a2*v3*x + 16*_a*u*v3*x - 4*_a*v4*x + 37*_a4*x2 - 84*_a3*u*x2 + 34*_a2*u2*x2 + 16*_a*u3*x2 - 79*_a3*v*x2 + 100*_a2*u*v*x2 - 16*_a*u2*v*x2 + 26*_a2*v2*x2 - 16*_a*u*v2*x2 + 16*_a*v3*x2 + 16*_a3*x3 + 4*_a2*u*x3 - 24*_a*u2*x3 + 8*_a2*v*x3 - 16*_a*u*v*x3 - 24*_a*v2*x3 - 13*_a2*x4 + 16*_a*u*x4 + 16*_a*v*x4 - 4*_a*x5 - 3*_a5*z + 14*_a4*u*z - _a3*u2*z - 8*_a2*u3*z - 2*_a*u4*z - _a4*v*z - 20*_a3*u*v*z + 13*_a2*u2*v*z + 8*_a*u3*v*z + 9*_a3*v2*z - 2*_a2*u*v2*z - 12*_a*u2*v2*z - 3*_a2*v3*z + 8*_a*u*v3*z - 2*_a*v4*z + 26*_a4*x*z - 62*_a3*u*x*z + 8*_a2*u2*x*z + 24*_a*u3*x*z + 4*u4*x*z - 28*_a3*v*x*z + 86*_a2*u*v*x*z - 32*_a*u2*v*x*z - 16*u3*v*x*z - 18*_a2*v2*x*z - 8*_a*u*v2*x*z + 24*u2*v2*x*z + 16*_a*v3*x*z - 16*u*v3*x*z + 4*v4*x*z - 33*_a3*x2*z + 72*_a2*u*x2*z - 28*_a*u2*x2*z - 16*u3*x2*z + 61*_a2*v*x2*z - 88*_a*u*v*x2*z + 16*u2*v*x2*z - 12*_a*v2*x2*z + 16*u*v2*x2*z - 16*v3*x2*z - 8*_a2*x3*z - 8*_a*u*x3*z + 24*u2*x3*z - 16*_a*v*x3*z + 16*u*v*x3*z + 24*v2*x3*z + 14*_a*x4*z - 16*u*x4*z - 16*v*x4*z + 4*x5*z - 12*_a4*z2 + 14*_a3*u*z2 + 3*_a2*u2*z2 - 4*_a*u3*z2 - u4*z2 + 17*_a3*v*z2 - 24*_a2*u*v*z2 + 3*_a*u2*v*z2 + 4*u3*v*z2 + _a2*v2*z2 + 6*_a*u*v2*z2 - 6*u2*v2*z2 - 5*_a*v3*z2 + 4*u*v3*z2 - v4*z2 + 26*_a3*x*z2 - 30*_a2*u*x*z2 + 4*u3*x*z2 - 44*_a2*v*x*z2 + 42*_a*u*v*x*z2 + 10*_a*v2*x*z2 - 12*u*v2*x*z2 + 8*v3*x*z2 - 5*_a2*x2*z2 + 12*_a*u*x2*z2 - 6*u2*x2*z2 + 19*_a*v*x2*z2 - 12*u*v*x2*z2 - 14*v2*x2*z2 - 8*_a*x3*z2 + 4*u*x3*z2 + 8*v*x3*z2 - x4*z2 - 3*_a3*z3 + 2*_a2*u*z3 + _a*u2*z3 + 5*_a2*v*z3 - 4*_a*u*v*z3 - u2*v*z3 - _a*v2*z3 + 2*u*v2*z3 - v3*z3 + 2*_a2*x*z3 - 2*_a*u*x*z3 - 4*_a*v*x*z3 + 2*u*v*x*z3 + 2*v2*x*z3 + _a*x2*z3 - v*x2*z3;
      *(result+7) = 0;
    }
  else if (SAME2(u,x) && SAME2(w,y))
    {
      *(result) = 18*_a6;
      *(result+1) = -108*_a6 + 54*_a5*u + 3*_a5*v + 30*_a5*w + 21*_a5*z;
      *(result+2) = 270*_a6 - 270*_a5*u + 37*_a4*u2 - 15*_a5*v + 26*_a4*u*v - 12*_a4*v2 - 150*_a5*w + 94*_a4*u*w + 14*_a4*v*w - 3*_a4*w2 - 105*_a5*z + 76*_a4*u*z - _a4*v*z + 48*_a4*w*z - 9*_a4*z2;
      *(result+3) = -360*_a6 + 540*_a5*u - 148*_a4*u2 - 16*_a3*u3 + 30*_a5*v - 104*_a4*u*v + 33*_a3*u2*v + 48*_a4*v2 - 26*_a3*u*v2 + 3*_a3*v3 + 300*_a5*w - 376*_a4*u*w + 84*_a3*u2*w - 56*_a4*v*w + 62*_a3*u*v*w - 14*_a3*v2*w + 12*_a4*w2 + 8*_a3*u*w2 + _a3*v*w2 - 12*_a3*w3 + 210*_a5*z - 304*_a4*u*z + 79*_a3*u2*z + 4*_a4*v*z + 28*_a3*u*v*z - 17*_a3*v2*z - 192*_a4*w*z + 130*_a3*u*w*z + 20*_a3*v*w*z + 15*_a3*w2*z + 36*_a4*z2 - 6*_a3*u*z2 - 9*_a3*v*z2 + 6*_a3*w*z2 - 9*_a3*z3;
      *(result+4) = 270*_a6 - 540*_a5*u + 222*_a4*u2 + 48*_a3*u3 - 13*_a2*u4 - 30*_a5*v + 156*_a4*u*v - 99*_a3*u2*v - 8*_a2*u3*v - 72*_a4*v2 + 78*_a3*u*v2 - 5*_a2*u2*v2 - 9*_a3*v3 + 2*_a2*u*v3 - 300*_a5*w + 564*_a4*u*w - 252*_a3*u2*w + 4*_a2*u3*w + 84*_a4*v*w - 186*_a3*u*v*w + 72*_a2*u2*v*w + 42*_a3*v2*w - 30*_a2*u*v2*w + 2*_a2*v3*w - 18*_a4*w2 - 24*_a3*u*w2 + 34*_a2*u2*w2 - 3*_a3*v*w2 + 8*_a2*u*v*w2 + 3*_a2*v2*w2 + 36*_a3*w3 - 28*_a2*u*w3 - 8*_a2*v*w3 + 3*_a2*w4 - 210*_a5*z + 456*_a4*u*z - 237*_a3*u2*z + 8*_a2*u3*z - 6*_a4*v*z - 84*_a3*u*v*z + 61*_a2*u2*v*z + 51*_a3*v2*z - 44*_a2*u*v2*z + 5*_a2*v3*z + 288*_a4*w*z - 390*_a3*u*w*z + 100*_a2*u2*w*z - 60*_a3*v*w*z + 86*_a2*u*v*w*z - 24*_a2*v2*w*z - 45*_a3*w2*z + 32*_a2*u*w2*z + 13*_a2*v*w2*z - 12*_a2*w3*z - 54*_a4*z2 + 18*_a3*u*z2 + 26*_a2*u2*z2 + 27*_a3*v*z2 - 18*_a2*u*v*z2 + _a2*v2*z2 - 18*_a3*w*z2 + 20*_a2*u*w*z2 - 2*_a2*v*w*z2 + 18*_a2*w2*z2 + 27*_a3*z3 - 24*_a2*u*z3 - 3*_a2*v*z3 - 12*_a2*w*z3 + 3*_a2*z4;
      *(result+5) = -108*_a6 + 270*_a5*u - 148*_a4*u2 - 48*_a3*u3 + 26*_a2*u4 + 4*_a*u5 + 15*_a5*v - 104*_a4*u*v + 99*_a3*u2*v + 16*_a2*u3*v - 14*_a*u4*v + 48*_a4*v2 - 78*_a3*u*v2 + 10*_a2*u2*v2 + 8*_a*u3*v2 + 9*_a3*v3 - 4*_a2*u*v3 - _a*u2*v3 + 150*_a5*w - 376*_a4*u*w + 252*_a3*u2*w - 8*_a2*u3*w - 16*_a*u4*w - 56*_a4*v*w + 186*_a3*u*v*w - 144*_a2*u2*v*w + 8*_a*u3*v*w - 42*_a3*v2*w + 60*_a2*u*v2*w - 12*_a*u2*v2*w - 4*_a2*v3*w + 2*_a*u*v3*w + 12*_a4*w2 + 24*_a3*u*w2 - 68*_a2*u2*w2 + 24*_a*u3*w2 + 3*_a3*v*w2 - 16*_a2*u*v*w2 + 28*_a*u2*v*w2 - 6*_a2*v2*w2 - _a*v3*w2 - 36*_a3*w3 + 56*_a2*u*w3 - 16*_a*u2*w3 + 16*_a2*v*w3 - 24*_a*u*v*w3 + 4*_a*v2*w3 - 6*_a2*w4 + 4*_a*u*w4 + 2*_a*v*w4 + 105*_a5*z - 304*_a4*u*z + 237*_a3*u2*z - 16*_a2*u3*z - 16*_a*u4*z + 4*_a4*v*z + 84*_a3*u*v*z - 122*_a2*u2*v*z + 16*_a*u3*v*z - 51*_a3*v2*z + 88*_a2*u*v2*z - 19*_a*u2*v2*z - 10*_a2*v3*z + 4*_a*u*v3*z - 192*_a4*w*z + 390*_a3*u*w*z - 200*_a2*u2*w*z + 16*_a*u3*w*z + 60*_a3*v*w*z - 172*_a2*u*v*w*z + 88*_a*u2*v*w*z + 48*_a2*v2*w*z - 42*_a*u*v2*w*z + 4*_a*v3*w*z + 45*_a3*w2*z - 64*_a2*u*w2*z + 16*_a*u2*w2*z - 26*_a2*v*w2*z + 32*_a*u*v*w2*z - 3*_a*v2*w2*z + 24*_a2*w3*z - 16*_a*u*w3*z - 8*_a*v*w3*z + 36*_a4*z2 - 18*_a3*u*z2 - 52*_a2*u2*z2 + 24*_a*u3*z2 - 27*_a3*v*z2 + 36*_a2*u*v*z2 + 12*_a*u2*v*z2 - 2*_a2*v2*z2 - 10*_a*u*v2*z2 + _a*v3*z2 + 18*_a3*w*z2 - 40*_a2*u*w*z2 + 16*_a*u2*w*z2 + 4*_a2*v*w*z2 + 8*_a*u*v*w*z2 - 6*_a*v2*w*z2 - 36*_a2*w2*z2 + 24*_a*u*w2*z2 + 12*_a*v*w2*z2 - 27*_a3*z3 + 48*_a2*u*z3 - 16*_a*u2*z3 + 6*_a2*v*z3 - 16*_a*u*v*z3 + 5*_a*v2*z3 + 24*_a2*w*z3 - 16*_a*u*w*z3 - 8*_a*v*w*z3 - 6*_a2*z4 + 4*_a*u*z4 + 2*_a*v*z4;
      *(result+6) = 18*_a6 - 54*_a5*u + 37*_a4*u2 + 16*_a3*u3 - 13*_a2*u4 - 4*_a*u5 - 3*_a5*v + 26*_a4*u*v - 33*_a3*u2*v - 8*_a2*u3*v + 14*_a*u4*v + 4*u5*v - 12*_a4*v2 + 26*_a3*u*v2 - 5*_a2*u2*v2 - 8*_a*u3*v2 - u4*v2 - 3*_a3*v3 + 2*_a2*u*v3 + _a*u2*v3 - 30*_a5*w + 94*_a4*u*w - 84*_a3*u2*w + 4*_a2*u3*w + 16*_a*u4*w + 14*_a4*v*w - 62*_a3*u*v*w + 72*_a2*u2*v*w - 8*_a*u3*v*w - 16*u4*v*w + 14*_a3*v2*w - 30*_a2*u*v2*w + 12*_a*u2*v2*w + 4*u3*v2*w + 2*_a2*v3*w - 2*_a*u*v3*w - 3*_a4*w2 - 8*_a3*u*w2 + 34*_a2*u2*w2 - 24*_a*u3*w2 - _a3*v*w2 + 8*_a2*u*v*w2 - 28*_a*u2*v*w2 + 24*u3*v*w2 + 3*_a2*v2*w2 - 6*u2*v2*w2 + _a*v3*w2 + 12*_a3*w3 - 28*_a2*u*w3 + 16*_a*u2*w3 - 8*_a2*v*w3 + 24*_a*u*v*w3 - 16*u2*v*w3 - 4*_a*v2*w3 + 4*u*v2*w3 + 3*_a2*w4 - 4*_a*u*w4 - 2*_a*v*w4 + 4*u*v*w4 - v2*w4 - 21*_a5*z + 76*_a4*u*z - 79*_a3*u2*z + 8*_a2*u3*z + 16*_a*u4*z - _a4*v*z - 28*_a3*u*v*z + 61*_a2*u2*v*z - 16*_a*u3*v*z - 16*u4*v*z + 17*_a3*v2*z - 44*_a2*u*v2*z + 19*_a*u2*v2*z + 8*u3*v2*z + 5*_a2*v3*z - 4*_a*u*v3*z - u2*v3*z + 48*_a4*w*z - 130*_a3*u*w*z + 100*_a2*u2*w*z - 16*_a*u3*w*z - 20*_a3*v*w*z + 86*_a2*u*v*w*z - 88*_a*u2*v*w*z + 16*u3*v*w*z - 24*_a2*v2*w*z + 42*_a*u*v2*w*z - 12*u2*v2*w*z - 4*_a*v3*w*z + 2*u*v3*w*z - 15*_a3*w2*z + 32*_a2*u*w2*z - 16*_a*u2*w2*z + 13*_a2*v*w2*z - 32*_a*u*v*w2*z + 16*u2*v*w2*z + 3*_a*v2*w2*z - v3*w2*z - 12*_a2*w3*z + 16*_a*u*w3*z + 8*_a*v*w3*z - 16*u*v*w3*z + 4*v2*w3*z - 9*_a4*z2 + 6*_a3*u*z2 + 26*_a2*u2*z2 - 24*_a*u3*z2 + 9*_a3*v*z2 - 18*_a2*u*v*z2 - 12*_a*u2*v*z2 + 24*u3*v*z2 + _a2*v2*z2 + 10*_a*u*v2*z2 - 14*u2*v2*z2 - _a*v3*z2 + 2*u*v3*z2 - 6*_a3*w*z2 + 20*_a2*u*w*z2 - 16*_a*u2*w*z2 - 2*_a2*v*w*z2 - 8*_a*u*v*w*z2 + 16*u2*v*w*z2 + 6*_a*v2*w*z2 - 12*u*v2*w*z2 + 2*v3*w*z2 + 18*_a2*w2*z2 - 24*_a*u*w2*z2 - 12*_a*v*w2*z2 + 24*u*v*w2*z2 - 6*v2*w2*z2 + 9*_a3*z3 - 24*_a2*u*z3 + 16*_a*u2*z3 - 3*_a2*v*z3 + 16*_a*u*v*z3 - 16*u2*v*z3 - 5*_a*v2*z3 + 8*u*v2*z3 - v3*z3 - 12*_a2*w*z3 + 16*_a*u*w*z3 + 8*_a*v*w*z3 - 16*u*v*w*z3 + 4*v2*w*z3 + 3*_a2*z4 - 4*_a*u*z4 - 2*_a*v*z4 + 4*u*v*z4 - v2*z4;
      *(result+7) = 0;
    }
  else if (SAME2(v,w) && SAME2(x,z))
    {
      *(result) = 18*_a6;
      *(result+1) = -108*_a6 + 21*_a5*u + 30*_a5*v + 54*_a5*x + 3*_a5*y;
      *(result+2) = 270*_a6 - 105*_a5*u - 9*_a4*u2 - 150*_a5*v + 48*_a4*u*v - 3*_a4*v2 - 270*_a5*x + 76*_a4*u*x + 94*_a4*v*x + 37*_a4*x2 - 15*_a5*y - _a4*u*y + 14*_a4*v*y + 26*_a4*x*y - 12*_a4*y2;
      *(result+3) = -360*_a6 + 210*_a5*u + 36*_a4*u2 - 9*_a3*u3 + 300*_a5*v - 192*_a4*u*v + 6*_a3*u2*v + 12*_a4*v2 + 15*_a3*u*v2 - 12*_a3*v3 + 540*_a5*x - 304*_a4*u*x - 6*_a3*u2*x - 376*_a4*v*x + 130*_a3*u*v*x + 8*_a3*v2*x - 148*_a4*x2 + 79*_a3*u*x2 + 84*_a3*v*x2 - 16*_a3*x3 + 30*_a5*y + 4*_a4*u*y - 9*_a3*u2*y - 56*_a4*v*y + 20*_a3*u*v*y + _a3*v2*y - 104*_a4*x*y + 28*_a3*u*x*y + 62*_a3*v*x*y + 33*_a3*x2*y + 48*_a4*y2 - 17*_a3*u*y2 - 14*_a3*v*y2 - 26*_a3*x*y2 + 3*_a3*y3;
      *(result+4) = 270*_a6 - 210*_a5*u - 54*_a4*u2 + 27*_a3*u3 + 3*_a2*u4 - 300*_a5*v + 288*_a4*u*v - 18*_a3*u2*v - 12*_a2*u3*v - 18*_a4*v2 - 45*_a3*u*v2 + 18*_a2*u2*v2 + 36*_a3*v3 - 12*_a2*u*v3 + 3*_a2*v4 - 540*_a5*x + 456*_a4*u*x + 18*_a3*u2*x - 24*_a2*u3*x + 564*_a4*v*x - 390*_a3*u*v*x + 20*_a2*u2*v*x - 24*_a3*v2*x + 32*_a2*u*v2*x - 28*_a2*v3*x + 222*_a4*x2 - 237*_a3*u*x2 + 26*_a2*u2*x2 - 252*_a3*v*x2 + 100*_a2*u*v*x2 + 34*_a2*v2*x2 + 48*_a3*x3 + 8*_a2*u*x3 + 4*_a2*v*x3 - 13*_a2*x4 - 30*_a5*y - 6*_a4*u*y + 27*_a3*u2*y - 3*_a2*u3*y + 84*_a4*v*y - 60*_a3*u*v*y - 2*_a2*u2*v*y - 3*_a3*v2*y + 13*_a2*u*v2*y - 8*_a2*v3*y + 156*_a4*x*y - 84*_a3*u*x*y - 18*_a2*u2*x*y - 186*_a3*v*x*y + 86*_a2*u*v*x*y + 8*_a2*v2*x*y - 99*_a3*x2*y + 61*_a2*u*x2*y + 72*_a2*v*x2*y - 8*_a2*x3*y - 72*_a4*y2 + 51*_a3*u*y2 + _a2*u2*y2 + 42*_a3*v*y2 - 24*_a2*u*v*y2 + 3*_a2*v2*y2 + 78*_a3*x*y2 - 44*_a2*u*x*y2 - 30*_a2*v*x*y2 - 5*_a2*x2*y2 - 9*_a3*y3 + 5*_a2*u*y3 + 2*_a2*v*y3 + 2*_a2*x*y3;
      *(result+5) = -108*_a6 + 105*_a5*u + 36*_a4*u2 - 27*_a3*u3 - 6*_a2*u4 + 150*_a5*v - 192*_a4*u*v + 18*_a3*u2*v + 24*_a2*u3*v + 12*_a4*v2 + 45*_a3*u*v2 - 36*_a2*u2*v2 - 36*_a3*v3 + 24*_a2*u*v3 - 6*_a2*v4 + 270*_a5*x - 304*_a4*u*x - 18*_a3*u2*x + 48*_a2*u3*x + 4*_a*u4*x - 376*_a4*v*x + 390*_a3*u*v*x - 40*_a2*u2*v*x - 16*_a*u3*v*x + 24*_a3*v2*x - 64*_a2*u*v2*x + 24*_a*u2*v2*x + 56*_a2*v3*x - 16*_a*u*v3*x + 4*_a*v4*x - 148*_a4*x2 + 237*_a3*u*x2 - 52*_a2*u2*x2 - 16*_a*u3*x2 + 252*_a3*v*x2 - 200*_a2*u*v*x2 + 16*_a*u2*v*x2 - 68*_a2*v2*x2 + 16*_a*u*v2*x2 - 16*_a*v3*x2 - 48*_a3*x3 - 16*_a2*u*x3 + 24*_a*u2*x3 - 8*_a2*v*x3 + 16*_a*u*v*x3 + 24*_a*v2*x3 + 26*_a2*x4 - 16*_a*u*x4 - 16*_a*v*x4 + 4*_a*x5 + 15*_a5*y + 4*_a4*u*y - 27*_a3*u2*y + 6*_a2*u3*y + 2*_a*u4*y - 56*_a4*v*y + 60*_a3*u*v*y + 4*_a2*u2*v*y - 8*_a*u3*v*y + 3*_a3*v2*y - 26*_a2*u*v2*y + 12*_a*u2*v2*y + 16*_a2*v3*y - 8*_a*u*v3*y + 2*_a*v4*y - 104*_a4*x*y + 84*_a3*u*x*y + 36*_a2*u2*x*y - 16*_a*u3*x*y + 186*_a3*v*x*y - 172*_a2*u*v*x*y + 8*_a*u2*v*x*y - 16*_a2*v2*x*y + 32*_a*u*v2*x*y - 24*_a*v3*x*y + 99*_a3*x2*y - 122*_a2*u*x2*y + 12*_a*u2*x2*y - 144*_a2*v*x2*y + 88*_a*u*v*x2*y + 28*_a*v2*x2*y + 16*_a2*x3*y + 16*_a*u*x3*y + 8*_a*v*x3*y - 14*_a*x4*y + 48*_a4*y2 - 51*_a3*u*y2 - 2*_a2*u2*y2 + 5*_a*u3*y2 - 42*_a3*v*y2 + 48*_a2*u*v*y2 - 6*_a*u2*v*y2 - 6*_a2*v2*y2 - 3*_a*u*v2*y2 + 4*_a*v3*y2 - 78*_a3*x*y2 + 88*_a2*u*x*y2 - 10*_a*u2*x*y2 + 60*_a2*v*x*y2 - 42*_a*u*v*x*y2 + 10*_a2*x2*y2 - 19*_a*u*x2*y2 - 12*_a*v*x2*y2 + 8*_a*x3*y2 + 9*_a3*y3 - 10*_a2*u*y3 + _a*u2*y3 - 4*_a2*v*y3 + 4*_a*u*v*y3 - _a*v2*y3 - 4*_a2*x*y3 + 4*_a*u*x*y3 + 2*_a*v*x*y3 - _a*x2*y3;
      *(result+6) = 18*_a6 - 21*_a5*u - 9*_a4*u2 + 9*_a3*u3 + 3*_a2*u4 - 30*_a5*v + 48*_a4*u*v - 6*_a3*u2*v - 12*_a2*u3*v - 3*_a4*v2 - 15*_a3*u*v2 + 18*_a2*u2*v2 + 12*_a3*v3 - 12*_a2*u*v3 + 3*_a2*v4 - 54*_a5*x + 76*_a4*u*x + 6*_a3*u2*x - 24*_a2*u3*x - 4*_a*u4*x + 94*_a4*v*x - 130*_a3*u*v*x + 20*_a2*u2*v*x + 16*_a*u3*v*x - 8*_a3*v2*x + 32*_a2*u*v2*x - 24*_a*u2*v2*x - 28*_a2*v3*x + 16*_a*u*v3*x - 4*_a*v4*x + 37*_a4*x2 - 79*_a3*u*x2 + 26*_a2*u2*x2 + 16*_a*u3*x2 - 84*_a3*v*x2 + 100*_a2*u*v*x2 - 16*_a*u2*v*x2 + 34*_a2*v2*x2 - 16*_a*u*v2*x2 + 16*_a*v3*x2 + 16*_a3*x3 + 8*_a2*u*x3 - 24*_a*u2*x3 + 4*_a2*v*x3 - 16*_a*u*v*x3 - 24*_a*v2*x3 - 13*_a2*x4 + 16*_a*u*x4 + 16*_a*v*x4 - 4*_a*x5 - 3*_a5*y - _a4*u*y + 9*_a3*u2*y - 3*_a2*u3*y - 2*_a*u4*y + 14*_a4*v*y - 20*_a3*u*v*y - 2*_a2*u2*v*y + 8*_a*u3*v*y - _a3*v2*y + 13*_a2*u*v2*y - 12*_a*u2*v2*y - 8*_a2*v3*y + 8*_a*u*v3*y - 2*_a*v4*y + 26*_a4*x*y - 28*_a3*u*x*y - 18*_a2*u2*x*y + 16*_a*u3*x*y + 4*u4*x*y - 62*_a3*v*x*y + 86*_a2*u*v*x*y - 8*_a*u2*v*x*y - 16*u3*v*x*y + 8*_a2*v2*x*y - 32*_a*u*v2*x*y + 24*u2*v2*x*y + 24*_a*v3*x*y - 16*u*v3*x*y + 4*v4*x*y - 33*_a3*x2*y + 61*_a2*u*x2*y - 12*_a*u2*x2*y - 16*u3*x2*y + 72*_a2*v*x2*y - 88*_a*u*v*x2*y + 16*u2*v*x2*y - 28*_a*v2*x2*y + 16*u*v2*x2*y - 16*v3*x2*y - 8*_a2*x3*y - 16*_a*u*x3*y + 24*u2*x3*y - 8*_a*v*x3*y + 16*u*v*x3*y + 24*v2*x3*y + 14*_a*x4*y - 16*u*x4*y - 16*v*x4*y + 4*x5*y - 12*_a4*y2 + 17*_a3*u*y2 + _a2*u2*y2 - 5*_a*u3*y2 - u4*y2 + 14*_a3*v*y2 - 24*_a2*u*v*y2 + 6*_a*u2*v*y2 + 4*u3*v*y2 + 3*_a2*v2*y2 + 3*_a*u*v2*y2 - 6*u2*v2*y2 - 4*_a*v3*y2 + 4*u*v3*y2 - v4*y2 + 26*_a3*x*y2 - 44*_a2*u*x*y2 + 10*_a*u2*x*y2 + 8*u3*x*y2 - 30*_a2*v*x*y2 + 42*_a*u*v*x*y2 - 12*u2*v*x*y2 + 4*v3*x*y2 - 5*_a2*x2*y2 + 19*_a*u*x2*y2 - 14*u2*x2*y2 + 12*_a*v*x2*y2 - 12*u*v*x2*y2 - 6*v2*x2*y2 - 8*_a*x3*y2 + 8*u*x3*y2 + 4*v*x3*y2 - x4*y2 - 3*_a3*y3 + 5*_a2*u*y3 - _a*u2*y3 - u3*y3 + 2*_a2*v*y3 - 4*_a*u*v*y3 + 2*u2*v*y3 + _a*v2*y3 - u*v2*y3 + 2*_a2*x*y3 - 4*_a*u*x*y3 + 2*u2*x*y3 - 2*_a*v*x*y3 + 2*u*v*x*y3 + _a*x2*y3 - u*x2*y3;
      *(result+7) = 0;
    }
  else if (SAME2(v,x) && SAME2(w,z))
    {
      *(result) = 18*_a6;
      *(result+1) = -108*_a6 + 3*_a5*u + 54*_a5*v + 30*_a5*w + 21*_a5*y;
      *(result+2) = 270*_a6 - 15*_a5*u - 12*_a4*u2 - 270*_a5*v + 26*_a4*u*v + 37*_a4*v2 - 150*_a5*w + 14*_a4*u*w + 94*_a4*v*w - 3*_a4*w2 - 105*_a5*y - _a4*u*y + 76*_a4*v*y + 48*_a4*w*y - 9*_a4*y2;
      *(result+3) = -360*_a6 + 30*_a5*u + 48*_a4*u2 + 3*_a3*u3 + 540*_a5*v - 104*_a4*u*v - 26*_a3*u2*v - 148*_a4*v2 + 33*_a3*u*v2 - 16*_a3*v3 + 300*_a5*w - 56*_a4*u*w - 14*_a3*u2*w - 376*_a4*v*w + 62*_a3*u*v*w + 84*_a3*v2*w + 12*_a4*w2 + _a3*u*w2 + 8*_a3*v*w2 - 12*_a3*w3 + 210*_a5*y + 4*_a4*u*y - 17*_a3*u2*y - 304*_a4*v*y + 28*_a3*u*v*y + 79*_a3*v2*y - 192*_a4*w*y + 20*_a3*u*w*y + 130*_a3*v*w*y + 15*_a3*w2*y + 36*_a4*y2 - 9*_a3*u*y2 - 6*_a3*v*y2 + 6*_a3*w*y2 - 9*_a3*y3;
      *(result+4) = 270*_a6 - 30*_a5*u - 72*_a4*u2 - 9*_a3*u3 - 540*_a5*v + 156*_a4*u*v + 78*_a3*u2*v + 2*_a2*u3*v + 222*_a4*v2 - 99*_a3*u*v2 - 5*_a2*u2*v2 + 48*_a3*v3 - 8*_a2*u*v3 - 13*_a2*v4 - 300*_a5*w + 84*_a4*u*w + 42*_a3*u2*w + 2*_a2*u3*w + 564*_a4*v*w - 186*_a3*u*v*w - 30*_a2*u2*v*w - 252*_a3*v2*w + 72*_a2*u*v2*w + 4*_a2*v3*w - 18*_a4*w2 - 3*_a3*u*w2 + 3*_a2*u2*w2 - 24*_a3*v*w2 + 8*_a2*u*v*w2 + 34*_a2*v2*w2 + 36*_a3*w3 - 8*_a2*u*w3 - 28*_a2*v*w3 + 3*_a2*w4 - 210*_a5*y - 6*_a4*u*y + 51*_a3*u2*y + 5*_a2*u3*y + 456*_a4*v*y - 84*_a3*u*v*y - 44*_a2*u2*v*y - 237*_a3*v2*y + 61*_a2*u*v2*y + 8*_a2*v3*y + 288*_a4*w*y - 60*_a3*u*w*y - 24*_a2*u2*w*y - 390*_a3*v*w*y + 86*_a2*u*v*w*y + 100*_a2*v2*w*y - 45*_a3*w2*y + 13*_a2*u*w2*y + 32*_a2*v*w2*y - 12*_a2*w3*y - 54*_a4*y2 + 27*_a3*u*y2 + _a2*u2*y2 + 18*_a3*v*y2 - 18*_a2*u*v*y2 + 26*_a2*v2*y2 - 18*_a3*w*y2 - 2*_a2*u*w*y2 + 20*_a2*v*w*y2 + 18*_a2*w2*y2 + 27*_a3*y3 - 3*_a2*u*y3 - 24*_a2*v*y3 - 12*_a2*w*y3 + 3*_a2*y4;
      *(result+5) = -108*_a6 + 15*_a5*u + 48*_a4*u2 + 9*_a3*u3 + 270*_a5*v - 104*_a4*u*v - 78*_a3*u2*v - 4*_a2*u3*v - 148*_a4*v2 + 99*_a3*u*v2 + 10*_a2*u2*v2 - _a*u3*v2 - 48*_a3*v3 + 16*_a2*u*v3 + 8*_a*u2*v3 + 26*_a2*v4 - 14*_a*u*v4 + 4*_a*v5 + 150*_a5*w - 56*_a4*u*w - 42*_a3*u2*w - 4*_a2*u3*w - 376*_a4*v*w + 186*_a3*u*v*w + 60*_a2*u2*v*w + 2*_a*u3*v*w + 252*_a3*v2*w - 144*_a2*u*v2*w - 12*_a*u2*v2*w - 8*_a2*v3*w + 8*_a*u*v3*w - 16*_a*v4*w + 12*_a4*w2 + 3*_a3*u*w2 - 6*_a2*u2*w2 - _a*u3*w2 + 24*_a3*v*w2 - 16*_a2*u*v*w2 - 68*_a2*v2*w2 + 28*_a*u*v2*w2 + 24*_a*v3*w2 - 36*_a3*w3 + 16*_a2*u*w3 + 4*_a*u2*w3 + 56*_a2*v*w3 - 24*_a*u*v*w3 - 16*_a*v2*w3 - 6*_a2*w4 + 2*_a*u*w4 + 4*_a*v*w4 + 105*_a5*y + 4*_a4*u*y - 51*_a3*u2*y - 10*_a2*u3*y - 304*_a4*v*y + 84*_a3*u*v*y + 88*_a2*u2*v*y + 4*_a*u3*v*y + 237*_a3*v2*y - 122*_a2*u*v2*y - 19*_a*u2*v2*y - 16*_a2*v3*y + 16*_a*u*v3*y - 16*_a*v4*y - 192*_a4*w*y + 60*_a3*u*w*y + 48*_a2*u2*w*y + 4*_a*u3*w*y + 390*_a3*v*w*y - 172*_a2*u*v*w*y - 42*_a*u2*v*w*y - 200*_a2*v2*w*y + 88*_a*u*v2*w*y + 16*_a*v3*w*y + 45*_a3*w2*y - 26*_a2*u*w2*y - 3*_a*u2*w2*y - 64*_a2*v*w2*y + 32*_a*u*v*w2*y + 16*_a*v2*w2*y + 24*_a2*w3*y - 8*_a*u*w3*y - 16*_a*v*w3*y + 36*_a4*y2 - 27*_a3*u*y2 - 2*_a2*u2*y2 + _a*u3*y2 - 18*_a3*v*y2 + 36*_a2*u*v*y2 - 10*_a*u2*v*y2 - 52*_a2*v2*y2 + 12*_a*u*v2*y2 + 24*_a*v3*y2 + 18*_a3*w*y2 + 4*_a2*u*w*y2 - 6*_a*u2*w*y2 - 40*_a2*v*w*y2 + 8*_a*u*v*w*y2 + 16*_a*v2*w*y2 - 36*_a2*w2*y2 + 12*_a*u*w2*y2 + 24*_a*v*w2*y2 - 27*_a3*y3 + 6*_a2*u*y3 + 5*_a*u2*y3 + 48*_a2*v*y3 - 16*_a*u*v*y3 - 16*_a*v2*y3 + 24*_a2*w*y3 - 8*_a*u*w*y3 - 16*_a*v*w*y3 - 6*_a2*y4 + 2*_a*u*y4 + 4*_a*v*y4;
      *(result+6) = 18*_a6 - 3*_a5*u - 12*_a4*u2 - 3*_a3*u3 - 54*_a5*v + 26*_a4*u*v + 26*_a3*u2*v + 2*_a2*u3*v + 37*_a4*v2 - 33*_a3*u*v2 - 5*_a2*u2*v2 + _a*u3*v2 + 16*_a3*v3 - 8*_a2*u*v3 - 8*_a*u2*v3 - 13*_a2*v4 + 14*_a*u*v4 - u2*v4 - 4*_a*v5 + 4*u*v5 - 30*_a5*w + 14*_a4*u*w + 14*_a3*u2*w + 2*_a2*u3*w + 94*_a4*v*w - 62*_a3*u*v*w - 30*_a2*u2*v*w - 2*_a*u3*v*w - 84*_a3*v2*w + 72*_a2*u*v2*w + 12*_a*u2*v2*w + 4*_a2*v3*w - 8*_a*u*v3*w + 4*u2*v3*w + 16*_a*v4*w - 16*u*v4*w - 3*_a4*w2 - _a3*u*w2 + 3*_a2*u2*w2 + _a*u3*w2 - 8*_a3*v*w2 + 8*_a2*u*v*w2 + 34*_a2*v2*w2 - 28*_a*u*v2*w2 - 6*u2*v2*w2 - 24*_a*v3*w2 + 24*u*v3*w2 + 12*_a3*w3 - 8*_a2*u*w3 - 4*_a*u2*w3 - 28*_a2*v*w3 + 24*_a*u*v*w3 + 4*u2*v*w3 + 16*_a*v2*w3 - 16*u*v2*w3 + 3*_a2*w4 - 2*_a*u*w4 - u2*w4 - 4*_a*v*w4 + 4*u*v*w4 - 21*_a5*y - _a4*u*y + 17*_a3*u2*y + 5*_a2*u3*y + 76*_a4*v*y - 28*_a3*u*v*y - 44*_a2*u2*v*y - 4*_a*u3*v*y - 79*_a3*v2*y + 61*_a2*u*v2*y + 19*_a*u2*v2*y - u3*v2*y + 8*_a2*v3*y - 16*_a*u*v3*y + 8*u2*v3*y + 16*_a*v4*y - 16*u*v4*y + 48*_a4*w*y - 20*_a3*u*w*y - 24*_a2*u2*w*y - 4*_a*u3*w*y - 130*_a3*v*w*y + 86*_a2*u*v*w*y + 42*_a*u2*v*w*y + 2*u3*v*w*y + 100*_a2*v2*w*y - 88*_a*u*v2*w*y - 12*u2*v2*w*y - 16*_a*v3*w*y + 16*u*v3*w*y - 15*_a3*w2*y + 13*_a2*u*w2*y + 3*_a*u2*w2*y - u3*w2*y + 32*_a2*v*w2*y - 32*_a*u*v*w2*y - 16*_a*v2*w2*y + 16*u*v2*w2*y - 12*_a2*w3*y + 8*_a*u*w3*y + 4*u2*w3*y + 16*_a*v*w3*y - 16*u*v*w3*y - 9*_a4*y2 + 9*_a3*u*y2 + _a2*u2*y2 - _a*u3*y2 + 6*_a3*v*y2 - 18*_a2*u*v*y2 + 10*_a*u2*v*y2 + 2*u3*v*y2 + 26*_a2*v2*y2 - 12*_a*u*v2*y2 - 14*u2*v2*y2 - 24*_a*v3*y2 + 24*u*v3*y2 - 6*_a3*w*y2 - 2*_a2*u*w*y2 + 6*_a*u2*w*y2 + 2*u3*w*y2 + 20*_a2*v*w*y2 - 8*_a*u*v*w*y2 - 12*u2*v*w*y2 - 16*_a*v2*w*y2 + 16*u*v2*w*y2 + 18*_a2*w2*y2 - 12*_a*u*w2*y2 - 6*u2*w2*y2 - 24*_a*v*w2*y2 + 24*u*v*w2*y2 + 9*_a3*y3 - 3*_a2*u*y3 - 5*_a*u2*y3 - u3*y3 - 24*_a2*v*y3 + 16*_a*u*v*y3 + 8*u2*v*y3 + 16*_a*v2*y3 - 16*u*v2*y3 - 12*_a2*w*y3 + 8*_a*u*w*y3 + 4*u2*w*y3 + 16*_a*v*w*y3 - 16*u*v*w*y3 + 3*_a2*y4 - 2*_a*u*y4 - u2*y4 - 4*_a*v*y4 + 4*u*v*y4;
      *(result+7) = 0;
    }
  else if (SAME2(u,v))
    {
      *(result) = 18*_a6;
      *(result+1) = -108*_a6 + 42*_a5*u + 9*_a5*w + 15*_a5*x + 21*_a5*y + 21*_a5*z;
      *(result+2) = 270*_a6 - 210*_a5*u + 15*_a4*u2 - 45*_a5*w + 30*_a4*u*w - 9*_a4*w2 - 75*_a5*x + 52*_a4*u*x + 3*_a4*w*x - 16*_a4*x2 - 105*_a5*y + 49*_a4*u*y + 15*_a4*w*y + 26*_a4*x*y - 9*_a4*y2 - 105*_a5*z + 49*_a4*u*z + 15*_a4*w*z + 26*_a4*x*z + 33*_a4*y*z - 9*_a4*z2;
      *(result+3) = -360*_a6 + 420*_a5*u - 60*_a4*u2 - 12*_a3*u3 + 90*_a5*w - 120*_a4*u*w + 24*_a3*u2*w + 36*_a4*w2 - 12*_a3*u*w2 + 150*_a5*x - 208*_a4*u*x + 28*_a3*u2*x - 12*_a4*w*x + 32*_a3*u*w*x - 12*_a3*w2*x + 64*_a4*x2 - 16*_a3*u*x2 - 14*_a3*w*x2 - 6*_a3*x3 + 210*_a5*y - 196*_a4*u*y + 22*_a3*u2*y - 60*_a4*w*y + 32*_a3*u*w*y - 6*_a3*w2*y - 104*_a4*x*y + 76*_a3*u*x*y + 16*_a3*w*x*y - 8*_a3*x2*y + 36*_a4*y2 - 21*_a3*u*y2 + 3*_a3*w*y2 + 6*_a3*x*y2 - 9*_a3*y3 + 210*_a5*z - 196*_a4*u*z + 22*_a3*u2*z - 60*_a4*w*z + 32*_a3*u*w*z - 6*_a3*w2*z - 104*_a4*x*z + 76*_a3*u*x*z + 16*_a3*w*x*z - 8*_a3*x2*z - 132*_a4*y*z + 86*_a3*u*y*z + 18*_a3*w*y*z + 16*_a3*x*y*z + 3*_a3*y2*z + 36*_a4*z2 - 21*_a3*u*z2 + 3*_a3*w*z2 + 6*_a3*x*z2 + 3*_a3*y*z2 - 9*_a3*z3;
      *(result+4) = 270*_a6 - 420*_a5*u + 90*_a4*u2 + 36*_a3*u3 - 90*_a5*w + 180*_a4*u*w - 72*_a3*u2*w - 54*_a4*w2 + 36*_a3*u*w2 - 150*_a5*x + 312*_a4*u*x - 84*_a3*u2*x - 20*_a2*u3*x + 18*_a4*w*x - 96*_a3*u*w*x + 40*_a2*u2*w*x + 36*_a3*w2*x - 20*_a2*u*w2*x - 96*_a4*x2 + 48*_a3*u*x2 + 10*_a2*u2*x2 + 42*_a3*w*x2 - 20*_a2*u*w*x2 + 2*_a2*w2*x2 + 18*_a3*x3 - 20*_a2*u*x3 - 2*_a2*w*x3 + 6*_a2*x4 - 210*_a5*y + 294*_a4*u*y - 66*_a3*u2*y - 8*_a2*u3*y + 90*_a4*w*y - 96*_a3*u*w*y + 16*_a2*u2*w*y + 18*_a3*w2*y - 8*_a2*u*w2*y + 156*_a4*x*y - 228*_a3*u*x*y + 42*_a2*u2*x*y - 48*_a3*w*x*y + 48*_a2*u*w*x*y - 10*_a2*w2*x*y + 24*_a3*x2*y + 6*_a2*u*x2*y - 10*_a2*w*x2*y - 10*_a2*x3*y - 54*_a4*y2 + 63*_a3*u*y2 - 9*_a2*u2*y2 - 9*_a3*w*y2 - 2*_a2*u*w*y2 + 3*_a2*w2*y2 - 18*_a3*x*y2 + 7*_a2*u*x*y2 + 11*_a2*w*x*y2 + 11*_a2*x2*y2 + 27*_a3*y3 - 21*_a2*u*y3 - 3*_a2*w*y3 - 6*_a2*x*y3 + 3*_a2*y4 - 210*_a5*z + 294*_a4*u*z - 66*_a3*u2*z - 8*_a2*u3*z + 90*_a4*w*z - 96*_a3*u*w*z + 16*_a2*u2*w*z + 18*_a3*w2*z - 8*_a2*u*w2*z + 156*_a4*x*z - 228*_a3*u*x*z + 42*_a2*u2*x*z - 48*_a3*w*x*z + 48*_a2*u*w*x*z - 10*_a2*w2*x*z + 24*_a3*x2*z + 6*_a2*u*x2*z - 10*_a2*w*x2*z - 10*_a2*x3*z + 198*_a4*y*z - 258*_a3*u*y*z + 50*_a2*u2*y*z - 54*_a3*w*y*z + 36*_a2*u*w*y*z - 6*_a2*w2*y*z - 48*_a3*x*y*z + 70*_a2*u*x*y*z + 18*_a2*w*x*y*z - 12*_a2*x2*y*z - 9*_a3*y2*z + 13*_a2*u*y2*z + 3*_a2*w*y2*z - 4*_a2*x*y2*z - 9*_a2*y3*z - 54*_a4*z2 + 63*_a3*u*z2 - 9*_a2*u2*z2 - 9*_a3*w*z2 - 2*_a2*u*w*z2 + 3*_a2*w2*z2 - 18*_a3*x*z2 + 7*_a2*u*x*z2 + 11*_a2*w*x*z2 + 11*_a2*x2*z2 - 9*_a3*y*z2 + 13*_a2*u*y*z2 + 3*_a2*w*y*z2 - 4*_a2*x*y*z2 + 12*_a2*y2*z2 + 27*_a3*z3 - 21*_a2*u*z3 - 3*_a2*w*z3 - 6*_a2*x*z3 - 9*_a2*y*z3 + 3*_a2*z4;
      *(result+5) = -108*_a6 + 210*_a5*u - 60*_a4*u2 - 36*_a3*u3 + 45*_a5*w - 120*_a4*u*w + 72*_a3*u2*w + 36*_a4*w2 - 36*_a3*u*w2 + 75*_a5*x - 208*_a4*u*x + 84*_a3*u2*x + 40*_a2*u3*x - 12*_a4*w*x + 96*_a3*u*w*x - 80*_a2*u2*w*x - 36*_a3*w2*x + 40*_a2*u*w2*x + 64*_a4*x2 - 48*_a3*u*x2 - 20*_a2*u2*x2 - 4*_a*u3*x2 - 42*_a3*w*x2 + 40*_a2*u*w*x2 + 8*_a*u2*w*x2 - 4*_a2*w2*x2 - 4*_a*u*w2*x2 - 18*_a3*x3 + 40*_a2*u*x3 - 4*_a*u2*x3 + 4*_a2*w*x3 - 16*_a*u*w*x3 + 4*_a*w2*x3 - 12*_a2*x4 + 6*_a*u*x4 + 5*_a*w*x4 - _a*x5 + 105*_a5*y - 196*_a4*u*y + 66*_a3*u2*y + 16*_a2*u3*y - 60*_a4*w*y + 96*_a3*u*w*y - 32*_a2*u2*w*y - 18*_a3*w2*y + 16*_a2*u*w2*y - 104*_a4*x*y + 228*_a3*u*x*y - 84*_a2*u2*x*y - 16*_a*u3*x*y + 48*_a3*w*x*y - 96*_a2*u*w*x*y + 32*_a*u2*w*x*y + 20*_a2*w2*x*y - 16*_a*u*w2*x*y - 24*_a3*x2*y - 12*_a2*u*x2*y + 18*_a*u2*x2*y + 20*_a2*w*x2*y - 2*_a*w2*x2*y + 20*_a2*x3*y - 20*_a*u*x3*y - 8*_a*w*x3*y + 3*_a*x4*y + 36*_a4*y2 - 63*_a3*u*y2 + 18*_a2*u2*y2 + 4*_a*u3*y2 + 9*_a3*w*y2 + 4*_a2*u*w*y2 - 8*_a*u2*w*y2 - 6*_a2*w2*y2 + 4*_a*u*w2*y2 + 18*_a3*x*y2 - 14*_a2*u*x*y2 + 2*_a*u2*x*y2 - 22*_a2*w*x*y2 + 12*_a*u*w*x*y2 + 2*_a*w2*x*y2 - 22*_a2*x2*y2 + 25*_a*u*x2*y2 + 5*_a*w*x2*y2 - 4*_a*x3*y2 - 27*_a3*y3 + 42*_a2*u*y3 - 12*_a*u2*y3 + 6*_a2*w*y3 - 4*_a*u*w*y3 + 12*_a2*x*y3 - 18*_a*u*x*y3 - 2*_a*w*x*y3 + 3*_a*x2*y3 - 6*_a2*y4 + 7*_a*u*y4 - _a*x*y4 + 105*_a5*z - 196*_a4*u*z + 66*_a3*u2*z + 16*_a2*u3*z - 60*_a4*w*z + 96*_a3*u*w*z - 32*_a2*u2*w*z - 18*_a3*w2*z + 16*_a2*u*w2*z - 104*_a4*x*z + 228*_a3*u*x*z - 84*_a2*u2*x*z - 16*_a*u3*x*z + 48*_a3*w*x*z - 96*_a2*u*w*x*z + 32*_a*u2*w*x*z + 20*_a2*w2*x*z - 16*_a*u*w2*x*z - 24*_a3*x2*z - 12*_a2*u*x2*z + 18*_a*u2*x2*z + 20*_a2*w*x2*z - 2*_a*w2*x2*z + 20*_a2*x3*z - 20*_a*u*x3*z - 8*_a*w*x3*z + 3*_a*x4*z - 132*_a4*y*z + 258*_a3*u*y*z - 100*_a2*u2*y*z - 8*_a*u3*y*z + 54*_a3*w*y*z - 72*_a2*u*w*y*z + 16*_a*u2*w*y*z + 12*_a2*w2*y*z - 8*_a*u*w2*y*z + 48*_a3*x*y*z - 140*_a2*u*x*y*z + 60*_a*u2*x*y*z - 36*_a2*w*x*y*z + 40*_a*u*w*x*y*z - 4*_a*w2*x*y*z + 24*_a2*x2*y*z - 14*_a*u*x2*y*z - 2*_a*w*x2*y*z + 4*_a*x3*y*z + 9*_a3*y2*z - 26*_a2*u*y2*z + 12*_a*u2*y2*z - 6*_a2*w*y2*z + 4*_a*u*w*y2*z + 8*_a2*x*y2*z + 2*_a*u*x*y2*z + 2*_a*w*x*y2*z - 5*_a*x2*y2*z + 18*_a2*y3*z - 24*_a*u*y3*z + 6*_a*x*y3*z + 36*_a4*z2 - 63*_a3*u*z2 + 18*_a2*u2*z2 + 4*_a*u3*z2 + 9*_a3*w*z2 + 4*_a2*u*w*z2 - 8*_a*u2*w*z2 - 6*_a2*w2*z2 + 4*_a*u*w2*z2 + 18*_a3*x*z2 - 14*_a2*u*x*z2 + 2*_a*u2*x*z2 - 22*_a2*w*x*z2 + 12*_a*u*w*x*z2 + 2*_a*w2*x*z2 - 22*_a2*x2*z2 + 25*_a*u*x2*z2 + 5*_a*w*x2*z2 - 4*_a*x3*z2 + 9*_a3*y*z2 - 26*_a2*u*y*z2 + 12*_a*u2*y*z2 - 6*_a2*w*y*z2 + 4*_a*u*w*y*z2 + 8*_a2*x*y*z2 + 2*_a*u*x*y*z2 + 2*_a*w*x*y*z2 - 5*_a*x2*y*z2 - 24*_a2*y2*z2 + 34*_a*u*y2*z2 - 10*_a*x*y2*z2 - 27*_a3*z3 + 42*_a2*u*z3 - 12*_a*u2*z3 + 6*_a2*w*z3 - 4*_a*u*w*z3 + 12*_a2*x*z3 - 18*_a*u*x*z3 - 2*_a*w*x*z3 + 3*_a*x2*z3 + 18*_a2*y*z3 - 24*_a*u*y*z3 + 6*_a*x*y*z3 - 6*_a2*z4 + 7*_a*u*z4 - _a*x*z4;
      *(result+6) = 18*_a6 - 42*_a5*u + 15*_a4*u2 + 12*_a3*u3 - 9*_a5*w + 30*_a4*u*w - 24*_a3*u2*w - 9*_a4*w2 + 12*_a3*u*w2 - 15*_a5*x + 52*_a4*u*x - 28*_a3*u2*x - 20*_a2*u3*x + 3*_a4*w*x - 32*_a3*u*w*x + 40*_a2*u2*w*x + 12*_a3*w2*x - 20*_a2*u*w2*x - 16*_a4*x2 + 16*_a3*u*x2 + 10*_a2*u2*x2 + 4*_a*u3*x2 + 14*_a3*w*x2 - 20*_a2*u*w*x2 - 8*_a*u2*w*x2 + 2*_a2*w2*x2 + 4*_a*u*w2*x2 + 6*_a3*x3 - 20*_a2*u*x3 + 4*_a*u2*x3 + 4*u3*x3 - 2*_a2*w*x3 + 16*_a*u*w*x3 - 8*u2*w*x3 - 4*_a*w2*x3 + 4*u*w2*x3 + 6*_a2*x4 - 6*_a*u*x4 - u2*x4 - 5*_a*w*x4 + 6*u*w*x4 - w2*x4 + _a*x5 - w*x5 - 21*_a5*y + 49*_a4*u*y - 22*_a3*u2*y - 8*_a2*u3*y + 15*_a4*w*y - 32*_a3*u*w*y + 16*_a2*u2*w*y + 6*_a3*w2*y - 8*_a2*u*w2*y + 26*_a4*x*y - 76*_a3*u*x*y + 42*_a2*u2*x*y + 16*_a*u3*x*y - 16*_a3*w*x*y + 48*_a2*u*w*x*y - 32*_a*u2*w*x*y - 10*_a2*w2*x*y + 16*_a*u*w2*x*y + 8*_a3*x2*y + 6*_a2*u*x2*y - 18*_a*u2*x2*y - 8*u3*x2*y - 10*_a2*w*x2*y + 16*u2*w*x2*y + 2*_a*w2*x2*y - 8*u*w2*x2*y - 10*_a2*x3*y + 20*_a*u*x3*y - 2*u2*x3*y + 8*_a*w*x3*y - 16*u*w*x3*y + 2*w2*x3*y - 3*_a*x4*y + u*x4*y + 3*w*x4*y - 9*_a4*y2 + 21*_a3*u*y2 - 9*_a2*u2*y2 - 4*_a*u3*y2 - 3*_a3*w*y2 - 2*_a2*u*w*y2 + 8*_a*u2*w*y2 + 3*_a2*w2*y2 - 4*_a*u*w2*y2 - 6*_a3*x*y2 + 7*_a2*u*x*y2 - 2*_a*u2*x*y2 + 4*u3*x*y2 + 11*_a2*w*x*y2 - 12*_a*u*w*x*y2 - 8*u2*w*x*y2 - 2*_a*w2*x*y2 + 4*u*w2*x*y2 + 11*_a2*x2*y2 - 25*_a*u*x2*y2 + 11*u2*x2*y2 - 5*_a*w*x2*y2 + 14*u*w*x2*y2 - w2*x2*y2 + 4*_a*x3*y2 - 3*u*x3*y2 - 3*w*x3*y2 + 9*_a3*y3 - 21*_a2*u*y3 + 12*_a*u2*y3 - 3*_a2*w*y3 + 4*_a*u*w*y3 - 6*_a2*x*y3 + 18*_a*u*x*y3 - 12*u2*x*y3 + 2*_a*w*x*y3 - 4*u*w*x*y3 - 3*_a*x2*y3 + 3*u*x2*y3 + w*x2*y3 + 3*_a2*y4 - 7*_a*u*y4 + 4*u2*y4 + _a*x*y4 - u*x*y4 - 21*_a5*z + 49*_a4*u*z - 22*_a3*u2*z - 8*_a2*u3*z + 15*_a4*w*z - 32*_a3*u*w*z + 16*_a2*u2*w*z + 6*_a3*w2*z - 8*_a2*u*w2*z + 26*_a4*x*z - 76*_a3*u*x*z + 42*_a2*u2*x*z + 16*_a*u3*x*z - 16*_a3*w*x*z + 48*_a2*u*w*x*z - 32*_a*u2*w*x*z - 10*_a2*w2*x*z + 16*_a*u*w2*x*z + 8*_a3*x2*z + 6*_a2*u*x2*z - 18*_a*u2*x2*z - 8*u3*x2*z - 10*_a2*w*x2*z + 16*u2*w*x2*z + 2*_a*w2*x2*z - 8*u*w2*x2*z - 10*_a2*x3*z + 20*_a*u*x3*z - 2*u2*x3*z + 8*_a*w*x3*z - 16*u*w*x3*z + 2*w2*x3*z - 3*_a*x4*z + u*x4*z + 3*w*x4*z + 33*_a4*y*z - 86*_a3*u*y*z + 50*_a2*u2*y*z + 8*_a*u3*y*z - 18*_a3*w*y*z + 36*_a2*u*w*y*z - 16*_a*u2*w*y*z - 6*_a2*w2*y*z + 8*_a*u*w2*y*z - 16*_a3*x*y*z + 70*_a2*u*x*y*z - 60*_a*u2*x*y*z - 8*u3*x*y*z + 18*_a2*w*x*y*z - 40*_a*u*w*x*y*z + 16*u2*w*x*y*z + 4*_a*w2*x*y*z - 8*u*w2*x*y*z - 12*_a2*x2*y*z + 14*_a*u*x2*y*z + 10*u2*x2*y*z + 2*_a*w*x2*y*z + 4*u*w*x2*y*z + 2*w2*x2*y*z - 4*_a*x3*y*z + 2*u*x3*y*z - 2*w*x3*y*z - x4*y*z - 3*_a3*y2*z + 13*_a2*u*y2*z - 12*_a*u2*y2*z + 3*_a2*w*y2*z - 4*_a*u*w*y2*z - 4*_a2*x*y2*z - 2*_a*u*x*y2*z + 12*u2*x*y2*z - 2*_a*w*x*y2*z + 4*u*w*x*y2*z + 5*_a*x2*y2*z - 11*u*x2*y2*z - w*x2*y2*z + 2*x3*y2*z - 9*_a2*y3*z + 24*_a*u*y3*z - 16*u2*y3*z - 6*_a*x*y3*z + 8*u*x*y3*z - x2*y3*z - 9*_a4*z2 + 21*_a3*u*z2 - 9*_a2*u2*z2 - 4*_a*u3*z2 - 3*_a3*w*z2 - 2*_a2*u*w*z2 + 8*_a*u2*w*z2 + 3*_a2*w2*z2 - 4*_a*u*w2*z2 - 6*_a3*x*z2 + 7*_a2*u*x*z2 - 2*_a*u2*x*z2 + 4*u3*x*z2 + 11*_a2*w*x*z2 - 12*_a*u*w*x*z2 - 8*u2*w*x*z2 - 2*_a*w2*x*z2 + 4*u*w2*x*z2 + 11*_a2*x2*z2 - 25*_a*u*x2*z2 + 11*u2*x2*z2 - 5*_a*w*x2*z2 + 14*u*w*x2*z2 - w2*x2*z2 + 4*_a*x3*z2 - 3*u*x3*z2 - 3*w*x3*z2 - 3*_a3*y*z2 + 13*_a2*u*y*z2 - 12*_a*u2*y*z2 + 3*_a2*w*y*z2 - 4*_a*u*w*y*z2 - 4*_a2*x*y*z2 - 2*_a*u*x*y*z2 + 12*u2*x*y*z2 - 2*_a*w*x*y*z2 + 4*u*w*x*y*z2 + 5*_a*x2*y*z2 - 11*u*x2*y*z2 - w*x2*y*z2 + 2*x3*y*z2 + 12*_a2*y2*z2 - 34*_a*u*y2*z2 + 24*u2*y2*z2 + 10*_a*x*y2*z2 - 14*u*x*y2*z2 + 2*x2*y2*z2 + 9*_a3*z3 - 21*_a2*u*z3 + 12*_a*u2*z3 - 3*_a2*w*z3 + 4*_a*u*w*z3 - 6*_a2*x*z3 + 18*_a*u*x*z3 - 12*u2*x*z3 + 2*_a*w*x*z3 - 4*u*w*x*z3 - 3*_a*x2*z3 + 3*u*x2*z3 + w*x2*z3 - 9*_a2*y*z3 + 24*_a*u*y*z3 - 16*u2*y*z3 - 6*_a*x*y*z3 + 8*u*x*y*z3 - x2*y*z3 + 3*_a2*z4 - 7*_a*u*z4 + 4*u2*z4 + _a*x*z4 - u*x*z4;
      *(result+7) = 0;
    }
  else if (SAME2(y,z))
    {
      *(result) = 18*_a6;
      *(result+1) = -108*_a6 + 21*_a5*u + 21*_a5*v + 9*_a5*w + 15*_a5*x + 42*_a5*y;
      *(result+2) = 270*_a6 - 105*_a5*u - 9*_a4*u2 - 105*_a5*v + 33*_a4*u*v - 9*_a4*v2 - 45*_a5*w + 15*_a4*u*w + 15*_a4*v*w - 9*_a4*w2 - 75*_a5*x + 26*_a4*u*x + 26*_a4*v*x + 3*_a4*w*x - 16*_a4*x2 - 210*_a5*y + 49*_a4*u*y + 49*_a4*v*y + 30*_a4*w*y + 52*_a4*x*y + 15*_a4*y2;
      *(result+3) = -360*_a6 + 210*_a5*u + 36*_a4*u2 - 9*_a3*u3 + 210*_a5*v - 132*_a4*u*v + 3*_a3*u2*v + 36*_a4*v2 + 3*_a3*u*v2 - 9*_a3*v3 + 90*_a5*w - 60*_a4*u*w + 3*_a3*u2*w - 60*_a4*v*w + 18*_a3*u*v*w + 3*_a3*v2*w + 36*_a4*w2 - 6*_a3*u*w2 - 6*_a3*v*w2 + 150*_a5*x - 104*_a4*u*x + 6*_a3*u2*x - 104*_a4*v*x + 16*_a3*u*v*x + 6*_a3*v2*x - 12*_a4*w*x + 16*_a3*u*w*x + 16*_a3*v*w*x - 12*_a3*w2*x + 64*_a4*x2 - 8*_a3*u*x2 - 8*_a3*v*x2 - 14*_a3*w*x2 - 6*_a3*x3 + 420*_a5*y - 196*_a4*u*y - 21*_a3*u2*y - 196*_a4*v*y + 86*_a3*u*v*y - 21*_a3*v2*y - 120*_a4*w*y + 32*_a3*u*w*y + 32*_a3*v*w*y - 12*_a3*w2*y - 208*_a4*x*y + 76*_a3*u*x*y + 76*_a3*v*x*y + 32*_a3*w*x*y - 16*_a3*x2*y - 60*_a4*y2 + 22*_a3*u*y2 + 22*_a3*v*y2 + 24*_a3*w*y2 + 28*_a3*x*y2 - 12*_a3*y3;
      *(result+4) = 270*_a6 - 210*_a5*u - 54*_a4*u2 + 27*_a3*u3 + 3*_a2*u4 - 210*_a5*v + 198*_a4*u*v - 9*_a3*u2*v - 9*_a2*u3*v - 54*_a4*v2 - 9*_a3*u*v2 + 12*_a2*u2*v2 + 27*_a3*v3 - 9*_a2*u*v3 + 3*_a2*v4 - 90*_a5*w + 90*_a4*u*w - 9*_a3*u2*w - 3*_a2*u3*w + 90*_a4*v*w - 54*_a3*u*v*w + 3*_a2*u2*v*w - 9*_a3*v2*w + 3*_a2*u*v2*w - 3*_a2*v3*w - 54*_a4*w2 + 18*_a3*u*w2 + 3*_a2*u2*w2 + 18*_a3*v*w2 - 6*_a2*u*v*w2 + 3*_a2*v2*w2 - 150*_a5*x + 156*_a4*u*x - 18*_a3*u2*x - 6*_a2*u3*x + 156*_a4*v*x - 48*_a3*u*v*x - 4*_a2*u2*v*x - 18*_a3*v2*x - 4*_a2*u*v2*x - 6*_a2*v3*x + 18*_a4*w*x - 48*_a3*u*w*x + 11*_a2*u2*w*x - 48*_a3*v*w*x + 18*_a2*u*v*w*x + 11*_a2*v2*w*x + 36*_a3*w2*x - 10*_a2*u*w2*x - 10*_a2*v*w2*x - 96*_a4*x2 + 24*_a3*u*x2 + 11*_a2*u2*x2 + 24*_a3*v*x2 - 12*_a2*u*v*x2 + 11*_a2*v2*x2 + 42*_a3*w*x2 - 10*_a2*u*w*x2 - 10*_a2*v*w*x2 + 2*_a2*w2*x2 + 18*_a3*x3 - 10*_a2*u*x3 - 10*_a2*v*x3 - 2*_a2*w*x3 + 6*_a2*x4 - 420*_a5*y + 294*_a4*u*y + 63*_a3*u2*y - 21*_a2*u3*y + 294*_a4*v*y - 258*_a3*u*v*y + 13*_a2*u2*v*y + 63*_a3*v2*y + 13*_a2*u*v2*y - 21*_a2*v3*y + 180*_a4*w*y - 96*_a3*u*w*y - 2*_a2*u2*w*y - 96*_a3*v*w*y + 36*_a2*u*v*w*y - 2*_a2*v2*w*y + 36*_a3*w2*y - 8*_a2*u*w2*y - 8*_a2*v*w2*y + 312*_a4*x*y - 228*_a3*u*x*y + 7*_a2*u2*x*y - 228*_a3*v*x*y + 70*_a2*u*v*x*y + 7*_a2*v2*x*y - 96*_a3*w*x*y + 48*_a2*u*w*x*y + 48*_a2*v*w*x*y - 20*_a2*w2*x*y + 48*_a3*x2*y + 6*_a2*u*x2*y + 6*_a2*v*x2*y - 20*_a2*w*x2*y - 20*_a2*x3*y + 90*_a4*y2 - 66*_a3*u*y2 - 9*_a2*u2*y2 - 66*_a3*v*y2 + 50*_a2*u*v*y2 - 9*_a2*v2*y2 - 72*_a3*w*y2 + 16*_a2*u*w*y2 + 16*_a2*v*w*y2 - 84*_a3*x*y2 + 42*_a2*u*x*y2 + 42*_a2*v*x*y2 + 40*_a2*w*x*y2 + 10*_a2*x2*y2 + 36*_a3*y3 - 8*_a2*u*y3 - 8*_a2*v*y3 - 20*_a2*x*y3;
      *(result+5) = -108*_a6 + 105*_a5*u + 36*_a4*u2 - 27*_a3*u3 - 6*_a2*u4 + 105*_a5*v - 132*_a4*u*v + 9*_a3*u2*v + 18*_a2*u3*v + 36*_a4*v2 + 9*_a3*u*v2 - 24*_a2*u2*v2 - 27*_a3*v3 + 18*_a2*u*v3 - 6*_a2*v4 + 45*_a5*w - 60*_a4*u*w + 9*_a3*u2*w + 6*_a2*u3*w - 60*_a4*v*w + 54*_a3*u*v*w - 6*_a2*u2*v*w + 9*_a3*v2*w - 6*_a2*u*v2*w + 6*_a2*v3*w + 36*_a4*w2 - 18*_a3*u*w2 - 6*_a2*u2*w2 - 18*_a3*v*w2 + 12*_a2*u*v*w2 - 6*_a2*v2*w2 + 75*_a5*x - 104*_a4*u*x + 18*_a3*u2*x + 12*_a2*u3*x - _a*u4*x - 104*_a4*v*x + 48*_a3*u*v*x + 8*_a2*u2*v*x + 6*_a*u3*v*x + 18*_a3*v2*x + 8*_a2*u*v2*x - 10*_a*u2*v2*x + 12*_a2*v3*x + 6*_a*u*v3*x - _a*v4*x - 12*_a4*w*x + 48*_a3*u*w*x - 22*_a2*u2*w*x - 2*_a*u3*w*x + 48*_a3*v*w*x - 36*_a2*u*v*w*x + 2*_a*u2*v*w*x - 22*_a2*v2*w*x + 2*_a*u*v2*w*x - 2*_a*v3*w*x - 36*_a3*w2*x + 20*_a2*u*w2*x + 2*_a*u2*w2*x + 20*_a2*v*w2*x - 4*_a*u*v*w2*x + 2*_a*v2*w2*x + 64*_a4*x2 - 24*_a3*u*x2 - 22*_a2*u2*x2 + 3*_a*u3*x2 - 24*_a3*v*x2 + 24*_a2*u*v*x2 - 5*_a*u2*v*x2 - 22*_a2*v2*x2 - 5*_a*u*v2*x2 + 3*_a*v3*x2 - 42*_a3*w*x2 + 20*_a2*u*w*x2 + 5*_a*u2*w*x2 + 20*_a2*v*w*x2 - 2*_a*u*v*w*x2 + 5*_a*v2*w*x2 - 4*_a2*w2*x2 - 2*_a*u*w2*x2 - 2*_a*v*w2*x2 - 18*_a3*x3 + 20*_a2*u*x3 - 4*_a*u2*x3 + 20*_a2*v*x3 + 4*_a*u*v*x3 - 4*_a*v2*x3 + 4*_a2*w*x3 - 8*_a*u*w*x3 - 8*_a*v*w*x3 + 4*_a*w2*x3 - 12*_a2*x4 + 3*_a*u*x4 + 3*_a*v*x4 + 5*_a*w*x4 - _a*x5 + 210*_a5*y - 196*_a4*u*y - 63*_a3*u2*y + 42*_a2*u3*y + 7*_a*u4*y - 196*_a4*v*y + 258*_a3*u*v*y - 26*_a2*u2*v*y - 24*_a*u3*v*y - 63*_a3*v2*y - 26*_a2*u*v2*y + 34*_a*u2*v2*y + 42*_a2*v3*y - 24*_a*u*v3*y + 7*_a*v4*y - 120*_a4*w*y + 96*_a3*u*w*y + 4*_a2*u2*w*y - 4*_a*u3*w*y + 96*_a3*v*w*y - 72*_a2*u*v*w*y + 4*_a*u2*v*w*y + 4*_a2*v2*w*y + 4*_a*u*v2*w*y - 4*_a*v3*w*y - 36*_a3*w2*y + 16*_a2*u*w2*y + 4*_a*u2*w2*y + 16*_a2*v*w2*y - 8*_a*u*v*w2*y + 4*_a*v2*w2*y - 208*_a4*x*y + 228*_a3*u*x*y - 14*_a2*u2*x*y - 18*_a*u3*x*y + 228*_a3*v*x*y - 140*_a2*u*v*x*y + 2*_a*u2*v*x*y - 14*_a2*v2*x*y + 2*_a*u*v2*x*y - 18*_a*v3*x*y + 96*_a3*w*x*y - 96*_a2*u*w*x*y + 12*_a*u2*w*x*y - 96*_a2*v*w*x*y + 40*_a*u*v*w*x*y + 12*_a*v2*w*x*y + 40*_a2*w2*x*y - 16*_a*u*w2*x*y - 16*_a*v*w2*x*y - 48*_a3*x2*y - 12*_a2*u*x2*y + 25*_a*u2*x2*y - 12*_a2*v*x2*y - 14*_a*u*v*x2*y + 25*_a*v2*x2*y + 40*_a2*w*x2*y - 4*_a*w2*x2*y + 40*_a2*x3*y - 20*_a*u*x3*y - 20*_a*v*x3*y - 16*_a*w*x3*y + 6*_a*x4*y - 60*_a4*y2 + 66*_a3*u*y2 + 18*_a2*u2*y2 - 12*_a*u3*y2 + 66*_a3*v*y2 - 100*_a2*u*v*y2 + 12*_a*u2*v*y2 + 18*_a2*v2*y2 + 12*_a*u*v2*y2 - 12*_a*v3*y2 + 72*_a3*w*y2 - 32*_a2*u*w*y2 - 8*_a*u2*w*y2 - 32*_a2*v*w*y2 + 16*_a*u*v*w*y2 - 8*_a*v2*w*y2 + 84*_a3*x*y2 - 84*_a2*u*x*y2 + 2*_a*u2*x*y2 - 84*_a2*v*x*y2 + 60*_a*u*v*x*y2 + 2*_a*v2*x*y2 - 80*_a2*w*x*y2 + 32*_a*u*w*x*y2 + 32*_a*v*w*x*y2 - 20*_a2*x2*y2 + 18*_a*u*x2*y2 + 18*_a*v*x2*y2 + 8*_a*w*x2*y2 - 4*_a*x3*y2 - 36*_a3*y3 + 16*_a2*u*y3 + 4*_a*u2*y3 + 16*_a2*v*y3 - 8*_a*u*v*y3 + 4*_a*v2*y3 + 40*_a2*x*y3 - 16*_a*u*x*y3 - 16*_a*v*x*y3 - 4*_a*x2*y3;
      *(result+6) = 18*_a6 - 21*_a5*u - 9*_a4*u2 + 9*_a3*u3 + 3*_a2*u4 - 21*_a5*v + 33*_a4*u*v - 3*_a3*u2*v - 9*_a2*u3*v - 9*_a4*v2 - 3*_a3*u*v2 + 12*_a2*u2*v2 + 9*_a3*v3 - 9*_a2*u*v3 + 3*_a2*v4 - 9*_a5*w + 15*_a4*u*w - 3*_a3*u2*w - 3*_a2*u3*w + 15*_a4*v*w - 18*_a3*u*v*w + 3*_a2*u2*v*w - 3*_a3*v2*w + 3*_a2*u*v2*w - 3*_a2*v3*w - 9*_a4*w2 + 6*_a3*u*w2 + 3*_a2*u2*w2 + 6*_a3*v*w2 - 6*_a2*u*v*w2 + 3*_a2*v2*w2 - 15*_a5*x + 26*_a4*u*x - 6*_a3*u2*x - 6*_a2*u3*x + _a*u4*x + 26*_a4*v*x - 16*_a3*u*v*x - 4*_a2*u2*v*x - 6*_a*u3*v*x - 6*_a3*v2*x - 4*_a2*u*v2*x + 10*_a*u2*v2*x - 6*_a2*v3*x - 6*_a*u*v3*x + _a*v4*x + 3*_a4*w*x - 16*_a3*u*w*x + 11*_a2*u2*w*x + 2*_a*u3*w*x - 16*_a3*v*w*x + 18*_a2*u*v*w*x - 2*_a*u2*v*w*x + 11*_a2*v2*w*x - 2*_a*u*v2*w*x + 2*_a*v3*w*x + 12*_a3*w2*x - 10*_a2*u*w2*x - 2*_a*u2*w2*x - 10*_a2*v*w2*x + 4*_a*u*v*w2*x - 2*_a*v2*w2*x - 16*_a4*x2 + 8*_a3*u*x2 + 11*_a2*u2*x2 - 3*_a*u3*x2 + 8*_a3*v*x2 - 12*_a2*u*v*x2 + 5*_a*u2*v*x2 - u3*v*x2 + 11*_a2*v2*x2 + 5*_a*u*v2*x2 + 2*u2*v2*x2 - 3*_a*v3*x2 - u*v3*x2 + 14*_a3*w*x2 - 10*_a2*u*w*x2 - 5*_a*u2*w*x2 + u3*w*x2 - 10*_a2*v*w*x2 + 2*_a*u*v*w*x2 - u2*v*w*x2 - 5*_a*v2*w*x2 - u*v2*w*x2 + v3*w*x2 + 2*_a2*w2*x2 + 2*_a*u*w2*x2 - u2*w2*x2 + 2*_a*v*w2*x2 + 2*u*v*w2*x2 - v2*w2*x2 + 6*_a3*x3 - 10*_a2*u*x3 + 4*_a*u2*x3 - 10*_a2*v*x3 - 4*_a*u*v*x3 + 2*u2*v*x3 + 4*_a*v2*x3 + 2*u*v2*x3 - 2*_a2*w*x3 + 8*_a*u*w*x3 - 3*u2*w*x3 + 8*_a*v*w*x3 - 2*u*v*w*x3 - 3*v2*w*x3 - 4*_a*w2*x3 + 2*u*w2*x3 + 2*v*w2*x3 + 6*_a2*x4 - 3*_a*u*x4 - 3*_a*v*x4 - u*v*x4 - 5*_a*w*x4 + 3*u*w*x4 + 3*v*w*x4 - w2*x4 + _a*x5 - w*x5 - 42*_a5*y + 49*_a4*u*y + 21*_a3*u2*y - 21*_a2*u3*y - 7*_a*u4*y + 49*_a4*v*y - 86*_a3*u*v*y + 13*_a2*u2*v*y + 24*_a*u3*v*y + 21*_a3*v2*y + 13*_a2*u*v2*y - 34*_a*u2*v2*y - 21*_a2*v3*y + 24*_a*u*v3*y - 7*_a*v4*y + 30*_a4*w*y - 32*_a3*u*w*y - 2*_a2*u2*w*y + 4*_a*u3*w*y - 32*_a3*v*w*y + 36*_a2*u*v*w*y - 4*_a*u2*v*w*y - 2*_a2*v2*w*y - 4*_a*u*v2*w*y + 4*_a*v3*w*y + 12*_a3*w2*y - 8*_a2*u*w2*y - 4*_a*u2*w2*y - 8*_a2*v*w2*y + 8*_a*u*v*w2*y - 4*_a*v2*w2*y + 52*_a4*x*y - 76*_a3*u*x*y + 7*_a2*u2*x*y + 18*_a*u3*x*y - u4*x*y - 76*_a3*v*x*y + 70*_a2*u*v*x*y - 2*_a*u2*v*x*y + 8*u3*v*x*y + 7*_a2*v2*x*y - 2*_a*u*v2*x*y - 14*u2*v2*x*y + 18*_a*v3*x*y + 8*u*v3*x*y - v4*x*y - 32*_a3*w*x*y + 48*_a2*u*w*x*y - 12*_a*u2*w*x*y - 4*u3*w*x*y + 48*_a2*v*w*x*y - 40*_a*u*v*w*x*y + 4*u2*v*w*x*y - 12*_a*v2*w*x*y + 4*u*v2*w*x*y - 4*v3*w*x*y - 20*_a2*w2*x*y + 16*_a*u*w2*x*y + 4*u2*w2*x*y + 16*_a*v*w2*x*y - 8*u*v*w2*x*y + 4*v2*w2*x*y + 16*_a3*x2*y + 6*_a2*u*x2*y - 25*_a*u2*x2*y + 3*u3*x2*y + 6*_a2*v*x2*y + 14*_a*u*v*x2*y - 11*u2*v*x2*y - 25*_a*v2*x2*y - 11*u*v2*x2*y + 3*v3*x2*y - 20*_a2*w*x2*y + 14*u2*w*x2*y + 4*u*v*w*x2*y + 14*v2*w*x2*y + 4*_a*w2*x2*y - 8*u*w2*x2*y - 8*v*w2*x2*y - 20*_a2*x3*y + 20*_a*u*x3*y - 3*u2*x3*y + 20*_a*v*x3*y + 2*u*v*x3*y - 3*v2*x3*y + 16*_a*w*x3*y - 16*u*w*x3*y - 16*v*w*x3*y + 4*w2*x3*y - 6*_a*x4*y + u*x4*y + v*x4*y + 6*w*x4*y + 15*_a4*y2 - 22*_a3*u*y2 - 9*_a2*u2*y2 + 12*_a*u3*y2 + 4*u4*y2 - 22*_a3*v*y2 + 50*_a2*u*v*y2 - 12*_a*u2*v*y2 - 16*u3*v*y2 - 9*_a2*v2*y2 - 12*_a*u*v2*y2 + 24*u2*v2*y2 + 12*_a*v3*y2 - 16*u*v3*y2 + 4*v4*y2 - 24*_a3*w*y2 + 16*_a2*u*w*y2 + 8*_a*u2*w*y2 + 16*_a2*v*w*y2 - 16*_a*u*v*w*y2 + 8*_a*v2*w*y2 - 28*_a3*x*y2 + 42*_a2*u*x*y2 - 2*_a*u2*x*y2 - 12*u3*x*y2 + 42*_a2*v*x*y2 - 60*_a*u*v*x*y2 + 12*u2*v*x*y2 - 2*_a*v2*x*y2 + 12*u*v2*x*y2 - 12*v3*x*y2 + 40*_a2*w*x*y2 - 32*_a*u*w*x*y2 - 8*u2*w*x*y2 - 32*_a*v*w*x*y2 + 16*u*v*w*x*y2 - 8*v2*w*x*y2 + 10*_a2*x2*y2 - 18*_a*u*x2*y2 + 11*u2*x2*y2 - 18*_a*v*x2*y2 + 10*u*v*x2*y2 + 11*v2*x2*y2 - 8*_a*w*x2*y2 + 16*u*w*x2*y2 + 16*v*w*x2*y2 + 4*_a*x3*y2 - 2*u*x3*y2 - 2*v*x3*y2 - 8*w*x3*y2 - x4*y2 + 12*_a3*y3 - 8*_a2*u*y3 - 4*_a*u2*y3 - 8*_a2*v*y3 + 8*_a*u*v*y3 - 4*_a*v2*y3 - 20*_a2*x*y3 + 16*_a*u*x*y3 + 4*u2*x*y3 + 16*_a*v*x*y3 - 8*u*v*x*y3 + 4*v2*x*y3 + 4*_a*x2*y3 - 8*u*x2*y3 - 8*v*x2*y3 + 4*x3*y3;
      *(result+7) = 0;
    }
  else
    {
      *(result) = -18*_a7;
      *(result+1) = 126*_a7 - 21*_a6*u - 21*_a6*v - 9*_a6*w - 33*_a6*x - 21*_a6*y - 21*_a6*z;
      *(result+2) = -378*_a7 + 126*_a6*u + 9*_a5*u2 + 126*_a6*v - 33*_a5*u*v + 9*_a5*v2 + 54*_a6*w - 15*_a5*u*w - 15*_a5*v*w + 9*_a5*w2 + 198*_a6*x - 47*_a5*u*x - 47*_a5*v*x - 12*_a5*w*x + _a5*x2 + 126*_a6*y - 20*_a5*u*y - 29*_a5*v*y - 15*_a5*w*y - 47*_a5*x*y + 9*_a5*y2 + 126*_a6*z - 29*_a5*u*z - 20*_a5*v*z - 15*_a5*w*z - 47*_a5*x*z - 33*_a5*y*z + 9*_a5*z2;
      *(result+3) = 630*_a7 - 315*_a6*u - 45*_a5*u2 + 9*_a4*u3 - 315*_a6*v + 165*_a5*u*v - 3*_a4*u2*v - 45*_a5*v2 - 3*_a4*u*v2 + 9*_a4*v3 - 135*_a6*w + 75*_a5*u*w - 3*_a4*u2*w + 75*_a5*v*w - 18*_a4*u*v*w - 3*_a4*v2*w - 45*_a5*w2 + 6*_a4*u*w2 + 6*_a4*v*w2 - 495*_a6*x + 235*_a5*u*x + 3*_a4*u2*x + 235*_a5*v*x - 49*_a4*u*v*x + 3*_a4*v2*x + 60*_a5*w*x - 31*_a4*u*w*x - 31*_a4*v*w*x + 21*_a4*w2*x - 5*_a5*x2 - 18*_a4*u*x2 - 18*_a4*v*x2 + 11*_a4*w*x2 + 22*_a4*x3 - 315*_a6*y + 100*_a5*u*y + 18*_a4*u2*y + 145*_a5*v*y - 43*_a4*u*v*y + 3*_a4*v2*y + 75*_a5*w*y - 25*_a4*u*w*y - 7*_a4*v*w*y + 6*_a4*w2*y + 235*_a5*x*y - 61*_a4*u*x*y - 64*_a4*v*x*y - 31*_a4*w*x*y - 18*_a4*x2*y - 45*_a5*y2 + 18*_a4*u*y2 + 3*_a4*v*y2 - 3*_a4*w*y2 + 3*_a4*x*y2 + 9*_a4*y3 - 315*_a6*z + 145*_a5*u*z + 3*_a4*u2*z + 100*_a5*v*z - 43*_a4*u*v*z + 18*_a4*v2*z + 75*_a5*w*z - 7*_a4*u*w*z - 25*_a4*v*w*z + 6*_a4*w2*z + 235*_a5*x*z - 64*_a4*u*x*z - 61*_a4*v*x*z - 31*_a4*w*x*z - 18*_a4*x2*z + 165*_a5*y*z - 43*_a4*u*y*z - 43*_a4*v*y*z - 18*_a4*w*y*z - 49*_a4*x*y*z - 3*_a4*y2*z - 45*_a5*z2 + 3*_a4*u*z2 + 18*_a4*v*z2 - 3*_a4*w*z2 + 3*_a4*x*z2 - 3*_a4*y*z2 + 9*_a4*z3;
      *(result+4) = -630*_a7 + 420*_a6*u + 90*_a5*u2 - 36*_a4*u3 - 3*_a3*u4 + 420*_a6*v - 330*_a5*u*v + 12*_a4*u2*v + 9*_a3*u3*v + 90*_a5*v2 + 12*_a4*u*v2 - 12*_a3*u2*v2 - 36*_a4*v3 + 9*_a3*u*v3 - 3*_a3*v4 + 180*_a6*w - 150*_a5*u*w + 12*_a4*u2*w + 3*_a3*u3*w - 150*_a5*v*w + 72*_a4*u*v*w - 3*_a3*u2*v*w + 12*_a4*v2*w - 3*_a3*u*v2*w + 3*_a3*v3*w + 90*_a5*w2 - 24*_a4*u*w2 - 3*_a3*u2*w2 - 24*_a4*v*w2 + 6*_a3*u*v*w2 - 3*_a3*v2*w2 + 660*_a6*x - 470*_a5*u*x - 12*_a4*u2*x + 15*_a3*u3*x - 470*_a5*v*x + 196*_a4*u*v*x + _a3*u2*v*x - 12*_a4*v2*x + _a3*u*v2*x + 15*_a3*v3*x - 120*_a5*w*x + 124*_a4*u*w*x - 14*_a3*u2*w*x + 124*_a4*v*w*x - 36*_a3*u*v*w*x - 14*_a3*v2*w*x - 84*_a4*w2*x + 16*_a3*u*w2*x + 16*_a3*v*w2*x + 10*_a5*x2 + 72*_a4*u*x2 - 17*_a3*u2*x2 + 72*_a4*v*x2 - 4*_a3*u*v*x2 - 17*_a3*v2*x2 - 44*_a4*w*x2 - 6*_a3*u*w*x2 - 6*_a3*v*w*x2 + 10*_a3*w2*x2 - 88*_a4*x3 + 18*_a3*u*x3 + 18*_a3*v*x3 + 16*_a3*w*x3 + 420*_a6*y - 200*_a5*u*y - 72*_a4*u2*y + 12*_a3*u3*y - 290*_a5*v*y + 172*_a4*u*v*y + _a3*u2*v*y - 12*_a4*v2*y - 14*_a3*u*v2*y + 9*_a3*v3*y - 150*_a5*w*y + 100*_a4*u*w*y - 5*_a3*u2*w*y + 28*_a4*v*w*y - 18*_a3*u*v*w*y + 7*_a3*v2*w*y - 24*_a4*w2*y + 4*_a3*u*w2*y + 4*_a3*v*w2*y - 470*_a5*x*y + 244*_a4*u*x*y + 15*_a3*u2*x*y + 256*_a4*v*x*y - 78*_a3*u*v*x*y - _a3*v2*x*y + 124*_a4*w*x*y - 52*_a3*u*w*x*y - 28*_a3*v*w*x*y + 16*_a3*w2*x*y + 72*_a4*x2*y - 48*_a3*u*x2*y - 34*_a3*v*x2*y - 6*_a3*w*x2*y + 18*_a3*x3*y + 90*_a5*y2 - 72*_a4*u*y2 + 8*_a3*u2*y2 - 12*_a4*v*y2 + 9*_a3*u*v*y2 - 8*_a3*v2*y2 + 12*_a4*w*y2 - 5*_a3*u*w*y2 + 7*_a3*v*w*y2 - 3*_a3*w2*y2 - 12*_a4*x*y2 + 15*_a3*u*x*y2 - _a3*v*x*y2 - 14*_a3*w*x*y2 - 17*_a3*x2*y2 - 36*_a4*y3 + 12*_a3*u*y3 + 9*_a3*v*y3 + 3*_a3*w*y3 + 15*_a3*x*y3 - 3*_a3*y4 + 420*_a6*z - 290*_a5*u*z - 12*_a4*u2*z + 9*_a3*u3*z - 200*_a5*v*z + 172*_a4*u*v*z - 14*_a3*u2*v*z - 72*_a4*v2*z + _a3*u*v2*z + 12*_a3*v3*z - 150*_a5*w*z + 28*_a4*u*w*z + 7*_a3*u2*w*z + 100*_a4*v*w*z - 18*_a3*u*v*w*z - 5*_a3*v2*w*z - 24*_a4*w2*z + 4*_a3*u*w2*z + 4*_a3*v*w2*z - 470*_a5*x*z + 256*_a4*u*x*z - _a3*u2*x*z + 244*_a4*v*x*z - 78*_a3*u*v*x*z + 15*_a3*v2*x*z + 124*_a4*w*x*z - 28*_a3*u*w*x*z - 52*_a3*v*w*x*z + 16*_a3*w2*x*z + 72*_a4*x2*z - 34*_a3*u*x2*z - 48*_a3*v*x2*z - 6*_a3*w*x2*z + 18*_a3*x3*z - 330*_a5*y*z + 172*_a4*u*y*z + 9*_a3*u2*y*z + 172*_a4*v*y*z - 68*_a3*u*v*y*z + 9*_a3*v2*y*z + 72*_a4*w*y*z - 18*_a3*u*w*y*z - 18*_a3*v*w*y*z + 6*_a3*w2*y*z + 196*_a4*x*y*z - 78*_a3*u*x*y*z - 78*_a3*v*x*y*z - 36*_a3*w*x*y*z - 4*_a3*x2*y*z + 12*_a4*y2*z + _a3*u*y2*z - 14*_a3*v*y2*z - 3*_a3*w*y2*z + _a3*x*y2*z + 9*_a3*y3*z + 90*_a5*z2 - 12*_a4*u*z2 - 8*_a3*u2*z2 - 72*_a4*v*z2 + 9*_a3*u*v*z2 + 8*_a3*v2*z2 + 12*_a4*w*z2 + 7*_a3*u*w*z2 - 5*_a3*v*w*z2 - 3*_a3*w2*z2 - 12*_a4*x*z2 - _a3*u*x*z2 + 15*_a3*v*x*z2 - 14*_a3*w*x*z2 - 17*_a3*x2*z2 + 12*_a4*y*z2 - 14*_a3*u*y*z2 + _a3*v*y*z2 - 3*_a3*w*y*z2 + _a3*x*y*z2 - 12*_a3*y2*z2 - 36*_a4*z3 + 9*_a3*u*z3 + 12*_a3*v*z3 + 3*_a3*w*z3 + 15*_a3*x*z3 + 9*_a3*y*z3 - 3*_a3*z4;
      *(result+5) = 378*_a7 - 315*_a6*u - 90*_a5*u2 + 54*_a4*u3 + 9*_a3*u4 - 315*_a6*v + 330*_a5*u*v - 18*_a4*u2*v - 27*_a3*u3*v - 90*_a5*v2 - 18*_a4*u*v2 + 36*_a3*u2*v2 + 54*_a4*v3 - 27*_a3*u*v3 + 9*_a3*v4 - 135*_a6*w + 150*_a5*u*w - 18*_a4*u2*w - 9*_a3*u3*w + 150*_a5*v*w - 108*_a4*u*v*w + 9*_a3*u2*v*w - 18*_a4*v2*w + 9*_a3*u*v2*w - 9*_a3*v3*w - 90*_a5*w2 + 36*_a4*u*w2 + 9*_a3*u2*w2 + 36*_a4*v*w2 - 18*_a3*u*v*w2 + 9*_a3*v2*w2 - 495*_a6*x + 470*_a5*u*x + 18*_a4*u2*x - 45*_a3*u3*x - 2*_a2*u4*x + 470*_a5*v*x - 294*_a4*u*v*x - 3*_a3*u2*v*x + 3*_a2*u3*v*x + 18*_a4*v2*x - 3*_a3*u*v2*x - 2*_a2*u2*v2*x - 45*_a3*v3*x + 3*_a2*u*v3*x - 2*_a2*v4*x + 120*_a5*w*x - 186*_a4*u*w*x + 42*_a3*u2*w*x + 5*_a2*u3*w*x - 186*_a4*v*w*x + 108*_a3*u*v*w*x - 5*_a2*u2*v*w*x + 42*_a3*v2*w*x - 5*_a2*u*v2*w*x + 5*_a2*v3*w*x + 126*_a4*w2*x - 48*_a3*u*w2*x - 5*_a2*u2*w2*x - 48*_a3*v*w2*x + 10*_a2*u*v*w2*x - 5*_a2*v2*w2*x - 10*_a5*x2 - 108*_a4*u*x2 + 51*_a3*u2*x2 + 3*_a2*u3*x2 - 108*_a4*v*x2 + 12*_a3*u*v*x2 + 9*_a2*u2*v*x2 + 51*_a3*v2*x2 + 9*_a2*u*v2*x2 + 3*_a2*v3*x2 + 66*_a4*w*x2 + 18*_a3*u*w*x2 - 16*_a2*u2*w*x2 + 18*_a3*v*w*x2 - 16*_a2*u*v*w*x2 - 16*_a2*v2*w*x2 - 30*_a3*w2*x2 + 12*_a2*u*w2*x2 + 12*_a2*v*w2*x2 + 132*_a4*x3 - 54*_a3*u*x3 - 7*_a2*u2*x3 - 54*_a3*v*x3 + 8*_a2*u*v*x3 - 7*_a2*v2*x3 - 48*_a3*w*x3 + 18*_a2*u*w*x3 + 18*_a2*v*w*x3 - 6*_a2*w2*x3 + 7*_a2*u*x4 + 7*_a2*v*x4 - 3*_a2*w*x4 - 5*_a2*x5 - 315*_a6*y + 200*_a5*u*y + 108*_a4*u2*y - 36*_a3*u3*y - 5*_a2*u4*y + 290*_a5*v*y - 258*_a4*u*v*y - 3*_a3*u2*v*y + 15*_a2*u3*v*y + 18*_a4*v2*y + 42*_a3*u*v2*y - 17*_a2*u2*v2*y - 27*_a3*v3*y + 9*_a2*u*v3*y - 2*_a2*v4*y + 150*_a5*w*y - 150*_a4*u*w*y + 15*_a3*u2*w*y + 5*_a2*u3*w*y - 42*_a4*v*w*y + 54*_a3*u*v*w*y - 11*_a2*u2*v*w*y - 21*_a3*v2*w*y + 7*_a2*u*v2*w*y - _a2*v3*w*y + 36*_a4*w2*y - 12*_a3*u*w2*y - 2*_a2*u2*w2*y - 12*_a3*v*w2*y + 4*_a2*u*v*w2*y - 2*_a2*v2*w2*y + 470*_a5*x*y - 366*_a4*u*x*y - 45*_a3*u2*x*y + 25*_a2*u3*x*y - 384*_a4*v*x*y + 234*_a3*u*v*x*y - 4*_a2*u2*v*x*y + 3*_a3*v2*x*y - 11*_a2*u*v2*x*y + 14*_a2*v3*x*y - 186*_a4*w*x*y + 156*_a3*u*w*x*y - 15*_a2*u2*w*x*y + 84*_a3*v*w*x*y - 38*_a2*u*v*w*x*y + 5*_a2*v2*w*x*y - 48*_a3*w2*x*y + 12*_a2*u*w2*x*y + 12*_a2*v*w2*x*y - 108*_a4*x2*y + 144*_a3*u*x2*y - 21*_a2*u2*x2*y + 102*_a3*v*x2*y - 28*_a2*u*v*x2*y - 11*_a2*v2*x2*y + 18*_a3*w*x2*y - 22*_a2*u*w*x2*y - 26*_a2*v*w*x2*y + 12*_a2*w2*x2*y - 54*_a3*x3*y + 6*_a2*u*x3*y + 8*_a2*v*x3*y + 18*_a2*w*x3*y + 7*_a2*x4*y - 90*_a5*y2 + 108*_a4*u*y2 - 24*_a3*u2*y2 - 2*_a2*u3*y2 + 18*_a4*v*y2 - 27*_a3*u*v*y2 + 9*_a2*u2*v*y2 + 24*_a3*v2*y2 - 10*_a2*u*v2*y2 - _a2*v3*y2 - 18*_a4*w*y2 + 15*_a3*u*w*y2 - _a2*u2*w*y2 - 21*_a3*v*w*y2 + 2*_a2*u*v*w*y2 + 7*_a2*v2*w*y2 + 9*_a3*w2*y2 - 2*_a2*u*w2*y2 - 2*_a2*v*w2*y2 + 18*_a4*x*y2 - 45*_a3*u*x*y2 + 19*_a2*u2*x*y2 + 3*_a3*v*x*y2 - 7*_a2*u*v*x*y2 - 5*_a2*v2*x*y2 + 42*_a3*w*x*y2 - 15*_a2*u*w*x*y2 + 5*_a2*v*w*x*y2 - 5*_a2*w2*x*y2 + 51*_a3*x2*y2 - 21*_a2*u*x2*y2 - 11*_a2*v*x2*y2 - 16*_a2*w*x2*y2 - 7*_a2*x3*y2 + 54*_a4*y3 - 36*_a3*u*y3 - 2*_a2*u2*y3 - 27*_a3*v*y3 + 15*_a2*u*v*y3 - _a2*v2*y3 - 9*_a3*w*y3 + 5*_a2*u*w*y3 - _a2*v*w*y3 - 45*_a3*x*y3 + 25*_a2*u*x*y3 + 14*_a2*v*x*y3 + 5*_a2*w*x*y3 + 3*_a2*x2*y3 + 9*_a3*y4 - 5*_a2*u*y4 - 2*_a2*v*y4 - 2*_a2*x*y4 - 315*_a6*z + 290*_a5*u*z + 18*_a4*u2*z - 27*_a3*u3*z - 2*_a2*u4*z + 200*_a5*v*z - 258*_a4*u*v*z + 42*_a3*u2*v*z + 9*_a2*u3*v*z + 108*_a4*v2*z - 3*_a3*u*v2*z - 17*_a2*u2*v2*z - 36*_a3*v3*z + 15*_a2*u*v3*z - 5*_a2*v4*z + 150*_a5*w*z - 42*_a4*u*w*z - 21*_a3*u2*w*z - _a2*u3*w*z - 150*_a4*v*w*z + 54*_a3*u*v*w*z + 7*_a2*u2*v*w*z + 15*_a3*v2*w*z - 11*_a2*u*v2*w*z + 5*_a2*v3*w*z + 36*_a4*w2*z - 12*_a3*u*w2*z - 2*_a2*u2*w2*z - 12*_a3*v*w2*z + 4*_a2*u*v*w2*z - 2*_a2*v2*w2*z + 470*_a5*x*z - 384*_a4*u*x*z + 3*_a3*u2*x*z + 14*_a2*u3*x*z - 366*_a4*v*x*z + 234*_a3*u*v*x*z - 11*_a2*u2*v*x*z - 45*_a3*v2*x*z - 4*_a2*u*v2*x*z + 25*_a2*v3*x*z - 186*_a4*w*x*z + 84*_a3*u*w*x*z + 5*_a2*u2*w*x*z + 156*_a3*v*w*x*z - 38*_a2*u*v*w*x*z - 15*_a2*v2*w*x*z - 48*_a3*w2*x*z + 12*_a2*u*w2*x*z + 12*_a2*v*w2*x*z - 108*_a4*x2*z + 102*_a3*u*x2*z - 11*_a2*u2*x2*z + 144*_a3*v*x2*z - 28*_a2*u*v*x2*z - 21*_a2*v2*x2*z + 18*_a3*w*x2*z - 26*_a2*u*w*x2*z - 22*_a2*v*w*x2*z + 12*_a2*w2*x2*z - 54*_a3*x3*z + 8*_a2*u*x3*z + 6*_a2*v*x3*z + 18*_a2*w*x3*z + 7*_a2*x4*z + 330*_a5*y*z - 258*_a4*u*y*z - 27*_a3*u2*y*z + 15*_a2*u3*y*z - 258*_a4*v*y*z + 204*_a3*u*v*y*z - 11*_a2*u2*v*y*z - 27*_a3*v2*y*z - 11*_a2*u*v2*y*z + 15*_a2*v3*y*z - 108*_a4*w*y*z + 54*_a3*u*w*y*z + 2*_a2*u2*w*y*z + 54*_a3*v*w*y*z - 20*_a2*u*v*w*y*z + 2*_a2*v2*w*y*z - 18*_a3*w2*y*z + 4*_a2*u*w2*y*z + 4*_a2*v*w2*y*z - 294*_a4*x*y*z + 234*_a3*u*x*y*z - 7*_a2*u2*x*y*z + 234*_a3*v*x*y*z - 96*_a2*u*v*x*y*z - 7*_a2*v2*x*y*z + 108*_a3*w*x*y*z - 38*_a2*u*w*x*y*z - 38*_a2*v*w*x*y*z + 10*_a2*w2*x*y*z + 12*_a3*x2*y*z - 28*_a2*u*x2*y*z - 28*_a2*v*x2*y*z - 16*_a2*w*x2*y*z + 8*_a2*x3*y*z - 18*_a4*y2*z - 3*_a3*u*y2*z + 9*_a2*u2*y2*z + 42*_a3*v*y2*z - 11*_a2*u*v*y2*z - 10*_a2*v2*y2*z + 9*_a3*w*y2*z - 11*_a2*u*w*y2*z + 7*_a2*v*w*y2*z - 3*_a3*x*y2*z - 4*_a2*u*x*y2*z - 11*_a2*v*x*y2*z - 5*_a2*w*x*y2*z + 9*_a2*x2*y2*z - 27*_a3*y3*z + 15*_a2*u*y3*z + 9*_a2*v*y3*z + 3*_a2*x*y3*z - 90*_a5*z2 + 18*_a4*u*z2 + 24*_a3*u2*z2 - _a2*u3*z2 + 108*_a4*v*z2 - 27*_a3*u*v*z2 - 10*_a2*u2*v*z2 - 24*_a3*v2*z2 + 9*_a2*u*v2*z2 - 2*_a2*v3*z2 - 18*_a4*w*z2 - 21*_a3*u*w*z2 + 7*_a2*u2*w*z2 + 15*_a3*v*w*z2 + 2*_a2*u*v*w*z2 - _a2*v2*w*z2 + 9*_a3*w2*z2 - 2*_a2*u*w2*z2 - 2*_a2*v*w2*z2 + 18*_a4*x*z2 + 3*_a3*u*x*z2 - 5*_a2*u2*x*z2 - 45*_a3*v*x*z2 - 7*_a2*u*v*x*z2 + 19*_a2*v2*x*z2 + 42*_a3*w*x*z2 + 5*_a2*u*w*x*z2 - 15*_a2*v*w*x*z2 - 5*_a2*w2*x*z2 + 51*_a3*x2*z2 - 11*_a2*u*x2*z2 - 21*_a2*v*x2*z2 - 16*_a2*w*x2*z2 - 7*_a2*x3*z2 - 18*_a4*y*z2 + 42*_a3*u*y*z2 - 10*_a2*u2*y*z2 - 3*_a3*v*y*z2 - 11*_a2*u*v*y*z2 + 9*_a2*v2*y*z2 + 9*_a3*w*y*z2 + 7*_a2*u*w*y*z2 - 11*_a2*v*w*y*z2 - 3*_a3*x*y*z2 - 11*_a2*u*x*y*z2 - 4*_a2*v*x*y*z2 - 5*_a2*w*x*y*z2 + 9*_a2*x2*y*z2 + 36*_a3*y2*z2 - 17*_a2*u*y2*z2 - 17*_a2*v*y2*z2 - 2*_a2*x*y2*z2 + 54*_a4*z3 - 27*_a3*u*z3 - _a2*u2*z3 - 36*_a3*v*z3 + 15*_a2*u*v*z3 - 2*_a2*v2*z3 - 9*_a3*w*z3 - _a2*u*w*z3 + 5*_a2*v*w*z3 - 45*_a3*x*z3 + 14*_a2*u*x*z3 + 25*_a2*v*x*z3 + 5*_a2*w*x*z3 + 3*_a2*x2*z3 - 27*_a3*y*z3 + 9*_a2*u*y*z3 + 15*_a2*v*y*z3 + 3*_a2*x*y*z3 + 9*_a3*z4 - 2*_a2*u*z4 - 5*_a2*v*z4 - 2*_a2*x*z4;
      *(result+6) = -126*_a7 + 126*_a6*u + 45*_a5*u2 - 36*_a4*u3 - 9*_a3*u4 + 126*_a6*v - 165*_a5*u*v + 12*_a4*u2*v + 27*_a3*u3*v + 45*_a5*v2 + 12*_a4*u*v2 - 36*_a3*u2*v2 - 36*_a4*v3 + 27*_a3*u*v3 - 9*_a3*v4 + 54*_a6*w - 75*_a5*u*w + 12*_a4*u2*w + 9*_a3*u3*w - 75*_a5*v*w + 72*_a4*u*v*w - 9*_a3*u2*v*w + 12*_a4*v2*w - 9*_a3*u*v2*w + 9*_a3*v3*w + 45*_a5*w2 - 24*_a4*u*w2 - 9*_a3*u2*w2 - 24*_a4*v*w2 + 18*_a3*u*v*w2 - 9*_a3*v2*w2 + 198*_a6*x - 235*_a5*u*x - 12*_a4*u2*x + 45*_a3*u3*x + 4*_a2*u4*x - 235*_a5*v*x + 196*_a4*u*v*x + 3*_a3*u2*v*x - 6*_a2*u3*v*x - 12*_a4*v2*x + 3*_a3*u*v2*x + 4*_a2*u2*v2*x + 45*_a3*v3*x - 6*_a2*u*v3*x + 4*_a2*v4*x - 60*_a5*w*x + 124*_a4*u*w*x - 42*_a3*u2*w*x - 10*_a2*u3*w*x + 124*_a4*v*w*x - 108*_a3*u*v*w*x + 10*_a2*u2*v*w*x - 42*_a3*v2*w*x + 10*_a2*u*v2*w*x - 10*_a2*v3*w*x - 84*_a4*w2*x + 48*_a3*u*w2*x + 10*_a2*u2*w2*x + 48*_a3*v*w2*x - 20*_a2*u*v*w2*x + 10*_a2*v2*w2*x + 5*_a5*x2 + 72*_a4*u*x2 - 51*_a3*u2*x2 - 6*_a2*u3*x2 + _a*u4*x2 + 72*_a4*v*x2 - 12*_a3*u*v*x2 - 18*_a2*u2*v*x2 - 5*_a*u3*v*x2 - 51*_a3*v2*x2 - 18*_a2*u*v2*x2 + 8*_a*u2*v2*x2 - 6*_a2*v3*x2 - 5*_a*u*v3*x2 + _a*v4*x2 - 44*_a4*w*x2 - 18*_a3*u*w*x2 + 32*_a2*u2*w*x2 + _a*u3*w*x2 - 18*_a3*v*w*x2 + 32*_a2*u*v*w*x2 - _a*u2*v*w*x2 + 32*_a2*v2*w*x2 - _a*u*v2*w*x2 + _a*v3*w*x2 + 30*_a3*w2*x2 - 24*_a2*u*w2*x2 - _a*u2*w2*x2 - 24*_a2*v*w2*x2 + 2*_a*u*v*w2*x2 - _a*v2*w2*x2 - 88*_a4*x3 + 54*_a3*u*x3 + 14*_a2*u2*x3 - 3*_a*u3*x3 + 54*_a3*v*x3 - 16*_a2*u*v*x3 + 3*_a*u2*v*x3 + 14*_a2*v2*x3 + 3*_a*u*v2*x3 - 3*_a*v3*x3 + 48*_a3*w*x3 - 36*_a2*u*w*x3 - 2*_a*u2*w*x3 - 36*_a2*v*w*x3 + 4*_a*u*v*w*x3 - 2*_a*v2*w*x3 + 12*_a2*w2*x3 - 14*_a2*u*x4 + 4*_a*u2*x4 - 14*_a2*v*x4 - 3*_a*u*v*x4 + 4*_a*v2*x4 + 6*_a2*w*x4 + 5*_a*u*w*x4 + 5*_a*v*w*x4 - 3*_a*w2*x4 + 10*_a2*x5 - 3*_a*u*x5 - 3*_a*v*x5 - 4*_a*w*x5 + _a*x6 + 126*_a6*y - 100*_a5*u*y - 72*_a4*u2*y + 36*_a3*u3*y + 10*_a2*u4*y - 145*_a5*v*y + 172*_a4*u*v*y + 3*_a3*u2*v*y - 30*_a2*u3*v*y - 12*_a4*v2*y - 42*_a3*u*v2*y + 34*_a2*u2*v2*y + 27*_a3*v3*y - 18*_a2*u*v3*y + 4*_a2*v4*y - 75*_a5*w*y + 100*_a4*u*w*y - 15*_a3*u2*w*y - 10*_a2*u3*w*y + 28*_a4*v*w*y - 54*_a3*u*v*w*y + 22*_a2*u2*v*w*y + 21*_a3*v2*w*y - 14*_a2*u*v2*w*y + 2*_a2*v3*w*y - 24*_a4*w2*y + 12*_a3*u*w2*y + 4*_a2*u2*w2*y + 12*_a3*v*w2*y - 8*_a2*u*v*w2*y + 4*_a2*v2*w2*y - 235*_a5*x*y + 244*_a4*u*x*y + 45*_a3*u2*x*y - 50*_a2*u3*x*y - 4*_a*u4*x*y + 256*_a4*v*x*y - 234*_a3*u*v*x*y + 8*_a2*u2*v*x*y + 10*_a*u3*v*x*y - 3*_a3*v2*x*y + 22*_a2*u*v2*x*y - 10*_a*u2*v2*x*y - 28*_a2*v3*x*y + 6*_a*u*v3*x*y - 2*_a*v4*x*y + 124*_a4*w*x*y - 156*_a3*u*w*x*y + 30*_a2*u2*w*x*y + 6*_a*u3*w*x*y - 84*_a3*v*w*x*y + 76*_a2*u*v*w*x*y - 10*_a*u2*v*w*x*y - 10*_a2*v2*w*x*y + 2*_a*u*v2*w*x*y + 2*_a*v3*w*x*y + 48*_a3*w2*x*y - 24*_a2*u*w2*x*y - 4*_a*u2*w2*x*y - 24*_a2*v*w2*x*y + 8*_a*u*v*w2*x*y - 4*_a*v2*w2*x*y + 72*_a4*x2*y - 144*_a3*u*x2*y + 42*_a2*u2*x2*y + 10*_a*u3*x2*y - 102*_a3*v*x2*y + 56*_a2*u*v*x2*y + _a*u2*v*x2*y + 22*_a2*v2*x2*y + 8*_a*u*v2*x2*y + 5*_a*v3*x2*y - 18*_a3*w*x2*y + 44*_a2*u*w*x2*y - 15*_a*u2*w*x2*y + 52*_a2*v*w*x2*y - 22*_a*u*v*w*x2*y - 11*_a*v2*w*x2*y - 24*_a2*w2*x2*y + 12*_a*u*w2*x2*y + 12*_a*v*w2*x2*y + 54*_a3*x3*y - 12*_a2*u*x3*y - 15*_a*u2*x3*y - 16*_a2*v*x3*y + 6*_a*u*v*x3*y - 7*_a*v2*x3*y - 36*_a2*w*x3*y + 12*_a*u*w*x3*y + 4*_a*v*w*x3*y - 14*_a2*x4*y + 12*_a*u*x4*y + 7*_a*v*x4*y + 5*_a*w*x4*y - 3*_a*x5*y + 45*_a5*y2 - 72*_a4*u*y2 + 24*_a3*u2*y2 + 4*_a2*u3*y2 - _a*u4*y2 - 12*_a4*v*y2 + 27*_a3*u*v*y2 - 18*_a2*u2*v*y2 + 3*_a*u3*v*y2 - 24*_a3*v2*y2 + 20*_a2*u*v2*y2 - 2*_a*u2*v2*y2 + 2*_a2*v3*y2 - _a*u*v3*y2 + _a*v4*y2 + 12*_a4*w*y2 - 15*_a3*u*w*y2 + 2*_a2*u2*w*y2 + _a*u3*w*y2 + 21*_a3*v*w*y2 - 4*_a2*u*v*w*y2 - 5*_a*u2*v*w*y2 - 14*_a2*v2*w*y2 + 7*_a*u*v2*w*y2 - 3*_a*v3*w*y2 - 9*_a3*w2*y2 + 4*_a2*u*w2*y2 + _a*u2*w2*y2 + 4*_a2*v*w2*y2 - 2*_a*u*v*w2*y2 + _a*v2*w2*y2 - 12*_a4*x*y2 + 45*_a3*u*x*y2 - 38*_a2*u2*x*y2 + 5*_a*u3*x*y2 - 3*_a3*v*x*y2 + 14*_a2*u*v*x*y2 + _a*u2*v*x*y2 + 10*_a2*v2*x*y2 - 13*_a*u*v2*x*y2 - _a*v3*x*y2 - 42*_a3*w*x*y2 + 30*_a2*u*w*x*y2 - 10*_a2*v*w*x*y2 + 16*_a*v2*w*x*y2 + 10*_a2*w2*x*y2 - 4*_a*u*w2*x*y2 - 4*_a*v*w2*x*y2 - 51*_a3*x2*y2 + 42*_a2*u*x2*y2 + 3*_a*u2*x2*y2 + 22*_a2*v*x2*y2 - 19*_a*u*v*x2*y2 + 3*_a*v2*x2*y2 + 32*_a2*w*x2*y2 - 15*_a*u*w*x2*y2 - 11*_a*v*w*x2*y2 - _a*w2*x2*y2 + 14*_a2*x3*y2 - 15*_a*u*x3*y2 - 7*_a*v*x3*y2 - 2*_a*w*x3*y2 + 4*_a*x4*y2 - 36*_a4*y3 + 36*_a3*u*y3 + 4*_a2*u2*y3 - 4*_a*u3*y3 + 27*_a3*v*y3 - 30*_a2*u*v*y3 + 3*_a*u2*v*y3 + 2*_a2*v2*y3 + 2*_a*u*v2*y3 - _a*v3*y3 + 9*_a3*w*y3 - 10*_a2*u*w*y3 + _a*u2*w*y3 + 2*_a2*v*w*y3 + 2*_a*u*v*w*y3 - 3*_a*v2*w*y3 + 45*_a3*x*y3 - 50*_a2*u*x*y3 + 5*_a*u2*x*y3 - 28*_a2*v*x*y3 + 20*_a*u*v*x*y3 - _a*v2*x*y3 - 10*_a2*w*x*y3 + 6*_a*u*w*x*y3 + 2*_a*v*w*x*y3 - 6*_a2*x2*y3 + 10*_a*u*x2*y3 + 5*_a*v*x2*y3 + _a*w*x2*y3 - 3*_a*x3*y3 - 9*_a3*y4 + 10*_a2*u*y4 - _a*u2*y4 + 4*_a2*v*y4 - 4*_a*u*v*y4 + _a*v2*y4 + 4*_a2*x*y4 - 4*_a*u*x*y4 - 2*_a*v*x*y4 + _a*x2*y4 + 126*_a6*z - 145*_a5*u*z - 12*_a4*u2*z + 27*_a3*u3*z + 4*_a2*u4*z - 100*_a5*v*z + 172*_a4*u*v*z - 42*_a3*u2*v*z - 18*_a2*u3*v*z - 72*_a4*v2*z + 3*_a3*u*v2*z + 34*_a2*u2*v2*z + 36*_a3*v3*z - 30*_a2*u*v3*z + 10*_a2*v4*z - 75*_a5*w*z + 28*_a4*u*w*z + 21*_a3*u2*w*z + 2*_a2*u3*w*z + 100*_a4*v*w*z - 54*_a3*u*v*w*z - 14*_a2*u2*v*w*z - 15*_a3*v2*w*z + 22*_a2*u*v2*w*z - 10*_a2*v3*w*z - 24*_a4*w2*z + 12*_a3*u*w2*z + 4*_a2*u2*w2*z + 12*_a3*v*w2*z - 8*_a2*u*v*w2*z + 4*_a2*v2*w2*z - 235*_a5*x*z + 256*_a4*u*x*z - 3*_a3*u2*x*z - 28*_a2*u3*x*z - 2*_a*u4*x*z + 244*_a4*v*x*z - 234*_a3*u*v*x*z + 22*_a2*u2*v*x*z + 6*_a*u3*v*x*z + 45*_a3*v2*x*z + 8*_a2*u*v2*x*z - 10*_a*u2*v2*x*z - 50*_a2*v3*x*z + 10*_a*u*v3*x*z - 4*_a*v4*x*z + 124*_a4*w*x*z - 84*_a3*u*w*x*z - 10*_a2*u2*w*x*z + 2*_a*u3*w*x*z - 156*_a3*v*w*x*z + 76*_a2*u*v*w*x*z + 2*_a*u2*v*w*x*z + 30*_a2*v2*w*x*z - 10*_a*u*v2*w*x*z + 6*_a*v3*w*x*z + 48*_a3*w2*x*z - 24*_a2*u*w2*x*z - 4*_a*u2*w2*x*z - 24*_a2*v*w2*x*z + 8*_a*u*v*w2*x*z - 4*_a*v2*w2*x*z + 72*_a4*x2*z - 102*_a3*u*x2*z + 22*_a2*u2*x2*z + 5*_a*u3*x2*z - 144*_a3*v*x2*z + 56*_a2*u*v*x2*z + 8*_a*u2*v*x2*z + 42*_a2*v2*x2*z + _a*u*v2*x2*z + 10*_a*v3*x2*z - 18*_a3*w*x2*z + 52*_a2*u*w*x2*z - 11*_a*u2*w*x2*z + 44*_a2*v*w*x2*z - 22*_a*u*v*w*x2*z - 15*_a*v2*w*x2*z - 24*_a2*w2*x2*z + 12*_a*u*w2*x2*z + 12*_a*v*w2*x2*z + 54*_a3*x3*z - 16*_a2*u*x3*z - 7*_a*u2*x3*z - 12*_a2*v*x3*z + 6*_a*u*v*x3*z - 15*_a*v2*x3*z - 36*_a2*w*x3*z + 4*_a*u*w*x3*z + 12*_a*v*w*x3*z - 14*_a2*x4*z + 7*_a*u*x4*z + 12*_a*v*x4*z + 5*_a*w*x4*z - 3*_a*x5*z - 165*_a5*y*z + 172*_a4*u*y*z + 27*_a3*u2*y*z - 30*_a2*u3*y*z - 4*_a*u4*y*z + 172*_a4*v*y*z - 204*_a3*u*v*y*z + 22*_a2*u2*v*y*z + 14*_a*u3*v*y*z + 27*_a3*v2*y*z + 22*_a2*u*v2*y*z - 20*_a*u2*v2*y*z - 30*_a2*v3*y*z + 14*_a*u*v3*y*z - 4*_a*v4*y*z + 72*_a4*w*y*z - 54*_a3*u*w*y*z - 4*_a2*u2*w*y*z + 2*_a*u3*w*y*z - 54*_a3*v*w*y*z + 40*_a2*u*v*w*y*z - 2*_a*u2*v*w*y*z - 4*_a2*v2*w*y*z - 2*_a*u*v2*w*y*z + 2*_a*v3*w*y*z + 18*_a3*w2*y*z - 8*_a2*u*w2*y*z - 2*_a*u2*w2*y*z - 8*_a2*v*w2*y*z + 4*_a*u*v*w2*y*z - 2*_a*v2*w2*y*z + 196*_a4*x*y*z - 234*_a3*u*x*y*z + 14*_a2*u2*x*y*z + 20*_a*u3*x*y*z - 234*_a3*v*x*y*z + 192*_a2*u*v*x*y*z - 12*_a*u2*v*x*y*z + 14*_a2*v2*x*y*z - 12*_a*u*v2*x*y*z + 20*_a*v3*x*y*z - 108*_a3*w*x*y*z + 76*_a2*u*w*x*y*z + 76*_a2*v*w*x*y*z - 32*_a*u*v*w*x*y*z - 20*_a2*w2*x*y*z + 8*_a*u*w2*x*y*z + 8*_a*v*w2*x*y*z - 12*_a3*x2*y*z + 56*_a2*u*x2*y*z - 19*_a*u2*x2*y*z + 56*_a2*v*x2*y*z - 32*_a*u*v*x2*y*z - 19*_a*v2*x2*y*z + 32*_a2*w*x2*y*z - 22*_a*u*w*x2*y*z - 22*_a*v*w*x2*y*z + 2*_a*w2*x2*y*z - 16*_a2*x3*y*z + 6*_a*u*x3*y*z + 6*_a*v*x3*y*z + 4*_a*w*x3*y*z - 3*_a*x4*y*z + 12*_a4*y2*z + 3*_a3*u*y2*z - 18*_a2*u2*y2*z + 3*_a*u3*y2*z - 42*_a3*v*y2*z + 22*_a2*u*v*y2*z + 8*_a*u2*v*y2*z + 20*_a2*v2*y2*z - 13*_a*u*v2*y2*z + 2*_a*v3*y2*z - 9*_a3*w*y2*z + 22*_a2*u*w*y2*z - 5*_a*u2*w*y2*z - 14*_a2*v*w*y2*z - 2*_a*u*v*w*y2*z + 7*_a*v2*w*y2*z + 3*_a3*x*y2*z + 8*_a2*u*x*y2*z + _a*u2*x*y2*z + 22*_a2*v*x*y2*z - 12*_a*u*v*x*y2*z - 13*_a*v2*x*y2*z + 10*_a2*w*x*y2*z - 10*_a*u*w*x*y2*z + 2*_a*v*w*x*y2*z - 18*_a2*x2*y2*z + _a*u*x2*y2*z + 8*_a*v*x2*y2*z - _a*w*x2*y2*z + 3*_a*x3*y2*z + 27*_a3*y3*z - 30*_a2*u*y3*z + 3*_a*u2*y3*z - 18*_a2*v*y3*z + 14*_a*u*v*y3*z - _a*v2*y3*z - 6*_a2*x*y3*z + 10*_a*u*x*y3*z + 6*_a*v*x*y3*z - 5*_a*x2*y3*z + 45*_a5*z2 - 12*_a4*u*z2 - 24*_a3*u2*z2 + 2*_a2*u3*z2 + _a*u4*z2 - 72*_a4*v*z2 + 27*_a3*u*v*z2 + 20*_a2*u2*v*z2 - _a*u3*v*z2 + 24*_a3*v2*z2 - 18*_a2*u*v2*z2 - 2*_a*u2*v2*z2 + 4*_a2*v3*z2 + 3*_a*u*v3*z2 - _a*v4*z2 + 12*_a4*w*z2 + 21*_a3*u*w*z2 - 14*_a2*u2*w*z2 - 3*_a*u3*w*z2 - 15*_a3*v*w*z2 - 4*_a2*u*v*w*z2 + 7*_a*u2*v*w*z2 + 2*_a2*v2*w*z2 - 5*_a*u*v2*w*z2 + _a*v3*w*z2 - 9*_a3*w2*z2 + 4*_a2*u*w2*z2 + _a*u2*w2*z2 + 4*_a2*v*w2*z2 - 2*_a*u*v*w2*z2 + _a*v2*w2*z2 - 12*_a4*x*z2 - 3*_a3*u*x*z2 + 10*_a2*u2*x*z2 - _a*u3*x*z2 + 45*_a3*v*x*z2 + 14*_a2*u*v*x*z2 - 13*_a*u2*v*x*z2 - 38*_a2*v2*x*z2 + _a*u*v2*x*z2 + 5*_a*v3*x*z2 - 42*_a3*w*x*z2 - 10*_a2*u*w*x*z2 + 16*_a*u2*w*x*z2 + 30*_a2*v*w*x*z2 + 10*_a2*w2*x*z2 - 4*_a*u*w2*x*z2 - 4*_a*v*w2*x*z2 - 51*_a3*x2*z2 + 22*_a2*u*x2*z2 + 3*_a*u2*x2*z2 + 42*_a2*v*x2*z2 - 19*_a*u*v*x2*z2 + 3*_a*v2*x2*z2 + 32*_a2*w*x2*z2 - 11*_a*u*w*x2*z2 - 15*_a*v*w*x2*z2 - _a*w2*x2*z2 + 14*_a2*x3*z2 - 7*_a*u*x3*z2 - 15*_a*v*x3*z2 - 2*_a*w*x3*z2 + 4*_a*x4*z2 + 12*_a4*y*z2 - 42*_a3*u*y*z2 + 20*_a2*u2*y*z2 + 2*_a*u3*y*z2 + 3*_a3*v*y*z2 + 22*_a2*u*v*y*z2 - 13*_a*u2*v*y*z2 - 18*_a2*v2*y*z2 + 8*_a*u*v2*y*z2 + 3*_a*v3*y*z2 - 9*_a3*w*y*z2 - 14*_a2*u*w*y*z2 + 7*_a*u2*w*y*z2 + 22*_a2*v*w*y*z2 - 2*_a*u*v*w*y*z2 - 5*_a*v2*w*y*z2 + 3*_a3*x*y*z2 + 22*_a2*u*x*y*z2 - 13*_a*u2*x*y*z2 + 8*_a2*v*x*y*z2 - 12*_a*u*v*x*y*z2 + _a*v2*x*y*z2 + 10*_a2*w*x*y*z2 + 2*_a*u*w*x*y*z2 - 10*_a*v*w*x*y*z2 - 18*_a2*x2*y*z2 + 8*_a*u*x2*y*z2 + _a*v*x2*y*z2 - _a*w*x2*y*z2 + 3*_a*x3*y*z2 - 36*_a3*y2*z2 + 34*_a2*u*y2*z2 - 2*_a*u2*y2*z2 + 34*_a2*v*y2*z2 - 20*_a*u*v*y2*z2 - 2*_a*v2*y2*z2 + 4*_a2*x*y2*z2 - 10*_a*u*x*y2*z2 - 10*_a*v*x*y2*z2 + 8*_a*x2*y2*z2 - 36*_a4*z3 + 27*_a3*u*z3 + 2*_a2*u2*z3 - _a*u3*z3 + 36*_a3*v*z3 - 30*_a2*u*v*z3 + 2*_a*u2*v*z3 + 4*_a2*v2*z3 + 3*_a*u*v2*z3 - 4*_a*v3*z3 + 9*_a3*w*z3 + 2*_a2*u*w*z3 - 3*_a*u2*w*z3 - 10*_a2*v*w*z3 + 2*_a*u*v*w*z3 + _a*v2*w*z3 + 45*_a3*x*z3 - 28*_a2*u*x*z3 - _a*u2*x*z3 - 50*_a2*v*x*z3 + 20*_a*u*v*x*z3 + 5*_a*v2*x*z3 - 10*_a2*w*x*z3 + 2*_a*u*w*x*z3 + 6*_a*v*w*x*z3 - 6*_a2*x2*z3 + 5*_a*u*x2*z3 + 10*_a*v*x2*z3 + _a*w*x2*z3 - 3*_a*x3*z3 + 27*_a3*y*z3 - 18*_a2*u*y*z3 - _a*u2*y*z3 - 30*_a2*v*y*z3 + 14*_a*u*v*y*z3 + 3*_a*v2*y*z3 - 6*_a2*x*y*z3 + 6*_a*u*x*y*z3 + 10*_a*v*x*y*z3 - 5*_a*x2*y*z3 - 9*_a3*z4 + 4*_a2*u*z4 + _a*u2*z4 + 10*_a2*v*z4 - 4*_a*u*v*z4 - _a*v2*z4 + 4*_a2*x*z4 - 2*_a*u*x*z4 - 4*_a*v*x*z4 + _a*x2*z4;
      *(result+7) = 18*_a7 - 21*_a6*u - 9*_a5*u2 + 9*_a4*u3 + 3*_a3*u4 - 21*_a6*v + 33*_a5*u*v - 3*_a4*u2*v - 9*_a3*u3*v - 9*_a5*v2 - 3*_a4*u*v2 + 12*_a3*u2*v2 + 9*_a4*v3 - 9*_a3*u*v3 + 3*_a3*v4 - 9*_a6*w + 15*_a5*u*w - 3*_a4*u2*w - 3*_a3*u3*w + 15*_a5*v*w - 18*_a4*u*v*w + 3*_a3*u2*v*w - 3*_a4*v2*w + 3*_a3*u*v2*w - 3*_a3*v3*w - 9*_a5*w2 + 6*_a4*u*w2 + 3*_a3*u2*w2 + 6*_a4*v*w2 - 6*_a3*u*v*w2 + 3*_a3*v2*w2 - 33*_a6*x + 47*_a5*u*x + 3*_a4*u2*x - 15*_a3*u3*x - 2*_a2*u4*x + 47*_a5*v*x - 49*_a4*u*v*x - _a3*u2*v*x + 3*_a2*u3*v*x + 3*_a4*v2*x - _a3*u*v2*x - 2*_a2*u2*v2*x - 15*_a3*v3*x + 3*_a2*u*v3*x - 2*_a2*v4*x + 12*_a5*w*x - 31*_a4*u*w*x + 14*_a3*u2*w*x + 5*_a2*u3*w*x - 31*_a4*v*w*x + 36*_a3*u*v*w*x - 5*_a2*u2*v*w*x + 14*_a3*v2*w*x - 5*_a2*u*v2*w*x + 5*_a2*v3*w*x + 21*_a4*w2*x - 16*_a3*u*w2*x - 5*_a2*u2*w2*x - 16*_a3*v*w2*x + 10*_a2*u*v*w2*x - 5*_a2*v2*w2*x - _a5*x2 - 18*_a4*u*x2 + 17*_a3*u2*x2 + 3*_a2*u3*x2 - _a*u4*x2 - 18*_a4*v*x2 + 4*_a3*u*v*x2 + 9*_a2*u2*v*x2 + 5*_a*u3*v*x2 + 17*_a3*v2*x2 + 9*_a2*u*v2*x2 - 8*_a*u2*v2*x2 + 3*_a2*v3*x2 + 5*_a*u*v3*x2 - _a*v4*x2 + 11*_a4*w*x2 + 6*_a3*u*w*x2 - 16*_a2*u2*w*x2 - _a*u3*w*x2 + 6*_a3*v*w*x2 - 16*_a2*u*v*w*x2 + _a*u2*v*w*x2 - 16*_a2*v2*w*x2 + _a*u*v2*w*x2 - _a*v3*w*x2 - 10*_a3*w2*x2 + 12*_a2*u*w2*x2 + _a*u2*w2*x2 + 12*_a2*v*w2*x2 - 2*_a*u*v*w2*x2 + _a*v2*w2*x2 + 22*_a4*x3 - 18*_a3*u*x3 - 7*_a2*u2*x3 + 3*_a*u3*x3 - 18*_a3*v*x3 + 8*_a2*u*v*x3 - 3*_a*u2*v*x3 + u3*v*x3 - 7*_a2*v2*x3 - 3*_a*u*v2*x3 - 2*u2*v2*x3 + 3*_a*v3*x3 + u*v3*x3 - 16*_a3*w*x3 + 18*_a2*u*w*x3 + 2*_a*u2*w*x3 - u3*w*x3 + 18*_a2*v*w*x3 - 4*_a*u*v*w*x3 + u2*v*w*x3 + 2*_a*v2*w*x3 + u*v2*w*x3 - v3*w*x3 - 6*_a2*w2*x3 + u2*w2*x3 - 2*u*v*w2*x3 + v2*w2*x3 + 7*_a2*u*x4 - 4*_a*u2*x4 + 7*_a2*v*x4 + 3*_a*u*v*x4 - 2*u2*v*x4 - 4*_a*v2*x4 - 2*u*v2*x4 - 3*_a2*w*x4 - 5*_a*u*w*x4 + 3*u2*w*x4 - 5*_a*v*w*x4 + 2*u*v*w*x4 + 3*v2*w*x4 + 3*_a*w2*x4 - 2*u*w2*x4 - 2*v*w2*x4 - 5*_a2*x5 + 3*_a*u*x5 + 3*_a*v*x5 + u*v*x5 + 4*_a*w*x5 - 3*u*w*x5 - 3*v*w*x5 + w2*x5 - _a*x6 + w*x6 - 21*_a6*y + 20*_a5*u*y + 18*_a4*u2*y - 12*_a3*u3*y - 5*_a2*u4*y + 29*_a5*v*y - 43*_a4*u*v*y - _a3*u2*v*y + 15*_a2*u3*v*y + 3*_a4*v2*y + 14*_a3*u*v2*y - 17*_a2*u2*v2*y - 9*_a3*v3*y + 9*_a2*u*v3*y - 2*_a2*v4*y + 15*_a5*w*y - 25*_a4*u*w*y + 5*_a3*u2*w*y + 5*_a2*u3*w*y - 7*_a4*v*w*y + 18*_a3*u*v*w*y - 11*_a2*u2*v*w*y - 7*_a3*v2*w*y + 7*_a2*u*v2*w*y - _a2*v3*w*y + 6*_a4*w2*y - 4*_a3*u*w2*y - 2*_a2*u2*w2*y - 4*_a3*v*w2*y + 4*_a2*u*v*w2*y - 2*_a2*v2*w2*y + 47*_a5*x*y - 61*_a4*u*x*y - 15*_a3*u2*x*y + 25*_a2*u3*x*y + 4*_a*u4*x*y - 64*_a4*v*x*y + 78*_a3*u*v*x*y - 4*_a2*u2*v*x*y - 10*_a*u3*v*x*y + _a3*v2*x*y - 11*_a2*u*v2*x*y + 10*_a*u2*v2*x*y + 14*_a2*v3*x*y - 6*_a*u*v3*x*y + 2*_a*v4*x*y - 31*_a4*w*x*y + 52*_a3*u*w*x*y - 15*_a2*u2*w*x*y - 6*_a*u3*w*x*y + 28*_a3*v*w*x*y - 38*_a2*u*v*w*x*y + 10*_a*u2*v*w*x*y + 5*_a2*v2*w*x*y - 2*_a*u*v2*w*x*y - 2*_a*v3*w*x*y - 16*_a3*w2*x*y + 12*_a2*u*w2*x*y + 4*_a*u2*w2*x*y + 12*_a2*v*w2*x*y - 8*_a*u*v*w2*x*y + 4*_a*v2*w2*x*y - 18*_a4*x2*y + 48*_a3*u*x2*y - 21*_a2*u2*x2*y - 10*_a*u3*x2*y + u4*x2*y + 34*_a3*v*x2*y - 28*_a2*u*v*x2*y - _a*u2*v*x2*y - 5*u3*v*x2*y - 11*_a2*v2*x2*y - 8*_a*u*v2*x2*y + 7*u2*v2*x2*y - 5*_a*v3*x2*y - 3*u*v3*x2*y + 6*_a3*w*x2*y - 22*_a2*u*w*x2*y + 15*_a*u2*w*x2*y + u3*w*x2*y - 26*_a2*v*w*x2*y + 22*_a*u*v*w*x2*y + u2*v*w*x2*y + 11*_a*v2*w*x2*y - 5*u*v2*w*x2*y + 3*v3*w*x2*y + 12*_a2*w2*x2*y - 12*_a*u*w2*x2*y - 2*u2*w2*x2*y - 12*_a*v*w2*x2*y + 4*u*v*w2*x2*y - 2*v2*w2*x2*y - 18*_a3*x3*y + 6*_a2*u*x3*y + 15*_a*u2*x3*y - 3*u3*x3*y + 8*_a2*v*x3*y - 6*_a*u*v*x3*y + 6*u2*v*x3*y + 7*_a*v2*x3*y + 5*u*v2*x3*y + 18*_a2*w*x3*y - 12*_a*u*w*x3*y - 5*u2*w*x3*y - 4*_a*v*w*x3*y - 2*u*v*w*x3*y - 9*v2*w*x3*y + 4*u*w2*x3*y + 4*v*w2*x3*y + 7*_a2*x4*y - 12*_a*u*x4*y + 3*u2*x4*y - 7*_a*v*x4*y - u*v*x4*y - 5*_a*w*x4*y + 7*u*w*x4*y + 9*v*w*x4*y - 2*w2*x4*y + 3*_a*x5*y - u*x5*y - 3*w*x5*y - 9*_a5*y2 + 18*_a4*u*y2 - 8*_a3*u2*y2 - 2*_a2*u3*y2 + _a*u4*y2 + 3*_a4*v*y2 - 9*_a3*u*v*y2 + 9*_a2*u2*v*y2 - 3*_a*u3*v*y2 + 8*_a3*v2*y2 - 10*_a2*u*v2*y2 + 2*_a*u2*v2*y2 - _a2*v3*y2 + _a*u*v3*y2 - _a*v4*y2 - 3*_a4*w*y2 + 5*_a3*u*w*y2 - _a2*u2*w*y2 - _a*u3*w*y2 - 7*_a3*v*w*y2 + 2*_a2*u*v*w*y2 + 5*_a*u2*v*w*y2 + 7*_a2*v2*w*y2 - 7*_a*u*v2*w*y2 + 3*_a*v3*w*y2 + 3*_a3*w2*y2 - 2*_a2*u*w2*y2 - _a*u2*w2*y2 - 2*_a2*v*w2*y2 + 2*_a*u*v*w2*y2 - _a*v2*w2*y2 + 3*_a4*x*y2 - 15*_a3*u*x*y2 + 19*_a2*u2*x*y2 - 5*_a*u3*x*y2 - 2*u4*x*y2 + _a3*v*x*y2 - 7*_a2*u*v*x*y2 - _a*u2*v*x*y2 + 7*u3*v*x*y2 - 5*_a2*v2*x*y2 + 13*_a*u*v2*x*y2 - 8*u2*v2*x*y2 + _a*v3*x*y2 + 3*u*v3*x*y2 + 14*_a3*w*x*y2 - 15*_a2*u*w*x*y2 + u3*w*x*y2 + 5*_a2*v*w*x*y2 - 5*u2*v*w*x*y2 - 16*_a*v2*w*x*y2 + 7*u*v2*w*x*y2 - 3*v3*w*x*y2 - 5*_a2*w2*x*y2 + 4*_a*u*w2*x*y2 + u2*w2*x*y2 + 4*_a*v*w2*x*y2 - 2*u*v*w2*x*y2 + v2*w2*x*y2 + 17*_a3*x2*y2 - 21*_a2*u*x2*y2 - 3*_a*u2*x2*y2 + 7*u3*x2*y2 - 11*_a2*v*x2*y2 + 19*_a*u*v*x2*y2 - 8*u2*v*x2*y2 - 3*_a*v2*x2*y2 - 3*u*v2*x2*y2 - 16*_a2*w*x2*y2 + 15*_a*u*w*x2*y2 + u2*w*x2*y2 + 11*_a*v*w*x2*y2 - 2*u*v*w*x2*y2 + 9*v2*w*x2*y2 + _a*w2*x2*y2 - 2*u*w2*x2*y2 - 2*v*w2*x2*y2 - 7*_a2*x3*y2 + 15*_a*u*x3*y2 - 8*u2*x3*y2 + 7*_a*v*x3*y2 - 3*u*v*x3*y2 + 2*_a*w*x3*y2 - 5*u*w*x3*y2 - 9*v*w*x3*y2 + w2*x3*y2 - 4*_a*x4*y2 + 3*u*x4*y2 + 3*w*x4*y2 + 9*_a4*y3 - 12*_a3*u*y3 - 2*_a2*u2*y3 + 4*_a*u3*y3 + u4*y3 - 9*_a3*v*y3 + 15*_a2*u*v*y3 - 3*_a*u2*v*y3 - 3*u3*v*y3 - _a2*v2*y3 - 2*_a*u*v2*y3 + 3*u2*v2*y3 + _a*v3*y3 - u*v3*y3 - 3*_a3*w*y3 + 5*_a2*u*w*y3 - _a*u2*w*y3 - u3*w*y3 - _a2*v*w*y3 - 2*_a*u*v*w*y3 + 3*u2*v*w*y3 + 3*_a*v2*w*y3 - 3*u*v2*w*y3 + v3*w*y3 - 15*_a3*x*y3 + 25*_a2*u*x*y3 - 5*_a*u2*x*y3 - 5*u3*x*y3 + 14*_a2*v*x*y3 - 20*_a*u*v*x*y3 + 6*u2*v*x*y3 + _a*v2*x*y3 - u*v2*x*y3 + 5*_a2*w*x*y3 - 6*_a*u*w*x*y3 + u2*w*x*y3 - 2*_a*v*w*x*y3 + 2*u*v*w*x*y3 - 3*v2*w*x*y3 + 3*_a2*x2*y3 - 10*_a*u*x2*y3 + 7*u2*x2*y3 - 5*_a*v*x2*y3 + 5*u*v*x2*y3 - _a*w*x2*y3 + u*w*x2*y3 + 3*v*w*x2*y3 + 3*_a*x3*y3 - 3*u*x3*y3 - w*x3*y3 + 3*_a3*y4 - 5*_a2*u*y4 + _a*u2*y4 + u3*y4 - 2*_a2*v*y4 + 4*_a*u*v*y4 - 2*u2*v*y4 - _a*v2*y4 + u*v2*y4 - 2*_a2*x*y4 + 4*_a*u*x*y4 - 2*u2*x*y4 + 2*_a*v*x*y4 - 2*u*v*x*y4 - _a*x2*y4 + u*x2*y4 - 21*_a6*z + 29*_a5*u*z + 3*_a4*u2*z - 9*_a3*u3*z - 2*_a2*u4*z + 20*_a5*v*z - 43*_a4*u*v*z + 14*_a3*u2*v*z + 9*_a2*u3*v*z + 18*_a4*v2*z - _a3*u*v2*z - 17*_a2*u2*v2*z - 12*_a3*v3*z + 15*_a2*u*v3*z - 5*_a2*v4*z + 15*_a5*w*z - 7*_a4*u*w*z - 7*_a3*u2*w*z - _a2*u3*w*z - 25*_a4*v*w*z + 18*_a3*u*v*w*z + 7*_a2*u2*v*w*z + 5*_a3*v2*w*z - 11*_a2*u*v2*w*z + 5*_a2*v3*w*z + 6*_a4*w2*z - 4*_a3*u*w2*z - 2*_a2*u2*w2*z - 4*_a3*v*w2*z + 4*_a2*u*v*w2*z - 2*_a2*v2*w2*z + 47*_a5*x*z - 64*_a4*u*x*z + _a3*u2*x*z + 14*_a2*u3*x*z + 2*_a*u4*x*z - 61*_a4*v*x*z + 78*_a3*u*v*x*z - 11*_a2*u2*v*x*z - 6*_a*u3*v*x*z - 15*_a3*v2*x*z - 4*_a2*u*v2*x*z + 10*_a*u2*v2*x*z + 25*_a2*v3*x*z - 10*_a*u*v3*x*z + 4*_a*v4*x*z - 31*_a4*w*x*z + 28*_a3*u*w*x*z + 5*_a2*u2*w*x*z - 2*_a*u3*w*x*z + 52*_a3*v*w*x*z - 38*_a2*u*v*w*x*z - 2*_a*u2*v*w*x*z - 15*_a2*v2*w*x*z + 10*_a*u*v2*w*x*z - 6*_a*v3*w*x*z - 16*_a3*w2*x*z + 12*_a2*u*w2*x*z + 4*_a*u2*w2*x*z + 12*_a2*v*w2*x*z - 8*_a*u*v*w2*x*z + 4*_a*v2*w2*x*z - 18*_a4*x2*z + 34*_a3*u*x2*z - 11*_a2*u2*x2*z - 5*_a*u3*x2*z + 48*_a3*v*x2*z - 28*_a2*u*v*x2*z - 8*_a*u2*v*x2*z - 3*u3*v*x2*z - 21*_a2*v2*x2*z - _a*u*v2*x2*z + 7*u2*v2*x2*z - 10*_a*v3*x2*z - 5*u*v3*x2*z + v4*x2*z + 6*_a3*w*x2*z - 26*_a2*u*w*x2*z + 11*_a*u2*w*x2*z + 3*u3*w*x2*z - 22*_a2*v*w*x2*z + 22*_a*u*v*w*x2*z - 5*u2*v*w*x2*z + 15*_a*v2*w*x2*z + u*v2*w*x2*z + v3*w*x2*z + 12*_a2*w2*x2*z - 12*_a*u*w2*x2*z - 2*u2*w2*x2*z - 12*_a*v*w2*x2*z + 4*u*v*w2*x2*z - 2*v2*w2*x2*z - 18*_a3*x3*z + 8*_a2*u*x3*z + 7*_a*u2*x3*z + 6*_a2*v*x3*z - 6*_a*u*v*x3*z + 5*u2*v*x3*z + 15*_a*v2*x3*z + 6*u*v2*x3*z - 3*v3*x3*z + 18*_a2*w*x3*z - 4*_a*u*w*x3*z - 9*u2*w*x3*z - 12*_a*v*w*x3*z - 2*u*v*w*x3*z - 5*v2*w*x3*z + 4*u*w2*x3*z + 4*v*w2*x3*z + 7*_a2*x4*z - 7*_a*u*x4*z - 12*_a*v*x4*z - u*v*x4*z + 3*v2*x4*z - 5*_a*w*x4*z + 9*u*w*x4*z + 7*v*w*x4*z - 2*w2*x4*z + 3*_a*x5*z - v*x5*z - 3*w*x5*z + 33*_a5*y*z - 43*_a4*u*y*z - 9*_a3*u2*y*z + 15*_a2*u3*y*z + 4*_a*u4*y*z - 43*_a4*v*y*z + 68*_a3*u*v*y*z - 11*_a2*u2*v*y*z - 14*_a*u3*v*y*z - 9*_a3*v2*y*z - 11*_a2*u*v2*y*z + 20*_a*u2*v2*y*z + 15*_a2*v3*y*z - 14*_a*u*v3*y*z + 4*_a*v4*y*z - 18*_a4*w*y*z + 18*_a3*u*w*y*z + 2*_a2*u2*w*y*z - 2*_a*u3*w*y*z + 18*_a3*v*w*y*z - 20*_a2*u*v*w*y*z + 2*_a*u2*v*w*y*z + 2*_a2*v2*w*y*z + 2*_a*u*v2*w*y*z - 2*_a*v3*w*y*z - 6*_a3*w2*y*z + 4*_a2*u*w2*y*z + 2*_a*u2*w2*y*z + 4*_a2*v*w2*y*z - 4*_a*u*v*w2*y*z + 2*_a*v2*w2*y*z - 49*_a4*x*y*z + 78*_a3*u*x*y*z - 7*_a2*u2*x*y*z - 20*_a*u3*x*y*z - 2*u4*x*y*z + 78*_a3*v*x*y*z - 96*_a2*u*v*x*y*z + 12*_a*u2*v*x*y*z + 6*u3*v*x*y*z - 7*_a2*v2*x*y*z + 12*_a*u*v2*x*y*z - 8*u2*v2*x*y*z - 20*_a*v3*x*y*z + 6*u*v3*x*y*z - 2*v4*x*y*z + 36*_a3*w*x*y*z - 38*_a2*u*w*x*y*z + 2*u3*w*x*y*z - 38*_a2*v*w*x*y*z + 32*_a*u*v*w*x*y*z - 2*u2*v*w*x*y*z - 2*u*v2*w*x*y*z + 2*v3*w*x*y*z + 10*_a2*w2*x*y*z - 8*_a*u*w2*x*y*z - 2*u2*w2*x*y*z - 8*_a*v*w2*x*y*z + 4*u*v*w2*x*y*z - 2*v2*w2*x*y*z + 4*_a3*x2*y*z - 28*_a2*u*x2*y*z + 19*_a*u2*x2*y*z + 5*u3*x2*y*z - 28*_a2*v*x2*y*z + 32*_a*u*v*x2*y*z - u2*v*x2*y*z + 19*_a*v2*x2*y*z - u*v2*x2*y*z + 5*v3*x2*y*z - 16*_a2*w*x2*y*z + 22*_a*u*w*x2*y*z - 2*u2*w*x2*y*z + 22*_a*v*w*x2*y*z - 12*u*v*w*x2*y*z - 2*v2*w*x2*y*z - 2*_a*w2*x2*y*z + 4*u*w2*x2*y*z + 4*v*w2*x2*y*z + 8*_a2*x3*y*z - 6*_a*u*x3*y*z - 3*u2*x3*y*z - 6*_a*v*x3*y*z - 4*u*v*x3*y*z - 3*v2*x3*y*z - 4*_a*w*x3*y*z - 2*u*w*x3*y*z - 2*v*w*x3*y*z - 2*w2*x3*y*z + 3*_a*x4*y*z - u*x4*y*z - v*x4*y*z + 2*w*x4*y*z + x5*y*z - 3*_a4*y2*z - _a3*u*y2*z + 9*_a2*u2*y2*z - 3*_a*u3*y2*z - 2*u4*y2*z + 14*_a3*v*y2*z - 11*_a2*u*v*y2*z - 8*_a*u2*v*y2*z + 5*u3*v*y2*z - 10*_a2*v2*y2*z + 13*_a*u*v2*y2*z - 3*u2*v2*y2*z - 2*_a*v3*y2*z - u*v3*y2*z + v4*y2*z + 3*_a3*w*y2*z - 11*_a2*u*w*y2*z + 5*_a*u2*w*y2*z + 3*u3*w*y2*z + 7*_a2*v*w*y2*z + 2*_a*u*v*w*y2*z - 9*u2*v*w*y2*z - 7*_a*v2*w*y2*z + 9*u*v2*w*y2*z - 3*v3*w*y2*z - _a3*x*y2*z - 4*_a2*u*x*y2*z - _a*u2*x*y2*z + 6*u3*x*y2*z - 11*_a2*v*x*y2*z + 12*_a*u*v*x*y2*z - u2*v*x*y2*z + 13*_a*v2*x*y2*z - 4*u*v2*x*y2*z - v3*x*y2*z - 5*_a2*w*x*y2*z + 10*_a*u*w*x*y2*z - 5*u2*w*x*y2*z - 2*_a*v*w*x*y2*z - 2*u*v*w*x*y2*z + 7*v2*w*x*y2*z + 9*_a2*x2*y2*z - _a*u*x2*y2*z - 8*u2*x2*y2*z - 8*_a*v*x2*y2*z - u*v*x2*y2*z - 3*v2*x2*y2*z + _a*w*x2*y2*z + u*w*x2*y2*z - 5*v*w*x2*y2*z - 3*_a*x3*y2*z + 6*u*x3*y2*z + 5*v*x3*y2*z + w*x3*y2*z - 2*x4*y2*z - 9*_a3*y3*z + 15*_a2*u*y3*z - 3*_a*u2*y3*z - 3*u3*y3*z + 9*_a2*v*y3*z - 14*_a*u*v*y3*z + 5*u2*v*y3*z + _a*v2*y3*z - u*v2*y3*z - v3*y3*z + 3*_a2*x*y3*z - 10*_a*u*x*y3*z + 7*u2*x*y3*z - 6*_a*v*x*y3*z + 6*u*v*x*y3*z + 3*v2*x*y3*z + 5*_a*x2*y3*z - 5*u*x2*y3*z - 3*v*x2*y3*z + x3*y3*z - 9*_a5*z2 + 3*_a4*u*z2 + 8*_a3*u2*z2 - _a2*u3*z2 - _a*u4*z2 + 18*_a4*v*z2 - 9*_a3*u*v*z2 - 10*_a2*u2*v*z2 + _a*u3*v*z2 - 8*_a3*v2*z2 + 9*_a2*u*v2*z2 + 2*_a*u2*v2*z2 - 2*_a2*v3*z2 - 3*_a*u*v3*z2 + _a*v4*z2 - 3*_a4*w*z2 - 7*_a3*u*w*z2 + 7*_a2*u2*w*z2 + 3*_a*u3*w*z2 + 5*_a3*v*w*z2 + 2*_a2*u*v*w*z2 - 7*_a*u2*v*w*z2 - _a2*v2*w*z2 + 5*_a*u*v2*w*z2 - _a*v3*w*z2 + 3*_a3*w2*z2 - 2*_a2*u*w2*z2 - _a*u2*w2*z2 - 2*_a2*v*w2*z2 + 2*_a*u*v*w2*z2 - _a*v2*w2*z2 + 3*_a4*x*z2 + _a3*u*x*z2 - 5*_a2*u2*x*z2 + _a*u3*x*z2 - 15*_a3*v*x*z2 - 7*_a2*u*v*x*z2 + 13*_a*u2*v*x*z2 + 3*u3*v*x*z2 + 19*_a2*v2*x*z2 - _a*u*v2*x*z2 - 8*u2*v2*x*z2 - 5*_a*v3*x*z2 + 7*u*v3*x*z2 - 2*v4*x*z2 + 14*_a3*w*x*z2 + 5*_a2*u*w*x*z2 - 16*_a*u2*w*x*z2 - 3*u3*w*x*z2 - 15*_a2*v*w*x*z2 + 7*u2*v*w*x*z2 - 5*u*v2*w*x*z2 + v3*w*x*z2 - 5*_a2*w2*x*z2 + 4*_a*u*w2*x*z2 + u2*w2*x*z2 + 4*_a*v*w2*x*z2 - 2*u*v*w2*x*z2 + v2*w2*x*z2 + 17*_a3*x2*z2 - 11*_a2*u*x2*z2 - 3*_a*u2*x2*z2 - 21*_a2*v*x2*z2 + 19*_a*u*v*x2*z2 - 3*u2*v*x2*z2 - 3*_a*v2*x2*z2 - 8*u*v2*x2*z2 + 7*v3*x2*z2 - 16*_a2*w*x2*z2 + 11*_a*u*w*x2*z2 + 9*u2*w*x2*z2 + 15*_a*v*w*x2*z2 - 2*u*v*w*x2*z2 + v2*w*x2*z2 + _a*w2*x2*z2 - 2*u*w2*x2*z2 - 2*v*w2*x2*z2 - 7*_a2*x3*z2 + 7*_a*u*x3*z2 + 15*_a*v*x3*z2 - 3*u*v*x3*z2 - 8*v2*x3*z2 + 2*_a*w*x3*z2 - 9*u*w*x3*z2 - 5*v*w*x3*z2 + w2*x3*z2 - 4*_a*x4*z2 + 3*v*x4*z2 + 3*w*x4*z2 - 3*_a4*y*z2 + 14*_a3*u*y*z2 - 10*_a2*u2*y*z2 - 2*_a*u3*y*z2 + u4*y*z2 - _a3*v*y*z2 - 11*_a2*u*v*y*z2 + 13*_a*u2*v*y*z2 - u3*v*y*z2 + 9*_a2*v2*y*z2 - 8*_a*u*v2*y*z2 - 3*u2*v2*y*z2 - 3*_a*v3*y*z2 + 5*u*v3*y*z2 - 2*v4*y*z2 + 3*_a3*w*y*z2 + 7*_a2*u*w*y*z2 - 7*_a*u2*w*y*z2 - 3*u3*w*y*z2 - 11*_a2*v*w*y*z2 + 2*_a*u*v*w*y*z2 + 9*u2*v*w*y*z2 + 5*_a*v2*w*y*z2 - 9*u*v2*w*y*z2 + 3*v3*w*y*z2 - _a3*x*y*z2 - 11*_a2*u*x*y*z2 + 13*_a*u2*x*y*z2 - u3*x*y*z2 - 4*_a2*v*x*y*z2 + 12*_a*u*v*x*y*z2 - 4*u2*v*x*y*z2 - _a*v2*x*y*z2 - u*v2*x*y*z2 + 6*v3*x*y*z2 - 5*_a2*w*x*y*z2 - 2*_a*u*w*x*y*z2 + 7*u2*w*x*y*z2 + 10*_a*v*w*x*y*z2 - 2*u*v*w*x*y*z2 - 5*v2*w*x*y*z2 + 9*_a2*x2*y*z2 - 8*_a*u*x2*y*z2 - 3*u2*x2*y*z2 - _a*v*x2*y*z2 - u*v*x2*y*z2 - 8*v2*x2*y*z2 + _a*w*x2*y*z2 - 5*u*w*x2*y*z2 + v*w*x2*y*z2 - 3*_a*x3*y*z2 + 5*u*x3*y*z2 + 6*v*x3*y*z2 + w*x3*y*z2 - 2*x4*y*z2 + 12*_a3*y2*z2 - 17*_a2*u*y2*z2 + 2*_a*u2*y2*z2 + 3*u3*y2*z2 - 17*_a2*v*y2*z2 + 20*_a*u*v*y2*z2 - 3*u2*v*y2*z2 + 2*_a*v2*y2*z2 - 3*u*v2*y2*z2 + 3*v3*y2*z2 - 2*_a2*x*y2*z2 + 10*_a*u*x*y2*z2 - 8*u2*x*y2*z2 + 10*_a*v*x*y2*z2 - 8*u*v*x*y2*z2 - 8*v2*x*y2*z2 - 8*_a*x2*y2*z2 + 7*u*x2*y2*z2 + 7*v*x2*y2*z2 - 2*x3*y2*z2 + 9*_a4*z3 - 9*_a3*u*z3 - _a2*u2*z3 + _a*u3*z3 - 12*_a3*v*z3 + 15*_a2*u*v*z3 - 2*_a*u2*v*z3 - u3*v*z3 - 2*_a2*v2*z3 - 3*_a*u*v2*z3 + 3*u2*v2*z3 + 4*_a*v3*z3 - 3*u*v3*z3 + v4*z3 - 3*_a3*w*z3 - _a2*u*w*z3 + 3*_a*u2*w*z3 + u3*w*z3 + 5*_a2*v*w*z3 - 2*_a*u*v*w*z3 - 3*u2*v*w*z3 - _a*v2*w*z3 + 3*u*v2*w*z3 - v3*w*z3 - 15*_a3*x*z3 + 14*_a2*u*x*z3 + _a*u2*x*z3 + 25*_a2*v*x*z3 - 20*_a*u*v*x*z3 - u2*v*x*z3 - 5*_a*v2*x*z3 + 6*u*v2*x*z3 - 5*v3*x*z3 + 5*_a2*w*x*z3 - 2*_a*u*w*x*z3 - 3*u2*w*x*z3 - 6*_a*v*w*x*z3 + 2*u*v*w*x*z3 + v2*w*x*z3 + 3*_a2*x2*z3 - 5*_a*u*x2*z3 - 10*_a*v*x2*z3 + 5*u*v*x2*z3 + 7*v2*x2*z3 - _a*w*x2*z3 + 3*u*w*x2*z3 + v*w*x2*z3 + 3*_a*x3*z3 - 3*v*x3*z3 - w*x3*z3 - 9*_a3*y*z3 + 9*_a2*u*y*z3 + _a*u2*y*z3 - u3*y*z3 + 15*_a2*v*y*z3 - 14*_a*u*v*y*z3 - u2*v*y*z3 - 3*_a*v2*y*z3 + 5*u*v2*y*z3 - 3*v3*y*z3 + 3*_a2*x*y*z3 - 6*_a*u*x*y*z3 + 3*u2*x*y*z3 - 10*_a*v*x*y*z3 + 6*u*v*x*y*z3 + 7*v2*x*y*z3 + 5*_a*x2*y*z3 - 3*u*x2*y*z3 - 5*v*x2*y*z3 + x3*y*z3 + 3*_a3*z4 - 2*_a2*u*z4 - _a*u2*z4 - 5*_a2*v*z4 + 4*_a*u*v*z4 + u2*v*z4 + _a*v2*z4 - 2*u*v2*z4 + v3*z4 - 2*_a2*x*z4 + 2*_a*u*x*z4 + 4*_a*v*x*z4 - 2*u*v*x*z4 - 2*v2*x*z4 - _a*x2*z4 + v*x2*z4;
    }

  return;
}

/* **************************************************************** */
/* **************************************************************** */

void TVIL_cHGnum (TVIL_REAL u,
		  TVIL_REAL v,
		  TVIL_REAL w,
		  TVIL_REAL x,
		  TVIL_REAL y,
		  TVIL_REAL z,
		  TVIL_REAL *result)
{
  TVIL_REAL  u2 = u*u;
  TVIL_REAL  u3 = u2*u;
  TVIL_REAL  u4 = u2*u2;

  TVIL_REAL  v2 = v*v;
  TVIL_REAL  v3 = v2*v;
  TVIL_REAL  v4 = v2*v2;

  TVIL_REAL  w2 = w*w;
  TVIL_REAL  w3 = w2*w;

  TVIL_REAL  x2 = x*x;
  TVIL_REAL  x3 = x2*x;
  TVIL_REAL  x4 = x2*x2;
  TVIL_REAL  x5 = x2*x3;

  TVIL_REAL  y2 = y*y;
  TVIL_REAL  y3 = y2*y;

  TVIL_REAL  z2 = z*z;
  TVIL_REAL  z3 = z2*z;

  if (SAME6(u,v,w,x,y,z))
    {
      *(result) = 0;
      *(result+1) = 0;
      *(result+2) = 0;
      *(result+3) = 0;
      *(result+4) = 0;
    }
  else if (SAME5(u,v,w,x,y))
    {
      *(result) = -(_a*u) + _a*z;
      *(result+1) = 0;
      *(result+2) = 0;
      *(result+3) = 0;
      *(result+4) = 0;
    }
  else if (SAME5(u,v,w,x,z))
    {
      *(result) = -(_a*u) + _a*y;
      *(result+1) = 0;
      *(result+2) = 0;
      *(result+3) = 0;
      *(result+4) = 0;
    }
  else if (SAME5(u,w,x,y,z))
    {
      *(result) = -(_a*u) + _a*v;
      *(result+1) = 0;
      *(result+2) = 0;
      *(result+3) = 0;
      *(result+4) = 0;
    }
  else if (SAME5(v,w,x,y,z))
    {
      *(result) = _a*u - _a*v;
      *(result+1) = 0;
      *(result+2) = 0;
      *(result+3) = 0;
      *(result+4) = 0;
    }
  else if (SAME4(u,w,x,y) && SAME2(v,z))
    {
      *(result) = -(_a*u) + _a*v;
      *(result+1) = 0;
      *(result+2) = 0;
      *(result+3) = 0;
      *(result+4) = 0;
    }
  else if (SAME4(v,w,x,z) && SAME2(u,y))
    {
      *(result) = _a*u - _a*v;
      *(result+1) = 0;
      *(result+2) = 0;
      *(result+3) = 0;
      *(result+4) = 0;
    }
  else if (SAME3(u,v,w) && SAME3(x,y,z))
    {
      *(result) = -(_a*u) + _a*x;
      *(result+1) = 0;
      *(result+2) = 0;
      *(result+3) = 0;
      *(result+4) = 0;
    }
  else if (SAME3(u,v,x) && SAME3(w,y,z))
    {
      *(result) = _a*u - _a*w;
      *(result+1) = 0;
      *(result+2) = 0;
      *(result+3) = 0;
      *(result+4) = 0;
    }
  else if (SAME3(u,w,z) && SAME3(v,x,y))
    {
      *(result) = -(_a*u) + _a*v;
      *(result+1) = 0;
      *(result+2) = 0;
      *(result+3) = 0;
      *(result+4) = 0;
    }
  else if (SAME3(u,x,z) && SAME3(v,w,y))
    {
      *(result) = _a*u - _a*v;
      *(result+1) = 0;
      *(result+2) = 0;
      *(result+3) = 0;
      *(result+4) = 0;
    }
  else if (SAME4(u,v,y,z))
    {
      *(result) = 4*_a*u - 3*_a*w - _a*x;
      *(result+1) = 0;
      *(result+2) = 0;
      *(result+3) = 0;
      *(result+4) = 0;
    }
  else if (SAME2(u,z) && SAME2(v,y) && SAME2(w,x))
    {
      *(result) = -2*_a2*u - 2*_a2*v + 4*_a2*w;
      *(result+1) = 2*_a2*u + 2*_a*u2 + 2*_a2*v - 4*_a*u*v + 2*_a*v2 - 4*_a2*w - 2*_a*u*w - 2*_a*v*w + 4*_a*w2;
      *(result+2) = 0;
      *(result+3) = 0;
      *(result+4) = 0;
    }
  else if (SAME2(u,v) && SAME2(y,z))
    {
      *(result) = -6*_a2*u + 9*_a2*w + 3*_a2*x - 6*_a2*y;
      *(result+1) = 6*_a2*u - 6*_a*u2 - 9*_a2*w + 6*_a*u*w - 3*_a2*x + 4*_a*u*x - 3*_a*w*x - _a*x2 + 6*_a2*y - 4*_a*u*y + 6*_a*w*y + 4*_a*x*y - 6*_a*y2;
      *(result+2) = 0;
      *(result+3) = 0;
      *(result+4) = 0;
    }
  else if (SAME3(u,v,x))
    {
      *(result) = -(_a2*u) + 3*_a2*w - _a2*y - _a2*z;
      *(result+1) = _a2*u - _a*u2 - 3*_a2*w + _a*u*w + _a2*y + _a*w*y - _a*y2 + _a2*z + _a*w*z - _a*z2;
      *(result+2) = 0;
      *(result+3) = 0;
      *(result+4) = 0;
    }
  else if (SAME3(x,y,z))
    {
      *(result) = -(_a2*u) - _a2*v + 3*_a2*w - _a2*x;
      *(result+1) = _a2*u - _a*u2 + _a2*v - _a*v2 - 3*_a2*w + _a*u*w + _a*v*w + _a2*x + _a*w*x - _a*x2;
      *(result+2) = 0;
      *(result+3) = 0;
      *(result+4) = 0;
    }
  else if (SAME3(u,v,w) && SAME2(x,y))
    {
      *(result) = -3*_a3*u + 3*_a3*z;
      *(result+1) = 6*_a3*u - 8*_a2*u*x + 2*_a2*x2 - 6*_a3*z + 2*_a2*u*z + 4*_a2*x*z;
      *(result+2) = -3*_a3*u + 8*_a2*u*x - 2*_a2*x2 - 4*_a*u*x2 + _a*x3 + 3*_a3*z - 2*_a2*u*z - 4*_a2*x*z + 3*_a*x2*z + _a*u*z2 - _a*x*z2;
      *(result+3) = 0;
      *(result+4) = 0;
    }
  else if (SAME3(u,v,w) && SAME2(x,z))
    {
      *(result) = -3*_a3*u + 3*_a3*y;
      *(result+1) = 6*_a3*u - 8*_a2*u*x + 2*_a2*x2 - 6*_a3*y + 2*_a2*u*y + 4*_a2*x*y;
      *(result+2) = -3*_a3*u + 8*_a2*u*x - 2*_a2*x2 - 4*_a*u*x2 + _a*x3 + 3*_a3*y - 2*_a2*u*y - 4*_a2*x*y + 3*_a*x2*y + _a*u*y2 - _a*x*y2;
      *(result+3) = 0;
      *(result+4) = 0;
    }
  else if (SAME3(w,y,z) && SAME2(u,x))
    {
      *(result) = 3*_a3*v - 3*_a3*w;
      *(result+1) = 2*_a2*u2 - 6*_a3*v + 4*_a2*u*v + 6*_a3*w - 8*_a2*u*w + 2*_a2*v*w;
      *(result+2) = -2*_a2*u2 + _a*u3 + 3*_a3*v - 4*_a2*u*v + 3*_a*u2*v - _a*u*v2 - 3*_a3*w + 8*_a2*u*w - 4*_a*u2*w - 2*_a2*v*w + _a*v2*w;
      *(result+3) = 0;
      *(result+4) = 0;
    }
  else if (SAME3(w,y,z) && SAME2(v,x))
    {
      *(result) = 3*_a3*u - 3*_a3*w;
      *(result+1) = -6*_a3*u + 4*_a2*u*v + 2*_a2*v2 + 6*_a3*w + 2*_a2*u*w - 8*_a2*v*w;
      *(result+2) = 3*_a3*u - 4*_a2*u*v - _a*u2*v - 2*_a2*v2 + 3*_a*u*v2 + _a*v3 - 3*_a3*w - 2*_a2*u*w + _a*u2*w + 8*_a2*v*w - 4*_a*v2*w;
      *(result+3) = 0;
      *(result+4) = 0;
    }
  else if (SAME4(u,w,x,y))
    {
      *(result) = -6*_a3*u + 3*_a3*v + 3*_a3*z;
      *(result+1) = 12*_a3*u - 8*_a2*u2 - 6*_a3*v + 2*_a2*u*v - 6*_a3*z + 2*_a2*u*z + 4*_a2*v*z;
      *(result+2) = -6*_a3*u + 8*_a2*u2 + 3*_a3*v - 2*_a2*u*v - 4*_a*u2*v + _a*u*v2 + 3*_a3*z - 2*_a2*u*z - 4*_a*u2*z - 4*_a2*v*z + 8*_a*u*v*z - _a*v2*z + _a*u*z2 - _a*v*z2;
      *(result+3) = 0;
      *(result+4) = 0;
    }
  else if (SAME4(v,w,x,z))
    {
      *(result) = 3*_a3*u - 6*_a3*v + 3*_a3*y;
      *(result+1) = -6*_a3*u + 12*_a3*v + 2*_a2*u*v - 8*_a2*v2 - 6*_a3*y + 4*_a2*u*y + 2*_a2*v*y;
      *(result+2) = 3*_a3*u - 6*_a3*v - 2*_a2*u*v + _a*u2*v + 8*_a2*v2 - 4*_a*u*v2 + 3*_a3*y - 4*_a2*u*y - _a*u2*y - 2*_a2*v*y + 8*_a*u*v*y - 4*_a*v2*y - _a*u*y2 + _a*v*y2;
      *(result+3) = 0;
      *(result+4) = 0;
    }
  else if (SAME2(u,y) && SAME2(v,z))
    {
      *(result) = 2*_a3*u + 2*_a3*v - 3*_a3*w - _a3*x;
      *(result+1) = -4*_a3*u + 4*_a2*u2 - 4*_a3*v - 8*_a2*u*v + 4*_a2*v2 + 6*_a3*w + 2*_a3*x + 4*_a2*u*x + 4*_a2*v*x - 6*_a2*w*x - 2*_a2*x2;
      *(result+2) = 2*_a3*u - 4*_a2*u2 + 2*_a*u3 + 2*_a3*v + 8*_a2*u*v - 2*_a*u2*v - 4*_a2*v2 - 2*_a*u*v2 + 2*_a*v3 - 3*_a3*w - _a*u2*w + 2*_a*u*v*w - _a*v2*w - _a3*x - 4*_a2*u*x + _a*u2*x - 4*_a2*v*x - 2*_a*u*v*x + _a*v2*x + 6*_a2*w*x + 2*_a2*x2 + 2*_a*u*x2 + 2*_a*v*x2 - 3*_a*w*x2 - _a*x3;
      *(result+3) = 0;
      *(result+4) = 0;
    }
  else if (SAME2(u,z) && SAME2(v,y))
    {
      *(result) = 2*_a3*u + 2*_a3*v - 3*_a3*w - _a3*x;
      *(result+1) = -4*_a3*u - 2*_a2*u2 - 4*_a3*v + 4*_a2*u*v - 2*_a2*v2 + 6*_a3*w + 2*_a3*x + 4*_a2*u*x + 4*_a2*v*x - 6*_a2*w*x - 2*_a2*x2;
      *(result+2) = 2*_a3*u + 2*_a2*u2 + 2*_a3*v - 4*_a2*u*v + 2*_a2*v2 - 3*_a3*w - _a*u2*w + 2*_a*u*v*w - _a*v2*w - _a3*x - 4*_a2*u*x - _a*u2*x - 4*_a2*v*x + 2*_a*u*v*x - _a*v2*x + 6*_a2*w*x + 2*_a2*x2 + 2*_a*u*x2 + 2*_a*v*x2 - 3*_a*w*x2 - _a*x3;
      *(result+3) = 0;
      *(result+4) = 0;
    }
  else if (SAME4(u,w,x,z))
    {
      *(result) = 6*_a4*u - 3*_a4*v - 3*_a4*y;
      *(result+1) = -18*_a4*u + 20*_a3*u2 + 9*_a4*v - 11*_a3*u*v - 3*_a3*v2 + 9*_a4*y - 11*_a3*u*y + 8*_a3*v*y - 3*_a3*y2;
      *(result+2) = 18*_a4*u - 40*_a3*u2 + 16*_a2*u3 - 9*_a4*v + 22*_a3*u*v - 4*_a2*u2*v + 6*_a3*v2 - 9*_a2*u*v2 - 9*_a4*y + 22*_a3*u*y - 4*_a2*u2*y - 16*_a3*v*y + 4*_a2*u*v*y + 3*_a2*v2*y + 6*_a3*y2 - 9*_a2*u*y2 + 3*_a2*v*y2;
      *(result+3) = -6*_a4*u + 20*_a3*u2 - 16*_a2*u3 + 3*_a4*v - 11*_a3*u*v + 4*_a2*u2*v + 8*_a*u3*v - 3*_a3*v2 + 9*_a2*u*v2 - 10*_a*u2*v2 + 2*_a*u*v3 + 3*_a4*y - 11*_a3*u*y + 4*_a2*u2*y + 8*_a*u3*y + 8*_a3*v*y - 4*_a2*u*v*y - 8*_a*u2*v*y - 3*_a2*v2*y + 5*_a*u*v2*y - 2*_a*v3*y - 3*_a3*y2 + 9*_a2*u*y2 - 10*_a*u2*y2 - 3*_a2*v*y2 + 5*_a*u*v*y2 + 2*_a*v2*y2 + 2*_a*u*y3 - 2*_a*v*y3;
      *(result+4) = 0;
    }
  else if (SAME4(v,w,x,y))
    {
      *(result) = -3*_a4*u + 6*_a4*v - 3*_a4*z;
      *(result+1) = 9*_a4*u - 3*_a3*u2 - 18*_a4*v - 11*_a3*u*v + 20*_a3*v2 + 9*_a4*z + 8*_a3*u*z - 11*_a3*v*z - 3*_a3*z2;
      *(result+2) = -9*_a4*u + 6*_a3*u2 + 18*_a4*v + 22*_a3*u*v - 9*_a2*u2*v - 40*_a3*v2 - 4*_a2*u*v2 + 16*_a2*v3 - 9*_a4*z - 16*_a3*u*z + 3*_a2*u2*z + 22*_a3*v*z + 4*_a2*u*v*z - 4*_a2*v2*z + 6*_a3*z2 + 3*_a2*u*z2 - 9*_a2*v*z2;
      *(result+3) = 3*_a4*u - 3*_a3*u2 - 6*_a4*v - 11*_a3*u*v + 9*_a2*u2*v + 2*_a*u3*v + 20*_a3*v2 + 4*_a2*u*v2 - 10*_a*u2*v2 - 16*_a2*v3 + 8*_a*u*v3 + 3*_a4*z + 8*_a3*u*z - 3*_a2*u2*z - 2*_a*u3*z - 11*_a3*v*z - 4*_a2*u*v*z + 5*_a*u2*v*z + 4*_a2*v2*z - 8*_a*u*v2*z + 8*_a*v3*z - 3*_a3*z2 - 3*_a2*u*z2 + 2*_a*u2*z2 + 9*_a2*v*z2 + 5*_a*u*v*z2 - 10*_a*v2*z2 - 2*_a*u*z3 + 2*_a*v*z3;
      *(result+4) = 0;
    }
  else if (SAME2(u,w) && SAME2(x,y))
    {
      *(result) = 6*_a4*u - 3*_a4*v - 3*_a4*z;
      *(result+1) = -18*_a4*u + 9*_a4*v + 3*_a3*u*v - 3*_a3*v2 + 10*_a3*u*x + _a3*v*x - 2*_a3*x2 + 9*_a4*z + 5*_a3*u*z - 7*_a3*v*z - 7*_a3*x*z;
      *(result+2) = 18*_a4*u - 9*_a4*v - 6*_a3*u*v + 6*_a3*v2 - 20*_a3*u*x - 3*_a2*u2*x - 2*_a3*v*x + 6*_a2*u*v*x - 3*_a2*v2*x + 4*_a3*x2 + 6*_a2*u*x2 + 6*_a2*v*x2 - 3*_a2*x3 - 9*_a4*z - 10*_a3*u*z + 3*_a2*u2*z + 14*_a3*v*z - 3*_a2*v2*z + 14*_a3*x*z + 8*_a2*u*x*z - 10*_a2*v*x*z - 7*_a2*x2*z - 2*_a2*u*z2 + _a2*v*z2 + _a2*x*z2;
      *(result+3) = -6*_a4*u + 3*_a4*v + 3*_a3*u*v - 3*_a3*v2 + 10*_a3*u*x + 3*_a2*u2*x + _a*u3*x + _a3*v*x - 6*_a2*u*v*x - 3*_a*u2*v*x + 3*_a2*v2*x + 3*_a*u*v2*x - _a*v3*x - 2*_a3*x2 - 6*_a2*u*x2 - 3*_a*u2*x2 - 6*_a2*v*x2 + 2*_a*u*v*x2 + _a*v2*x2 + 3*_a2*x3 + 3*_a*u*x3 + _a*v*x3 - _a*x4 + 3*_a4*z + 5*_a3*u*z - 3*_a2*u2*z - _a*u3*z - 7*_a3*v*z + 3*_a*u2*v*z + 3*_a2*v2*z - 3*_a*u*v2*z + _a*v3*z - 7*_a3*x*z - 8*_a2*u*x*z + 3*_a*u2*x*z + 10*_a2*v*x*z + 2*_a*u*v*x*z - 5*_a*v2*x*z + 7*_a2*x2*z + _a*u*x2*z - _a*v*x2*z - 3*_a*x3*z + 2*_a2*u*z2 - _a2*v*z2 - _a*u*v*z2 + _a*v2*z2 - _a2*x*z2 - _a*u*x*z2 + _a*x2*z2;
      *(result+4) = 0;
    }
  else if (SAME2(u,x) && SAME2(w,y))
    {
      *(result) = -3*_a4*v + 6*_a4*w - 3*_a4*z;
      *(result+1) = -2*_a3*u2 + 9*_a4*v - 7*_a3*u*v - 18*_a4*w + 10*_a3*u*w + 5*_a3*v*w + 9*_a4*z + _a3*u*z - 7*_a3*v*z + 3*_a3*w*z - 3*_a3*z2;
      *(result+2) = 4*_a3*u2 - 3*_a2*u3 - 9*_a4*v + 14*_a3*u*v - 7*_a2*u2*v + _a2*u*v2 + 18*_a4*w - 20*_a3*u*w + 6*_a2*u2*w - 10*_a3*v*w + 8*_a2*u*v*w - 2*_a2*v2*w - 3*_a2*u*w2 + 3*_a2*v*w2 - 9*_a4*z - 2*_a3*u*z + 6*_a2*u2*z + 14*_a3*v*z - 10*_a2*u*v*z + _a2*v2*z - 6*_a3*w*z + 6*_a2*u*w*z + 6*_a3*z2 - 3*_a2*u*z2 - 3*_a2*v*z2;
      *(result+3) = -2*_a3*u2 + 3*_a2*u3 - _a*u4 + 3*_a4*v - 7*_a3*u*v + 7*_a2*u2*v - 3*_a*u3*v - _a2*u*v2 + _a*u2*v2 - 6*_a4*w + 10*_a3*u*w - 6*_a2*u2*w + 3*_a*u3*w + 5*_a3*v*w - 8*_a2*u*v*w + _a*u2*v*w + 2*_a2*v2*w - _a*u*v2*w + 3*_a2*u*w2 - 3*_a*u2*w2 - 3*_a2*v*w2 + 3*_a*u*v*w2 + _a*u*w3 - _a*v*w3 + 3*_a4*z + _a3*u*z - 6*_a2*u2*z + _a*u3*z - 7*_a3*v*z + 10*_a2*u*v*z - _a*u2*v*z - _a2*v2*z + 3*_a3*w*z - 6*_a2*u*w*z + 2*_a*u2*w*z + 2*_a*u*v*w*z - _a*v2*w*z - 3*_a*u*w2*z + 3*_a*v*w2*z - 3*_a3*z2 + 3*_a2*u*z2 + _a*u2*z2 + 3*_a2*v*z2 - 5*_a*u*v*z2 + _a*v2*z2 + 3*_a*u*w*z2 - 3*_a*v*w*z2 - _a*u*z3 + _a*v*z3;
      *(result+4) = 0;
    }
  else if (SAME2(v,w) && SAME2(x,z))
    {
      *(result) = -3*_a4*u + 6*_a4*v - 3*_a4*y;
      *(result+1) = 9*_a4*u - 3*_a3*u2 - 18*_a4*v + 3*_a3*u*v + _a3*u*x + 10*_a3*v*x - 2*_a3*x2 + 9*_a4*y - 7*_a3*u*y + 5*_a3*v*y - 7*_a3*x*y;
      *(result+2) = -9*_a4*u + 6*_a3*u2 + 18*_a4*v - 6*_a3*u*v - 2*_a3*u*x - 3*_a2*u2*x - 20*_a3*v*x + 6*_a2*u*v*x - 3*_a2*v2*x + 4*_a3*x2 + 6*_a2*u*x2 + 6*_a2*v*x2 - 3*_a2*x3 - 9*_a4*y + 14*_a3*u*y - 3*_a2*u2*y - 10*_a3*v*y + 3*_a2*v2*y + 14*_a3*x*y - 10*_a2*u*x*y + 8*_a2*v*x*y - 7*_a2*x2*y + _a2*u*y2 - 2*_a2*v*y2 + _a2*x*y2;
      *(result+3) = 3*_a4*u - 3*_a3*u2 - 6*_a4*v + 3*_a3*u*v + _a3*u*x + 3*_a2*u2*x - _a*u3*x + 10*_a3*v*x - 6*_a2*u*v*x + 3*_a*u2*v*x + 3*_a2*v2*x - 3*_a*u*v2*x + _a*v3*x - 2*_a3*x2 - 6*_a2*u*x2 + _a*u2*x2 - 6*_a2*v*x2 + 2*_a*u*v*x2 - 3*_a*v2*x2 + 3*_a2*x3 + _a*u*x3 + 3*_a*v*x3 - _a*x4 + 3*_a4*y - 7*_a3*u*y + 3*_a2*u2*y + _a*u3*y + 5*_a3*v*y - 3*_a*u2*v*y - 3*_a2*v2*y + 3*_a*u*v2*y - _a*v3*y - 7*_a3*x*y + 10*_a2*u*x*y - 5*_a*u2*x*y - 8*_a2*v*x*y + 2*_a*u*v*x*y + 3*_a*v2*x*y + 7*_a2*x2*y - _a*u*x2*y + _a*v*x2*y - 3*_a*x3*y - _a2*u*y2 + _a*u2*y2 + 2*_a2*v*y2 - _a*u*v*y2 - _a2*x*y2 - _a*v*x*y2 + _a*x2*y2;
      *(result+4) = 0;
    }
  else if (SAME2(v,x) && SAME2(w,z))
    {
      *(result) = -3*_a4*u + 6*_a4*w - 3*_a4*y;
      *(result+1) = 9*_a4*u - 7*_a3*u*v - 2*_a3*v2 - 18*_a4*w + 5*_a3*u*w + 10*_a3*v*w + 9*_a4*y - 7*_a3*u*y + _a3*v*y + 3*_a3*w*y - 3*_a3*y2;
      *(result+2) = -9*_a4*u + 14*_a3*u*v + _a2*u2*v + 4*_a3*v2 - 7*_a2*u*v2 - 3*_a2*v3 + 18*_a4*w - 10*_a3*u*w - 2*_a2*u2*w - 20*_a3*v*w + 8*_a2*u*v*w + 6*_a2*v2*w + 3*_a2*u*w2 - 3*_a2*v*w2 - 9*_a4*y + 14*_a3*u*y + _a2*u2*y - 2*_a3*v*y - 10*_a2*u*v*y + 6*_a2*v2*y - 6*_a3*w*y + 6*_a2*v*w*y + 6*_a3*y2 - 3*_a2*u*y2 - 3*_a2*v*y2;
      *(result+3) = 3*_a4*u - 7*_a3*u*v - _a2*u2*v - 2*_a3*v2 + 7*_a2*u*v2 + _a*u2*v2 + 3*_a2*v3 - 3*_a*u*v3 - _a*v4 - 6*_a4*w + 5*_a3*u*w + 2*_a2*u2*w + 10*_a3*v*w - 8*_a2*u*v*w - _a*u2*v*w - 6*_a2*v2*w + _a*u*v2*w + 3*_a*v3*w - 3*_a2*u*w2 + 3*_a2*v*w2 + 3*_a*u*v*w2 - 3*_a*v2*w2 - _a*u*w3 + _a*v*w3 + 3*_a4*y - 7*_a3*u*y - _a2*u2*y + _a3*v*y + 10*_a2*u*v*y - 6*_a2*v2*y - _a*u*v2*y + _a*v3*y + 3*_a3*w*y - _a*u2*w*y - 6*_a2*v*w*y + 2*_a*u*v*w*y + 2*_a*v2*w*y + 3*_a*u*w2*y - 3*_a*v*w2*y - 3*_a3*y2 + 3*_a2*u*y2 + _a*u2*y2 + 3*_a2*v*y2 - 5*_a*u*v*y2 + _a*v2*y2 - 3*_a*u*w*y2 + 3*_a*v*w*y2 + _a*u*y3 - _a*v*y3;
      *(result+4) = 0;
    }
  else if (SAME2(u,v))
    {
      *(result) = -6*_a4*u + 9*_a4*w + 3*_a4*x - 3*_a4*y - 3*_a4*z;
      *(result+1) = 18*_a4*u - 6*_a3*u2 - 27*_a4*w + 6*_a3*u*w - 9*_a4*x - 8*_a3*u*x + 15*_a3*w*x + 5*_a3*x2 + 9*_a4*y - 2*_a3*u*y + 3*_a3*w*y - 4*_a3*x*y - 3*_a3*y2 + 9*_a4*z - 2*_a3*u*z + 3*_a3*w*z - 4*_a3*x*z - 3*_a3*z2;
      *(result+2) = -18*_a4*u + 12*_a3*u2 + 27*_a4*w - 12*_a3*u*w + 9*_a4*x + 16*_a3*u*x - 12*_a2*u2*x - 30*_a3*w*x + 12*_a2*u*w*x - 10*_a3*x2 + 2*_a2*u*x2 + 3*_a2*w*x2 + _a2*x3 - 9*_a4*y + 4*_a3*u*y - 6*_a3*w*y + 8*_a3*x*y - 4*_a2*u*x*y + 6*_a2*w*x*y + _a2*x2*y + 6*_a3*y2 - 3*_a2*u*y2 - 3*_a2*x*y2 - 9*_a4*z + 4*_a3*u*z - 6*_a3*w*z + 8*_a3*x*z - 4*_a2*u*x*z + 6*_a2*w*x*z + _a2*x2*z + 6*_a2*u*y*z - 6*_a2*x*y*z + 6*_a3*z2 - 3*_a2*u*z2 - 3*_a2*x*z2;
      *(result+3) = 6*_a4*u - 6*_a3*u2 - 9*_a4*w + 6*_a3*u*w - 3*_a4*x - 8*_a3*u*x + 12*_a2*u2*x + 15*_a3*w*x - 12*_a2*u*w*x + 5*_a3*x2 - 2*_a2*u*x2 - 6*_a*u2*x2 - 3*_a2*w*x2 + 6*_a*u*w*x2 - _a2*x3 + 4*_a*u*x3 - 3*_a*w*x3 - _a*x4 + 3*_a4*y - 2*_a3*u*y + 3*_a3*w*y - 4*_a3*x*y + 4*_a2*u*x*y - 6*_a2*w*x*y - _a2*x2*y - 2*_a*u*x2*y + 3*_a*w*x2*y + 2*_a*x3*y - 3*_a3*y2 + 3*_a2*u*y2 - 2*_a*u2*y2 + 2*_a*u*w*y2 + 3*_a2*x*y2 + _a*u*x*y2 - 2*_a*w*x*y2 - 2*_a*x2*y2 - _a*u*y3 + _a*x*y3 + 3*_a4*z - 2*_a3*u*z + 3*_a3*w*z - 4*_a3*x*z + 4*_a2*u*x*z - 6*_a2*w*x*z - _a2*x2*z - 2*_a*u*x2*z + 3*_a*w*x2*z + 2*_a*x3*z - 6*_a2*u*y*z + 4*_a*u2*y*z - 4*_a*u*w*y*z + 6*_a2*x*y*z - 2*_a*u*x*y*z + 4*_a*w*x*y*z - 2*_a*x2*y*z + _a*u*y2*z - _a*x*y2*z - 3*_a3*z2 + 3*_a2*u*z2 - 2*_a*u2*z2 + 2*_a*u*w*z2 + 3*_a2*x*z2 + _a*u*x*z2 - 2*_a*w*x*z2 - 2*_a*x2*z2 + _a*u*y*z2 - _a*x*y*z2 - _a*u*z3 + _a*x*z3;
      *(result+4) = 0;
    }
  else if (SAME2(y,z))
    {
      *(result) = -3*_a4*u - 3*_a4*v + 9*_a4*w + 3*_a4*x - 6*_a4*y;
      *(result+1) = 9*_a4*u - 3*_a3*u2 + 9*_a4*v - 3*_a3*v2 - 27*_a4*w + 3*_a3*u*w + 3*_a3*v*w - 9*_a4*x - 4*_a3*u*x - 4*_a3*v*x + 15*_a3*w*x + 5*_a3*x2 + 18*_a4*y - 2*_a3*u*y - 2*_a3*v*y + 6*_a3*w*y - 8*_a3*x*y - 6*_a3*y2;
      *(result+2) = -9*_a4*u + 6*_a3*u2 - 9*_a4*v + 6*_a3*v2 + 27*_a4*w - 6*_a3*u*w - 6*_a3*v*w + 9*_a4*x + 8*_a3*u*x - 3*_a2*u2*x + 8*_a3*v*x - 6*_a2*u*v*x - 3*_a2*v2*x - 30*_a3*w*x + 6*_a2*u*w*x + 6*_a2*v*w*x - 10*_a3*x2 + _a2*u*x2 + _a2*v*x2 + 3*_a2*w*x2 + _a2*x3 - 18*_a4*y + 4*_a3*u*y - 3*_a2*u2*y + 4*_a3*v*y + 6*_a2*u*v*y - 3*_a2*v2*y - 12*_a3*w*y + 16*_a3*x*y - 4*_a2*u*x*y - 4*_a2*v*x*y + 12*_a2*w*x*y + 2*_a2*x2*y + 12*_a3*y2 - 12*_a2*x*y2;
      *(result+3) = 3*_a4*u - 3*_a3*u2 + 3*_a4*v - 3*_a3*v2 - 9*_a4*w + 3*_a3*u*w + 3*_a3*v*w - 3*_a4*x - 4*_a3*u*x + 3*_a2*u2*x + _a*u3*x - 4*_a3*v*x + 6*_a2*u*v*x - _a*u2*v*x + 3*_a2*v2*x - _a*u*v2*x + _a*v3*x + 15*_a3*w*x - 6*_a2*u*w*x - 2*_a*u2*w*x - 6*_a2*v*w*x + 4*_a*u*v*w*x - 2*_a*v2*w*x + 5*_a3*x2 - _a2*u*x2 - 2*_a*u2*x2 - _a2*v*x2 - 2*_a*u*v*x2 - 2*_a*v2*x2 - 3*_a2*w*x2 + 3*_a*u*w*x2 + 3*_a*v*w*x2 - _a2*x3 + 2*_a*u*x3 + 2*_a*v*x3 - 3*_a*w*x3 - _a*x4 + 6*_a4*y - 2*_a3*u*y + 3*_a2*u2*y - _a*u3*y - 2*_a3*v*y - 6*_a2*u*v*y + _a*u2*v*y + 3*_a2*v2*y + _a*u*v2*y - _a*v3*y + 6*_a3*w*y + 2*_a*u2*w*y - 4*_a*u*v*w*y + 2*_a*v2*w*y - 8*_a3*x*y + 4*_a2*u*x*y + _a*u2*x*y + 4*_a2*v*x*y - 2*_a*u*v*x*y + _a*v2*x*y - 12*_a2*w*x*y - 2*_a2*x2*y - 2*_a*u*x2*y - 2*_a*v*x2*y + 6*_a*w*x2*y + 4*_a*x3*y - 6*_a3*y2 - 2*_a*u2*y2 + 4*_a*u*v*y2 - 2*_a*v2*y2 + 12*_a2*x*y2 - 6*_a*x2*y2;
      *(result+4) = 0;
    }
  else
    {
      *(result) = 3*_a5*u + 3*_a5*v - 9*_a5*w - 3*_a5*x + 3*_a5*y + 3*_a5*z;
      *(result+1) = -12*_a5*u + 3*_a4*u2 - 12*_a5*v + 3*_a4*v2 + 36*_a5*w - 3*_a4*u*w - 3*_a4*v*w + 12*_a5*x + 7*_a4*u*x + 7*_a4*v*x - 24*_a4*w*x - 8*_a4*x2 - 12*_a5*y + 10*_a4*u*y - 8*_a4*v*y - 3*_a4*w*y + 7*_a4*x*y + 3*_a4*y2 - 12*_a5*z - 8*_a4*u*z + 10*_a4*v*z - 3*_a4*w*z + 7*_a4*x*z + 3*_a4*z2;
      *(result+2) = 18*_a5*u - 9*_a4*u2 + 18*_a5*v - 9*_a4*v2 - 54*_a5*w + 9*_a4*u*w + 9*_a4*v*w - 18*_a5*x - 21*_a4*u*x + 6*_a3*u2*x - 21*_a4*v*x + 6*_a3*u*v*x + 6*_a3*v2*x + 72*_a4*w*x - 9*_a3*u*w*x - 9*_a3*v*w*x + 24*_a4*x2 + 3*_a3*u*x2 + 3*_a3*v*x2 - 18*_a3*w*x2 - 6*_a3*x3 + 18*_a5*y - 30*_a4*u*y + 6*_a3*u2*y + 24*_a4*v*y - 3*_a3*u*v*y - 3*_a3*v2*y + 9*_a4*w*y - 21*_a4*x*y + 12*_a3*u*x*y - 6*_a3*v*x*y - 9*_a3*w*x*y + 3*_a3*x2*y - 9*_a4*y2 + 6*_a3*u*y2 - 3*_a3*v*y2 + 6*_a3*x*y2 + 18*_a5*z + 24*_a4*u*z - 3*_a3*u2*z - 30*_a4*v*z - 3*_a3*u*v*z + 6*_a3*v2*z + 9*_a4*w*z - 21*_a4*x*z - 6*_a3*u*x*z + 12*_a3*v*x*z - 9*_a3*w*x*z + 3*_a3*x2*z - 3*_a3*u*y*z - 3*_a3*v*y*z + 6*_a3*x*y*z - 9*_a4*z2 - 3*_a3*u*z2 + 6*_a3*v*z2 + 6*_a3*x*z2;
      *(result+3) = -12*_a5*u + 9*_a4*u2 - 12*_a5*v + 9*_a4*v2 + 36*_a5*w - 9*_a4*u*w - 9*_a4*v*w + 12*_a5*x + 21*_a4*u*x - 12*_a3*u2*x - _a2*u3*x + 21*_a4*v*x - 12*_a3*u*v*x + _a2*u2*v*x - 12*_a3*v2*x + _a2*u*v2*x - _a2*v3*x - 72*_a4*w*x + 18*_a3*u*w*x + 2*_a2*u2*w*x + 18*_a3*v*w*x - 4*_a2*u*v*w*x + 2*_a2*v2*w*x - 24*_a4*x2 - 6*_a3*u*x2 + 5*_a2*u2*x2 - 6*_a3*v*x2 + 8*_a2*u*v*x2 + 5*_a2*v2*x2 + 36*_a3*w*x2 - 9*_a2*u*w*x2 - 9*_a2*v*w*x2 + 12*_a3*x3 - 3*_a2*u*x3 - 3*_a2*v*x3 - 12*_a5*y + 30*_a4*u*y - 12*_a3*u2*y - _a2*u3*y - 24*_a4*v*y + 6*_a3*u*v*y + 4*_a2*u2*v*y + 6*_a3*v2*y - 5*_a2*u*v2*y + 2*_a2*v3*y - 9*_a4*w*y - _a2*u2*w*y + 2*_a2*u*v*w*y - _a2*v2*w*y + 21*_a4*x*y - 24*_a3*u*x*y + 6*_a2*u2*x*y + 12*_a3*v*x*y - 2*_a2*u*v*x*y - 4*_a2*v2*x*y + 18*_a3*w*x*y - 6*_a3*x2*y + 2*_a2*u*x2*y + 4*_a2*v*x2*y - 9*_a2*w*x2*y - 3*_a2*x3*y + 9*_a4*y2 - 12*_a3*u*y2 + 2*_a2*u2*y2 + 6*_a3*v*y2 + 2*_a2*u*v*y2 - 2*_a2*v2*y2 - _a2*u*w*y2 - _a2*v*w*y2 - 12*_a3*x*y2 + 6*_a2*u*x*y2 - 4*_a2*v*x*y2 + 2*_a2*w*x*y2 + 5*_a2*x2*y2 - _a2*u*y3 + 2*_a2*v*y3 - _a2*x*y3 - 12*_a5*z - 24*_a4*u*z + 6*_a3*u2*z + 2*_a2*u3*z + 30*_a4*v*z + 6*_a3*u*v*z - 5*_a2*u2*v*z - 12*_a3*v2*z + 4*_a2*u*v2*z - _a2*v3*z - 9*_a4*w*z - _a2*u2*w*z + 2*_a2*u*v*w*z - _a2*v2*w*z + 21*_a4*x*z + 12*_a3*u*x*z - 4*_a2*u2*x*z - 24*_a3*v*x*z - 2*_a2*u*v*x*z + 6*_a2*v2*x*z + 18*_a3*w*x*z - 6*_a3*x2*z + 4*_a2*u*x2*z + 2*_a2*v*x2*z - 9*_a2*w*x2*z - 3*_a2*x3*z + 6*_a3*u*y*z + 2*_a2*u2*y*z + 6*_a3*v*y*z - 8*_a2*u*v*y*z + 2*_a2*v2*y*z + 2*_a2*u*w*y*z + 2*_a2*v*w*y*z - 12*_a3*x*y*z - 2*_a2*u*x*y*z - 2*_a2*v*x*y*z - 4*_a2*w*x*y*z + 8*_a2*x2*y*z + 4*_a2*u*y2*z - 5*_a2*v*y2*z + _a2*x*y2*z + 9*_a4*z2 + 6*_a3*u*z2 - 2*_a2*u2*z2 - 12*_a3*v*z2 + 2*_a2*u*v*z2 + 2*_a2*v2*z2 - _a2*u*w*z2 - _a2*v*w*z2 - 12*_a3*x*z2 - 4*_a2*u*x*z2 + 6*_a2*v*x*z2 + 2*_a2*w*x*z2 + 5*_a2*x2*z2 - 5*_a2*u*y*z2 + 4*_a2*v*y*z2 + _a2*x*y*z2 + 2*_a2*u*z3 - _a2*v*z3 - _a2*x*z3;
      *(result+4) = 3*_a5*u - 3*_a4*u2 + 3*_a5*v - 3*_a4*v2 - 9*_a5*w + 3*_a4*u*w + 3*_a4*v*w - 3*_a5*x - 7*_a4*u*x + 6*_a3*u2*x + _a2*u3*x - 7*_a4*v*x + 6*_a3*u*v*x - _a2*u2*v*x + 6*_a3*v2*x - _a2*u*v2*x + _a2*v3*x + 24*_a4*w*x - 9*_a3*u*w*x - 2*_a2*u2*w*x - 9*_a3*v*w*x + 4*_a2*u*v*w*x - 2*_a2*v2*w*x + 8*_a4*x2 + 3*_a3*u*x2 - 5*_a2*u2*x2 - _a*u3*x2 + 3*_a3*v*x2 - 8*_a2*u*v*x2 + _a*u2*v*x2 - 5*_a2*v2*x2 + _a*u*v2*x2 - _a*v3*x2 - 18*_a3*w*x2 + 9*_a2*u*w*x2 + 2*_a*u2*w*x2 + 9*_a2*v*w*x2 - 4*_a*u*v*w*x2 + 2*_a*v2*w*x2 - 6*_a3*x3 + 3*_a2*u*x3 + 2*_a*u2*x3 + 3*_a2*v*x3 + 2*_a*u*v*x3 + 2*_a*v2*x3 - 3*_a*u*w*x3 - 3*_a*v*w*x3 - 2*_a*u*x4 - 2*_a*v*x4 + 3*_a*w*x4 + _a*x5 + 3*_a5*y - 10*_a4*u*y + 6*_a3*u2*y + _a2*u3*y + 8*_a4*v*y - 3*_a3*u*v*y - 4*_a2*u2*v*y - 3*_a3*v2*y + 5*_a2*u*v2*y - 2*_a2*v3*y + 3*_a4*w*y + _a2*u2*w*y - 2*_a2*u*v*w*y + _a2*v2*w*y - 7*_a4*x*y + 12*_a3*u*x*y - 6*_a2*u2*x*y - 6*_a3*v*x*y + 2*_a2*u*v*x*y + _a*u2*v*x*y + 4*_a2*v2*x*y - 2*_a*u*v2*x*y + _a*v3*x*y - 9*_a3*w*x*y - _a*u2*w*x*y + 2*_a*u*v*w*x*y - _a*v2*w*x*y + 3*_a3*x2*y - 2*_a2*u*x2*y - 4*_a2*v*x2*y + _a*u*v*x2*y - _a*v2*x2*y + 9*_a2*w*x2*y + 3*_a2*x3*y + 2*_a*v*x3*y - 3*_a*w*x3*y - 2*_a*x4*y - 3*_a4*y2 + 6*_a3*u*y2 - 2*_a2*u2*y2 - _a*u3*y2 - 3*_a3*v*y2 - 2*_a2*u*v*y2 + 2*_a*u2*v*y2 + 2*_a2*v2*y2 - _a*u*v2*y2 + _a2*u*w*y2 + _a*u2*w*y2 + _a2*v*w*y2 - 2*_a*u*v*w*y2 + _a*v2*w*y2 + 6*_a3*x*y2 - 6*_a2*u*x*y2 + 3*_a*u2*x*y2 + 4*_a2*v*x*y2 - _a*v2*x*y2 - 2*_a2*w*x*y2 - _a*u*w*x*y2 - _a*v*w*x*y2 - 5*_a2*x2*y2 - _a*v*x2*y2 + 2*_a*w*x2*y2 + 2*_a*x3*y2 + _a2*u*y3 - _a*u2*y3 - 2*_a2*v*y3 + _a*u*v*y3 + _a2*x*y3 + _a*v*x*y3 - _a*x2*y3 + 3*_a5*z + 8*_a4*u*z - 3*_a3*u2*z - 2*_a2*u3*z - 10*_a4*v*z - 3*_a3*u*v*z + 5*_a2*u2*v*z + 6*_a3*v2*z - 4*_a2*u*v2*z + _a2*v3*z + 3*_a4*w*z + _a2*u2*w*z - 2*_a2*u*v*w*z + _a2*v2*w*z - 7*_a4*x*z - 6*_a3*u*x*z + 4*_a2*u2*x*z + _a*u3*x*z + 12*_a3*v*x*z + 2*_a2*u*v*x*z - 2*_a*u2*v*x*z - 6*_a2*v2*x*z + _a*u*v2*x*z - 9*_a3*w*x*z - _a*u2*w*x*z + 2*_a*u*v*w*x*z - _a*v2*w*x*z + 3*_a3*x2*z - 4*_a2*u*x2*z - _a*u2*x2*z - 2*_a2*v*x2*z + _a*u*v*x2*z + 9*_a2*w*x2*z + 3*_a2*x3*z + 2*_a*u*x3*z - 3*_a*w*x3*z - 2*_a*x4*z - 3*_a3*u*y*z - 2*_a2*u2*y*z + _a*u3*y*z - 3*_a3*v*y*z + 8*_a2*u*v*y*z - _a*u2*v*y*z - 2*_a2*v2*y*z - _a*u*v2*y*z + _a*v3*y*z - 2*_a2*u*w*y*z - 2*_a*u2*w*y*z - 2*_a2*v*w*y*z + 4*_a*u*v*w*y*z - 2*_a*v2*w*y*z + 6*_a3*x*y*z + 2*_a2*u*x*y*z + 2*_a2*v*x*y*z - 4*_a*u*v*x*y*z + 4*_a2*w*x*y*z + 2*_a*u*w*x*y*z + 2*_a*v*w*x*y*z - 8*_a2*x2*y*z + _a*u*x2*y*z + _a*v*x2*y*z - 4*_a*w*x2*y*z + 2*_a*x3*y*z - 4*_a2*u*y2*z + 2*_a*u2*y2*z + 5*_a2*v*y2*z - _a*u*v*y2*z - _a*v2*y2*z - _a2*x*y2*z + _a*u*x*y2*z - 2*_a*v*x*y2*z + _a*x2*y2*z - 3*_a4*z2 - 3*_a3*u*z2 + 2*_a2*u2*z2 + 6*_a3*v*z2 - 2*_a2*u*v*z2 - _a*u2*v*z2 - 2*_a2*v2*z2 + 2*_a*u*v2*z2 - _a*v3*z2 + _a2*u*w*z2 + _a*u2*w*z2 + _a2*v*w*z2 - 2*_a*u*v*w*z2 + _a*v2*w*z2 + 6*_a3*x*z2 + 4*_a2*u*x*z2 - _a*u2*x*z2 - 6*_a2*v*x*z2 + 3*_a*v2*x*z2 - 2*_a2*w*x*z2 - _a*u*w*x*z2 - _a*v*w*x*z2 - 5*_a2*x2*z2 - _a*u*x2*z2 + 2*_a*w*x2*z2 + 2*_a*x3*z2 + 5*_a2*u*y*z2 - _a*u2*y*z2 - 4*_a2*v*y*z2 - _a*u*v*y*z2 + 2*_a*v2*y*z2 - _a2*x*y*z2 - 2*_a*u*x*y*z2 + _a*v*x*y*z2 + _a*x2*y*z2 - 2*_a2*u*z3 + _a2*v*z3 + _a*u*v*z3 - _a*v2*z3 + _a2*x*z3 + _a*u*x*z3 - _a*x2*z3;
    }

  return;
}

/* GAAK */

/* **************************************************************** */
/* **************************************************************** */

TVIL_HTYPE *TVIL_SetParamsH (TVIL_HTYPE *foo,
			     TVIL_REAL   u, 
			     TVIL_REAL   v, 
			     TVIL_REAL   w, 
			     TVIL_REAL   x,
			     TVIL_REAL   y,
			     TVIL_REAL   z)
{
  foo->arg[0] = u;
  foo->arg[1] = v;
  foo->arg[2] = w;
  foo->arg[3] = x;
  foo->arg[4] = y;
  foo->arg[5] = z;

  return foo;
}

/* **************************************************************** */

TVIL_HTYPE *TVIL_SetupH (TVIL_HTYPE *foo)
{
  TVIL_REAL u, v, w, x, y, z;

  u = foo->arg[0];
  v = foo->arg[1];
  w = foo->arg[2];
  x = foo->arg[3];
  y = foo->arg[4];
  z = foo->arg[5];

  /* printf("Original roots:\n"); */
  /* TVIL_cHd1Roots_orig (foo, foo->cHd1roots); */
  /* printf("New roots:\n"); */

  TVIL_cHd1Roots (foo, foo->cHd1roots);

  /* for (i=0; i<3; i++) */
  /*   printf("Root %d is %Lf\n", i+1, foo->cHd1roots[i]); */

  TVIL_cHGnum (u, v, w, x, y, z, &(foo->cHGnum[0][0]));
  TVIL_cHGnum (u, z, x, w, y, v, &(foo->cHGnum[1][0]));
  TVIL_cHGnum (u, w, v, z, y, x, &(foo->cHGnum[2][0]));
  TVIL_cHGnum (u, x, z, v, y, w, &(foo->cHGnum[3][0]));
  TVIL_cHGnum (w, v, u, y, x, z, &(foo->cHGnum[4][0]));
  TVIL_cHGnum (x, v, y, u, w, z, &(foo->cHGnum[5][0]));

  TVIL_cHGden (u, v, w, x, y, z, &(foo->cHGden[0][0]));
  TVIL_cHGden (u, z, x, w, y, v, &(foo->cHGden[1][0]));
  TVIL_cHGden (u, w, v, z, y, x, &(foo->cHGden[2][0]));
  TVIL_cHGden (u, x, z, v, y, w, &(foo->cHGden[3][0]));
  TVIL_cHGden (w, v, u, y, x, z, &(foo->cHGden[4][0]));
  TVIL_cHGden (x, v, y, u, w, z, &(foo->cHGden[5][0]));

  TVIL_cHnum (u, v, w, x, y, z, &(foo->cHnum[0]));

  TVIL_cHden (u, v, w, x, y, z, &(foo->cHden[0]));

  return foo;
}

/* **************************************************************** */
/* **************************************************************** */

void TVIL_cHd1Roots (TVIL_HTYPE *foo, TVIL_REAL *result)
{
  TVIL_COMPLEX r1, r2, r3;
  TVIL_REAL u, v, w, x, y, z;
  TVIL_REAL A, B, C, D;
  TVIL_REAL A2;
  TVIL_REAL B2, B3;

  u  = foo->arg[0];
  v  = foo->arg[1];
  w  = foo->arg[2];
  x  = foo->arg[3];
  y  = foo->arg[4];
  z  = foo->arg[5];

  TVIL_REAL u2 = u*u;
  TVIL_REAL  v2 = v*v;
  TVIL_REAL  w2 = w*w;
  TVIL_REAL  x2 = x*x;
  TVIL_REAL  y2 = y*y;
  TVIL_REAL  z2 = z*z;

  D = -2*_a3;
  C = 6*_a3 - _a2*u - _a2*v - _a2*w - _a2*x - _a2*y - _a2*z;
  B = -6*_a3 + 2*_a2*u + _a*u2 + 2*_a2*v - _a*u*v + _a*v2 + 
    2*_a2*w - _a*u*w - _a*v*w + _a*w2 + 2*_a2*x - _a*u*x - _a*v*x + 
    _a*x2 + 2*_a2*y - _a*v*y - _a*w*y - _a*x*y + _a*y2 + 2*_a2*z - 
    _a*u*z - _a*w*z - _a*x*z - _a*y*z + _a*z2;
  A = 2*_a3 - _a2*u - _a*u2 - _a2*v + _a*u*v - _a*v2 - _a2*w + 
    _a*u*w + _a*v*w - _a*w2 - _a2*x + _a*u*x + _a*v*x + u*v*x - 
    u*w*x - v*w*x + w2*x - _a*x2 + w*x2 - _a2*y + u2*y + 
    _a*v*y - u*v*y + _a*w*y - u*w*y + v*w*y + _a*x*y - u*x*y - 
    w*x*y - _a*y2 + u*y2 - _a2*z + _a*u*z - u*v*z + v2*z + 
    _a*w*z + u*w*z - v*w*z + _a*x*z - v*x*z - w*x*z + _a*y*z - 
    u*y*z - v*y*z + x*y*z - _a*z2 + v*z2;

  B2 = B*B;
  B3 = B2*B;
  A2 = A*A;

  r1 = -B/(3.*A) - (CUBERT2*(-B2 + 3*A*C))/
    (3.*A*TVIL_CPOW(-2*B3 + 9*A*B*C - 27*A2*D + 
	   TVIL_CSQRT(4*TVIL_CPOW(-B2 + 3*A*C,3) + 
	TVIL_CPOW(-2*B3 + 9*A*B*C - 27*A2*D,2)), 1.L/3.L)) + 
    TVIL_CPOW(-2*B3 + 9*A*B*C - 27*A2*D + 
     TVIL_CSQRT(4*TVIL_CPOW(-B2 + 3*A*C,3) + 
       TVIL_CPOW(-2*B3 + 9*A*B*C - 27*A2*D,2)), 1.L/3.L)/
    (3.*CUBERT2*A);

  r2 = -B/(3.*A) + ((1 + I*SQRT3)*(-B2 + 3*A*C))/
    (3.*CUBERT2*CUBERT2*A*
     TVIL_CPOW(-2*B3 + 9*A*B*C - 27*A2*D + 
      TVIL_CSQRT(4*TVIL_CPOW(-B2 + 3*A*C,3) + 
	   TVIL_CPOW(-2*B3 + 9*A*B*C - 27*A2*D,2)), 1.L/3.L)) - 
    ((1 - I*SQRT3)*TVIL_CPOW(-2*B3 + 9*A*B*C - 27*A2*D + 
      TVIL_CSQRT(4*TVIL_CPOW(-B2 + 3*A*C,3) + 
          TVIL_CPOW(-2*B3 + 9*A*B*C - 27*A2*D,2)), 1.L/3.L))/
    (6.*CUBERT2*A);

  r3 = -B/(3.*A) + ((1 - I*SQRT3)*(-B2 + 3*A*C))/
    (3.*CUBERT2*CUBERT2*A*
     TVIL_CPOW(-2*B3 + 9*A*B*C - 27*A2*D + 
      TVIL_CSQRT(4*TVIL_CPOW(-B2 + 3*A*C,3) + 
	  TVIL_CPOW(-2*B3 + 9*A*B*C - 27*A2*D,2)), 1.L/3.L)) - 
      ((1 + I*SQRT3)*TVIL_CPOW(-2*B3 + 9*A*B*C - 27*A2*D + 
          TVIL_CSQRT(4*TVIL_CPOW(-B2 + 3*A*C,3) + 
        TVIL_CPOW(-2*B3 + 9*A* B*C - 27*A2*D,2)), 1.L/3.L))/
      (6.*CUBERT2*A);

  /* printf("r1 = "); TVIL_cprintfM (r1); printf("\n"); */
  /* printf("r2 = "); TVIL_cprintfM (r2); printf("\n"); */
  /* printf("r3 = "); TVIL_cprintfM (r3); printf("\n"); */

  /* exit(0); */

  *(result)   = TVIL_CREAL(r1);
  *(result+1) = TVIL_CREAL(r2);
  *(result+2) = TVIL_CREAL(r3);

  return;
}
