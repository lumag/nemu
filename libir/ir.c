/*
 * ir.c
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

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

struct IRStmt *new_alu(IRSize size, IRAluOp op, int op1_stmt, int op2_stmt) {
	struct IRStmt *stmt = calloc(1, sizeof(struct IRStmt));
	stmt->type = ALUOp;
	stmt->size = size;
	stmt->alu.op = op;
	stmt->alu.op1_stmt = op1_stmt;
	stmt->alu.op2_stmt = op2_stmt;

	return stmt;
}
