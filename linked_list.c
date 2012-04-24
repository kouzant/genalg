#include <stdio.h>
#include "proto.h"

void push(struct Node **head, struct genes organism){
    struct Node *tmp_node;
    tmp_node = (struct Node *) malloc(sizeof(struct Node));
    tmp_node->organism = organism;
    if (*head == NULL){
    /* List is empty */
        *head = tmp_node;
        (*head)->next = NULL;
    }else{
    /* List is not empty */
        tmp_node->next = *head;
        *head = tmp_node;
    }
}

void delete(struct Node **head){
    struct Node *index;
    index = *head;
    *head = index->next;
    free(index);
}

int size(struct Node **head){
    struct Node *index;
    int counter = 0;
    index = *head;
    
    while (index != NULL){
        index = index->next;
        counter++;
    }

    return counter;
}
