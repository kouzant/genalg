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
    int i, j, hit = 0;

    for (i = 0; i < ROW; i++){
        for (j = 0; j < COL; j++){
            /* Compare each cell to the original.
               If there is a penalty increase by one
               the counter */
            if (tmp_gene->gene[i][j] == source[i][j])
                hit++;
        }
    }
    /* Fitness is between 0 and 1 */
    tmp_gene->fitness = (float) hit/(COL * ROW);
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

/* Compute total fitness */
float total_fitness(struct Node *head){
    struct Node *index = head;
    float total_fit = 0;

    while(index != NULL){
        total_fit += index->organism.fitness;
        index = index->next;
    }

    return total_fit;
}

/* Pick an organism with Roulette Wheel sampling */
struct Genes pick_one_parent(struct Node *head, float total_fit){
    int total_fitness = ((int) total_fit) + 1;
    /* Threshold between 0 and total_fitness */
    int threshold = random() % total_fitness;
    float sum = 0;
    struct Node *index = head;

    while (index != NULL){
        sum += index->organism.fitness;
        if (sum >= threshold)
            break;
        index = index->next;
    }

    return index->organism;
}

/* Mutate a random gene*/
void mutate(struct Node **next_gen){
    int i;

    for (i = 0; i < ROW; i++){
        /*Pick a random gene between 0 and COL */
        int gene = random() % COL;
        int rand = random();
        if((rand % 2) == 0){
            int value = (*next_gen)->organism.gene[i][gene];
            if(value == 0)
                (*next_gen)->organism.gene[i][gene] = 1;
            else
                (*next_gen)->organism.gene[i][gene] = 0;
        }
    }
}

/* Mate two organisms */
void mate(struct Node **next_gen, struct Node *mate_pool){
    /* Pick two parents */
    struct Genes parent0 = pick_one_parent(mate_pool,
            total_fitness(mate_pool));
    struct Genes parent1 = pick_one_parent(mate_pool,
            total_fitness(mate_pool));
    /* Two children */
    struct Genes child0;
    struct Genes child1;
    int i, j;

    for (i = 0; i < ROW; i++){
        for (j = 0; j < COL; j++){
            child0.gene[i][j] = parent0.gene[i][j];
            child1.gene[i][j] = parent1.gene[i][j];
        }
    }

    /* Mating process with mask 1111000 (see HSIZE) */
    for (i = 0; i < ROW; i++){
        for (j = 0; j < (HSIZE - 1); j++){
            child0.gene[i][COL - HSIZE + 1 + j] = parent1.gene[i][COL - HSIZE + 1 + j];
            child1.gene[i][COL - HSIZE + 1 + j] = parent0.gene[i][COL - HSIZE + 1 + j];
        }
    }
    comp_fitness(&child0);
    comp_fitness(&child1);
    push(next_gen, child0);
    push(next_gen, child1);
}

int main(int argc, char *argv[]){
    struct Genes total_Genes[POPULATION];
    struct Node *cur_gen = NULL;
    struct Node *mate_pool = NULL;
    struct Node *next_gen = NULL;
    int i;
    /* Seed of random */
    srandom(time(NULL));

    /* Initialize the first generation */
    for (i = 0; i < POPULATION; i++){
        push(&cur_gen, initialize());
    }


    struct Node *list_index = cur_gen;
    while (list_index != NULL){
        //printf("=================\n");
        /* Compute fitness */
        comp_fitness(&(list_index->organism));
        //print_gene(list_index->organism);
        list_index = list_index->next;
    }

        /* Sort ascending the initial population */
        sort(&cur_gen);
        float biggest_fit = 0;
        int flag = 0;
    do{

        list_index = cur_gen;
        float koko = 0;
        while (list_index != NULL){
            //printf("=================\n");
            //print_gene(list_index->organism);
            koko += list_index->organism.fitness;
            list_index = list_index->next;
        }

        printf("Old total fitness: %f\n", koko);
        /* First next generation */
        int new_gen_pop = POPULATION * POP_RATE;
        sort(&cur_gen);
        list_index = cur_gen;
        /* Copy 50% best primitive organisms to mating pool */
        for (i = 0; i < new_gen_pop; i++){
            push(&mate_pool, list_index->organism);
            list_index = list_index->next;
        }
        printf("M A T E  P O O L\n");
        printf("current generation size: %d\n", size(cur_gen));
        printf("mating pool size: %d\n", size(mate_pool));
        printf("total fitness: %f\n", total_fitness(mate_pool));

        /* Mate organisms */
        for (i = 0; i < size(mate_pool); i++){
            mate(&next_gen, mate_pool);
        }

        /* Mutate the first mutated organisms */
        int mutated = POPULATION * MUT_RATE;
        list_index = next_gen;
        for(i = 0; i < mutated; i++){
            mutate(&list_index);
            list_index = list_index->next;
        }
        printf("mate pool size: %d\n", size(mate_pool));
        printf("next gen size: %d\n", size(next_gen));
        sort(&next_gen);
        //print_list(next_gen);
        biggest_fit = next_gen->organism.fitness;
        if (biggest_fit > 0.9)
            print_gene(next_gen->organism);
        printf("Biggest fitness: %f\n", biggest_fit);
        
        delete(&cur_gen);
        cur_gen = NULL;
        copy_list(&next_gen, &cur_gen);
        //cur_gen = next_gen;
        delete(&next_gen);
        delete(&mate_pool);
        next_gen = NULL;
        mate_pool = NULL;
        printf("Time %d\n", time(NULL));
        //biggest_fit = 1;
        flag++;
    }while(biggest_fit < 1);
    exit(EXIT_SUCCESS);
}
