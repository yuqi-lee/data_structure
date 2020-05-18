#include<iostream>
#include"time.h"
using namespace std;

int _count = 0;
int   chessboard[10];       //每行有且只有一个皇后，可用一维数组来表示皇后的坐标

//判断位置是否合法
bool if_valid(int i){
    for(int j = 0;j<i;j++){     //这里的j控制行数，遍历i之前的行
        if( chessboard[i] == chessboard[j]      || 
            chessboard[i]-chessboard[j] == i-j  || 
            chessboard[i]-chessboard[j] == j-i  )   
            
            return(0);  
    }
    return(1);
}

//尝试在第i+1行放皇后
void counter(int i,int n){
    if(i == n){
        //此时n行已经全部放满
        _count++;
        //打印该种情况下的结果
        for(int m = 0;m<n;m++)
        {
            for(int k = 0;k<n;k++)
            {
                if(k == chessboard[m])
                    cout<<"Q ";
                else
                    cout<<"# ";
            }
            cout<<endl;
        }
        cout<<endl;
        return;
    }
    for(int j = 0;j<n;j++)  //这个for控制每一行的所有列均进行尝试。 所有列均尝试完成后，退栈
    {
        chessboard[i] = j;
        if(if_valid(i))     counter(i+1,n);     //若这个插入合法，则开始进行下一行的插入(进入下一个函数）。
                                                //否则，仍停留在该行，向下一列寻找
    }
}

int main(){
    int n;
    cout<<"输入最多皇后数: ";
    clock_t start, finish;    
    double  duration;        
    start = clock();  
    cin>>n;
    counter(0,n);
    cout<<_count<<endl;
    finish = clock();    
    duration = (double)(finish - start) / CLOCKS_PER_SEC;    
    printf( "%f seconds\n", duration );    
    system("pause");
}
