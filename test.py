#!/usr/bin/env python

import sys
import os
import random

def search():
  num = int(sys.argv[1])
  size = int(sys.argv[2])
  itr = int(num/size)

  for i in range(0,1):
    lst1 = list(range(0, itr))
    random.shuffle (lst1)
    for j in lst1:
      cmd = """curl -XPOST 'localhost:9200/test_data/_search?pretty' -d '{ "query": { "match_all": {} },"from": """+str(j*size)+""","size":"""+ str(size)+"""}'"""
      os.system(cmd)
  

if __name__ == '__main__':
  search()
  
