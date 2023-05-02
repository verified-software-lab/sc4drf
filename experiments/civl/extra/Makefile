# This Makefile will run all CIVL "extra" experiments
# Type "make foo" to verify foo.c only.
# Type "make" to run all experiments.
# CIVL's output is sent to a file (see variable OUT).
# A summary of results is printed to stdout.

VERIFY= civl verify -errorBound=3
OUT = civl_out.txt
LOG = | tee -a $(OUT)
CHECK_Y = $(LOG) | grep "Data-race detected"; \
  if [ $$? -eq 0 ]; then echo "PASS"; else echo "FAIL"; fi
CHECK_N = $(LOG) | grep "All properties .* hold"; \
  if [ $$? -eq 0 ]; then echo "PASS"; else echo "FAIL"; fi
ALL = sync1 critsec3 atomic3  diffusion1 diffusion2 critsec2 prodcons bar1 bar2 bar3

run: clean
	$(MAKE) all

all: $(ALL)

sync1 critsec2 critsec3 atomic3 bar1 bar2 bar3 : % : %_yes.c %_no.c
	@echo "Checking $*_yes.c ..." $(LOG)
	@$(VERIFY) -input_omp_thread_max=2 $*_yes.c $(CHECK_Y)
	@echo "Checking $*_no.c ..." $(LOG)
	@$(VERIFY) -input_omp_thread_max=2 $*_no.c $(CHECK_N)

diffusion1 diffusion2 :  % : %_yes.c %_no.c
	@echo "Checking $*_yes.c ..." $(LOG)
	@$(VERIFY) -input_omp_thread_max=5 $*_yes.c $(CHECK_Y)
	@echo "Checking $*_no.c ..." $(LOG)
	@$(VERIFY) -input_omp_thread_max=5 $*_no.c $(CHECK_N)

prodcons : % : %_yes.c %_no.c
	@echo "Checking $*_yes.c ..." $(LOG)
	@$(VERIFY) -input_omp_thread_max=8 $*_yes.c $(CHECK_Y)
	@echo "Checking $*_no.c ..." $(LOG)
	@$(VERIFY) -input_omp_thread_max=8 $*_no.c $(CHECK_N)

clean:
	rm -rf *~ CIVLREP $(OUT) *.tmp a.out

.PHONY: $(ALL) all clean run
