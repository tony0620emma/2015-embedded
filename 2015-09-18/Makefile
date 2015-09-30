CFLAGS = -march=native -Wall -g -O0 -std=gnu99 
BIN = test_base test_avxsimd test_avxsimd_v2 test_avxsimd_v3
MAIN = hw1_ext.c

test: $(BIN)

test_base: $(MAIN)
	$(CC) $(CFLAGS) -o $@ $^ -DBASE
	./$@ > base.txt

test_avxsimd: $(MAIN)
	$(CC) $(CFLAGS) -o $@ $^ -DAVXSIMD
	./$@ > avxsimd_v1.txt

test_avxsimd_v2: $(MAIN)
	$(CC) $(CFLAGS) -o $@ $^ -DAVXSIMD2
	./$@ > avxsimd_v2.txt

test_avxsimd_v3: $(MAIN)
	$(CC) $(CFLAGS) -o $@ $^ -DAVXSIMD3
	./$@ > avxsimd_v3.txt

.PHONY: clean

clean:
	rm -f $(BIN) *.txt *.png
