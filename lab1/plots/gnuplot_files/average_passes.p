set terminal pngcairo size 900,900

set title "Расчётная кривая повторных обходов массива"
set xlabel "Размер массива (M)" 
set ylabel "Количество повторных обходов (passes)"
set grid

set output "plots/pictures/average_passes.png"
plot "plots/files/average_passes.dat" using 1:2 title "Среднее количество обходов" with linespoints
