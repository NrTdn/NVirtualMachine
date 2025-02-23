#include "../include/nvm.h"

extern char* SETS[]; 



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
                exit(1);
            break; 

            default:
                printf("default\n");
            break;
        }
    }
}