#!/usr/bin/python
import numpy as np
import matplotlib.pyplot as plt

walking = np.array([0.84794, 0.909459, 0.850478, 0.906831, 0.862499, 0.926355, 0.906276, 0.900198, 0.938393, 0.934762, 0.920486, 0.864496, 0.921065, 0.854258, 0.900292, 0.894288, 0.908544, 0.888207, 0.901154, 0.921692, 0.890178, 0.887596, 0.828443, 0.904484, 0.849955, 0.916847, 0.899168, 0.91797, 0.932738, 0.936772, 0.95634, 0.906997, 0.931281, 0.875598, 0.920153, 0.838532, 0.904328, 0.904448, 0.918744, 0.946283, 0.921908, 0.930042, 0.86388, 0.923708, 0.885149, 0.918485, 0.896543, 0.917104, 0.935319, 0.906593, 0.914294, 0.906969, 0.929369, 0.858822, 0.894336, 0.824241, 0.904161, 0.830148, 0.874468, 0.785672, 0.899271, 0.940611, 0.907252, 0.913564, 0.877749, 0.929613, 0.912499, 0.925567, 0.866579, 0.929623, 0.93787, 0.939557, 0.955559, 0.925966, 0.933549, 0.843215, 0.914925, 0.858983, 0.899164, 0.866985, 0.90986, 0.92087, 0.896269, 0.93171, 0.909918, 0.929025, 0.888036, 0.940737, 0.894057, 0.931365, 0.934599, 0.928244, 0.92282, 0.921015, 0.951321, 0.913612, 0.904481, 0.839105, 0.896004, 0.8588, 0.896319, 0.854178, 0.885876, 0.900081, 0.91569, 0.935342, 0.922368, 0.929162, 0.895921, 0.926157, 0.867629, 0.893603, 0.878906, 0.917411, 0.91562, 0.94121, 0.944205, 0.919567, 0.943681, 0.911371, 0.947294, 0.956737, 0.956125, 0.958828, 0.947283, 0.966719, 0.924671, 0.940748, 0.889098, 0.927789, 0.875759, 0.905913, 0.896647, 0.907511, 0.933524, 0.920492, 0.923788, 0.893768, 0.913336, 0.865062, 0.913386, 0.883637, 0.903123, 0.866881, 0.903453, 0.920731, 0.88505, 0.939967, 0.901619, 0.934523, 0.889663, 0.926323, 0.901285, 0.908031, 0.909289, 0.923446, 0.934659, 0.934598, 0.949645, 0.908067, 0.910707, 0.869039, 0.927072, 0.905367, 0.925551, 0.912338, 0.905817, 0.936264, 0.880576, 0.92859, 0.843708, 0.879873, 0.826994, 0.905264, 0.911376, 0.917238, 0.933009, 0.898513, 0.937063, 0.892177, 0.946836, 0.91991, 0.924891, 0.933932, 0.934353, 0.921666, 0.839023, 0.904294, 0.859086, 0.896721, 0.86768, 0.893096, 0.890697, 0.921343, 0.930745, 0.936265, 0.939215, 0.918313, 0.946375, 0.919351, 0.935114, 0.923725, 0.934041, 0.941688, 0.939578, 0.956527, 0.940947, 0.933056, 0.898514, 0.945094, 0.88771, 0.904917, 0.907533, 0.92786, 0.946098, 0.948585, 0.962405, 0.929531, 0.933455, 0.923765, 0.941599, 0.919069, 0.940204, 0.947485, 0.948427, 0.952853, 0.942196, 0.957732, 0.899363, 0.925428, 0.884403, 0.924885, 0.90273, 0.916171, 0.927368, 0.930656, 0.916308, 0.890598, 0.934537, 0.887396, 0.936231, 0.929023, 0.938279, 0.946846, 0.943457, 0.96996, 0.922866, 0.956731, 0.859757, 0.907367, 0.899173, 0.91909, 0.928146, 0.909033, 0.922153, 0.885011, 0.929819, 0.880473, 0.90415, 0.85526, 0.904488, 0.925886, 0.928248, 0.926717, 0.914716, 0.932041, 0.879482, 0.898241, 0.857904, 0.895399, 0.856461, 0.888349, 0.893585, 0.903402, 0.914296, 0.915198, 0.93667, 0.91319, 0.95032, 0.932409, 0.94468, 0.965393, 0.957563, 0.941803, 0.903273, 0.947113, 0.88779, 0.923759, 0.855948, 0.905863, 0.895192, 0.885045, 0.858525, 0.820775, 0.891636])

