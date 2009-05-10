/*
 * mmio-drv.h
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


#ifndef MMIODRV_H_
#define MMIODRV_H_


typedef unsigned long ram_offset_t;

struct mmio_handler { // FIXME: it may be necessary to add 64-bit handlers
	uint8_t (*read8)(void *opaque, ram_offset_t offset);
	uint16_t (*read16)(void *opaque, ram_offset_t offset);
	uint32_t (*read32)(void *opaque, ram_offset_t offset);
	void (*write8)(void *opaque, ram_offset_t offset, uint8_t value);
	void (*write16)(void *opaque, ram_offset_t offset, uint16_t value);
	void (*write32)(void *opaque, ram_offset_t offset, uint32_t value);
};

#endif

