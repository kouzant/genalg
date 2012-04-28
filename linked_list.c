/*
    Copyright (C) 2012
    Kouzoupis Antonis

    This file is part of genalg.

    genalg is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    genalg is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with genalg.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include "proto.h"

/* Add nodes at the beggining of the list */
void push(struct Node **head, struct Genes organism){
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

/* Delete all nodes from the list */
void delete(struct Node **head){
    struct Node *index;
    index = *head;
    while(index != NULL){
        struct Node *next = index->next;
        free(index);
        index = next;
    }
}

/* Print a list with organisms */
void print_list(struct Node *head){
    struct Node *index;
    index = head;
    while (index != NULL){
        printf("====================\n");
        print_gene(index->organism);
        index = index->next;
    }
}

/* Sort the list in ascending order */
void sort(struct Node **head){
    struct Node *tmp_node1;
    struct Node *tmp_node2;
    tmp_node1 = (struct Node *) malloc(sizeof(struct Node));
    tmp_node2 = (struct Node *) malloc(sizeof(struct Node));
    struct Genes tmp_organism;

    for (tmp_node1 = *head; tmp_node1 != NULL; tmp_node1 = tmp_node1->next){
        for (tmp_node2 = tmp_node1->next; tmp_node2 != NULL; tmp_node2 = tmp_node2->next){
            if (tmp_node1->organism.fitness <= tmp_node2->organism.fitness){
                tmp_organism = tmp_node1->organism;
                tmp_node1->organism = tmp_node2->organism;
                tmp_node2->organism = tmp_organism;
            }
        }
    }
}

/* Calculates the size of the list */
int size(struct Node *head){
    struct Node *index;
    int counter = 0;
    index = head;
    
    while (index != NULL){
        index = index->next;
        counter++;
    }

    return counter;
}
