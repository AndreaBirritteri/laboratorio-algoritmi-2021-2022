default: main

clean:
	rm -f -r bin/*

unity:
	cc -c ../Unity/unity.c -o bin/unity.o

ordered_array:
	cc -c src/ordered_array.c -o bin/ordered_array.o

sorting:
	cc -c src/sorting.c -o bin/sorting.o

test: sorting ordered_array unity
	cc -c src/test.c -o bin/test.o
	cc -o bin/test bin/sorting.o bin/ordered_array.o bin/unity.o bin/test.o
	./bin/test

main: ordered_array sorting
	cc -c src/main.c -o bin/main.o
	cc -o bin/exercise_1 bin/sorting.o bin/ordered_array.o bin/main.o

exec_binary_insertion_sort: clean main
	./bin/exercise_1 files/records.csv 0

exec_quick_sort: clean main
	./bin/exercise_1 files/records.csv 1