#include <ctype.h> //isalpha func
#include "../include/asmnlexer.h"

char* SETS[] = { //23 eleman
    "NOP",
    "PUSH",
    "POP",
    "DUP",
    "INDUP",
    "SWAP",
    "INSWAP",
    "ADD",
    "SUB",
    "MUL",
    "MOD",
    "DIV",
    "CMPE",
    "CMPNE",
    "CMPG",
    "CMPL",
    "CMPGE",
    "CMPLE",
    "JMP",
    "ZJMP",
    "NZJMP",
    "PRINT",
    "HALT",
    "FAIL"
};

TOKEN* Tokens = {0};

const int SET_SIZE = 24;

char* open_file(char* file_path, int* length){
    FILE* file = fopen(file_path, "r");
    if(!file){
        fprintf(stderr, "Hata: Dosya açılamadı => %s\n", file_path);
        exit(1);
    }
    char* current = {0};

    fseek(file, 0, SEEK_END);
    *length = ftell(file);
    fseek(file, 0, SEEK_SET);

    current = malloc(sizeof(char) * *length);
    if(!current){
        fprintf(stderr, "HATA: Dosya okunurken hata meydana geldi.\n");
        exit(1);
    }
    fread(current, 1, *length, file);
    
    fclose(file);
    free(file);
    return current;
}

int sizeOfStr(char* str){
    int offset = 0;
    int size = 0;

    while (*(str + offset) != '\0'){
        ++size;
        ++offset;
    }
    return size;
}

void removeNewLineChar(char* str){
    char* newStr = strtok(str, "\n");
    if(newStr != NULL) strcpy(str, newStr);
}

char** SplitLine(char* buffer){
    removeNewLineChar(buffer);
    char** resultArray = (char**)malloc(sizeof(char*) * 2);
    if(resultArray == NULL){
        fprintf(stderr, "HATA: Bellek ayirilirken problem yasandi. => resultArray\n");
        exit(1);
    }

    char* tempBuffer = buffer;
    printf("BUFFER KARDAS => %s\n", tempBuffer);
    char* inst = strtok(buffer, " ");
    if(inst == NULL){
        printf("HATA: Satir Dogru Bir Sekilde Bolunemedi.\n");
        return NULL;
    }
    //printf("inst değeri => %s\n", inst);
    char* value = strtok(NULL, "\n");
    if(value == NULL){
        printf("HATA: Satir Dogru Bir Sekilde Bolunemedi.\n");
        return NULL;
    }
    //printf("value değeri => %s\n", value);
    /*
        PUSH 27
        stringini girersek bunu önce boşluğa göre ayırır ve PUSH inst değişkenine atanır.
        Stringde "27" kalır. Bundan sonrada \n karakterinin arar. Bulursa zaten "27" döndürür.
        Eğer bulamazsa kalan stringi döndürür yani yine "27" değerini döndürür.
        Ancak 27den sonra farklı bir ifade varsa yani PUSH 27 31 olursa çalışmaz. Çünkü value değişkenine 
        27 31 değişkenini atar. Bu da hatalara yol açar kodumuzda.
    */
    int sizeofValue = sizeOfStr(value);
    char tempChar = 0;
    for(int i = 0; i < sizeofValue; i++){
        tempChar = value[i];
        if(tempChar != ';'){
            if(!isdigit(tempChar)){
                printf("HATA: Yanlis Soz Dizimi => Birden fazla değer girilmiş.\n");
                return NULL;
            }
        }
    }

    resultArray[0] = inst;
    resultArray[1] = value;
    return resultArray;
}

int convertStrToInt(char* str){
    int convertedInt;
    if(sscanf(str, "%d", &convertedInt) == 1) return convertedInt;
    return 0;
}

INST_SET getInst(int theIndex){
    switch (theIndex)
    {
        case 0:
            printf("INST_NOP\n"); return INST_NOP;  
            break;
        case 1:
            printf("INST_PUSH\n"); return INST_PUSH; break;
        case 2:
            printf("INST_POP\n"); return INST_POP; break;
        case 3:
            printf("INST_DUP\n"); return INST_DUP; break;
        case 4:
            printf("INST_INDUP\n"); return INST_INDUP; break;
        case 5: 
            printf("INST_SWAP\n"); return INST_SWAP; break;
        case 6:
            printf("INST_INSWAP\n"); return INST_INSWAP; break;
        case 7:
            printf("INST_ADD\n");return INST_ADD; break;
        case 8:
            printf("INST_SUB\n"); return INST_SUB; break;
        case 9:
            printf("INST_MUL\n"); return INST_MUL;  break;
        case 10: 
            printf("INST_MOD\n"); return INST_MOD; break;
        case 11:
            printf("INST_DIV\n"); return INST_DIV; break;
        case 12:
            printf("INST_CMPE\n"); return INST_CMPE; break;
        case 13:
            printf("INST_CMPNE\n"); return INST_CMPNE; break;
        case 14:
            printf("INST_CMPG\n"); return INST_CMPG; break;
        case 15:
            printf("INST_CMPL\n"); return INST_CMPL; break;
        case 16:
            printf("INST_CMPGE\n"); return INST_CMPGE; break;
        case 17:
            printf("INST_CMPLE\n"); return INST_CMPLE; break;
        case 18:
            printf("INST_JMP\n"); return INST_JMP; break;
        case 19:
            printf("INST_ZJMP\n"); return INST_ZJMP; break;
        case 20:
            printf("INST_NZJMP\n"); return INST_NZJMP; break;
        case 21:
            printf("INST_PRINT\n"); return INST_PRINT; break;
        case 22:
            printf("INST_HALT\n"); return INST_HALT; break;
        case 23:
            printf("INST_FAIL\n"); return INST_FAIL; break;
        default:
            printf("HATA: Boyle Bir Inst Bulunmamaktadir.\n");
            return INST_NULL;
            break;
    }
    return INST_NULL;
}

