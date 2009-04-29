/*
 * i8080.h
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

#ifndef I8080_H_
#define I8080_H_

#include <stdint.h>
#include <stdlib.h>

#include "sys.h"

struct I8080CPU {
	uint16_t BC;
	uint16_t DE;
	uint16_t HL;

	uint16_t AF;

	uint16_t SP;
	uint16_t PC;
};

typedef uint16_t target_ulong_t; // FIXME

#define off_BC	offsetof(struct I8080CPU, BC)
#define off_DE	offsetof(struct I8080CPU, DE)
#define off_HL	offsetof(struct I8080CPU, HL)
#define off_AF	offsetof(struct I8080CPU, AF)
#define off_SP	offsetof(struct I8080CPU, SP)
#define off_PC	offsetof(struct I8080CPU, PC)

#include <endian.h>
#if BYTE_ORDER == LITTLE_ENDIAN

#define off_B	(off_BC+1)
#define off_C	(off_BC)
#define off_D	(off_DE+1)
#define off_E	(off_DE)
#define off_H	(off_HL+1)
#define off_L	(off_HL)
#define off_A	(off_AF+1)
#define off_PSW	(off_AF)
#define off_PCH	(off_PC+1)
#define off_PCL	(off_PC)

#else /* BIG_ENDIAN */

#define off_B	(off_BC)
#define off_C	(off_BC+1+1)
#define off_D	(off_DE)
#define off_E	(off_DE+1)
#define off_H	(off_HL)
#define off_L	(off_HL+1)
#define off_A	(off_AF)
#define off_PSW	(off_AF+1)
#define off_PCH	(off_PC)
#define off_PCL	(off_PC+1)

#endif


#endif /* I8080_H_ */
