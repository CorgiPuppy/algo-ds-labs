set terminal pngcairo size 1200,900 enhanced font "Helvetica,12"

set title "Распределение высот веток (N = 2^{18})"
set xlabel "Глубина"
set ylabel "Количество веток"
set style data histogram
set style fill solid border -1
set boxwidth 0.8 relative
set key top right

# Для автоматического масштабирования
set auto x
set yrange [0:*]

set output "plots/pictures/depths_distribution.png"

plot "plots/dat-files/depths_avl_random_hist.dat" using 2:xtic(1) title "AVL Random", \
     "plots/dat-files/depths_cartesian_random_hist.dat" using 2:xtic(1) title "Cartesian Random", \
     "plots/dat-files/depths_rb_random_hist.dat" using 2:xtic(1) title "RB Random", \
     "plots/dat-files/depths_avl_sorted_hist.dat" using 2:xtic(1) title "AVL Sorted", \
     "plots/dat-files/depths_cartesian_sorted_hist.dat" using 2:xtic(1) title "Cartesian Sorted", \
     "plots/dat-files/depths_rb_sorted_hist.dat" using 2:xtic(1) title "RB Sorted"

set output
