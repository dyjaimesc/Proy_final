all: ejecutar #random_example.x random_example.txt

ejecutar: run.sh
	./$<

%.x: random_example.cpp
	g++ -std=c++17 -Wall -g -fsanitize=address -fsanitize=leak -fsanitize=undefined  $< -o random_example.x

%.txt: random_example.x
	./$< > $@ 

profiling:
	gprof 1_test_gprof.x gmon.out>analisis.txt


.PHONY: clean
clean:
	rm -f *.x  *~ a.out *#  *.pdf 0 *.gp *.dat 3 gmon.out
