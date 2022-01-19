/* Miscellaneous useful constants.  Users who #include this file
   should be careful to insure that there are no name conflicts with
   their own variables or functions. */

#ifndef _TVIL_GLOBAL_H_
#define _TVIL_GLOBAL_H_

/* Status codes (status) */
enum {UNEVALUATED, ANALYTIC, REAXIS, CONTOUR};

/* Function codes (mode) */
enum {ALL, EFGH=0, FULL=0, EFG, EF, THREESCALE_A, THREESCALE_B, THREESCALE_C};

/* Print styles */
enum {STANDARD, BASIC=0, STD=0, GENERIC=0, PLAIN=0, MATH};

/* Maximum number of posible poles on Re t axis: */
/* So far this is poles associated with I functions (32) and FBAR
   functions (24) and the H function (3). */
#define NUM_POLES 59

/* Enums for indexing */
enum {Iuvx, Ixyz, Iuxy, Ivxz, Iuwz, Ivwy, Iuwy, Ivwz, Ivyz, Iwxy, 
      Iuvz, Iuwx, Iuyz, Iwxz, Iuvy, Ivwx};
enum {uvx, xyz, uxy, vxz, uwz, vwy, uwy, vwz, vyz, wxy, 
      uvz, uwx, uyz, wxz, uvy, vwx};
enum {_124, _456, _145, _246, _136, _235, _135, _236, _256, _345,
      _126, _134, _156, _346, _125, _234};

enum {Fwuxy, Fwvxz, Fxuwy, Fxvwz, Fuvyz, Fuwxy, 
      Fyuvz, Fyuwx, Fvuyz, Fvwxz, Fzuvy, Fzvwx};
enum {wuxy, wvxz, xuwy, xvwz, uvyz, uwxy, 
      yuvz, yuwx, vuyz, vwxz, zuvy, zvwx};
enum {_3145, _3246, _4135, _4236, _1256, _1345, 
      _5126, _5134, _2156, _2346, _6125, _6234};

/* DGR would be nice to make above enums for F align with these... */
enum {Ewuxy, Evwxz, Euvyz};

enum {Gwuzvy, Gxuvyz, Guvxwz, Gyvwxz, Gvuxwy, Gzuwxy};
enum {wuzvy, xuvyz, uvxwz, yvwxz, vuxwy, zuwxy};
enum {_31625, _41256, _12436, _52346, _21435, _61345};

/* Allowed permutations */
enum {P123456, P164352, P245163, P321546, P416235, P461532, P542613, P635124,
      P132654, P213465, P254361, P356241, P425136, P524316, P563412, P641523, 
      P146253, P231564, P312645, P365142, P452631, P536214, P614325, P653421};

/* Function types: */
enum {ITYPE, FBARTYPE, GTYPE, HTYPE, FTYPE, ETYPE};

/* For 3-scale evaluation: */
enum {_z00xx, _zxxyy=0, _zxyxy=0, _x0yxz, _y0xyz,
      _0xyz=0, _z0xy, _x0yz, _y0xz,
      _xxz=0, _yyz, _xyz};

#endif /* tvil_global.h */
