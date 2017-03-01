#include <stdlib.h>
#include <complex.h>
#include <stdio.h>

#define BASETYPE double complex
#define INITPOOL 256
#define NOBOND 0
#define NOTENSOR 0
#define READBASE(F,D)                    \
{                                        \
    double t;                            \
    char s;                              \
    fscanf((F),"%lf",&t);                \
    *(D) = t;                            \
    if((s=fgetc(F))!=' '){               \
        if((s!='+')&&(s!='-'))           \
            *(D) *= I;                   \
        else{                            \
            fscanf((F),"%lf",&t);        \
            *(D) += (s=='+'?1:-1)*t*I;   \
            fgetc(F);                    \
        }                                \
    }                                    \
}

typedef struct tensor{
    int dimensions;
    int *dimension;
    int *bond;
    BASETYPE *data;
} tensor;

typedef struct network{
    int max_bond;
    int current_bond;
    tensor* (*bond_pool)[2];
    int max_tensor;
    int current_tensor;
    tensor **tensor_pool;
} network;

tensor* tensor_malloc(
        int dimensions,
        int dimension[],
        int bond[]);

int tensor_free(tensor*);

network* network_malloc();

int network_free(network*);

network* check_pool(network*);

tensor* network_append_tensor(
        network*,
        tensor*);

tensor* tensor_times(
        network* N,
        int bond);

network* tensor_import(
        network*,
        char *);

