#include <stdio.h>
#include <stdlib.h>
#define __USE_GNU  
#include <sched.h> 
#include <sys/mman.h> 

int main()
{
    char *addr, *adjust_addr;  

    size_t len = 1024 * 1024 * 1024;
    size_t i, tem;

    cpu_set_t set;
    CPU_ZERO(&set); // clear cpu mask
    CPU_SET(36, &set);  // set cpu 36
    sched_setaffinity(0, sizeof(cpu_set_t), &set);  // 0 is the calling process

    addr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    madvise(addr, len, MADV_HUGEPAGE);

    for(i = 0; i < len; i++)
        addr[i] = 'a';

    tem = (size_t)addr;
    tem = tem % (2 * 1024 * 1024);
    adjust_addr = addr - tem; //adjust_addr 2MB align

    for(i = 0; i < 127 * 1024; i++)
        madvise(adjust_addr +  i * 8192, 4096, MADV_DONTNEED);

    getchar();

    return 0;
}
