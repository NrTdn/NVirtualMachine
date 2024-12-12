#ifndef ASMNLEXER_H
#define ASMNLEXER_H

#include "nvm.h"
#include "tokenlist.h"

extern char* SETS[];

char* open_file(char*, int *);//Dosyayı bir string dizisine çevirecek olan fonksiyon.
int sizeOfStr(char*);//Stringlerin(char* şeklinde olan) boyutunu hesaplayacak olan fonksiyon.
void removeNewLineChar(char*);//Satır içinde '\n' karakterini temizleyerek derlemede hata almamamızı sağlayacak olan fonksiyon
char** SplitLine(char*);//Bir Satırı boşluklara göre ayırır.
int convertStrToInt(char*);//Bir stringi uygun olması durumnda int değere dönüştürecek olan fonksiyon
INST_SET getInst(int);//Girilen indeksteki instruction'ı gösterecek olan fonksiyon
INST_SET CheckSuitibility(char*, int);//Bir satırı söz dizimi bakımından uygunluğunu bildirecek olan fonksiyon
TOKEN* InitializeToken(BLOCK*);//Bir Token oluşturacak olan fonksiyon
BLOCK* InitializeBlock(char*, int);//Bir Block oluşturacak olan fonksiyon.
Machine* generateMachine(TOKENLIST*);//Machine struct'ına yüklenecek olan instructions'ları üretir.
Machine* lexer(LEXER*);
#endif 