set terminal png size 1280, 720
set xrange[0:200]
set output "./plots/H2.png"
set xlabel "List index"
set ylabel "Amount of collisions"
set title "First ascii code" font "Helvetica Bold, 20"
set xtics 0, 10, 200
plot "./data/H2.txt" with lines
