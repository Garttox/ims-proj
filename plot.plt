set xrange [*:*]
set yrange [*:*]
set xlabel "Vzdálenost [m]"
set ylabel "Nadmořská výška [m]"

set ticslevel 0
set grid

plot "trajectory.dat" u 1:3 with lines title "trajectory"

pause -1 "pause"