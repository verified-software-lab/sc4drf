# This Makefile will run all LLOV DataRaceBench experiments
# Type "make foo" to verify foo.c only.
# Type "make" to run all experiments.
# LLOV's output is sent to a file (see variable OUT).
# A summary of results is printed to stdout.

POLYFLAG = utilities/polybench.c -I. -Iutilities -DPOLYBENCH_NO_FLUSH_CACHE -DPOLYBENCH_TIME -D_POSIX_C_SOURCE=200112L
LLOV_DIR = $(HOME)/LLOV-v0.3
LLVM_DIR = /usr/lib/llvm-10/lib/clang/10.0.0

LVERIFY = $(LLOV_DIR)/bin/clang $(POLYFLAG) -I$(LLOV_DIR)/include -I$(LLVM_DIR)/include/ -L$(LLOV_DIR)/lib -lm -Xclang -disable-O0-optnone -Xclang -load -Xclang $(LLOV_DIR)/lib/OpenMPVerify.so -fopenmp -g # LLOV's verify command, assuming civl is in the PATH
OUT = llov_out.txt   # LLOV output appended to this file
LOG = 2>&1 | tee -a $(OUT)  # copy stdout to OUT file
CHECK_Y = $(LOG) | grep -q "Data Race detected."; \
  if [ $$? -eq 0 ]; then echo "PASS"; else echo "FAIL"; fi
CHECK_N = $(LOG) | grep -q "Data Race detected."; \
  if [ $$? -eq 0 ]; then echo "FAIL"; else echo "PASS"; fi

GROUP1 = DRB023-sections1-orig-yes \
DRB051-getthreadnum-orig-no \
DRB059-lastprivate-orig-no \
DRB069-sectionslock1-orig-no \
DRB075-getthreadnum-orig-yes \
DRB076-flush-orig-no \
DRB077-single-orig-no \
DRB088-dynamic-storage-orig-yes \
DRB089-dynamic-storage2-orig-yes \
DRB074-flush-orig-yes \
DRB103-master-orig-no \
DRB108-atomic-orig-no \
DRB120-barrier-orig-no \
DRB121-reduction-orig-no \
DRB124-master-orig-yes \
DRB125-single-orig-no \
DRB126-firstprivatesections-orig-no \
DRB139-worksharingcritical-orig-no \
DRB140-reduction-barrier-orig-yes \
DRB141-reduction-barrier-orig-no \
DRB172-critical2-orig-no \
DRB001-antidep1-orig-yes \
DRB002-antidep1-var-yes \
DRB003-antidep2-orig-yes \
DRB004-antidep2-var-yes \
DRB011-minusminus-orig-yes \
DRB012-minusminus-var-yes \
DRB013-nowait-orig-yes \
DRB014-outofbounds-orig-yes \
DRB015-outofbounds-var-yes \
DRB018-plusplus-orig-yes \
DRB019-plusplus-var-yes \
DRB020-privatemissing-var-yes \
DRB021-reductionmissing-orig-yes \
DRB022-reductionmissing-var-yes \
DRB028-privatemissing-orig-yes \
DRB029-truedep1-orig-yes \
DRB030-truedep1-var-yes \
DRB031-truedepfirstdimension-orig-yes \
DRB032-truedepfirstdimension-var-yes \
DRB033-truedeplinear-orig-yes \
DRB034-truedeplinear-var-yes \
DRB037-truedepseconddimension-orig-yes \
DRB038-truedepseconddimension-var-yes \
DRB041-3mm-parallel-no \
DRB047-doallchar-orig-no \
DRB048-firstprivate-orig-no \
DRB050-functionparameter-orig-no \
DRB052-indirectaccesssharebase-orig-no \
DRB053-inneronly1-orig-no \
DRB054-inneronly2-orig-no \
DRB057-jacobiinitialize-orig-no \
DRB060-matrixmultiply-orig-no \
DRB061-matrixvector1-orig-no \
DRB063-outeronly1-orig-no \
DRB064-outeronly2-orig-no \
DRB065-pireduction-orig-no \
DRB066-pointernoaliasing-orig-no \
DRB067-restrictpointer1-orig-no \
DRB068-restrictpointer2-orig-no \
DRB090-static-local-orig-yes \
DRB093-doall2-collapse-orig-no \
DRB104-nowait-barrier-orig-no \
DRB110-ordered-orig-no \
DRB111-linearmissing-orig-yes \
DRB113-default-orig-no \
DRB169-missingsyncwrite-orig-yes \
DRB170-nestedloops-orig-no \
DRB005-indirectaccess1-orig-yes \
DRB006-indirectaccess2-orig-yes \
DRB007-indirectaccess3-orig-yes \
DRB008-indirectaccess4-orig-yes \
DRB009-lastprivatemissing-orig-yes \
DRB010-lastprivatemissing-var-yes \
DRB016-outputdep-orig-yes \
DRB017-outputdep-var-yes \
DRB035-truedepscalar-orig-yes \
DRB036-truedepscalar-var-yes \
DRB039-truedepsingleelement-orig-yes \
DRB040-truedepsingleelement-var-yes \
DRB045-doall1-orig-no \
DRB046-doall2-orig-no \
DRB055-jacobi2d-parallel-no \
DRB073-doall2-orig-yes \
DRB109-orderedmissing-orig-yes \
DRB043-adi-parallel-no \
DRB058-jacobikernel-orig-no \
DRB062-matrixvector2-orig-no

GROUP1_Y = $(filter %yes,$(GROUP1))
GROUP1_N = $(filter %no,$(GROUP1))

ALL = $(GROUP1) 

run: clean
	$(MAKE) all

all: $(ALL)

$(GROUP1_Y) : % : %.c
	@echo "Checking $@ ..." $(LOG)
	@$(LVERIFY) $< $(CHECK_Y)
	@echo "" $(LOG)

$(GROUP1_N) : % : %.c
	@echo "Checking $@ ..." $(LOG)
	@$(LVERIFY) $< $(CHECK_N)
	@echo "" $(LOG)

clean:
	rm -rf *~ *.tmp a.out $(OUT) 

.PHONY: all clean $(ALL) run
