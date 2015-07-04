#!/usr/bin/python
import read_kinetisense
import phase_correlation
import read_correlations
import read_reference
import read_parameters
import cross_corr
import preproc
import pylab as pl
import numpy as np


#data = "../../data/Phase_2/csv_format/Craig/walk_jog_run_tredmil.csv"
#kin_data = read_kinetisense.KIN( data )

#inputs = "../submit/input_craig_tredmil"
#params = read_parameters.read_parameters( inputs )

#ref_file = "../submit/output/ref_craig17190"
#ref_file = "../submit/output/ref_craig12020"
#ref_file = "/home/euler/projects/sensor/code/submit/output/ref_craig17190"
#ref = read_reference.read_reference( ref_file )
#ref.plot()

#start_time = 1000.0
#interval   = 4.0
#dt         = params.dt

#ax = kin_data.get_sensor_a( 2, 1, start_time, interval, dt)
#ay = kin_data.get_sensor_a( 2, 2, start_time, interval, dt)
#az = kin_data.get_sensor_a( 2, 3, start_time, interval, dt)

#[axp, ayp, azp] = preproc.preproc( ax, ay, az )

#correlation_primary = phase_correlation.phase_correlation( ref.primary, axp, 1)
#print "Primary correlation = %f"          % correlation_primary.matched_corr
#correlation_primary.plot_match()

#correlation_secondary = phase_correlation.phase_correlation( ref.secondary, ayp, 1)
#print "Secondary correlation = %f"          % correlation_secondary.matched_corr

#combined_corr = cross_corr.cross_corr()
#combined_corr.phase_corrs.append( correlation_primary )
#combined_corr.phase_corrs.append( correlation_secondary )

#combined_corr.combined_matched_corr()

###

correlations = []
#correlation_file = "../output/correlations_demo17190"
correlation_file = "../submit/output/correlations_craig_tredmil17190"
correlations.append( read_correlations.read_correlations( correlation_file ) )
#correlation_file = "../output/old/correlations_demo17190"
correlation_file = "../submit/output/correlations_craig_tredmil12020"
correlations.append( read_correlations.read_correlations( correlation_file ) )
correlations[0].print_stats()
correlations[0].plot()
correlations[1].print_stats()
correlations[1].plot()
