#ifndef NIM_H //header'ın birden fazla kez dahil edilmesini engeller
#define NIM_H

#include "maindatastructures.h"

#define DEF_INST_NOP {.type = INST_NOP}
#define DEF_INST_PUSH(x) {.type = INST_PUSH, .value = x}
#define DEF_INST_POP {.type = INST_POP}
#define DEF_INST_DUP {.type = INST_DUP}
#define DEF_INST_INDUP(i) {.type = INST_INDUP, .value = i}
#define DEF_INST_SWAP {.type = INST_SWAP}
#define DEF_INST_INSWAP(i) {.type = INST_INSWAP, .value = i}
#define DEF_INST_ADD {.type = INST_ADD}
#define DEF_INST_SUB {.type = INST_SUB}
#define DEF_INST_MUL {.type = INST_MUL}
#define DEF_INST_MOD {.type = INST_MOD}
#define DEF_INST_DIV {.type = INST_DIV}
#define DEF_INST_CMPE {.type = INST_CMPE}
#define DEF_INST_CMPNE {.type = INST_CMPNE}
#define DEF_INST_CMPG {.type = INST_CMPG}
#define DEF_INST_CMPL {.type = INST_CMPL}
#define DEF_INST_CMPGE {.type = INST_CMPGE}
#define DEF_INST_CMPLE {.type = INST_CMPLE}
#define DEF_INST_JMP(i) {.type = INST_JMP, .value = i}
#define DEF_INST_ZJMP(i) {.type = INST_ZJMP, .value = i}
#define DEF_INST_NZJMP(i) {.type = INST_NZJMP, .value = i}
#define DEF_INST_PRINT {.type = INST_PRINT}
#define DEF_INST_HALT {.type = INST_HALT}

void push(Machine*, int);
int pop(Machine*);
void index_swap(Machine*, int);
void index_dup(Machine*, int);
void print_stack(Machine*);
extern void write_program_to_file(Machine*, char*);
extern Machine* read_program_file(Machine*, char*);
void run_program(Machine*);
int main();

#endif