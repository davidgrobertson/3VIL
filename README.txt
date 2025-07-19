                     ********************************
		            Welcome to 3VIL
                     ********************************

Copyright (C) 2016 S.P. Martin and D.G. Robertson

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or (at
your option) any later version.  See the file LICENSE.txt for further
details.

Contents of this file:

I.    Overview
II.   Building 3VIL
III.  Using 3VIL
IV.   The 3VIL Application Programmer Interface
V.    Numerical Integration in 3VIL
VI.   Using 3VIL with C++
VII.  Using 3VIL with FORTRAN


************************************************************************
I. Overview
************************************************************************

3VIL (3-Loop Vacuum Integral Library) is a library of utilities for
the numerical calculation of dimensionally regularized three-loop
vacuum Feynman integrals.  A convenient basis for these functions can
be obtained by repeated application of integration by parts, with the
result that the general integral can be written in terms of 35 basis
functions, for arbitrary input masses.  When analytical expressions
are available, they are used; otherwise evaluation proceeds by
numerical integration of a set of coupled, first-order differential
equations for the basis integrals.  The code is written in C, and can
be linked from C/C++ or FORTRAN.

Authors:
S.P. Martin [spmartin AT niu.edu] 
Department of Physics
Northern Illinois University
DeKalb, IL 60115
USA

D.G. Robertson [drober23 AT nd.edu]
Department of Physics and Astronomy
University of Notre Dame
Notre Dame, IN 46556
USA

To cite this program, please reference the paper (referred to in this
document as [MR16]):

"Evaluation of the general 3-loop vacuum Feynman integral", by
S.P. Martin and D.G. Robertson
Phys. Rev. D95 (2017) no.1, 016008 [arXiv:1610.07720]

Some details of the numerical integration techniques used here are
given in

"TSIL: a program for the calculation of two-loop self-energy
integrals", by S.P. Martin and D.G. Robertson
Comput. Phys. Commun. 174 (2006) 133-151 [arXiv:hep-ph/0501132]

and referred to in this document as [MR05].

3VIL is available from:

    https://github.com/davidgrobertson/3VIL
    https://www.niu.edu/spmartin/3VIL

Version number: 2.02


************************************************************************
II. Building 3VIL
************************************************************************

3VIL can be compiled on any system that supports the GNU Compiler
Collection (gcc), the Intel C compiler (icc), or a similar C compiler
with support for complex mathematics. The compiler should also support
the C99 standard (or later).

To compile 3VIL, edit the Makefile and choose:

1. Compiler and optimization flags.

   Several sets are pre-defined in the Makefile; simply uncomment the
   appropriate one for your system, if present.  3VIL is currently
   known to compile with gcc (under Linux or Mac OS X) and icc.  Other
   C compilers should work provided that complex mathematics is
   supported, but in this case you will need to explicitly set the
   compiler name and optimization flags.

   If you succeed in building 3VIL on a new platform, the authors
   would be grateful to know it, and to learn of any special measures
   that were needed to compile it.

2. Install directories, if desired.

   You can set TVIL_LIBDIR and TVIL_INCDIR to point to directories
   where you would like the library and the 3VIL header file,
   respectively, to be placed after compilation. If TVIL_LIBDIR and
   TVIL_INCDIR are not set, then the library and the header file will
   be left after compilation in the directory where the sources
   reside, and they can be moved by hand to an appropriate
   place. Standard directories that are automatically searched by
   compilers and linkers typically include /usr/lib and /usr/include,
   but you will need root access to write to these directories.  If
   you specify other directories not on the standard search path, note
   that when compiling your own code it will be necessary to specify
   these directories using the options -I<dir> and -L<dir>.  See the
   compiler/linker man pages for complete details.

Once these choices have been made, simply type

   make

to build the library, along with the associated test and sample
programs.  After this command is complete, and after 3VIL has been
tested with satisfactory results (see below), you can optionally type

   make install

to install the library and header files in the specified locations.
Congratulations, 3VIL is ready for action!

The end product intended for the user consists of the files:

   lib3vil.a     The static 3VIL archive (will be placed in
                 TVIL_LIBDIR upon "make install")

   3vil.h        The 3VIL header file, must be included in any 
                 user code that uses 3VIL (will be placed in
                 TVIL_INCDIR upon "make install")

   3vil          Executable for basic computation (see below 
                 for details)

   3vil.tst      Test program (see below for details)

In addition, the files

   3vil_cpp.h
   3vil_fort.inc

may be useful if you are planning to call 3VIL from C++ or FORTRAN,
respectively.  See sections VI-VII of this document for additional
information on using 3VIL with these languages.

It is strongly recommended that you run the test program after
compiling 3VIL, to insure that correct results are being obtained.
The program

   3vil.tst

compares the output of TVIL_Evaluate to predefined results in 3220
data files, which are located in the directory TestData.  These data
files include cases representing all known analytic results as well as
cases requiring integration, including many that are challenging
numerically.

3vil.tst takes a list of filenames as command line arguments, and
outputs, for each test case (i.e., for each file) either PASS, OKAY,
WARN or FAIL.  If a WARN or FAIL results, the responsible functions
are printed, with both the expected and obtained values.  Assuming you
have just compiled 3VIL, the easiest way to run the entire suite of
tests is via

    make tests

