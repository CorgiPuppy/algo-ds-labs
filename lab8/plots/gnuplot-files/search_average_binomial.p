set terminal pngcairo size 900,900

set title "Расчётные кривые времени поиска минимума в биномиальнойкуче"
set xlabel "Размер кучи (N)"
set ylabel "Время (t, с)"
set grid

set output "plots/pictures/search_average_binomial.png"
plot "plots/dat-files/search_average.dat" using 1:3 title "Binomial" with linespoint
