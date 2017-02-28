#include "tensor.h"

tensor* tensor_malloc(
        int dimensions,
        int* dimension,
        int* bond){
    tensor *T;
    T=(tensor*)malloc(sizeof(tensor));
    T->dimensions=dimensions;
    T->dimension=(int*)malloc(sizeof(int)*dimensions);
    T->bond=(int*)malloc(sizeof(int)*dimensions);
    //malloc something
    int m = 1;
    for(int i=0;i<dimensions;i++){
        T->bond[i] = bond[i];
        m *= (T->dimension[i]=dimension[i]);
    }
    T->data=(BASETYPE *)malloc(sizeof(BASETYPE)*m);
    //calculate the storage of data and malloc
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
    N->bond_pool=(tensor*(*)[2]) malloc(sizeof(tensor*[2])*INITPOOL);
    N->max_tensor=INITPOOL;
    N->current_tensor=0;
    N->tensor_pool=(tensor* *) malloc(sizeof(tensor*)*INITPOOL);
    //malloc everything
    for(int i=0;i<INITPOOL;i++){
        N->bond_pool[i][0]=N->bond_pool[i][1]=NOBOND;
        N->tensor_pool[i]=NOTENSOR;
    }
    //initialize pool
    return N;
}

int network_free(network* N){
    for(int i = 0;i<N->current_tensor;i++)
        tensor_free(N->tensor_pool[i]);
    free(N->tensor_pool);
    free(N->bond_pool);
    free(N);
    return 0;
}

int check_pool(network* N){
    if(N->max_bond<2*N->current_bond){
        N->max_bond*=2;
        N->bond_pool = (tensor*(*)[2])realloc(
                N->bond_pool,
                N->max_bond);
        //extend if half full
        for(int i=N->max_bond/2;i<N->max_bond;i++){
            N->bond_pool[i][0]=NOBOND;
            N->bond_pool[i][1]=NOBOND;
        }
        //initialize new pool
    }
    if(N->max_tensor<2*N->current_tensor){
        N->max_tensor*=2;
        N->tensor_pool = (tensor **)realloc(
                N->tensor_pool,
                N->max_tensor);
        //extend if half full
        for(int i=N->max_tensor/2;i<N->max_tensor;i++){
            N->tensor_pool[i]=NOTENSOR;
        }
        //initialize new pool
    }
    return 0;
}

tensor* network_append_tensor(network* N,tensor* T){
    N->tensor_pool[N->current_tensor++]=T;
    //update tensor pool
    for(int i = 0;i<T->dimensions;i++){
        if(N->bond_pool[T->bond[i]][0]==NOBOND)
            N->bond_pool[T->bond[i]][0]=T;
        else
            N->bond_pool[T->bond[i]][1]=T;
        if(N->current_bond<T->bond[i])
            N->current_bond=T->bond[i];
    }
    //update bond pool
    check_pool(N);
    //whatif pool is full
    return T;
}

tensor* tensor_times(
        network *N,
        int abond){
    tensor* T1=N->bond_pool[abond][0];
    tensor* T2=N->bond_pool[abond][1];
    //tensor
    if(T1==T2){
        tensor *T=T1;
        int dimensions = T->dimensions-2;
        int* dimension = (int*)malloc(sizeof(int)*dimensions);
        int* bond = (int*)malloc(sizeof(int)*dimensions);
        int Tf=1;
        int Tm=1;
        int Tl=1;
        int p=0;
        int i=0;
        while(T->bond[p]!=abond){
            Tf*=(dimension[i]=T->dimension[p]);
            bond[i]=T->bond[p];
            i++;
            p++;
        }
        p++;
        while(T->bond[p]!=abond){
            Tm*=(dimension[i]=T->dimension[p]);
            bond[i]=T->bond[p];
            i++;
            p++;
        }
        int adim=T->dimension[p];
        p++;
        while(p!=T->dimensions){
            Tl*=(dimension[i]=T->dimension[p]);
            bond[i]=T->bond[p];
            i++;
            p++;
        }
        tensor* ANS=tensor_malloc(dimensions,dimension,bond);
        for(int i=0;i<Tf;i++)
            for(int j=0;j<Tm;j++)
                for(int k=0;k<Tl;k++){
                    BASETYPE *temp=&ANS->data[(i*Tm+j)*Tl+k];
                    for(int l=0;l<adim;l++){
                        *temp += T->data[(((i*adim+l)*Tm+j)*adim+l)*Tl+k];
                    }
                }

        return ANS;
    }
    //whatif the same
    int dimensions  = T1->dimensions+T2->dimensions-2;
    int* dimension = (int*)malloc(sizeof(int)*dimensions);
    int* bond = (int*)malloc(sizeof(int)*dimensions);
    int p=0;
    int i=0;
    int T1f=1;
    int T1l=1;
    int T2f=1;
    int T2l=1;
    int adim=1;
    while(T1->bond[p]!=abond){
        T1f*=(dimension[i]=T1->dimension[p]);
        bond[i]=T1->bond[p];
        i++;
        p++;
    }
    p++;
    while(p!=T1->dimensions){
        T1l*=(dimension[i]=T1->dimension[p]);
        bond[i]=T1->bond[p];
        i++;
        p++;
    }
    p=0;
    while(T2->bond[p]!=abond){
        T2f*=(dimension[i]=T2->dimension[p]);
        bond[i]=T2->bond[p];
        i++;
        p++;
    }
    adim=T2->dimension[p];
    p++;
    while(p!=T2->dimensions){
        T2l*=(dimension[i]=T2->dimension[p]);
        bond[i]=T2->bond[p];
        i++;
        p++;
    }
    tensor* ANS=tensor_malloc(dimensions,dimension,bond);
    //get the shape
    for(int i=0;i<T1f;i++)
        for(int j=0;j<T1l;j++)
            for(int k=0;k<T2f;k++)
                for(int l=0;l<T2l;l++){
                    BASETYPE* temp=&ANS->data[((i*T1l+j)*T2f+k)*T2l+l];
                    *temp = 0;
                    for(int m=0;m<adim;m++)
                        *temp += T1->data[(i*adim+m)*T1l+j]*T2->data[(k*adim+m)*T2l+l];
                }
    //calculate the data
    for(int i=0;i<T1->dimensions;i++){
        if(N->bond_pool[T1->bond[i]][0]==T1)
            N->bond_pool[T1->bond[i]][0]=ANS;
        else
            N->bond_pool[T1->bond[i]][1]=ANS;
    }
    for(int i=0;i<T2->dimensions;i++){
        if(N->bond_pool[T2->bond[i]][0]==T2)
            N->bond_pool[T2->bond[i]][0]=ANS;
        else
            N->bond_pool[T2->bond[i]][1]=ANS;
    }
    N->bond_pool[abond][0]=NOTENSOR;
    N->bond_pool[abond][1]=NOTENSOR;
    //update bond
    tensor_free(T1);
    tensor_free(T2);
    free(dimension);
    free(bond);
    //free others
    return ANS;
}
