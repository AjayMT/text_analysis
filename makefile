
zipf: zipf.c text_analysis.c
	$(CC) -o zipf zipf.c

test: FORCE
	$(CC) -o test test.c
	./test

example: zipf
	./zipf $(shell stat --printf="%s" ./test-data/sherlock.txt) < ./test-data/sherlock.txt > ./out.txt

clean:
	rm ./zipf ./test ./out.txt

FORCE: ;
