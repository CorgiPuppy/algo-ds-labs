set terminal pngcairo size 900,900

set title ""
set xlabel "N" 
set ylabel "t, mks"
set grid

set output "plots/pictures/worst_and_complexity.png"
plot "plots/files/worst_and_complexity.dat" using 1:2 title "f" with linespoints, \
	 "plots/files/worst_and_complexity.dat" using 1:3 title "O(N^2)" with linespoints
