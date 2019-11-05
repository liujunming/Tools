//cp /sys/bus/pci/devices/0000\:00\:02.0/resource .

#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef unsigned long int	uint64_t;
typedef unsigned int		uint32_t;

int main(){

    int ret;
    char resource[512];
    int res_fd;
	uint64_t gttmmadr_low_addr;
	uint64_t gttmmadr_high_addr;
	uint64_t aperture_low_addr;
	uint64_t aperture_high_addr;
	char * next;
	int i; 
	uint64_t flags; 

    res_fd = open("./resource", O_RDONLY);
	if (res_fd == -1) {
		perror("gvt:open host pci resource failed\n");
		return -1;
	}    

    ret = pread(res_fd, resource, 512, 0);

    close(res_fd);

    if (ret < 512) {
		perror("failed to read host device resource space\n");
		return -1;
	}

    resource[511] = '\0';

    next = resource;

    gttmmadr_low_addr = strtoull( next, & next, 16 );
    gttmmadr_high_addr = strtoull( next, & next, 16);
    printf("gttmmadr_low_addr = %lx, gttmmadr_high_addr = %lx\n", gttmmadr_low_addr, gttmmadr_high_addr);

    next = next + 80;

    aperture_low_addr = strtoull( next, & next,  16);
    aperture_high_addr = strtoull( next, & next, 16 );
    printf("aperture_low_addr = %lx, aperture_high_addr = %lx\n", aperture_low_addr, aperture_high_addr);

    return 0;
}
