/*
 * test.c
 *
 *  Created on: 28.04.2009
 *      Author: lumag
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <guest.h>
#include <i8080.h>
#include <ir.h>

int main(int argc, char **argv) {
	struct IRs *bb;
	struct I8080CPU cpu;
	if (argc < 2) {
		fprintf(stderr, "Usage: %s file\n", argv[0]);
		return EXIT_FAILURE;
	}

	int fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		perror("open");
		return EXIT_FAILURE;
	}

	struct stat buf;
	int ret = fstat(fd, &buf);
	if (ret < 0) {
		perror("fstat");
		return EXIT_FAILURE;
	}

	void *addr = mmap(NULL, buf.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED) {
		perror("mmap");
		return EXIT_FAILURE;
	}

	close(fd);

	bb = parse(addr, buf.st_size);
	dump_ir(bb);
	interp_ir(bb, (uint8_t *)&cpu);

	return EXIT_SUCCESS;
}
