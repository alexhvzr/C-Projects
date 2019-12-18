set terminal postscript portrait
set nolabel
set xlabel "n"
set xrange [8:3000]
set ylabel "modulus"
set yrange [0:30]
set output "euclid.ps"
plot log(2 * x / 3) / log( 1.5 ), "euclid.dat" title "empirical data" with linespoints