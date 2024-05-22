#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 300

void ktwice(int* , int , int);
int compare(int*,int*);
void substract(int* , int* ,int);
void divide_by_two(int* , int);
bool iszero(int* ,int);

int main(void){
    // char讀取輸入 並轉換成int儲存
    int a[MAX]={0};int b[MAX]={0};
    for(int i = 0; i<MAX+1; i++){
        a[i]=0;
        b[i]=0;
    }
    int * m = a; int*n = b; 

    char input1[MAX], input2[MAX];
    int k = 0; //k 次方數
    scanf("%s%s",input1,input2);
    int len1 =strlen(input1) ,len2 =strlen(input2); // 紀錄input 的長度
    for(int i = 0; i<len1; i++){
       a[len1-i-1]= input1[i] - '0'; // 寫入數字並轉成int
    }

    for(int i = 0; i<len2; i++){
        b[len2-i-1] = input2[i] - '0';
    }
    int max_size = len1>len2 ? len1 : len2;
    
    if (compare(a,b)>=0){
         m = a ;
         n = b ;
    }
    else{
        m = b ;
        n = a ;
    }
    // algorithm
    while(!iszero(m,max_size)&&!iszero(n,max_size)){
        if(m[0]%2==0 &&n[0]%2==0){
            k++;
            divide_by_two(m,max_size);
            divide_by_two(n,max_size);
        }
        else if (m[0]%2==0 ){
            divide_by_two(m,max_size);
        }
        else if (n[0]%2==0 ){
            divide_by_two(n,max_size);
        }
        if (compare(n,m)>0){
            int * tmp =n;
            n = m;
            m = tmp;

        }
        substract(m,n,max_size);
    }
    ktwice(n,k,max_size);
    bool zero = true;
    for (int i = (max_size - 1); i >= 0; i--){
        if (n[i] != 0 && zero)
            zero = false;
        if (!zero)
            printf("%d", n[i]);
    }
    return 0;
}



void ktwice (int* a , int k , int size){
    int tmp = 0 ;
    for(int time = 0 ; time < k ; time++ ){
        for( int i = 0 ; i<=size ;i++){
            a[i]*=2;
            a[i]+=tmp;//加上進位
            tmp = 0 ;//進位清0
            tmp = a[i]/10;// if a[i]> 10 tmp有值  otherwise tmp = 0
            a[i]%=10;
            if (i==size && tmp!=0){
                size+=1;
            }
        }
    }
}
int compare(int*a ,int*b ){
    //兩數比大小 a>b 回傳正數 a<b回傳負數 a=b回傳0
    //從最後一位(此時為數字的最大位數)開始互相比較，兩個不同時互減
    int i=MAX-1;
    while(i>0 && a[i]==b[i]){
        --i;  
    }
    return a[i]-b[i];
}
void substract(int * a , int *b ,int size){//兩數相減  only 大減少 a-b 賦值回給a
    int tmp = 0 , res[size];
    memset(res,0,size);
    for(int i = 0 ; i<size;i++){
        res[i]=a[i]-b[i]-tmp;
        if (res[i]<0){
            tmp=1 ;
            res[i]+=10;
        }
        else{
            tmp = 0;
        }
        a[i] = res[i];
    }

}
void divide_by_two(int * a , int size){ //3.數字除以2 奇數會忽略尾數
    int i = size;
    while(i >=0){
        if (a[i] % 2 == 1 ){
            a[i-1]+=10;
        }
        a[i] = a[i] / 2 ;
        i--;
    }
}
bool iszero (int* a , int size){
    for (int i = 0; i < size; i++){
        if (a[i] != 0)
            return false;
    }

    return true;
}