#ifndef ASMNLEXER_H
#define ASMNLEXER_H

#include "nvm.h"
#include "tokenlist.h"

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
Machine* generateMachine(TOKENLIST* tokenList);//Machine struct'ına yüklenecek olan instructions'ları üretir.
Machine* lexer(LEXER* lex);
#endif 