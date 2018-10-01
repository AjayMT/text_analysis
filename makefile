
zipf: zipf.c text_analysis.c
	$(CC) -o zipf zipf.c

test: test.c text_analysis.c
	$(CC) -o test test.c

clean:
	rm ./zipf ./test ./out.txt
