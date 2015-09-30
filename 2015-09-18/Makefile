CFLAGS = -march=native -Wall -g -O0 -std=gnu99 
BIN = test_base test_avxsimd test_avxsimd_v2
MAIN = hw1_ext.c

test: test_base test_avxsimd test_avxsimd_v2

test_base: $(MAIN)
	$(CC) $(CFLAGS) -o $@ $^ -DBASE
	./$@

test_avxsimd: $(MAIN)
	$(CC) $(CFLAGS) -o $@ $^ -DAVXSIMD
	./$@

test_avxsimd_v2: $(MAIN)
	$(CC) $(CFLAGS) -o $@ $^ -DAVXSIMD2
	./$@ 

.PHONY: clean

clean:
	rm -f $(BIN)
