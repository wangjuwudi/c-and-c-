#include <stdio.h>
#include <stdlib.h>
int main()
{
    double a=1,b=1,c=0;
    while(a<=30)
    {
        b=b*a;
        c=c+b;
        a++;
    }
    printf("%.2e",c);
    return 0;
}
