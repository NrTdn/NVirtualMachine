#ifndef TOKEN_LIST
#define TOKEN_LIST
#include "asmnlexer.h"
typedef struct Node{
    size_t index;//list'teki indeksi
    TOKEN data;
    struct Node* next;
} Node;

typedef struct TOKENLIST{
    Node* head;
    size_t size;
} TOKENLIST;

char compareTokens(TOKEN* token1, const TOKEN* token2);//İki Token'ı birbiriyle karşılaştırarak birbirleridnen farklı olup olmadıkları bildiren fonksiyon
TOKENLIST* createTokenList();//Bir TOKENLIST oluşturan fonksiyon
void insertAhead(TOKENLIST* list, const TOKEN* data);//Bir Token'ı listenin başına ekleyen fonksiyon
void insertTail(TOKENLIST* list, const TOKEN* data);//Bir Token'ı listenin sonuna ekleyen fonksiyon
void deleteNode(TOKENLIST* list, const TOKEN* data); //Bir Token'ı listeden silen fonksiyon
Node* getNodeAt(TOKENLIST* list, size_t index);//Bir listenin istenen indeksindeki Token'ı gösteren fonksiyon
void printList(TOKENLIST* list);//Bir listenin içindeki değerleri yazdıran fonksiyon
TOKEN* getListAsArray(TOKENLIST* list);//Bir listeyi bir sabit bir diziye dönüştüren fonksiyon
void freeTokenList(TOKENLIST* list);//Oluşturulmuş olan Listi ve elemanlarını serbest bırakan fonksiyon

#endif