which runs the commands

   ./3vil.tst TestData/generic/* > testout_generic.txt &
   ./3vil.tst TestData/StandardModel/* > testout_SM.txt &
   ./3vil.tst TestData/1scale/* > testout_1.txt &
   ./3vil.tst TestData/2scaleA/* > testout_2scaleA.txt &
   ./3vil.tst TestData/2scaleB/* > testout_2scaleB.txt &
   ./3vil.tst TestData/2scaleC/* > testout_2scaleC.txt &
   ./3vil.tst TestData/2scaleD/* > testout_2scaleD.txt &
   ./3vil.tst TestData/2scaleE/* > testout_2scaleE.txt &
   ./3vil.tst TestData/3scaleA/* > testout_3scaleA.txt &
   ./3vil.tst TestData/3scaleB/* > testout_3scaleB.txt &
   ./3vil.tst TestData/3scaleC/* > testout_3scaleC.txt &
   ./3vil.tst TestData/difficult/* > testout_difficult.txt &

with the output redirected to files *.txt for later perusal
recommended due to the large number of tests.  The end of each file
will contain a summary with the total number of PASS, OKAY, FAIL, and
WARN results for that subset of test cases. The total CPU time needed to run
the tests on modern hardware should be of order 1 minute.

The pass/fail/warn criteria are controlled by macros TVIL_PASS,
TVIL_OKAY, and TVIL_WARN, defined in 3vil_testparams.h.  The first
sets the maximum relative error allowed for the test to pass; the
second sets a lower error threshold below which the test is deemed to
be "okay".  The last sets a minimal threshold below which the test is
deemed to fail.

Default values are:

   TVIL_PASS = 1.e-8
   TVIL_OKAY = 1.e-5
   TVIL_WARN = 1.e-3

Generic cases should usually exceed these relative precisions with
ease; these pass/okay/warn/fail parameters are aimed to be "friendly"
to the more difficult cases. Even so, you may see some WARNs, and
possibly even FAILs, when running the test suite, depending on your
platform.

Users should not need to do this to insure correct functionality, but
the test program can be configured to evaluate subset cases (EFG or EF
functions) by uncommenting the appropriate flag in the Makefile. In
this case the test program evaluates the selected subset case for each
set of input parameters, comparing the results to values taken from
the full data files.

The make command also produces the executable

   3vil

which implements the most basic 3VIL calculation: it takes as
command-line arguments u, v, w, x, y, z, and Q^2, in that order, and
prints the values of all integral functions together with timing and
other information.  As an example,

   ./3vil 1 2 3 4 5 6 1

evaluates all functions for u=1.0, v=2.0, w=3.0, x=4.0, y=5.0, z=6.0,
and Q^2=1.0 and prints the results to stdout.


************************************************************************
III. Using 3VIL
************************************************************************

To use 3VIL functions in your code, you must:

1.  Include the header file 3vil.h in any source file that makes use
    of 3VIL data structures or functions, e.g. by adding the line

    #include "3vil.h"

    This is appropriate if the file 3vil.h is located in the directory
    where the code is being compiled; if it has been placed in a
    standard location such as /usr/include, then

    #include <3vil.h>

    would work.  If it is a nonstandard directory <inc_dir>, the
    compiler option

    -I<inc_dir>

    will generally be necessary.  See the compiler man pages on your
    system for further details.

    Some potentially useful constants are also defined in the file

    3vil_global.h 

    which may be included by users wishing to access them.

2.  Link to the library at the end of the compilation process.  This
    is accomplished via the (linker) flag

    -l3vil

    If lib3vil.a is not in a standard location (including the case
    where it is in the current directory), you will generally need to
    add the flag

    -L<lib_dir>

    where <lib_dir> is the directory in which lib3vil.a may be found.
    If this is the current directory, then

    -L.

    may be used.  Again, consult the compiler man pages for complete
    details on making user libraries available to the linker.

Complete details regarding the 3VIL functions are given in section IV
of this document.  In the rest of the section we will discuss some
general points and exhibit some simple examples.

3VIL Datatypes
--------------

3VIL uses long double/long double complex as its basic datatypes.
Defined types

    TVIL_REAL
    TVIL_COMPLEX

automatically correspond to these.  Note also that macros of the form

    TVIL_CLOG

will evaluate to the appropriate intrinsic function, in this case
clogl.  For a full list of intrinsics with this behavior, see the file
3vil.h.

The basic data object in 3VIL is a C struct with type name

    TVIL_RESULT

which contains the parameter values u, v, w, x, y, z and Q^2, as well
as values for the 35 basis functions of types I, FBAR, G, and H. The
functions E and F are also included, as well as the "bold" versions of
E, F, G, and H [MR16].  Detailed definitions of the struct and its
contents are contained in the header file 3vil.h.

For non-negative squared-mass arguments, all basis functions are real
in principle.  However, they are treated internally in 3VIL as type
TVIL_COMPLEX, to allow for complex intermediate values during
integration in the complex t-plane, or evaluation with negative
squared-mass arguments. (The smallness of the imaginary part can also
be used as a quick check of the numerical evaluation of the
functions.) For non-negative squared-mass arguments, the final (real)
values of the basis functions are equal to the real parts of the 3VIL
functions. The user is responsible for converting the TVIL_COMPLEX
results into real variables.

In any program that calls 3VIL functions for basis function
evaluation, at least one of these high-level data objects must be
declared, e.g.

    TVIL_RESULT result;

More than one such object, and arrays of such objects, are allowed.
Users can of course access the items in the struct directly, though it
is recommended that the provided user interface routines be used.
These allow one to extract values of individual functions, set the
values of the external parameters, and so on.  See section IV for
details of all functions in the user API.

In the simplest application of 3VIL, the parameters u, v, w, x, y, z,
and Q^2 will be set and the integrals evaluated by a single call to
TVIL_Evaluate, with the results either printed using TVIL_PrintData,
or extracted by the calling program with the command TVIL_GetFunction.  
Generic code for this would look like:

    TVIL_RESULT  result;
    TVIL_REAL    u, v, w, x, y, z, qq;
    TVIL_COMPLEX integral1, integral2;
    ...
    TVIL_Evaluate (u, v, w, x, y, z, qq, &result);
    ...
    integral1 = TVIL_GetFunction (&result, <string1>);
    integral2 = TVIL_GetFunction (&result, <string2>);
    ...

where the strings <string1>, <string2> can each be one of

    "H"

    "Gwuzvy", "Gxuvyz", "Guvxwz", "Gyvwxz", "Gvuxwy", "Gzuwxy"

    "Ewuxy", "Evwxz", "Euvyz"

    "FBARwuxy", "FBARwvxz", "FBARxuwy", "FBARxvwz", "FBARuvyz", "FBARuwxy",
    "FBARyuvz", "FBARyuwx", "FBARvuyz", "FBARvwxz", "FBARzuvy", "FBARzvwx"

    "Fwuxy", "Fwvxz", "Fxuwy", "Fxvwz", "Fuvyz", "Fuwxy",
    "Fyuvz", "Fyuwx", "Fvuyz", "Fvwxz", "Fzuvy", "Fzvwx"

    "Iuvx", "Ixyz", "Iuxy", "Ivxz", "Iuwz", "Ivwy", "Iuwy", "Ivwz",
    "Ivyz", "Iwxy", "Iuvz", "Iuwx", "Iuyz", "Iwxz", "Iuvy", "Ivwx"

according to which of the basis integrals is desired.  Note that
permutations of the arguments that match the symmetries of the basis
functions are also allowed; thus "Fwvzx" returns the same value as
does "Fwvxz", etc.

The "bold" variants of the I, E, F, G, and H functions defined in
[MR16] can be accessed in a similar way; e.g.

    integral3 = TVIL_GetBoldFunction (&result, <string3>, n);

would return the coefficient of 1/\epsilon^n in the bold-faced
function corresponding to an appropriate <string3> from the list
above.

TVIL_Evaluate first decides whether the case at hand is known
analytically; if so, the basis functions are computed directly. If
not, numerical integration is performed. TVIL_Evaluate returns 1
(TRUE) for successful execution or 0 (FALSE) for error execution. The
data object further contains a status parameter, accessible via the
function TVIL_GetStatus, which indicates how the master integral
evaluation was performed: either analytic, numerical integration along
real axis, or numerical integration along the displaced contour int he
complex plane.

All integrals that are analytically known in terms of polylogarithms
can also be evaluated directly, without using TVIL_Evaluate or
TVIL_GetFunction. For example,

    TVIL_Hanalytic (u, v, w, x, y, z, qq, &result);

will return the int value 1 and set the variable result equal to 
H(u, v, w, x, y, z, qq), if it is analytically available, and otherwise
will return 0. Here u, v, w, x, y, z, qq are of type TVIL_REAL, and
result is of type TVIL_COMPLEX.  The functions

    TVIL_FBARanalytic
    TVIL_Fanalytic
    TVIL_Ganalytic

have analogous behavior. For example,

    TVIL_Ganalytic (u, v, w, x, y, qq, &result);

will return the int value 1 and set the variable result equal to 
G(u, v, w, x, y, qq) if it is analytically available, and otherwise will
return 0 and leave result untouched.

The 1- and 2-loop vacuum functions A(x) and I(x, y, z) assign without
pointers, for example

    result = TVIL_I2 (x,y,z,qq);

will set result equal to I(x,y,z) computed analytically.  Full details
of these and other functions in the user API are given below.

The standard output function is TVIL_PrintData, which prints all
function values on stdout. Printing of bold functions can be toggled
on or off using the functions TVIL_SetPrintBold and
TVIL_UnsetPrintBold. An alternate format, designed so that captured
output can serve as valid input files for Mathematica, is obtained by
TVIL_SetPrintStyle(MATH).  Additional utilities allow the user to
extract individual basis functions. Note that warning and error
messages appear on stderr so that they may be redirected by the shell
and examined separately.

A complete example program that uses 3VIL is given in

    sample.c,

included with the distribution.  It computes all 3-loop vacuum basis
integrals with (u, v, w, x, y, z) = (t, t, b, h, W, W) at the
renormalization scale Q = 150 GeV, and prints the results to stdout.
(Here t is the top quark mass squared, b is the bottom quark, h the
Higgs boson, etc.)  Most of the basic functionality available in 3VIL
is exhibited in this program.

To compile this program using gcc, assuming 3vil.h and lib3vil.a are
present in the current directory, use e.g.

    gcc -o samp sample.c -L. -l3vil -lm

This command produces the executable samp, which can then be run as

    ./samp

Two related programs:

    sampleEFG.c
    sampleEF.c

illustrate the EFG and EF subset evaluation modes.

In addition, the program

    figureH.c

generates all data needed to reproduce Fig. 7.2 of the paper
[MR16]. Run time for this program will be around 7 minutes on modern
hardware.


************************************************************************
IV. The 3VIL Application Programmer Interface
************************************************************************

In this section we give the signatures of all functions in the 3VIL
API, and describe their operation.  All these functions are defined in
3vil.h.

(Although 3vil.h contains everything that should be needed for the
normal use of 3VIL, advanced users may wish to examine internal.h, the
header file used internally to 3VIL, to see signatures for all 3VIL
functions and other possibly useful constructs.)


Basic Evaluation and Extraction Functions
=========================================

1. int TVIL_Evaluate (TVIL_REAL u,
                      TVIL_REAL v,
                      TVIL_REAL w,
                      TVIL_REAL x,
		      TVIL_REAL y,
		      TVIL_REAL z,
                      TVIL_REAL qq,
		      TVIL_RESULT *result)
  
   Sets parameter values u, v, w, x, y, z, qq in the data object
   *result, and evaluates all functions including bold
   variants. Return value is 1 (TRUE) for successful execution, 0
   (FALSE) for error execution.

---------------------------------------------------------------------

2. int TVIL_EvaluateEFG (TVIL_REAL u,
                         TVIL_REAL v,
                         TVIL_REAL w,
                         TVIL_REAL x,
		         TVIL_REAL y,
                         TVIL_REAL qq,
		         TVIL_RESULT *result)
  
   Sets parameter values u, v, w, x, y, qq in the data object *result,
   and evaluates Gvuxwy, Ewuxy, and the subsidiary integrals neede to
   compute them, specifically FBARwuxy, FBARxuwy, FBARuwxy, FBARyuwx,
   and Iuvx, Iuxy, Ivwy, Iuwy, Iwxy, Iuwx.  (Note that these are all
   functions that do not involve the argument z.) Bold variants are
   included.  Return value is 1 (TRUE) for successful execution, 0
   (FALSE) for error execution.

---------------------------------------------------------------------

3. int TVIL_EvaluateEF (TVIL_REAL u,
                        TVIL_REAL w,
                        TVIL_REAL x,
		        TVIL_REAL y,
                        TVIL_REAL qq,
		        TVIL_RESULT *result)
  
   Sets parameter values u, w, x, y, qq in the data object *result,
   and evaluates Ewuxy, and the subsidiary integrals neede to compute
   it, specifically FBARwuxy, FBARxuwy, FBARuwxy, FBARyuwx, and Iuxy,
   Iuwy, Iwxy, Iuwx.  (Note that these are all functions that do not
   include the arguments z or v.)  Bold variants are included.  Return
   value is 1 (TRUE) for successful execution, 0 (FALSE) for error
   execution.

---------------------------------------------------------------------

4. int TVIL_GetStatus (TVIL_RESULT *result)

   Returns the evaluation status of *result; either

	   0  Unevaluated
	   1  Evaluated by analytical formula
	   2  Evaluated by numerical integration along real t-axis
	   3  Evaluated by numerical integration along displaced
	      contour

   Note that a set of enum'ed constants (UNEVALUATED, ANALYTIC,
   REAXIS, CONTOUR) representing these are available in 3vil_global.h.

---------------------------------------------------------------------

5. TVIL_COMPLEX TVIL_GetFunction (TVIL_RESULT *result, const char *str)

   Returns a single function from *result according to the string
   provided.  str may be any of

   "H"

   "Gwuzvy", "Gxuvyz", "Guvxwz", "Gyvwxz", "Gvuxwy", "Gzuwxy"

   "Ewuxy", "Evwxz", "Euvyz"

   "FBARwuxy", "FBARwvxz", "FBARxuwy", "FBARxvwz", "FBARuvyz", "FBARuwxy",
   "FBARyuvz", "FBARyuwx", "FBARvuyz", "FBARvwxz", "FBARzuvy", "FBARzvwx"

   "Fwuxy", "Fwvxz", "Fxuwy", "Fxvwz", "Fuvyz", "Fuwxy",
   "Fyuvz", "Fyuwx", "Fvuyz", "Fvwxz", "Fzuvy", "Fzvwx"

   "Iuvx", "Ixyz", "Iuxy", "Ivxz", "Iuwz", "Ivwy", "Iuwy", "Ivwz",
   "Ivyz", "Iwxy", "Iuvz", "Iuwx", "Iuyz", "Iwxz", "Iuvy", "Ivwx"

   or permutations allowed by the symmetries of the basis functions.
   For example, the F functions are symmetric under interchange of any
   of their last three arguments: F(u,v,y,z) = F(u,y,v,z), etc.  This
   function can be accessed using the identifier string "Fuyvz" in
   addition to "Fuvyz".  Likewise, any of the strings "Iuvx", "Ixuv",
   "Ivxu", "Ivux", "Ixvu", or "Iuxv", will return the function
   I(u,v,x) (symmetric under interchange of any of its arguments),
   etc.

   Example:
   ========
   TVIL_RESULT result;
   TVIL_COMPLEX fvuyz;
   ...
   fvuyz = TVIL_GetFunction (&result, "Fvuyz");

   A fatal error results if an invalid function identifier is
   specified, or if an attempt is made to extract a function from an
   unevaluated TVIL_RESULT struct.

---------------------------------------------------------------------

6. TVIL_COMPLEX TVIL_GetBoldFunction (TVIL_RESULT *result, 
                                      const char *str,
				      int n)			      

   Like TVIL_GetFunction but returns the coefficient of 1/epsilon^n in
   the "bold" variant function specified by the string str. The string
   str may be any of

   "H"

   "Gwuzvy", "Gxuvyz", "Guvxwz", "Gyvwxz", "Gvuxwy", "Gzuwxy"

   "Ewuxy", "Evwxz", "Euvyz"

   "Fwuxy", "Fwvxz", "Fxuwy", "Fxvwz", "Fuvyz", "Fuwxy",
   "Fyuvz", "Fyuwx", "Fvuyz", "Fvwxz", "Fzuvy", "Fzvwx"

   "Iuvx", "Ixyz", "Iuxy", "Ivxz", "Iuwz", "Ivwy", "Iuwy", "Ivwz",
   "Ivyz", "Iwxy", "Iuvz", "Iuwx", "Iuyz", "Iwxz", "Iuvy", "Ivwx"

   (or permutations matching the symmetries of the basis functions).

   Allowed values of n are:

   	   n = 0,1     for H
	   n = 0,1,2,3 for E, F and G
	   n = 0,1,2   for I

   Example:
   ========
   TVIL_RESULT result;
   TVIL_COMPLEX gzuwxy2;
   ...
   /* Returns power of 1/epsilon^2 in bold Gzuwxy: */
   gzuwxy2 = TVIL_GetBoldFunction (&result, "Gzuwxy", 2);


   A fatal error results if an invalid function identifier is
   specified, or if an attempt is made to extract a function from an
   unevaluated TVIL_RESULT struct, or if an invalid n is specified for
   any function type.

