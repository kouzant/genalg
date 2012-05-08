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
#include <time.h>

#include "proto.h"

/* Randomly initialize the Organisms */
struct Organisms initialize (){
    struct Organisms tmp_gene;
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
void comp_fitness(struct Organisms* tmp_gene){
    int i, j, hit = 0;

    for (i = 0; i < ROW; i++){
        for (j = 0; j < COL; j++){
            /* Compare each cell to the original.
                If two cells are identical increase
                the hit counter */
            if (tmp_gene->gene[i][j] == source[i][j])
                hit++;
        }
    }
    /* Fitness is between 0 and 1 
        0 is the worst and 1 is the best */
    tmp_gene->fitness = (float) hit/(COL * ROW);
}

/* Print a gene struct */
void print_gene(struct Organisms tmp_gene){
    int i, j;
    printf("\n");
    for (i = 0; i < ROW; i++){
        for (j = 0; j < COL; j++){
            /* Colors work only in UNIX */
#if defined(__unix__)
            if (tmp_gene.gene[i][j] == 1)
                printf(GREEN "%2d" RESET, tmp_gene.gene[i][j]);
            else
                printf(WHITE "%2d" RESET, tmp_gene.gene[i][j]);
#elif defined(_WIN32)
                printf("%2d", tmp_gene.gene[i][j]);
#endif
        }
        printf("\n");
    }
    printf("\n");
    printf("fitness: %f\n", tmp_gene.fitness);
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
struct Organisms pick_one_parent(struct Node *head, float total_fit){
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

    /* In every ROW one gene may mutate */
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
    struct Organisms parent0 = pick_one_parent(mate_pool,
            total_fitness(mate_pool));
    struct Organisms parent1 = pick_one_parent(mate_pool,
            total_fitness(mate_pool));
    /* Two children */
    struct Organisms child0;
    struct Organisms child1;
    int i, j;

    /* Copy parents unchanged to children */
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
    /* Compute fitness for children */
    comp_fitness(&child0);
    comp_fitness(&child1);
    /* Push children to next generation */
    push(next_gen, child0);
    push(next_gen, child1);
}

int main(int argc, char *argv[]){
    long start_t = time(NULL);
    long end_t = 0;
    int generations = 0;
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
        /* Compute fitness */
        comp_fitness(&(list_index->organism));
        list_index = list_index->next;
    }

    /* Sort descending the initial population */
    sort(&cur_gen);
    generations++;
    float biggest_fit = 0;
    do{

        list_index = cur_gen;
        /* First next generation */
        int new_gen_pop = POPULATION * POP_RATE;
        /* Sort descenting the current population */
        sort(&cur_gen);
        list_index = cur_gen;
        /* Copy POP_RATE best primitive organisms to mating pool */
        for (i = 0; i < new_gen_pop; i++){
            push(&mate_pool, list_index->organism);
            list_index = list_index->next;
        }

        /* Mate organisms */
        for (i = 0; i < size(mate_pool); i++){
            mate(&next_gen, mate_pool);
        }

        /* Mutate the first organisms */
        int mutated = POPULATION * MUT_RATE;
        list_index = next_gen;
        for(i = 0; i < mutated; i++){
            mutate(&list_index);
            list_index = list_index->next;
        }
        /* Sort descending the next generation */
        sort(&next_gen);
        /* The organism with the biggest fitness is the first one */
        biggest_fit = next_gen->organism.fitness;
        /* Print the organism with fitness = 1 (aka final) */
        if (biggest_fit == 1)
            print_gene(next_gen->organism);
        printf("Biggest fitness in generation %d:  %f\n", generations, biggest_fit);

        /* Delete current generation */
        delete(&cur_gen);
        cur_gen = NULL;
        /* Copy next generation to current */
        copy_list(&next_gen, &cur_gen);
        /* Delete next generation and mating pool */
        delete(&next_gen);
        delete(&mate_pool);
        next_gen = NULL;
        mate_pool = NULL;
        generations++;
    }while(biggest_fit < 1);
    end_t = time(NULL);
    printf("Computed after %d generations and after %d seconds.\n", generations - 1,
        (int)(end_t - start_t));
    exit(EXIT_SUCCESS);
}
