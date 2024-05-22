#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
typedef struct node Node;
typedef struct graph Graph;
struct node{
    int data;
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

Node* newnode(int a){
    Node* node = malloc(sizeof(Node));
    node->data = a;
    node->next = NULL;
    return node;
}
Graph* newgraph(int x){
    int vertices = (int)(2*x);
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
void addEdge(Graph* graph,int s , int d ){
    //s to d
    Node* node = newnode(d);
    node->next = graph->adjList[s];
    graph->adjList[s] = node;
    // d to s 
    node = newnode(s);
    node->next = graph->adjList[d];
    graph->adjList[d] = node;

}
void DFSvisit(Graph* graph,int vertex){
    graph->color[vertex] = 1;
    Node* adjList = graph->adjList[vertex];
    Node* tmp = adjList;
    while(tmp!=NULL){
        int connected = tmp->data;
        if(graph->color[connected]==0){
            graph->predecessor[connected] = vertex;
            DFSvisit(graph,connected);
        }
        tmp = tmp->next;
    }
    graph->color[vertex] =2;
}
void DFS(Graph* graph,int start){
    int i = start;
    for (int j =1 ; j<=graph->numVer; j++){
        if (graph->color[i]==0){
            DFSvisit(graph,i);
        }
        i =j;
    }
}
void find_SR_line(Graph* graph , int end){
    int cur = end;
    while(cur!=-1){
        graph->ans[cur] =cur;
        graph->visited[cur] =1;
        cur=graph->predecessor[cur];

    }
};
void _DFSvisit(Graph* graph,int vertex,const int start){
    graph->visited[vertex] = 1;
    Node* adjList = graph->adjList[vertex];
    Node* tmp = adjList;
    while(tmp!=NULL){
        int connected = tmp->data;
        if(graph->visited[connected]==0){
            graph->ans[connected]= start;
            _DFSvisit(graph,connected,start);
        }
        tmp = tmp->next;
    }
    graph->visited[vertex] =2;
}
void _DFS(Graph* graph,int start){
    int i = start;
    for (int j =1 ; j<=graph->numVer+1; j++){
        if (graph->visited[i]!=0){ // 做出以SR line 的 N個子樹
            _DFSvisit(graph,i,i);
        }
        i =j;
    }
}
int main (){
    int N ,Q ,S ,R;
    int a ,b;
    int query;
    scanf("%d %d %d %d",&N,&Q,&S,&R);
    if(S==R){
        for(int i=1;i<N;i++){ //讀取剩下N-1條路 and do nothing
            scanf("%d %d",&a,&b);
        }
        for(int i=0;i<Q;i++){   //讀取 Q個 query 並且print out 結果
            scanf("%d",&query);
            printf("%d\n",S);
        }
    }
    else{
        Graph* graph = newgraph(N);
        for(int i=1;i<N;i++){ //讀取剩下N-1條路 創建 adj list
            scanf("%d %d",&a,&b);
            addEdge(graph,a,b);
        } 
        DFS(graph,S);
        
        find_SR_line(graph,R);
        ///拆成小樹
        for(int i = 1; i <= graph->numVer+1; i++){
            if(graph->ans[i]!=0){
                graph->visited[i]=2;
            }
            else{
                graph->ans[i]=0;
                graph->visited[i]=0;
            }
        }
        free(graph->color);
        free(graph->predecessor);
        _DFS(graph,S);
        
        free(graph->visited);
        for(int i=0;i<Q;i++){   //讀取 Q個 query 並且print out 結果
            scanf("%d",&query);
            printf("%d\n",graph->ans[query]);            
        }
        free(graph->ans);
        free(graph->adjList);
        free(graph);
    }
    

    return 0;
}