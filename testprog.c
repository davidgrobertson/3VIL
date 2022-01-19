/* Test Suite Driver Program */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "internal.h"
#include "3vil_testparams.h"

FILE *fp;

enum { FAIL, OKAY, WARN, PASS };

/* **************************************************************** */

void TVIL_SkipLine (FILE * foo)
{
  int s;

  while ((s = getc (foo)) != '\n')
    ;

  return;
}

/* **************************************************************** */

void TVIL_Test (const char   *name,
		TVIL_COMPLEX  actual,
		TVIL_COMPLEX  computed,
		int          *result)
{
  TVIL_REAL err;

  if (TVIL_IsInfinite (actual)) {
      if (TVIL_IsInfinite (computed))
	*result = PASS;
      else
	*result = FAIL;
  } else {
    err = TVIL_CABS (actual - computed) / (TVIL_CABS(actual) + TVIL_EPSILON);
    if (err < TVIL_PASS)
      *result = PASS;
    else if (err < TVIL_OKAY)
      *result = OKAY;
    else if (err < TVIL_WARN)
      *result = WARN;
    else
      *result = FAIL;
  }

  if ((*result == PASS) || (*result == OKAY))
    ;
  else {
    if (*result == WARN) printf ("\nWARN\n");
    if (*result == FAIL) printf ("\nFAIL\n");
    printf ("Expected for %s: ", name); TVIL_cprintf(actual); printf("\n");
    printf ("Obtained for %s: ", name); TVIL_cprintf(computed); printf("\n");
  }

  return;
}

/* **************************************************************** */

TVIL_REAL TVIL_GetReal ()
{
  TVIL_REAL val;
  char       s[50];
  const char inf[] = "ComplexInfinity;";
  char * p = s;

  while (fgetc (fp) != '=')
    ;

  /* This automatically skips leading white space: */
  fscanf (fp, "%s", s);

  /* Strip trailing semicolon: */
  p[strlen(p) - 1] = 0;

  /* printf("Read in string: %s\n", s); */

  if (strcmp (s, inf) == 0)
    val = TVIL_Infinity;
  else
    val = strtold (s, (char **) NULL);

  /* Trim final newline */
  fgetc (fp);

  return val;
}

/* **************************************************************** */

TVIL_COMPLEX TVIL_GetComplex ()
{
  TVIL_COMPLEX val;
  TVIL_REAL    im;
  char         s[100];
  const char   inf[] = "ComplexInfinity;";

  while (fgetc (fp) != '=')
    ;

  /* This automatically skips leading white space: */
  fscanf (fp, "%s", s);

  if (strcmp (s, inf) == 0)
    val = TVIL_Infinity;
  else
    {
      val = (TVIL_COMPLEX) strtold (s, (char **) NULL);
      fscanf (fp, " + %Lf I;", &im);
      val += I * im;
    }
  return val;
}

/* ******************************************************************* */

