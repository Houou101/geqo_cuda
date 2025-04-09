#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "geqo.h"

void init_tour(Gene *tour, int num_gene) {
    for (int i = 0; i < num_gene; i++) tour[i] = i;
    for (int i = 0; i < num_gene; i++) {
        int j = rand() % num_gene;
        int tmp = tour[i]; tour[i] = tour[j]; tour[j] = tmp;
    }
}

void random_init_pool(PlannerInfo *root, Pool *pool) {
    for (int i = 0; i < pool->size; i++) {
        init_tour(pool->data[i].string, pool->string_length);
        pool->data[i].worth = geqo_eval(root, pool->data[i].string, pool->string_length);
    }
}

int compare(const void *a, const void *b) {
    double diff = ((Chromosome*)a)->worth - ((Chromosome*)b)->worth;
    return (diff < 0) ? -1 : 1;
}

void sort_pool(Pool *pool) {
    qsort(pool->data, pool->size, sizeof(Chromosome), compare);
}
