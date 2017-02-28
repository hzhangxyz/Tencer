#include "tensor.h"

tensor* tensor_malloc(
        int dimensions,
        int* dimension,
        int* bond){
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
    N->bond_pool=(tensor*(*)[2]) malloc(sizeof(int[2])*INITPOOL);
    N->max_tensor=INITPOOL;
    N->current_tensor=0;
    N->tensor_pool=(tensor* *) malloc(sizeof(tensor*)*INITPOOL);
    for(int i=0;i<INITPOOL;i++){
        N->bond_pool[i][0]=N->bond_pool[i][1]=NOBOND;
        N->tensor_pool[i]=NOTENSOR;
    }
    return N;
}

int network_free(network* N){
    free(N->bond_pool);
    for(int i = 0;i<=N->current_tensor;i++)
        tensor_free(N->tensor_pool[i]);
    free(N->tensor_pool);
    free(N);
    return 0;
}

int check_bond_and_tensor(network* N){
    if(N->max_bond<2*N->current_bond){
        N->max_bond*=2;
        N->bond_pool = (tensor*(*)[2])realloc(
                N->bond_pool,
                N->max_bond);
        for(int i=N->max_bond/2;i<N->max_bond;i++){
            N->bond_pool[i][0]=NOBOND;
            N->bond_pool[i][1]=NOBOND;
        }
    }
    if(N->max_tensor<2*N->current_tensor){
        N->max_tensor*=2;
        N->tensor_pool = (tensor **)realloc(
                N->tensor_pool,
                N->max_tensor);
        for(int i=N->max_tensor/2;i<N->max_tensor;i++){
            N->tensor_pool[i]=NOTENSOR;
        }
    }
    return 0;
}

tensor* network_append_tensor(network* N,tensor* T){
    N->tensor_pool[N->current_tensor++]=T;
    for(int i = 0;i<T->dimensions;i++){
        if(N->bond_pool[T->bond[i]][0]==NOBOND)
            N->bond_pool[T->bond[i]][0]=T;
        else
            N->bond_pool[T->bond[i]][1]=T;
        if(N->current_bond<T->bond[i])
            N->current_bond=T->bond[i];
    }
    check_bond_and_tensor(N);
    return T;
}

tensor* tensor_times(
        network *N,
        int bond){
    tensor* T1=N->bond_pool[bond][0];
    tensor* T2=N->bond_pool[bond][1];


}