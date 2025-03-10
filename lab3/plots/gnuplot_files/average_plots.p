set terminal pngcairo size 900,900

set title "Расчётная кривая среднего количества обмена значений"
set xlabel "Размер массива (M)" 
set ylabel "Количество обменов (swaps)"
set grid

set output "plots/pictures/average_swaps.png"
plot "plots/files/average_swaps.dat" using 1:2 title "Среднее количество обменов" with linespoints