---------------------------------------------------------------------


I/O and Related Functions
=========================

1. void TVIL_PrintStatus (TVIL_RESULT *result)

   Prints to stdout the evaluation status of *result, whether
   unevaluated, evaluated by analytical formula, evaluated by
   numerical integration along real t-axis, or evaluated by numerical
   integration along the displaced contour.  If evaluation made use of
   one of the special 3-scale modes, that is also noted.

---------------------------------------------------------------------

2. void TVIL_PrintData (TVIL_RESULT *result)

   Prints to stdout the values of all integral functions associated
   with *result, including E, F, and "bold" variants (assuming printing
   of bold functions has been enabled; see TVIL_SetPrintBold below).

---------------------------------------------------------------------

3. void TVIL_WriteData (FILE *fp, TVIL_RESULT *result)

   Like TVIL_Prinresult, but writes to the file pointer fp rather than
   stdout. The user is responsible for properly initializing the file
   pointer.

---------------------------------------------------------------------

4. void TVIL_SetPrintStyle (int newStyle)

   Sets the print style to newStyle. Currently this can be STANDARD,
   BASIC, STD, GENERIC, or PLAIN (all equivalent to 0) for a basic
   "vanilla" style, or MATH (equivalent to 1) for Mathematica-
   compatible style.  The default is MATH.

