set terminal pngcairo size 900,900

set title "Расчётные кривые среднего по серии количества вызовов функции построения кучи и количества вызовов внутренней функции"
set xlabel "Размер массива (M)" 
set ylabel "Количество вызовов"
set grid

set output "plots/pictures/heap_calls.png"
plot "plots/files/heap_calls.dat" using 1:2 title "Среднее количество вызовов кучи" with linespoints, \
     "plots/files/heap_calls.dat" using 1:3 title "Среднее количество внутренних вызовов" with linespoints
