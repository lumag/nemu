/*
 * parse.c
 *
 *  Created on: 21.04.2009
 *      Author: lumag
 */
#include <stdio.h>

#include "i8080.h"
#include "ir.h"

struct reg_s {
	const char *name;
	uint32_t off;
};

#define REG_MEM	6
#define REG_A	7

static struct reg_s regs[] = {
		{"b", off_B},
		{"c", off_C},
		{"d", off_D},
		{"e", off_E},
		{"h", off_H},
		{"l", off_L},
		{"(hl)", -1},
		{"a", off_A},
};

static struct reg_s pairs[] = {
		{"bc", off_BC},
		{"de", off_DE},
		{"hl", off_HL},
		{"sp", off_SP},
};

static struct reg_s alu_ops[] = { // FIXME
		{"add", ADD},
		{"adc", -1},
		{"sub", SUB},
		{"sbb", -1},
		{"and", AND},
		{"xor", XOR},
		{"or", OR},
		{"cp", -1},
};

#define STMT_STEP	16

static int ir_add_stmt(struct IRs *bb, struct IRStmt *stmt) {
	int s;

	if (bb->num_stmt >= bb->max_stmt) {
		bb->max_stmt += STMT_STEP;
		bb->stmts = realloc(bb->stmts, bb->max_stmt * sizeof(*bb->stmts));
	}

	if (bb->num_code >= bb->max_code) {
		bb->max_code += STMT_STEP;
		bb->code = realloc(bb->code, bb->max_code * sizeof(*bb->code));
	}

	s = bb->num_stmt;

	bb->stmts[bb->num_stmt ++] = stmt;
	bb->code[bb->num_code ++] = s;
	return s;
}

