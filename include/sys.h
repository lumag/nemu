/*
 * sys.h
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

#ifndef SYS_H_
#define SYS_H_

#undef offsetof
#ifndef offsetof
//#define offsetof(TYPE, MEMBER)	__builtin_offsetof(TYPE, MEMBER)
#define offsetof(TYPE, MEMBER)		((size_t) &((TYPE *)0)->MEMBER)
#endif

#endif /* SYS_H_ */
