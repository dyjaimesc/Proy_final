#!/bin/bash
pwd
name="random_walk_2d"
VAR=0.05
Name_walk="Walk"

g++ -std=c++17 -Wall -g -fsanitize=address -fsanitize=leak -fsanitize=undefined  $name.cpp -o $name.x
./$name.x > $name.txt



cat <<EOF> $name.gp


set term pdf
set output "Rand_walk_vs_steps.pdf"
set xlabel "x"
set ylabel "y"
set grid
#set xtics 50
#set ytics 250
#set mxtics 2
#set mytics 2
#set logscale x 2
set key left top box
#unset key
plot [][] "$name.txt" u 3:4 title "$Name_walk 1" w lp ps $VAR lt rgb "red" pointtype 7, \
     	  "$name.txt" u 5:6  title "$Name_walk 2" w lp ps $VAR lt rgb "blue" pointtype 7, \
	  "$name.txt" u 7:8  title "$Name_walk 3" w lp ps $VAR lt rgb "green" pointtype 7

set term pdf
set output "Mean_Rand_walk_vs_steps.pdf"
set xlabel "Steps"
set ylabel "<x^2>"
set grid
#set xtics 50
#set ytics 250
#set mxtics 2
#set mytics 2
#set logscale x 
#set logscale y
set key right bottom box
g(x)=x
plot [][] "$name.txt" u 1:2 w lp ps $VAR lt rgb "red" pointtype 7, g(x) w lp ps $VAR lt rgb "blue" pointtype 7


EOF
gnuplot $name.gp

okular Rand_walk_vs_steps.pdf &
okular Mean_Rand_walk_vs_steps.pdf &

