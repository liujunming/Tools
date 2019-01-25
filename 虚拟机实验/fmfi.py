# -*- coding: UTF-8 -*-
import os
import math
import time

# reference:http://events17.linuxfoundation.org/sites/events/files/slides/%5BELC-2015%5D-System-wide-Memory-Defragmenter.pdf p4-p6

while True:
    result = os.popen("cat /proc/buddyinfo | grep 'Node 1'").read().split()
    total_free_pages = 0
    for i in range(4, 15):
        total_free_pages = total_free_pages + int(result[i]) * pow(2, i-4)
    tem = pow(2, 9) * int(result[13]) + pow(2, 10) * int(result[14])
    frag_level = (total_free_pages - tem) * 100 / total_free_pages
    print(frag_level)

    time.sleep(2)
