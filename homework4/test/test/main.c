#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef struct operation{
    char o;
    int int1 ;
    int int2 ;
    } Operation;

Operation op[1000001];
typedef struct disjointSet{
    int parent;
    int size;
    
    } DisjointSet;

DisjointSet ds[1000001];

bool set[1000001] = {};

void makeset(const int i){
    ds[i].parent = i;
    ds[i].size = 1;
}

void  init(const int i) {
    if (!set[i]) {
        makeset(i);
        set[i] = 1;
    }
}

int find_set(const int i) {
    init(i);
    if( i == ds[i].parent ){
        return i;
    }
        return ds[i].parent = find_set(ds[i].parent);
}
bool merge(const int ra, const int rb) {
    int a = find_set(ra), b = find_set(rb);
    if(a!=b){
        if (ds[a].size < ds[b].size ){
            ds[a].parent = b ;
            ds[b].size+= ds[a].size;
        }
        else if (ds[a].size > ds[b].size){
            ds[b].parent = a ;
            ds[a].size+= ds[b].size;
        }
        return true;
    }
    else{ // merge failed 沒有減
        return false;
    }
    
    
}
bool same_set(const int a, const int b) {
    return find_set(a) == find_set(b);
}
int query[1000001]={0};
int main(){
    int N , M , int1 ,int2;
    int Q=0;
    bool flag = false;
    scanf("%d %d", &N ,&M);
    char read[10] = {"\0"} ;
    for(int i=0; i<M; i++){
        scanf("%s",read);
        if(strcmp(read,"merge")==0){
            scanf("%d %d ", &int1 ,&int2);
            op[i].o='m';
            op[i].int1 = int1;
            op[i].int2 = int2;
        }
        else if(strcmp(read,"query")==0){
            Q++;
            op[i].o ='q';
            op[i].int1 = -1;
            op[i].int2 = -1;
            query[Q]=i;
        }
        else if(strcmp(read,"boom")==0){
            flag = true;
            scanf("%d", &int1 );
            op[i].o ='b';
            op[i].int1 = int1;
            op[i].int2 = -1;
        }
    }
    if(flag==true){
        int answer[Q]; // Q代表有幾個query
                        // query[j] = 代表在第幾天query
        for(int j =Q; j>0 ; j--){
            memset(set, 0, 1000001);
            int  ans =N;
            // for(int k = query[j] ; k >=0 ; k--) //改成用while 才能處理boom 跳躍的問題
            int k =query[j];
            while(k>=0){
                
                if(op[k].o=='m'){
                    if(merge(op[k].int1,op[k].int2)){
                    ans-=1;
                    }
                }
                else if(op[k].o == 'b'){
                    // printf("form k = %d ",k);
                    k =op[k].int1;
                    // printf("goes to k =%d\n",k);
                }
                k = k-1;
            }
            if(ans<1){
                answer[j]=1;
            }
            else
            answer[j]=ans;
        }
        for(int j =1; j<=Q ; j++){
            printf("%d\n",answer[j]);
        
        }
    }
    else{
        for(int i=0; i<M; i++){
            if(op[i].o=='m'){
                if(merge(op[i].int1,op[i].int2)){
                    N-=1;
                }
            }
            else if(op[i].o=='q'){
                if(N<=0){
                    printf("1");
                }else
                printf("%d\n",N);
            }
        }
    }
    return 0;
}