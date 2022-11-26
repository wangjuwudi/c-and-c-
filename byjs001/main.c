#include<stdlib.h>
#include<stdio.h>
 int main(){
    char c[100];
    int length=0;
    for(int i=0;getchar()!='\n';i++){
        length++; 
        scanf("%c",c[i]);
    }
    for(int j=0;j<length;j++){
        printf("%c",c[j]);
    }
    system("pause");
    return 0;
 }