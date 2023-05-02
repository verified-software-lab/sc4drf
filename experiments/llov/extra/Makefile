# This Makefile will run all LLOV DataRaceBench experiments
# Type "make foo" to verify foo.c only.
# Type "make" to run all experiments.
# LLOV's output is sent to a file (see variable OUT).
# A summary of results is printed to stdout.

LLOV_DIR = $(HOME)/LLOV-v0.3
LLVM_DIR = /usr/lib/llvm-10/lib/clang/10.0.0

LVERIFY = $(LLOV_DIR)/bin/clang -I$(LLOV_DIR)/include -I$(LLVM_DIR)/include/ -L$(LLOV_DIR)/lib -lm -Xclang -disable-O0-optnone -Xclang -load -Xclang $(LLOV_DIR)/lib/OpenMPVerify.so -fopenmp -g # LLOV's verify command, assuming civl is in the PATH
OUT = llov_out.txt   # LLOV output appended to this file
LOG = 2>&1 | tee -a $(OUT)  # copy stdout to OUT file
CHECK_Y = $(LOG) | grep -q "Data Race detected."; \
  if [ $$? -eq 0 ]; then echo "PASS"; else echo "FAIL"; fi
CHECK_N = $(LOG) | grep -q "Data Race detected."; \
  if [ $$? -eq 0 ]; then echo "FAIL"; else echo "PASS"; fi

GROUP1 = atomic3_no \
atomic3_yes \
bar1_no \
bar1_yes \
bar2_no \
bar2_yes \
bar3_no \
bar3_yes \
critsec2_no \
critsec2_yes \
critsec3_no \
critsec3_yes \
diffusion1_no \
diffusion1_yes \
diffusion2_no \
diffusion2_yes \
prodcons_no \
prodcons_yes \
sync1_no \
sync1_yes

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
