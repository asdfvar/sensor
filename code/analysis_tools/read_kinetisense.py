#!/usr/bin/python

class KIN:
   def __init__(self, path):
      with open(path,'r') as fid
         reader = csv.reader(fid)
         print reader[0]
