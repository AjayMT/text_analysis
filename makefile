
zipf: zipf.c text_analysis.c
	$(CC) -o zipf zipf.c

test: FORCE
	$(CC) -o test test.c
	./test

example: zipf
	./zipf $(shell stat --printf="%s" ./test-data/harry-potter.txt) < ./test-data/harry-potter.txt > ./out.txt

clean:
	rm ./zipf ./test ./out.txt

FORCE: ;
