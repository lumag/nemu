/*
 * dump_ir.c
 *
 *  Created on: 28.04.2009
 *      Author: lumag
 */

#include <stdio.h>

#include <ir.h>

static const char *sizes[] = {
		[Size_I8] = "I8",
		[Size_I16] = "I16",
};

void dump_ir(struct IRs *bb) {
	int i;
	for (i = 0; i < bb->num_code; i++) {
		struct IRStmt *stmt = bb->stmts[bb->code[i]];
		printf("%6x\t", i);
		switch (stmt->type) {
		case Immediate:
			printf("Imm%s =%Lx", sizes[stmt->size], stmt->immediate.val); // XXX
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
