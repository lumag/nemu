/*
 * i7seg.c
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

#include <stdio.h>
#include <stdint.h>

#include <mmio.h>

static uint8_t i7seg_read8(void *opaque, ram_offset_t offset) {
	fprintf(stderr, "7-segment at %p read8 at: 0x%lx\n", opaque, offset);
	return 0xff;
}
static uint16_t i7seg_read16(void *opaque, ram_offset_t offset) {
	fprintf(stderr, "7-segment at %p read16 at: 0x%lx\n", opaque, offset);
	return 0xffff;
}
static uint32_t i7seg_read32(void *opaque, ram_offset_t offset) {
	fprintf(stderr, "7-segment at %p read32 at: 0x%lx\n", opaque, offset);
	return 0xffffff;
}
static void i7seg_write8(void *opaque, ram_offset_t offset, uint8_t value) {
	fprintf(stderr, "7-segment at %p write8 at: 0x%lx\n", opaque, offset);
}
static void i7seg_write16(void *opaque, ram_offset_t offset, uint16_t value) {
	fprintf(stderr, "7-segment at %p write16 at: 0x%lx\n", opaque, offset);
}
static void i7seg_write32(void *opaque, ram_offset_t offset, uint32_t value) {
	fprintf(stderr, "7-segment at %p write32 at: 0x%lx\n", opaque, offset);
}

struct mmio_handler i7seg_hdlr = {
	.read8 = i7seg_read8,
	.read16 = i7seg_read16,
	.read32 = i7seg_read32,
	.write8 = i7seg_write8,
	.write16 = i7seg_write16,
	.write32 = i7seg_write32,
};

