CMD=sed 's/\#include/__include__/g' 
OPTS= | cpp -P | sed 's/__NL__/\n/g' | sed 's/__pragma__/\#pragma/g' | sed 's/__include__/\#include/g'

all: bar1_norace_prep.c bar1_race_prep.c bar1_subtle_race_prep.c bar3_norace_prep.c bar3_race_prep.c

bar1_norace_prep.c: bar1_norace.c
	$(CMD) $^ $(OPTS) > $@

bar1_race_prep.c: bar1_race.c
	$(CMD) $^ $(OPTS) > $@

bar1_subtle_race_prep.c: bar1_subtle_race.c
	$(CMD) $^ $(OPTS) > $@

bar3_norace_prep.c: bar3_norace.c
	$(CMD) $^ $(OPTS) > $@

bar3_race_prep.c: bar3_race.c
	$(CMD) $^ $(OPTS) > $@

clean:
	rm bar1_norace_prep.c bar1_race_prep.c bar1_subtle_race_prep.c bar3_norace_prep.c bar3_race_prep.c
