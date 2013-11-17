all:	AL

.PHONY:
	run

AL:	main.c
	g++ main.c -o AL

clean:
	rm AL ./test/output

run:
	./AL < ./test/sample > ./test/output
