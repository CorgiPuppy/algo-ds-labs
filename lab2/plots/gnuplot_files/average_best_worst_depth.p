set terminal pngcairo size 900,900

set title "Расчётные кривые средней, наилучшей и наихудшей глубины рекурсии"
set xlabel "Размер массива (M)" 
set ylabel "Глубина рекурсии (N)"
set grid

set output "plots/pictures/average_best_worst_recursion.png"
plot "plots/files/recursion_depth.dat" using 1:2 title "Средний вариант" with linespoints, \
     "plots/files/recursion_depth.dat" using 1:3 title "Наилучший вариант" with linespoints, \
     "plots/files/recursion_depth.dat" using 1:4 title "Наихудший вариант" with linespoints
