set terminal pngcairo size 900,900

set title "Расчётные кривые времени поиска минимума в Бинарной кучи"
set xlabel "Размер кучи (N)"
set ylabel "Время (t, с)"
set grid
set logscale x 10
set logscale y 10

set output "plots/pictures/search_average.png"
plot "plots/dat-files/search_average.dat" using 1:2 title "BinaryAvg" with linespoint, \
     "plots/dat-files/search_average.dat" using 1:3 title "BinomialAvg" with linespoint, \
     "plots/dat-files/search_max.dat" using 1:2 title "BinaryMax" with linespoint, \
     "plots/dat-files/search_max.dat" using 1:3 title "BinomialMax" with linespoint
