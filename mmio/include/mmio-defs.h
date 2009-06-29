/*
 * mmio-defs.h
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


#ifndef MMIODEFS_H_
#define MMIODEFS_H_

#define GUEST_PAGE_BITS 10

#if GUEST_ADDRESS_BITS < GUEST_PAGE_BITS
#error bad guest MMU configuration
#endif

#include <stdint.h>

#define GUEST_PGD_BITS 10
#if GUEST_ADDRESS_BITS <= GUEST_PAGE_BITS + GUEST_PGD_BITS
#undef GUEST_PGD_BITS
#define GUEST_PGD_BITS (GUEST_ADDRESS_BITS - GUEST_PAGE_BITS)
#define GUEST_PGD_LEVEL 1
#else
#define GUEST_PGD_LEVEL 2
#endif

#define GUEST_PAGE_SIZE (1 << GUEST_PAGE_BITS)
#define GUEST_PAGE_MASK (~(GUEST_PAGE_SIZE - 1))

extern struct mmio_handler *undef_hdlr; // FIXME

#endif /* MMUDEFS_H_ */