---------------------------------------------------------------------

5. void TVIL_cprintf (TVIL_COMPLEX)

   Prints a complex value to stdout with a fixed number of significant
   figures (default 16). No newline is appended.

---------------------------------------------------------------------

6. void TVIL_cfprintf (FILE *fp, TVIL_COMPLEX)

   Prints a complex value to a file with a fixed number of significant
   figures (default 16). No newline is appended.

---------------------------------------------------------------------

7. void TVIL_Error (char *func, char *msg, int errcode)

   Prints an error message to stderr and exits with status errcode.
   The message indicates the function in which the error was generated
   (func) and an error-specific message (msg) of the user's
   choice. This function also results in a stack trace.

---------------------------------------------------------------------

8. void TVIL_Warn (char *func, char *msg)

   Prints a warning message to stderr; execution continues normally.
   The message contains the function in which the error was generated
   (func) and an error-specific message (msg) of the user's choice.

---------------------------------------------------------------------

9. void TVIL_SetPrintBold (void)

   Enables default printing of all bold function values when
   TVIL_Prinresult or TVIL_PrinresultM or TVIL_WriteData or
   TVIL_WriteDataM is called.  This is a global switch; it applies to
   all data structs that are instantiated.

---------------------------------------------------------------------

10. void TVIL_UnsetPrintBold (void)

   Turns off printing of all bold function values when TVIL_Prinresult
   or TVIL_PrinresultM or TVIL_WriteData or TVIL_WriteDataM is called.
   This is a global switch; it applies to all data structs that are
   instantiated.

