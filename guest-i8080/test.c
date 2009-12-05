/*
 * test.c
 *
 * Copyright (C) 2009 Dmitry Eremin-Solenikov
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <i8080.h>
#include <ir.h>
#include <mmio.h>
#include <drivers.h>

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

	mmio_register_memory(0x9000, 1, (void *)0x9000, &i7seg_hdlr);
	mmio_register_memory(0x9001, 1, (void *)0x9001, &i7seg_hdlr);
	mmio_register_memory(0x9002, 1, (void *)0x9002, &i7seg_hdlr);

	cpu.PC = 0;

	while (1) {
		bb = parse(addr + cpu.PC, buf.st_size - cpu.PC);
		dump_ir(bb);
		interp_ir(bb, (uint8_t *)&cpu);
		free_ir(bb);
	}

	return EXIT_SUCCESS;
}
