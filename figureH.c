/*   === figureH.c ===
 *
 *   Sample code for calculation of figure showing various H values. 
 *
 *   To compile:
 *
 *   cc -o figureH figureH.c -L<dir> -l3vil -lm
 *
 *   where <dir> is the directory containing lib3vil.a. 
 *
 *   Run as: ./figureH > figureH.dat
 */

#include <stdio.h>
#include "3vil.h"  /* Required TSIL header file */

int main (int argc, char *argv[])
{
  TVIL_RESULT    result; /* Top-level TSIL data object */

  TVIL_REAL x;
  TVIL_REAL Q2 = 1;

  TVIL_COMPLEX Hxxxxx1, Hxx11xx, Hxx1x11, Hx111x1, Hx11111;
  TVIL_COMPLEX H0000x1, H000xx1, H00xxx1, H0xxx1x, H01xxx1;
  TVIL_COMPLEX H0x11x1, H0111x1;

  int i;
  int Npoints = 151;

  TVIL_REAL x_input_table[] = {0, 0.0002, 0.0004, 0.0006, 0.0008, 0.001, 0.002,
    0.003, 0.004, 0.005, 0.006, 0.008, 0.01, 0.015, 0.02, 0.025, 0.03, 0.035, 
    0.04, 0.045, 0.05, 0.055, 0.06, 0.065, 0.07, 0.075, 0.08, 0.085, 0.09, 
    0.095, 0.1, 0.105, 0.11, 0.115, 0.12, 0.125, 0.13, 0.135, 0.14, 0.145, 
    0.15, 0.155, 0.16, 0.165, 0.17, 0.175, 0.18, 0.185, 0.19, 0.195, 0.2, 
    0.205, 0.21, 0.215, 0.22, 0.225, 0.23, 0.235, 0.24, 0.245, 0.25, 0.255, 
    0.26, 0.265, 0.27, 0.275, 0.28, 0.285, 0.29, 0.295, 0.3, 0.305, 0.31,
    0.315, 0.32, 0.325, 0.33, 0.335, 0.34, 0.345, 0.35, 0.355, 0.36, 0.365, 
    0.37, 0.375, 0.38, 0.385, 0.39, 0.395, 0.4, 0.41, 0.42, 0.43, 0.44, 0.45,
    0.46, 0.47, 0.48, 0.49, 0.5, 0.51, 0.52, 0.53, 0.54, 0.55, 0.56, 0.57, 
    0.58, 0.59, 0.6, 0.61, 0.62, 0.63, 0.64, 0.65, 0.66, 0.67, 0.68, 0.69, 
    0.7, 0.71, 0.72, 0.73, 0.74, 0.75, 0.76, 0.77, 0.78, 0.79, 0.8, 0.81, 
    0.82, 0.83, 0.84, 0.85, 0.86, 0.87, 0.88, 0.89, 0.9, 0.91, 0.92, 0.93, 
    0.94, 0.95, 0.96, 0.97, 0.98, 0.99, 1};

  printf("# Data for left panel of figure. \n");
  printf("# Column 1 = x \n");
  printf("# Column 2 = H(x,x,x,x,x,1) \n");
  printf("# Column 3 = H(x,x,1,1,x,x) \n");
  printf("# Column 4 = H(x,x,1,x,1,1) \n");
  printf("# Column 5 = H(x,1,1,1,x,1) \n");
  printf("# Column 6 = H(x,1,1,1,1,1) \n");

  for (i = 0; i < Npoints; i++) {
    x = x_input_table[i];

    TVIL_Evaluate (x, x, x, x, x, 1, Q2, &result);
    Hxxxxx1 = TVIL_CREAL(TVIL_GetFunction (&result, "H"));

    TVIL_Evaluate (x, x, 1, 1, x, x, Q2, &result);
    Hxx11xx = TVIL_CREAL(TVIL_GetFunction (&result, "H"));

    TVIL_Evaluate (x, x, 1, x, 1, 1, Q2, &result);
    Hxx1x11 = TVIL_CREAL(TVIL_GetFunction (&result, "H"));

    TVIL_Evaluate (x, 1, 1, 1, x, 1, Q2, &result);
    Hx111x1 = TVIL_CREAL(TVIL_GetFunction (&result, "H"));

    TVIL_Evaluate (x, 1, 1, 1, 1, 1, Q2, &result);
    Hx11111 = TVIL_CREAL(TVIL_GetFunction (&result, "H"));

    printf("%6.4lf %12.10lf %12.10lf %12.10lf %12.10lf %12.10lf\n", 
      (double) x, 
      creal(Hxxxxx1),
      creal(Hxx11xx),
      creal(Hxx1x11),
      creal(Hx111x1),
      creal(Hx11111));
  }

  printf("\n");

  printf("# Data for right panel of figure. \n");
  printf("# Column 1 = x \n");
  printf("# Column 2 = H(0,0,0,0,x,1) \n");
  printf("# Column 3 = H(0,0,0,x,x,1) \n");
  printf("# Column 4 = H(0,0,x,x,x,1) \n");
  printf("# Column 5 = H(0,x,x,x,1,x) \n");
  printf("# Column 6 = H(0,1,x,x,x,1) \n");
  printf("# Column 7 = H(0,x,1,1,x,1) \n");
  printf("# Column 8 = H(0,1,1,1,x,1) \n");

  for (i = 0; i < Npoints; i++) {
    x = x_input_table[i];

    TVIL_Evaluate (0, 0, 0, 0, x, 1, Q2, &result);
    H0000x1 = TVIL_CREAL(TVIL_GetFunction (&result, "H"));

    TVIL_Evaluate (0, 0, 0, x, x, 1, Q2, &result);
    H000xx1 = TVIL_CREAL(TVIL_GetFunction (&result, "H"));

    TVIL_Evaluate (0, 0, x, x, x, 1, Q2, &result);
    H00xxx1 = TVIL_CREAL(TVIL_GetFunction (&result, "H"));

    TVIL_Evaluate (0, x, x, x, 1, x, Q2, &result);
    H0xxx1x = TVIL_CREAL(TVIL_GetFunction (&result, "H"));

    TVIL_Evaluate (0, 1, x, x, x, 1, Q2, &result);
    H01xxx1 = TVIL_CREAL(TVIL_GetFunction (&result, "H"));

    TVIL_Evaluate (0, x, 1, 1, x, 1, Q2, &result);
    H0x11x1 = TVIL_CREAL(TVIL_GetFunction (&result, "H"));

    TVIL_Evaluate (0, 1, 1, 1, x, 1, Q2, &result);
    H0111x1 = TVIL_CREAL(TVIL_GetFunction (&result, "H"));

    printf("%6.4lf %12.10lf %12.10lf %12.10lf %12.10lf %12.10lf %12.10lf %12.10lf\n", 
      (double) x, 
      creal(H0000x1),
      creal(H000xx1),
      creal(H00xxx1),
      creal(H0xxx1x),
      creal(H01xxx1),
      creal(H0x11x1),
      creal(H0111x1));
  }

  return 0;
} 
  
