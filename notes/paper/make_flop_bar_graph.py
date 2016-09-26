#!/usr/bin/python
import numpy as np
import matplotlib.pyplot as plt


flops = ( 3.45, 3.42, 10.22, 5.43, 8.52, 2.98, 25.56, 3.42, 25.56, 0.71, 10.71)
names = ("Demeaning", "Signal Power", "Covariance matrix", "Eigen vectors/values", "Orient axis", "Signal norm", "Signal to frequency", "Conjugate multiply", "Frequency to correlation", "Find max correlation", "Normalize the correlation")

fig, ax = plt.subplots()
index = np.arange(len(flops))
width = 0.5
opacity = 1.0
ax.set_xticks(index + width/2.0)
rects1 = plt.bar(index, flops, width, alpha=opacity, color='#000000')
plt.xlabel('')
plt.ylabel("Measured Flops (% of Processing)", fontsize=16)
plt.title("Processing Distribution", fontsize=26)
plt.xticks(index + width/2.0, names, rotation=90, fontsize=14)
plt.tight_layout()
plt.savefig("flops_graph.png", bbox_inches="tight")
