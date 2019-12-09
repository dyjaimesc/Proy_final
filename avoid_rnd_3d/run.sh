#!/bin/bash
pwd
name="avoid_rnd_3d"
VAR=0.05
Name_walk="Walk"
col="3002"

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
#set key left top box
#unset key
splot [][] "$name.txt" u 1:2:3 title "$Name_walk 1" w lp ps $VAR lt rgb "red" pointtype 7, \
     	 # "$name.txt" u 4:5:6  title "$Name_walk 2" w lp ps $VAR lt rgb "blue" pointtype 7, \
	 # "$name.txt" u 7:8:9  title "$Name_walk 3" w lp ps $VAR lt rgb "green" pointtype 7

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
plot [][] "$name.txt" u $col:$col-1 w lp ps $VAR lt rgb "red" pointtype 7, g(x) w lp ps $VAR lt rgb "blue" pointtype 7


#f(x) = m*x + b
#fit f(x) "$name.txt" using (log(\$3002)):(log(\$3001)) via m,b

set term pdf
set output "ajuste.pdf
set xlabel "log(Steps)"
set ylabel "log(<x^2>)"
set fit quiet #Evita imprimir ajuste en consola
f(x) = a*x + b
a=1
b=1
fit f(x) "$name.txt" using (log(\$3002)):(log(\$3001)) via a,b
#set fit logfile '/dev/null' #no crear un archivo fit.log
print "error of a is:", a_err
#set label "a=%6.2f", a, "+/- %6.2f", a_err
save fit "datos_ajuste.txt
plot "$name.txt" using (log(\$3002)):(log(\$3001)), f(x) title sprintf("y=m*x+b, m=%.3f; b=%.3f", a, b)


EOF
gnuplot $name.gp

okular Rand_walk_vs_steps.pdf &
okular Mean_Rand_walk_vs_steps.pdf &
okular ajuste.pdf &

