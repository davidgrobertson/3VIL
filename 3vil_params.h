#ifndef TVIL_PARAMS_H
#define TVIL_PARAMS_H

/* This file contains parameters associated with the numerical
   integration in TVIL */

/* The macros TVIL_PRECISION_GOAL, TVIL_NSTEPS_START,
   TVIL_NSTEPS_MAX_CON, TVIL_NSTEPS_MAX_VAR, and TVIL_NSTEPS_MIN are
   used by TVIL_SetParameters to set the corresponding members of the
   data struct. To reset them at run time, use the function
   TVIL_ResetStepSizeParams after calling TVIL_SetParameters */

#define TVIL_PRECISION_GOAL 1e-12
/* For each RK step, require that the estimated error for each
   dependent variable is less than TVIL_PRECISION_GOAL times the
   increment of that dependent variable for that step. Otherwise, the
   step size is reduced and the step is retried.  This requirement is
   ignored if the step size gets too small, or if the estimated error
   is less than TVIL_EPSILON [DGR - TVIL_TOL?] times the absolute value of the dependent
   variable. If TVIL_PRECISION_GOAL is set to 0, the step sizes will
   be determined by TVIL_NSTEPS_MAX_CON and TVIL_NSTEPS_MAX_VAR below.
   If TVIL_PRECISION_GOAL is set to a large number, the step sizes
   will tend towards that given by TVIL_NSTEPS_MIN below. */

#define TVIL_MIN_STEP_SIZE 0.000005L

#define TVIL_NSTEPS_START 500
/* For each leg of the contour of the RK integration, the initial step
   size is chosen so that there would be 500 total steps if the step
   size did not change. */

#define TVIL_NSTEPS_MAX_CON 10000
#define TVIL_NSTEPS_MAX_VAR 10000
#define TVIL_NSTEPS_MIN     100
/* The minimum step size for a leg of the contour with dimensionless
   rescaled independent variable length L is given by:

   L/(N_STEPS_MAX_CON + L * N_STEPS_MAX_VAR).

   The maximum step size is L/NSTEPS_MIN. */

#define IM_DISPL 0.8L
/* Contour displacement in Im(t) direction to avoid thresholds. */

#define THRESH_CUTOFF 0.0001L
/* Maximum distance considered "close" to a pole. */

#define T_INIT 0.013L
/* Starting displacement from t=0 for integration. */

#define DEFAULTMAXFINALSTEP 8.e-6L

#define THREESCALE_ENDPOINT 1.e-9

#define DOANALYTIC YES
/* This is the default value. If YES (NO), program does (does not)
   look for analytic subcases even when the H integral cannot be done
   analytically. */

/* Set default behaviors for printing of results: */
#define PRINTWARNS_DEFAULT YES
#define PRINTBOLD_DEFAULT  NO
#define PRINTSTYLE_DEFAULT MATH

#endif /* TVIL_PARAMS_H */
