#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "proto.h"

struct genes initialize (){
    printf("Initializing...\n");
    struct genes tmp_gene;
    
    int i, j;

    for (i = 0; i < 11; i++){
        for (j = 0; j < 7; j++){
            long rand = random();
            if (rand % 2 == 0)
                tmp_gene.gene[i][j] = 0;
            else
                tmp_gene.gene[i][j] = 1;
        }
    }
    tmp_gene.fitness = 0;

    return tmp_gene;
}

void print_gene(struct genes tmp_gene){
    int i, j;
    for (i = 0; i < COL; i++){
        for (j = 0; j < ROW; j++){
            printf("%d", tmp_gene.gene[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("fitness: %d\n", tmp_gene.fitness);
}

int main(int argc, char *argv[]){
    
    struct genes total_genes[POPULATION];
    int i;

    for (i = 0; i < POPULATION; i++){
        total_genes[i] = initialize();
    }

    for (i = 0; i < POPULATION; i++){
        print_gene(total_genes[i]);
    }
    exit(EXIT_SUCCESS);
}
