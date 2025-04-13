set terminal png size 900,900

set title "Распределение высот веток (N = 2^{18})"
set xlabel "Высота ветки"
set ylabel "Количество веток"
plot "plots/dat-files/avl_depths.dat" using 2:xtic(1) with boxes title "AVL", \
     "plots/dat-files/cartesianTree_depths.dat" using 2:xtic(1) with boxes title "Cartesian"
