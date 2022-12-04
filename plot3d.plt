
set xrange [0:1000]
set yrange [0:1000]
set zrange [0:1000]
set xlabel "[m]"
set ylabel "[m]"
set zlabel "[m]"

set grid
set xyplane at 0

splot "trajectory.dat" u 1:2:3 with lines title "trajectory 1", \
    "trajectory1.dat" u 1:2:3 with lines


pause -1 "pause"