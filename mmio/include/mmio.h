/*
 * mmio.h
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


#ifndef MMIO_H_
#define MMIO_H_

#include <stdint.h>

#if !defined(GUEST_ADDRESS_BITS)
#error you shoud define GUEST_ADDRESS_BITS
#elif GUEST_ADDRESS_BITS <= 16
typedef uint16_t guest_address_t;
#elif GUEST_ADDRESS_BITS <= 32
typedef uint32_t guest_address_t;
#else
#error guest address space not supported
#endif

typedef unsigned long ram_offset_t;

struct mmio_handler { // FIXME: it may be necessary to add 64-bit handlers
	uint8_t (*read8)(void *opaque, ram_offset_t offset);
	uint16_t (*read16)(void *opaque, ram_offset_t offset);
	uint32_t (*read32)(void *opaque, ram_offset_t offset);
	void (*write8)(void *opaque, ram_offset_t offset, uint8_t value);
	void (*write16)(void *opaque, ram_offset_t offset, uint16_t value);
	void (*write32)(void *opaque, ram_offset_t offset, uint32_t value);
};

void mmio_register_memory(guest_address_t start, ram_offset_t size, void *opaque, struct mmio_handler *hdlr);

uint8_t mmio_read_8(guest_address_t addr);
void mmio_write_8(guest_address_t addr, uint8_t value);
uint16_t mmio_read_16(guest_address_t addr);
void mmio_write_16(guest_address_t addr, uint16_t value);
uint32_t mmio_read_32(guest_address_t addr);
void mmio_write_32(guest_address_t addr, uint32_t value);


#endif /* MMU_H_ */
