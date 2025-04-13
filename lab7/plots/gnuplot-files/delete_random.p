set terminal pngcairo size 900,900

set title "Расчётные кривые времени удаления в AVL, Декартово и Красно-чёрное деревьях (рандомные данные)"
set xlabel "Размер массива (N)"
set ylabel "Время (t, мкс)"
set grid

set output "plots/pictures/delete_random.png"
plot "plots/dat-files/delete_random.dat" using 1:2 title "AVL" with linespoint, \
     "plots/dat-files/delete_random.dat" using 1:3 title "Cartesian" with linespoint, \
     "plots/dat-files/delete_random.dat" using 1:4 title "RB" with linespoint

