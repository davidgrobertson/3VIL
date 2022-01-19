/* Code for performing permutations of function arguments */

#include "internal.h"
#include <string.h>

/* ******************************************************************* */
/* Returns the inverse of the specified permutation. (Perms themselves
   are as defined in 3vil_global.h.) */

int TVIL_InversePerm (int perm)
{
  int inverse[] = {0, 1, 4, 3, 2, 19, 21, 20, 8, 9, 22, 15, 12,
		   13, 14, 11, 16, 18, 17, 5, 7, 6, 10, 23};

  if (perm < 0 || perm > 23)
    TVIL_Error ("Inverse", "Invalid permutation specified.", 321);

  return inverse[perm];
}

/* ******************************************************************* */

void TVIL_PermuteArgs (TVIL_REAL *in,
		       int perm,
		       TVIL_REAL *out)
{
  TVIL_REAL *incopy;
  int i;

  /* Enable function to be called with in and out pointing to the same
     results struct: */
  if (in == out) {
    if (perm == 0)
      return;
    incopy = (TVIL_REAL *) calloc (6, sizeof (TVIL_REAL));
    for (i=0; i<6; i++)
      incopy[i] = in[i];
  }
  else
    incopy = in;

  /* Negative perm indicates the inverse of |perm| */
  if (perm < 0)
    perm = TVIL_InversePerm (-perm);

  if (perm == P164352) {
    out[0] = incopy[0];
    out[1] = incopy[5];
    out[2] = incopy[3];
    out[3] = incopy[2];
    out[4] = incopy[4];
    out[5] = incopy[1];
  }
  else if (perm == P245163) {
    out[0] = incopy[1];
    out[1] = incopy[3];
    out[2] = incopy[4];
    out[3] = incopy[0];
    out[4] = incopy[5];
    out[5] = incopy[2];
  }
  else if (perm == P321546) {
    out[0] = incopy[2];
    out[1] = incopy[1];
    out[2] = incopy[0];
    out[3] = incopy[4];
    out[4] = incopy[3];
    out[5] = incopy[5];
  }
  else if (perm == P416235) {
    out[0] = incopy[3];
    out[1] = incopy[0];
    out[2] = incopy[5];
    out[3] = incopy[1];
    out[4] = incopy[2];
    out[5] = incopy[4];
  }
  else if (perm == P461532) {
    out[0] = incopy[3];
    out[1] = incopy[5];
    out[2] = incopy[0];
    out[3] = incopy[4];
    out[4] = incopy[2];
    out[5] = incopy[1];
  }
  else if (perm == P542613) {
    out[0] = incopy[4];
    out[1] = incopy[3];
    out[2] = incopy[1];
    out[3] = incopy[5];
    out[4] = incopy[0];
    out[5] = incopy[2];
  }
  else if (perm == P635124) {
    out[0] = incopy[5];
    out[1] = incopy[2];
    out[2] = incopy[4];
    out[3] = incopy[0];
    out[4] = incopy[1];
    out[5] = incopy[3];
  }
  else if (perm == P132654) {
    out[0] = incopy[0];
    out[1] = incopy[2];
    out[2] = incopy[1];
    out[3] = incopy[5];
    out[4] = incopy[4];
    out[5] = incopy[3];
  }
  else if (perm == P213465) {
    out[0] = incopy[1];
    out[1] = incopy[0];
    out[2] = incopy[2];
    out[3] = incopy[3];
    out[4] = incopy[5];
    out[5] = incopy[4];
  }
  else if (perm == P254361) {
    out[0] = incopy[1];
    out[1] = incopy[4];
    out[2] = incopy[3];
    out[3] = incopy[2];
    out[4] = incopy[5];
    out[5] = incopy[0];
  }
  else if (perm == P356241) {
    out[0] = incopy[2];
    out[1] = incopy[4];
    out[2] = incopy[5];
    out[3] = incopy[1];
    out[4] = incopy[3];
    out[5] = incopy[0];
  }
  else if (perm == P425136) {
    out[0] = incopy[3];
    out[1] = incopy[1];
    out[2] = incopy[4];
    out[3] = incopy[0];
    out[4] = incopy[2];
    out[5] = incopy[5];
  }
  else if (perm == P524316) {
    out[0] = incopy[4];
    out[1] = incopy[1];
    out[2] = incopy[3];
    out[3] = incopy[2];
    out[4] = incopy[0];
    out[5] = incopy[5];
  }
  else if (perm == P563412) {
    out[0] = incopy[4];
    out[1] = incopy[5];
    out[2] = incopy[2];
    out[3] = incopy[3];
    out[4] = incopy[0];
    out[5] = incopy[1];
  }
  else if (perm == P641523) {
    out[0] = incopy[5];
    out[1] = incopy[3];
    out[2] = incopy[0];
    out[3] = incopy[4];
    out[4] = incopy[1];
    out[5] = incopy[2];
  }
  else if (perm == P146253) {
    out[0] = incopy[0];
    out[1] = incopy[3];
    out[2] = incopy[5];
    out[3] = incopy[1];
    out[4] = incopy[4];
    out[5] = incopy[2];
  }
  else if (perm == P231564) {
    out[0] = incopy[1];
    out[1] = incopy[2];
    out[2] = incopy[0];
    out[3] = incopy[4];
    out[4] = incopy[5];
    out[5] = incopy[3];
  }
  else if (perm == P312645) {
    out[0] = incopy[2];
    out[1] = incopy[0];
    out[2] = incopy[1];
    out[3] = incopy[5];
    out[4] = incopy[3];
    out[5] = incopy[4];
  }
  else if (perm == P365142) {
    out[0] = incopy[2];
    out[1] = incopy[5];
    out[2] = incopy[4];
    out[3] = incopy[0];
    out[4] = incopy[3];
    out[5] = incopy[1];
  }
  else if (perm == P452631) {
    out[0] = incopy[3];
    out[1] = incopy[4];
    out[2] = incopy[1];
    out[3] = incopy[5];
    out[4] = incopy[2];
    out[5] = incopy[0];
  }
  else if (perm == P536214) {
    out[0] = incopy[4];
    out[1] = incopy[2];
    out[2] = incopy[5];
    out[3] = incopy[1];
    out[4] = incopy[0];
    out[5] = incopy[3];
  }
  else if (perm == P614325) {
    out[0] = incopy[5];
    out[1] = incopy[0];
    out[2] = incopy[3];
    out[3] = incopy[2];
    out[4] = incopy[1];
    out[5] = incopy[4];
  }
  else if (perm == P653421) {
    out[0] = incopy[5];
    out[1] = incopy[4];
    out[2] = incopy[2];
    out[3] = incopy[3];
    out[4] = incopy[1];
    out[5] = incopy[0];
  }
  else if (perm == P123456) {
    out[0] = incopy[0];
    out[1] = incopy[1];
    out[2] = incopy[2];
    out[3] = incopy[3];
    out[4] = incopy[4];
    out[5] = incopy[5];
  }
  else 
    TVIL_Error ("PermuteArgs", "Bad permutation specified.", 111);

  if (in == out)
    free (incopy);

  return;
}

/* ******************************************************************* */
/* Permutes arguments and functions in a TVIL_RESULT.  
   - Pointers in and out can be to the same result structs, or
     different.
   - perm can be 0 to 23, with 0 = identity. See 3vil_global.h for
     details and definitions.
   - If a negative perm is given, we do the inverse of |perm|.
 */

