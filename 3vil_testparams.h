/* Parameters used in test program: */

#ifndef TVIL_TESTPARAMS_H
#define TVIL_TESTPARAMS_H

/* NOTE: Generic cases should usually exceed these relative precisions
   with ease; these pass/warn/fail parameters are aimed to be
   "friendly" to the more difficult cases. Even so, you should expect
   to see some WARNs, and possibly FAILs, when running the test suite,
   depending on your platform. */

#define TVIL_PASS    1.e-8
#define TVIL_OKAY    1.e-5
#define TVIL_WARN    1.e-3

#endif /* 3vil_testparams.h */
