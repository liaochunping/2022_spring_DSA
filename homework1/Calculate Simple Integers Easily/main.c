#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#define ll long long
/////////////////////////////////////////////////////////////////////////////////
                        //////////數字stack///////////
/////////////////////////////////////////////////////////////////////////////////
typedef struct node Node;        //把struct node 改稱為 Node
struct node{                      // linked lsit node
    ll int data ;              //linked list 資料
    Node * next;            // node指標 指向下一個node
};
typedef struct stack Stack; //把struct stack 改稱為Stack
struct stack{               // 改稱struct stack Stack
    Node * top;             // 指出stack 的 top 在哪裡 移入移出都是改 linked lsit 的 top 
    int size  ;              // stack 的大小
};

void stackfree(Stack*);         //刪掉(free)stack 
ll int peek(const Stack *);        //看stack的最上面的值
void push(Stack * , const ll int); //data放入stack
ll int  pop(Stack * );             //取出stack最上面的值
//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
                        //////////符號stack///////////
/////////////////////////////////////////////////////////////////////////////////
typedef struct nodec NodeC; //把struct node 改稱為 Node
struct nodec{             // linked lsit node
    char data ;              //linked list 資料
    NodeC * next;            // node指標 指向下一個node
};
typedef struct stackc StackC; //把struct stack 改稱為Stack
struct stackc{               // 改稱struct stack Stack
    NodeC * top;             // 指出stack 的 top 在哪裡 移入移出都是改 linked lsit 的 top 
    int size  ;              // stack 的大小
};

void stackfreeC(StackC*);         //刪掉(free)stack 
char peekC(const StackC *);        //看stack的最上面的值
void pushC(StackC * , const char); //data放入stack
char  popC(StackC * );             //取出stack最上面的值
//////////////////////////////////////////////////////////////////////////////////////

ll int operate(ll int ,ll int , char);
int getIndex(char);             // operator into int and 比大小
char priority(char ,char);       //判斷兩個operator的順序

int main (){
    bool continued =true;
    Stack * new_stack = malloc(sizeof(Stack));      //創造一個Stack叫new_stack 來存 數字
    StackC * new_stackC = malloc(sizeof(StackC));   //創造一個StackC叫new_stackC 來存 符號
    new_stack->size = 0;                            //初始化stack的size =0
    new_stack->top =NULL;
    new_stackC->size = 0;
    new_stackC->top =NULL;
    ll int n=0 ;
    ll int a,b,sum;
    char input, tmp_operator;
    scanf("%c",&input);
    pushC(new_stackC, '$');
    {
        while(peekC(new_stackC)!= '='){
            if(input>='0' &&input<='9'){                //如果是數字
                n = n*10+input-'0';                     //轉成int 暫存在n(用來處理大數字)
                scanf("%c",&input);
            }                                           //碰到operator
            else{                                       
                if(n!=0){                               //if暫存區有數字
                    push(new_stack, n);                 // push到數字stack
                    n = 0 ;
                    
                }
                    else{
                        if(getIndex(input)==-1){
                            break;
                        }
                        else{
                            switch(priority(input,peekC(new_stackC))){    //讀入的operator 跟stack_operator的頂端比順序
                                    case '^':{                             //input 為=
                                        
                                        while(getIndex(peekC(new_stackC))!=0){          //   在遇到(前 所有的運算吐出來計算
                                                    tmp_operator = popC(new_stackC) ;   // 退出stack_operator
                                                    a = pop(new_stack);                 //取出stack的兩個數字
                                                    b = pop(new_stack);
                                                    sum = operate(a,b,tmp_operator);    //計算
                                                    push(new_stack,sum);  
                                        }
                                                
                                        printf("Print: %lld\n",new_stack->top->data);
                                        scanf("%c",&input);
                                        break;
                                    }
                                    case '>':{                          //stack_operator的頂端的順序低
                                        pushC(new_stackC,input);        //input 壓進去Stack_operator頂端
                                        scanf("%c",&input);           //重製input 重跑while
                                        break;
                                    }
                                    
                                    case '<':{                               //stack_operator的頂端的順序高或是一樣 
                                        tmp_operator = popC(new_stackC) ;   // 退出stack_operator
                                        a = pop(new_stack);                 //取出stack的兩個數字
                                        b = pop(new_stack);
                                        sum = operate(a,b,tmp_operator);    //計算
                                        push(new_stack,sum);                //數字存回去
                                                                            //input沒有更新，從跑一次while重新比較c 的順序
                                        break;
                                    }
                                    case'#':{                               //括號計算
                                        if(getIndex(input)==7&&getIndex(peekC(new_stackC))==6){//如果讀入是) stack頂是( 
                                            tmp_operator = popC(new_stackC) ;// pop掉(
                                            scanf("%c",&input);           //重製input洗掉) 重跑while
                                            break;
                                        }
                                        else{
                                            if(getIndex(input)==6||getIndex(peekC(new_stackC))==6){   //輸入是( 或是stack頂是( [已經排除()相遇的狀況]
                                                
                                                pushC(new_stackC,input);            //
                                                scanf("%c",&input);
                                                break;
                                            }
                                            
                                            else if(getIndex(input)==7){               //輸入是)
                                                while(getIndex(peekC(new_stackC))!=6){          //   在遇到(前 所有的運算吐出來計算
                                                    tmp_operator = popC(new_stackC) ;   // 退出stack_operator
                                                    a = pop(new_stack);                 //取出stack的兩個數字
                                                    b = pop(new_stack);
                                                    sum = operate(a,b,tmp_operator);    //計算
                                                    push(new_stack,sum);  
                                                }
                                                break;
                                            }
                                        }
                                    }
                                    default:{
                                        scanf("%c",&input); 
                                    }
                            }//switch
                        }
                    }
            }//else
        }//while
    }
    stackfree(new_stack);
    stackfreeC(new_stackC);
    return 0 ;
}//main



