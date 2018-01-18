#!/usr/bin/python
# Filename : test.py
# 1. chmod a+x test.py
# 2. sudo ./test.py /var/www/html/

import sys
import os
import random

if __name__ == "__main__":
	basepath = sys.argv[1] # get the path

	listfile = []
	dirs = os.listdir(basepath)
	for file in dirs:
		filepath = basepath + file
		if(os.path.isfile(filepath)):
			listfile.append(file) # only remain the file name in the list

	random.shuffle(listfile) # shuffle the list

	length = len(listfile) # writre the string list to file,and the seperate between the string is NUL
	f = open("wlog.log", "w")
	i = 1
	for file in listfile:
			f.write('/'+file+'\0')
	f.write('\0')
