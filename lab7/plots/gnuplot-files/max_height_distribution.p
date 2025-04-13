set terminal png size 900,900

set title "Распределение максимальной высоты (N = 2^{18})"
set xlabel "Максимальная высота"
set ylabel "Частота"
set style data histogram
set style fill solid
set boxwidth 0.9

set output "plots/max_height_distribution.png"
plot "plots/dat-files/max_heights.dat" using 1 with boxes title "AVL vs Декартово"
