/*
 * mmio-undef.c
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

#include <mmio.h>
#include <mmio-defs.h>
#include <stdio.h>

static uint8_t undef_read8(void *opaque, ram_offset_t offset) {
	fprintf(stderr, "Undefined read8 at: 0x%lx\n", offset);
	return 0xff;
}
static uint16_t undef_read16(void *opaque, ram_offset_t offset) {
	fprintf(stderr, "Undefined read16 at: 0x%lx\n", offset);
	return 0xffff;
}
static uint32_t undef_read32(void *opaque, ram_offset_t offset) {
	fprintf(stderr, "Undefined read32 at: 0x%lx\n", offset);
	return 0xffffff;
}
static void undef_write8(void *opaque, ram_offset_t offset, uint8_t value) {
	fprintf(stderr, "Undefined write8 at: 0x%lx\n", offset);
}
static void undef_write16(void *opaque, ram_offset_t offset, uint16_t value) {
	fprintf(stderr, "Undefined write16 at: 0x%lx\n", offset);
}
static void undef_write32(void *opaque, ram_offset_t offset, uint32_t value) {
	fprintf(stderr, "Undefined write32 at: 0x%lx\n", offset);
}

struct mmio_handler *undef_hdlr = &(struct mmio_handler){
	.read8 = undef_read8,
	.read16 = undef_read16,
	.read32 = undef_read32,
	.write8 = undef_write8,
	.write16 = undef_write16,
	.write32 = undef_write32,
};
