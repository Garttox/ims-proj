set xrange [*:*]
set yrange [*:*]
set xlabel "Vzdálenost [m]" font ", 25" offset 0,-2
set ylabel "Teplota [°C]" font ", 25" offset -5,0
set tics font ", 16"
set key font ", 20"
set lmargin at screen 0.06
set rmargin at screen 0.94
set tmargin at screen 0.9
set bmargin at screen 0.1

set ticslevel 0
set grid

plot "temps.dat" u 1:2 with lines lw 3 title "závislost uražené vzdálenosti na teplotě"

pause -1 "pause"