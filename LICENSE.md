# License

## Dependencies
The Ubuntu operating system and its installed packages are governed by
their respective licenses that allow redistribution and use under
certain restrictions. This includes the following packages that we installed
using the `apt` package manager:

 - ant
 - cvc4
 - z3
 - openjdk-17
 - subversion
 - vim
 - grip
 - zerofree

The last four packages are not needed by CIVL or LLOV, but were useful
during the preparation of this artifact. We also installed the VirtualBox Guest
Additions (under GPLv2 license) to improve the usability of our artifact.

## Experiments

All experiments are located in /home/vboxuser/Desktop/sc4drf/experiments. The
experiments consist of the following files from DataRaceBench:

    experiments/llov/micro-benchmarks/*.c
    experiments/llov/micro-benchmarks/polybench/*
    experiments/llov/micro-benchmarks/utilities/*
    experiments/civl/micro-benchmarks/*.c

DataRaceBench files are covered by the DataRaceBench license found in
experiments/llov/micro-benchmarks/LICENSE.txt, which allows
redistribution and use in source and binary forms, with or without
modification, under certain restrictions (3-clause BSD license).

We added new experiments and scripts to run the DataRaceBench experiments.
We release our own files under GPLv3 license. The files are located in

    experiments/civl/extras : all files
    experiments/llov/extras : all files
    experiments/civl/micro-benchmarks: Makefile, civl_out.txt, results_m1mac,
                                       summary.txt, times.txt, CIVLREP
    experiments/llov/micro-benchmarks: Makefile, llov_expected_output.txt

## CIVL

The CIVL tool is located in `/home/vboxuser/CIVL` and is released under GPLv3 license. 
The license file can be found at `/home/vboxuser/CIVL/README`

## LLOV

The license for LLOV can be found in `/home/vboxuser/LLOV-v0.3/LICENSE.txt` and
allows redistribution and reuse under certain restrictions.
4. The LLOV tool in .... (4-clause BSD license).
