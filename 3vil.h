#define TVIL_VERSION "2.02"

/* General header file for the user API and all 3VIL types.  This file
   must be included in all applications of 3VIL.  */

#ifndef _TVIL_H_
#define _TVIL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <complex.h>

/* ========= Basic Datatype Definitions ========= */

typedef long double          TVIL_REAL;
typedef long double _Complex TVIL_COMPLEX;
#define TVIL_EXP             expl
#define TVIL_CEXP            cexpl
#define TVIL_LOG             logl
#define TVIL_CLOG            clogl
#define TVIL_FABS            fabsl
#define TVIL_CABS            cabsl
#define TVIL_SQRT            sqrtl
#define TVIL_CSQRT           csqrtl
#define TVIL_POW             powl
#define TVIL_CPOW            cpowl
#define TVIL_ATAN            atanl
#define TVIL_ATAN2           atan2l
#define TVIL_CREAL           creall
#define TVIL_CIMAG           cimagl
#define TVIL_CONJ            conjl
#define TVIL_EPSILON         LDBL_EPSILON
#define TVIL_TOL             1000.0L*LDBL_EPSILON

/* Number of each type of function (could just be hardwired) */
#define NUM_I_FUNCS 16
#define NUM_F_FUNCS 12
#define NUM_E_FUNCS 3
#define NUM_G_FUNCS 6

/* ======================================== */
/*          Results Data Structure          */
/* ======================================== */
struct TVIL_Result
{
  TVIL_REAL u, v, w, x, y, z, qq;

  /* These record which functions are to be evaluated: */
  int evaluateII[NUM_I_FUNCS];
  int evaluateFBAR[NUM_F_FUNCS];
  int evaluateE[NUM_E_FUNCS];
  int evaluateG[NUM_G_FUNCS];
  int evaluateH;

  int nIfuns, nFBARfuns, nEfuns, nGfuns, nHfuns;

  /* The function values: */
  TVIL_COMPLEX    II[NUM_I_FUNCS];
  TVIL_COMPLEX  FBAR[NUM_F_FUNCS];
  TVIL_COMPLEX     F[NUM_F_FUNCS];
  TVIL_COMPLEX     E[NUM_E_FUNCS];
  TVIL_COMPLEX     G[NUM_G_FUNCS];
  TVIL_COMPLEX     H;

  /* Bold function values: */
  TVIL_COMPLEX    IIbold[NUM_I_FUNCS][3];
  TVIL_COMPLEX     Fbold[NUM_F_FUNCS][4];
  TVIL_COMPLEX     Ebold[NUM_E_FUNCS][4];
  TVIL_COMPLEX     Gbold[NUM_G_FUNCS][4];
  TVIL_COMPLEX     Hbold[2];

  TVIL_COMPLEX    IIderiv[NUM_I_FUNCS];
  TVIL_COMPLEX  FBARderiv[NUM_F_FUNCS];
  TVIL_COMPLEX     Gderiv[NUM_G_FUNCS];
  TVIL_COMPLEX     Hderiv;

  int evalMode;      /* Indicates which set of functions is to be
			evaluated (i.e., ALL=EFGH, EFG, EF).  See
			3vil_global.h for details */

  int poleAt1;       /* YES/NO depending on whether there is a pole
			near t=1. */

  int status;        /* Current evaluation status: whether evaluated
                        and, if so, how (see 3vil_global.h for value
                        definitions). */
};

typedef struct TVIL_Result TVIL_RESULT;

/* === Prototypes for functions in the user API: === */

/* Basic evaluation functions: */
int TVIL_Evaluate (TVIL_REAL, TVIL_REAL, TVIL_REAL, TVIL_REAL,
		   TVIL_REAL, TVIL_REAL, TVIL_REAL, TVIL_RESULT *);
int TVIL_EvaluateEFG (TVIL_REAL, TVIL_REAL, TVIL_REAL, TVIL_REAL,
		      TVIL_REAL, TVIL_REAL, TVIL_RESULT *);
