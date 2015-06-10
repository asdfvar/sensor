#!/usr/bin/python
import read_kinetisense
import phase_correlation
import read_correlations
import read_reference

walking = "/home/euler/projects/sensor/data/Phase_2/csv_format/Craig/Craig_Walking_tredmil.csv"

#kin_data = read_kinetisense.KIN( walking )

#kin_data.plot_sensor_1_ax()

ref_demo = "/home/euler/projects/sensor/code/output/ref_data17190"

ref = read_reference.read_reference( ref_demo )

ref.plot()
