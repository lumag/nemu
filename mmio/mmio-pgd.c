/*
 * mmio-pgd.c
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

#include <stdlib.h>

#include <mmio.h>
#include "mmio-defs.h"

struct page {
	ram_offset_t start; // offset from start of this page
	ram_offset_t end; // offset from start of this page
	ram_offset_t area_offset; // offset for the value passed to the handlers
	struct page *next;
	void *opaque;
	struct mmio_handler *hdlr;
};

#if GUEST_PGD_LEVEL == 1
static struct page* pgd[(1 << GUEST_PGD_BITS)];
#else
#error not supported yet
#endif

void mmio_register_memory(guest_address_t start, ram_offset_t size, void *opaque, struct mmio_handler *hdlr) {
	guest_address_t addr;
	ram_offset_t area_offset = 0;
	for (addr = start & GUEST_PAGE_MASK; addr <= start + size; addr += GUEST_PAGE_SIZE) {
		struct page *page = calloc(1, sizeof(struct page));
		if (addr < start)
			page->start = start & ~GUEST_PAGE_MASK;
		else
			page->start = 0;

		if (addr + GUEST_PAGE_SIZE > start + size)
			page->end = (start + size) &~GUEST_PAGE_MASK;
		else
			page->end = GUEST_PAGE_SIZE;

		page->area_offset = area_offset - page->start;
		area_offset += page->end - page->start;

		page->opaque = opaque;
		page->hdlr = hdlr;

#if GUEST_PGD_LEVEL == 1
		page->next = pgd[addr >> (GUEST_ADDRESS_BITS - GUEST_PGD_BITS)];
		pgd[addr >> (GUEST_ADDRESS_BITS - GUEST_PGD_BITS)] = page;
#else
#error not supported yet
#endif
	}
}

static struct page *mmio_get_page(guest_address_t addr) {
	struct page *page = pgd[addr >> (GUEST_ADDRESS_BITS - GUEST_PGD_BITS)];
	ram_offset_t off = addr & ~GUEST_PAGE_MASK;

	while (page && (off < page->start || page->end <= off)) {
		page = page->next;
	}

	return page;
}

uint8_t mmio_read_8(guest_address_t addr) {
	struct page *page = mmio_get_page(addr);
	if (!page)
		return undef_hdlr->read8(NULL, addr); // FIXME: split addr into opaque and offset for undefined handler;
	return page->hdlr->read8(page->opaque, page->area_offset + (addr &~GUEST_PAGE_MASK) - page->start);
}

uint16_t mmio_read_16(guest_address_t addr) {
	struct page *page = mmio_get_page(addr);
	if (!page)
		return undef_hdlr->read16(NULL, addr); // FIXME: split addr into opaque and offset for undefined handler;
	return page->hdlr->read16(page->opaque, page->area_offset + (addr &~GUEST_PAGE_MASK));
}

uint32_t mmio_read_32(guest_address_t addr) {
	struct page *page = mmio_get_page(addr);
	if (!page)
		return undef_hdlr->read32(NULL, addr); // FIXME: split addr into opaque and offset for undefined handler;
	return page->hdlr->read32(page->opaque, page->area_offset + (addr &~GUEST_PAGE_MASK));
}

void mmio_write_8(guest_address_t addr, uint8_t value) {
	struct page *page = mmio_get_page(addr);
	if (!page)
		undef_hdlr->write8(NULL, addr, value); // FIXME: split addr into opaque and offset for undefined handler
	else
		page->hdlr->write8(page->opaque, page->area_offset + (addr &~GUEST_PAGE_MASK), value);
}

void mmio_write_16(guest_address_t addr, uint16_t value) {
	struct page *page = mmio_get_page(addr);
	if (!page)
		undef_hdlr->write16(NULL, addr, value); // FIXME: split addr into opaque and offset for undefined handler
	else
		page->hdlr->write16(page->opaque, page->area_offset + (addr &~GUEST_PAGE_MASK), value);
}

void mmio_write_32(guest_address_t addr, uint32_t value) {
	struct page *page = mmio_get_page(addr);
	if (!page)
		undef_hdlr->write32(NULL, addr, value); // FIXME: split addr into opaque and offset for undefined handler
	else
		page->hdlr->write32(page->opaque, page->area_offset + (addr &~GUEST_PAGE_MASK), value);
}
