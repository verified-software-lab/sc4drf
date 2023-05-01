CIVL=civl
VERIFY=$(CIVL) verify -ompNoSimplify -enablePrintf=false

all: sync1_no sync1_yes critsec3_no critsec3_yes atomic3_no atomic3_yes diffusion1_no diffusion1_yes diffusion2_no diffusion2_yes critsec2_no critsec2_yes prodcons_no prodcons_yes bar1_no bar1_yes bar2_no bar2_yes bar3_no bar3_yes 

sync1_no: sync1_no.c
	$(VERIFY) -input_omp_thread_max=2 $<

sync1_yes: sync1_yes.c
	$(VERIFY) -input_omp_thread_max=2 $<

critsec3_no: critsec3_no.c
	$(VERIFY) -input_omp_thread_max=2 $<

critsec3_yes: critsec3_yes.c
	$(VERIFY) -input_omp_thread_max=2 $<

atomic3_no: atomic3_no.c
	$(VERIFY) -input_omp_thread_max=2 $<

atomic3_yes: atomic3_yes.c
	$(VERIFY) -input_omp_thread_max=2 $<

bar1_no: bar1_no.c
	$(VERIFY) -input_omp_thread_max=2 $<

bar1_yes: bar1_yes.c
	$(VERIFY) -input_omp_thread_max=2 $<

bar2_no: bar2_no.c
	$(VERIFY) -input_omp_thread_max=2 $<

bar2_yes: bar2_yes.c
	$(VERIFY) -input_omp_thread_max=2 $<

bar3_no: bar3_no.c
	$(VERIFY) -input_omp_thread_max=2 $<

bar3_yes: bar3_yes.c
	$(VERIFY) -input_omp_thread_max=2 $<

diffusion1_no: diffusion1_no.c
	$(VERIFY) -input_omp_thread_max=5 $<

diffusion1_yes: diffusion1_yes.c
	$(VERIFY) -input_omp_thread_max=5 -errorBound=3 $<

diffusion2_no: diffusion2_no.c
	$(VERIFY) -input_omp_thread_max=5 $<

diffusion2_yes: diffusion2_yes.c
	$(VERIFY) -input_omp_thread_max=5 $<

critsec2_no : critsec2_no.c
	$(VERIFY) -input_omp_thread_max=2 $<

critsec2_yes : critsec2_yes.c
	$(VERIFY) -input_omp_thread_max=2 $<

prodcons_no  : prodcons_no.c
	$(VERIFY) -input_omp_thread_max=8 $<

prodcons_yes : prodcons_yes.c
	$(VERIFY) -input_omp_thread_max=8 $<

clean:
	rm -rf *~ CIVLREP OUT *.tmp 
