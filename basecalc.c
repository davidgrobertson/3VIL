/* 

   basecalc.c
   ==========
   This program implements the most general 3VIL calculation: it takes
   input values of u, v, w, x, y, z, qq (as command line arguments, in
   that order) and prints the values of all integral functions,
   General and timing information for the computation are also
   printed.

   Compile as, e.g.

   gcc -o 3vil basecalc.c -L. -l3vil -lm

   (assuming lib3vil.a is in the current directory) and run as

   ./3vil 1 2 3 4 5 6 1

   This also shows the use of the subset evaulation routines
   TVIL_EvaluateEFG and TVIL_EvaluateEF (see below).

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "3vil.h"

int main (int argc, char *argv[])
{
  TVIL_RESULT result;
  TVIL_REAL x, y, z, u, v, w, qq;
  clock_t t0, t1;
  int i;

  if (argc != 8)
    TVIL_Error ("main", "Incorrect number of args; should be 7", 1);

  for (i=1; i<8; i++)
    if (!TVIL_IsNumeric (argv[i])) {
      TVIL_Error ("main", "One of the command-line arguments is not numeric.", 2);
    }

  /* Get input parameters */
  u  = (TVIL_REAL) strtold(argv[1], (char **) NULL);
  v  = (TVIL_REAL) strtold(argv[2], (char **) NULL);
  w  = (TVIL_REAL) strtold(argv[3], (char **) NULL);
  x  = (TVIL_REAL) strtold(argv[4], (char **) NULL);
  y  = (TVIL_REAL) strtold(argv[5], (char **) NULL);
  z  = (TVIL_REAL) strtold(argv[6], (char **) NULL);
  qq = (TVIL_REAL) strtold(argv[7], (char **) NULL);

  /* Evaluate functions: */
  t0 = clock ();
  TVIL_Evaluate (u, v, w, x, y, z, qq, &result);
  /* TVIL_EvaluateEFG (u, v, w, x, y, qq, &result); */
  /* TVIL_EvaluateEF (u, w, x, y, qq, &result); */
  t1 = clock ();

  /* Choose print options: */
  /* TVIL_SetPrintBold (); */
  /* TVIL_SetPrintStyle (PLAIN); */

  /* Output general information and results: */
  TVIL_PrintVersion ();
  TVIL_PrintStatus (&result);
  TVIL_PrintData (&result);

  printf("\n(* Total calculation time (s): %lf *)\n",
  	 difftime(t1, t0)/CLOCKS_PER_SEC);

  return 0;
}
