set terminal png size 1280, 720
set xrange[0:2003]
set output "./plots/H3.png"
set xlabel "List index"
set ylabel "Amount of collisions"
set title "Ascii sum" font "Helvetica Bold, 20"
set xtics 0, 100, 2003
plot "./data/H3.txt" with lines
