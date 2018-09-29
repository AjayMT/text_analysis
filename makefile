
zipf: zipf.c
	$(CC) -o zipf zipf.c

test: test.c
	$(CC) -o test test.c

clean:
	rm ./zipf ./test
