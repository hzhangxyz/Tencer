#include <stdlib.h>

#define BASETYPE double
#define INITPOOL 256
#define NOBOND -1
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
    int (*bond_pool)[2];
    int max_tensor;
    int current_tensor;
    tensor **tensor_pool;
} network;

tensor* tensor_malloc(int,int[],int[]);
int tensor_free(tensor*);
network* network_malloc();
tensor* tensor_times(network*,int);
