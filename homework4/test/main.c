#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
typedef struct node Node;
typedef struct graph Graph;
typedef struct stack stack_t;
struct stack {
    size_t size;
    size_t capacity;
    size_t top;
    int *elements;
};

typedef struct operation{
    char o;
    int int1 ;
    int int2 ;
    } Operation;

struct node{
    Operation* operation;
    int data;  //means 第幾天的事情
    Node* next;
};

struct graph{
    int numVer;
    int time;
    int* predecessor;
    int* color;
    int* ans;
    int* visited;
    Node** adjList;
};

void stack_delete(void *self){
    if (!self) {
        return;
    }

    int *elements = ((stack_t *) self)->elements;
    if (elements)
        free(elements);
    
    free(self);
}
stack_t * stack_new(void){
    stack_t *s = malloc(sizeof(stack_t));
    if (!s)
        return s;

    s->size = 0;
    s->capacity = 2;
    s->top = 0;
    s->elements = malloc(s->capacity * sizeof(int));
    if (!(s->elements)) {
        stack_delete(s);
        s = NULL;
        return s;
    }

    return s;
}
bool stack_is_empty(const stack_t *self){
    assert(self);
    return self->size == 0;
}
int stack_peek(const stack_t *self){
    assert(!stack_is_empty(self));

    return self->elements[self->top];
}
static bool stack_expand(stack_t *self){
    if (self->size < self->capacity) {
        return true;
    }

    int *old_arr = self->elements;
    self->capacity = self->size * 2;
    int *new_arr = malloc(self->capacity * sizeof(int));
    if (!new_arr) {
        return false;
    }

bool stack_push(stack_t *self, int data){
    if (!stack_expand(self))
        return false;

    if (stack_size(self) > 0)
        self->top = (self->top + 1) % self->capacity;

    self->elements[self->top] = data;
    self->size++;

    return true;
}

    size_t sz1 = 0;
    int i = self->top;
    int j = self->top;
    while ( sz1 < self->capacity) {
        new_arr[i] = old_arr[j];

        i = i == 0 ? self->capacity - 1 : i - 1;
        j = j == 0 ? self->size - 1 : j - 1;
        sz1++;
    }

    self->elements = new_arr;
    free(old_arr);

    return true;
}
int stack_pop(stack_t *self){
    assert(!stack_is_empty(self));

    int popped = self->elements[self->top];

    self->top = self->top == 0 ? self->capacity - 1 : self->top - 1;
    self->size--;

    return popped;
}
Node* newnode(Operation* a){
    Node* node = malloc(sizeof(Node));
    node->operation = a;
    node->next = NULL;
    return node;
}
Graph* newgraph(int x){
    int vertices = (int)(x+5);
    Graph* graph =malloc(sizeof(Graph));
    graph->numVer = x;
    graph->adjList = malloc(vertices * sizeof(Node*));
    graph->predecessor =malloc(vertices * sizeof(int));
    graph->color =malloc(vertices * sizeof(int));
    graph->ans =malloc(vertices * sizeof(int));
    graph->visited =malloc(vertices * sizeof(int));
    for(int i = 1; i <= x; i++){
        graph->adjList[i] = NULL;
        graph->color[i] = 0;
        graph->ans[i]=0;
        graph->predecessor[i] = -1;
        graph->visited[i]=0;
    }
    return graph;
}
void addEdge(Graph* graph,Operation* s , Operation* d ,int i ,int j){
    //s to d
    Node* node = newnode(d);
    node->data =i;
    node->next = graph->adjList[i];
    graph->adjList[i] = node;
    // d to s 
    node = newnode(s);
    node->data = j;
    node->next = graph->adjList[j];
    graph->adjList[j] = node;

}
typedef struct disjointSet{
    int parent;
    int rank;
    
    } DisjointSet;

DisjointSet ds[1000001];

bool set[1000001] = {};

void makeset(const int i){
    ds[i].parent = i;
    ds[i].rank = 0;
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
        if (ds[a].rank < ds[b].rank )
         ds[a].parent = b ;
        else if (ds[a].rank > ds[b].rank)
         ds[b].parent = a ;
        else{ //x's rank =y's rank
         ds[b].parent = a ; 
         ds[a].rank +=1 ;//高度相同rank才+1
        }

        return true;
    }
    else{ // merge failed 沒有減
        return false;
    }
void undo(){
    
}
    
}
bool same_set(const int a, const int b) {
    return find_set(a) == find_set(b);
}
int query[1000001]={0};
int main(){
    int N , M , int1 ,int2;
    int Q=1;
    scanf("%d %d", &N ,&M);
    char read[10] = {"\0"} ;
    Graph* graph = newgraph(N);
    Operation* op;
    Operation* optmp ;
    for(int i=0; i<M; i++){
        optmp = op;
        scanf("%s",read);
        if(strcmp(read,"merge")==0){
            scanf("%d %d ", &int1 ,&int2);
            op->o='m';
            op->int1 = int1;
            op->int2 = int2;
            // if(merge(int1,int2)){
            //     N=N-1;
            // }
        }
        else if(strcmp(read,"query")==0){
            
            op->o ='q';
            op->int1 = -1;
            op->int2 = -1;
            query[Q]=i;
            Q++;

            // if(N<=0){
            //     printf("1");
            // }else
            // printf("%d\n",N);
        }
        else if(strcmp(read,"boom")==0){
            scanf("%d", &int1 );
            op->o ='b';
            op->int1 = int1;
            op->int2 = -1;
            //boom(int1);
        }
        printf("iter %d\n",i);
        if(i==0){
        addEdge(graph,op,op,0,0);
        }
        else{
        addEdge(graph,optmp,op,i-1,i);
        }
    }
    int answer[Q]; // Q代表有幾個query
                    // query[j] = 代表在第幾天query
    for(int j =Q; j>0 ; j--){
        memset(set, 0, 1000001);
        int  ans =N;
        for(int k = query[j] ; k >=0 ; k--){  //改成用while 才能處理boom 跳躍的問題
            if(op[k].o='m'){
                if(merge(op[k].int1,op[k].int2)){
                 ans=ans-1;
                }
            }    
        }
        if(ans<=1){
            answer[j]=1;
        }else
        answer[j]=ans;
    }
    for(int j =1; j<Q ; j++){
        printf("%d\n",answer[j]);
    }
    return 0;
}