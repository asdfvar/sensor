#!/usr/bin/python
import numpy as np
import matplotlib.pyplot as plt


flops = ( 3.02, 3.00, 8.95, 4.76, 7.46, 2.61, 22.38, 3.00, 22.38, 22.45)
names = ("Data demeaning", "Signal power", "Covariance Matrix", "Eigen-vectors/values", "Projection onto axis", "Signal norm", "FFT", "Conjugate multiply", "Inverse FFT", "Normalization & add. proc.")

fig, ax = plt.subplots()
index = np.arange(len(flops))
width = 0.5
opacity = 1.0
ax.set_xticks(index + width/2.0)
rects1 = plt.bar(index, flops, width, alpha=opacity, color='#000000')
plt.title("Computational Cost Estimate", fontsize=26)
plt.xlabel('')
plt.ylabel("Flops (% of Processing)", fontsize=16)
plt.yticks(np.linspace(0, 25, 6), fontsize=16)
plt.xticks(index + width/2.0, names, rotation=90, fontsize=16)
plt.tight_layout()
plt.savefig("flops_graph.png", bbox_inches="tight")