INST_SET CheckSuitibility(char* buffer, int length){ //Eğer uygunsa instruction'ı döndürür, değilse FATAL ERROR döndürür.
    char controller = 0;
    char* tempBuffer = (char*)malloc(sizeof(char) * 8);
    if(tempBuffer == NULL){
        fprintf(stderr, "HATA: Bellek ayirilirken problem yasandi. => tempBuffer\n");
        exit(1);
    }
    char tempChar = 0;
    int theIndex = 0;

    for (int i = 0; i < SET_SIZE; i++)
    {
        if(strcmp(buffer, SETS[i]) == 0){
            controller++;
            theIndex = i;
        }
    }
    char result = ((char)(controller == 1)) ? TRUE : FALSE;
    switch (result)
    {
        case TRUE:
            return getInst(theIndex);
            break;
        case FALSE:
            return INST_FAIL;
            break;
        default:
            return INST_NULL;
            break;
    }

    free(tempBuffer);
    return INST_NULL;
}

TOKEN* InitializeToken(BLOCK* block){
    TOKEN* token = (TOKEN*)malloc(sizeof(TOKEN));
    if(token == NULL){
        fprintf(stderr, "HATA: Bellek ayirilirken problem yasandi. => token\n");
        exit(1);
    }
    token->type = block->instruction;
    token->value = block->value;
    return token;
}

BLOCK* InitializeBlock(char* buffer, int length){
    char** splittedLine =  SplitLine(buffer);//temizlenmesi gerek

    BLOCK* block = (BLOCK*)malloc(sizeof(BLOCK));
    if(splittedLine == NULL){
        printf("HATA: Blok Olusturulamadi. => Söz Dizimi Hatasi\n");
        return block;
    }

    char* instText  = splittedLine[0];
    INST_SET inst = CheckSuitibility(instText, sizeOfStr(instText));
    if(inst == INST_NULL){
        fprintf(stderr, "HATA: Block olusturulamadi.\n");
        return NULL;
    }
    block->instruction = inst;
    block->value = convertStrToInt(splittedLine[1]);

    free(splittedLine);
    return block;
}

Machine* generateMachine(TOKENLIST* tokenList){
    int tokenSize = tokenList->size;
    Inst* program = (Inst*)malloc(INST_SIZE * tokenSize);
    if(program == NULL){
        fprintf(stderr, "HATA: Bellek ayirilirken problem yasandi. => program\n");
        exit(1);
    }
    Machine* machine = (Machine*)malloc(sizeof(Machine));
    if(machine == NULL){
        fprintf(stderr, "HATA: Bellek ayirilirken problem yasandi. => machine\n");
        exit(1);
    }
    
    int programSize = 0;

    for(int i = 0; i < tokenSize; i++){
        Inst instruction;
        TOKEN token = *getTokenAt(tokenList, i);
        instruction.type = token.type;
        instruction.value = token.value;
        printf("INSTRUCTION TYPE => %d :: VALUE => %d\n", instruction.type, instruction.value);
        
        program[i] = instruction;
        programSize++;
    }

    machine->Instructions = program;
    machine->program_size = programSize;

    return machine;
}

Machine* lexer(LEXER* lex){
    TOKENLIST* tokenList = createTokenList();

    int length;
    char* current = open_file(lex->filePath, &length);

    int currentIndex = 0;

    int line = 0;
    char* tempBuffer = current;
    char* blockBuffer = (char*)malloc(sizeof(char) * 32);
    if(blockBuffer == NULL){
        fprintf(stderr, "HATA: Bellek ayirmada problem yasandi. => blockBuffer\n");
        exit(1);
    }
    memset(blockBuffer, 0, sizeof(char) * 32);
    int i = 0;

    int blockCount = 0;
    BLOCK* block = (BLOCK*)malloc(sizeof(BLOCK));
    if(block == NULL){
        fprintf(stderr, "HATA: Bellek ayirmada problem yasandi. => block\n");
        exit(1);
    }

    while (currentIndex <= length)
    {
        char currentChar = tempBuffer[currentIndex];
        if(currentChar != ';'){
            if(currentChar == '\n') line++;
            blockBuffer[i] = currentChar;
            i++;
        } else {
            int bufferSize = i;
            i = 0;
            char* buffer = (char*)malloc(bufferSize);
            if(buffer == NULL){
                fprintf(stderr, "HATA: Bellek ayirmada problem yasandi. => buffer\n");
                exit(1);
            }
            buffer = blockBuffer;

            block = InitializeBlock(buffer, bufferSize);
            if(block == NULL) {
                fprintf(stderr, "HATA: Block olusturulamadi.\n");
                exit(1);
            }
            blockCount++;
            TOKEN* token =  InitializeToken(block);
            memset(blockBuffer, 0, sizeof(char) * 32);
            memset(buffer, 0, bufferSize);
            memset(block, 0, sizeof(BLOCK));
            insertTail(tokenList, token);
        }
        currentIndex++;
    }

    Machine* machine =  generateMachine(tokenList);

    printList(tokenList);

    printf("GENERATING THE PROGRAM::::::\n");
    printf("::::::\n");
    
    free(current);
    free(blockBuffer);
    free(tempBuffer);
    free(block);

    freeTokenList(tokenList);

    return machine;
}