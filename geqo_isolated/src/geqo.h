#pragma once
#include <stdio.h>

typedef int Gene;

typedef struct {
    Gene *string;
    double worth;
} Chromosome;

typedef struct {
    int size;
    int string_length;
    Chromosome *data;
} Pool;

typedef struct {
    Pool *pool;
} PlannerInfo;
