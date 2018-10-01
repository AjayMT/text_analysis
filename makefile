
zipf: zipf.c text_analysis.c
	$(CC) -o zipf zipf.c

test: test.c text_analysis.c
	$(CC) -o test test.c
	./test

example: zipf
	./zipf $(shell stat --printf="%s" ./test-data/harry-potter.txt) < ./test-data/harry-potter.txt > ./out.txt

clean:
	rm ./zipf ./test ./out.txt
