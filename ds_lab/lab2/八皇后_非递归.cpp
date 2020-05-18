#include<iostream>
#include"time.h"
using namespace std;
typedef int status;
#define OK 1

int _count = 0;
struct SqStack{
    int* elem;
    int top;
    int maxsize;
};

void init_stack(SqStack &S,int n)
{
    S.elem = (int*)malloc(n*sizeof(int));
    S.top = -1;
    S.maxsize = n;
    return;
}

int pop(SqStack &S)
{
    int e;
    if(S.top == -1)
        e = -2;         //栈中元素均为自然数，返回负值时表明进行pop前栈已空    
    else
    {    
        e = S.elem[S.top];
        S.top--;
    }
    return(e);
}

status push(SqStack &S,int e)
{
    if(S.top>=S.maxsize-1)
        exit(-1);
    else
    {
        S.top++;
        S.elem[S.top] = e;
    }
    return(OK);  
}

void stack_destroy(SqStack &S)
{
    free(S.elem);
    S.maxsize = 0;
    S.top = -1;
    return;
}

bool judge_queen(SqStack &S)
{
    //检验栈顶元素是否合法
    for(int j = 0;j<S.top;j++){     //这里的j控制行数，遍历i之前的行
        if( S.elem[S.top]==S.elem[j] || 
            S.elem[S.top]-S.elem[j] == S.top-j || 
            S.elem[S.top]-S.elem[j] == j-S.top )   
            return(0);  
    }
    return(1);
}
void print(const SqStack &S,int n)
{
     //打印该种情况下的结果
        for(int m = 0;m<n;m++)
        {
            for(int k = 0;k<n;k++)
            {
                if(k == S.elem[m])
                    cout<<"Q ";
                else
                    cout<<"# ";
            }
            cout<<endl;
        }
        cout<<endl;
        return;
}
void counter(SqStack &S,int n){
    int j = 0;
    do
    {
        if(S.top == n-1)
        {   /* n行已被全部占满，得到一种可行的情况
                记录、打印出该结果之后，最后一行的j向下一列移动 */
            _count++;
            print(S,n);
            j = pop(S);
            j++;
            continue;
        }
        if(j == n)
        {//若j已经试遍了某行的所有列，则上一行的皇后向下一列移动
            j = pop(S);
            j++;
            continue;
        }
        push(S,j);  //将皇后放在该行第j列
        if(judge_queen(S))
        {//插入位置合法，进入下一行寻找
            j = 0;
            continue;
        }
        else
        {//插入位置非法，j出栈，向该行的下一列寻找
            pop(S);
            j++;
        }    
    }while( j != -1 );//结束条件为第一行所有列已尝试完毕
}//counter

int main(){
    SqStack S;
    clock_t start, finish;    
    double  duration;        
    start = clock();    
   

    int n ;
    cout<<"请输入n：";
    cin>>n;
    init_stack(S,n);
    int j = 0;
    counter(S,n);
    cout<<_count<<endl;
    stack_destroy(S);
    finish = clock();    
    duration = (double)(finish - start) / CLOCKS_PER_SEC;    
    printf( "%f seconds\n", duration );   
    stack_destroy(S); 
    system("pause");
}

