#!/usr/bin/env python
import re

load_count = []
store_count = []
with open('1.txt') as f:
    data = f.readlines()
index = 1
for line in data:
    line_data = line.strip()
    words = line.split()
    #print(words[0])
    if re.match("^\d+?\.\d+?$", words[0]):
        if index > 500:
            break
        #print(words[1])
        count = int(words[1].replace(',', ''))
        load_count.append(count)
        index += 1

with open('2.txt') as f:
    data = f.readlines()
index = 1
for line in data:
    line_data = line.strip()
    words = line.split()
    if re.match("^\d+?\.\d+?$", words[0]):
        if index > 500:
            break
        count = int(words[1].replace(',', ''))
        store_count.append(count)
        index += 1
result = []
index = 0
while index < 500:
    result.append(load_count[index] + store_count[index])
    index += 1

print(result)