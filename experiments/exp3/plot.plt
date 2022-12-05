
    set xrange [*:*]
    set yrange [*:*]
    set xlabel "Uražená vzdálenost [m]" font ", 25" offset 0,-2
    set ylabel "Nadmořská výška [m]" font ", 25" offset -5,0
    set ticslevel 0
    set grid
    set tics font ", 16"
    set key font ", 20"
    set lmargin at screen 0.06
    set rmargin at screen 0.94
    set tmargin at screen 0.9
    set bmargin at screen 0.1
    
plot "experiments/exp3/out/trajectory1.dat" u 1:3 with lines lw 3 title "humidity: 0 temperature: -22", \
"experiments/exp3/out/trajectory2.dat" u 1:3 with lines lw 3 title "humidity: 0 temperature: -9", \
"experiments/exp3/out/trajectory3.dat" u 1:3 with lines lw 3 title "humidity: 0 temperature: -5", \
"experiments/exp3/out/trajectory4.dat" u 1:3 with lines lw 3 title "humidity: 90 temperature: 4", \
"experiments/exp3/out/trajectory5.dat" u 1:3 with lines lw 3 title "humidity: 80 temperature: 11", \
"experiments/exp3/out/trajectory6.dat" u 1:3 with lines lw 3 title "humidity: 70 temperature: 22", \
"experiments/exp3/out/trajectory7.dat" u 1:3 with lines lw 3 title "humidity: 40 temperature: 23", \
"experiments/exp3/out/trajectory8.dat" u 1:3 with lines lw 3 title "humidity: 10 temperature: 31", \
"experiments/exp3/out/trajectory9.dat" u 1:3 with lines lw 3 title "humidity: 20 temperature: 40"
pause -1 "plot"