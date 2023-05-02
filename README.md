
This is the Artifact for the CAV 2023 paper:
*Model Checking Race-Freedom when "Sequential Consistency for  Data-race-free Programs" is Guaranteed*

# Overview of this Artifact

The artifact consists of a VirtualBox machine running Ubuntu 22.04 LTS, which
has all software installed that is needed for the experiments reported in the
paper.

## Starting the Artifact

Please follow these steps:

 - Start VirtualBox 
 - Click "Add"
 - Select the sc4drf virtual machine image
 - Follow the prompts to set up and start the virtual machine
 - The machine should log in automatically. If a username or password is ever
   required, use `vboxuser` as username and `changeme` as password.
 - Double-click the `sc4drf` folder on the Desktop
 - In the folder window that appears, right-click and select "Open in Terminal"
 - Follow the steps under "replication of experiments" below.

## Artifact Contents

Most of the contents are available on
https://github.com/verified-software-lab/sc4drf. This repository contains:

 - README (this file)
 - experiments
   - civl
     - micro-benchmarks
       - 88 DataRaceBench input files used in experiments
       - Makefile
       - results_m1mac (results of running experiments on M1 MacBook Pro)
     - extra
       - the 20 extra problems
       - Makefile
       - results_m1mac
   - llov
     - micro-benchmarks
       - 88 DataRaceBench input files used in experiments
       - Makefile
       - llov_expected_output (results of running experiments)
     - extra
       - the 20 extra problems
       - Makefile
       - llov_expected_output (results of running experiments)

The virtual machine contains a clone of this repository, and preinstalled
software:
 - CIVL (source, documentation, executable, examples)
 - CIVL dependencies: CVC4, Z3, Java JRE
 - LLOV (the static analysis tool)
 - LLOV dependencies: llvm, clang

The machine also has modified scripts inside the `sc4drf` folder to run the
experiments, with environment variables and locations adjusted to work in the
virtual machine.

## Replication of Experiments Reported in Paper

Section 3.4 "Evaluation" describes the experiments.  Two tools were used: CIVL
and LLOV.  The artifacts for CIVL are in the civl directory, and those for LLOV
are in llov.

**civl:** there are 88 programs from the DataRaceBench suite.  All have
filenames beginning with `DRB`.  As described in the paper, 68 of these 88 have
been manually edited by us.  (The original unedited versions can be found in
the llov directory.)  There are in addition 20 programs which we wrote
ourselves.

All 108 experiments should run by executing the following inside the `sc4drf`
repository folder:

    (cd experiments/civl/micro-benchmarks && make)
    (cd experiments/civl/extra && make)

Files with `yes` in the filename have a datarace; those with `no` in the
filename do not have a datarace.  The paper reports that CIVL gets the correct
result (race or no race) on all tests except DRB139, DRB014, and DRB015.
Additional information can be found in the README files in the results_m1mac
directories.  The detailed CIVL output file `civl_out.txt` also reports total
runtime for each test.

**llov:** there are 88 programs from the DataRaceBench suite (unedited) and the
20 additional programs.  All 108 experiments should run by typing the following
inside the `sc4drf` repository folder:

    (cd experiments/llov/micro-benchmarks && make)
    (cd experiments/llov/extra && make)

For the DRB tests, LLOV obtains the correct result on all but DRB140, DRB052,
DRB054, and DRB069.  For the 20 additional tests, LLOV produces the wrong
answer on the following:

 - sync1_norace.c
 - critsec3.c
 - atomic3.c
 - bar1_norace.c
 - bar2_norace.c
 - bar3_norace.c
 - diffusion1_race.c

and fails on the following:

 - diffusion2_norace.c
 - diffusion2_race.c
 - critsec2.c
 - critsec2_race.c
 - prodcons.c
 - prodcons_race.c.


## Reusability

The CIVL model checker can be used in any Unix-like system with a Java 17 JDK.
It requires the automated theorem provers CVC4 and Z3 be installed and in the
user's PATH. All of these are available with common package managers. CIVL
itself is a (modular) Java program and can be run from the command line using
the JAR file or using the class files directly.  Type `which civl` and examine
the simple civl script to see how to invoke CIVL.  Downloads and documentations
are also available at http://vsl.cis.udel.edu/civl.

**OpenMP support.** as described in the paper, CIVL does not support the entire
OpenMP API.  Programs using the following OpenMP features are supported:

**constructs**:
 - parallel
 -  private, shared, firstprivate
 - loop worksharing construct (i.e., for)
 -   schedule, chunk_size, ordered, lastprivate, reduction
 - sections
 - atomic (seq_cst only)
 - critical (with or without name)
 - master
 - single
 - barrier

**Functions:**
 - omp_get_num_threads
 - omp_get_thread_num
 - omp_init_lock
 - omp_destroy_lock
 - omp_set_lock
 - omp_unset_lock
 - omp_get_wtime

To run CIVL on a C/OpenMP program, execute:

    civl verify -input_omp_thread_max=N filename.c

where `N` is the upper bound on the default number of OpenMP threads to be used
for an OpenMP parallel region and `filename.c` is the file to be verified.
Programs can also be instrumented to specify parameters and ranges; see
`sc4drf/experiments/civl/micro-benchmarks/DRB001-antidep1-orig-yes.c` for an
example.  To specify a particular value `VAL` for an input variable `VAR`, add
`-input_VAR=VAL` to the command line after "verify", e.g.,

    civl verify -input_omp_thread_max=5 -inputBOUND=10 filename.c

