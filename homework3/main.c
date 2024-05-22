#include<stdio.h>
#include<stdlib.h>
#include <string.h>
void printString(char *ch){
    while (*ch != '\0'){
        putchar(*ch); 
        ch = ch + 1;
    }
}
char *strrev(char *str){
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

   
int main(){
    char a[20000001];
    char c[20000001];
    int ch;
    size_t index = 0;
    size_t chars_read = 0;
    while((ch = getchar()) !='\n'&&ch!=EOF){
        if (index < sizeof(a)-1){
            a[index++] = (char)ch;
        }
        chars_read++;
    }
    a[index] = '\0';

    int lens = strlen(a);
    
    int n=lens;
    char b[n+1];
    strcpy(b,a);
    strcpy(c,a);
    *strrev(c);
    a[n] = '`';
    a[n+1] = '\0';
    c[n] = '`';
    c[n+1] = '\0';
    n = strlen(a);
    for(int i=0; i<n-1; i++){
      a[i+n] = a[n-i-2];
    }
    a[(2*n) + 1] = '\0';
    for(int i=0; i<n-1; i++){
      c[i+n] = c[n-i-2];
    }
    c[(2*n) + 1] = '\0';
    
/////////////////////////////////////////////////////
    int lps1[strlen(c)];
    lps1[0] = 0; 
    int i1 = 1, len1=0; 
    while (i1 < strlen(c)) { 
        if (c[i1] == c[len1]) { 
            len1++; 
            lps1[i1] = len1; 
            i1++; 
        } 
        else { 
            if (len1 != 0) { 
                len1 = lps1[len1-1]; 
            } 
            else{ 
                lps1[i1] = 0; 
                i1++; 
            } 
        } 
    }
////////////////////////////////////////////////////////////////

    int lps[strlen(a)];
    lps[0] = 0; 
    int i = 1, len=0; 
    while (i < strlen(a)) { 
        if (a[i] == a[len]) { 
            len++; 
            lps[i] = len; 
            i++; 
        } 
        else { 
            if (len != 0) { 
                len = lps[len-1]; 
            } 
            else{ 
                lps[i] = 0; 
                i++; 
            } 
        } 
    }
//////////////////////////////////////////////////////////////

    
    int forward = lens-lps[strlen(a)-1];
    int backward = lens-lps1[strlen(c)-1];
    
    if(forward == 0 || backward == 0){
        printf("%d\n",0);
        printString(b);
    }
    else{
        if(forward < backward) {
            printf("%d\n",forward);
            char f[lens-lps[strlen(a)-1]];
            f[lens-lps[strlen(a)-1]]='\0';
            for(int i=0; i<lens-lps[strlen(a)-1]; i++){
                f[i]=b[lens-i-1];
            }
            printString(f);
            printString(b);
            printf("\n");
        }
        else if(backward < forward) {
            printf("%d\n",backward);
            printString(b);
            char f[lens-lps1[strlen(c)-1]];
            f[lens-lps1[strlen(c)-1]]='\0';
            for(int i=0; i<lens-lps1[strlen(c)-1]; i++){
                f[i]=b[lens-lps1[strlen(c)-1]-i-1];
            }
            printString(f);
        }
        else if(backward == forward){
            printf("%d\n",backward);
            char f[lens-lps[strlen(a)-1]];
            f[lens-lps[strlen(a)-1]]='\0';
            for(int i=0; i<lens-lps[strlen(a)-1]; i++){
                f[i]=b[lens-i-1];
            }
            printString(f);
            printString(b);
            printf("\n");

            printString(b);
            char e[lens-lps1[strlen(c)-1]];
            e[lens-lps1[strlen(c)-1]]='\0';
            for(int i=0; i<lens-lps1[strlen(c)-1]; i++){
                e[i]=b[lens-lps1[strlen(c)-1]-i-1];
            }
            printString(e);
        }
    }
        
}


