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

      self.sensor_1_ax = np.zeros(row_count-1, dtype = float)
      self.sensor_1_ay = np.zeros(row_count-1)
      self.sensor_1_az = np.zeros(row_count-1)
      self.sensor_1_wx = np.zeros(row_count-1)
      self.sensor_1_wy = np.zeros(row_count-1)
      self.sensor_1_wz = np.zeros(row_count-1)
      self.sensor_2_ax = np.zeros(row_count-1)
      self.sensor_2_ay = np.zeros(row_count-1)
      self.sensor_2_az = np.zeros(row_count-1)
      self.sensor_2_wx = np.zeros(row_count-1)
      self.sensor_2_wy = np.zeros(row_count-1)
      self.sensor_2_wz = np.zeros(row_count-1)
      self.sensor_3_ax = np.zeros(row_count-1)
      self.sensor_3_ay = np.zeros(row_count-1)
      self.sensor_3_az = np.zeros(row_count-1)
      self.sensor_3_wx = np.zeros(row_count-1)
      self.sensor_3_wy = np.zeros(row_count-1)
      self.sensor_3_wz = np.zeros(row_count-1)
      self.EMG_1       = np.zeros(row_count-1)
      self.EMG_2       = np.zeros(row_count-1)
      self.Event       = np.zeros(row_count-1)

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

   def plot_sensor_1_ax(self):
      pl.plot(self.sensor_1_ax)
      pl.show()
