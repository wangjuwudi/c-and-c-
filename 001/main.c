#include <stdio.h>
#include <stdlib.h>

void hanoi(int n,char one,char two,char three)
 /*  定义hanoi函数,将ｎ个盘从one座借助two座，移到three座 */
 {
  void move(char x,char y);     /* 对move函数的声明 */
  if(n==1) move(one,three);
     else
      {  hanoi(n-1,one,three,two) ;//递归调用
         move(one,three);
         hanoi(n-1,two,one,three);  //递归调用
 }

  }
void move(char x,char y)           /* 定义move函数 */
 {
    printf("%c-->%c\n",x,y);
}

int main()
{
   hanoi(4,'A','B','C');
    return 0;
}
