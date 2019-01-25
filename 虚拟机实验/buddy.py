# -*- coding: UTF-8 -*-
import os
import math
import time

while True:
    result = os.popen("cat /proc/buddyinfo | grep 'Node 1'").read().split()
    # total_free_pages = 0
    # for i in range(4, 15):
    #     total_free_pages = total_free_pages + int(result[i]) * pow(2, i-4)
    # tem = pow(2, 9) * int(result[13]) + pow(2, 10) * int(result[14])
    # frag_level = (total_free_pages - tem) * 100 / total_free_pages
    # print(result)
    print('2MB page memory size: ' + str(int(result[13]) * 2) + "MB")
    print('4MB page memory size: ' + str(int(result[14]) * 4) + "MB")
    
    time.sleep(2)