int TVIL_EvaluateEF (TVIL_REAL, TVIL_REAL, TVIL_REAL, TVIL_REAL,
		     TVIL_REAL, TVIL_RESULT *);
TVIL_COMPLEX TVIL_GetFunction (TVIL_RESULT *, const char *);
TVIL_COMPLEX TVIL_GetBoldFunction (TVIL_RESULT *, const char *, int);

/* I/O and related functions: */
void TVIL_PrintData (TVIL_RESULT *);
void TVIL_WriteData (FILE *, TVIL_RESULT *);
void TVIL_Error (const char *, const char *, int);
void TVIL_Warn (const char *, const char *);
void TVIL_WarnsOff (void);
void TVIL_WarnsOn (void);
void TVIL_SetPrintBold (void);
void TVIL_UnsetPrintBold (void);
void TVIL_cfprintf (FILE *, TVIL_COMPLEX);
void TVIL_cprintf (TVIL_COMPLEX);

/* Utilities: */
int  TVIL_IsNumeric (const char *);
int  TVIL_GetStatus (TVIL_RESULT *);
int  TVIL_IsInfinite (TVIL_COMPLEX);
void TVIL_PrintStatus (TVIL_RESULT *);
void TVIL_PrintVersion (void);
void TVIL_SetPrintStyle (int);
void TVIL_ResetStepSizeParams (TVIL_REAL, int, int, int, int);
void TVIL_ResetStepSizeParamDefaults (void);
void TVIL_Set_aParameter (TVIL_REAL);
void TVIL_SetContourDisplacement (TVIL_REAL);
void TVIL_Set_tInitial (TVIL_REAL);
void TVIL_SetDoAnalytic (void);
void TVIL_UnsetDoAnalytic (void);
void TVIL_SetForceContour (void);
void TVIL_UnsetForceContour (void);
void TVIL_SetForceDefault (void);
void TVIL_UnsetForceDefault (void);
void TVIL_PermuteResult (TVIL_RESULT *, int, TVIL_RESULT *);
int  TVIL_InversePerm (int);

/* Analytic cases: */
TVIL_COMPLEX TVIL_Dilog (TVIL_COMPLEX);
TVIL_COMPLEX TVIL_Trilog (TVIL_COMPLEX);
TVIL_COMPLEX TVIL_A (TVIL_REAL, TVIL_REAL);
TVIL_COMPLEX TVIL_Aeps (TVIL_REAL, TVIL_REAL);
TVIL_COMPLEX TVIL_Aeps2 (TVIL_REAL, TVIL_REAL);
TVIL_COMPLEX TVIL_I2  (TVIL_REAL, TVIL_REAL, TVIL_REAL, TVIL_REAL);
TVIL_COMPLEX TVIL_II2 (TVIL_REAL, TVIL_REAL, TVIL_REAL, TVIL_REAL);
TVIL_COMPLEX TVIL_II1 (TVIL_REAL, TVIL_REAL, TVIL_REAL, TVIL_REAL);
TVIL_COMPLEX TVIL_II0 (TVIL_REAL, TVIL_REAL, TVIL_REAL, TVIL_REAL);
TVIL_COMPLEX TVIL_Ieps (TVIL_REAL, TVIL_REAL, TVIL_REAL, TVIL_REAL);
int TVIL_FBARanalytic (TVIL_REAL, TVIL_REAL, TVIL_REAL, TVIL_REAL, TVIL_REAL, TVIL_COMPLEX *);
int TVIL_Fanalytic (TVIL_REAL, TVIL_REAL, TVIL_REAL, TVIL_REAL, TVIL_REAL, TVIL_COMPLEX *);
int TVIL_Ganalytic (TVIL_REAL, TVIL_REAL, TVIL_REAL, TVIL_REAL, TVIL_REAL, TVIL_REAL, TVIL_COMPLEX *);
int TVIL_Hanalytic (TVIL_REAL, TVIL_REAL, TVIL_REAL, TVIL_REAL, TVIL_REAL, TVIL_REAL, TVIL_REAL, TVIL_COMPLEX *);

#ifdef __cplusplus
}
#endif

#endif /* 3vil.h */
