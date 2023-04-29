CIVL=civl-omp
BOUND_VERIFY=$(CIVL) verify -ompNoSimplify -enablePrintf=false -input_omp_thread_max=5 -inputBOUND=10
VERIFY=$(CIVL) verify -ompNoSimplify -input_omp_thread_max=5 -enablePrintf=false
VERIFY2=$(CIVL) verify -ompNoSimplify -input_omp_thread_max=2 -enablePrintf=false

all: all_yes all_no

all_yes: $(patsubst  %.c, C_%, $(wildcard *yes.c))

all_no: $(patsubst  %.c, C_%, $(wildcard *no.c))

C_%: %.c
	$(BOUND_VERIFY) $<

C_DRB005-indirectaccess1-orig-yes:: DRB005-indirectaccess1-orig-yes.c
	$(VERIFY) -inputN=10 $<

C_DRB006-indirectaccess2-orig-yes:: DRB006-indirectaccess2-orig-yes.c
	$(VERIFY) -inputN=10 $<

C_DRB007-indirectaccess3-orig-yes:: DRB007-indirectaccess3-orig-yes.c
	$(VERIFY) -inputN=10 $<

C_DRB008-indirectaccess4-orig-yes:: DRB008-indirectaccess4-orig-yes.c
	$(VERIFY) -inputN=10 $<

C_DRB009-lastprivatemissing-orig-yes:: DRB009-lastprivatemissing-orig-yes.c
	$(VERIFY) -inputN=10 $<

C_DRB010-lastprivatemissing-var-yes:: DRB010-lastprivatemissing-var-yes.c
	$(VERIFY) -inputN=10 $<

C_DRB016-outputdep-orig-yes:: DRB016-outputdep-orig-yes.c
	$(VERIFY) -inputN=10 $<

C_DRB017-outputdep-var-yes:: DRB017-outputdep-var-yes.c
	$(VERIFY) -inputN=10 $<

C_DRB023-sections1-orig-yes::  DRB023-sections1-orig-yes.c
	$(VERIFY) $<

C_DRB035-truedepscalar-orig-yes:: DRB035-truedepscalar-orig-yes.c
	$(VERIFY) -inputN=10 $<

C_DRB036-truedepscalar-var-yes:: DRB036-truedepscalar-var-yes.c
	$(VERIFY) -inputN=10 $<

C_DRB039-truedepsingleelement-orig-yes:: DRB039-truedepsingleelement-orig-yes.c
	$(VERIFY) -inputN=10 $<

C_DRB040-truedepsingleelement-var-yes:: DRB040-truedepsingleelement-var-yes.c
	$(VERIFY) -inputN=10 $<

C_DRB041-3mm-parallel-no:: DRB041-3mm-parallel-no.c
	$(VERIFY2) -inputN=10 $<

C_DRB043-adi-parallel-no:: DRB043-adi-parallel-no.c
	$(VERIFY2) -inputN=4 $<

C_DRB045-doall1-orig-no:: DRB045-doall1-orig-no.c
	$(VERIFY) -inputN=10 $<

C_DRB046-doall2-orig-no:: DRB046-doall2-orig-no.c
	$(VERIFY) -inputN=10 $<

C_DRB051-getthreadnum-orig-no:: DRB051-getthreadnum-orig-no.c
	$(VERIFY) $<

C_DRB055-jacobi2d-parallel-no:: DRB055-jacobi2d-parallel-no.c
	$(VERIFY) -inputN=10 $<

C_DRB058-jacobikernel-orig-no:: DRB058-jacobikernel-orig-no.c
	$(VERIFY) -inputBOUND=5 $<

C_DRB059-lastprivate-orig-no::  DRB059-lastprivate-orig-no.c
	$(VERIFY) $<

C_DRB060-matrixmultiply-orig-no:: DRB060-matrixmultiply-orig-no.c
	$(VERIFY) $<

C_DRB062-matrixvector2-orig-no:: DRB062-matrixvector2-orig-no.c
	$(VERIFY2) -inputBOUND=10 $<

C_DRB069-sectionslock1-orig-no:: DRB069-sectionslock1-orig-no.c
	$(VERIFY2) $<

C_DRB073-doall2-orig-yes:: DRB073-doall2-orig-yes.c
	$(VERIFY) -inputN=10 $<

C_DRB075-getthreadnum-orig-yes:: DRB075-getthreadnum-orig-yes.c
	$(VERIFY) $<

C_DRB076-flush-orig-no:: DRB076-flush-orig-no.c
	$(VERIFY2) $<

C_DRB077-single-orig-no:: DRB077-single-orig-no.c
	$(VERIFY) $<

C_DRB088-dynamic-storage-orig-yes:: DRB088-dynamic-storage-orig-yes.c
	$(VERIFY) $<

C_DRB089-dynamic-storage2-orig-yes:: DRB089-dynamic-storage2-orig-yes.c
	$(VERIFY) $<

C_DRB103-master-orig-no:: DRB103-master-orig-no.c
	$(VERIFY) $<

C_DRB108-atomic-orig-no:: DRB108-atomic-orig-no.c
	$(VERIFY) $<

C_DRB109-orderedmissing-orig-yes:: DRB109-orderedmissing-orig-yes.c
	$(VERIFY) -inputN=10 $<

C_DRB120-barrier-orig-no:: DRB120-barrier-orig-no.c
	$(VERIFY) $<

C_DRB121-reduction-orig-no:: DRB121-reduction-orig-no.c
	$(VERIFY) $<

C_DRB124-master-orig-yes:: DRB124-master-orig-yes.c
	$(VERIFY) $<

C_DRB125-single-orig-no:: DRB125-single-orig-no.c
	$(VERIFY) $<

C_DRB126-firstprivatesections-orig-no:: DRB126-firstprivatesections-orig-no.c
	$(VERIFY2) $<

C_DRB139-worksharingcritical-orig-no:: DRB139-worksharingcritical-orig-no.c
	$(VERIFY) $<

C_DRB141-reduction-barrier-orig-no:: DRB141-reduction-barrier-orig-no.c
	$(VERIFY2) $<

C_DRB172-critical2-orig-no:: DRB172-critical2-orig-no.c
	$(VERIFY) $<

clean:
	rm -rf CIVLREP *~