static target_ulong_t parse_insn(struct IRs *bb, uint8_t *addr, target_ulong_t pc) {
	uint8_t b = addr[pc++];
	uint8_t op8;
	uint16_t op16;
	int stmt1, stmt2;
	int reg, reg2;
	switch (b & 0xc0) {
	case 0x00:
		switch (b & 7) {
		case 0:
			if (b == 0) {
				printf("!nop");
			} else
				goto undef;
			break;
		case 1:
			reg = (b & 0x30) >> 4;
			if (b&8) {
				stmt1 = ir_add_stmt(bb, new_get_reg(Size_I16, off_HL));
				stmt2 = ir_add_stmt(bb, new_get_reg(Size_I16, pairs[reg].off));
				stmt1 = ir_add_stmt(bb, new_alu(Size_I16, ADD, stmt1, stmt2));
				ir_add_stmt(bb, new_set_reg(Size_I16, off_HL, stmt1));
				printf("add hl,%s", pairs[reg].name);
			} else {
				op16 = addr[pc++];
				op16 |= (addr[pc++] << 8);
				stmt1 = ir_add_stmt(bb, new_immediate(Size_I16, op16));
				ir_add_stmt(bb, new_set_reg(Size_I16, pairs[reg].off, stmt1));
				printf("ld %s, 0x%04x", pairs[reg].name, op16);
			}
			break;
		case 2:
			switch ((b >> 3) & 7) {
			case 0:
				stmt1 = ir_add_stmt(bb, new_get_reg(Size_I8, off_A));

				stmt2 = ir_add_stmt(bb, new_get_reg(Size_I16, off_BC));
				ir_add_stmt(bb, new_store(Size_I8, stmt2, stmt1));

				printf("ld (bc), a");
				break;
			case 1:
				stmt2 = ir_add_stmt(bb, new_get_reg(Size_I16, off_BC));
				stmt1 = ir_add_stmt(bb, new_load(Size_I8, stmt2));
				ir_add_stmt(bb, new_set_reg(Size_I8, off_A, stmt1));
				printf("ld a,(bc)");
				break;
			case 2:
				stmt1 = ir_add_stmt(bb, new_get_reg(Size_I8, off_A));

				stmt2 = ir_add_stmt(bb, new_get_reg(Size_I16, off_DE));
				ir_add_stmt(bb, new_store(Size_I8, stmt2, stmt1));

				printf("ld (de), a");
				break;
			case 3:
				stmt2 = ir_add_stmt(bb, new_get_reg(Size_I16, off_DE));
				stmt1 = ir_add_stmt(bb, new_load(Size_I8, stmt2));
				ir_add_stmt(bb, new_set_reg(Size_I8, off_A, stmt1));
				printf("ld a, (de)");
				break;
			case 4:
				op16 = addr[pc++];
				op16 |= (addr[pc++] << 8);
				stmt1 = ir_add_stmt(bb, new_immediate(Size_I16, op16));
				stmt2 = ir_add_stmt(bb, new_get_reg(Size_I16, off_HL));
				ir_add_stmt(bb, new_store(Size_I16, stmt1, stmt2));
				printf("ld (0x%04x), hl", op16);
				break;
			case 5:
				op16 = addr[pc++];
				op16 |= (addr[pc++] << 8);
				stmt1 = ir_add_stmt(bb, new_immediate(Size_I16, op16));
				stmt2 = ir_add_stmt(bb, new_load(Size_I16, stmt1));
				ir_add_stmt(bb, new_set_reg(Size_I16, off_HL, stmt2));
				printf("ld hl, (0x%04x)", op16);
				break;
			case 6:
				op16 = addr[pc++];
				op16 |= (addr[pc++] << 8);
				stmt1 = ir_add_stmt(bb, new_immediate(Size_I16, op16));
				stmt2 = ir_add_stmt(bb, new_get_reg(Size_I8, off_A));
				ir_add_stmt(bb, new_store(Size_I8, stmt1, stmt2));
				printf("ld (0x%04x), a", op16);
				break;
			case 7:
				op16 = addr[pc++];
				op16 |= (addr[pc++] << 8);
				stmt1 = ir_add_stmt(bb, new_immediate(Size_I16, op16));
				stmt2 = ir_add_stmt(bb, new_load(Size_I8, stmt1));
				ir_add_stmt(bb, new_set_reg(Size_I8, off_A, stmt2));
				printf("ld a, (0x%04x)", op16);
				break;
			}
			break;
		case 3:
			reg = (b & 0x30) >> 4;
			stmt1 = ir_add_stmt(bb, new_get_reg(Size_I16, pairs[reg].off));
			stmt2 = ir_add_stmt(bb, new_immediate(Size_I16, 1));
			if (b&8) {
				stmt1 = ir_add_stmt(bb, new_alu(Size_I16, SUB, stmt1, stmt2));
				printf("dec %s", regs[(b >> 3) & 7].name);
			} else {
				stmt1 = ir_add_stmt(bb, new_alu(Size_I16, ADD, stmt1, stmt2));
				printf("inc %s", regs[(b >> 3) & 7].name);
			}
			ir_add_stmt(bb, new_set_reg(Size_I16, pairs[reg].off, stmt1));
			break;
		case 4:
			reg = (b >> 3) & 7;

			if (reg == REG_MEM) {
				stmt2 = ir_add_stmt(bb, new_get_reg(Size_I16, off_HL));
				stmt1 = ir_add_stmt(bb, new_load(Size_I8, stmt2));
			} else {
				stmt1 = ir_add_stmt(bb, new_get_reg(Size_I8, regs[reg].off));
			}
			stmt2 = ir_add_stmt(bb, new_immediate(Size_I8, 1));

			stmt1 = ir_add_stmt(bb, new_alu(Size_I8, ADD, stmt1, stmt2));

			ir_add_stmt(bb, new_set_reg(Size_I8, regs[reg].off, stmt1));

			printf("inc %s", regs[reg].name);
			break;
		case 5:
			reg = (b >> 3) & 7;

			if (reg == REG_MEM) {
				stmt2 = ir_add_stmt(bb, new_get_reg(Size_I16, off_HL));
				stmt1 = ir_add_stmt(bb, new_load(Size_I8, stmt2));
			} else {
				stmt1 = ir_add_stmt(bb, new_get_reg(Size_I8, regs[reg].off));
			}
			stmt2 = ir_add_stmt(bb, new_immediate(Size_I8, 1));

			stmt1 = ir_add_stmt(bb, new_alu(Size_I8, SUB, stmt1, stmt2));

			ir_add_stmt(bb, new_set_reg(Size_I8, regs[reg].off, stmt1));

			printf("dec %s", regs[reg].name);
			break;
		case 6:
			op8 = addr[pc++];
			reg = (b >> 3) & 7;
			stmt1 = ir_add_stmt(bb, new_immediate(Size_I8, op8));
			if (reg == REG_MEM) {
				stmt2 = ir_add_stmt(bb, new_get_reg(Size_I16, off_HL));
				ir_add_stmt(bb, new_store(Size_I8, stmt1, stmt2));
			} else {
				ir_add_stmt(bb, new_set_reg(Size_I8, regs[reg].off, stmt1));
			}
			printf("ld %s, 0x%02x", regs[reg].name, op8);
			break;
		default:
			goto undef;
		}
		break;
	case 0x40:
		reg = (b >> 3) & 7;
		reg2 = b & 7;
		if (reg == REG_MEM && reg2 == REG_MEM) {
			printf("!HALT"); // FIXME
			break;
		}
		if (reg2 == REG_MEM) {
			stmt2 = ir_add_stmt(bb, new_get_reg(Size_I16, off_HL));
			stmt1 = ir_add_stmt(bb, new_load(Size_I8, stmt2));
		} else {
			stmt1 = ir_add_stmt(bb, new_get_reg(Size_I8, regs[reg2].off));
		}

		if (reg == REG_MEM) {
			stmt2 = ir_add_stmt(bb, new_get_reg(Size_I16, off_HL));
			ir_add_stmt(bb, new_store(Size_I8, stmt2, stmt1));
		} else {
			ir_add_stmt(bb, new_set_reg(Size_I8, regs[reg].off, stmt1));
		}
		printf("ld %s, %s", regs[reg].name, regs[reg2].name);
		break;
	case 0x80:
		reg = b & 7;
		reg2 = (b >> 3) & 7;

		if (reg == REG_MEM) {
			stmt1 = ir_add_stmt(bb, new_get_reg(Size_I16, off_HL));
			stmt2 = ir_add_stmt(bb, new_load(Size_I8, stmt1));
		} else {
			stmt2 = ir_add_stmt(bb, new_get_reg(Size_I8, regs[reg].off));
		}
		stmt1 = ir_add_stmt(bb, new_get_reg(Size_I8, regs[REG_A].off));

		stmt1 = ir_add_stmt(bb, new_alu(Size_I8, alu_ops[reg2].off, stmt1, stmt2));

		ir_add_stmt(bb, new_set_reg(Size_I8, regs[REG_A].off, stmt1));

		printf("%s %s", alu_ops[reg2].name, regs[reg].name);
		break;
	case 0xc0:
		switch (b & 7) {
		case 6:
			op8 = addr[pc++];
			reg2 = (b >> 3) & 7;
			stmt2 = ir_add_stmt(bb, new_immediate(Size_I8, op8));
			stmt1 = ir_add_stmt(bb, new_get_reg(Size_I8, regs[REG_A].off));

			stmt1 = ir_add_stmt(bb, new_alu(Size_I8, alu_ops[reg2].off, stmt1, stmt2));

			ir_add_stmt(bb, new_set_reg(Size_I8, regs[REG_A].off, stmt1));

			printf("%s 0x%x", alu_ops[reg2].name, op8);
			break;
		default:
			goto undef;
		}
		break;
	}
	return pc;

undef:
	printf("!Undefined insn: 0x%02x", b);
	return pc;
}

struct IRs *parse(void *addr, unsigned long size) {
	target_ulong_t pc = 0; // FIXME
	struct IRs *bb = calloc(1, sizeof(struct IRs));

	while (pc < size) {
		printf("%02x  ", pc);
		pc = parse_insn(bb, addr, pc);
		printf("\n");
	}

	return bb;
}
