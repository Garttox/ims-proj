
    set xrange [*:*]
    set yrange [*:*]
    set xlabel "Uražená vzdálenost [m]" font ", 25" offset 0,-2
    set ylabel "Nadmořská výška [m]" font ", 25" offset -5,0
    set grid
    set tics font ", 16"
    set key font ", 20"
    set lmargin at screen 0.06
    set rmargin at screen 0.94
    set tmargin at screen 0.9
    set bmargin at screen 0.1
    
plot "experiments/exp1/out/trajectory1.dat" u 1:3 with lines lw 3 title "humidity: 0 temperature: -16", \
"experiments/exp1/out/trajectory2.dat" u 1:3 with lines lw 3 title "humidity: 0 temperature: -7", \
"experiments/exp1/out/trajectory3.dat" u 1:3 with lines lw 3 title "humidity: 0 temperature: 3", \
"experiments/exp1/out/trajectory4.dat" u 1:3 with lines lw 3 title "humidity: 0 temperature: 5", \
"experiments/exp1/out/trajectory5.dat" u 1:3 with lines lw 3 title "humidity: 0 temperature: 12", \
"experiments/exp1/out/trajectory6.dat" u 1:3 with lines lw 3 title "humidity: 0 temperature: 24", \
"experiments/exp1/out/trajectory7.dat" u 1:3 with lines lw 3 title "humidity: 0 temperature: 30", \
"experiments/exp1/out/trajectory8.dat" u 1:3 with lines lw 3 title "humidity: 0 temperature: 36"
pause -1 "plot"