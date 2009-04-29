/*
 * interp.c
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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ir.h"

// FIXME endianness!!!
void interp_ir(struct IRs *bb, uint8_t *regfile) {
	int i;
	uint64_t *results; // FIXME
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
				uint64_t r = 0;
				switch (stmt->size) {
				case Size_I16:
					r |= (*(ptr+1)) << 8;
				case Size_I8:
					r |= *ptr;
				}
				results[nstmt] = r;
			}
			break;
		case SetReg:
			{
				uint8_t *ptr = regfile + stmt->get_reg.reg_offset;
				uint64_t r = results[stmt->set_reg.val_stmt];
				switch (stmt->size) {
				case Size_I16:
					(*(ptr+1)) = (r >> 8) & 0xff;
				case Size_I8:
					*ptr = r & 0xff;
				}
				results[nstmt] = r;
			}
			break;
		case Load:
			printf("!!!!Load");
//			printf("Load%s @(%x)", sizes[stmt->size], stmt->load.addr_stmt);
			break;
		case Store:
			printf("!!!!Store");
//			printf("Store%s @(%x) #(%x)", sizes[stmt->size], stmt->store.addr_stmt, stmt->store.val_stmt);
			break;
		case ALUOp:
			printf("!!!!ALU");
//			printf("ALU%s #(%x) #(%x)", sizes[stmt->size], stmt->alu.op1_stmt, stmt->alu.op2_stmt);
			break;
		}

		printf("%04Lx\n", results[nstmt]);
	}

	free(results);

}
