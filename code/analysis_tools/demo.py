#!/usr/bin/python
import read_kinetisense
import phase_correlation
import read_correlations
import read_reference
import read_parameters
import preproc
import pylab as pl


walking = "../../data/Phase_2/csv_format/Craig/Craig_Walking_tredmil.csv"
kin_data = read_kinetisense.KIN( walking )

inputs = "../input_demo"
params = read_parameters.read_parameters( inputs )

ref_demo = "../output/ref_data17190"
ref = read_reference.read_reference( ref_demo )
#ref.plot()

start_time = 400.0
interval   = 4.0
dt         = params.dt

ax = kin_data.get_sensor_a( 2, 1, start_time, interval, dt)
ay = kin_data.get_sensor_a( 2, 2, start_time, interval, dt)
az = kin_data.get_sensor_a( 2, 3, start_time, interval, dt)

[axp, ayp, azp] = preproc.preproc( ax, ay, az )

#pl.plot(axp, 'r')
#pl.plot(ayp, 'g')
#pl.plot(azp, 'b')
#pl.show()

correlation = phase_correlation.phase_correlation( ref.primary, axp )

#pl.plot( ref.primary, 'r' )
#pl.plot( axp )
#pl.show()

pl.plot( correlation )
pl.show()
