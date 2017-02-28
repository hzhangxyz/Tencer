#include <stdio.h>
#include "tensor.h"

int main(){
    network *N=network_malloc();
    int T_d[]={2};
    int T_b[]={1};
    tensor* T1=network_append_tensor(
            N,
            tensor_malloc(1,T_d,T_b));
    tensor* T2=network_append_tensor(
            N,
            tensor_malloc(1,T_d,T_b));
    T1->data[0]=1;
    T1->data[1]=2;
    T2->data[0]=3;
    T2->data[1]=4;
    tensor* ANS=tensor_times(N,1);
    printf("%lf\n",ANS->data[0]);
    network_free(N);
    return 0;
}
