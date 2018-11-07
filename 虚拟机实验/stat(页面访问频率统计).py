#!/usr/bin/env python

import os
import sys

if __name__ == "__main__":
    filename = "tmp.txt"
    f = open(filename)
    tag = '11111111'
    d = {}
    while True:
        line = f.readline()
        if not line:
            break
        line = line[:-1]
        if line.split(':')[0] == tag:
            if line.split(':')[1] in d:
                d[line.split(':')[1]] = int(line.split(':')[2]) + d[line.split(':')[1]]
            else:  
                d[line.split(':')[1]] = int(line.split(':')[2])

    # print(d)
    data = {0 : long('0'), 1 : long('0'), 2 : long('0'), 3 : long('0'), 4 : long('0'), 5 : long('0'), 6 : long('0'), 7 : long('0'), 8 : long('0'), 9 :long('0'), 10 : long('0')}
    for key, value in d.items():
        if value in data:
            data[value] = data[value] + 1
            # print(key, value)
    for key, value in data.items():
        print(value)
