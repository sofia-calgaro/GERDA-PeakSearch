#! /usr/bin/env python3

import pickle

with open('supercdms_2019_dp.pkl', 'rb') as pkl_file:
	data = pickle.load(pkl_file)
data
