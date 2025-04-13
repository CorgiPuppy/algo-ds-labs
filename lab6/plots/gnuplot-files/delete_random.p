set terminal pngcairo size 900,900

set title "Расчётные кривые времени удаления в BST и AVL деревьях (рандомные данные)"
set xlabel "Размер массива (N)"
set ylabel "Время (t, мкс)"
set grid

set output "plots/pictures/delete_random.png"
plot "plots/dat-files/delete_random.dat" using 1:2 title "BST" with linespoint, \
     "plots/dat-files/delete_random.dat" using 1:3 title "AVL" with linespoint

