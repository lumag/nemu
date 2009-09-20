/*
 * dump_ir.c
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

#include <ir.h>

static const char *sizes[] = {
		[Size_I8] = "I8",
		[Size_I16] = "I16",
		[Size_I32] = "I32",
};

void dump_ir(struct IRs *bb) {
	int i;
	for (i = 0; i < bb->num_code; i++) {
		struct IRStmt *stmt = bb->stmts[bb->code[i]];
		printf("%6x\t", i);
		switch (stmt->type) {
		case Immediate:
			printf("Imm%s =%Lx", sizes[stmt->size], stmt->immediate.val.val64);
			break;
		case GetReg:
			printf("GetReg%s %%%x", sizes[stmt->size], stmt->get_reg.reg_offset);
			break;
		case SetReg:
			printf("SetReg%s %%%x #(%x)", sizes[stmt->size], stmt->set_reg.reg_offset, stmt->set_reg.val_stmt);
			break;
		case Load:
			printf("Load%s @(%x)", sizes[stmt->size], stmt->load.addr_stmt);
			break;
		case Store:
			printf("Store%s @(%x) #(%x)", sizes[stmt->size], stmt->store.addr_stmt, stmt->store.val_stmt);
			break;
		case ALUOp:
			printf("ALU%s #(%x) #(%x)", sizes[stmt->size], stmt->alu.op1_stmt, stmt->alu.op2_stmt);
			break;
		}

		printf("\n");
	}
}
