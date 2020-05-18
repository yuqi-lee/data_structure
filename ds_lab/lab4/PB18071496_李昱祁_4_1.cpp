#include<iostream>
#include<algorithm>
#include<fstream>
#include<vector>
#include<stack>
using namespace std;
typedef int status;

class Mgraph
{
public:
    Mgraph(){arcs = NULL;vex_num = arcs_num = 0;}
    Mgraph(ifstream &fin);
    ~Mgraph();
    bool** arcs;
    int vex_num,arcs_num;
    vector<bool> visited;
    vector<int>  order;
    vector<int>  low;
    vector<int>  articul;
};

Mgraph::~Mgraph()
{
    for (int j = 0; j<vex_num; j++)
    {
        delete[]arcs[j];
    }
    delete[]arcs;
}

Mgraph::Mgraph(ifstream &fin)   //读取文件中数据构造图
{
    fin>>vex_num;
    arcs = new bool* [vex_num];
    for(int i = 0;i<vex_num;i++)
        arcs[i] = new bool[vex_num]();      
    int v1,v2;
    while(!fin.eof())
    {
        fin>>v1;
        fin>>v2;
        arcs[v1][v2] = arcs[v2][v1] = 1;
        arcs_num++;
    }
    visited.assign(vex_num,false);
    order.assign(vex_num,0);
    low.assign(vex_num,vex_num);
    return;
}                                                                                                                                                                                                                            

void DFS(Mgraph &G,int v1,int &count)
{
    int e;
    stack<int> S;
    int v2 = 0;
    int _v1 = v1;
    vector<int> min(G.vex_num);
    do{  
        if(G.order[v1] == 0 )
            G.order[v1] = min[v1] = ++count;
        for(;v2<G.vex_num;v2++)
        {
            if(G.arcs[v1][v2] == 1 )    //v1与v2之间存在边
            {
                if(G.visited[v2] == false) //v2未曾访问，是v1的孩子
                {
            	    G.visited[v2] = true;
                    //DFS(G,w,count); 
                    S.push(v1);
                    v1 = v2;
                    v2 = 0;
                    break;
                }    
                else if(G.order[v2] < min[v1]) //v2已访问，是v1在生成树上的祖先
                    min[v1] = G.order[v2];
            }    
        }//for
        /*叶子节点直接被排除*/
        if(v2 == G.vex_num) //此时自v1已经无法向下进行,已访问完v1的所有子树,计算low[v1] 
        {
            G.low[v1] = min[v1];    
            v2 = v1;
            if(v1 != _v1)
            {
                v1 = S.top();
                S.pop();
            }
            else
                break;
            if(G.low[v2] < min[v1])
                min[v1] = G.low[v2];
            if(G.low[v2] >= G.order[v1])    //v1的任意孩子没有指向v1祖先的回边
                G.articul.push_back(v1);                    
        }         
    }while(!S.empty() || v1 == _v1);
    return;
}

void Print_Graph(Mgraph &G)
{
    ofstream fout;
    fout.open("graph.dot",ios_base::out);
    fout<<"digraph G{"<<endl;
    for(int i = 0;i<G.vex_num;i++)
    {
        for(int j = i;j<G.vex_num;j++)
        {
            if(G.arcs[i][j] == true )
                fout<<i<<" -> "<<j <<" [arrowhead= none]"<<endl;
        }
    }
    fout<<"}";
    fout.close();
    system("dot -Tpng graph.dot -o sample.png");
    return;
}
void FindArticul(Mgraph &G)
{   //从v0顶点出发访问
    int count = 1;
    int v2 = 1;
    G.order[0] = 1;
    G.visited[0] = true;
    for(int v1=0;v2 < G.vex_num;v2++)
    {
        if(G.arcs[v1][v2])
        {
        	G.visited[v2] = true; 
            DFS(G,v2,count);    //从第v2顶点出发深度优先查找关节点
            break;
        }
    }
    if(count < G.vex_num)   //此时根节点已确定为关节点
    {
        G.articul.push_back(0);
        for(int v1=0;v2<G.vex_num;v2++)
        {
            if(G.arcs[v1][v2] && G.visited[v2] == false)
            {
                G.visited[v2] = true;
                DFS(G,v2,count);
            }
        }
    }    
}

int main(){
    ifstream fin;
    fin.open("case2.txt",ios_base::in);
    Mgraph G(fin);
    fin.close();
    Print_Graph(G);
    FindArticul(G);
    sort(G.articul.begin(),G.articul.end());
    vector<int> :: iterator ite = unique(G.articul.begin(),G.articul.end());
    if(ite != G.articul.end())
        G.articul.erase(ite,G.articul.end());
    int size = G.articul.size();
    for(int i = 0;i<size;i++)
        cout<<G.articul[i]<<" ";
    cout<<endl;
    return 0;  
}