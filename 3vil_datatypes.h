/* All the special datatpyes for 3VIL */

#ifndef DATATYPES_H
#define DATATYPES_H

#include "3vil.h"

/* ======================================== */
/*            I-type function               */
/* ======================================== */
struct TVIL_Itype {

  int          type;
  int          which;
  TVIL_REAL    arg[3];
  TVIL_COMPLEX value;
  TVIL_COMPLEX deriv;
  TVIL_COMPLEX bold[3];

  /* DGR testing */
  TVIL_COMPLEX *lnbarA1, *lnbarA2, *lnbarA3;

  /* Evolution coefficients: */
  TVIL_REAL p[2];
  TVIL_REAL cII[2];
  TVIL_REAL cILL_012[2], cILL_021[2], cILL_120[2];
  TVIL_REAL cIL_012[3], cIL_102[3], cIL_201[3];
  TVIL_REAL cI[3];

  /* For generic use: */
  TVIL_REAL *coeff;

  TVIL_REAL sumargs;
};

typedef struct TVIL_Itype TVIL_ITYPE;

/* ======================================== */
/*          Fbar-type function              */
/* ======================================== */
struct TVIL_FBARtype {

  int          type;
  int          which;
  TVIL_REAL    arg[4];
  TVIL_COMPLEX value;
  TVIL_COMPLEX deriv;
  TVIL_COMPLEX fValue;
  TVIL_COMPLEX boldF[4];

  /* DGR testing */
  TVIL_COMPLEX *lnbarA1, *lnbarA2, *lnbarA3, *lnbarA4;

  /* Pole locations (they are the same for each term!) */
  TVIL_REAL p2, p3, p4, p5;

  /* Evolution coefficients: */
  TVIL_REAL cFF11, cFF13;
  TVIL_REAL cFF21, cFF22[3], cFF23[3];
  TVIL_REAL cFLLL11, cFLLL12, cFLLL13;
  TVIL_REAL cFLLL21, cFLLL23[3], cFLLL24[3], cFLLL25[3];
  TVIL_REAL cFLL11, cFLL12[3], cFLL13[3];
  TVIL_REAL cFLL21, cFLL23[3], cFLL24[3], cFLL25[3];
  TVIL_REAL cFIL4, cFIL5;
  TVIL_REAL cFI22;
  TVIL_REAL cFL10, cFL11, cFL13, cFL14, cFL15;
  TVIL_REAL cFL20[3], cFL21, cFL22[3], cFL23[3];
  TVIL_REAL cF0, cF2, cF3;

  /* For generic use: */
  TVIL_REAL *coeff;

  /* Pointers to needed data: */
  TVIL_COMPLEX *fval[3];
  TVIL_COMPLEX *ival[4];

  TVIL_REAL sumargs;
};

typedef struct TVIL_FBARtype TVIL_FBARTYPE;

/* ======================================== */
/*            E-type function               */
/* ======================================== */
struct TVIL_Etype {

  int          type;
  int          which;
  TVIL_REAL    arg[4];
  TVIL_COMPLEX value;
  TVIL_COMPLEX bold[4];

  TVIL_COMPLEX *fval[4];
};

typedef struct TVIL_Etype TVIL_ETYPE;

/* ======================================== */
/*             G-type function              */
/* ======================================== */
struct TVIL_Gtype {

  int          type;
  int          which;
  TVIL_REAL    arg[5];
  TVIL_COMPLEX value;
  TVIL_COMPLEX deriv;
  TVIL_COMPLEX bold[4];
  int          hasNegativeArg;

  /* DGR testing */
  TVIL_COMPLEX *A1, *A2, *A3, *A4, *A5;
  TVIL_COMPLEX *lnbarA1, *lnbarA2, *lnbarA3, *lnbarA4, *lnbarA5;

  /* Pole locations (default arg ordering): */
  TVIL_REAL p1, p2, p3, p4, p5;

  /* These correspond to the four F terms, in order */
  TVIL_REAL cGF1[4], cGF4[4], cGF5[4];
  TVIL_REAL cGF_p4[4], cGF_p5[4];
  TVIL_REAL cGI_p2[2], cGI_p3[2];
  TVIL_REAL cGL_p2[4], cGL_p3[4];
  TVIL_REAL cG0, cG1, cG2, cG3, cG4, cG5;

  /* For generic use: */
  TVIL_REAL *coeff;

  /* Pointers to needed data: */
  TVIL_COMPLEX *fval[4];
  TVIL_COMPLEX *ival[10];

  TVIL_REAL sumargs;
};

typedef struct TVIL_Gtype TVIL_GTYPE;

/* ======================================== */
/*             H-type function              */
/* ======================================== */
struct TVIL_Htype {

  int          type;
  TVIL_REAL    arg[6];
  TVIL_COMPLEX value;
  TVIL_COMPLEX deriv;
  TVIL_COMPLEX bold[2];

  TVIL_REAL cHGnum[6][5];
  TVIL_REAL cHGden[6][8];
  TVIL_REAL cHnum[3];
  TVIL_REAL cHden[4];

  TVIL_REAL cHd1roots[3];

  /* For generic use: */
  TVIL_REAL *coeff;

  /* Pointers to needed data: */
  TVIL_COMPLEX *gval[6];
  TVIL_COMPLEX *fval[6][2];
  TVIL_COMPLEX *ival[6][4];

  TVIL_REAL sumargs;
};

typedef struct TVIL_Htype TVIL_HTYPE;

#endif /* DATATYPES_H */
