#!/bin/bash
pwd
name="random_walk_3d"
VAR=0.05
Name_walk="Camino"

g++ -std=c++17 -Wall -g -fsanitize=address -fsanitize=leak -fsanitize=undefined  $name.cpp -o $name.x
./$name.x > $name.txt



cat <<EOF> $name.gp


set term pdf
set output "Rand_walk_vs_steps_3d.pdf"
set xlabel "x"
set ylabel "y"
set zlabel "z"
set grid
#set xtics 50
#set ytics 250
#set mxtics 2
#set mytics 2
#set logscale x 2
#set key left top box
#unset key
splot [][] "$name.txt" u 3:4:5 title "$Name_walk 1" w lp ps $VAR lt rgb "red" pointtype 7, \
     	  "$name.txt" u 6:7:8  title "$Name_walk 2" w lp ps $VAR lt rgb "blue" pointtype 7, \
	  "$name.txt" u 9:10:11  title "$Name_walk 3" w lp ps $VAR lt rgb "green" pointtype 7


set term pdf
set output "ajuste_rw_3d.pdf
set xlabel "Pasos"
set ylabel "<r^2>"
set key right bottom box
set fit quiet #Evita imprimir ajuste en consola
f(x) = a*x + b
a=1
b=1
fit f(x) "$name.txt" using 1:2 via a,b
set print "$slope.txt" append #append bandera para que me sobrescriba en el archivo ya existente
print a 
save fit "datos_ajuste.txt"
plot "$name.txt" using 1:2 title "Datos" w p ps 0.3 lt rgb "red" pointtype 7 , f(x) title sprintf("Ajuste lineal: y=m*x+b, con m=%.3f; b=%.3f", a, b)


EOF
gnuplot $name.gp

okular Rand_walk_vs_steps_3d.pdf &
okular ajuste_rw_3d.pdf &

