/*
 * ir.c
 *
 *  Created on: 28.04.2009
 *      Author: lumag
 */

#include <stdlib.h>
#include <stdio.h>

#include "ir.h"

struct IRStmt *new_immediate(IRSize size, uint64_t value) {
	struct IRStmt *stmt = calloc(1, sizeof(struct IRStmt));
	stmt->type = Immediate;
	stmt->size = size;
	stmt->immediate.val = value;

	return stmt;
}

struct IRStmt *new_get_reg(IRSize size, uint32_t offset) {
	struct IRStmt *stmt = calloc(1, sizeof(struct IRStmt));
	stmt->type = GetReg;
	stmt->size = size;
	stmt->get_reg.reg_offset = offset;

	return stmt;
}

struct IRStmt *new_set_reg(IRSize size, uint32_t offset, uint32_t val_stmt) {
	struct IRStmt *stmt = calloc(1, sizeof(struct IRStmt));
	stmt->type = SetReg;
	stmt->size = size;
	stmt->set_reg.reg_offset = offset;
	stmt->set_reg.val_stmt = val_stmt;

	return stmt;
}

struct IRStmt *new_load(IRSize size, int addr_stmt) {
	struct IRStmt *stmt = calloc(1, sizeof(struct IRStmt));
	stmt->type = Load;
	stmt->size = size;
	stmt->load.addr_stmt = addr_stmt;

	return stmt;
}

struct IRStmt *new_store(IRSize size, int addr_stmt, int val_stmt) {
	struct IRStmt *stmt = calloc(1, sizeof(struct IRStmt));
	stmt->type = Store;
	stmt->size = size;
	stmt->store.addr_stmt = addr_stmt;
	stmt->store.val_stmt = val_stmt;

	return stmt;
}

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
		}

		printf("\n");
	}
}
