/*  wd  2022.10.31 */
#include <iostream>
#include <stack>
using namespace std;

void init(string (&form)[5][6]);
static string nextToken();
int translation();
string transback(string x0);
bool find(string st);

static string ahead;//������ַ����ĵ�һ���ַ�
static string substring;//ʣ���ַ�

/* first��follow��
   firstE ={(,id}   followE ={$,)}
   firstE'={+,��}      followE'={$,)}
   firstT ={(,id}   followT ={$,+,)}
   firstT'={*,��}      followT'={$,+,)}
   firstF ={(,id}   followF ={$,+,),*}
 */
int main() {
    stack<string> stack; //����ջ
    stack.push("#");  //��# �� E ѹ��ջ
    stack.push("0");
    string form[5][6]={""};
    init(form);//��ʼ�� ������
   // cout<<form[0][0]<<endl;



    string input;
    cin>>input;
    
    substring=input;
    ahead=nextToken();
    cout<<substring<<endl;


    while(stack.top()!="#"){
        const char *m=stack.top().c_str();
        int n=*m-48;
        //cout<<stack.top()<<" "<<ahead<<endl;
        if(stack.top()==ahead){
            cout<<"ƥ��"<<ahead<<"�ɹ�"<<endl;
            ahead=nextToken();
            stack.pop();

        }else if( find(stack.top())){
            cout<<"ƥ����� ���ս��"<<stack.top()<<"δ�ҵ�ƥ�䣬����ջ"<<endl;
            stack.pop();

        }else if(form[n][translation()].empty()){
            cout<<"ƥ�����,����"<<ahead<<"  �û���������һ��"<<ahead<<endl;
            ahead=nextToken();

        }else if(form[n][translation()]==" "){
            cout<<"��Լ�մ�"<<transback(stack.top())<<"-> ^"<<endl;
            stack.pop();

        }else{
                string info=form[n][translation()];
                string result;
                cout<<"չ��"<<transback(stack.top())<<"->"<<transback(info)<<endl;
                stack.pop();
                for(int i=info.length(); i>0;i--){
                    if(info.substr(0,2)=="id"){
                        stack.push("id");
                        info.erase(0,2);
                        i--;
                        result="id";
                    }else {
                        string in = info.substr(0, 1);
                        stack.push(in);
                        info.erase(0, 1);
                    }

                }
            }
        }
    if(substring!="#"){cout<<"error  ջ�գ���������δ��"<<endl;}
    return 0;
}

// �������봮
static string nextToken() {
    if (substring.length() >= 2) {
        if (substring.substr(0,2)=="id") {
            substring = substring.erase(0,2);
            ahead = "id";
        } else {
            ahead = substring.substr(0, 1);
            substring = substring.erase(0,1);
        }
    } else if (substring.length() == 1) {
        ahead = substring.substr(0, 1);
    }
    return ahead;
}
//�����봮�ĵ�һ���ַ�ת��Ϊ�����������
int translation (){
   if(ahead=="id"){
       return 0;
   }else if(ahead=="+"){
       return 1;
   }else if(ahead=="*"){
       return 2;
   }else if(ahead=="("){
       return 3;
   }else if(ahead==")"){
       return 4;
   }else if(ahead=="#"){
       return 5;
   }else{return 6;}
}
//��������� ����1����E 0����E' 2:T 3:T' 4:F
void init(string (&form)[5][6]) {
    form[0][0]="12";
    form[0][3]="12";
    form[1][1]="12+";
    form[1][4]=" ";
    form[1][5]=" ";
    form[2][0]="34";
    form[2][3]="34";
    form[3][1]=" ";
    form[3][2]="34*";
    form[3][4]=" ";
    form[3][5]=" ";
    form[4][0]="id";
    form[4][3]=")0(";
}
//������ת���ط��ս��
string transback(string x0){
    int x;
    string result;
    for(int i=0;i<x0.length();i++){
        if(x0.substr(0,2)=="id"){
            result="id";
        }else {
            string in = x0.substr(x0.length()-1-i,x0.length()-i);
            if(in>="0"&&in<"9"){
                const char *x1=in.c_str();
                x=*x1-48;
                switch(x) {
                    case 0:
                        result = result + "E";
                        break;
                    case 1:
                        result = result + "E'";
                        break;
                    case 2:
                        result += "T";
                        break;
                    case 3:
                        result += "T'";
                        break;
                    case 4:
                        result += "F";
                        break;
                    default:
                        result += "_";
                }
            } else result+=in;
        }
    }
    return result;
}
//�ж��Ƿ�Ϊ�ս��
bool find (string st){
    string  end[5]={"id","*","+","(",")"};//��¼�ս��
    for(int i=0;i<5;i++){
        if(st==end[i])
        return true;
    }
    return false;
}
