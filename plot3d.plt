
set xrange [*:*]
set yrange [*:*]
set zrange [*:*]
set xlabel "x [m]"
set ylabel "z [m]"
set zlabel "y [m]"

set grid
set xyplane at 0

splot "trajectory.dat" u 1:2:3 with lines title "trajectory 1", \
    "trajectory1.dat" u 1:2:3 with lines


pause -1 "pause"