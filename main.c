#include <stdio.h>
#include <stdlib.h>
#include "./include/asmnlexer.h"

#define PROGRAM_SIZE sizeof(program)/sizeof(program[0])

Inst program[] = {
    DEF_INST_PUSH(1),
    DEF_INST_PUSH(4),
    DEF_INST_PUSH(6),
    DEF_INST_PUSH(8),
    DEF_INST_PUSH(10),
    DEF_INST_PUSH(12),
    DEF_INST_PUSH(14),
    DEF_INST_INDUP(2)
};

void write_program_to_file_bytes(Machine* machine, char* file_path) {
    FILE* file = fopen(file_path, "wb");
    if(file == NULL) {
        fprintf(stderr, "Bu dosyaya yazma işlemi gerçekleştirilemiyor => %s\n", file_path);
        exit(1);
    }

    fwrite(machine->Instructions, sizeof(machine->Instructions[0]), PROGRAM_SIZE, file);
    fclose(file);
}

Machine* read_program_file_bytes(Machine* machine, char* file_path){
    FILE* file = fopen(file_path, "rb");
    if(file == NULL){
        fprintf(stderr, "Bu dosyada okuma işlemi gerçekleştirilemiyor => %s\n", file_path);
        exit(1);
    }

    printf("BURADAYIZ\n");

    Inst* instructions = malloc(sizeof(Inst) * MAX_STACK_SIZE);

    fseek(file, 0, SEEK_END);//dosyanın akışı sonda kaldı.
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);//tekrar doğru bir şekilde okunması için akışı dosyanın başına getirir
    fread(instructions, sizeof(instructions[0]), length / INST_SIZE, file);

    machine->program_size = length / INST_SIZE;
    machine->Instructions = instructions;

    fclose(file);
    return machine;
}

int main(){ 
    LEXER* lex= (LEXER*)malloc(sizeof(LEXER));
    if(lex == NULL){
        fprintf(stderr, "HATA: Bellek ayirmada problem yasandi.\n");
        exit(1);
    }
    lex->filePath = "C:\\Users\\HelyakX\\Desktop\\Visual Studio Code\\C\\NVM\\test.asmn";
    Machine* loadedMachine =  lexer(lex);
    printf("Makine olusturuldu.\n");
    run_program(loadedMachine);
    print_stack(loadedMachine);

    write_program_to_file_bytes(loadedMachine, "test.nvm");
    read_program_file_bytes(loadedMachine, "test.nvm");

    free(loadedMachine->Instructions);
    free(loadedMachine);
    free(lex->filePath);
    free(lex);
    return 0;
}