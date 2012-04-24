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

void sort(struct Node **head){
    struct Node *tmp_node1;
    struct Node *tmp_node2;
    tmp_node1 = (struct Node *) malloc(sizeof(struct Node));
    tmp_node2 = (struct Node *) malloc(sizeof(struct Node));
    struct genes tmp_organism;

    for (tmp_node1 = *head; tmp_node1 != NULL; tmp_node1 = tmp_node1->next){
        for (tmp_node2 = tmp_node1->next; tmp_node2 != NULL; tmp_node2 = tmp_node2->next){
            if (tmp_node1->organism.fitness >= tmp_node2->organism.fitness){
                tmp_organism = tmp_node1->organism;
                tmp_node1->organism = tmp_node2->organism;
                tmp_node2->organism = tmp_organism;
            }
        }
    }
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
