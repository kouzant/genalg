#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "proto.h"

struct genes initialize (){
    struct genes tmp_gene;
    int i, j;

    for (i = 0; i < ROW; i++){
        for (j = 0; j < COL; j++){
            long rand = random();
            /* If even paint it white (0),
                else paint it black (1) */
            if (rand % 2 == 0)
                tmp_gene.gene[i][j] = 0;
            else
                tmp_gene.gene[i][j] = 1;
        }
    }
    tmp_gene.fitness = 0;

    return tmp_gene;
}

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

void print_gene(struct genes tmp_gene){
    int i, j;
    for (i = 0; i < COL; i++){
        for (j = 0; j < ROW; j++){
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

int main(int argc, char *argv[]){
    struct genes total_genes[POPULATION];
    int i;

    /* Initialize the first generation */
    for (i = 0; i < POPULATION; i++){
        total_genes[i] = initialize();
    }

    
    for (i = 0; i < POPULATION; i++){
        printf("====================\n");
        /* Compute fitness */
        comp_fitness(&total_genes[i]);
        print_gene(total_genes[i]);
    }
    exit(EXIT_SUCCESS);
}
