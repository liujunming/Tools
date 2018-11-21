#!/usr/bin/env python

import os
import sys
import re 

if __name__ == "__main__":
    filename = "1.txt"
    list_num = []
    f = open(filename)

    while True:
        line = f.readline()
        if not line:
            break
        line = f.readline()
        line = line[:-1]
        list_num.append(int(re.findall('\\d+', line)[0]))
    print(*list_num, sep='\t')
    # print(*list_num, sep='\t')