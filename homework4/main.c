#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// typedef struct node Node;
// typedef struct graph Graph;
// typedef struct stack stack_t;
// struct stack {
//     size_t size;
//     size_t capacity;
//     size_t top;
//     int *elements;
// };

// struct node{
//     int data;
//     Node* next;
// };

// struct graph{
//     int numVer;
//     int time;
//     int* predecessor;
//     int* color;
//     int* ans;
//     int* visited;
//     Node** adjList;
// };

// stack_t * stack_new(void){
//     stack_t *s = malloc(sizeof(stack_t));
//     if (!s)
//         return s;

//     s->size = 0;
//     s->capacity = 2;
//     s->top = 0;
//     s->elements = malloc(s->capacity * sizeof(int));
//     if (!(s->elements)) {
//         stack_delete(s);
//         s = NULL;
//         return s;
//     }

//     return s;
// }
// void stack_delete(void *self)
// {
//     if (!self) {
//         return;
//     }

//     int *elements = ((stack_t *) self)->elements;
//     if (elements)
//         free(elements);
    
//     free(self);
// }
// bool stack_is_empty(const stack_t *self){
//     assert(self);
//     return self->size == 0;
// }
// int stack_peek(const stack_t *self){
//     assert(!stack_is_empty(self));

//     return self->elements[self->top];
// }
// bool stack_push(stack_t *self, int data){
//     if (!stack_expand(self))
//         return false;

//     if (stack_size(self) > 0)
//         self->top = (self->top + 1) % self->capacity;

//     self->elements[self->top] = data;
//     self->size++;

//     return true;
// }
// static bool stack_expand(stack_t *self){
//     if (self->size < self->capacity) {
//         return true;
//     }

//     int *old_arr = self->elements;
//     self->capacity = self->size * 2;
//     int *new_arr = malloc(self->capacity * sizeof(int));
//     if (!new_arr) {
//         return false;
//     }

//     size_t sz = 0;
//     int i = self->top;
//     int j = self->top;
//     while (sz < self->capacity) {
//         new_arr[i] = old_arr[j];

//         i = i == 0 ? self->capacity - 1 : i - 1;
//         j = j == 0 ? self->size - 1 : j - 1;
//         sz++;
//     }

//     self->elements = new_arr;
//     free(old_arr);

//     return true;
// }
// int stack_pop(stack_t *self){
//     assert(!stack_is_empty(self));

//     int popped = self->elements[self->top];

//     self->top = self->top == 0 ? self->capacity - 1 : self->top - 1;
//     self->size--;

//     return popped;
// }
// Node* newnode(int a){
//     Node* node = malloc(sizeof(Node));
//     node->data = a;
//     node->next = NULL;
//     return node;
// }
// Graph* newgraph(int x){
//     int vertices = (int)(x+5);
//     Graph* graph =malloc(sizeof(Graph));
//     graph->numVer = x;
//     graph->adjList = malloc(vertices * sizeof(Node*));
//     graph->predecessor =malloc(vertices * sizeof(int));
//     graph->color =malloc(vertices * sizeof(int));
//     graph->ans =malloc(vertices * sizeof(int));
//     graph->visited =malloc(vertices * sizeof(int));
//     for(int i = 1; i <= x; i++){
//         graph->adjList[i] = NULL;
//         graph->color[i] = 0;
//         graph->ans[i]=0;
//         graph->predecessor[i] = -1;
//         graph->visited[i]=0;
//     }
//     return graph;
// }
// void addEdge(Graph* graph,int s , int d ){
//     //s to d
//     Node* node = newnode(d);
//     node->next = graph->adjList[s];
//     graph->adjList[s] = node;
//     // d to s 
//     node = newnode(s);
//     node->next = graph->adjList[d];
//     graph->adjList[d] = node;

// }

typedef struct disjointSet{
    int parent;
    int size;
    int rank;
    
    } DisjointSet;

DisjointSet ds[1000001];

bool set[1000001] = {};
char operation[1000000];
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
    
    
}

bool same_set(const int a, const int b) {
    return find_set(a) == find_set(b);
}
int main(){
    int N , M , int1 ,int2;
    int day = 0 , current_day=0;
    scanf("%d %d", &N ,&M);
    char read[10] = {"\0"} ;
    for(int i=0; i<M; i++){
        scanf("%s",read);
        if(strcmp(read,"merge")==0){
            scanf("%d %d ", &int1 ,&int2);
            if(merge(int1,int2)){
                N=N-1;
            }
        }
        else if(strcmp(read,"query")==0){
            if(N<=0){
                printf("1");
            }else
            printf("%d\n",N);
        }
        else if(strcmp(read,"boom")==0){
            scanf("%d", &int1 );
            //boom(int1);
        }
        ++day;
    }



    return 0;
}