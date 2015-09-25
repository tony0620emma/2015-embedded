CFLAGS = -mavx -Wall -g -O0 -std=gnu99 
BIN = test_base test_avxsimd
MAIN = hw1_ext.c

test: test_base test_avxsimd

test_base: $(MAIN)
	$(CC) $(CFLAGS) -o $@ $^ -DBASE
	./$@

test_avxsimd: $(MAIN)
	$(CC) $(CFLAGS) -o $@ $^ -DAVXSIMD
	./$@

.PHONY: clean

clean:
	rm -f $(BIN)
