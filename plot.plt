set xrange [*:*]
set yrange [*:*]
set xlabel "x [m]"
set ylabel "y [m]"

set ticslevel 0
set grid

plot "trajectory.dat" u 1:3 with lines

pause -1 "pause"