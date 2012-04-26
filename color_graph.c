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
#include <stdlib.h>
#include <unistd.h>
#include "proto.h"

/* Check whether an adjacent cell is colored */
/* Eventually I don't need it */
int check_adj(struct Genes tmp_gene, int row, int col){
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

/* Randomly initialize the Genes */
struct Genes initialize (){
    struct Genes tmp_gene;
    int i, j;

    for (i = 0; i < ROW; i++){
        for (j = 0; j < COL; j++){
            long rand = random();
            tmp_gene.gene[i][j] = 0;
            /* If even paint it black (1) */
            if (rand % 2 == 0){
                tmp_gene.gene[i][j] = 1;
            }
        }
    }
    tmp_gene.fitness = 0;

    return tmp_gene;
}

/* Compute fitness */
void comp_fitness(struct Genes* tmp_gene){
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
void print_gene(struct Genes tmp_gene){
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
    struct Genes total_Genes[POPULATION];
    struct Node *init_population = NULL;
    int i;

    /* Initialize the first generation */
    for (i = 0; i < POPULATION; i++){
        push(&init_population, initialize());
    }
    
     
    struct Node *list_index = init_population;
    while (list_index != NULL){
        printf("=================\n");
        /* Compute fitness */
        comp_fitness(&(list_index->organism));
        print_gene(list_index->organism);
        list_index = list_index->next;
    }
    
    /* Sort ascending the initial population */
    sort(&init_population);
    
    list_index = init_population;
    while (list_index != NULL){
        printf("=================\n");
        print_gene(list_index->organism);
        list_index = list_index->next;
    }

    /* First next generation */
    int new_gen_pop = POPULATION * POP_RATE;
    
    struct Node *cur_gen = NULL;
    list_index = init_population;
    /* Copy 50% best primitive organisms to current generation */
    for (i = 0; i < new_gen_pop; i++){
        push(&cur_gen, list_index->organism);
        list_index = list_index->next;
    }
    printf("cur generation: %d\n", size(&cur_gen));
    exit(EXIT_SUCCESS);
}
