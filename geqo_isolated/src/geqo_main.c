#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "geqo.h"

extern double geqo_eval(PlannerInfo *root, Gene *tour, int num_gene);

Chromosome run_geqo(int num_cities, int generations, int pool_size) {
    PlannerInfo root;
    Pool pool;
    root.pool = &pool;
    pool.size = pool_size;
    pool.string_length = num_cities;
    pool.data = malloc(pool.size * sizeof(Chromosome));

    for (int i = 0; i < pool.size; i++)
        pool.data[i].string = malloc(num_cities * sizeof(Gene));

    random_init_pool(&root, &pool);
    sort_pool(&pool);

    Chromosome best = pool.data[0];
    for (int g = 0; g < generations; g++) {
        Chromosome child;
        child.string = malloc(num_cities * sizeof(Gene));
        init_tour(child.string, num_cities);
        child.worth = geqo_eval(&root, child.string, num_cities);

        if (child.worth < pool.data[pool.size - 1].worth) {
            memcpy(pool.data[pool.size - 1].string, child.string, num_cities * sizeof(Gene));
            pool.data[pool.size - 1].worth = child.worth;
            sort_pool(&pool);
            best = pool.data[0];
        }
        free(child.string);
    }

    Chromosome result;
    result.string = malloc(num_cities * sizeof(Gene));
    memcpy(result.string, best.string, num_cities * sizeof(Gene));
    result.worth = best.worth;

    for (int i = 0; i < pool.size; i++)
        free(pool.data[i].string);
    free(pool.data);
    return result;
}
