/* General header for "internal" use */

#ifndef INTERNAL_H
#define INTERNAL_H

#include "3vil.h"
#include "3vil_globaldata.h"
#include "3vil_datatypes.h"
#include "3vil_funcs.h"
#include "3vil_global.h"
#include "3vil_params.h"

#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

#ifndef PI
#define PI      3.1415926535897932385L
#endif
#define PI2     9.8696044010893586188L
#define LN2     0.69314718055994530942L
#define SQRT2   1.4142135623730950488L
#define SQRT3   1.7320508075688772935L
#define CUBERT2 1.2599210498948731648L
#define Zeta2   1.644934066848226436472415166646025189219L
#define Zeta3   1.202056903159594285399738161511449990765L
#define LS2     0.67662773760643575001413503618301352396112620502020L
#define LS3    -2.1447672125694943914826421122153512974711431057868L
#define LSP4   -0.49767555160664719605829895429509963073508410781489L
#define A4TRANS 0.51747906167389938633075816189886294562237747514138L

#define TVIL_ComplexInfinity ((1.0L + 1.0L*I)/0.0L)
#define TVIL_Infinity (1.0L/0.0L)

enum {FALSE, TRUE};
enum {NO, YES};

/* ================================ */
/*          GLOBAL DATA             */
/* ================================ */

extern int _isAligned;     /* Indicates whether the data sub-objects
			     have been constructed. */

extern int _isInitialized; /* Indicates whether initial values have
			     been set. */

extern int _evalMode;      /* Indicates which set of functions is to be
			     evaluated (i.e., ALL=EFGH, EFG, EF).  See
			     3vil_global.h for details */

extern int _reAxisOK;      /* YES/NO depending on whether there is a
			     pole on the real-t axis between t=0 and
			     t=1. */

extern int _poleAt1;       /* YES/NO depending on whether there is a
			     pole near t=1. */

extern int _doAnalytic;    /* If YES (NO), put in (don't put in) all
			     analytically known functions after
			     generic evaulation. */

extern int _forceContour;  /* If YES, force evaulation by integration
			     along contour in complex plane, even if
			     integration along real t-axis is
			     possible. */

extern int _forceDefault;  /* If YES, force default evaluation,
			     ignoring special 3-scale cases. */

extern int _status;        /* Current evaluation status: whether
			     evaluated and, if so, how (see
			     3vil_global.h for value definitions). */

/* Parameters and basis fuctions: */
extern TVIL_REAL       _u, _v, _w, _x, _y, _z, _qq;
extern TVIL_ITYPE      _II[NUM_I_FUNCS];
extern TVIL_FBARTYPE _FBAR[NUM_F_FUNCS];
extern TVIL_ETYPE       _E[NUM_E_FUNCS];
extern TVIL_GTYPE       _G[NUM_G_FUNCS];
extern TVIL_HTYPE       _H;

/* For testing argument permutations: */
extern TVIL_REAL _arglist[6];

/* The actual functions to be integrated: */
extern int _integrateII[NUM_I_FUNCS];
extern int _integrateFBAR[NUM_F_FUNCS];
extern int _integrateE[NUM_E_FUNCS];
extern int _integrateG[NUM_G_FUNCS];
extern int _integrateH;

/* Pointers to these: */
extern int _nIfuns;
extern int _nFBARfuns;
extern int _nEfuns;
extern int _nGfuns;
extern int _nHfuns;
extern TVIL_ITYPE    *_ifun[NUM_I_FUNCS];
extern TVIL_FBARTYPE *_fbarfun[NUM_F_FUNCS];
extern TVIL_ETYPE    *_efun[NUM_E_FUNCS];
extern TVIL_GTYPE    *_gfun[NUM_G_FUNCS];
extern TVIL_HTYPE    *_hfun;

