/*
 * ir.h
 *
 *  Created on: 21.04.2009
 *      Author: lumag
 */

#ifndef IR_H_
#define IR_H_

#include <stdint.h>

typedef enum { Size_I8, Size_I16 } IRSize;

typedef enum {
	GetReg, SetReg,
	Load, Store,
	Immediate,
} IRStmtType;

struct IRStmt {
	IRStmtType stmt_type;
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
	};
};

struct IRStmt *new_immediate(IRSize size, uint64_t value);
struct IRStmt *new_get_reg(IRSize size, uint32_t offset);
struct IRStmt *new_set_reg(IRSize size, uint32_t offset, uint32_t val_stmt);
struct IRStmt *new_load(IRSize size, int addr_stmt);
struct IRStmt *new_store(IRSize size, int addr_stmt, int val_stmt);

struct IRs {
	uint64_t startPC; // FIXME: type of startPC
	uint32_t num_stmt;
	uint32_t max_stmt;
	struct IRStmt **stmts;
	uint32_t num_code;
	uint32_t max_code;
	int *code; /* indices inside stmts array */
};

#endif /* IR_H_ */
