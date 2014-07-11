import pylab as pl
import datetime
import numpy as np
data = """0.04 Switch_Tor
0.08 Switch_Aggr
0.053 Link_Trunk
0.095 Link_Core"""

values = []
dates = []

for line in data.split("\n"):
    x, y = line.split()
    values.append(float(x))
    dates.append(y)

fig = pl.figure()
ax = pl.subplot(111)
width=0.4
ax.bar(range(len(dates)), values, width=width)
ax.set_xticks(np.arange(len(dates)) + width/2)
ax.set_ylim(0,0.25)
ax.set_xticklabels(dates)
pl.ylabel("Ratio of devices experiencing > 1 loss")
pl.title("Failure prob in simualtions")
pl.show()
