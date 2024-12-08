#ifndef NIM_H //header'ın birden fazla kez dahil edilmesini engeller
#define NIM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_STACK_SIZE 1024

typedef enum { // Instruction Set => Talimat Seti
    INST_NOP = 0,
    INST_PUSH,
    INST_POP,
    INST_DUP,
    INST_INDUP,
    INST_SWAP,
    INST_INSWAP,
    INST_ADD,
    INST_SUB,
    INST_MUL,
    INST_MOD,
    INST_DIV,
    INST_CMPE, //Açılım => Compare Equal
    INST_CMPNE, //Açılım => Compare Not Equal
    INST_CMPG, //Açılım => Compare Greater
    INST_CMPL, //Açılım => Compare Less
    INST_CMPGE, //Açılım => Compare Greater Equal
    INST_CMPLE, //Açılım => Compare Less Equal
    INST_JMP, // Döngüler için kullanılabilir.
    INST_ZJMP, //Açılım => Zero Jump
    INST_NZJMP, //Açılım => Non Zero Jump
    INST_PRINT,
    INST_HALT,
    INST_FAIL,
    INST_NULL//Dönüş Değeri INST_SET olan fonksiyonlarda NULL döndürerek bir hata meydana geldiğini bildirdiğim fonksiyonlarda kullanıcam. 
} INST_SET;

typedef struct {
    INST_SET type;
    int value;
} Inst;

#define INST_SIZE sizeof(Inst)

typedef struct{
    int stack[MAX_STACK_SIZE];
    int stack_size;
    int program_size;
    Inst* Instructions;
} Machine;

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

void push(Machine* machine, int value);
int pop(Machine* machine);
void index_swap(Machine* machine, int index);
void index_dup(Machine* machine, int index);
void print_stack(Machine* machine);
void write_program_to_file(Machine* machine, char* file_path);
Machine* read_program_file(Machine* machine, char* file_path);
void run_program(Machine* machine);
int main();

#endif