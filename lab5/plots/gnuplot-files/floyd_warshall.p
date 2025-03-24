set terminal pngcairo size 900,900

set title "Расчётные кривые метода Флойда-Варшалла"
set xlabel "Количество вершин (N)"
set ylabel "Время выполнения (сек)"
set grid

set output "plots/pictures/floyd_warshall.png"
plot "plots/dat-files/floyd_warshall.dat" using 1:2 with linespoints
