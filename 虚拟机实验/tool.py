#!/usr/bin/env python

import os
import sys

def fun(filename):
	f = open(filename)
	ret = ''
	while True:
		line_time = f.readline()
		if not line_time: 
			break
		line_sharing = f.readline()
		ret = ret + '\t' + filter(str.isdigit, line_sharing)

	fh = open("output.txt", 'w') 
	fh.write(ret)
	#print(ret)


if __name__ == "__main__":
	filename = sys.argv[1]
	fun(filename)
