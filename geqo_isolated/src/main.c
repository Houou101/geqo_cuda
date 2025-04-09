#include <stdio.h>
#include <stdlib.h>
#include "geqo.h"

double **dist_matrix;

void read_matrix(const char *filename, int size) {
    dist_matrix = malloc(size * sizeof(double *));
    for (int i = 0; i < size; i++) {
        dist_matrix[i] = malloc(size * sizeof(double));
    }

    FILE *file = fopen(filename, "r");
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            fscanf(file, "%lf", &dist_matrix[i][j]);
    fclose(file);
}

int main() {
    int cities = 10;
    int generations = 1000;
    int pool = 20;

    read_matrix("data/tsp_10.txt", cities);
    Chromosome result = run_geqo(cities, generations, pool);

    printf("Beste Tour (Kosten: %.2f):\n", result.worth);
    for (int i = 0; i < cities; i++) {
        printf("%d ", result.string[i]);
    }
    printf("\n");

    free(result.string);
    for (int i = 0; i < cities; i++) free(dist_matrix[i]);
    free(dist_matrix);
    return 0;
}
