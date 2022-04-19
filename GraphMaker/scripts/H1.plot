set terminal png size 1280, 720
set xrange[0:200]
set output "./plots/H1.png"
set xlabel "List index"
set ylabel "Amount of collisions"
set title "Always 1 hash"
plot "./data/H1.txt" with lines
