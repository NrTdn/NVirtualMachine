#include <stdio.h>
#include <stdlib.h>
#include "./include/asmnlexer.h"
#include "./include/nvm.h"

extern char* SETS[]; 

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

#define PROGRAM_SIZE sizeof(program)/sizeof(program[0])

void push(Machine* machine, int value) {
    if(machine->stack_size >= MAX_STACK_SIZE){
        fprintf(stderr, "Error: Stack Overflow\n");
        exit(1);
    }
    machine->stack[machine->stack_size] = value;
    machine->stack_size++;
}

int pop(Machine* machine){
    if(machine->stack_size <= 0) {
        fprintf( stderr, "Error: Stack Underflow\n");
        exit(1);
    }
    machine->stack_size--;
    return machine->stack[machine->stack_size];
}

void index_swap(Machine* machine, int index){
    if(index >= machine->stack_size || index < 0){
        fprintf(stderr, "Error: Index out of range\n");
        exit(1);
    }

    int temp_value = machine->stack[index];
    machine->stack[index] = pop(machine);
    push(machine, temp_value);
}

void index_dup(Machine* machine, int index){
    if(index >= machine->stack_size || index < 0){
        fprintf(stderr, "Error: Index out of range\n");
        exit(1);
    }

    push(machine, machine->stack[index]);

}

void print_stack(Machine* machine){
    printf("Stack:\n");
    for(int i = machine->stack_size - 1; i >= 0; i--) {
        printf("# %d\n", machine->stack[i]);
    }
    printf("*************\n");
}

void write_program_to_file(Machine* machine, char* file_path) {
    FILE* file = fopen(file_path, "wb");
    if(file == NULL) {
        fprintf(stderr, "Bu dosyaya yazma işlemi gerçekleştirilemiyor => %s\n", file_path);
        exit(1);
    }

    fwrite(machine->Instructions, sizeof(machine->Instructions[0]), PROGRAM_SIZE, file);

    fclose(file);
}

Machine* read_program_file(Machine* machine, char* file_path){
    FILE* file = fopen(file_path, "rb");
    if(file == NULL){
        fprintf(stderr, "Bu dosyada okuma işlemi gerçekleştirilemiyor => %s\n", file_path);
        exit(1);
    }

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

void run_program(Machine* machine){
    int a, b;
    for(size_t ip = 0; ip < machine->program_size; ip++){
        switch (machine->Instructions[ip].type)    
        {
            case INST_NOP:
                continue;
            break;
            
            case INST_PUSH:
                push(machine, machine->Instructions[ip].value);
            break;

            case INST_POP:
                pop(machine);
            break;

            case INST_DUP:
                a = pop(machine);
                push(machine, a);
                push(machine, a);
            break;

            case INST_INDUP:
                index_dup(machine, machine->Instructions[ip].value);
            break;

            case INST_SWAP:
                a = pop(machine);
                b = pop(machine);
                push(machine, a);
                push(machine, b);
            break;

            case INST_INSWAP:
                index_swap(machine, machine->Instructions[ip].value);
            break;

            case INST_ADD:
                a = pop(machine);
                b = pop(machine);
                push(machine, a + b);
            break;  

            case INST_SUB:
                a = pop(machine);
                b = pop(machine);
                push(machine, a - b);
            break;

            case INST_MUL:
                a = pop(machine);
                b = pop(machine);
                push(machine, a * b);
            break;

            case INST_MOD:
            a = pop(machine);
            b = pop(machine);
            push(machine, a % b);
            break;

            case INST_DIV:
                a = pop(machine);
                b = pop(machine);
                if(b == 0){
                    fprintf(stderr, "Error: Bolen 0 Olamaz\n");
                    exit(1);
                }
                push(machine, a / b);
            break;

            case INST_CMPE:
                a = pop(machine);
                b = pop(machine);
                push(machine, b);
                push(machine, a);
                if (a == b) push(machine, 1);
                else push(machine, 0);
                
            break;

            case INST_CMPNE:
                a = pop(machine);
                b = pop(machine);
                push(machine, b);
                push(machine, a);
                if (a != b) push(machine, 1);
                else push(machine, 0);
            break;

            case INST_CMPG:
                a = pop(machine);
                b = pop(machine);
                push(machine, b);
                push(machine, a);
                if (a > b) push(machine, 1);
                else push(machine, 0);
            break;

            case INST_CMPL:
                a = pop(machine);
                b = pop(machine);
                push(machine, b);
                push(machine, a);
                if (a < b) push(machine, 1);
                else push(machine, 0);
            break;

            case INST_CMPGE:
                a = pop(machine);
                b = pop(machine);
                push(machine, b);
                push(machine, a);
                if (a >= b) push(machine, 1);
                else push(machine, 0);
            break;

            case INST_CMPLE:
                a = pop(machine);
                b = pop(machine);
                push(machine, b);
                push(machine, a);
                if (a <= b) push(machine, 1);
                else push(machine, 0);
            break;

            case INST_JMP:
                ip = machine->Instructions[ip].value - 1;
                if(ip + 1 >= machine->program_size){
                        fprintf(stderr, "Error: Cannot Jump Out Of Bounds\n");
                        exit(1);
                    }
            break;

            case INST_ZJMP:
                if (pop(machine) ==  0) {
                    ip = machine->Instructions[ip].value - 1;
                    if(ip + 1 >= machine->program_size){
                        fprintf(stderr, "Error: Cannot Jump Out Of Bounds\n");
                        exit(1);
                    }
                }
                else continue;
            break;

            case INST_NZJMP:
                if (pop(machine) != 0) {
                    ip = machine->Instructions[ip].value - 1;
                    if(ip + 1 >= machine->program_size){
                        fprintf(stderr, "Error: Cannot Jump Out Of Bounds\n");
                        exit(1);
                    }
                }
                else continue;
            break;

            case INST_PRINT:
                printf("%d\n", pop(machine));
            break;

            case INST_HALT:
                ip = machine->program_size;
            break;

            case INST_FAIL:
                fprintf(stderr, "Program Failed\n");
                exit(0);
            break; 

            default:
                printf("default");
            break;
        }
    }
}

int main(){ 
    LEXER* lex= (LEXER*)malloc(sizeof(LEXER));
    if(lex == NULL){
        fprintf(stderr, "HATA: Bellek ayirmada problem yasandi.\n");
        exit(1);
    }
    lex->filePath = "C:\\Users\\HelyakX\\Desktop\\Visual Studio Code\\C\\NVM\\test.asmn";
    lexer(lex);
    Machine* loaded_machine = malloc(sizeof(Machine));

    loaded_machine->Instructions = program; 
    write_program_to_file(loaded_machine, "test.nvm");
    loaded_machine  = read_program_file(loaded_machine, "test.nvm");

    run_program(loaded_machine);
    print_stack(loaded_machine);
    
    return 0;
}