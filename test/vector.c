#include <stdio.h>
#include "../tensor.h"

int main(){
    network *N=network_malloc();
    int T_d[]={2};
    int T_b[]={0};
    tensor* T1=network_append_tensor(
            N,
            tensor_malloc(1,T_d,T_b));
    tensor* T2=network_append_tensor(
            N,
            tensor_malloc(1,T_d,T_b));
    T1->data[0]=I;
    T1->data[1]=2;
    T2->data[0]=10;
    T2->data[1]=100;
    tensor* ANS=tensor_times(N,0);
    printf("%.2f + %.2fi\n",creal(ANS->data[0]),cimag(ANS->data[0]));
    network_free(N);
    return 0;
}