void TVIL_PermuteResult (TVIL_RESULT *in,
			 int perm,
			 TVIL_RESULT *out)
{
  TVIL_RESULT *incopy;
  char funcname[] = "PermuteResult";

  if (in->evalMode == EF || in->evalMode == EFG) {
    TVIL_Warn (funcname, "Permutation of subset cases not allowed.");
    out->status = UNEVALUATED;
    return;
  }

  /* Enable function to be called with in and out pointing to the same
     results struct: */
  if (in == out) {
    if (perm == 0)
      return;
    incopy = (TVIL_RESULT *) malloc (sizeof (TVIL_RESULT));
    *incopy = *in;
  }
  else {
    incopy = in;

    /* This transfers flags, function lists, etc. into the new struct
       -- overkill but simple. */
    *out = *in;
  }

  if (perm < 0)
    perm = TVIL_InversePerm (-perm);

  /* These are always the same: */
  out->qq = incopy->qq;
  out->H = incopy->H;

  if (perm == P164352) {
    out->u = incopy->u;
    out->v = incopy->z;
    out->w = incopy->x;
    out->x = incopy->w;
    out->y = incopy->y;
    out->z = incopy->v;

    out->G[wuzvy] = incopy->G[xuvyz];
    out->G[xuvyz] = incopy->G[wuzvy];
    out->G[uvxwz] = incopy->G[uvxwz];
    out->G[yvwxz] = incopy->G[yvwxz];
    out->G[vuxwy] = incopy->G[zuwxy];
    out->G[zuwxy] = incopy->G[vuxwy];

    out->FBAR[wuxy] = incopy->FBAR[xuwy];
    out->F[wuxy] = incopy->F[xuwy];
    out->FBAR[wvxz] = incopy->FBAR[xvwz];
    out->F[wvxz] = incopy->F[xvwz];
    out->FBAR[xuwy] = incopy->FBAR[wuxy];
    out->F[xuwy] = incopy->F[wuxy];
    out->FBAR[xvwz] = incopy->FBAR[wvxz];
    out->F[xvwz] = incopy->F[wvxz];
    out->FBAR[uvyz] = incopy->FBAR[uvyz];
    out->F[uvyz] = incopy->F[uvyz];
    out->FBAR[uwxy] = incopy->FBAR[uwxy];
    out->F[uwxy] = incopy->F[uwxy];
    out->FBAR[yuvz] = incopy->FBAR[yuvz];
    out->F[yuvz] = incopy->F[yuvz];
    out->FBAR[yuwx] = incopy->FBAR[yuwx];
    out->F[yuwx] = incopy->F[yuwx];
    out->FBAR[vuyz] = incopy->FBAR[zuvy];
    out->F[vuyz] = incopy->F[zuvy];
    out->FBAR[vwxz] = incopy->FBAR[zvwx];
    out->F[vwxz] = incopy->F[zvwx];
    out->FBAR[zuvy] = incopy->FBAR[vuyz];
    out->F[zuvy] = incopy->F[vuyz];
    out->FBAR[zvwx] = incopy->FBAR[vwxz];
    out->F[zvwx] = incopy->F[vwxz];

    out->II[uvx] = incopy->II[uwz];
    out->II[xyz] = incopy->II[vwy];
    out->II[uxy] = incopy->II[uwy];
    out->II[vxz] = incopy->II[vwz];
    out->II[uwz] = incopy->II[uvx];
    out->II[vwy] = incopy->II[xyz];
    out->II[uwy] = incopy->II[uxy];
    out->II[vwz] = incopy->II[vxz];
    out->II[vyz] = incopy->II[vyz];
    out->II[wxy] = incopy->II[wxy];
    out->II[uvz] = incopy->II[uvz];
    out->II[uwx] = incopy->II[uwx];
    out->II[uyz] = incopy->II[uvy];
    out->II[wxz] = incopy->II[vwx];
    out->II[uvy] = incopy->II[uyz];
    out->II[vwx] = incopy->II[wxz];

    out->E[Ewuxy] = incopy->E[Ewuxy];
    out->E[Evwxz] = incopy->E[Evwxz];
    out->E[Euvyz] = incopy->E[Euvyz];
  }
  else if (perm == P245163) {
    out->u = incopy->v;
    out->v = incopy->x;
    out->w = incopy->y;
    out->x = incopy->u;
    out->y = incopy->z;
    out->z = incopy->w;

    out->G[wuzvy] = incopy->G[yvwxz];
    out->G[xuvyz] = incopy->G[uvxwz];
    out->G[uvxwz] = incopy->G[vuxwy];
    out->G[yvwxz] = incopy->G[zuwxy];
    out->G[vuxwy] = incopy->G[xuvyz];
    out->G[zuwxy] = incopy->G[wuzvy];

    out->FBAR[wuxy] = incopy->FBAR[yuvz];
    out->F[wuxy] = incopy->F[yuvz];
    out->FBAR[wvxz] = incopy->FBAR[yuwx];
    out->F[wvxz] = incopy->F[yuwx];
    out->FBAR[xuwy] = incopy->FBAR[uvyz];
    out->F[xuwy] = incopy->F[uvyz];
    out->FBAR[xvwz] = incopy->FBAR[uwxy];
    out->F[xvwz] = incopy->F[uwxy];
    out->FBAR[uvyz] = incopy->FBAR[vwxz];
    out->F[uvyz] = incopy->F[vwxz];
    out->FBAR[uwxy] = incopy->FBAR[vuyz];
    out->F[uwxy] = incopy->F[vuyz];
    out->FBAR[yuvz] = incopy->FBAR[zvwx];
    out->F[yuvz] = incopy->F[zvwx];
    out->FBAR[yuwx] = incopy->FBAR[zuvy];
    out->F[yuwx] = incopy->F[zuvy];
    out->FBAR[vuyz] = incopy->FBAR[xvwz];
    out->F[vuyz] = incopy->F[xvwz];
    out->FBAR[vwxz] = incopy->FBAR[xuwy];
    out->F[vwxz] = incopy->F[xuwy];
    out->FBAR[zuvy] = incopy->FBAR[wvxz];
    out->F[zuvy] = incopy->F[wvxz];
    out->FBAR[zvwx] = incopy->FBAR[wuxy];
    out->F[zvwx] = incopy->F[wuxy];

    out->II[uvx] = incopy->II[uvx];
    out->II[xyz] = incopy->II[uwz];
    out->II[uxy] = incopy->II[uvz];
    out->II[vxz] = incopy->II[uwx];
    out->II[uwz] = incopy->II[vwy];
    out->II[vwy] = incopy->II[xyz];
    out->II[uwy] = incopy->II[vyz];
    out->II[vwz] = incopy->II[wxy];
    out->II[vyz] = incopy->II[wxz];
    out->II[wxy] = incopy->II[uyz];
    out->II[uvz] = incopy->II[vwx];
    out->II[uwx] = incopy->II[uvy];
    out->II[uyz] = incopy->II[vwz];
    out->II[wxz] = incopy->II[uwy];
    out->II[uvy] = incopy->II[vxz];
    out->II[vwx] = incopy->II[uxy];

    out->E[Ewuxy] = incopy->E[Euvyz];
    out->E[Evwxz] = incopy->E[Ewuxy];
    out->E[Euvyz] = incopy->E[Evwxz];
  }
  else if (perm == P321546) {
    out->u = incopy->w;
    out->v = incopy->v;
    out->w = incopy->u;
    out->x = incopy->y;
    out->y = incopy->x;
    out->z = incopy->z;

    out->G[wuzvy] = incopy->G[uvxwz];
    out->G[xuvyz] = incopy->G[yvwxz];
    out->G[uvxwz] = incopy->G[wuzvy];
    out->G[yvwxz] = incopy->G[xuvyz];
    out->G[vuxwy] = incopy->G[vuxwy];
    out->G[zuwxy] = incopy->G[zuwxy];

    out->FBAR[wuxy] = incopy->FBAR[uwxy];
    out->F[wuxy] = incopy->F[uwxy];
    out->FBAR[wvxz] = incopy->FBAR[uvyz];
    out->F[wvxz] = incopy->F[uvyz];
    out->FBAR[xuwy] = incopy->FBAR[yuwx];
    out->F[xuwy] = incopy->F[yuwx];
    out->FBAR[xvwz] = incopy->FBAR[yuvz];
    out->F[xvwz] = incopy->F[yuvz];
    out->FBAR[uvyz] = incopy->FBAR[wvxz];
    out->F[uvyz] = incopy->F[wvxz];
    out->FBAR[uwxy] = incopy->FBAR[wuxy];
    out->F[uwxy] = incopy->F[wuxy];
    out->FBAR[yuvz] = incopy->FBAR[xvwz];
    out->F[yuvz] = incopy->F[xvwz];
    out->FBAR[yuwx] = incopy->FBAR[xuwy];
    out->F[yuwx] = incopy->F[xuwy];
    out->FBAR[vuyz] = incopy->FBAR[vwxz];
    out->F[vuyz] = incopy->F[vwxz];
    out->FBAR[vwxz] = incopy->FBAR[vuyz];
    out->F[vwxz] = incopy->F[vuyz];
    out->FBAR[zuvy] = incopy->FBAR[zvwx];
    out->F[zuvy] = incopy->F[zvwx];
    out->FBAR[zvwx] = incopy->FBAR[zuvy];
    out->F[zvwx] = incopy->F[zuvy];

    out->II[uvx] = incopy->II[vwy];
    out->II[xyz] = incopy->II[xyz];
    out->II[uxy] = incopy->II[wxy];
    out->II[vxz] = incopy->II[vyz];
    out->II[uwz] = incopy->II[uwz];
    out->II[vwy] = incopy->II[uvx];
    out->II[uwy] = incopy->II[uwx];
    out->II[vwz] = incopy->II[uvz];
    out->II[vyz] = incopy->II[vxz];
    out->II[wxy] = incopy->II[uxy];
    out->II[uvz] = incopy->II[vwz];
    out->II[uwx] = incopy->II[uwy];
    out->II[uyz] = incopy->II[wxz];
    out->II[wxz] = incopy->II[uyz];
    out->II[uvy] = incopy->II[vwx];
    out->II[vwx] = incopy->II[uvy];

    out->E[Ewuxy] = incopy->E[Ewuxy];
    out->E[Evwxz] = incopy->E[Euvyz];
    out->E[Euvyz] = incopy->E[Evwxz];
  }
  else if (perm == P416235) {
    out->u = incopy->x;
    out->v = incopy->u;
    out->w = incopy->z;
    out->x = incopy->v;
    out->y = incopy->w;
    out->z = incopy->y;

    out->G[wuzvy] = incopy->G[zuwxy];
    out->G[xuvyz] = incopy->G[vuxwy];
    out->G[uvxwz] = incopy->G[xuvyz];
    out->G[yvwxz] = incopy->G[wuzvy];
    out->G[vuxwy] = incopy->G[uvxwz];
    out->G[zuwxy] = incopy->G[yvwxz];

    out->FBAR[wuxy] = incopy->FBAR[zvwx];
    out->F[wuxy] = incopy->F[zvwx];
    out->FBAR[wvxz] = incopy->FBAR[zuvy];
    out->F[wvxz] = incopy->F[zuvy];
    out->FBAR[xuwy] = incopy->FBAR[vwxz];
    out->F[xuwy] = incopy->F[vwxz];
    out->FBAR[xvwz] = incopy->FBAR[vuyz];
    out->F[xvwz] = incopy->F[vuyz];
    out->FBAR[uvyz] = incopy->FBAR[xuwy];
    out->F[uvyz] = incopy->F[xuwy];
    out->FBAR[uwxy] = incopy->FBAR[xvwz];
    out->F[uwxy] = incopy->F[xvwz];
    out->FBAR[yuvz] = incopy->FBAR[wuxy];
    out->F[yuvz] = incopy->F[wuxy];
    out->FBAR[yuwx] = incopy->FBAR[wvxz];
    out->F[yuwx] = incopy->F[wvxz];
    out->FBAR[vuyz] = incopy->FBAR[uwxy];
    out->F[vuyz] = incopy->F[uwxy];
    out->FBAR[vwxz] = incopy->FBAR[uvyz];
    out->F[vwxz] = incopy->F[uvyz];
    out->FBAR[zuvy] = incopy->FBAR[yuwx];
    out->F[zuvy] = incopy->F[yuwx];
    out->FBAR[zvwx] = incopy->FBAR[yuvz];
    out->F[zvwx] = incopy->F[yuvz];

    out->II[uvx] = incopy->II[uvx];
    out->II[xyz] = incopy->II[vwy];
    out->II[uxy] = incopy->II[vwx];
    out->II[vxz] = incopy->II[uvy];
    out->II[uwz] = incopy->II[xyz];
    out->II[vwy] = incopy->II[uwz];
    out->II[uwy] = incopy->II[wxz];
    out->II[vwz] = incopy->II[uyz];
    out->II[vyz] = incopy->II[uwy];
    out->II[wxy] = incopy->II[vwz];
    out->II[uvz] = incopy->II[uxy];
    out->II[uwx] = incopy->II[vxz];
    out->II[uyz] = incopy->II[wxy];
    out->II[wxz] = incopy->II[vyz];
    out->II[uvy] = incopy->II[uwx];
    out->II[vwx] = incopy->II[uvz];

    out->E[Ewuxy] = incopy->E[Evwxz];
    out->E[Evwxz] = incopy->E[Euvyz];
    out->E[Euvyz] = incopy->E[Ewuxy];
  }
  else if (perm == P461532) {
    out->u = incopy->x;
    out->v = incopy->z;
    out->w = incopy->u;
    out->x = incopy->y;
    out->y = incopy->w;
    out->z = incopy->v;

    out->G[wuzvy] = incopy->G[uvxwz];
    out->G[xuvyz] = incopy->G[yvwxz];
    out->G[uvxwz] = incopy->G[xuvyz];
    out->G[yvwxz] = incopy->G[wuzvy];
    out->G[vuxwy] = incopy->G[zuwxy];
    out->G[zuwxy] = incopy->G[vuxwy];

    out->FBAR[wuxy] = incopy->FBAR[uwxy];
    out->F[wuxy] = incopy->F[uwxy];
    out->FBAR[wvxz] = incopy->FBAR[uvyz];
    out->F[wvxz] = incopy->F[uvyz];
    out->FBAR[xuwy] = incopy->FBAR[yuwx];
    out->F[xuwy] = incopy->F[yuwx];
    out->FBAR[xvwz] = incopy->FBAR[yuvz];
    out->F[xvwz] = incopy->F[yuvz];
    out->FBAR[uvyz] = incopy->FBAR[xvwz];
    out->F[uvyz] = incopy->F[xvwz];
    out->FBAR[uwxy] = incopy->FBAR[xuwy];
    out->F[uwxy] = incopy->F[xuwy];
    out->FBAR[yuvz] = incopy->FBAR[wvxz];
    out->F[yuvz] = incopy->F[wvxz];
    out->FBAR[yuwx] = incopy->FBAR[wuxy];
    out->F[yuwx] = incopy->F[wuxy];
    out->FBAR[vuyz] = incopy->FBAR[zvwx];
    out->F[vuyz] = incopy->F[zvwx];
    out->FBAR[vwxz] = incopy->FBAR[zuvy];
    out->F[vwxz] = incopy->F[zuvy];
    out->FBAR[zuvy] = incopy->FBAR[vwxz];
    out->F[zuvy] = incopy->F[vwxz];
    out->FBAR[zvwx] = incopy->FBAR[vuyz];
    out->F[zvwx] = incopy->F[vuyz];

    out->II[uvx] = incopy->II[xyz];
    out->II[xyz] = incopy->II[vwy];
    out->II[uxy] = incopy->II[wxy];
    out->II[vxz] = incopy->II[vyz];
    out->II[uwz] = incopy->II[uvx];
    out->II[vwy] = incopy->II[uwz];
    out->II[uwy] = incopy->II[uwx];
    out->II[vwz] = incopy->II[uvz];
    out->II[vyz] = incopy->II[vwz];
    out->II[wxy] = incopy->II[uwy];
    out->II[uvz] = incopy->II[vxz];
    out->II[uwx] = incopy->II[uxy];
    out->II[uyz] = incopy->II[vwx];
    out->II[wxz] = incopy->II[uvy];
    out->II[uvy] = incopy->II[wxz];
    out->II[vwx] = incopy->II[uyz];

    out->E[Ewuxy] = incopy->E[Ewuxy];
    out->E[Evwxz] = incopy->E[Euvyz];
    out->E[Euvyz] = incopy->E[Evwxz];
  }
  else if (perm == P542613) {
    out->u = incopy->y;
    out->v = incopy->x;
    out->w = incopy->v;
    out->x = incopy->z;
    out->y = incopy->u;
    out->z = incopy->w;

    out->G[wuzvy] = incopy->G[vuxwy];
    out->G[xuvyz] = incopy->G[zuwxy];
    out->G[uvxwz] = incopy->G[yvwxz];
    out->G[yvwxz] = incopy->G[uvxwz];
    out->G[vuxwy] = incopy->G[xuvyz];
    out->G[zuwxy] = incopy->G[wuzvy];

    out->FBAR[wuxy] = incopy->FBAR[vuyz];
    out->F[wuxy] = incopy->F[vuyz];
    out->FBAR[wvxz] = incopy->FBAR[vwxz];
    out->F[wvxz] = incopy->F[vwxz];
    out->FBAR[xuwy] = incopy->FBAR[zuvy];
    out->F[xuwy] = incopy->F[zuvy];
    out->FBAR[xvwz] = incopy->FBAR[zvwx];
    out->F[xvwz] = incopy->F[zvwx];
    out->FBAR[uvyz] = incopy->FBAR[yuwx];
    out->F[uvyz] = incopy->F[yuwx];
    out->FBAR[uwxy] = incopy->FBAR[yuvz];
    out->F[uwxy] = incopy->F[yuvz];
    out->FBAR[yuvz] = incopy->FBAR[uwxy];
    out->F[yuvz] = incopy->F[uwxy];
    out->FBAR[yuwx] = incopy->FBAR[uvyz];
    out->F[yuwx] = incopy->F[uvyz];
    out->FBAR[vuyz] = incopy->FBAR[xuwy];
    out->F[vuyz] = incopy->F[xuwy];
    out->FBAR[vwxz] = incopy->FBAR[xvwz];
    out->F[vwxz] = incopy->F[xvwz];
    out->FBAR[zuvy] = incopy->FBAR[wuxy];
    out->F[zuvy] = incopy->F[wuxy];
    out->FBAR[zvwx] = incopy->FBAR[wvxz];
    out->F[zvwx] = incopy->F[wvxz];

    out->II[uvx] = incopy->II[xyz];
    out->II[xyz] = incopy->II[uwz];
    out->II[uxy] = incopy->II[uyz];
    out->II[vxz] = incopy->II[wxz];
    out->II[uwz] = incopy->II[vwy];
    out->II[vwy] = incopy->II[uvx];
    out->II[uwy] = incopy->II[uvy];
    out->II[vwz] = incopy->II[vwx];
    out->II[vyz] = incopy->II[uwx];
    out->II[wxy] = incopy->II[uvz];
    out->II[uvz] = incopy->II[wxy];
    out->II[uwx] = incopy->II[vyz];
    out->II[uyz] = incopy->II[uwy];
    out->II[wxz] = incopy->II[vwz];
    out->II[uvy] = incopy->II[uxy];
    out->II[vwx] = incopy->II[vxz];

    out->E[Ewuxy] = incopy->E[Euvyz];
    out->E[Evwxz] = incopy->E[Evwxz];
    out->E[Euvyz] = incopy->E[Ewuxy];
  }
  else if (perm == P635124) {
    out->u = incopy->z;
    out->v = incopy->w;
    out->w = incopy->y;
    out->x = incopy->u;
    out->y = incopy->v;
    out->z = incopy->x;

    out->G[wuzvy] = incopy->G[yvwxz];
    out->G[xuvyz] = incopy->G[uvxwz];
    out->G[uvxwz] = incopy->G[zuwxy];
    out->G[yvwxz] = incopy->G[vuxwy];
    out->G[vuxwy] = incopy->G[wuzvy];
    out->G[zuwxy] = incopy->G[xuvyz];

    out->FBAR[wuxy] = incopy->FBAR[yuvz];
    out->F[wuxy] = incopy->F[yuvz];
    out->FBAR[wvxz] = incopy->FBAR[yuwx];
    out->F[wvxz] = incopy->F[yuwx];
    out->FBAR[xuwy] = incopy->FBAR[uvyz];
    out->F[xuwy] = incopy->F[uvyz];
    out->FBAR[xvwz] = incopy->FBAR[uwxy];
    out->F[xvwz] = incopy->F[uwxy];
    out->FBAR[uvyz] = incopy->FBAR[zvwx];
    out->F[uvyz] = incopy->F[zvwx];
    out->FBAR[uwxy] = incopy->FBAR[zuvy];
    out->F[uwxy] = incopy->F[zuvy];
    out->FBAR[yuvz] = incopy->FBAR[vwxz];
    out->F[yuvz] = incopy->F[vwxz];
    out->FBAR[yuwx] = incopy->FBAR[vuyz];
    out->F[yuwx] = incopy->F[vuyz];
    out->FBAR[vuyz] = incopy->FBAR[wvxz];
    out->F[vuyz] = incopy->F[wvxz];
    out->FBAR[vwxz] = incopy->FBAR[wuxy];
    out->F[vwxz] = incopy->F[wuxy];
    out->FBAR[zuvy] = incopy->FBAR[xvwz];
    out->F[zuvy] = incopy->F[xvwz];
    out->FBAR[zvwx] = incopy->FBAR[xuwy];
    out->F[zvwx] = incopy->F[xuwy];

    out->II[uvx] = incopy->II[uwz];
    out->II[xyz] = incopy->II[uvx];
    out->II[uxy] = incopy->II[uvz];
    out->II[vxz] = incopy->II[uwx];
    out->II[uwz] = incopy->II[xyz];
    out->II[vwy] = incopy->II[vwy];
    out->II[uwy] = incopy->II[vyz];
    out->II[vwz] = incopy->II[wxy];
    out->II[vyz] = incopy->II[vwx];
    out->II[wxy] = incopy->II[uvy];
    out->II[uvz] = incopy->II[wxz];
    out->II[uwx] = incopy->II[uyz];
    out->II[uyz] = incopy->II[vxz];
    out->II[wxz] = incopy->II[uxy];
    out->II[uvy] = incopy->II[vwz];
    out->II[vwx] = incopy->II[uwy];

    out->E[Ewuxy] = incopy->E[Euvyz];
    out->E[Evwxz] = incopy->E[Ewuxy];
    out->E[Euvyz] = incopy->E[Evwxz];
  }
  else if (perm == P132654) {
    out->u = incopy->u;
    out->v = incopy->w;
    out->w = incopy->v;
    out->x = incopy->z;
    out->y = incopy->y;
    out->z = incopy->x;

    out->G[wuzvy] = incopy->G[vuxwy];
    out->G[xuvyz] = incopy->G[zuwxy];
    out->G[uvxwz] = incopy->G[uvxwz];
    out->G[yvwxz] = incopy->G[yvwxz];
    out->G[vuxwy] = incopy->G[wuzvy];
    out->G[zuwxy] = incopy->G[xuvyz];

    out->FBAR[wuxy] = incopy->FBAR[vuyz];
    out->F[wuxy] = incopy->F[vuyz];
    out->FBAR[wvxz] = incopy->FBAR[vwxz];
    out->F[wvxz] = incopy->F[vwxz];
    out->FBAR[xuwy] = incopy->FBAR[zuvy];
    out->F[xuwy] = incopy->F[zuvy];
    out->FBAR[xvwz] = incopy->FBAR[zvwx];
    out->F[xvwz] = incopy->F[zvwx];
    out->FBAR[uvyz] = incopy->FBAR[uwxy];
    out->F[uvyz] = incopy->F[uwxy];
    out->FBAR[uwxy] = incopy->FBAR[uvyz];
    out->F[uwxy] = incopy->F[uvyz];
    out->FBAR[yuvz] = incopy->FBAR[yuwx];
    out->F[yuvz] = incopy->F[yuwx];
    out->FBAR[yuwx] = incopy->FBAR[yuvz];
    out->F[yuwx] = incopy->F[yuvz];
    out->FBAR[vuyz] = incopy->FBAR[wuxy];
    out->F[vuyz] = incopy->F[wuxy];
    out->FBAR[vwxz] = incopy->FBAR[wvxz];
    out->F[vwxz] = incopy->F[wvxz];
    out->FBAR[zuvy] = incopy->FBAR[xuwy];
    out->F[zuvy] = incopy->F[xuwy];
    out->FBAR[zvwx] = incopy->FBAR[xvwz];
    out->F[zvwx] = incopy->F[xvwz];

    out->II[uvx] = incopy->II[uwz];
    out->II[xyz] = incopy->II[xyz];
    out->II[uxy] = incopy->II[uyz];
    out->II[vxz] = incopy->II[wxz];
    out->II[uwz] = incopy->II[uvx];
    out->II[vwy] = incopy->II[vwy];
    out->II[uwy] = incopy->II[uvy];
    out->II[vwz] = incopy->II[vwx];
    out->II[vyz] = incopy->II[wxy];
    out->II[wxy] = incopy->II[vyz];
    out->II[uvz] = incopy->II[uwx];
    out->II[uwx] = incopy->II[uvz];
    out->II[uyz] = incopy->II[uxy];
    out->II[wxz] = incopy->II[vxz];
    out->II[uvy] = incopy->II[uwy];
    out->II[vwx] = incopy->II[vwz];

    out->E[Ewuxy] = incopy->E[Euvyz];
    out->E[Evwxz] = incopy->E[Evwxz];
    out->E[Euvyz] = incopy->E[Ewuxy];
  }
  else if (perm == P213465) {
    out->u = incopy->v;
    out->v = incopy->u;
    out->w = incopy->w;
    out->x = incopy->x;
    out->y = incopy->z;
    out->z = incopy->y;

    out->G[wuzvy] = incopy->G[wuzvy];
    out->G[xuvyz] = incopy->G[xuvyz];
    out->G[uvxwz] = incopy->G[vuxwy];
    out->G[yvwxz] = incopy->G[zuwxy];
    out->G[vuxwy] = incopy->G[uvxwz];
    out->G[zuwxy] = incopy->G[yvwxz];

    out->FBAR[wuxy] = incopy->FBAR[wvxz];
    out->F[wuxy] = incopy->F[wvxz];
    out->FBAR[wvxz] = incopy->FBAR[wuxy];
    out->F[wvxz] = incopy->F[wuxy];
    out->FBAR[xuwy] = incopy->FBAR[xvwz];
    out->F[xuwy] = incopy->F[xvwz];
    out->FBAR[xvwz] = incopy->FBAR[xuwy];
    out->F[xvwz] = incopy->F[xuwy];
    out->FBAR[uvyz] = incopy->FBAR[vuyz];
    out->F[uvyz] = incopy->F[vuyz];
    out->FBAR[uwxy] = incopy->FBAR[vwxz];
    out->F[uwxy] = incopy->F[vwxz];
    out->FBAR[yuvz] = incopy->FBAR[zuvy];
    out->F[yuvz] = incopy->F[zuvy];
    out->FBAR[yuwx] = incopy->FBAR[zvwx];
    out->F[yuwx] = incopy->F[zvwx];
    out->FBAR[vuyz] = incopy->FBAR[uvyz];
    out->F[vuyz] = incopy->F[uvyz];
    out->FBAR[vwxz] = incopy->FBAR[uwxy];
    out->F[vwxz] = incopy->F[uwxy];
    out->FBAR[zuvy] = incopy->FBAR[yuvz];
    out->F[zuvy] = incopy->F[yuvz];
    out->FBAR[zvwx] = incopy->FBAR[yuwx];
    out->F[zvwx] = incopy->F[yuwx];

    out->II[uvx] = incopy->II[uvx];
    out->II[xyz] = incopy->II[xyz];
    out->II[uxy] = incopy->II[vxz];
    out->II[vxz] = incopy->II[uxy];
    out->II[uwz] = incopy->II[vwy];
    out->II[vwy] = incopy->II[uwz];
    out->II[uwy] = incopy->II[vwz];
    out->II[vwz] = incopy->II[uwy];
    out->II[vyz] = incopy->II[uyz];
    out->II[wxy] = incopy->II[wxz];
    out->II[uvz] = incopy->II[uvy];
    out->II[uwx] = incopy->II[vwx];
    out->II[uyz] = incopy->II[vyz];
    out->II[wxz] = incopy->II[wxy];
    out->II[uvy] = incopy->II[uvz];
    out->II[vwx] = incopy->II[uwx];

    out->E[Ewuxy] = incopy->E[Evwxz];
    out->E[Evwxz] = incopy->E[Ewuxy];
    out->E[Euvyz] = incopy->E[Euvyz];
  }
  else if (perm == P254361) {
    out->u = incopy->v;
    out->v = incopy->y;
    out->w = incopy->x;
    out->x = incopy->w;
    out->y = incopy->z;
    out->z = incopy->u;

    out->G[wuzvy] = incopy->G[xuvyz];
    out->G[xuvyz] = incopy->G[wuzvy];
    out->G[uvxwz] = incopy->G[vuxwy];
    out->G[yvwxz] = incopy->G[zuwxy];
    out->G[vuxwy] = incopy->G[yvwxz];
    out->G[zuwxy] = incopy->G[uvxwz];

    out->FBAR[wuxy] = incopy->FBAR[xvwz];
    out->F[wuxy] = incopy->F[xvwz];
    out->FBAR[wvxz] = incopy->FBAR[xuwy];
    out->F[wvxz] = incopy->F[xuwy];
    out->FBAR[xuwy] = incopy->FBAR[wvxz];
    out->F[xuwy] = incopy->F[wvxz];
    out->FBAR[xvwz] = incopy->FBAR[wuxy];
    out->F[xvwz] = incopy->F[wuxy];
    out->FBAR[uvyz] = incopy->FBAR[vuyz];
    out->F[uvyz] = incopy->F[vuyz];
    out->FBAR[uwxy] = incopy->FBAR[vwxz];
    out->F[uwxy] = incopy->F[vwxz];
    out->FBAR[yuvz] = incopy->FBAR[zuvy];
    out->F[yuvz] = incopy->F[zuvy];
    out->FBAR[yuwx] = incopy->FBAR[zvwx];
    out->F[yuwx] = incopy->F[zvwx];
    out->FBAR[vuyz] = incopy->FBAR[yuvz];
    out->F[vuyz] = incopy->F[yuvz];
    out->FBAR[vwxz] = incopy->FBAR[yuwx];
    out->F[vwxz] = incopy->F[yuwx];
    out->FBAR[zuvy] = incopy->FBAR[uvyz];
    out->F[zuvy] = incopy->F[uvyz];
    out->FBAR[zvwx] = incopy->FBAR[uwxy];
    out->F[zvwx] = incopy->F[uwxy];

    out->II[uvx] = incopy->II[vwy];
    out->II[xyz] = incopy->II[uwz];
    out->II[uxy] = incopy->II[vwz];
    out->II[vxz] = incopy->II[uwy];
    out->II[uwz] = incopy->II[uvx];
    out->II[vwy] = incopy->II[xyz];
    out->II[uwy] = incopy->II[vxz];
    out->II[vwz] = incopy->II[uxy];
    out->II[vyz] = incopy->II[uyz];
    out->II[wxy] = incopy->II[wxz];
    out->II[uvz] = incopy->II[uvy];
    out->II[uwx] = incopy->II[vwx];
    out->II[uyz] = incopy->II[uvz];
    out->II[wxz] = incopy->II[uwx];
    out->II[uvy] = incopy->II[vyz];
    out->II[vwx] = incopy->II[wxy];

    out->E[Ewuxy] = incopy->E[Evwxz];
    out->E[Evwxz] = incopy->E[Ewuxy];
    out->E[Euvyz] = incopy->E[Euvyz];
  }
  else if (perm == P356241) {
    out->u = incopy->w;
    out->v = incopy->y;
    out->w = incopy->z;
    out->x = incopy->v;
    out->y = incopy->x;
    out->z = incopy->u;

    out->G[wuzvy] = incopy->G[zuwxy];
    out->G[xuvyz] = incopy->G[vuxwy];
    out->G[uvxwz] = incopy->G[wuzvy];
    out->G[yvwxz] = incopy->G[xuvyz];
    out->G[vuxwy] = incopy->G[yvwxz];
    out->G[zuwxy] = incopy->G[uvxwz];

    out->FBAR[wuxy] = incopy->FBAR[zvwx];
    out->F[wuxy] = incopy->F[zvwx];
    out->FBAR[wvxz] = incopy->FBAR[zuvy];
    out->F[wvxz] = incopy->F[zuvy];
    out->FBAR[xuwy] = incopy->FBAR[vwxz];
    out->F[xuwy] = incopy->F[vwxz];
    out->FBAR[xvwz] = incopy->FBAR[vuyz];
    out->F[xvwz] = incopy->F[vuyz];
    out->FBAR[uvyz] = incopy->FBAR[wuxy];
    out->F[uvyz] = incopy->F[wuxy];
    out->FBAR[uwxy] = incopy->FBAR[wvxz];
    out->F[uwxy] = incopy->F[wvxz];
    out->FBAR[yuvz] = incopy->FBAR[xuwy];
    out->F[yuvz] = incopy->F[xuwy];
    out->FBAR[yuwx] = incopy->FBAR[xvwz];
    out->F[yuwx] = incopy->F[xvwz];
    out->FBAR[vuyz] = incopy->FBAR[yuwx];
    out->F[vuyz] = incopy->F[yuwx];
    out->FBAR[vwxz] = incopy->FBAR[yuvz];
    out->F[vwxz] = incopy->F[yuvz];
    out->FBAR[zuvy] = incopy->FBAR[uwxy];
    out->F[zuvy] = incopy->F[uwxy];
    out->FBAR[zvwx] = incopy->FBAR[uvyz];
    out->F[zvwx] = incopy->F[uvyz];

    out->II[uvx] = incopy->II[vwy];
    out->II[xyz] = incopy->II[uvx];
    out->II[uxy] = incopy->II[vwx];
    out->II[vxz] = incopy->II[uvy];
    out->II[uwz] = incopy->II[uwz];
    out->II[vwy] = incopy->II[xyz];
    out->II[uwy] = incopy->II[wxz];
    out->II[vwz] = incopy->II[uyz];
    out->II[vyz] = incopy->II[uxy];
    out->II[wxy] = incopy->II[vxz];
    out->II[uvz] = incopy->II[uwy];
    out->II[uwx] = incopy->II[vwz];
    out->II[uyz] = incopy->II[uwx];
    out->II[wxz] = incopy->II[uvz];
    out->II[uvy] = incopy->II[wxy];
    out->II[vwx] = incopy->II[vyz];

    out->E[Ewuxy] = incopy->E[Evwxz];
    out->E[Evwxz] = incopy->E[Euvyz];
    out->E[Euvyz] = incopy->E[Ewuxy];
  }
  else if (perm == P425136) {
    out->u = incopy->x;
    out->v = incopy->v;
    out->w = incopy->y;
    out->x = incopy->u;
    out->y = incopy->w;
    out->z = incopy->z;

    out->G[wuzvy] = incopy->G[yvwxz];
    out->G[xuvyz] = incopy->G[uvxwz];
    out->G[uvxwz] = incopy->G[xuvyz];
    out->G[yvwxz] = incopy->G[wuzvy];
    out->G[vuxwy] = incopy->G[vuxwy];
    out->G[zuwxy] = incopy->G[zuwxy];

    out->FBAR[wuxy] = incopy->FBAR[yuwx];
    out->F[wuxy] = incopy->F[yuwx];
    out->FBAR[wvxz] = incopy->FBAR[yuvz];
    out->F[wvxz] = incopy->F[yuvz];
    out->FBAR[xuwy] = incopy->FBAR[uwxy];
    out->F[xuwy] = incopy->F[uwxy];
    out->FBAR[xvwz] = incopy->FBAR[uvyz];
    out->F[xvwz] = incopy->F[uvyz];
    out->FBAR[uvyz] = incopy->FBAR[xvwz];
    out->F[uvyz] = incopy->F[xvwz];
    out->FBAR[uwxy] = incopy->FBAR[xuwy];
    out->F[uwxy] = incopy->F[xuwy];
    out->FBAR[yuvz] = incopy->FBAR[wvxz];
    out->F[yuvz] = incopy->F[wvxz];
    out->FBAR[yuwx] = incopy->FBAR[wuxy];
    out->F[yuwx] = incopy->F[wuxy];
    out->FBAR[vuyz] = incopy->FBAR[vwxz];
    out->F[vuyz] = incopy->F[vwxz];
    out->FBAR[vwxz] = incopy->FBAR[vuyz];
    out->F[vwxz] = incopy->F[vuyz];
    out->FBAR[zuvy] = incopy->FBAR[zvwx];
    out->F[zuvy] = incopy->F[zvwx];
    out->FBAR[zvwx] = incopy->FBAR[zuvy];
    out->F[zvwx] = incopy->F[zuvy];

    out->II[uvx] = incopy->II[uvx];
    out->II[xyz] = incopy->II[uwz];
    out->II[uxy] = incopy->II[uwx];
    out->II[vxz] = incopy->II[uvz];
    out->II[uwz] = incopy->II[xyz];
    out->II[vwy] = incopy->II[vwy];
    out->II[uwy] = incopy->II[wxy];
    out->II[vwz] = incopy->II[vyz];
    out->II[vyz] = incopy->II[vwz];
    out->II[wxy] = incopy->II[uwy];
    out->II[uvz] = incopy->II[vxz];
    out->II[uwx] = incopy->II[uxy];
    out->II[uyz] = incopy->II[wxz];
    out->II[wxz] = incopy->II[uyz];
    out->II[uvy] = incopy->II[vwx];
    out->II[vwx] = incopy->II[uvy];

    out->E[Ewuxy] = incopy->E[Ewuxy];
    out->E[Evwxz] = incopy->E[Euvyz];
    out->E[Euvyz] = incopy->E[Evwxz];
  }
  else if (perm == P524316) {
    out->u = incopy->y;
    out->v = incopy->v;
    out->w = incopy->x;
    out->x = incopy->w;
    out->y = incopy->u;
    out->z = incopy->z;

    out->G[wuzvy] = incopy->G[xuvyz];
    out->G[xuvyz] = incopy->G[wuzvy];
    out->G[uvxwz] = incopy->G[yvwxz];
    out->G[yvwxz] = incopy->G[uvxwz];
    out->G[vuxwy] = incopy->G[vuxwy];
    out->G[zuwxy] = incopy->G[zuwxy];

    out->FBAR[wuxy] = incopy->FBAR[xuwy];
    out->F[wuxy] = incopy->F[xuwy];
    out->FBAR[wvxz] = incopy->FBAR[xvwz];
    out->F[wvxz] = incopy->F[xvwz];
    out->FBAR[xuwy] = incopy->FBAR[wuxy];
    out->F[xuwy] = incopy->F[wuxy];
    out->FBAR[xvwz] = incopy->FBAR[wvxz];
    out->F[xvwz] = incopy->F[wvxz];
    out->FBAR[uvyz] = incopy->FBAR[yuvz];
    out->F[uvyz] = incopy->F[yuvz];
    out->FBAR[uwxy] = incopy->FBAR[yuwx];
    out->F[uwxy] = incopy->F[yuwx];
    out->FBAR[yuvz] = incopy->FBAR[uvyz];
    out->F[yuvz] = incopy->F[uvyz];
    out->FBAR[yuwx] = incopy->FBAR[uwxy];
    out->F[yuwx] = incopy->F[uwxy];
    out->FBAR[vuyz] = incopy->FBAR[vuyz];
    out->F[vuyz] = incopy->F[vuyz];
    out->FBAR[vwxz] = incopy->FBAR[vwxz];
    out->F[vwxz] = incopy->F[vwxz];
    out->FBAR[zuvy] = incopy->FBAR[zuvy];
    out->F[zuvy] = incopy->F[zuvy];
    out->FBAR[zvwx] = incopy->FBAR[zvwx];
    out->F[zvwx] = incopy->F[zvwx];

    out->II[uvx] = incopy->II[vwy];
    out->II[xyz] = incopy->II[uwz];
    out->II[uxy] = incopy->II[uwy];
    out->II[vxz] = incopy->II[vwz];
    out->II[uwz] = incopy->II[xyz];
    out->II[vwy] = incopy->II[uvx];
    out->II[uwy] = incopy->II[uxy];
    out->II[vwz] = incopy->II[vxz];
    out->II[vyz] = incopy->II[uvz];
    out->II[wxy] = incopy->II[uwx];
    out->II[uvz] = incopy->II[vyz];
    out->II[uwx] = incopy->II[wxy];
    out->II[uyz] = incopy->II[uyz];
    out->II[wxz] = incopy->II[wxz];
    out->II[uvy] = incopy->II[uvy];
    out->II[vwx] = incopy->II[vwx];

    out->E[Ewuxy] = incopy->E[Ewuxy];
    out->E[Evwxz] = incopy->E[Evwxz];
    out->E[Euvyz] = incopy->E[Euvyz];
  }
  else if (perm == P563412) {
    out->u = incopy->y;
    out->v = incopy->z;
    out->w = incopy->w;
    out->x = incopy->x;
    out->y = incopy->u;
    out->z = incopy->v;

    out->G[wuzvy] = incopy->G[wuzvy];
    out->G[xuvyz] = incopy->G[xuvyz];
    out->G[uvxwz] = incopy->G[yvwxz];
    out->G[yvwxz] = incopy->G[uvxwz];
    out->G[vuxwy] = incopy->G[zuwxy];
    out->G[zuwxy] = incopy->G[vuxwy];

    out->FBAR[wuxy] = incopy->FBAR[wuxy];
    out->F[wuxy] = incopy->F[wuxy];
    out->FBAR[wvxz] = incopy->FBAR[wvxz];
    out->F[wvxz] = incopy->F[wvxz];
    out->FBAR[xuwy] = incopy->FBAR[xuwy];
    out->F[xuwy] = incopy->F[xuwy];
    out->FBAR[xvwz] = incopy->FBAR[xvwz];
    out->F[xvwz] = incopy->F[xvwz];
    out->FBAR[uvyz] = incopy->FBAR[yuvz];
    out->F[uvyz] = incopy->F[yuvz];
    out->FBAR[uwxy] = incopy->FBAR[yuwx];
    out->F[uwxy] = incopy->F[yuwx];
    out->FBAR[yuvz] = incopy->FBAR[uvyz];
    out->F[yuvz] = incopy->F[uvyz];
    out->FBAR[yuwx] = incopy->FBAR[uwxy];
    out->F[yuwx] = incopy->F[uwxy];
    out->FBAR[vuyz] = incopy->FBAR[zuvy];
    out->F[vuyz] = incopy->F[zuvy];
    out->FBAR[vwxz] = incopy->FBAR[zvwx];
    out->F[vwxz] = incopy->F[zvwx];
    out->FBAR[zuvy] = incopy->FBAR[vuyz];
    out->F[zuvy] = incopy->F[vuyz];
    out->FBAR[zvwx] = incopy->FBAR[vwxz];
    out->F[zvwx] = incopy->F[vwxz];

    out->II[uvx] = incopy->II[xyz];
    out->II[xyz] = incopy->II[uvx];
    out->II[uxy] = incopy->II[uxy];
    out->II[vxz] = incopy->II[vxz];
    out->II[uwz] = incopy->II[vwy];
    out->II[vwy] = incopy->II[uwz];
    out->II[uwy] = incopy->II[uwy];
    out->II[vwz] = incopy->II[vwz];
    out->II[vyz] = incopy->II[uvz];
    out->II[wxy] = incopy->II[uwx];
    out->II[uvz] = incopy->II[vyz];
    out->II[uwx] = incopy->II[wxy];
    out->II[uyz] = incopy->II[uvy];
    out->II[wxz] = incopy->II[vwx];
    out->II[uvy] = incopy->II[uyz];
    out->II[vwx] = incopy->II[wxz];

    out->E[Ewuxy] = incopy->E[Ewuxy];
    out->E[Evwxz] = incopy->E[Evwxz];
    out->E[Euvyz] = incopy->E[Euvyz];
  }
  else if (perm == P641523) {
    out->u = incopy->z;
    out->v = incopy->x;
    out->w = incopy->u;
    out->x = incopy->y;
    out->y = incopy->v;
    out->z = incopy->w;

    out->G[wuzvy] = incopy->G[uvxwz];
    out->G[xuvyz] = incopy->G[yvwxz];
    out->G[uvxwz] = incopy->G[zuwxy];
    out->G[yvwxz] = incopy->G[vuxwy];
    out->G[vuxwy] = incopy->G[xuvyz];
    out->G[zuwxy] = incopy->G[wuzvy];

    out->FBAR[wuxy] = incopy->FBAR[uvyz];
    out->F[wuxy] = incopy->F[uvyz];
    out->FBAR[wvxz] = incopy->FBAR[uwxy];
    out->F[wvxz] = incopy->F[uwxy];
    out->FBAR[xuwy] = incopy->FBAR[yuvz];
    out->F[xuwy] = incopy->F[yuvz];
    out->FBAR[xvwz] = incopy->FBAR[yuwx];
    out->F[xvwz] = incopy->F[yuwx];
    out->FBAR[uvyz] = incopy->FBAR[zvwx];
    out->F[uvyz] = incopy->F[zvwx];
    out->FBAR[uwxy] = incopy->FBAR[zuvy];
    out->F[uwxy] = incopy->F[zuvy];
    out->FBAR[yuvz] = incopy->FBAR[vwxz];
    out->F[yuvz] = incopy->F[vwxz];
    out->FBAR[yuwx] = incopy->FBAR[vuyz];
    out->F[yuwx] = incopy->F[vuyz];
    out->FBAR[vuyz] = incopy->FBAR[xvwz];
    out->F[vuyz] = incopy->F[xvwz];
    out->FBAR[vwxz] = incopy->FBAR[xuwy];
    out->F[vwxz] = incopy->F[xuwy];
    out->FBAR[zuvy] = incopy->FBAR[wvxz];
    out->F[zuvy] = incopy->F[wvxz];
    out->FBAR[zvwx] = incopy->FBAR[wuxy];
    out->F[zvwx] = incopy->F[wuxy];

    out->II[uvx] = incopy->II[xyz];
    out->II[xyz] = incopy->II[vwy];
    out->II[uxy] = incopy->II[vyz];
    out->II[vxz] = incopy->II[wxy];
    out->II[uwz] = incopy->II[uwz];
    out->II[vwy] = incopy->II[uvx];
    out->II[uwy] = incopy->II[uvz];
    out->II[vwz] = incopy->II[uwx];
    out->II[vyz] = incopy->II[vwx];
    out->II[wxy] = incopy->II[uvy];
    out->II[uvz] = incopy->II[wxz];
    out->II[uwx] = incopy->II[uyz];
    out->II[uyz] = incopy->II[vwz];
    out->II[wxz] = incopy->II[uwy];
    out->II[uvy] = incopy->II[vxz];
    out->II[vwx] = incopy->II[uxy];

    out->E[Ewuxy] = incopy->E[Euvyz];
    out->E[Evwxz] = incopy->E[Ewuxy];
    out->E[Euvyz] = incopy->E[Evwxz];
  }
  else if (perm == P146253) {
    out->u = incopy->u;
    out->v = incopy->x;
    out->w = incopy->z;
    out->x = incopy->v;
    out->y = incopy->y;
    out->z = incopy->w;

    out->G[wuzvy] = incopy->G[zuwxy];
    out->G[xuvyz] = incopy->G[vuxwy];
    out->G[uvxwz] = incopy->G[uvxwz];
    out->G[yvwxz] = incopy->G[yvwxz];
    out->G[vuxwy] = incopy->G[xuvyz];
    out->G[zuwxy] = incopy->G[wuzvy];

    out->FBAR[wuxy] = incopy->FBAR[zuvy];
    out->F[wuxy] = incopy->F[zuvy];
    out->FBAR[wvxz] = incopy->FBAR[zvwx];
    out->F[wvxz] = incopy->F[zvwx];
    out->FBAR[xuwy] = incopy->FBAR[vuyz];
    out->F[xuwy] = incopy->F[vuyz];
    out->FBAR[xvwz] = incopy->FBAR[vwxz];
    out->F[xvwz] = incopy->F[vwxz];
    out->FBAR[uvyz] = incopy->FBAR[uwxy];
    out->F[uvyz] = incopy->F[uwxy];
    out->FBAR[uwxy] = incopy->FBAR[uvyz];
    out->F[uwxy] = incopy->F[uvyz];
    out->FBAR[yuvz] = incopy->FBAR[yuwx];
    out->F[yuvz] = incopy->F[yuwx];
    out->FBAR[yuwx] = incopy->FBAR[yuvz];
    out->F[yuwx] = incopy->F[yuvz];
    out->FBAR[vuyz] = incopy->FBAR[xuwy];
    out->F[vuyz] = incopy->F[xuwy];
    out->FBAR[vwxz] = incopy->FBAR[xvwz];
    out->F[vwxz] = incopy->F[xvwz];
    out->FBAR[zuvy] = incopy->FBAR[wuxy];
    out->F[zuvy] = incopy->F[wuxy];
    out->FBAR[zvwx] = incopy->FBAR[wvxz];
    out->F[zvwx] = incopy->F[wvxz];

    out->II[uvx] = incopy->II[uvx];
    out->II[xyz] = incopy->II[vwy];
    out->II[uxy] = incopy->II[uvy];
    out->II[vxz] = incopy->II[vwx];
    out->II[uwz] = incopy->II[uwz];
    out->II[vwy] = incopy->II[xyz];
    out->II[uwy] = incopy->II[uyz];
    out->II[vwz] = incopy->II[wxz];
    out->II[vyz] = incopy->II[wxy];
    out->II[wxy] = incopy->II[vyz];
    out->II[uvz] = incopy->II[uwx];
    out->II[uwx] = incopy->II[uvz];
    out->II[uyz] = incopy->II[uwy];
    out->II[wxz] = incopy->II[vwz];
    out->II[uvy] = incopy->II[uxy];
    out->II[vwx] = incopy->II[vxz];

    out->E[Ewuxy] = incopy->E[Euvyz];
    out->E[Evwxz] = incopy->E[Evwxz];
    out->E[Euvyz] = incopy->E[Ewuxy];
  }
  else if (perm == P231564) {
    out->u = incopy->v;
    out->v = incopy->w;
    out->w = incopy->u;
    out->x = incopy->y;
    out->y = incopy->z;
    out->z = incopy->x;

    out->G[wuzvy] = incopy->G[uvxwz];
    out->G[xuvyz] = incopy->G[yvwxz];
    out->G[uvxwz] = incopy->G[vuxwy];
    out->G[yvwxz] = incopy->G[zuwxy];
    out->G[vuxwy] = incopy->G[wuzvy];
    out->G[zuwxy] = incopy->G[xuvyz];

    out->FBAR[wuxy] = incopy->FBAR[uvyz];
    out->F[wuxy] = incopy->F[uvyz];
    out->FBAR[wvxz] = incopy->FBAR[uwxy];
    out->F[wvxz] = incopy->F[uwxy];
    out->FBAR[xuwy] = incopy->FBAR[yuvz];
    out->F[xuwy] = incopy->F[yuvz];
    out->FBAR[xvwz] = incopy->FBAR[yuwx];
    out->F[xvwz] = incopy->F[yuwx];
    out->FBAR[uvyz] = incopy->FBAR[vwxz];
    out->F[uvyz] = incopy->F[vwxz];
    out->FBAR[uwxy] = incopy->FBAR[vuyz];
    out->F[uwxy] = incopy->F[vuyz];
    out->FBAR[yuvz] = incopy->FBAR[zvwx];
    out->F[yuvz] = incopy->F[zvwx];
    out->FBAR[yuwx] = incopy->FBAR[zuvy];
    out->F[yuwx] = incopy->F[zuvy];
    out->FBAR[vuyz] = incopy->FBAR[wvxz];
    out->F[vuyz] = incopy->F[wvxz];
    out->FBAR[vwxz] = incopy->FBAR[wuxy];
    out->F[vwxz] = incopy->F[wuxy];
    out->FBAR[zuvy] = incopy->FBAR[xvwz];
    out->F[zuvy] = incopy->F[xvwz];
    out->FBAR[zvwx] = incopy->FBAR[xuwy];
    out->F[zvwx] = incopy->F[xuwy];

    out->II[uvx] = incopy->II[vwy];
    out->II[xyz] = incopy->II[xyz];
    out->II[uxy] = incopy->II[vyz];
    out->II[vxz] = incopy->II[wxy];
    out->II[uwz] = incopy->II[uvx];
    out->II[vwy] = incopy->II[uwz];
    out->II[uwy] = incopy->II[uvz];
    out->II[vwz] = incopy->II[uwx];
    out->II[vyz] = incopy->II[wxz];
    out->II[wxy] = incopy->II[uyz];
    out->II[uvz] = incopy->II[vwx];
    out->II[uwx] = incopy->II[uvy];
    out->II[uyz] = incopy->II[vxz];
    out->II[wxz] = incopy->II[uxy];
    out->II[uvy] = incopy->II[vwz];
    out->II[vwx] = incopy->II[uwy];

    out->E[Ewuxy] = incopy->E[Euvyz];
    out->E[Evwxz] = incopy->E[Ewuxy];
    out->E[Euvyz] = incopy->E[Evwxz];
  }
  else if (perm == P312645) {
    out->u = incopy->w;
    out->v = incopy->u;
    out->w = incopy->v;
    out->x = incopy->z;
    out->y = incopy->x;
    out->z = incopy->y;

    out->G[wuzvy] = incopy->G[vuxwy];
    out->G[xuvyz] = incopy->G[zuwxy];
    out->G[uvxwz] = incopy->G[wuzvy];
    out->G[yvwxz] = incopy->G[xuvyz];
    out->G[vuxwy] = incopy->G[uvxwz];
    out->G[zuwxy] = incopy->G[yvwxz];

    out->FBAR[wuxy] = incopy->FBAR[vwxz];
    out->F[wuxy] = incopy->F[vwxz];
    out->FBAR[wvxz] = incopy->FBAR[vuyz];
    out->F[wvxz] = incopy->F[vuyz];
    out->FBAR[xuwy] = incopy->FBAR[zvwx];
    out->F[xuwy] = incopy->F[zvwx];
    out->FBAR[xvwz] = incopy->FBAR[zuvy];
    out->F[xvwz] = incopy->F[zuvy];
    out->FBAR[uvyz] = incopy->FBAR[wuxy];
    out->F[uvyz] = incopy->F[wuxy];
    out->FBAR[uwxy] = incopy->FBAR[wvxz];
    out->F[uwxy] = incopy->F[wvxz];
    out->FBAR[yuvz] = incopy->FBAR[xuwy];
    out->F[yuvz] = incopy->F[xuwy];
    out->FBAR[yuwx] = incopy->FBAR[xvwz];
    out->F[yuwx] = incopy->F[xvwz];
    out->FBAR[vuyz] = incopy->FBAR[uwxy];
    out->F[vuyz] = incopy->F[uwxy];
    out->FBAR[vwxz] = incopy->FBAR[uvyz];
    out->F[vwxz] = incopy->F[uvyz];
    out->FBAR[zuvy] = incopy->FBAR[yuwx];
    out->F[zuvy] = incopy->F[yuwx];
    out->FBAR[zvwx] = incopy->FBAR[yuvz];
    out->F[zvwx] = incopy->F[yuvz];

    out->II[uvx] = incopy->II[uwz];
    out->II[xyz] = incopy->II[xyz];
    out->II[uxy] = incopy->II[wxz];
    out->II[vxz] = incopy->II[uyz];
    out->II[uwz] = incopy->II[vwy];
    out->II[vwy] = incopy->II[uvx];
    out->II[uwy] = incopy->II[vwx];
    out->II[vwz] = incopy->II[uvy];
    out->II[vyz] = incopy->II[uxy];
    out->II[wxy] = incopy->II[vxz];
    out->II[uvz] = incopy->II[uwy];
    out->II[uwx] = incopy->II[vwz];
    out->II[uyz] = incopy->II[wxy];
    out->II[wxz] = incopy->II[vyz];
    out->II[uvy] = incopy->II[uwx];
    out->II[vwx] = incopy->II[uvz];

    out->E[Ewuxy] = incopy->E[Evwxz];
    out->E[Evwxz] = incopy->E[Euvyz];
    out->E[Euvyz] = incopy->E[Ewuxy];
  }
  else if (perm == P365142) {
    out->u = incopy->w;
    out->v = incopy->z;
    out->w = incopy->y;
    out->x = incopy->u;
    out->y = incopy->x;
    out->z = incopy->v;

    out->G[wuzvy] = incopy->G[yvwxz];
    out->G[xuvyz] = incopy->G[uvxwz];
    out->G[uvxwz] = incopy->G[wuzvy];
    out->G[yvwxz] = incopy->G[xuvyz];
    out->G[vuxwy] = incopy->G[zuwxy];
    out->G[zuwxy] = incopy->G[vuxwy];

    out->FBAR[wuxy] = incopy->FBAR[yuwx];
    out->F[wuxy] = incopy->F[yuwx];
    out->FBAR[wvxz] = incopy->FBAR[yuvz];
    out->F[wvxz] = incopy->F[yuvz];
    out->FBAR[xuwy] = incopy->FBAR[uwxy];
    out->F[xuwy] = incopy->F[uwxy];
    out->FBAR[xvwz] = incopy->FBAR[uvyz];
    out->F[xvwz] = incopy->F[uvyz];
    out->FBAR[uvyz] = incopy->FBAR[wvxz];
    out->F[uvyz] = incopy->F[wvxz];
    out->FBAR[uwxy] = incopy->FBAR[wuxy];
    out->F[uwxy] = incopy->F[wuxy];
    out->FBAR[yuvz] = incopy->FBAR[xvwz];
    out->F[yuvz] = incopy->F[xvwz];
    out->FBAR[yuwx] = incopy->FBAR[xuwy];
    out->F[yuwx] = incopy->F[xuwy];
    out->FBAR[vuyz] = incopy->FBAR[zvwx];
    out->F[vuyz] = incopy->F[zvwx];
    out->FBAR[vwxz] = incopy->FBAR[zuvy];
    out->F[vwxz] = incopy->F[zuvy];
    out->FBAR[zuvy] = incopy->FBAR[vwxz];
    out->F[zuvy] = incopy->F[vwxz];
    out->FBAR[zvwx] = incopy->FBAR[vuyz];
    out->F[zvwx] = incopy->F[vuyz];

    out->II[uvx] = incopy->II[uwz];
    out->II[xyz] = incopy->II[uvx];
    out->II[uxy] = incopy->II[uwx];
    out->II[vxz] = incopy->II[uvz];
    out->II[uwz] = incopy->II[vwy];
    out->II[vwy] = incopy->II[xyz];
    out->II[uwy] = incopy->II[wxy];
    out->II[vwz] = incopy->II[vyz];
    out->II[vyz] = incopy->II[vxz];
    out->II[wxy] = incopy->II[uxy];
    out->II[uvz] = incopy->II[vwz];
    out->II[uwx] = incopy->II[uwy];
    out->II[uyz] = incopy->II[vwx];
    out->II[wxz] = incopy->II[uvy];
    out->II[uvy] = incopy->II[wxz];
    out->II[vwx] = incopy->II[uyz];

    out->E[Ewuxy] = incopy->E[Ewuxy];
    out->E[Evwxz] = incopy->E[Euvyz];
    out->E[Euvyz] = incopy->E[Evwxz];
  }
  else if (perm == P452631) {
    out->u = incopy->x;
    out->v = incopy->y;
    out->w = incopy->v;
    out->x = incopy->z;
    out->y = incopy->w;
    out->z = incopy->u;

    out->G[wuzvy] = incopy->G[vuxwy];
    out->G[xuvyz] = incopy->G[zuwxy];
    out->G[uvxwz] = incopy->G[xuvyz];
    out->G[yvwxz] = incopy->G[wuzvy];
    out->G[vuxwy] = incopy->G[yvwxz];
    out->G[zuwxy] = incopy->G[uvxwz];

    out->FBAR[wuxy] = incopy->FBAR[vwxz];
    out->F[wuxy] = incopy->F[vwxz];
    out->FBAR[wvxz] = incopy->FBAR[vuyz];
    out->F[wvxz] = incopy->F[vuyz];
    out->FBAR[xuwy] = incopy->FBAR[zvwx];
    out->F[xuwy] = incopy->F[zvwx];
    out->FBAR[xvwz] = incopy->FBAR[zuvy];
    out->F[xvwz] = incopy->F[zuvy];
    out->FBAR[uvyz] = incopy->FBAR[xuwy];
    out->F[uvyz] = incopy->F[xuwy];
    out->FBAR[uwxy] = incopy->FBAR[xvwz];
    out->F[uwxy] = incopy->F[xvwz];
    out->FBAR[yuvz] = incopy->FBAR[wuxy];
    out->F[yuvz] = incopy->F[wuxy];
    out->FBAR[yuwx] = incopy->FBAR[wvxz];
    out->F[yuwx] = incopy->F[wvxz];
    out->FBAR[vuyz] = incopy->FBAR[yuwx];
    out->F[vuyz] = incopy->F[yuwx];
    out->FBAR[vwxz] = incopy->FBAR[yuvz];
    out->F[vwxz] = incopy->F[yuvz];
    out->FBAR[zuvy] = incopy->FBAR[uwxy];
    out->F[zuvy] = incopy->F[uwxy];
    out->FBAR[zvwx] = incopy->FBAR[uvyz];
    out->F[zvwx] = incopy->F[uvyz];

    out->II[uvx] = incopy->II[xyz];
    out->II[xyz] = incopy->II[uwz];
    out->II[uxy] = incopy->II[wxz];
    out->II[vxz] = incopy->II[uyz];
    out->II[uwz] = incopy->II[uvx];
    out->II[vwy] = incopy->II[vwy];
    out->II[uwy] = incopy->II[vwx];
    out->II[vwz] = incopy->II[uvy];
    out->II[vyz] = incopy->II[uwy];
    out->II[wxy] = incopy->II[vwz];
    out->II[uvz] = incopy->II[uxy];
    out->II[uwx] = incopy->II[vxz];
    out->II[uyz] = incopy->II[uwx];
    out->II[wxz] = incopy->II[uvz];
    out->II[uvy] = incopy->II[wxy];
    out->II[vwx] = incopy->II[vyz];

    out->E[Ewuxy] = incopy->E[Evwxz];
    out->E[Evwxz] = incopy->E[Euvyz];
    out->E[Euvyz] = incopy->E[Ewuxy];
  }
  else if (perm == P536214) {
    out->u = incopy->y;
    out->v = incopy->w;
    out->w = incopy->z;
    out->x = incopy->v;
    out->y = incopy->u;
    out->z = incopy->x;

    out->G[wuzvy] = incopy->G[zuwxy];
    out->G[xuvyz] = incopy->G[vuxwy];
    out->G[uvxwz] = incopy->G[yvwxz];
    out->G[yvwxz] = incopy->G[uvxwz];
    out->G[vuxwy] = incopy->G[wuzvy];
    out->G[zuwxy] = incopy->G[xuvyz];

    out->FBAR[wuxy] = incopy->FBAR[zuvy];
    out->F[wuxy] = incopy->F[zuvy];
    out->FBAR[wvxz] = incopy->FBAR[zvwx];
    out->F[wvxz] = incopy->F[zvwx];
    out->FBAR[xuwy] = incopy->FBAR[vuyz];
    out->F[xuwy] = incopy->F[vuyz];
    out->FBAR[xvwz] = incopy->FBAR[vwxz];
    out->F[xvwz] = incopy->F[vwxz];
    out->FBAR[uvyz] = incopy->FBAR[yuwx];
    out->F[uvyz] = incopy->F[yuwx];
    out->FBAR[uwxy] = incopy->FBAR[yuvz];
    out->F[uwxy] = incopy->F[yuvz];
    out->FBAR[yuvz] = incopy->FBAR[uwxy];
    out->F[yuvz] = incopy->F[uwxy];
    out->FBAR[yuwx] = incopy->FBAR[uvyz];
    out->F[yuwx] = incopy->F[uvyz];
    out->FBAR[vuyz] = incopy->FBAR[wuxy];
    out->F[vuyz] = incopy->F[wuxy];
    out->FBAR[vwxz] = incopy->FBAR[wvxz];
    out->F[vwxz] = incopy->F[wvxz];
    out->FBAR[zuvy] = incopy->FBAR[xuwy];
    out->F[zuvy] = incopy->F[xuwy];
    out->FBAR[zvwx] = incopy->FBAR[xvwz];
    out->F[zvwx] = incopy->F[xvwz];

    out->II[uvx] = incopy->II[vwy];
    out->II[xyz] = incopy->II[uvx];
    out->II[uxy] = incopy->II[uvy];
    out->II[vxz] = incopy->II[vwx];
    out->II[uwz] = incopy->II[xyz];
    out->II[vwy] = incopy->II[uwz];
    out->II[uwy] = incopy->II[uyz];
    out->II[vwz] = incopy->II[wxz];
    out->II[vyz] = incopy->II[uwx];
    out->II[wxy] = incopy->II[uvz];
    out->II[uvz] = incopy->II[wxy];
    out->II[uwx] = incopy->II[vyz];
    out->II[uyz] = incopy->II[uxy];
    out->II[wxz] = incopy->II[vxz];
    out->II[uvy] = incopy->II[uwy];
    out->II[vwx] = incopy->II[vwz];

    out->E[Ewuxy] = incopy->E[Euvyz];
    out->E[Evwxz] = incopy->E[Evwxz];
    out->E[Euvyz] = incopy->E[Ewuxy];
  }
  else if (perm == P614325) {
    out->u = incopy->z;
    out->v = incopy->u;
    out->w = incopy->x;
    out->x = incopy->w;
    out->y = incopy->v;
    out->z = incopy->y;

    out->G[wuzvy] = incopy->G[xuvyz];
    out->G[xuvyz] = incopy->G[wuzvy];
    out->G[uvxwz] = incopy->G[zuwxy];
    out->G[yvwxz] = incopy->G[vuxwy];
    out->G[vuxwy] = incopy->G[uvxwz];
    out->G[zuwxy] = incopy->G[yvwxz];

    out->FBAR[wuxy] = incopy->FBAR[xvwz];
    out->F[wuxy] = incopy->F[xvwz];
    out->FBAR[wvxz] = incopy->FBAR[xuwy];
    out->F[wvxz] = incopy->F[xuwy];
    out->FBAR[xuwy] = incopy->FBAR[wvxz];
    out->F[xuwy] = incopy->F[wvxz];
    out->FBAR[xvwz] = incopy->FBAR[wuxy];
    out->F[xvwz] = incopy->F[wuxy];
    out->FBAR[uvyz] = incopy->FBAR[zuvy];
    out->F[uvyz] = incopy->F[zuvy];
    out->FBAR[uwxy] = incopy->FBAR[zvwx];
    out->F[uwxy] = incopy->F[zvwx];
    out->FBAR[yuvz] = incopy->FBAR[vuyz];
    out->F[yuvz] = incopy->F[vuyz];
    out->FBAR[yuwx] = incopy->FBAR[vwxz];
    out->F[yuwx] = incopy->F[vwxz];
    out->FBAR[vuyz] = incopy->FBAR[uvyz];
    out->F[vuyz] = incopy->F[uvyz];
    out->FBAR[vwxz] = incopy->FBAR[uwxy];
    out->F[vwxz] = incopy->F[uwxy];
    out->FBAR[zuvy] = incopy->FBAR[yuvz];
    out->F[zuvy] = incopy->F[yuvz];
    out->FBAR[zvwx] = incopy->FBAR[yuwx];
    out->F[zvwx] = incopy->F[yuwx];

    out->II[uvx] = incopy->II[uwz];
    out->II[xyz] = incopy->II[vwy];
    out->II[uxy] = incopy->II[vwz];
    out->II[vxz] = incopy->II[uwy];
    out->II[uwz] = incopy->II[xyz];
    out->II[vwy] = incopy->II[uvx];
    out->II[uwy] = incopy->II[vxz];
    out->II[vwz] = incopy->II[uxy];
    out->II[vyz] = incopy->II[uvy];
    out->II[wxy] = incopy->II[vwx];
    out->II[uvz] = incopy->II[uyz];
    out->II[uwx] = incopy->II[wxz];
    out->II[uyz] = incopy->II[vyz];
    out->II[wxz] = incopy->II[wxy];
    out->II[uvy] = incopy->II[uvz];
    out->II[vwx] = incopy->II[uwx];

    out->E[Ewuxy] = incopy->E[Evwxz];
    out->E[Evwxz] = incopy->E[Ewuxy];
    out->E[Euvyz] = incopy->E[Euvyz];
  }
  else if (perm == P653421) {
    out->u = incopy->z;
    out->v = incopy->y;
    out->w = incopy->w;
    out->x = incopy->x;
    out->y = incopy->v;
    out->z = incopy->u;

    out->G[wuzvy] = incopy->G[wuzvy];
    out->G[xuvyz] = incopy->G[xuvyz];
    out->G[uvxwz] = incopy->G[zuwxy];
    out->G[yvwxz] = incopy->G[vuxwy];
    out->G[vuxwy] = incopy->G[yvwxz];
    out->G[zuwxy] = incopy->G[uvxwz];

    out->FBAR[wuxy] = incopy->FBAR[wvxz];
    out->F[wuxy] = incopy->F[wvxz];
    out->FBAR[wvxz] = incopy->FBAR[wuxy];
    out->F[wvxz] = incopy->F[wuxy];
    out->FBAR[xuwy] = incopy->FBAR[xvwz];
    out->F[xuwy] = incopy->F[xvwz];
    out->FBAR[xvwz] = incopy->FBAR[xuwy];
    out->F[xvwz] = incopy->F[xuwy];
    out->FBAR[uvyz] = incopy->FBAR[zuvy];
    out->F[uvyz] = incopy->F[zuvy];
    out->FBAR[uwxy] = incopy->FBAR[zvwx];
    out->F[uwxy] = incopy->F[zvwx];
    out->FBAR[yuvz] = incopy->FBAR[vuyz];
    out->F[yuvz] = incopy->F[vuyz];
    out->FBAR[yuwx] = incopy->FBAR[vwxz];
    out->F[yuwx] = incopy->F[vwxz];
    out->FBAR[vuyz] = incopy->FBAR[yuvz];
    out->F[vuyz] = incopy->F[yuvz];
    out->FBAR[vwxz] = incopy->FBAR[yuwx];
    out->F[vwxz] = incopy->F[yuwx];
    out->FBAR[zuvy] = incopy->FBAR[uvyz];
    out->F[zuvy] = incopy->F[uvyz];
    out->FBAR[zvwx] = incopy->FBAR[uwxy];
    out->F[zvwx] = incopy->F[uwxy];

    out->II[uvx] = incopy->II[xyz];
    out->II[xyz] = incopy->II[uvx];
    out->II[uxy] = incopy->II[vxz];
    out->II[vxz] = incopy->II[uxy];
    out->II[uwz] = incopy->II[uwz];
    out->II[vwy] = incopy->II[vwy];
    out->II[uwy] = incopy->II[vwz];
    out->II[vwz] = incopy->II[uwy];
    out->II[vyz] = incopy->II[uvy];
    out->II[wxy] = incopy->II[vwx];
    out->II[uvz] = incopy->II[uyz];
    out->II[uwx] = incopy->II[wxz];
    out->II[uyz] = incopy->II[uvz];
    out->II[wxz] = incopy->II[uwx];
    out->II[uvy] = incopy->II[vyz];
    out->II[vwx] = incopy->II[wxy];

    out->E[Ewuxy] = incopy->E[Evwxz];
    out->E[Evwxz] = incopy->E[Ewuxy];
    out->E[Euvyz] = incopy->E[Euvyz];
  }
  else if (perm == P123456) {
    out->u = incopy->u;
    out->v = incopy->v;
    out->w = incopy->w;
    out->x = incopy->x;
    out->y = incopy->y;
    out->z = incopy->z;

    out->G[wuzvy] = incopy->G[wuzvy];
    out->G[xuvyz] = incopy->G[xuvyz];
    out->G[uvxwz] = incopy->G[uvxwz];
    out->G[yvwxz] = incopy->G[yvwxz];
    out->G[vuxwy] = incopy->G[vuxwy];
    out->G[zuwxy] = incopy->G[zuwxy];

    out->FBAR[wuxy] = incopy->FBAR[wuxy];
    out->F[wuxy] = incopy->F[wuxy];
    out->FBAR[wvxz] = incopy->FBAR[wvxz];
    out->F[wvxz] = incopy->F[wvxz];
    out->FBAR[xuwy] = incopy->FBAR[xuwy];
    out->F[xuwy] = incopy->F[xuwy];
    out->FBAR[xvwz] = incopy->FBAR[xvwz];
    out->F[xvwz] = incopy->F[xvwz];
    out->FBAR[uvyz] = incopy->FBAR[uvyz];
    out->F[uvyz] = incopy->F[uvyz];
    out->FBAR[uwxy] = incopy->FBAR[uwxy];
    out->F[uwxy] = incopy->F[uwxy];
    out->FBAR[yuvz] = incopy->FBAR[yuvz];
    out->F[yuvz] = incopy->F[yuvz];
    out->FBAR[yuwx] = incopy->FBAR[yuwx];
    out->F[yuwx] = incopy->F[yuwx];
    out->FBAR[vuyz] = incopy->FBAR[vuyz];
    out->F[vuyz] = incopy->F[vuyz];
    out->FBAR[vwxz] = incopy->FBAR[vwxz];
    out->F[vwxz] = incopy->F[vwxz];
    out->FBAR[zuvy] = incopy->FBAR[zuvy];
    out->F[zuvy] = incopy->F[zuvy];
    out->FBAR[zvwx] = incopy->FBAR[zvwx];
    out->F[zvwx] = incopy->F[zvwx];

    out->II[uvx] = incopy->II[uvx];
    out->II[xyz] = incopy->II[xyz];
    out->II[uxy] = incopy->II[uxy];
    out->II[vxz] = incopy->II[vxz];
    out->II[uwz] = incopy->II[uwz];
    out->II[vwy] = incopy->II[vwy];
    out->II[uwy] = incopy->II[uwy];
    out->II[vwz] = incopy->II[vwz];
    out->II[vyz] = incopy->II[vyz];
    out->II[wxy] = incopy->II[wxy];
    out->II[uvz] = incopy->II[uvz];
    out->II[uwx] = incopy->II[uwx];
    out->II[uyz] = incopy->II[uyz];
    out->II[wxz] = incopy->II[wxz];
    out->II[uvy] = incopy->II[uvy];
    out->II[vwx] = incopy->II[vwx];

    out->E[Ewuxy] = incopy->E[Ewuxy];
    out->E[Evwxz] = incopy->E[Evwxz];
    out->E[Euvyz] = incopy->E[Euvyz];
  }
  else 
    TVIL_Error ("PermuteResult", "Bad permutation specified.", 111);

  /* DGR Kludged for now: */
  TVIL_SetBold (out);

  if (in == out)
    free (incopy);

  return;
}
