set terminal pngcairo size 900,900

set title "Максимальная высота деревьев"
set xlabel "Размер массива (N)"
set ylabel "Высота"
set grid
set logscale x

set output "plots/pictures/max_height.png"
plot "plots/dat-files/max_height_random.dat" using 1:2 title "AVL Random" with lines, \
     "plots/dat-files/max_height_random.dat" using 1:3 title "Cartesian Random" with lines, \
     "plots/dat-files/max_height_random.dat" using 1:4 title "RB Random" with lines, \
     "plots/dat-files/max_height_sorted.dat" using 1:2 title "AVL Sorted" with lines, \
     "plots/dat-files/max_height_sorted.dat" using 1:3 title "Cartesian Sorted" with lines, \
     "plots/dat-files/max_height_sorted.dat" using 1:4 title "RB Sorted" with lines
