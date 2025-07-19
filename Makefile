####################################################################
# 
#    Makefile for 3VIL (3-loop Vacuum Integral Library)
#
########################## COMPILER ################################
# Uncomment the choices appropriate for your computing environment.
# (Not guaranteed to be complete. Please send info to the authors if
# you succeed in making things work on a system requiring different
# flags.)
#
# GNU C Compiler:
# ===============
 CC		= gcc
 TVIL_OPT	= -O3 # -funroll-loops 
#
# Intel C compiler:
# =================
# CC	 	= icc
# TVIL_OPT 	= -O3 -unroll -w
#
# General C compiler:
# ===================
# CC	 	= cc
# TVIL_OPT 	= -O3
#
################### INSTALLATION DIRECTORIES #######################
#
# TVIL_LIBDIR	= /usr/lib
# TVIL_INCDIR	= /usr/include
#
################### TEST SUITE MODE ################################
#
# TVIL_TESTOPT  = -DTVIL_TEST_EFG
# TVIL_TESTOPT  = -DTVIL_TEST_EF
#
####################################################################
#
#  Users should not need to modify anything below this point!!!
#
####################################################################
####################################################################

# -fcommon added after gcc 10:
CFLAGS	= $(TVIL_RESCALE) $(TVIL_SIZE) $(TVIL_OPT) -fcommon
LDFLAGS	= 
LIBS	= -L. -l3vil -lm
ARFLAGS = -rus

TVIL_SRCS = initialize.c \
	    functions.c \
	    analyticA.c \
	    analyticE.c \
	    analyticF.c \
	    analyticG.c \
	    analyticH.c \
	    analyticI.c \
	    initE.c \
	    initFBAR.c \
	    initG.c \
	    initH.c \
	    initI.c \
	    io.c \
            dFBARdt.c \
	    dGdt.c \
	    dHdt.c \
	    dIdt.c \
	    evaluate.c \
	    evaluate_subsets.c \
	    generic.c \
            perms.c \
	    special.c \
	    setbold.c \
	    rk6.c \
	    rk5.c \
	    dilog.c \
	    trilog.c \
	    3scale.c \
	    3scaleA.c \
	    3scaleB.c \
	    3scaleC.c \
	    fevaluate.c


TVIL_OBJS = $(TVIL_SRCS:.c=.o)

MAIN_OBJ = basecalc.o

TEST_SRC = testprog.c

TEST_OBJ = $(TEST_SRC:.c=.o)

all:	lib3vil.a 3vil 3vil.tst

lib3vil.a: $(TVIL_OBJS)
	$(AR) $(ARFLAGS) $@ $?

3vil:	$(MAIN_OBJ) lib3vil.a
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(MAIN_OBJ) $(LIBS)

$(TEST_OBJ):	$(TEST_SRC)
	$(CC) -c $(CFLAGS) $(TVIL_TESTOPT) $(TEST_SRC)

3vil.tst:	$(TEST_OBJ) lib3vil.a
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(TEST_OBJ) $(LIBS)

install: lib3vil.a
	cp lib3vil.a $(TVIL_LIBDIR)
	cp 3vil.h $(TVIL_INCDIR)

tests:	3vil.tst
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

tidy:
	rm -rf core* a.out *~ testout*

clean:
	rm -rf core* a.out 3vil 3vil.tst *~ *.o *.T lib3vil.a testout*

current:
	cp -p $(TVIL_SRCS) $(TEST_SRC) *.h *.inc basecalc.c* sample.c* figureH.c ftest.f Makefile README.txt LICENSE.txt CHANGELOG.txt $(CURRENT)
	cp -R TestData $(CURRENT)
	tar cvf $(CURRENT).tar $(CURRENT)
	gzip $(CURRENT).tar

# ===== Header dependencies: =====

3scaleA.o 3scaleB.o 3scaleC.o generic.o initialize.o: 3vil_params.h

$(TVIL_OBJS):	internal.h 3vil.h 3vil_funcs.h 3vil_global.h

$(MAIN_OBJ):	3vil.h

$(TEST_OBJ):	3vil_testparams.h internal.h 3vil.h

functions.o:	3vil_names.h