/* Pointers to derivative evaluators: */
extern TVIL_COMPLEX (*_Iderivative) (TVIL_ITYPE *, TVIL_COMPLEX, TVIL_REAL);
extern TVIL_COMPLEX (*_FBARderivative) (TVIL_FBARTYPE *, TVIL_COMPLEX, TVIL_REAL);
extern TVIL_COMPLEX (*_Gderivative) (TVIL_GTYPE *, TVIL_COMPLEX, TVIL_REAL);
extern TVIL_COMPLEX (*_Hderivative) (TVIL_HTYPE *, TVIL_COMPLEX, TVIL_REAL);

extern TVIL_REAL *_tPole;
extern int        _nPoles;

/* Parameters for numerical integration; defaults are defined in
   3vil_params.h: */
extern TVIL_REAL _imDispl;
extern TVIL_REAL _tInit;
extern TVIL_REAL _aParameter;

  /* Parameters for automatic step-size control in Runge-Kutta: */
extern TVIL_REAL _precisionGoal;
extern int       _nStepsStart, _nStepsMaxCon, _nStepsMaxVar, _nStepsMin;

extern TVIL_REAL _a, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9;
extern TVIL_REAL _maxerr, _err_H, _maxerr_noH;

extern TVIL_COMPLEX _Ug, _Vg, _Wg, _Xg, _Yg, _Zg;
extern TVIL_COMPLEX _lnbarUg, _lnbarVg, _lnbarWg, _lnbarXg, _lnbarYg, _lnbarZg;

/* Pointers to RK stepper functions: */
extern int  (*_RKstepper6) ();
extern void (*_RKstepper5) ();

/* Toggle to control printing style */
extern int _printStyle;

/* Toggle to control printing of warning messages */
extern int _print3VILWarns;

/* Toggle to control printing of bold functions */
extern int _printBold;

/* ====== END OF GLOBAL DATA ========== */

/* These are just useful shorthands: */

#define SAME2(arg1,arg2) ((TVIL_FABS(arg1 - arg2)) < TVIL_TOL)
#define SAME3(arg1,arg2,arg3) (((TVIL_FABS(arg1 - arg2)) < TVIL_TOL) && \
                         ((TVIL_FABS(arg2 - arg3)) < TVIL_TOL))
#define SAME4(arg1,arg2,arg3,arg4) (((TVIL_FABS(arg1 - arg2)) < TVIL_TOL) && \
                            ((TVIL_FABS(arg2 - arg3)) < TVIL_TOL) && \
                            ((TVIL_FABS(arg3 - arg4)) < TVIL_TOL))
#define SAME5(arg1,arg2,arg3,arg4,arg5) (((TVIL_FABS(arg1 - arg2)) < TVIL_TOL) && \
                               ((TVIL_FABS(arg2 - arg3)) < TVIL_TOL) && \
                               ((TVIL_FABS(arg3 - arg4)) < TVIL_TOL) && \
                               ((TVIL_FABS(arg4 - arg5)) < TVIL_TOL))
#define SAME6(arg1,arg2,arg3,arg4,arg5,arg6) (((TVIL_FABS(arg1 - arg2)) < TVIL_TOL) && \
                                  ((TVIL_FABS(arg2 - arg3)) < TVIL_TOL) && \
                                  ((TVIL_FABS(arg3 - arg4)) < TVIL_TOL) && \
                                  ((TVIL_FABS(arg4 - arg5)) < TVIL_TOL) && \
                                  ((TVIL_FABS(arg5 - arg6)) < TVIL_TOL))
#define SAME7(arg1,arg2,arg3,arg4,arg5,arg6,arg7) (((TVIL_FABS(arg1 - arg2)) < TVIL_TOL) && \
                                     ((TVIL_FABS(arg2 - arg3)) < TVIL_TOL) && \
                                     ((TVIL_FABS(arg3 - arg4)) < TVIL_TOL) && \
                                     ((TVIL_FABS(arg4 - arg5)) < TVIL_TOL) && \
                                     ((TVIL_FABS(arg5 - arg6)) < TVIL_TOL) && \
                                     ((TVIL_FABS(arg6 - arg7)) < TVIL_TOL))

#endif /* INTERNAL_H */
