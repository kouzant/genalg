#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    
    /* Genes */
    struct genes{
        int gene[11][7];
        int fitness;
    };

    struct genes lala;
    int i = 0, j = 0;
    srand((unsigned)time(NULL));

    for (i = 0; i < 11; i++){
        for (j = 0; j < 7; j++){
            int random = rand();
            if (random % 2 == 0)
                lala.gene[i][j] = 0;
            else
                lala.gene[i][j] = 1;
        }
    }
    printf("gene:\n");
    for (i=0;i<11;i++){
        for(j=0;j<7;j++){
            printf("%d", lala.gene[i][j]);
        }
        printf("\n");
    }
    printf("fitness: %d\n", lala.fitness);
    exit(EXIT_SUCCESS);
}
