all:
	cc -c src/main.c -o build/main.o
	cc -o bin/Program build/main.o

run:
	./bin/Program

clean:
	rm -f build/* bin/*

buildRun: clean all run