set terminal pngcairo size 900,900

set title "Расчётные кривые времени вставки в BST и AVL деревья (рандомные значения)"
set xlabel "Размер массива (N)"
set ylabel "Время (t, мкс)"
set grid

set output "plots/pictures/insert_random.png"
plot "plots/dat-files/insert_random.dat" using 1:2 title "BST" with linespoint, \
     "plots/dat-files/insert_random.dat" using 1:3 title "AVL" with linespoint

