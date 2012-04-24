#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "proto.h"

/* Check whether an adjacent cell is colored */
int check_adj(struct genes tmp_gene, int row, int col){
    int no_adj = 1;
    
    /* Check first row and all columns */
    if (row == 0 && col >= 0){
        if (tmp_gene.gene[row][col - 1] == 1)
            no_adj = 0;
    /* Check first column and all rows */
    }else if (row >= 0 && col == 0){
        if (tmp_gene.gene[row - 1][col])
            no_adj = 0;
    /* Check anything else in the grid */
    }else if (row > 0 && col > 0){
        if ((tmp_gene.gene[row][col - 1] == 1) ||
            (tmp_gene.gene[row - 1][col] == 1))
                no_adj = 0;
    }

    return no_adj;
}

/* Randomly initialize the genes */
struct genes initialize (){
    struct genes tmp_gene;
    int i, j;

    for (i = 0; i < ROW; i++){
        for (j = 0; j < COL; j++){
            long rand = random();
            tmp_gene.gene[i][j] = 0;
            /* If even paint it black (1) */
            if (rand % 2 == 0){
                if ((check_adj(tmp_gene, i, j)) != 0)
                    tmp_gene.gene[i][j] = 1;
            }
        }
    }
    tmp_gene.fitness = 0;

    return tmp_gene;
}

/* Compute fitness */
void comp_fitness(struct genes* tmp_gene){
    int i, j, penalty = 0;

    for (i = 0; i < ROW; i++){
        for (j = 0; j < COL; j++){
            /* Compare each cell to the original.
                If there is a penalty increase by one
                the counter */
            if (tmp_gene->gene[i][j] != source[i][j])
                penalty++;
        }
    }
    /* Fitness is between 0 and 1 */
    tmp_gene->fitness = (float) penalty/(COL * ROW);
}

/* Print a gene struct */
void print_gene(struct genes tmp_gene){
    int i, j;
    for (i = 0; i < ROW; i++){
        for (j = 0; j < COL; j++){
            /* Colors work only in UNIX */
            if (tmp_gene.gene[i][j] == 1)
                printf(GREEN "%2d" RESET, tmp_gene.gene[i][j]);
            else
                printf(WHITE "%2d" RESET, tmp_gene.gene[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("fitness: %f\n", tmp_gene.fitness);
}

/* Just want to see the source. Serves nothing */
void print_source(){
    int i, j;
    for (i = 0; i < ROW; i++){
        for (j = 0; j < COL; j++){
            if (source[i][j] == 1)
                printf(GREEN "%2d" RESET, source[i][j]);
            else
                printf(WHITE "%2d" RESET, source[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char *argv[]){
    struct genes total_genes[POPULATION];
    struct Node *init_population = NULL;
    int i;

    /* Initialize the first generation */
    for (i = 0; i < POPULATION; i++){
        push(&init_population, initialize());
    }
    
     
    struct Node *list_index = init_population;
    while (list_index != NULL){
        printf("=================\n");
        comp_fitness(&(list_index->organism));
        print_gene(list_index->organism);
        list_index = list_index->next;
    }
    





    /* TEST */
    struct Node *linked_list_head = NULL;
    //print_source();
    push(&linked_list_head, total_genes[0]);
    push(&linked_list_head, total_genes[1]);
    int size1 = size(&linked_list_head);
    printf("linked list size: %d\n", size(&linked_list_head));
    /*int lala;
    for (lala = 0; lala < size1; lala++){
        delete(&linked_list_head);
    }*/
    printf("linked list size: %d\n", size(&linked_list_head));
    printf("lala\n");
    struct Node *tmp = linked_list_head;
    while (tmp != NULL){
        printf("fitness: %f", tmp->organism.fitness);
        tmp = tmp->next;
    }
    exit(EXIT_SUCCESS);
}
