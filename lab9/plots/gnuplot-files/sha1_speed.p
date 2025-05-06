set terminal pngcairo size 900,900

set title "Расчётная кривая скорости расчёта хеша"
set xlabel "Размер входных данных (N)"
set ylabel "Время (мс)"
set grid

set output "plots/pictures/sha1_speed.png"
plot "plots/dat-files/sha1_speed.dat" using 1:2 title "SHA-1" with linespoints
