
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
    
plot "experiments/exp2/out/trajectory1.dat" u 1:3 with lines lw 3 title "relative humidity: 0%", \
"experiments/exp2/out/trajectory2.dat" u 1:3 with lines lw 3 title "relative humidity: 10%", \
"experiments/exp2/out/trajectory3.dat" u 1:3 with lines lw 3 title "relative humidity: 20%", \
"experiments/exp2/out/trajectory4.dat" u 1:3 with lines lw 3 title "relative humidity: 30%", \
"experiments/exp2/out/trajectory5.dat" u 1:3 with lines lw 3 title "relative humidity: 40%", \
"experiments/exp2/out/trajectory6.dat" u 1:3 with lines lw 3 title "relative humidity: 50%", \
"experiments/exp2/out/trajectory7.dat" u 1:3 with lines lw 3 title "relative humidity: 60%", \
"experiments/exp2/out/trajectory8.dat" u 1:3 with lines lw 3 title "relative humidity: 70%", \
"experiments/exp2/out/trajectory9.dat" u 1:3 with lines lw 3 title "relative humidity: 80%", \
"experiments/exp2/out/trajectory10.dat" u 1:3 with lines lw 3 title "relative humidity: 90%", \
"experiments/exp2/out/trajectory11.dat" u 1:3 with lines lw 3 title "relative humidity: 100%
pause -1 "plot"