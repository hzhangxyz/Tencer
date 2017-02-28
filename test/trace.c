#include <stdio.h>
#include "../tensor.h"

int main(){
    network *N=network_malloc();
    int T_d[]={2,2};
    int T_b[]={0,0};
    tensor* T=network_append_tensor(
            N,
            tensor_malloc(2,T_d,T_b));
    T->data[0]=1 * I;
    T->data[1]=2 * I;
    T->data[2]=100;
    T->data[3]=200;
    tensor* ANS=tensor_times(N,0);
    printf("%.2f + %.2fi\n",creal(ANS->data[0]),cimag(ANS->data[0]));
    network_free(N);
    return 0;
}
