default: main

clean: 
	rm -f -r bin/*

unity:
	cc -c ../Unity/unity.c -o bin/unity.o

utils:
	cc -c src/utils.c -o bin/utils.o

skip_list:
	cc -c src/skip_list.c -o bin/skip_list.o

test: skip_list utils unity
	cc -c src/test.c -o bin/test.o
	cc -o bin/test bin/utils.o bin/skip_list.o bin/unity.o bin/test.o
	./bin/test

main: skip_list utils
	cc -c src/main.c -o bin/main.o
	cc -o bin/exercise_2 bin/skip_list.o bin/utils.o bin/main.o

exec: clean main
	./bin/exercise_2 files/dictionary.txt files/correctme.txt