/* Definitions needed by the Fortran interface (fevaluate.c) */

#ifndef _TVIL_FORTRAN_H_
#define _TVIL_FORTRAN_H_

/*
  These values must match the types used in the calling Fortran
  programs.  TVIL_REAL_SIZE_F should be set to the size in bytes of
  the TVIL_REAL_F type. The calling Fortran program should then use
  REAL type

  REAL*(TVIL_FORT_SIZE) 
*/

/* Uncomment the following if your FORTRAN program uses
   REAL*16/COMPLEX*32 */
/*  #define TVIL_REAL_F       long double */
/*  #define TVIL_COMPLEX_F    long double complex */
/*  #define TVIL_REAL_SIZE_F  16 */

/* Otherwise assume REAL*8 as the type used by the Fortran program: */
#define TVIL_REAL_F       double
#define TVIL_COMPLEX_F    double complex
#define TVIL_REAL_SIZE_F  8

#endif /* 3vil_fortran.h */
