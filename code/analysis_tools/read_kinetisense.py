#!/usr/bin/python

import csv
import numpy as np
import pylab as pl

class KIN:

   def __init__(self, path):

      fid = open(path, 'r')
      reader = csv.reader(fid)
      row_count = sum(1 for row in reader)
      fid.close()

      samp_freq  = 128.0
      dt         = 1.0 / samp_freq
      N          = row_count - 1
      total_time = N / samp_freq

      print "%f total seconds of data" % total_time

      self.sensor_1_ax = np.zeros(row_count-1, dtype = float)
      self.sensor_1_ay = np.zeros(row_count-1, dtype = float)
      self.sensor_1_az = np.zeros(row_count-1, dtype = float)
      self.sensor_1_wx = np.zeros(row_count-1, dtype = float)
      self.sensor_1_wy = np.zeros(row_count-1, dtype = float)
      self.sensor_1_wz = np.zeros(row_count-1, dtype = float)
      self.sensor_2_ax = np.zeros(row_count-1, dtype = float)
      self.sensor_2_ay = np.zeros(row_count-1, dtype = float)
      self.sensor_2_az = np.zeros(row_count-1, dtype = float)
      self.sensor_2_wx = np.zeros(row_count-1, dtype = float)
      self.sensor_2_wy = np.zeros(row_count-1, dtype = float)
      self.sensor_2_wz = np.zeros(row_count-1, dtype = float)
      self.sensor_3_ax = np.zeros(row_count-1, dtype = float)
      self.sensor_3_ay = np.zeros(row_count-1, dtype = float)
      self.sensor_3_az = np.zeros(row_count-1, dtype = float)
      self.sensor_3_wx = np.zeros(row_count-1, dtype = float)
      self.sensor_3_wy = np.zeros(row_count-1, dtype = float)
      self.sensor_3_wz = np.zeros(row_count-1, dtype = float)
      self.EMG_1       = np.zeros(row_count-1, dtype = float)
      self.EMG_2       = np.zeros(row_count-1, dtype = float)
      self.Event       = np.zeros(row_count-1, dtype = float)

      with open(path,'r') as fid:
         reader = csv.reader(fid)
         header = reader.next()

         for p, row in enumerate(reader):
            for k, data in enumerate(row):
               if header[k] == "Sensor 1 ax":
                  self.sensor_1_ax[p] = float(data)
               elif header[k] == " Sensor 1 ay":
                  self.sensor_1_ay[p] = float(data)
               elif header[k] == " Sensor 1 az":
                  self.sensor_1_az[p] = float(data)
               elif header[k] == " Sensor 1 wx":
                  self.sensor_1_wx[p] = float(data)
               elif header[k] == " Sensor 1 wy":
                  self.sensor_1_wy[p] = float(data)
               elif header[k] == " Sensor 1 wz":
                  self.sensor_1_wz[p] = float(data)
               elif header[k] == " Sensor 2 ax":
                  self.sensor_2_ax[p] = float(data)
               elif header[k] == " Sensor 2 ay":
                  self.sensor_2_ay[p] = float(data)
               elif header[k] == " Sensor 2 az":
                  self.sensor_2_az[p] = float(data)
               elif header[k] == " Sensor 2 wx":
                  self.sensor_2_wx[p] = float(data)
               elif header[k] == " Sensor 2 wy":
                  self.sensor_2_wy[p] = float(data)
               elif header[k] == " Sensor 2 wz":
                  self.sensor_2_wz[p] = float(data)
               elif header[k] == " Sensor 3 ax":
                  self.sensor_3_ax[p] = float(data)
               elif header[k] == " Sensor 3 ay":
                  self.sensor_3_ay[p] = float(data)
               elif header[k] == " Sensor 3 az":
                  self.sensor_3_az[p] = float(data)
               elif header[k] == " Sensor 3 wx":
                  self.sensor_3_wx[p] = float(data)
               elif header[k] == " Sensor 3 wy":
                  self.sensor_3_wy[p] = float(data)
               elif header[k] == " Sensor 3 wz":
                  self.sensor_3_wz[p] = float(data)
               elif header[k] == " EMG 1":
                  self.EMG_1[p] = float(data)
               elif header[k] == " EMG 2":
                  self.EMG_2[p] = float(data)
               elif header[k] == " Event":
                  self.Event[p] = float(data)

   def get_sensor_a(self,
                    sensor_num,
                    sensor_dir,
                    start_time,
                    interval,
                    dt):

      start_index = int(start_time / dt)
      end_index   = int(start_index + interval / dt)

      if sensor_num == 1:
         if sensor_dir == 1:
            return self.sensor_1_ax[start_index: end_index]
         if sensor_dir == 2:
            return self.sensor_1_ay[start_index: end_index]
         if sensor_dir == 3:
            return self.sensor_1_az[start_index: end_index]
      elif sensor_num == 2:
         if sensor_dir == 1:
            return self.sensor_2_ax[start_index: end_index]
         if sensor_dir == 2:
            return self.sensor_2_ay[start_index: end_index]
         if sensor_dir == 3:
            return self.sensor_2_az[start_index: end_index]
      elif sensor_num == 3:
         if sensor_dir == 1:
            return self.sensor_3_ax[start_index: end_index]
         if sensor_dir == 2:
            return self.sensor_3_ay[start_index: end_index]
         if sensor_dir == 3:
            return self.sensor_3_az[start_index: end_index]

   def auto_correlate(self, sensor, direction, start, end, dt):
      if   (sensor == 1 and direction == 1):
         u = self.sensor_1_ax
      elif (sensor == 1 and direction == 2):
         u = self.sensor_1_ay
      elif (sensor == 1 and direction == 3):
         u = self.sensor_1_az
      elif (sensor == 2 and direction == 1):
         u = self.sensor_2_ax
      elif (sensor == 2 and direction == 2):
         u = self.sensor_2_ay
      elif (sensor == 2 and direction == 3):
         u = self.sensor_2_az
      elif (sensor == 3 and direction == 1):
         u = self.sensor_3_ax
      elif (sensor == 3 and direction == 2):
         u = self.sensor_3_ay
      elif (sensor == 3 and direction == 3):
         u = self.sensor_3_az
      else:
         u = np.zeros(1)

      start_index = int(start / dt)
      end_index   = int(end   / dt)

      u = u[start_index : end_index]

      correlation = np.correlate( u, u, 'same')

      N = len(u)

      norm_1 = np.zeros( N )
      norm_2 = np.zeros( N )

      for k in range(N/2):
         norm_1[k] = sum(u[0 : N/2+1 + k]**2)
         norm_2[k] = sum(u[N/2 - k : ]**2)

      if N % 2 != 0: norm_1[N/2] = sum(u**2)
      if N % 2 != 0: norm_2[N/2] = sum(u**2)

      if N % 2 != 0:
         for k in range(N/2):
            norm_1[k + N/2 + 1] = norm_2[N/2 - k - 1]
            norm_2[k + N/2 + 1] = norm_1[N/2 - k - 1]
      else:
         for k in range(N/2):
            norm_1[k + N/2] = norm_2[N/2 - k - 1]
            norm_2[k + N/2] = norm_1[N/2 - k - 1]

      norm = np.sqrt( norm_1 * norm_2 )

      return correlation / norm