---------------------------------------------------------------------

11. void TVIL_PrintVersion (void)

   Prints the current version of 3VIL to stdout.



Utilities
=========

1. void TVIL_ResetStepSizeParams (TVIL_RESULT *result,
                                  TVIL_REAL precisionGoal,
                                  int       nStepsStart,
                                  int       nStepsMaxCon,
                                  int       nStepsMaxVar,
                                  int       nStepsMin)

   Allows modification of integration parameters. In *result, sets
   precisionGoal, nStepsStart, nStepsMaxCon, nStepsMaxVar, nStepsMin
   to the specified values.

---------------------------------------------------------------------

2. void TVIL_ResetStepSizeParamDefaults (void)

   Resets integration parameters to the default values given in
   3vil_params.h.

---------------------------------------------------------------------

3. int TVIL_IsInfinite (TVIL_COMPLEX z)

   Returns 1 (TRUE) or 0 (FALSE) according to whether z is infinite.

---------------------------------------------------------------------

4. void TVIL_WarnsOff (void)

   Disables warning messages, for example when one tries to access an
   undefined function with TVIL_GetFunction or TVIL_GetBoldFunction.
   Error messages cannot be disabled.

---------------------------------------------------------------------

5. void TVIL_WarnsOn (void)

   Enables warning messages, for example when one tries to access an
   undefined function with TVIL_GetFunction, TVIL_GetBoldFunction.
   This is the default setting.

---------------------------------------------------------------------

6. void TVIL_Set_aParameter (TVIL_REAL newa)

   Sets a new value for the a parameter [MR16] in the data object
   result.  This overrides the value determined automatically by 3VIL.
   See technical notes below on how a is determined for a given set of
   input parameters.

---------------------------------------------------------------------

7. void TVIL_SetContourDisplacement (TVIL_REAL newdisplacement)

   Sets the displacement of the contour in the complex plane used for
   t-integration, when real-axis integration is unavailable.

   Default value is 0.8 (set in 3vil_params.h).

---------------------------------------------------------------------

8. void TVIL_Set_tInitial (TVIL_REAL tinitial)

   Sets starting displacement from t=0 for numerical integration. If
   integrating along real-t axis, then tinitial is the actual starting
   value.  If integrating along the displaced contour in the complex
   t-plane, the starting point is I*tinitial.

   Default value is 0.01 (set in 3vil_params.h).

---------------------------------------------------------------------

9. void TVIL_SetDoAnalytic (void)

   Enables automatic evaluation of any (or all) basis functions that
   are known analytically.  In cases where a subset of functions can
   be evaluated analytically, these are updated by their analytic
   values after numerical integration for the others is complete.

   This is the default behavior, and users are cautioned against
   changing this except for testing purposes, for example to compare
   the results of numerical integration against the analytic results.

---------------------------------------------------------------------

10. void TVIL_UnsetDoAnalytic (void)

   Disables automatic evaluation of analytically-known cases for
   functions in result. There is no good reason to do this, other than
   for testing purposes.

---------------------------------------------------------------------

11. void TVIL_SetForceContour (void)

   Toggle that forces evaluation to always proceed by integration
   along the displaced contour in the complex t-plane, even when
   integrations along the real t-axis would be permitted. This can be
   useful as a check on the numerical evaluation.

---------------------------------------------------------------------

12. void TVIL_UnsetForceContour (void)

   Disables forced integration along the displaced contour, i.e.,
   permits integration along the real t-axis when possible. This is
   the default setting.

---------------------------------------------------------------------

13. void TVIL_SetForceDefault (void)

   Forces default evaluation mode even for one of the special 3-scale
   cases. Useful mainly for testing.

---------------------------------------------------------------------

14. void TVIL_UnsetForceDefault (void)

   Disables forced default evaluation, i.e., allows 3-scale cases to
   be evaluated using the faster and more accurate techniques designed
   for them. This is the defaul tsetting.

---------------------------------------------------------------------

15. void TVIL_PermuteResult (TVIL_RESULT *in,
                             int          thePerm,
                             TVIL_RESULT *out)

   Performs permutation thePerm of the arguments and functions of *in,
   storing the results in *out. Integer thePerm can be one of

   P123456, P164352, P245163, P321546, P416235, P461532, P542613, P635124,
   P132654, P213465, P254361, P356241, P425136, P524316, P563412, P641523, 
   P146253, P231564, P312645, P365142, P452631, P536214, P614325, P653421

   in what is hopefully a self-evident notation (each represents a
   permutation of arguments 123456, so that, e.g., P123456 is the
   identity permutation). These constants are defined in 3vil_global.h.

---------------------------------------------------------------------

16. int TVIL_InversePerm (int thePerm)

   Returns the integer corresponding to the inverse of permutation
   thePerm.

---------------------------------------------------------------------


Analytic Cases
==============

1. TVIL_COMPLEX TVIL_Dilog (TVIL_COMPLEX z)

   Returns the dilogarithm of z.

---------------------------------------------------------------------

2. TVIL_COMPLEX TVIL_Trilog (TVIL_COMPLEX z)

   Returns the trilogarithm of z.

---------------------------------------------------------------------

3. TVIL_REAL TVIL_A (TVIL_REAL x, TVIL_REAL qq)

   Returns the one-loop vacuum function A(x) with renormalization
   scale squared equal to qq.

---------------------------------------------------------------------

