set terminal pngcairo size 900,900

set title "Расчётные кривые наихудшего времени выполнения сортировки и сложности алгоритма"
set xlabel "Размер массива (M)" 
set ylabel "Время (t, мс)"
set grid

set output "plots/pictures/worst_and_complexity.png"
plot "plots/files/worst_and_complexity.dat" using 1:2 title "Наихудший вариант" with linespoints, \
     "plots/files/worst_and_complexity.dat" using 1:3 title "O(M^2)" with linespoints
