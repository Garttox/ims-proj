from os import listdir
from os.path import isfile, join

files = [f for f in listdir("data") if isfile(join("data", f))]

outGnuplot = """
set xrange [-500:400]
set yrange [-400:500]
set zrange [-500:200]
set ticslevel 0
set grid
"""

for i, file in enumerate(files):
    if i == 0:
        outGnuplot += "\nsplot "+file+" u 1:2:3 with lines"
    else:
        outGnuplot += ", \\\n"+file+" u 1:2:3 with lines"

outGnuplot += "\npause -1 \"plot\""
print(outGnuplot)

