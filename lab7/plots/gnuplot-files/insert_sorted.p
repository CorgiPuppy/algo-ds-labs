set terminal pngcairo size 900,900

set title "Расчётные кривые времени вставки в AVL, Декартово и Красно-чёрное деревья (сортированные данные)"
set xlabel "Размер массива (N)"
set ylabel "Время (t, мкс)"
set grid

set output "plots/pictures/insert_sorted.png"
plot "plots/dat-files/insert_sorted.dat" using 1:2 title "AVL" with linespoint, \
     "plots/dat-files/insert_sorted.dat" using 1:3 title "Cartesian" with linespoint, \
     "plots/dat-files/insert_sorted.dat" using 1:4 title "RB" with linespoint