bicycling = np.array([0.679957, 0.789553, 0.59833, 0.596523, 0.614208, 0.597885, 0.611067, 0.602449, 0.631358, 0.622246, 0.61906, 0.633203, 0.558703, 0.565262, 0.592875, 0.533539, 0.567892, 0.590143, 0.533268, 0.556519, 0.515119, 0.540003, 0.579331, 0.578046, 0.556635, 0.571309, 0.557782, 0.565491, 0.55051, 0.568431, 0.556721, 0.579116, 0.603548, 0.587114, 0.648269, 0.645923, 0.641181, 0.651412, 0.629645, 0.594212, 0.581043, 0.588942, 0.589138, 0.572044, 0.528211, 0.54954, 0.585035, 0.55719, 0.572674, 0.574303, 0.653028, 0.662722, 0.647057, 0.6625, 0.64982, 0.662843, 0.565419, 0.569121, 0.54736, 0.541831, 0.563579, 0.53599, 0.570882, 0.554404, 0.549786, 0.546767, 0.537629, 0.509273, 0.509847, 0.534305, 0.516802, 0.523082, 0.534963, 0.526998, 0.546168, 0.538982, 0.543922, 0.515585, 0.478135, 0.433043, 0.597748, 0.525056, 0.555545, 0.53883, 0.531164, 0.527243])

threshold = np.linspace(0, 1, 1000)
walking_prob = np.zeros(len(threshold), dtype='float64')
for k in range(len(walking_prob)):
   walking_prob[k] = sum(walking > threshold[k])

walking_prob /= len(walking)

bicycling_prob = np.zeros(len(threshold), dtype='float64')
for k in range(len(bicycling_prob)):
   bicycling_prob[k] = sum(bicycling > threshold[k])

bicycling_prob /= len(bicycling)

plt.figure(figsize=(12,9))
walking_plot,   = plt.plot(threshold, walking_prob,   lw=4, color='#000000', linestyle='-', label="Walking data")
bicycling_plot, = plt.plot(threshold, bicycling_prob, lw=4, color='#000000', linestyle='--', label="Bicycling data")
plt.title("Correlations with Walking", fontsize=40)
plt.ylabel("Fraction Exceeding Threshold", fontsize=40)
plt.xlabel("Correlation Threshold", fontsize=40)
plt.yticks(fontsize=40)
plt.xticks(fontsize=40)
plt.grid(True)
plt.legend(handles=[walking_plot, bicycling_plot], loc='lower left', prop={'size':34})
plt.savefig("fraction_threshold_walking_to_bicycling.png", bbox_inches="tight")

plt.figure(figsize=(12, 9))
plt.ylim(0,1)
plt.title("ROC Curve (Walking vs. Bicycling)", fontsize=40)
plt.ylabel("Walking Classified as Walking", fontsize=40)
plt.xlabel("Bicycling Classified as Walking", fontsize=40)
plt.yticks(np.linspace(0, 1, 6), fontsize=40)
plt.xticks(np.linspace(0, 1, 6), fontsize=40)
plt.grid(True)
plt.plot(bicycling_prob, walking_prob, lw=8, color='#000000')
plt.savefig("ROC_walk_to_bike.png", bbox_inches="tight")
