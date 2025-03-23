set terminal pngcairo size 900,900

set title "Расчётные кривые методом обхода в ширину и обхода в глубину"
set xlabel "Количество вершин (m)"
set ylabel "Время исполнения (сек)"
set grid

set output "plots/pictures/bfs_dfs.png"
plot "plots/dat-files/bfs_dfs.dat" using 1:2 title "BFS" with linespoints, \
     "plots/dat-files/bfs_dfs.dat" using 1:3 title "DFS" with linespoints
