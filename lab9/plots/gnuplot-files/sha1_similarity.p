set terminal png size 900,900

set title "Гистограмма количество отличий - максимальная длина одинаковой последовательности"
set xlabel "Количество отличий"
set ylabel "Максимальная длина одинаковой последовательности"
set style data histogram
set style fill solid
set boxwidth 0.9
set yrange [0:40]

set output "plots/pictures/sha1_similarity.png"
plot "plots/dat-files/sha1_similarity.dat" using 2:xtic(1) title "SHA-1"
