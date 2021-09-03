#! /usr/bin/env python3

#import pickle
#import base64
#import csv

#your_pickle_obj = pickle.loads(open('cdex_2019_alps.pkl', 'rb').read())
#with open('output.csv', 'a', encoding='utf8') as csv_file:
#	wr = csv.writer(csv_file, delimiter='|')
#	pickle_bytes = pickle.dumps(your_pickle_obj)
#	b64_bytes = base64.b64encode(pickle_bytes)
#	b64_str = b64_bytes.decode('utf8')
#	wr.writerow(['col1', 'col2', b64_str])
	
	
import pickle

with open('cdex_2019_alps.pkl', 'rb') as pkl_file:
	new_data = pickle.load(pkl_file)
