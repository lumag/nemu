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

