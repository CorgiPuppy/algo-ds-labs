set terminal pngcairo size 1000,1000

set title "Расчётная кривая процентного соотношения вызовов внутренней функции к общему вызову функции"
set xlabel "Размер массива (M)" 
set ylabel "Соотношение (%)"
set grid

set output "plots/pictures/inner_heap_ratio.png"
plot "plots/files/inner_heap_ratio.dat" using 1:2 title "Процент внутренних вызовов" with linespoints
