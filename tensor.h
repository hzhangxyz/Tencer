#include <stdlib.h>

#define BASETYPE double
#define INITPOOL 256
#define NOBOND 0
#define NOTENSOR 0

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

int check_bond_and_tensor(network*);

tensor* network_append_tensor(
        network*,
        tensor*);

tensor* tensor_times(
        network* N,
        int bond);

