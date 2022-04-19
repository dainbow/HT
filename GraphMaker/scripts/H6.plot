set terminal png size 1280, 720
set xrange[0:2003]
set output "./plots/H6.png"
set xlabel "List index"
set ylabel "Amount of collisions"
set title "Crc32 hash" font "Helvetica Bold, 20"
set xtics 0, 100, 2003
plot "./data/H6.txt" with lines
