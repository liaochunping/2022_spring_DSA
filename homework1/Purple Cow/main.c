#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h>
#define ll long long
typedef struct node Node;
typedef struct list List;
Node* XOR(Node* a, Node* b){
    return(Node*)(((uintptr_t)(a))^((uintptr_t)(b)));
}


struct node{        //每個node代表一個USB
    ll int usb_id;
    Node* neighbor ;
};
struct list{
    Node* head;
    Node* tail;
};
List* newlist(){
    List* list =(List*)malloc(sizeof(List));
    list->head= NULL;
    list->tail= NULL;
    return list;
}
void freelist(List* list){
    if (NULL == list){
        return;
    }
    Node* curr = list->head;
    Node* prev = NULL;
    Node* next ;
    while(curr != NULL){
        next = XOR(curr->neighbor,prev);
        free(prev);
        prev = curr;
        curr = next;
    }
    free(curr);
}
Node* newnode(ll int id){
    Node* node = (Node*)malloc(sizeof(Node));
    node->neighbor=NULL;
    node->usb_id=id ;
    return node;
}
void insert(List* list , ll int usb_id ){
    Node* new_node = newnode(usb_id);
    if (list->head == NULL&&list->tail==NULL){
        new_node->neighbor =XOR(NULL,NULL);
        list->head = new_node;
        list->tail = new_node;  
    }
    else{
        Node* curr = list->tail;
        curr->neighbor = XOR(XOR(curr->neighbor,NULL),new_node);
        new_node->neighbor=XOR(curr,NULL);
        list->tail = new_node;
    }
}
void pophead(List* list ){
    if(list->head == list->tail){
        free(list->head);
    }
    else{
        Node* curr = list->head;
        Node* next = XOR(NULL,curr->neighbor);
        Node* nextnext = XOR(curr,next->neighbor);
        next->neighbor = XOR(NULL,nextnext);
        list->head = next;
        free(curr);
    }
}
void poptail(List* list){
    if(list->head == list->tail){
        free(list->head);
    }
    else{
        Node* curr = list->tail;
        Node* prev = XOR(NULL,curr->neighbor);
        Node* prevprev = XOR(curr,prev->neighbor);
        prev->neighbor = XOR(NULL,prevprev);
        list->tail = prev;
        free(curr);
    }
}
void printList(List* list){

    Node* curr = list->head;
    Node* prev = NULL;
    Node* next;
    while(curr!= NULL){
        printf("%lld ",curr->usb_id);
        next = XOR(prev, curr->neighbor);
        prev = curr ;
        curr = next ;
    }
    // Node* curr =*head;
    // Node* prev = NULL;
    // Node* next;
    // while(curr!= NULL){
    //     printf("%lld ",curr->usb_id);
    //     next = XOR(prev, curr->neighbor);
    //     prev = curr ;
    //     curr = next ;
    // }
    // printf("\n");
}
void releaseorder(int size,const int group, int* order){
    for(int i =0 ; i<size;i++){
        if(*(order+i)== group ){
            *(order+i)= -1;
            break;
        }
    } 
}
void maintaingrouporder ( int size,const int group, int* order){
    int flag = 0;
    int curr , next;
    for(int i =0 ; i<size;i++){         //判斷是不是都是空的才能從前面填
        if(*(order+i)!=-1){
            flag = 1;           //裡面有東西
            break;
        }
    }
    if(flag==0){
        for(int j =0 ; j<size;j++){
            if(*(order+j)== -1 || *(order+j)==group){
                *(order+j)= group;
                break;
            }
        }
    }else{
        for(int k =0 ; k<size;k++){
            curr= *(order+k);
            next = *(order+k+1);
            if(curr==group){
                *(order+k)= group;
                break;
            }
            if(curr!=-1&&next==-1){
                *(order+k+1)= group;
                break;
            }
        }
    } 
}
Node* reverse(Node** head) { 
    Node* curr = *head;
    if (curr == NULL){
        return NULL;
    }
    else{
        Node* prev = NULL;
        Node* next;
        while (XOR(prev,curr->neighbor)!= NULL) { 
            next = XOR(prev , curr->neighbor);
            prev = curr;
            curr = next;
        } 
        *head = curr ;
        return *head;
    }



    
 
} 

void enter(ll int m ,const ll int i ,ll int j,List* array){ //id j  group i
    List* list = array;
    insert(list,j);
}
void leave(ll int m, List* array){
    poptail(array);
}
void go(ll int m,List* array){
    pophead(array);
}
void close(ll int m){
}

int main(void){
    ll int M ,N ,K,m,i,j;
    char input[]={};
    int test = 1;
    scanf("%lld %lld %lld",&M,&N,&K);
    List* array[K];
    for(int i =0 ; i<K;i++){ 
        array[i] = newlist();
    }
    ll int orderK = 2*K;
    int grouporder[orderK];
    for(int i =0 ; i<orderK;i++){
        grouporder[i]=-1;
    }
    // int **arr =calloc(M,sizeof(int*));
    // for( int i = 0 ; i <=N ; i++){

    // }
    // ll int array[M][K];
    for(ll int iter =0 ; iter < N ; iter++){
        scanf("%s",&input);
        if(strcmp(input , "enter")==0){
            scanf("%lld %lld %lld",&i,&j,&m);
            maintaingrouporder(orderK,i,grouporder);
            enter(m,i,j, array[i]); // j =id i = group
            // printList(array[i]);
        }else if(strcmp(input , "leave")==0){
            scanf("%lld",&m);
            int tail;
            for(int v =orderK-1 ; v>=0;v--){
                if(*(grouporder+v)!= -1 ){
                    tail = grouporder[v];
                    printf("find tail is %d",tail);
                    break;
                }
            } 
            leave(m,array[tail]);
            if(array[tail]->head==NULL);{
                printf("NULL\n");
                releaseorder(orderK,tail,grouporder);
            }
        }else if(strcmp(input , "go")==0){
                scanf("%lld",&m);
                int first;
                for(int v =0 ; v<orderK;v++){
                    if(*(grouporder+v)== -1 ){
                        first = grouporder[v-1];
                        break;
                    }
                }
                go(m,array[first]);
                if(array[first]->head==NULL);{
                    printf("NULL\n");
                    releaseorder(orderK,first,grouporder);
                }
        }else if (strcmp(input , "close")==0){
            scanf("%lld",&m);
            close(m);
        }else{
        }
        
    }
    int order;
    for(ll int iter=0;iter<N;iter++){
        order = grouporder[iter];
        printList(array[order]);
    }
    return 0;
}











































































































