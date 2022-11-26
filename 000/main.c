#include<stdio.h>
int main()
{
    int a=0;
    scanf("%d", &a);
    int b=0,c=0;
    b=a%10;
    c=(a%100-b);
    printf("%d\n%d\n%d",(a-c-b)/100,c/10,b);
    return 0;
}
