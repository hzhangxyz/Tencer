#include "tensor.h"

tensor* tensor_malloc(int dimensions, int* dimension, int* bond){
    tensor *T;
    T=(tensor*)malloc(sizeof(tensor));
    T->dimensions=dimensions;
    T->dimension=(int*)malloc(sizeof(int)*dimensions);
    int m = 1;
    for(int i=0;i<dimensions;i++){
        T->bond[i] = bond[i];
        m *= (T->dimension[i]=dimension[i]);
    }
    T->data=(BASETYPE *)malloc(sizeof(BASETYPE)*m);
    return T;
}

int tensor_free(tensor *T){
    free(T->dimension);
    free(T->data);
    free(T);
    return 0;
}

network* network_malloc(){
    network* N;
    N = (network*) malloc(sizeof(network));
    N->max_bond=INITPOOL;
    N->current_bond=0;
    N->bond_pool=(int(*)[2]) malloc(sizeof(int[2])*INITPOOL);
    N->max_tensor=INITPOOL;
    N->current_tensor=0;
    N->tensor_pool=(tensor* *) malloc(sizeof(tensor*)*INITPOOL);
    for(int i=0;i<INITPOOL;i++){
        N->bond_pool[i][0]=N->bond_pool[i][1]=NOBOND;
        N->tensor_pool[i]=NOTENSOR;
    }
    return N;
}

tensor* tensor_times(network *N, int bond){

}
