#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "price.h"
#define long long ll

// int price(int s , int t){
//     return (s+t);
// }
int heap[10000], sz;
int Insert(int node){
    int now = ++sz , p ,x;
    heap[sz] = node;
    while(now > 1 ){

    }
}
int main(){
    // for(int i=0; i<1000000 ; i++){
        printf("%lld\n", price(1,1000000));
    // }
    // int A, Q ,N ;
    // scanf("%d %d %d",&A,&Q,&N);
    // int* S = malloc(A*sizeof(int));
    // int s,k; //s為額外stock 此處為0
    // for(int i=0; i<Q; i++){
    //     scanf("%d %d",&s,&k);
    //     // do something 
    //     //



    //     // print something about
    //     //
    // }


    







    return 0 ;
}