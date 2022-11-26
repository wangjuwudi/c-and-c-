/*  wd  2022.10.31 */
#include <iostream>
#include <stack>
using namespace std;

void init(string (&form)[5][6]);
static string nextToken();
int translation();
string transback(string x0);
bool find(string st);

static string ahead;//输入的字符串的第一个字符
static string substring;//剩余字符

/* first和follow集
   firstE ={(,id}   followE ={$,)}
   firstE'={+,空}      followE'={$,)}
   firstT ={(,id}   followT ={$,+,)}
   firstT'={*,空}      followT'={$,+,)}
   firstF ={(,id}   followF ={$,+,),*}
 */
int main() {
    stack<string> stack; //构造栈
    stack.push("#");  //将# 和 E 压入栈
    stack.push("0");
    string form[5][6]={""};
    init(form);//初始化 分析表
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
            cout<<"匹配"<<ahead<<"成功"<<endl;
            ahead=nextToken();
            stack.pop();

        }else if( find(stack.top())){
            cout<<"匹配错误 非终结符"<<stack.top()<<"未找到匹配，弹出栈"<<endl;
            stack.pop();

        }else if(form[n][translation()].empty()){
            cout<<"匹配错误,跳过"<<ahead<<"  用户多输入了一个"<<ahead<<endl;
            ahead=nextToken();

        }else if(form[n][translation()]==" "){
            cout<<"规约空串"<<transback(stack.top())<<"-> ^"<<endl;
            stack.pop();

        }else{
                string info=form[n][translation()];
                string result;
                cout<<"展开"<<transback(stack.top())<<"->"<<transback(info)<<endl;
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
    if(substring!="#"){cout<<"error  栈空，但是输入未空"<<endl;}
    return 0;
}

// 遍历输入串
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
//将输入串的第一个字符转化为分析表的列数
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
//构造分析表 其中1代表E 0代表E' 2:T 3:T' 4:F
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
//将数字转换回非终结符
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
//判断是否为终结符
bool find (string st){
    string  end[5]={"id","*","+","(",")"};//计录终结符
    for(int i=0;i<5;i++){
        if(st==end[i])
        return true;
    }
    return false;
}
