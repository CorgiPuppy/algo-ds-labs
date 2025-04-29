set terminal pngcairo size 900,900

set title "Расчётные кривые времени удаления минимума в Бинарную кучу"
set xlabel "Размер кучи (N)"
set ylabel "Время (t, с)"
set grid
set logscale x 10
set logscale y 10

set output "plots/pictures/delete_average.png"
plot "plots/dat-files/delete_average.dat" using 1:2 title "BinaryAvg" with linespoints, \
     "plots/dat-files/delete_average.dat" using 1:3 title "BinomialAvg" with linespoints, \
     "plots/dat-files/delete_max.dat" using 1:2 title "BinaryMax" with linespoints, \
     "plots/dat-files/delete_max.dat" using 1:3 title "BinomialMax" with linespoints
