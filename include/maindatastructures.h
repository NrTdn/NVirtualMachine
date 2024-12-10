#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_STACK_SIZE 1024
#define TRUE 1
#define FALSE 0
#define MAX_TOKEN_STACK_SIZE 128

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

typedef struct {
    INST_SET type;
    int line;
    int value;
} TOKEN;

typedef struct {
    INST_SET instruction;
    long value;
} BLOCK;

typedef struct {
    TOKEN tokenStack[MAX_TOKEN_STACK_SIZE];
    char* filePath;
} LEXER;

typedef struct Node{
    size_t index;//list'teki indeksi
    TOKEN data;
    struct Node* next;
} Node;

typedef struct TOKENLIST{
    Node* head;
    size_t size;
} TOKENLIST;

#endif