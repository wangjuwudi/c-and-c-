#include <stdio.h>
#include <stdlib.h>

void hanoi(int n,char one,char two,char three)
 /*  ����hanoi����,������̴�one������two�����Ƶ�three�� */
 {
  void move(char x,char y);     /* ��move���������� */
  if(n==1) move(one,three);
     else
      {  hanoi(n-1,one,three,two) ;//�ݹ����
         move(one,three);
         hanoi(n-1,two,one,three);  //�ݹ����
 }

  }
void move(char x,char y)           /* ����move���� */
 {
    printf("%c-->%c\n",x,y);
}

int main()
{
   hanoi(4,'A','B','C');
    return 0;
}
