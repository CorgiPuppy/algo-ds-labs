set terminal pngcairo size 900,900

set title "Расчётные кривые времени поиска по AVL и Декартово деревьям (рандомные данные)"
set xlabel "Размер массива (N)"
set ylabel "Время (t, мкс)"
set grid

set output "plots/pictures/search_random.png"
plot "plots/dat-files/search_random.dat" using 1:2 title "AVL" with linespoint, \
     "plots/dat-files/search_random.dat" using 1:3 title "Cartesian" with linespoint
