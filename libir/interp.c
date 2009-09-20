/*
 * interp.c
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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ir.h"

#include <mmio.h>

static uint32_t sizes[] = {
		[Size_I8] = 1,
		[Size_I16] = 2,
		[Size_I32] = 4,
};

#if GUEST_ADDRESS_BITS == 16
#define addrval val16
#else
#error guest address space is not suported
#endif


static inline uint64_t interp_alu(struct IRStmt *stmt, uint64_t op1, uint64_t op2) {
	uint64_t r;

	switch (stmt->alu.op) {
	case ADD:
		r = op1 + op2;
		break;
	case SUB:
		r = op1 - op2;
		break;
	case AND:
		r = op1 & op2;
		break;
	case OR:
		r = op1 | op2;
		break;
	case XOR:
		r = op1 ^ op2;
		break;
	}

	return r & ((1 << (8 * sizes[stmt->size])) - 1);
}

// FIXME endianness in register file access!!!
void interp_ir(struct IRs *bb, uint8_t *regfile) {
	int i;
	IRValue *results; // FIXME
	results = calloc(bb->num_stmt, sizeof(*results));
	for (i = 0; i < bb->num_code; i++) {
		int nstmt = bb->code[i];
		struct IRStmt *stmt = bb->stmts[nstmt];
		printf("%6x (%x)\t= ", i, nstmt);
		switch (stmt->type) {
		case Immediate:
			results[nstmt] = stmt->immediate.val;
			break;
		case GetReg:
			{
				uint8_t *ptr = regfile + stmt->get_reg.reg_offset;
				switch (stmt->size) {
				case Size_I32:
					results[nstmt].val32 = *(uint32_t*)ptr;
					break;
				case Size_I16:
					results[nstmt].val16 = *(uint16_t*)ptr;
					break;
				case Size_I8:
					results[nstmt].val8 = *(uint8_t*)ptr;
					break;
				}
			}
			break;
		case SetReg:
			{
				uint8_t *ptr = regfile + stmt->get_reg.reg_offset;
				switch (stmt->size) {
				case Size_I32:
					*(uint32_t*)ptr = results[stmt->set_reg.val_stmt].val32;
					break;
				case Size_I16:
					*(uint16_t*)ptr = results[stmt->set_reg.val_stmt].val16;
					break;
				case Size_I8:
					*(uint8_t*)ptr = results[stmt->set_reg.val_stmt].val8;
					break;
				}
			}
			break;
		case Load:
			printf("!!!!Load ");
			switch (stmt->size) {
			case Size_I8:
				results[nstmt].val8 = mmio_read_8(results[stmt->load.addr_stmt].addrval);
				break;
			case Size_I16:
				results[nstmt].val16 = mmio_read_16(results[stmt->load.addr_stmt].addrval);
				break;
			case Size_I32:
				results[nstmt].val32 = mmio_read_32(results[stmt->load.addr_stmt].addrval);
				break;
			}
//			printf("Load%s @(%x)", sizes[stmt->size], stmt->load.addr_stmt);
			break;
		case Store:
			switch (stmt->size) {
			case Size_I8:
				mmio_write_8(results[stmt->load.addr_stmt].addrval, results[stmt->store.val_stmt].val8);
				break;
			case Size_I16:
				mmio_write_16(results[stmt->load.addr_stmt].addrval, results[stmt->store.val_stmt].val16);
				break;
			case Size_I32:
				mmio_write_32(results[stmt->load.addr_stmt].addrval, results[stmt->store.val_stmt].val32);
				break;
			}
			results[nstmt] = results[stmt->store.val_stmt];
//			printf("Store%s @(%x) #(%x)", sizes[stmt->size], stmt->store.addr_stmt, stmt->store.val_stmt);
			break;
		case ALUOp:
//			printf("ALU%s #(%x) #(%x)", sizes[stmt->size], stmt->alu.op1_stmt, stmt->alu.op2_stmt);
			// FIXME: alu bitness
			results[nstmt].val64 = interp_alu(stmt, results[stmt->alu.op1_stmt].val64, results[stmt->alu.op2_stmt].val64);
			break;
		}

		printf("%04Lx\n", results[nstmt].val64);
	}

	free(results);

}
