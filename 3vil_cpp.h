/* 3VIL v2.02 */

/* General header file for the user API and all 3VIL types.  This file
   should be included in all C++ applications wishing to use 3VIL. */

#ifndef TVIL_CPP_H
#define TVIL_CPP_H

#include "3vil.h"
#include <complex>

#ifdef complex
#undef complex
#endif

typedef    std::complex<long double> TVIL_COMPLEXCPP;
#ifndef I
#define I  (std::complex<long double>(0.0L, 1.0L))
#endif


// ==================================================================
//    C++ wrappers
// ==================================================================
// General wrapper for C functions returning a complex:
TVIL_COMPLEXCPP c2cpp (const TVIL_COMPLEX& cval)
{
  return *((TVIL_COMPLEXCPP*) (&cval));
}

// Specific wrappers for existing TVIL functions:
// ==================================================================
int TVIL_Evaluate_ (TVIL_REAL u, TVIL_REAL v, TVIL_REAL w,
		    TVIL_REAL x, TVIL_REAL y, TVIL_REAL z,
		    TVIL_REAL qq, 
		    TVIL_RESULT *foo)
{
  return TVIL_Evaluate (u, v, w, x, y, z, qq, foo);
}
// ==================================================================
int TVIL_EvaluateEFG_ (TVIL_REAL u, TVIL_REAL v, TVIL_REAL w,
		       TVIL_REAL x, TVIL_REAL y,
		       TVIL_REAL qq,
		       TVIL_RESULT * foo)
{
  return TVIL_EvaluateEFG (u, v, w, x, y, qq, foo);
}
// ==================================================================
int TVIL_EvaluateEF_ (TVIL_REAL u, TVIL_REAL w, TVIL_REAL x,
		      TVIL_REAL y,
		      TVIL_REAL qq,
		      TVIL_RESULT *foo)
{
  return TVIL_EvaluateEF (u, w, x, y, qq, foo);
}
// ==================================================================
TVIL_COMPLEXCPP TVIL_GetFunction_ (TVIL_RESULT *foo, const char *which)
{
  return c2cpp (TVIL_GetFunction (foo, which));
}
// ==================================================================
TVIL_COMPLEXCPP TVIL_GetBoldFunction_ (TVIL_RESULT *foo, const char *which, int m)
{
  return c2cpp (TVIL_GetBoldFunction (foo, which, m));
}
// ==================================================================
// I/O and related functions:
void TVIL_PrintData_ (TVIL_RESULT *foo)
{
  TVIL_PrintData (foo);
}
// ==================================================================
void TVIL_WriteData_ (FILE *fp, TVIL_RESULT *foo)
{
  TVIL_WriteData (fp, foo);
}
// ==================================================================
void TVIL_Error_ (const char *foo, const char *bar, int m)
{
  TVIL_Error (foo, bar, m);
}
// ==================================================================
void TVIL_Warn_ (char *foo, char *bar)
{
  TVIL_Warn (foo, bar);
}
// ==================================================================
void TVIL_WarnsOff_ (void)
{
  TVIL_WarnsOff ();
}
// ==================================================================
void TVIL_WarnsOn_ (void)
{
  TVIL_WarnsOn ();
}
// ==================================================================
void TVIL_SetPrintBold_ (void)
{
  TVIL_SetPrintBold ();
}
// ==================================================================
void TVIL_UnsetPrintBold_ (void)
{
  TVIL_UnsetPrintBold ();
}
// ==================================================================
void TVIL_cfprintf_ (FILE *fp, TVIL_COMPLEXCPP z)
{
  TVIL_COMPLEX zz = *((TVIL_COMPLEX*) (&z));
  TVIL_cfprintf (fp, zz);
}
// ==================================================================
void TVIL_cprintf_ (TVIL_COMPLEXCPP z)
{
  TVIL_COMPLEX zz = *((TVIL_COMPLEX*) (&z));
  TVIL_cprintf (zz);
}
// ==================================================================
void TVIL_Setup_ (void)
{
  return TVIL_Setup ();
}
// ==================================================================
int TVIL_GetStatus_ (TVIL_RESULT *foo)
{
  return TVIL_GetStatus (foo);
}
// ==================================================================
int  TVIL_IsInfinite_ (TVIL_COMPLEXCPP z)
{
  TVIL_COMPLEX zz = *((TVIL_COMPLEX*) (&z));
  return TVIL_IsInfinite (zz);
}
// ==================================================================
void TVIL_PrintStatus_ (TVIL_RESULT *foo)
{
  TVIL_PrintStatus (foo);
}
// ==================================================================
void TVIL_PrintVersion_ (void)
{
  TVIL_PrintVersion ();
}
// ==================================================================
void TVIL_SetPrintStyle_ (int style)
{
  TVIL_SetPrintStyle (style);
}
// ==================================================================
void TVIL_ResetStepSizeParams_ (TVIL_REAL z, int i, int j, int k, int l)
{
  TVIL_ResetStepSizeParams (z, i, j, k, l);
}
// ==================================================================
void TVIL_Set_aParameter_ (TVIL_REAL newval)
{
  TVIL_Set_aParameter (newval);
}
// ==================================================================
void TVIL_SetContourDisplacement_ (TVIL_REAL newval)
{
  TVIL_SetContourDisplacement (newval);
}
// ==================================================================
void TVIL_Set_tInitial_ (TVIL_REAL newval)
{
  TVIL_Set_tInitial (newval);
}
// ==================================================================
void TVIL_SetDoAnalytic_ (void)
{
  TVIL_SetDoAnalytic ();
}
// ==================================================================
void TVIL_UnsetDoAnalytic_ (void)
{
  TVIL_UnsetDoAnalytic ();
}
// ==================================================================
void TVIL_SetForceContour_ (void)
{
  TVIL_SetForceContour ();
}
// ==================================================================
void TVIL_UnsetForceContour_ (void)
{
  TVIL_UnsetForceContour ();
}
// ==================================================================
void TVIL_SetForceDefault_ (void)
{
  TVIL_SetForceDefault ();
}
// ==================================================================
void TVIL_UnsetForceDefault_ (void)
{
  TVIL_UnsetForceDefault ();
}
// ==================================================================
void TVIL_PermuteResult_ (TVIL_RESULT *a, int p, TVIL_RESULT *b)
{
  TVIL_PermuteResult (a, p, b);
}
// ==================================================================
int TVIL_InversePerm_ (int p)
{
  return TVIL_InversePerm (p);
}
// ==================================================================
TVIL_COMPLEXCPP TVIL_Dilog_ (TVIL_COMPLEX z)
{
  TVIL_COMPLEX zz = *((TVIL_COMPLEX*) (&z));
  return c2cpp (TVIL_Dilog (zz));
}
// ==================================================================
TVIL_COMPLEXCPP TVIL_Trilog_ (TVIL_COMPLEX z)
{
  TVIL_COMPLEX zz = *((TVIL_COMPLEX*) (&z));
  return c2cpp (TVIL_Trilog (zz));
}
// ==================================================================
TVIL_COMPLEXCPP TVIL_A_ (TVIL_REAL x, TVIL_REAL qq) 
{
  return c2cpp (TVIL_A (x, qq));
}
// ==================================================================
TVIL_COMPLEXCPP TVIL_Aeps_ (TVIL_REAL x, TVIL_REAL qq)
{
  return c2cpp (TVIL_Aeps (x, qq));
}
// ==================================================================
TVIL_COMPLEXCPP TVIL_Aeps2_ (TVIL_REAL x, TVIL_REAL qq)
{
  return c2cpp (TVIL_Aeps2 (x, qq));
}
// ==================================================================
TVIL_COMPLEXCPP TVIL_I2_ (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL qq)
{
  return c2cpp (TVIL_I2 (x, y, z, qq));
}
// ==================================================================
TVIL_COMPLEXCPP TVIL_II2_ (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL qq)
{
  return c2cpp (TVIL_II2 (x, y, z, qq));
}
// ==================================================================
TVIL_COMPLEXCPP TVIL_II1_ (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL qq)
{
  return c2cpp (TVIL_II1 (x, y, z, qq));
}
// ==================================================================
TVIL_COMPLEXCPP TVIL_II0_ (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL qq)
{
  return c2cpp (TVIL_II0 (x, y, z, qq));
}
// ==================================================================
TVIL_COMPLEXCPP TVIL_Ieps_ (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL qq)
{
  return c2cpp (TVIL_Ieps (x, y, z, qq));
}
// ==================================================================
// We could just cast the return pointer, e.g.,
//    return TVIL_FBARanalytic (x, y, z, u, qq, (TVIL_COMPLEX *) res);
// (which seems to work) but this seems safer albeit more complicated:

int TVIL_FBARanalytic_ (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL u,
			TVIL_REAL qq, TVIL_COMPLEXCPP *res)
{
  TVIL_COMPLEX cres;
  int retval;

  retval = TVIL_FBARanalytic (x, y, z, u, qq, &cres);
  *res = *((TVIL_COMPLEXCPP *) (&cres));
  return retval;
}
// ==================================================================
int TVIL_Fanalytic_ (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL u,
		     TVIL_REAL qq, TVIL_COMPLEXCPP *res)
{
  TVIL_COMPLEX cres;
  int retval;

  retval = TVIL_Fanalytic (x, y, z, u, qq, &cres);
  *res = *((TVIL_COMPLEXCPP *) (&cres));
  return retval;
}
// ==================================================================
int TVIL_Ganalytic_ (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z, TVIL_REAL u,
		     TVIL_REAL v, TVIL_REAL qq, TVIL_COMPLEXCPP *res)
{
  TVIL_COMPLEX cres;
  int retval;

  retval = TVIL_Ganalytic (x, y, z, u, v, qq, &cres);
  *res = *((TVIL_COMPLEXCPP *) (&cres));
  return retval;
}
// ==================================================================
int TVIL_Hanalytic_ (TVIL_REAL x, TVIL_REAL y, TVIL_REAL z,
		     TVIL_REAL u, TVIL_REAL v, TVIL_REAL w,
		     TVIL_REAL qq, TVIL_COMPLEXCPP *res)
{
  TVIL_COMPLEX cres;
  int retval;

  retval = TVIL_Hanalytic (x, y, z, u, v, w, qq, &cres);
  *res = *((TVIL_COMPLEXCPP *) (&cres));
  return retval;
}

#endif // TVIL_CPP_H
