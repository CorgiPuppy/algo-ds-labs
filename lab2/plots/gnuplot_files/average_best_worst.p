set terminal pngcairo size 900,900

set title "Расчётные кривые среднего, наилучшего и наихудшего времени исполнения"
set xlabel "Размер массива (M)" 
set ylabel "Время (t, мс)"
set grid

set output "plots/pictures/average_best_worst.png"
plot "plots/files/average_best_worst.dat" using 1:2 title "Средний вариант" with linespoints, \
     "plots/files/average_best_worst.dat" using 1:3 title "Наилучший вариант" with linespoints, \
     "plots/files/average_best_worst.dat" using 1:4 title "Наихудший вариант" with linespoints
