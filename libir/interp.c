/*
 * interp.c
 *
 *  Created on: 29.04.2009
 *      Author: lumag
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