int main (int argc, char *argv[])
{
#include "3vil_names.h"

  TVIL_REAL u, v, w, x, y, z, qq;
  TVIL_COMPLEX val;
  TVIL_RESULT result;
  clock_t t0, t1;
  int i, j, foo, tally[4], nokay, nwarn, nfail, npass;
  char c;
  TVIL_COMPLEX Hvalue, Gvalue[NUM_G_FUNCS], FBARvalue[NUM_F_FUNCS];

  if (argc == 1)
    TVIL_Error ("main", "Must supply test data filename(s)...", 2);

  nokay = nwarn = nfail = npass = 0;
  
  printf("===== 3VIL TEST SUITE =====\n");
#if defined (TVIL_TEST_EFG)
  printf("(Testing EFG subset evaluation.)\n");
#elif defined (TVIL_TEST_EF)
  printf("(Testing EF subset evaluation.)\n");
#endif

  t0 = clock ();

  /* We don't need no stinkin' TVIL_Warnings here. */
  fclose (stderr);

  /* Loop over input files */
  for (i = 1; i < argc; i++)
    {
      if ((fp = fopen(argv[i], "r")) == NULL) {
	TVIL_Warn ("Test program", "Invalid file name");
	continue;
      }

      printf ("\nTest %d: ", i);
      printf ("%s\n", argv[i]);
      fflush (stdout);

      /* Skip any lines starting with '(' (comments): */
      while ((c = fgetc (fp)) == '(')
	TVIL_SkipLine (fp);

      /* Put back the last character after we find a non-comment line */
      ungetc ((int) c, fp);

      /* Read in parameters */
      u  = TVIL_GetReal ();
      v  = TVIL_GetReal ();
      w  = TVIL_GetReal ();
      x  = TVIL_GetReal ();
      y  = TVIL_GetReal ();
      z  = TVIL_GetReal ();
      qq = TVIL_GetReal ();

      /* Calculate everything... */
#if defined(TVIL_TEST_EFG)
      TVIL_EvaluateEFG (u, v, w, x, y, qq, &result);
#elif defined (TVIL_TEST_EF)
      TVIL_EvaluateEF (u, w, x, y, qq, &result);
#else
      TVIL_Evaluate (u, v, w, x, y, z, qq, &result);
#endif

      for (j = 0; j < 3; j++)
	tally[j] = 0;

      /* ...and test results: */

      TVIL_SkipLine (fp);

      /* Skip I functions, at least for now */
      for (j=0; j<NUM_I_FUNCS; j++) 
        val = TVIL_GetComplex ();

      TVIL_SkipLine (fp);

      /* Skip E functions, at least for now */
      for (j=0; j<NUM_E_FUNCS; j++) 
        val = TVIL_GetComplex ();

      TVIL_SkipLine (fp);

      /* Skip F functions, at least for now */
      for (j=0; j<NUM_F_FUNCS; j++) 
        val = TVIL_GetComplex ();

      TVIL_SkipLine (fp);

      /* FBAR */
      for (j=0; j<NUM_F_FUNCS; j++)
	{
	  val = TVIL_GetComplex ();
#if defined(TVIL_TEST_EFG) || defined(TVIL_TEST_EF)
	  if (j == wuxy || j == xuwy || j == uwxy || j == yuwx) {
#endif
	  FBARvalue[j] = result.FBAR[j];
	  TVIL_Test (fbarname[j][0], val, FBARvalue[j], &foo);
	  tally[foo]++;
#if defined(TVIL_TEST_EFG) || defined(TVIL_TEST_EF)
	  }
#endif
	}

#if defined(TVIL_TEST_EF)
      ;
#elif defined (TVIL_TEST_EFG)
      TVIL_SkipLine (fp);

      /* G */
      for (j=0; j<NUM_G_FUNCS; j++)
	{
	  val = TVIL_GetComplex ();
	  if (j == vuxwy) {
	    Gvalue[j] = result.G[j];
	    TVIL_Test (gname[j][0], val, Gvalue[j], &foo);
	    tally[foo]++;
	  }
	}
#else
      TVIL_SkipLine (fp);

      /* G */
      for (j=0; j<NUM_G_FUNCS; j++)
	{
	  val = TVIL_GetComplex ();
	  Gvalue[j] = result.G[j];
	  TVIL_Test (gname[j][0], val, Gvalue[j], &foo);
	  tally[foo]++;
	}
#endif

#if defined(TVIL_TEST_EFG) || defined(TVIL_TEST_EF)
        ;
#else
      TVIL_SkipLine (fp);

      /* H */
      val = TVIL_GetComplex ();
      Hvalue = result.H;
      TVIL_Test ("H", val, Hvalue, &foo);
      tally[foo]++;
#endif

      if (tally[FAIL] > 0)
	{
	  nfail++;
	  printf ("\nFAILED FOR INPUT PARAMETERS:\n");
	  printf ("u  = %.6lf;\n", (double) u);
	  printf ("v  = %.6lf;\n", (double) v);
	  printf ("w  = %.6lf;\n", (double) w);
	  printf ("x  = %.6lf;\n", (double) x);
	  printf ("y  = %.6lf;\n", (double) y);
	  printf ("z  = %.6lf;\n", (double) z);
	  printf ("qq = %.6lf;\n", (double) qq);
	  printf ("a  = %.6lf;\n", (double) _a);
	}
      else if (tally[WARN] > 0)
        {
	  printf ("\nWARNING FOR INPUT PARAMETERS:\n");
	  printf ("u  = %.6lf;\n", (double) u);
	  printf ("v  = %.6lf;\n", (double) v);
	  printf ("w  = %.6lf;\n", (double) w);
	  printf ("x  = %.6lf;\n", (double) x);
	  printf ("y  = %.6lf;\n", (double) y);
	  printf ("z  = %.6lf;\n", (double) z);
	  printf ("qq = %.6lf;\n", (double) qq);
	  printf ("a  = %.6lf;\n", (double) _a);
	  nwarn++;
        }
      else if (tally[OKAY] > 0)
        {
	  printf ("OKAY\n");
	  nokay++;
        }
      else
	{
	  printf ("PASS\n");
	  npass++;
	}

      fclose (fp);

      printf ("\n===== Done with input file ");
      printf ("%s", argv[i]);
      printf (" =====\n");
    }
  
  t1 = clock ();
  printf ("\n== FINAL RESULTS ==\n");
  printf ("Total input files: %d\n", (argc - 1));
  printf ("Total tests performed: %d\n", (argc - 1));
  printf ("Pass: %d\n", npass);
  printf ("Okay: %d\n", nokay);
  printf ("Warn: %d\n", nwarn);
  printf ("Fail: %d\n", nfail);
  printf("\nTotal calculation time (s): %lf\n",
         difftime(t1, t0)/CLOCKS_PER_SEC);

  return 0;
}
