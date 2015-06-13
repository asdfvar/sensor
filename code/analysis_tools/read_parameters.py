class read_parameters:

   def __init__(self, path):

      with open(path, 'r') as fid:
         innards = fid.readlines();

         for line in innards:
            parsed_line = line.split('=')

            if parsed_line[0] == 'tag':
               self.tag = parsed_line[1]

            elif parsed_line[0] == 'samp_freq':
               self.samp_freq = float(parsed_line[1])
               self.dt        = 1.0 / self.samp_freq

            elif parsed_line[0] == 'time_window':
               self.time_window = float(parsed_line[1])

            elif parsed_line[0] == 'cutoff_freq':
               self.cutoff_freq = float(parsed_line[1])

            elif parsed_line[0] == 'freq_range':
               self.freq_range = float(parsed_line[1])

            elif parsed_line[0] == 'threshold':
               self.threshold = float(parsed_line[1])

            elif parsed_line[0] == 'sex':
               self.sex = parsed_line[1]

            elif parsed_line[0] == 'age':
               self.age = int(parsed_line[1])

            elif parsed_line[0] == 'weight':
               self.weight = float(parsed_line[1])

            elif parsed_line[0] == 'height':
               self.height = float(parsed_line[1])

            elif parsed_line[0] == 'data_path':
               self.data_path = parsed_line[1]

            elif parsed_line[0] == 'ref_path':
               self.ref_path = parsed_line[1]

            else:
               print "un-identified line"
