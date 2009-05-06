/*
 * ir.h
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

#ifndef IR_H_
#define IR_H_

#include <stdint.h>

typedef enum { Size_I8, Size_I16 } IRSize;

typedef enum {
	GetReg, SetReg,
	Load, Store,
	Immediate,
	ALUOp,
} IRStmtType;

typedef enum {
	ADD,			// FIXME add more or understand how to work with carry
	SUB,
	AND,
	OR,
	XOR,
} IRAluOp;

struct IRStmt {
	IRStmtType type;
	IRSize size;
	union {
		struct {
			uint32_t reg_offset;
		} get_reg;
		struct {
			uint32_t reg_offset;
			int val_stmt;
		} set_reg;
		struct {
			int addr_stmt;
		} load;
		struct {
			int addr_stmt;
			int val_stmt;
		} store;
		struct {
			uint64_t val; // FIXME: replace with union?
		} immediate;
		struct {
			// FIXME: operation type
			IRAluOp op;
			int op1_stmt;
			int op2_stmt;
		} alu;
	};
};

struct IRStmt *new_immediate(IRSize size, uint64_t value);
struct IRStmt *new_get_reg(IRSize size, uint32_t offset);
struct IRStmt *new_set_reg(IRSize size, uint32_t offset, uint32_t val_stmt);
struct IRStmt *new_load(IRSize size, int addr_stmt);
struct IRStmt *new_store(IRSize size, int addr_stmt, int val_stmt);
struct IRStmt *new_alu(IRSize size, IRAluOp op, int op1_stmt, int op2_stmt);

struct IRs {
	uint64_t startPC; // FIXME: type of startPC
	uint32_t num_stmt;
	uint32_t max_stmt;
	struct IRStmt **stmts;
	uint32_t num_code;
	uint32_t max_code;
	int *code; /* indices inside stmts array */
};

void dump_ir(struct IRs *bb);
void interp_ir(struct IRs *bb, uint8_t *regfile);

#endif /* IR_H_ */
