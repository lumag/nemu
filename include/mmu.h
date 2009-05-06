/*
 * mmu.h
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


#ifndef MMU_H_
#define MMU_H_

#include <stdint.h>

// FIXME: maybe these should be bound to the whole box, not to the cpu in it?
// FIXME: addr and len are limited to 32 bit
struct CPUInfo;

typedef uint32_t (*mmio_read)(void *opaque, uint32_t offset);
typedef void (*mmio_write)(void *opaque, uint32_t offset);

int register_mmio(uint32_t addr, uint32_t mask, void *opaque);

uint32_t cpu_memory_read(struct CPUInfo *cpu, uint8_t *buf, uint32_t addr, uint32_t len);
uint32_t cpu_memory_write(struct CPUInfo *cpu, uint8_t *buf, uint32_t addr, uint32_t len);

#endif /* MMU_H_ */