4. TVIL_REAL TVIL_Ap (TVIL_REAL x, TVIL_REAL qq)

   Returns the derivative of the one-loop vacuum function A(x) with
   respect to x, with renormalization scale squared equal to qq.

---------------------------------------------------------------------

5. TVIL_COMPLEX TVIL_Aeps (TVIL_REAL x, TVIL_REAL qq)

   Returns A_\epsilon (x) with renormalization scale squared equal to
   qq.

---------------------------------------------------------------------

6. TVIL_COMPLEX TVIL_Aeps2 (TVIL_REAL x, TVIL_REAL qq)

   Returns A_epsilon^2 (x) with renormalization scale squared equal to
   qq.

---------------------------------------------------------------------

7. TVIL_COMPLEX TVIL_I2 (TVIL_REAL x,
                         TVIL_REAL y,
                         TVIL_REAL z,
                         TVIL_REAL qq)

   Returns the two-loop vacuum integral I(x,y,z), with renormalization
   scale squared equal to qq.

---------------------------------------------------------------------

8. TVIL_COMPLEX TVIL_II0 (TVIL_REAL x,
                          TVIL_REAL y,
                          TVIL_REAL z,
                          TVIL_REAL qq)

   Returns the term proportional to epsilon^0 in the epsilon expansion
   of the bold two-loop vacuum integral I(x,y,z), with renormalization
   scale squared equal to qq.

---------------------------------------------------------------------

9. TVIL_COMPLEX TVIL_II1 (TVIL_REAL x,
                          TVIL_REAL y,
                          TVIL_REAL z,
                          TVIL_REAL qq)

   Returns the term proportional to epsilon^(-1) in the epsilon
   expansion of the bold two-loop vacuum integral I(x,y,z), with
   renormalization scale squared equal to qq.

---------------------------------------------------------------------

10. TVIL_COMPLEX TVIL_II2 (TVIL_REAL x,
                           TVIL_REAL y,
                           TVIL_REAL z,
                           TVIL_REAL qq)

   Returns the term proportional to epsilon^(-2) in the epsilon
   expansion of the bold two-loop vacuum integral I(x,y,z), with
   renormalization scale squared equal to qq.

---------------------------------------------------------------------

11. TVIL_COMPLEX TVIL_Ieps (TVIL_REAL x,
                            TVIL_REAL y,
                            TVIL_REAL z,
                            TVIL_REAL qq)

   Returns the two-loop vacuum integral I_\eps (x,y,z), with
   renormalization scale squared equal to qq.

---------------------------------------------------------------------

12. int TVIL_FBARanalytic (TVIL_REAL a1,
                           TVIL_REAL a2,
                           TVIL_REAL a3,
                           TVIL_REAL a4,
                           TVIL_REAL qq,
                           TVIL_COMPLEX *result)

    If an analytic result for FBAR(a1, a2, a3, a4) is available,
    return 1 (TRUE) and evaluate it for renormalization scale squared
    qq.  The result is placed in *result.

    If no analytical result for FBAR is available, return 0 (FALSE).
    In this case *result is unchanged.

---------------------------------------------------------------------

13. int TVIL_Fanalytic (TVIL_REAL a1,
                        TVIL_REAL a2,
                        TVIL_REAL a3,
                        TVIL_REAL a4,
                        TVIL_REAL qq,
                        TVIL_COMPLEX *result)

    If an analytic result for F(a1, a2, a3, a4) is available, return 1
    (TRUE) and evaluate it for renormalization scale squared qq.  The
    result is placed in *result.

    If no analytical result for F is available, return 0 (FALSE).  In
    this case *result is unchanged.

---------------------------------------------------------------------

14. int TVIL_Ganalytic (TVIL_REAL a1,
                        TVIL_REAL a2,
                        TVIL_REAL a3,
                        TVIL_REAL a4,
                        TVIL_REAL a5,
                        TVIL_REAL qq,
                        TVIL_COMPLEX *result)

    If an analytic result for G(a1, a2, a3, a4, a5) is available,
    return 1 (TRUE) and evaluate it for renormalization scale squared
    qq.  The result is placed in *result.

    If no analytical result for G is available, return 0 (FALSE).  In
    this case *result is unchanged.

---------------------------------------------------------------------

15. int TVIL_Hanalytic (TVIL_REAL a1,
                        TVIL_REAL a2,
                        TVIL_REAL a3,
                        TVIL_REAL a4,
                        TVIL_REAL a5,
                        TVIL_REAL a6,
                        TVIL_REAL qq,
                        TVIL_COMPLEX *result)

    If an analytic result for H(a1, a2, a3, a4, a5, a6) is available,
    return 1 (TRUE) and evaluate it for renormalization scale squared
    qq. The result is placed in *result.

    If no analytical result for H is available, return 0 (FALSE).  In
    this case *result is unchanged.

---------------------------------------------------------------------


FORTRAN Interface
=================

subroutine tvilfevaluate (REAL u,
			  REAL v,
			  REAL w,
			  REAL x,
			  REAL y,
			  REAL z,
			  REAL qq)

Wrapper for TVIL_Evaluate, to be called from FORTRAN. See "Using 3VIL
with FORTRAN" below for complete details.

---------------------------------------------------------------------


************************************************************************
V. Numerical Integration in 3VIL
************************************************************************

As discussed in [MR16], we generically use a 6-stage, 5th-order
embedded Runge-Kutta scheme with coefficients given by Cash and Karp.
This gives an error estimate for each dependent variable at each step
and thus allows estimation of the step size necessary to achieve a
given precision.

In addition, whenever the endpoint t=1 is (or is near) a pole in the
evolution coefficients, we switch for the final leg of the numerical
integration to a 5-stage, 4th-order scheme. (This occurs for example
if any of u,v,w,x,y,z vanishes.) This is slower and does not provide
an error estimate, but it avoids evaluation of basis function
derivatives at the endpoint, where they may be singular.

For especially problematic cases, e.g., when several of the evolution
coefficients have poles at or near t=1, we employ the following
procedure.  As the RK evaluation approaches t=1, the RK error estimate
for H and the largest error estimate for all other functions are
examined.  If the error in H exceeds a specified threshold, then the
evaluation point is saved (i.e., all basis function values and the
value of t).  The integration proceeds and the threshold for H error
is increased by a multiplicative factor e^(1/3).  Then if the H error
ever exceeds this new threshold, the function values are again saved.
In this way, a collection of trial points is generated.

