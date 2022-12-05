
set xrange [*:*]
set yrange [*:*]
set zrange [*:*]
set xlabel "Vzdálenost [m]"
set ylabel ""
set zlabel "Nadmořská výška [m]"

set grid
set xyplane at 0

splot "trajectory.dat" u 1:2:3 with lines title "trajectory"


pause -1 "pause"