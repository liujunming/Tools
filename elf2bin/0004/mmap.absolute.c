#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

int
main(int argc, char *argv[])
{
	char *addr = NULL;
	int fd;
	struct stat sb;
	off_t offset = 0;
	size_t length;
	ssize_t s;

	if (argc != 1) {
		fprintf(stderr, "%s file offset [length]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	fd = open("./hello.bin", O_RDONLY);
	if (fd == -1)
		handle_error("open");

	if (fstat(fd, &sb) == -1)           /* To obtain file size */
		handle_error("fstat");

	length = sb.st_size - offset;

	addr = (char *)0x04200000;
	addr = mmap(addr, length, PROT_READ | PROT_WRITE | PROT_EXEC,
				MAP_PRIVATE | MAP_FIXED, fd, offset);
	if (addr == MAP_FAILED)
		handle_error("mmap");

	/* update the data address */
    #define inst_offset 17
	// data_offset = 0x04200000 + 0x2a
	*(addr + inst_offset) = 0x2a;
	*(addr + inst_offset + 1) = 0x00;
	*(addr + inst_offset + 2) = 0x20;
	*(addr + inst_offset + 3) = 0x04;

	__builtin___clear_cache(addr, addr + length);

	((void (*)(void))addr)();

	exit(EXIT_SUCCESS);
}