void stackfree(Stack* stack){
    Node * tmp = stack ->top;   //tmp指向linked list 的top
    while(tmp){                 //tmp沒有指向NULL前
        Node* tmp2 = tmp;       //tmp2 指向tmp指的同一個node
        tmp = tmp->next;        //tmp指向下一個 tmp2指的不變
        free(tmp2);             //free 掉tmp2指的的node
    }
    free(stack);                //free 整個stack占用的空間
}
ll int peek (const Stack * stack){
    return stack->top ->data; //偷看stack的top node的data
}
void push(Stack* stack , const ll int data){
    Node *new_node = (Node*)malloc(sizeof(Node)); //創造記憶體給Node
    new_node->next = NULL;
    new_node-> data = data;                //賦值data 給 新的Node
    new_node-> next = stack->top;          // 新的Node 的下一格指向原本stack的top
    stack->top = new_node;                  // 原本的stack的top指標更新為 指向新的Node
    stack->size +=1;                         // stack 的size+1
}
ll int pop (Stack* stack){
    Node * tmp = stack -> top ; // Node 指標tmp 指向 stack的top node
    ll int pop  = stack->top->data ;     //top node 的值賦予pop
    stack->top = tmp->next ;    // 改原本的stack 的top node 為下一個 node
    stack->size -=1;            // stack 的size-1
    free(tmp);                  //被取出值的node 要釋放掉，不然link list 仍然存著這格node 會在isempty出錯
    return pop;
}

///////////////////////////////////////////////////////////////////////////////////////////



void stackfreeC(StackC* stack){
    NodeC * tmp = stack ->top;   //tmp指向linked list 的top
    while(tmp){                 //tmp沒有指向NULL前
        NodeC* tmp2 = tmp;       //tmp2 指向tmp指的同一個node
        tmp = tmp->next;        //tmp指向下一個 tmp2指的不變
        free(tmp2);             //free 掉tmp2指的的node

    }
    free(stack);                //free 整個stack占用的空間
}
char peekC (const StackC * stack){
    return stack->top ->data; //偷看stack的top node的data
}
void pushC(StackC* stack , const char data){
    NodeC *new_node = (NodeC*)malloc(sizeof(NodeC)); //創造記憶體給Node
    new_node->next = NULL;
    new_node-> data = data;                //賦值data 給 新的Node
    new_node-> next = stack->top;          // 新的Node 的下一格指向原本stack的top
    stack->top = new_node;                  // 原本的stack的top更新為 新的Node
    stack->size +=1;                         // stack 的size+1
}
char popC (StackC* stack){
    NodeC * tmp = stack -> top ; // Node 指標tmp 指向 stack的top node
    char pop  = tmp ->data ;     //top node 的值賦予popped
    stack->top = tmp->next ;    // 改原本的stack 的top node 為下一個 node
    stack->size -=1;            // stack 的size-1
    free(tmp);                  //被取出值的node 要釋放掉，不然link list 仍然存著這格node 會在isempty出錯
    return pop;
}

ll int operate(ll int b ,ll int a , char char1 ){
    switch(char1){
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '%': return a%b;
        case '/': {
            ll int f =(ll int)floor(a/b);
            ll int k = a/b;
            if(a>=k*b)
            return k;
            return k-1;
            }
        default: return 0;
    }
}

int getIndex(char char1){
    switch (char1){
        case '=': return 1;
        case '+': return 4;
        case '-': return 4;
        case '*': return 5;
        case '%': return 5;
        case '/': return 5;
        case '(': return 6;
        case ')': return 7;
        case '$': return 0;
    }
    return -1;
}  

char priority(char char1 ,char char2){
    int i ,j ;
    i = getIndex(char1);
    j = getIndex(char2);
    if(i==6 || i==7 ||j==6){                   //進入括號特殊判斷
        return '#';
    }
    else if(i==1){
        return '^';
    }
    else{
        if (i-j>0){
            return '>';                // char1 >char2
        }
        else{
            return '<';               // char2 >char1
        }
    }
}

