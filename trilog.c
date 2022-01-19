#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <float.h>
#include "internal.h"

/* Local routines: */
TVIL_COMPLEX TVIL_Trilogoutofunitdisk (TVIL_COMPLEX);
TVIL_COMPLEX TVIL_Trilogunitdisk (TVIL_COMPLEX);
TVIL_COMPLEX TVIL_TrilogCLZseries (TVIL_COMPLEX);
TVIL_COMPLEX TVIL_Trilogseries (TVIL_COMPLEX);
TVIL_COMPLEX TVIL_TrilogregionA (TVIL_COMPLEX);
TVIL_COMPLEX TVIL_TrilogregionB (TVIL_COMPLEX);

#define cZeta2 1.644934066848226436472415166646025189219L
#define cZeta3 1.202056903159594285399738161511449990765L
#define PI_longdouble 3.141592653589793238462643383279502884197L

#define trilog_CLZseries_radius 1.2L
#define trilog_powerseries_radius 0.786152L

/*
  Descriptions of the regions inside the unit disk:
   "CLZseries" is for |ln(z)| < trilog_CLZseries_radius and |z|<1;
    Otherwise,
   "series" is for |z| <= trilog_powerseries_radius
   "A" is for Re(z) <= 0 and trilog_powerseries_radius < |z| <= 1.
   "B" is for Re(z) > 0 and trilog_powerseries_radius < |z| <= 1.
*/

/* ************************************************************** */

TVIL_COMPLEX TVIL_Trilog (TVIL_COMPLEX z)
{
  TVIL_COMPLEX result;
  
  if (TVIL_CABS(z) > 1.0L)
    result = TVIL_Trilogoutofunitdisk (z);
  else
    result = TVIL_Trilogunitdisk (z);

  return result;
}

/* ************************************************************** */

TVIL_COMPLEX TVIL_Trilogoutofunitdisk (TVIL_COMPLEX z)
{
  TVIL_COMPLEX result;
  TVIL_COMPLEX logminusz = TVIL_CLOG(-z);

  if (TVIL_CREAL(z) > 1.0L && TVIL_CIMAG((complex double) z) == 0.0)
    logminusz = I * PI_longdouble + TVIL_CLOG(TVIL_CREAL (z));

  result = TVIL_Trilogunitdisk (1.0L/z) -
    logminusz*(cZeta2 + logminusz*logminusz/6.0L);

  return result;
}

/* ************************************************************** */

TVIL_COMPLEX TVIL_Trilogunitdisk (TVIL_COMPLEX z)
{
  TVIL_COMPLEX result;
  TVIL_REAL rez = TVIL_CREAL (z);
  TVIL_REAL absz = TVIL_CABS (z);
  TVIL_REAL absimz = TVIL_FABS (TVIL_CIMAG (z));

  if (TVIL_CABS(z - 1.0L) < 2.0L * TVIL_TOL)
    result = cZeta3;
  else if (TVIL_CABS(z) < 2.0L * TVIL_TOL)
    result = 0.0L;
  else if (TVIL_CABS(TVIL_CLOG(z)) < trilog_CLZseries_radius)
    result = TVIL_TrilogCLZseries (z);
  else if (absz <= trilog_powerseries_radius)
    result = TVIL_Trilogseries (z);
  else if (rez <= 0.0L)
    result = TVIL_TrilogregionA (z);
  else if (rez <= absimz)
    result = TVIL_TrilogregionB (z);
  else {
    TVIL_Warn("TVIL_Trilogunitdisk", "trilog function yielding undefined result.");
    result = TVIL_ComplexInfinity;
  }

  return result;
}

/* ************************************************************** */
/* 
   The following is based on the formula by Cohen, Lewin and Zagier.
   It should converge for |ln(z)| < 2 Pi, but is used here only for
   |ln(z)| < trilog_CLZseries_radius. It seems to have a branch cut
   problem for real z > 1, but here it is only used within the unit
   disk anyway. */

