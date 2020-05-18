#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
#define INIT_SIZE 20
typedef int status;

template<typename T> 
class Queue {
private:
    int _capacity;
    int _front, _rear;
    T* _elem;
public:    
    Queue(int n);
    ~Queue() { delete[] _elem; } 
    T DeQueue();
    void EnQueue(T const& e);
    bool if_empty(){return(_front == _rear ? true:false);}
};

template<typename T>
Queue<T>::Queue(int n) 
{
    _capacity = n;
    _front = _rear = 0; 
    _elem = new T[n];
}
template<typename T>
T Queue<T>::DeQueue() 
{
    if (_front == _rear) 
        exit(-1);
    T e = _elem[_front];
    _front = (_front + 1) % _capacity; 
    return(e);
}
template<typename T>
void Queue<T>:: EnQueue(T const& e) 
{
    if (((_rear + 1) % _capacity) == _front) 
        exit(0);
    _elem[_rear] = e;
    _rear = (_rear + 1) % _capacity; 
}

struct ArcNode
{
    int adjvex;
    ArcNode*  nextarc;
};

struct VNode
{
    int vertex;
    ArcNode* firstedge;
    VNode(){firstedge = NULL;} 
};

struct ALGraph
{
    ALGraph(ifstream &fin);
    int vex_num,arc_num;
    vector<VNode*> vertices;
};

ALGraph::ALGraph(ifstream &fin)
{
    fin>>vex_num;
    for(int i = 0;i<vex_num;i++)
    {
        vertices.push_back(new VNode);
        vertices[i]->firstedge = NULL;
    }
    int v1,v2;
    arc_num = 0;
    while(!fin.eof())   //头插法建立邻接表
    {
        fin>>v1;fin>>v2;
        ArcNode* p = vertices[v1]->firstedge;
        vertices[v1]->firstedge = new ArcNode;
        vertices[v1]->firstedge->adjvex = v2;
        vertices[v1]->firstedge->nextarc = p;
        p = vertices[v2]->firstedge;
        vertices[v2]->firstedge = new ArcNode;
        vertices[v2]->firstedge->adjvex = v1;
        vertices[v2]->firstedge->nextarc = p;
        arc_num++;    
    }
}

void Print_List(ALGraph &G)
{
    for(int i = 0; i < G.vex_num; i++)
    {
        cout<<i;
        for(ArcNode* p = G.vertices[i]->firstedge; p ;p = p->nextarc)
            cout<<"->"<<p->adjvex;
        cout<<endl;
    }
}

void BFS_FindPath(ALGraph &G)
{
    /*设置局部变量*/
    Queue<int> Q(G.vex_num);
    vector<vector<int> > path(G.vex_num);
    bool final[G.vex_num];
    int distance[G.vex_num];
    for(int i = 0;i<G.vex_num;i++)
    {
        final[i] = false;
        distance[i] = G.vex_num;    
    }
    int _distance = 1;
    int rear,rear_temp;
    //进行第一次搜索
    for(ArcNode* p = G.vertices[0]->firstedge; p ; p=p->nextarc)
    {   
        Q.EnQueue(p->adjvex);   //与v0相邻的边进入队列，作为下一次搜索的出发点之一
        final[p->adjvex] = true;    //标记为已访问
        distance[p->adjvex] = _distance;    //记录距离
        path[p->adjvex].push_back(p->adjvex);   //记录路径
        if(p->nextarc == NULL)  
            rear = p->adjvex;   //用于控制距离增长
    }
    _distance++;
    //进行之后的搜索
    while(!Q.if_empty())
    {
        int v = Q.DeQueue();    //从v出发广度优先搜索
        for(ArcNode* p = G.vertices[v]->firstedge; p ; p = p->nextarc)
        {   
            if(final[p->adjvex] == false)   //与v相邻且未访问过的节点
            {
                rear_temp = p->adjvex;
                Q.EnQueue(p->adjvex);
                final[p->adjvex] = true;
                distance[p->adjvex] = _distance;
                /*复制重复路径*/
                path[p->adjvex] = path[v];
                path[p->adjvex].push_back(p->adjvex);
            }
            if( p->nextarc == NULL && rear == v )
            {
                rear = rear_temp;
                _distance++;
            }        
        }   
    }
    for(int j = 1;j < G.vex_num;j++)
    {
        cout<<distance[j]<<" 0";
        for(int k = 0;k<path[j].size();k++)
                cout<<"->"<<path[j][k];
        cout<<endl;
    }
    return;   
}
int main(){
    ifstream fin;
    fin.open("case2.txt",ios_base::in);
    ALGraph G(fin);   
    fin.close();
    //Print_List(G);
    BFS_FindPath(G);
}