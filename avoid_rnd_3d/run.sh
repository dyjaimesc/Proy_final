#!/bin/bash
pwd
name="avoid_rnd_3d"
slope="Pendiente"
VAR=0.05
Name_walk="Walk"
rm $slope.txt

for i in {1..15}
do
    rm -r entrada.dat
    echo $((i))>>entrada.dat # introduzco valor del bloque

g++ -std=c++17 -Wall -g -fsanitize=address -fsanitize=leak -fsanitize=undefined  $name.cpp -o $name.x
/usr/bin/time ./$name.x > $name.txt

cat <<EOF> $name.gp

set term pdf
set output "Saw_vs_steps_3d.pdf"
set xlabel "x"
set ylabel "y"
set grid
splot [][] "$name.txt" u 4:5:6 title "$Name_walk 1" w lp ps $VAR lt rgb "red" pointtype 7, \
     	  "$name.txt" u 7:8:9  title "$Name_walk 2" w lp ps $VAR lt rgb "blue" pointtype 7, \
	  "$name.txt" u 10:11:12  title "$Name_walk 3" w lp ps $VAR lt rgb "green" pointtype 7

set term pdf
set output "Mean_SAW_vs_steps_3d.pdf"
set xlabel "Steps"
set ylabel "<r^2>"
set grid

set key right bottom box
g(x)=x
plot [][] "$name.txt" u 1:2:3 title "Datos SAW" w p ps 0.5 lt rgb "red" pointtype 7 , g(x) title "Camino aleatorio libre" w lp ps $VAR lt rgb "blue" pointtype 7


set term pdf
set output "ajuste_SAW_3d.pdf
set xlabel "log(Steps)"
set ylabel "log(<r^2>)"
set key left top box
set fit quiet #Evita imprimir ajuste en consola
f(x) = a*x + b
a=1
b=1
fit f(x) "$name.txt" using (log(\$1)):(log(\$2)) via a,b
set print "$slope.txt" append
print a #"$slope.txt" a
save fit "datos_ajuste.txt
plot "$name.txt" using (log(\$1)):(log(\$2)):(log(\$3)) title "Datos" w p ps 0.5 lt rgb "red" pointtype 7 , f(x) title sprintf("Fit y=m*x+b, m=%.3f; b=%.3f", a, b)# w lp ps 0.1 lt rgb "green"


EOF
gnuplot $name.gp

done

okular Saw_vs_steps_3d.pdf &
okular Mean_SAW_vs_steps_3d.pdf &
okular ajuste_SAW_3d.pdf &

name2="media_destv"

g++ -std=c++17 -Wall -g -fsanitize=address -fsanitize=leak -fsanitize=undefined  -O3 $name2.cpp -o $name2.x
#/usr/bin/time ./$name.x #> $name.txt
echo -e "\n SAW 3 dimensiones"
./$name2.x #> $name.txt