TVIL_COMPLEX TVIL_TrilogCLZseries(TVIL_COMPLEX z)
{
  TVIL_COMPLEX logz, logzsquared, logztothek, term;
  TVIL_COMPLEX first6terms, remainingterms, result;
  TVIL_REAL accuracygoal;
  int j;

  TVIL_COMPLEX CLZcoeffs_trilog[] = {
    -9.841899722852103804484756865709246661628e-8L,
    1.14822163433274544385655496766607877719e-9L,
    -1.581572499080916589334097751606169114587e-11L,
    2.419500979252515194527327015649980163421e-13L,
    -3.982897776989487747865172909264620022997e-15L,
    6.923366618305929058068209540950658700107e-17L,
    -1.255272230449977275458465709126553674555e-18L,
    2.353754002768465230564411714140603787718e-20L,
    -4.536398903458687018447507089017008298634e-22L,
    8.94516967039264316712031170773304472046e-24L,
    -1.798284004695496271720202471410154260645e-25L,
    3.675499764793738444336047339126740989995e-27L,
    -7.620807971564795229539485009637654782326e-29L,
    1.600041964369485975173763922573256015938e-30L,
    -3.396761147560375587923120605208518524092e-32L,
    7.282272286757764695317256361444326644631e-34L,
    -1.575022647958003487184978939403782607194e-35L,
    3.433540092480589335887972120165270383376e-37L,
    -7.53884999808987000989116127657764248773e-39L,
    1.666068164765360410310510689355203042974e-40L,
    -3.703898902881387056958685332822841606828e-42L,
    8.279211796468274689853419455144944031424e-44L,
    -1.859914814630981113956561297352068541421e-45L,
    4.19762722532705994540447561866591994072e-47L,
   -9.514207698800453521831900594208537399763e-49L};

  logz = TVIL_CLOG(z);
  logzsquared = logz*logz;
  logztothek = logzsquared*logzsquared*logzsquared;

  first6terms = logztothek/86400.0L;
  first6terms += -logzsquared*logzsquared/288.0L;
  first6terms += -logzsquared*logz/12.0L;
  first6terms += (0.75L - 0.5L*TVIL_CLOG(-logz))*logzsquared;
  first6terms += cZeta3 + cZeta2*logz; 
  
  accuracygoal = TVIL_TOL* TVIL_CABS (first6terms);
  remainingterms = 0.0L;

  for (j=0; j< 25; j++)
    {
      logztothek = logztothek*logzsquared;
      term = CLZcoeffs_trilog[j]*logztothek;
      remainingterms += term;
      if (TVIL_CABS (term) < accuracygoal) 
	break;
      if (j == 24)
        TVIL_Warn("TVIL_TrilogCLZseries", "trilog CLZ series converging too slowly.");
    }

  result = remainingterms + first6terms;

  return result;
}

/* ************************************************************** */
/* Improved version thanks to Alexander Voigt, new in 3vil v2.01  */

TVIL_COMPLEX TVIL_Trilogseries (TVIL_COMPLEX z)
{
  TVIL_REAL absz = TVIL_CABS (z);
  TVIL_REAL logepsilon = TVIL_LOG (TVIL_TOL);
  TVIL_REAL mlogabsz;
  TVIL_COMPLEX sum = 0;
  TVIL_COMPLEX kcubed;
  int k, kmax;

  mlogabsz = -TVIL_CLOG (absz);

/*
  The following kmax is hopefully designed to give accuracy to within
  e^logepsilon, with some safety margin built in. Not completely
  tested, but it seems good enough for government work anyway.
*/

  kmax = 5 + (int) (( 6.0 -logepsilon -3.0 * log(-logepsilon)
                      + 3.0 * log (mlogabsz)) / mlogabsz);

  for (k = kmax; k >= 1; k--)
    {
      kcubed = k*k*k;
      sum = z*(sum + 1/kcubed);
    }

  return sum;
}

/* ************************************************************** */

TVIL_COMPLEX TVIL_TrilogregionA (TVIL_COMPLEX z)
{
  TVIL_COMPLEX result;
  TVIL_COMPLEX log1minusz = TVIL_CLOG (1.0L - z);
  TVIL_COMPLEX logminusz = TVIL_CLOG (-z);

  result = -TVIL_Trilogunitdisk(1.0L/(1.0L - z)) - TVIL_Trilogunitdisk (z/(z - 1.0L)) 
           + log1minusz*(log1minusz*log1minusz/3.0L -
	     0.5L*logminusz*log1minusz - cZeta2) + cZeta3;

  return result;
}

/* ************************************************************** */

TVIL_COMPLEX TVIL_TrilogregionB (TVIL_COMPLEX z)
{
  TVIL_COMPLEX result;

  result = 0.25L * TVIL_Trilogunitdisk (z * z) - TVIL_Trilogunitdisk (-z);

  return result;
}