Finally, each of the trial points is restored and a final RK step is
taken to the endpoint, using the 5-stage, 4th-order stepper. The best
final result is then chosen, based primarily on the magnitude of the
imaginary part of H.

The basic idea of this approach is that once the error in H gets
sufficiently large, it is better to just take a single step and finish
out the integration.  However, empirically the best final result can
be obtained by taking the final step from points with a range of H
errors; it is not always the smallest error in H that is best at this
point.

For the 3-scale special cases with arguments 
case A: (u,v,w,x,y,z) = (0,0,Y,Z,X,X), 
case B: (u,v,w,x,y,z) = (0,X,X,Y,Z,Y),
case C: (u,v,w,x,y,z) = (0,X,Y,X,Z,Y),
and cases related to these by permutation, a special evaluation mode
is used; this is new in v2.0. In each of these cases, the Runge-Kutta
running in in terms of Z, with X and Y held fixed. The running starts
from the known values at Z=0, and proceeds either along the real Z
axis or in the complex Z plane, depending on the singularity structure
of the integrand coefficients. This approach is significantly faster
and more accurate for these special cases, which often arise in
practice, including in the evaluation of the Standard Model effective
potential.  Most of the remarks above (and below) on numerical
integration still apply; only the form of the differential equations
is different.

Selection of the a Parameter
============================
It is important that the a parameter be set carefully.  In general, a
should be taken to be 2.0 times the largest argument of H, to avoid
singular points.  But in addition, a must be set so that if Phi = 0
(eq. (6.14) of [MR16]) for any distinct set of arguments, then the
corresponding Delta function (eq. (6.13) of [MR16]) is also zero.  In
3VIL this is implemented by specifying a list of four possible values
for a/Max(u,v,w,x,y,z), then testing to see if any is problematic.
The first one that is not problematic is taken (2.0 by default).
Since there are at most three problematic values of a, a good value
will always be found.

Users wishing to adjust the value of a should be aware of this issue
and proceed with caution.

Integration Contour
===================
For the generic rectangular integration contour described in [MR16],
the displacement along the imaginary axis of the complex t-plane is
set by IM_DISPL, also defined in 3vil_params.h.  Its default value is
0.8.  Of course all results should be independent of this value, so
users can change this as a probe of numerical stability if unusual
results are observed.

Parameters for Numerical Integration
====================================
Finally let us describe the parameters associated with adaptive
stepsize control.  These are also all defined in 3vil_params.h, and
can have a significant effect on execution speed and accuracy.

These are realized as members of the TVIL_RESULT struct, with names:

* precisionGoal: This is \delta_P in eq. (3.14) of [MR05].  (We use a
                 safety factor S=0.9.)  If the maximum estimated error
                 for any dependent variable exceeds \delta_P
                 multiplied by the increment of that variable for that
                 step, and also exceeds the relative precision of the
                 computer arithmetic times the absolute value of that
                 variable, then the step is retried with a smaller
                 step size, unless the step size would become smaller
                 than specified below. Also, after a successful step,
                 the size for the next step is chosen according to
                 eq. (3.14) of [MR05], unless it would exceed the
                 amount specified below.  (Default: 10^{-12})

* nStepsStart:   For each leg of the contour, the initial step size is
                 chosen so that there would be this many steps if the
                 step size did not change. (Default: 500)

* nStepsMin:     The maximum allowed step size on a leg of the contour
                 with dimensionless (rescaled) independent variable 
		 length L is given by L/nStepsMin. (Default: 100)

* nStepsMaxCon,
  nStepsMaxVar:  The minimum allowed step size on a leg of the contour
		 with dimensionless independent variable length L is 
		 given by L/(nStepsMaxCon + L*nStepsMaxVar).
		 (Defaults: 10000, 10000)

The step size is not allowed to increase by more than a factor of 1.5
or decrease by more than a factor of 2 after each step or attempted
step.  Note that by setting precisionGoal to 0, one can arrange that
the total number of steps on each leg tends to

    nStepsMaxCon + L*nStepsMaxVar

If instead one sets precisionGoal to a very large number, the number
of steps will tend to nStepsMin.

The default values have been found to give good results for a wide
variety of different choices of input parameters, for the integration
variables used in the program.  However, to deal with exceptional
situations, they can be reset at run time with the function
TVIL_ResetStepSizeParams, after calling TVIL_SetParameters and before
calling TVIL_Evaluate.

Note that in general, long double data (typically with 63 or more bits
of relative precision) gives results with relative accuracies better
than 10^{-10} for generic cases, but sometimes somewhat worse in cases
with large mass hierarchies, and in some particularly difficult cases
significantly worse.  The user should consider modifying the default
parameters of the program if significant sensitivity to parameters is
expected (or observed), or if speed is an overriding concern.


************************************************************************
VI. Using 3VIL with C++
************************************************************************

It is possible to call 3VIL functions from C++ code.  The header file

   3vil_cpp.h

should be included in any C++ source files that make use of 3VIL
functions.  This file is equivalent to the usual 3vil.h, but with
additional definitions to streamline inter-operation with C++.

Care should be taken that C++ type sizes match those used in 3VIL.
Thus

   std::complex<long double>

should be used for the corresponding C++ variables. The
macros

   TVIL_REAL
   TVIL_COMPLEXCPP

default to the appropriate types.  Note that macro TVIL_COMPLEX
retains its definition as the appropriate C complex type, i.e., 

   long double _Complex.

The one real subtlety has to do with compatibility of the C complex
type and C++ std::complex<>, for example when a 3VIL function returns
a TVIL_COMPLEX and the result is to be stored in a std::complex<long
double>, or when a 3VIL function takes a complex value as an argument.
Despite that the two complex types are supposed to be byte equivalent,
a straight assignment of this type does not work as expected for all
compilers.

However, the relevant standards guarantee that *pointers* to either
type will be correctly interpreted in any context.  Hence it is
necessary to add "wrapper" code around such 3VIL function calls, so
that complex values (either return values or arguments) are referred
to via pointers.

