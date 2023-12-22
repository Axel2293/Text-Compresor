#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../include/HuffmanTree.h"


//Two types of nodes, father and symbols
    // Father has the symbol char at NULL and has the sum
    //  of the frequency of the left and right side

struct node{
    char symbol;
    int freq;

    struct node * left;
    struct node * right;
}node;

struct FreqAnchor{
    struct node * current;
    struct FreqAnchor * next;
}FreqAnchor;


struct Frequency{
    struct FreqAnchor * first;
    struct FreqAnchor * last;
    size_t len;
}repset;

struct Tree{
    struct node * root;
};

freq FreqCount(string data, size_t lenght);
int IsInNode(char symbol, freq fq );
struct FreqAnchor * GetAnchorAtIndex(int indx, freq);
void printFreq(freq fq);
void sort(freq);
void insertNode(freq fq, struct node * new);
struct node * pop(freq fq);


freq FreqCount(string data, size_t lenght){
    
    freq fq = malloc(sizeof(struct Frequency));
    fq->first=NULL;
    fq->last =NULL;
    fq->len =0;


    for (size_t i = 0; i < lenght-1; i++)
    {
        int indx = IsInNode(*data, fq);
        if (indx!=-1)
        {
            //printf("The \"%d-%c\" symbol is already in a node, adding 1 to count\n", *data, *data);
            struct FreqAnchor * look = GetAnchorAtIndex(indx, fq); 
            look->current->freq++;
            //printf("\tAdded one count to symbol %c\n", look->current->symbol);
            //printf("\tCurrent count: %d\n", look->current->freq);          
        }
        else{
            //printf("Symbol not in node \"%d-%c\" \n", *data, *data);
            // Allocate the respective mem for new anchor and node
            struct FreqAnchor * fa = malloc(sizeof(struct FreqAnchor));
            struct node * nd = malloc(sizeof(struct node));

            //Initialize node
            nd->symbol=*data;
            nd->freq=1;
            //Initialize anchor
            fa->current=nd; 
            fa->next=NULL;

            
            //Means structure is empty
            if (fq->first == NULL)
            {
                fq->first = fa;
                fq->last =fa;
                fq->len++;
            }
            else{
                //New node becomes next of old last
                fq->last->next = fa;
                //New node becomes new last;
                fq->last=fa;
                fq->len++;
                
            }
        }
        //Move to next symbol
        data++;
    }
    return fq;
}


int IsInNode(char symbol, freq fq ){
    
    if (fq->len>0)
    {
        struct FreqAnchor * look = fq->first;
        for (size_t i = 0; i < fq->len; i++)
        {
            struct node * nd = look->current;
            if (nd->symbol == symbol)
            {
                return i;
            }else{
                if (look->next !=NULL)
                {
                    look = look->next;
                }else return -1;
            }
        }
    }else{
        return -1;
    }
    
    
}
struct FreqAnchor * GetAnchorAtIndex(int indx, freq fq){
    if (fq->len >0 && fq->len>=indx+1)
    {
        struct FreqAnchor * look = fq->first;

        for (size_t i = 0; i < fq->len; i++)
        {
            //Already found the anchor
            if (i == indx)
            {
                return look;
            }
            // move to next anchor
            look = look->next;
        }   
    }
}



void printFreq(freq fq){
    if (fq->len >0)
    {
        struct FreqAnchor * look = fq->first;
        for (size_t i = 0; i < fq->len; i++)
        {
            struct node * symbol = look->current;
            printf("Symbol: \"%d-%c\" with Frequency: %d \n", symbol->symbol, symbol->symbol, symbol->freq);
            if (look->next!=NULL)
            {
                look = look->next;
            }else break;
            
        }
    }
    else{
        printf("Frequency structure is empty\n");
    }   
}

void sort(freq fq){
    for (size_t i = 0; i < fq->len; i++)
    {
        struct FreqAnchor * fa = fq->first;
        struct node * nd = fa->current;
        for (size_t i = 0; i < (fq->len)-1; i++)
        {
            if (nd->freq > fa->next->current->freq)
            {   
                //Swap data
                char tempSymbol = nd->symbol;
                int tempFreq = nd->freq;
                
                nd->freq = fa->next->current->freq;
                nd->symbol = fa->next->current->symbol;

                fa->next->current->freq = tempFreq;
                fa->next->current->symbol = tempSymbol;
            }
            //Move to next element
            fa = fa->next;
            nd=fa->current;
            
        }
        
    }
    
}

// Gets the first node at the array (Lowest frequency)
struct node * pop(freq fq){
    if (fq->first!=NULL)
    {
        struct FreqAnchor * temp = fq->first;
        fq->first=temp->next;
        struct node * nd = temp->current;
        free(temp);
        fq->len--;
        printf("\t\t\t\t\t\t\tNODE POP HAS %c\n", nd->symbol);
        return nd;
    }else return NULL;
}

void insertNode(freq fq, struct node * new){
    if (fq!=NULL && new!=NULL)
    {
        if (fq->len>0)
        {
            struct FreqAnchor * fa = fq->first;
            while (fa->next != NULL && fa->next->current->freq < new->freq)
            {
                fa = fa->next;
            }
            struct FreqAnchor * newAnchor= malloc(sizeof(struct FreqAnchor));
            newAnchor->current = new;
            newAnchor->next = fa->next;
            fa->next = newAnchor;
            fq->len++;
        }
        //Array is empty
        else
        {
            struct FreqAnchor * newAnchor= malloc(sizeof(struct FreqAnchor));
            newAnchor->current=new;
            newAnchor->next=fq->first;
            fq->len++;
        }
    } 
}


void HuffmanCoding(string data, size_t lenght){
    //Obtain symbols frequencies
    printf("Counting frequencies....\n");
    freq fq = FreqCount(data, lenght);
    
    sort(fq);
    printFreq(fq);

    while (fq->len>1)
    {

        struct node *twig = malloc(sizeof(struct node));
        twig->left=pop(fq);
        twig->right=pop(fq);
        printf("\t\t\t\t\t\t\tPOP [%c-%c]\n", twig->left->symbol, twig->right->symbol);
        twig->freq=twig->left->freq + twig->right->freq;
        twig->symbol=0;

        insertNode(fq, twig);
        printFreq(fq);

    }
    //printf("TERMINAMOS con un ROOT: fq=%d\n", fq->first->current->freq);
}
