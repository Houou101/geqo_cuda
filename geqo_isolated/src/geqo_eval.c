#include <stdlib.h>
#include "geqo.h"

extern double **dist_matrix;

double geqo_eval(PlannerInfo *root, Gene *tour, int num_gene) {
    double cost = 0.0;
    for (int i = 0; i < num_gene - 1; i++)
        cost += dist_matrix[tour[i]][tour[i+1]];
    cost += dist_matrix[tour[num_gene - 1]][tour[0]];
    return cost;
}