What this means for the user is that the 3VIL functions all have
C++-specific versions that can be called with C++ types as arguments
and will return C++ types.  The names of these are the same as the
corresponding 3VIL functions, with a trailing underscore.  Thus the C
function

   TVIL_GetFunction (...)

becomes

   TVIL_GetFunction_ (...) 

when called from C++, etc.  *All* functions in the user API have been
supplied with such wrappers, even though not all functions really need
them; this is so that users need not remember which functions have
special names.

All these definitions appear at the end of 3vil_cpp.h, should you wish
to examine them.

The sample code

   sample.cpp

shows all this in action.  After building 3VIL, it can be compiled as,
e.g.,

   g++ -o samp sample.cpp -L<dir> -l3vil

where <dir> is the directory containing lib3vil.a.

In this C++ source code, note the
* inclusion of 3vil_cpp.h;
* use of the C++-specific calls to TVIL_A_, TVIL_B_,
  TVIL_GetFunction_, etc.

Please alert the authors if you encounter any issues using 3VIL with
C++ code!


************************************************************************
VII. Using 3VIL with FORTRAN
************************************************************************

It is possible to use 3VIL with FORTRAN, and some basic utilities for
this are included with the package. Essential functionality is
provided by a wrapper function tvilfevaluate (defined in the file
fevaluate.c), which is called as a subroutine from a FORTRAN program.
This subroutine implements the most general 3VIL calculation: it takes
as arguments u, v, w, x, y, z, and Q^2, and returns the values of all
basis functions, including "bold" functions.

These results are returned to the calling program in a COMMON block,
which corresponds to a special C struct used by tvilfevaluate.  This
COMMON block contains a number of pre-defined arrays that hold the
various function values. Definitions of the COMMON block and
subsidiary arrays are given in the header file

   3vil_fort.inc

which users should INCLUDE in their FORTRAN program.

IMPORTANT NOTE: It is crucial that the type sizes match between the
calling FORTRAN program and the 3VIL interface, because the COMMON
block must have the same memory "footprint" as the C struct defined in
the wrapper code.  In addition, the arguments to tvilfevaluate must be
consistently defined in both fevaluate.c and the calling FORTRAN
program.  Type size mismatches may result in non-fatal errors that are
difficult to diagnose.  Users should be aware that corresponding types
may not actually exist, depending on platform and compiler.  It is
strongly recommended that exact type sizes for your system be
determined before using 3VIL with FORTRAN.

The FORTRAN header file

   3vil_fort.inc

assumes that the basic floating-point type in the FORTRAN program is
REAL*8, assumed to be equal in size to the C type double.  (This is
true on all systems of which the authors are aware, but anomalies may
exist.)  The associated complex type is of course COMPLEX*16.  These
types must match those defined in the file

   3vil_fortran.h

which contains definitions for the C wrapper program (fevaluate.c).
Specifically, the macro

   TVIL_REAL_F

should be set to the C type corresponding to the FORTRAN floating-
point type used (in this case, double). Furthermore,

   TVIL_COMPLEX_F

should be set to the C type corresponding to the FORTRAN complex type
(in this case, double complex). Finally,

   TVIL_REAL_SIZE_F

should be set to the number of bytes in the basic floating-point type
used in the FORTRAN code (in this case, 8 for REAL*8).  This value is
used when tvilfevaluate is called to test whether there may be a type
mismatch.  (If a possible mismatch is detected, a warning message is
printed but execution continues.)  However, this test is rather simple
and should not be relied upon to detect all possible errors.

Note that these types do *not* have to match the basic types used in
the main 3VIL routines (namely long double/long double complex).  When
the wrapper calls TVIL_Evaluate, the arguments are cast to the
appropriate type used in the main 3VIL library (i.e., to TVIL_REAL),
and upon return the results are cast back to the type TVIL_COMPLEX_F,
appropriate for return to the calling FORTRAN program.  Thus it can be
that the FORTRAN program uses a "smaller" type, which is cast by the
wrapper to a more precise type for 3VIL evaluation, and then cast back
to the earlier type upon return.

Sample Code
===========

A FORTRAN program fragment that uses these utilities is shown below:

       PROGRAM ftest
c      Includes array and COMMON definitions:
       INCLUDE '3vil_fort.inc'

c      (Code setting values of u,v,w,x,y,z,qq not shown)
       ...
c      Evaluate basis integrals:
       CALL tvilfevaluate(u,v,w,x,y,z,qq)

c      Print a representative value:
       PRINT *, F(wuxy)
       ...

Note in the last line the use of the INTEGER wuxy.  This is one of a
set of integer variables, also defined in 3vil_fort.inc, that allow
items in the COMMON block arrays to be referred to by name.

A complete functional sample fortran program is available in ftest.f. It 
can be compiled by

   gfortran ftest.f -L. -l3vil

Running ./a.out then prints out the values of the integral functions
for the case u, v, w, x, y, z, qq = 1, 2, 3, 4, 5, 6, 1.

Other General FORTRAN Issues
============================

The provided wrapper code can serve as a model for users wishing to
write their own interface routines with additional functionality.  In
addition to the type size issue discussed above, the following general
points should be noted:

* In FORTRAN arguments are passed by reference, i.e. as pointers in C.
  Thus any C function that is called from FORTRAN should have pointer
  arguments.

* FORTRAN compilers typically append an underscore to all external
  names, to identify them as FORTRAN constructs.  (This is important
  because of the call-by-reference convention.)  Thus the FORTRAN
  subroutine tvilfevaluate is known as tvilfevaluate_ in C, and the
  COMMON block results corresponds to the struct results_ in C.
  FORTRAN names that already contain an underscore typically have two
  underscores appended.  Unfortunately, these conventions are not
  uniform among FORTRAN compilers, so testing is required in any
  particular case.  The utilities provided with 3VIL have been tested
  with the GNU compilers gcc/gfortran.

* FORTRAN and C store the elements of multi-dimensional arrays in a
  different order (column-major and row-major ordering, respectively).
  Thus a two-dimensional array generated in C must be reorganized for
  proper indexing in FORTRAN.  This reorganization amounts to
  "transposing" the arrays, interpreted as matrices.  Note also that
  indexing conventions differ: FORTRAN array indices start at 1 while
  C indices start at 0.

************************************************************************
End of README.txt
************************************************************************
