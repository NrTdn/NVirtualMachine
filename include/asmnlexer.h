#ifndef ASMNLEXER_H
#define ASMNLEXER_H

#include "nvm.h"

#define TRUE 1
#define FALSE 0

typedef struct {
    INST_SET type;
    char* text;
    int line;
    int character;  
} TOKEN;

typedef struct {
    INST_SET instruction;
    long value;
} BLOCK;

extern char* SETS[];

char* open_file(char* file_path, int *length);//Dosyayı bir string dizisine çevirecek olan fonksiyon.
int sizeOfStr(char* str);//Stringlerin(char* şeklinde olan) boyutunu hesaplayacak olan fonksiyon.
void removeNewLineChar(char* str);//Satır içinde '\n' karakterini temizleyerek derlemede hata almamamızı sağlayacak olan fonksiyon
char** SplitLine(char* buffer);//Bir Satırı boşluklara göre ayırır.
int convertStrToInt(char* str);//Bir stringi uygun olması durumnda int değere dönüştürecek olan fonksiyon
INST_SET getInst(int theIndex);//Girilen indeksteki instruction'ı gösterecek olan fonksiyon
INST_SET CheckSuitibility(char* buffer, int length);//Bir satırı söz dizimi bakımından uygunluğunu bildirecek olan fonksiyon
TOKEN* InitializeToken(BLOCK* block);//Bir Token oluşturacak olan fonksiyon
BLOCK* InitializeBlock(char* buffer, int length);//Bir Block oluşturacak olan fonksiyon.
int generateKeyWord(char* current, int currentIndex, int line, int character);
Inst generateProgram(TOKEN* tokens);
int lexer();
#endif 