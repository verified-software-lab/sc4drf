This is the Artifact for the CAV 2023 paper:

  Model Checking Race-Freedom when "Sequential Consistency for
  Data-race-free Programs" is Guaranteed


Structure of this Artifact
==========================

The artifact material is contained in the directory
/home/vboxuser/artifact.

Contents:
  README (this file)
  CIVL (source, documentation, executable, examples)
  LLOV (the static analysis tool)
  sc4drf
    experiments
      civl
        Makefile
        <all source files used in CIVL experiments>
        out (results of running experiments)
      llov
        Makefile
        <all source files used in LLOV experiments>
        out (results of running experiments)


Setting up this Artifact
========================

  Start VirtualBox
  Click "Add"
  Select the sc4drf.vbox file
  Follow the prompts to finish adding the virtual machine
  Select the machine and click "Start"
  When the login prompt appears, select user vboxuser
  Double-click the artifact shortcut on the Desktop
  In the folder that appears, right-click and select "Open in Terminal"
  Type make and hit enter.


Replication of Experiments Reported in Paper
============================================

Section 3.4 "Evaluation" describes the experiments.  Two tools were
used: CIVL and LLOV.  The artifacts for CIVL are in the civl
directory, and those for LLOV are in llov.

civl: there are 88 programs from the DataRaceBench suite.  All have
filenames beginning with "DRB".  As described in the paper, 68 of
these 88 have been manually edited by us.  (The original unedited
versions can be found in the llov directory.)  There are in addition
20 programs which we wrote ourselves.  All 108 experiments should run
by simply typing "make".  The DRB files with "yes" in the filename
have a datarace; those with "no" in the filename do not have a
datarace.  For the 20 additional files, "norace" in the filename
indicates there is no race, and "race" indicates there is a race.
The paper reports that CIVL gets the correct result (race or no race)
on all tests except DRB139, DRB014, and DRB015.  The output from our
own run can be found in subdirectory "out".

llov: there are 88 programs from the DataRaceBench suite (unedited)
and the 20 additional programs.  All 108 experiments should run by
typing "make".  For the DRB tests, LLOV obtains the correct result on
all but DRB140, DRB052, DRB054, and DRB069.  For the 20 additional
tests, LLOV produces the wrong answer on the following:

sync1_norace.c
critsec3.c
atomic3.c
bar1_norace.c
bar2_norace.c
bar3_norace.c
diffusion1_race.c

and fails on the following:

diffusion2_norace.c
diffusion2_race.c
critsec2.c
critsec2_race.c
prodcons.c
prodcons_race.c.


Reusability
===========

The CIVL model checker can be used in any Unix-like system with a Java
17 JDK.  It requires the automated theorem provers CVC4 and Z3 be
installed and in the user's PATH.  CIVL itself is a (modular) Java
program and can be run from the command line using the JAR file or
using the class files directly.  Type "which civl" and examine the
simple civl script to see how to invoke CIVL.  Downloads and
documentations are also available at http://vsl.cis.udel.edu/civl.

OpenMP support: as described in the paper, CIVL does not support the
entire OpenMP API.  Programs using the following OpenMP constructs
only should be supported:

Constructs:
parallel
  private, shared, firstprivate
loop worksharing construct (i.e., for)
  schedule, chunk_size, ordered, lastprivate, reduction
sections
atomic (seq_cst only)
critical (with or without name)
master
single
barrier

Functions:
omp_get_num_threads
omp_get_thread_num
omp_init_lock
omp_destroy_lock
omp_set_lock
omp_unset_lock
omp_get_wtime

