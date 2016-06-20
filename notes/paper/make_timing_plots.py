#!/usr/bin/python
import numpy as np
import matplotlib.pyplot as plt

freq = np.array([25, 32, 50, 62, 64, 75, 100, 128], dtype=np.float)
freq2 = np.array([16, 32, 62, 64, 75, 100, 128], dtype=np.float)

time_dec_8 = np.array([1.039, 0.1591, 0.2516, 0.3534, 0.3132, 0.503, 0.4765, 0.6255])
time_4sec_dec_8_1ref = np.array([0.05605, 0.0947, 0.2023, 0.1781, 0.2748, 0.2807, 0.3551])
time_4sec_dec_8_2ref = np.array([0.0826, 0.1591, 0.3534, 0.3132, 0.503, 0.4765, 0.6255])

plt.figure(figsize=(12,9))
sec4_dec8_plot_1ref, = plt.plot(freq2, time_4sec_dec_8_1ref, lw=4, color='#000000', label="1 Reference")
sec4_dec8_plot_2ref, = plt.plot(freq2, time_4sec_dec_8_2ref, lw=4, color='#888888', label="2 References")
plt.title("Timing on MSP432 at Decimation 8", fontsize=26)
plt.xlabel("Sampling Frequency", fontsize=26)
plt.ylabel("Execution Time (seconds)", fontsize=26)
plt.yticks(fontsize=20)
plt.xticks(fontsize=20)
plt.legend(handles=[sec4_dec8_plot_1ref, sec4_dec8_plot_2ref], loc='upper left', prop={'size':26})
plt.savefig("one_and_two_references.png", bbox_inches="tight")
