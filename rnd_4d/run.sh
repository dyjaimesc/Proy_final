#!/bin/bash
pwd
name="rnd_4d"
slope="Pendiente"
VAR=0.05
Name_walk="Walk"
rm $slope.txt

for i in {1..15}
do
    rm -r entrada.dat
    echo $((i))>>entrada.dat # introduzco valor del bloque

    g++ -std=c++17 -Wall -g -fsanitize=address -fsanitize=leak -fsanitize=undefined  -O3 $name.cpp -o $name.x
    /usr/bin/time ./$name.x > $name.txt
    #./$name.x > $name.txt

    

cat <<EOF> $name.gp



set term pdf
set output "Mean_RW_vs_steps_4d.pdf"
set xlabel "Pasos"
set ylabel "<r^2>"
set grid
set key right bottom box
g(x)=x
plot [][] "$name.txt" u 1:2:3 title "Datos RW 4d" w p ps 0.5 lt rgb "red" pointtype 7 , g(x) title "Camino aleatorio libre" w lp ps $VAR lt rgb "blue" pointtype 7


#f(x) = m*x + b
#fit f(x) "$name.txt" using (log(\$1)):(log(\$2)) via m,b

set term pdf
set output "ajuste_RW_4d.pdf
set xlabel "Pasos"
set ylabel "<r^2>"
set key left top box
set fit quiet #Evita imprimir ajuste en consola
f(x) = a*x + b
a=1
b=1
fit f(x) "$name.txt" using 1:2 via a,b
set print "$slope.txt" append #append bandera para que me sobrescriba en el archivo ya existente
print a #"$slope.txt" a
save fit "datos_ajuste.txt"
plot "$name.txt" using 1:2:3 title "Datos" w p ps 0.5 lt rgb "red" pointtype 7 , f(x) title sprintf("Ajuste: y=m*x+b, con m=%.3f; b=%.3f", a, b)

EOF
gnuplot $name.gp

done


okular Mean_RW_vs_steps_4d.pdf &
okular ajuste_RW_4d.pdf &

name2="media_destv"

g++ -std=c++17 -Wall -g -fsanitize=address -fsanitize=leak -fsanitize=undefined  -O3 $name2.cpp -o $name2.x
#/usr/bin/time ./$name.x #> $name.txt
echo -e "\n RW en 4 dimensiones"
./$name2.x #> $name.txt
