#!/usr/bin/python
import read_kinetisense
import phase_correlation
import read_correlations
import read_reference
import read_parameters
import preproc
import pylab as pl
import numpy as np


#data = "../../data/Phase_2/csv_format/Craig/Craig_Walking_tredmil.csv"
data = "../../data/Phase_2/csv_format/Craig/walk_jog_run_tredmil.csv"
kin_data = read_kinetisense.KIN( data )

#inputs = "../input_demo"
inputs = "../submit/input_craig_tredmil"
params = read_parameters.read_parameters( inputs )

#ref_file = "../output/ref_data17190"
ref_file = "../submit/output/ref_craig17190"
ref = read_reference.read_reference( ref_file )
ref.plot()

start_time = 1000.0
interval   = 4.0
dt         = params.dt

ax = kin_data.get_sensor_a( 2, 1, start_time, interval, dt)
ay = kin_data.get_sensor_a( 2, 2, start_time, interval, dt)
az = kin_data.get_sensor_a( 2, 3, start_time, interval, dt)

[axp, ayp, azp] = preproc.preproc( ax, ay, az )

correlation_primary = phase_correlation.phase_correlation( ref.primary, axp, 1)
print "primary correlation = %f"          % correlation.matched_corr
correlation.plot_match()
