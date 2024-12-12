#ifndef TOKEN_LIST
#define TOKEN_LIST

#include "maindatastructures.h"

char compareTokens(TOKEN*, const TOKEN*);//İki Token'ı birbiriyle karşılaştırarak birbirleridnen farklı olup olmadıkları bildiren fonksiyon
TOKENLIST* createTokenList();//Bir TOKENLIST oluşturan fonksiyon
void insertAhead(TOKENLIST*, const TOKEN*);//Bir Token'ı listenin başına ekleyen fonksiyon
void insertTail(TOKENLIST*, const TOKEN*);//Bir Token'ı listenin sonuna ekleyen fonksiyon
void deleteNode(TOKENLIST*, const TOKEN*); //Bir Token'ı listeden silen fonksiyon
TOKEN* getTokenAt(TOKENLIST*, size_t);//Bir listenin istenen indeksindeki Token'ı gösteren fonksiyon
void printList(TOKENLIST*);//Bir listenin içindeki değerleri yazdıran fonksiyon
TOKEN* getListAsArray(TOKENLIST*);//Bir listeyi bir sabit bir diziye dönüştüren fonksiyon
void freeTokenList(TOKENLIST*);//Oluşturulmuş olan Listi ve elemanlarını serbest bırakan fonksiyon

#endif