
set xrange [0:1000]
set yrange [0:1000]
set zrange [0:1000]
set ticslevel 0
set grid

splot "trajectory.dat" u 1:2:3 with lines


pause -1 "pause"