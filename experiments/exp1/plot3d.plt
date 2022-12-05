
    set xrange [*:*]
    set yrange [*:*]
    set zrange [*:*]
    set ticslevel 0
    set grid
    
splot "experiments/exp1/out/trajectory4.dat" u 1:2:3 with lines, \
"experiments/exp1/out/trajectory8.dat" u 1:2:3 with lines, \
"experiments/exp1/out/trajectory6.dat" u 1:2:3 with lines, \
"experiments/exp1/out/trajectory1.dat" u 1:2:3 with lines, \
"experiments/exp1/out/trajectory7.dat" u 1:2:3 with lines, \
"experiments/exp1/out/trajectory2.dat" u 1:2:3 with lines, \
"experiments/exp1/out/trajectory5.dat" u 1:2:3 with lines, \
"experiments/exp1/out/trajectory3.dat" u 1:2:3 with lines
pause -1 "plot"