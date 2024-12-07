#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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
    char* tempBuffer = buffer;
    char* inst = strtok(buffer, " ");
    if(inst == NULL){
        printf("HATA: Satir Dogru Bir Sekilde Bolunemedi.\n");
        return NULL;
    }
    printf("inst değeri => %s\n", inst);
    char* value = strtok(NULL, "\n");
    printf("value değeri => %s\n", value);
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
            return INST_NOP; break;
        case 1:
            return INST_PUSH; break;
        case 2:
            return INST_POP; break;
        case 3:
            return INST_DUP; break;
        case 4:
            return INST_INDUP; break;
        case 5: 
            return INST_SWAP; break;
        case 6:
            return INST_INSWAP; break;
        case 7:
            return INST_ADD; break;
        case 8:
            return INST_SUB; break;
        case 9:
            return INST_MUL; break;
        case 10: 
            return INST_MOD; break;
        case 11:
            return INST_DIV; break;
        case 12:
            return INST_CMPE; break;
        case 13:
            return INST_CMPNE; break;
        case 14:
            return INST_CMPG; break;
        case 15:
            return INST_CMPL; break;
        case 16:
            return INST_CMPGE; break;
        case 17:
            return INST_CMPLE; break;
        case 18:
            return INST_JMP; break;
        case 19:
            return INST_ZJMP; break;
        case 20:
            return INST_NZJMP; break;
        case 21:
            return INST_PRINT; break;
        case 22:
            return INST_HALT; break;
        case 23:
            return INST_FAIL; break;
        default:
            printf("HATA: Boyle Bir Inst Bulunmamaktadir.\n");
            return INST_FATAL_ERROR;
            break;
    }
}

INST_SET CheckSuitibility(char* buffer, int length){
    char controller = 0;
    char* tempBuffer = (char*)malloc(sizeof(char) * 8);
    char tempChar = 0;
    int theIndex = 0;

    printf("Karsilastirmak icin inst => %s\n", buffer);

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
            return INST_FAIL;
            break;
    }
}

TOKEN* InitializeToken(BLOCK* block){

    return NULL;
}

BLOCK* InitializeBlock(char* buffer, int length){
    char** splittedLine =  SplitLine(buffer);
    BLOCK* block = (BLOCK*)malloc(sizeof(BLOCK));
    if(splittedLine == NULL){
        printf("HATA: Blok Olusturulamadi. => Söz Dizimi Hatasi\n");
        return block;
    }
    char* instText  = splittedLine[0];
    INST_SET inst = CheckSuitibility(instText, sizeOfStr(instText));
    if(inst == INST_PUSH) printf("PUSH TALEBİ YAPILDI.\n");
    block->instruction = inst;
    block->value = convertStrToInt(splittedLine[1]);

    printf("block INST => %d\n", block->instruction);
    printf("block value => %d\n", block->value);

    return block;
}

int generateKeyWord(char* current, int currentIndex, int line, int character){
    char* keywordName = {0};
    int keywordLength = 0;
    while (isalpha(current[currentIndex]))
    {
        keywordName[keywordLength] = current[currentIndex];
        currentIndex++;
        keywordLength++;
    }
    
    InitializeToken;
    int current_Index;
}

Inst generateProgram(TOKEN* tokens){

}

int lexer(){
    int length;
    char* current = open_file("C:\\Users\\HelyakX\\Desktop\\Visual Studio Code\\C\\NVM\\test.asmn", &length);

    int currentIndex = 0;

    int line = 0;
    int character = 0;
    char* tempBuffer = current;
    char* blockBuffer = (char*)malloc(sizeof(char) * 32);
    int i = 0;

    BLOCK* block = (BLOCK*)malloc(sizeof(BLOCK));

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
            buffer = blockBuffer;
            printf("Blokta yapilacaklar => %s\n", buffer);
            block = InitializeBlock(buffer, bufferSize);
            memset(blockBuffer, 0, sizeof(char) * 32);
        }
        currentIndex++;
    }
    
    return 0;
}