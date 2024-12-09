#include "../include/tokenlist.h"

const int NODESIZE = sizeof(Node);
const int TOKENLISTSIZE = sizeof(TOKENLIST);

char compareTokens(TOKEN* token1, const TOKEN* token2){
    //Sadece Return İle yaparsam sonucun hesaplanma süresi =  0.150000 seconds
    //IF ile yaparsam sonucun hesaplanma süresi =  0.180000 seconds
    return  (token1->type == token2->type) && 
            (strcmp(token1->text, token2->text) == 0) &&
            (token1->line == token2->line) &&
            (token1->character == token2->character); 
}

TOKENLIST* createTokenList(){
    TOKENLIST* list = (TOKENLIST*)malloc(TOKENLISTSIZE);
    list->head = NULL;
    list->size = 0;
    return list;
}

void insertAhead(TOKENLIST* list, const TOKEN* data){
    Node* newNode = (Node*)malloc(NODESIZE);
    TOKEN temp = *data; //tampon değişken
    newNode->index = 0;
    newNode->data = temp;
    newNode->next = list->head;

    Node* current = list->head; //yapılan değişiklikler sonrası list içinde index numaralarını güncelleme  
    while (current != NULL)
    {
        current->index++;
        current = current->next;
    }

    list->head = newNode;
    list->size++;
}

void insertTail(TOKENLIST* list, const TOKEN* data){
    Node* newNode = (Node*)malloc(NODESIZE);
    TOKEN temp = *data;
    newNode->data = temp;
    newNode->next = NULL;

    if(list->head == NULL){
        newNode->index = 0;
        list->head = newNode;
    } else {
        Node* currenElement = list->head;
        while (currenElement->next != NULL) {
            currenElement = currenElement->next;
        }
        newNode->index = list->size;
        currenElement->next = newNode;
    }
    list->size++;
}

void deleteNode(TOKENLIST* list, const TOKEN* data){
    Node* current = list->head;
    Node* previous = NULL; //silinecek elemandan önceki elemanı tutar;

    //Eleman Listenin Başındaysa
    if(current != NULL && compareTokens(&current->data, data)){
        list->head = current->next;
        free(current);
        list->size--;

        current = list->head;
        while (current != NULL)
        {
            current->index++;
            current = current->next;
        }
        return;
    }

    while (current != NULL && compareTokens(&current->data, data) != 0)
    {
        previous = current;
        current = current->next;
    }

    if(current == NULL) return; //Veri bulunamadığı anlamına geliyor.
    
    previous->next = current->next;
    free(current);
    list->size--;

    current = previous->next;
    while (current != NULL)
    {
        current->index++;
        current = current->next;    
    }
}

TOKEN* getTokenAt(TOKENLIST* list, size_t index){
    if(index >= list->size){
        printf("HATA: Stack OverFlow\n");
        return NULL;
    }

    Node* current = list->head;
    while (current != NULL && current->index != index){
        current = current->next;
    }
    return &current->data;
}

void printList(TOKENLIST* list){
    Node* current = list->head;
    printf("LIST:\n");
    while (current != NULL)
    {
        printf("VALUE => %d\n", current->data.value);
        current = current->next;
    }
    printf("NULL\n*************\n");
}

TOKEN* getListAsArray(TOKENLIST* list){
    TOKEN* dataArray = (TOKEN*)malloc(sizeof(TOKEN));
    Node* current = list->head;
    TOKEN temp;
    for(int i = 0; i < list->size && current != NULL; i++){
        temp = current->data;
        dataArray[i] = temp;
        current = current->next;
    }

    return dataArray;
}

void freeTokenList(TOKENLIST* list){
    while (list->head != NULL)
    {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
    }
    free(list);
}