/*

  basecalc.cpp
  ============
  This program implements the most general 3VIL calculation: it takes
  input values of u, v, w, x, y, z, qq (as command line arguments, in
  that order) and prints the values of all integral functions, General
  and timing information for the computation are also printed.

  Compile as, e.g.

  g++ -o 3vil basecalc.cpp -L. -l3vil

  (assuming lib3vil.a is in the current directory) and run as

  ./3vil 1 2 3 4 5 6 1

*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <complex>
#include <vector>
#include <cmath>
#include <cfloat>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "3vil_cpp.h"  // Required TVIL header file

#ifndef PI
#define PI 4.0L*atan(1.0L)
#endif

int main (int argc, char *argv[])
{
  TVIL_RESULT result;
  TVIL_REAL x, y, z, u, v, w, qq;
  clock_t t0, t1;

  std::complex<long double> res;

  if (argc != 8)
    TVIL_Error_ ("main", "Incorrect number of args; should be 7", 1);

  // Get input parameters
  u  = (TVIL_REAL) strtold(argv[1], (char **) NULL);
  v  = (TVIL_REAL) strtold(argv[2], (char **) NULL);
  w  = (TVIL_REAL) strtold(argv[3], (char **) NULL);
  x  = (TVIL_REAL) strtold(argv[4], (char **) NULL);
  y  = (TVIL_REAL) strtold(argv[5], (char **) NULL);
  z  = (TVIL_REAL) strtold(argv[6], (char **) NULL);
  qq = (TVIL_REAL) strtold(argv[7], (char **) NULL);

  TVIL_Setup_ ();

  // Evaluate functions
  t0 = clock ();
  TVIL_Evaluate_ (u, v, w, x, y, z, qq, &result);
  t1 = clock ();

  /* Choose to print bold fuctions: */
  // TVIL_SetPrintBold_ ();
  // TVIL_UnsetPrintBold_ ();

  // Output general information and results
  TVIL_PrintVersion_ ();
  TVIL_PrintStatus_ (&result);
  TVIL_PrintData_ (&result);

  cout << "\nTotal calculation time (s): " << difftime(t1, t0)/CLOCKS_PER_SEC << endl;

  return 0;
}
