/*
 * mmu.c
 *
 * Copyright (C) 2009 Dmitry Eremin-Solenikov
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
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

#include <guest.h>
#include <mmu.h>
#include <stdio.h>
#include <string.h>

uint32_t cpu_memory_read(struct CPUInfo *cpu, uint8_t *buf, uint32_t addr, uint32_t len) {
	printf("read %d bytes at %x ", len, addr);
	memset(buf, -1, len);
	return -1;
}

uint32_t cpu_memory_write(struct CPUInfo *cpu, uint8_t *buf, uint32_t addr, uint32_t len) {
	printf("write %d bytes at %x ", len, addr);
	return -1;
}
