set terminal png size 900,900

set title "Распределение максимальной высоты (N = 2^{18})"
set xlabel "Максимальная высота"
set ylabel "Частота"
set style data histogram
set style fill solid
set boxwidth 0.9

set output "plots/pictures/max_height_distribution.png"
plot "plots/dat-files/max_height_avl_random.dat" using 2:xtic(1) title "AVL Random", \
     "plots/dat-files/max_height_cartesian_random.dat" using 2:xtic(1) title "Cartesian Random", \
     "plots/dat-files/max_height_rb_random.dat" using 2:xtic(1) title "RB Random"
