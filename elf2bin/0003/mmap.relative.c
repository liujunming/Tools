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
	char *addr;
	int fd;
	struct stat sb;
	off_t offset = 0;
	size_t length;
	ssize_t s;

	if (argc != 1) {
		fprintf(stderr, "%s file offset [length]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	fd = open("./hello.relative.bin", O_RDONLY);
	if (fd == -1)
		handle_error("open");

	if (fstat(fd, &sb) == -1)           /* To obtain file size */
		handle_error("fstat");

	length = sb.st_size - offset;

	addr = mmap(NULL, length, PROT_READ | PROT_EXEC,
				MAP_PRIVATE, fd, offset);
	if (addr == MAP_FAILED)
		handle_error("mmap");

	((void (*)(void))addr)();

	exit(EXIT_SUCCESS);
}
