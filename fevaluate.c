/* 
   === fevaluate.c ===

   This is a simple wrapper routine that provides an interface to
   Fortran.  In the Fortran program, include the header
   '3vil_fort.inc'; this defines a common block corresponding to the
   struct below.  One then calls the subroutine

   CALL tvilfevaluate(...)

   defined herein, to evaluate the basis integrals.  

   This code can serve as a model if users are interested in writing
   their own variants with more specialized capabilities.  See the
   file README.txt for detailed notes on the issues involved.
*/

#include "internal.h"
#include "3vil_fortran.h"

/* This struct is used to pass the results of the calculation back to
   the calling program; it matches the data COMMON block defined in
   3vil_fort.inc.  Note that the type sizes MUST agree between them;
   the struct and COMMON block must have the same memory footprint. */

struct {

  /* Basic functions */
  TVIL_COMPLEX_F II[NUM_I_FUNCS];
  TVIL_COMPLEX_F FBAR[NUM_F_FUNCS];
  TVIL_COMPLEX_F F[NUM_F_FUNCS];
  TVIL_COMPLEX_F E[NUM_E_FUNCS];
  TVIL_COMPLEX_F G[NUM_G_FUNCS];
  TVIL_COMPLEX_F H;

  /* Bold functions: */
  TVIL_COMPLEX_F III[NUM_I_FUNCS][3];
  TVIL_COMPLEX_F FF[NUM_F_FUNCS][4];
  TVIL_COMPLEX_F EE[NUM_E_FUNCS][4];
  TVIL_COMPLEX_F GG[NUM_G_FUNCS][4];
  TVIL_COMPLEX_F HH[2];

} tvilresults_;

/* For check that data types match (not foolproof!) */
struct {
  int rsize;
} tvilrsize_;

/* ******************************************************************* */
/* Generic wrapper function                                            */

void tvilfevaluate_ (TVIL_REAL_F *u, 
		     TVIL_REAL_F *v,
		     TVIL_REAL_F *w,
		     TVIL_REAL_F *x,
		     TVIL_REAL_F *y,
		     TVIL_REAL_F *z,
		     TVIL_REAL_F *qq)
{
#include "3vil_names.h"

  TVIL_RESULT res;
  int i, j;
  static int compiledSize = TVIL_REAL_SIZE_F;

  if (tvilrsize_.rsize != compiledSize)
    TVIL_Warn ("tvilfevaluate", "Apparent type mismatch between Fortran and C!");

  TVIL_Evaluate ((TVIL_REAL) (*u),
		 (TVIL_REAL) (*v),
		 (TVIL_REAL) (*w), 
		 (TVIL_REAL) (*x),
		 (TVIL_REAL) (*y),
		 (TVIL_REAL) (*z),
		 (TVIL_REAL) (*qq),
		 &res);

  /* Extract results */
  tvilresults_.H = (TVIL_COMPLEX_F) TVIL_GetFunction (&res, "H");

  /* Note non-standard indexing-by-pointer of bold function arrays for
     compatibility with Fortran indexing convention. */
  for (j=0; j<2; j++)
    tvilresults_.HH[j] = (TVIL_COMPLEX_F) TVIL_GetBoldFunction (&res, "H", j);

  for (i=0; i<NUM_G_FUNCS; i++) {
    tvilresults_.G[i] = (TVIL_COMPLEX_F) TVIL_GetFunction (&res, gname[i][0]);
    for (j=0; j<4; j++)
      *(&(tvilresults_.GG[0][0]) + j * NUM_G_FUNCS + i) = 
        (TVIL_COMPLEX_F) TVIL_GetBoldFunction (&res, gname[i][0], j);
  }

  for (i=0; i<NUM_E_FUNCS; i++) {
    tvilresults_.E[i] = (TVIL_COMPLEX_F) TVIL_GetFunction (&res, ename[i][0]);
    for (j=0; j<4; j++)
      *(&(tvilresults_.EE[0][0]) + j * NUM_E_FUNCS + i) = 
        (TVIL_COMPLEX_F) TVIL_GetBoldFunction (&res, ename[i][0], j);
  }

  for (i=0; i<NUM_F_FUNCS; i++) {
    tvilresults_.FBAR[i] = (TVIL_COMPLEX_F) TVIL_GetFunction (&res, fbarname[i][0]);
    tvilresults_.F[i] = (TVIL_COMPLEX_F) TVIL_GetFunction (&res, fname[i][0]);
    for (j=0; j<4; j++)
      *(&(tvilresults_.FF[0][0]) + j * NUM_F_FUNCS + i) = 
        (TVIL_COMPLEX_F) TVIL_GetBoldFunction (&res, fname[i][0], j);
  }

  for (i=0; i<NUM_I_FUNCS; i++) {
    tvilresults_.II[i] = (TVIL_COMPLEX_F) TVIL_GetFunction (&res, iname[i][0]);
    for (j=0; j<3; j++)
      *(&(tvilresults_.III[0][0]) + j * NUM_I_FUNCS + i) = 
        (TVIL_COMPLEX_F) TVIL_GetBoldFunction (&res, iname[i][0], j);
  }

  return;
}
