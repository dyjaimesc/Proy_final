#!/bin/bash
pwd
g++ -std=c++17 -Wall -g -fsanitize=address -fsanitize=leak -fsanitize=undefined  random_example.cpp -o random_example.x
./random_example.x > random_example.txt

VAR=0.1

cat <<EOF> random_example.gp


set term pdf
set output "Rand_walk_vs_steps.pdf"
set xlabel "Steps"
set ylabel "x"
set grid
#set xtics 50
#set ytics 250
#set mxtics 2
#set mytics 2
#set logscale x 2
unset key
plot [][] "random_example.txt" u 1:2 w lp ps $VAR lt rgb "red" pointtype 7, \
     	  "random_example.txt" u 1:3 w lp ps $VAR lt rgb "blue" pointtype 7, \
	  "random_example.txt" u 1:5 w lp ps $VAR lt rgb "green" pointtype 7

set term pdf
set output "Mean_Rand_walk_vs_steps.pdf"
set xlabel "Steps"
set ylabel "<x^2>"
set grid
#set xtics 50
#set ytics 250
#set mxtics 2
#set mytics 2
#set logscale x 2
set key
plot [][] "random_example.txt" u 1:502 w lp ps $VAR lt rgb "red" pointtype 7
replot x w lp ps $VAR lt rgb "blue" pointtype 7




EOF
gnuplot random_example.gp

okular Rand_walk_vs_steps.pdf &
okular Mean_Rand_walk_vs_steps.pdf &

