#include <iostream>
#include <stdlib.h>
using namespace std;
#define INIT_SIZE 20
#define thread 1
#define link 0

typedef struct BiTreeNode{
	char data;
    BiTreeNode *parent;
	BiTreeNode *lchild;
    BiTreeNode *rchild;
    int ltag,rtag;
}BiTreeNode,*BiTree;
 
struct CQueue{
	BiTree *elem;
	int front;
	int rear;
};
 
void Init_Queue(CQueue &q){
//初始化一个队列
	q.elem = (BiTree *)malloc(sizeof(BiTree) * INIT_SIZE);
	if(!q.elem) 
        exit(0);
	q.front = q.rear = 0;
}//InitQueue
 
void EnQueue(CQueue &q,BiTree bt){
//数据进队
	if( ((q.rear + 1)%INIT_SIZE) == q.front) 
        exit(0);
	q.elem[q.rear] = bt;
	q.rear = (q.rear + 1)%INIT_SIZE;
}//EnQueue
 
bool if_empty(CQueue &q){
//判断是否为空
	return q.front == q.rear? true:false;
}//if_empty

BiTree DeQueue(CQueue &q){
//出队列，返回值是出队列的元素（ BiTree型 ）
	if(if_empty(q)) 
        return(NULL);
	BiTree bt = q.elem[q.front];
	q.front = (q.front +1 )%INIT_SIZE;
    return(bt);
}//DeQueue

BiTree CreatTree(){
    char c1;
    cin>>c1;
    if(c1 == '#')
        return(NULL);
    BiTree bt = (BiTree)malloc(sizeof(BiTreeNode));
    bt->data = c1;
    bt->lchild  = NULL;
    bt->rchild	= NULL;
    bt->parent  = NULL;
    CQueue Q;
    Init_Queue(Q);
    EnQueue(Q,bt);  //根结点进队列
    while(!if_empty(Q))
    {
        BiTree p = DeQueue(Q);  //下一个结点出队列，等待判断其左右孩子的实/虚
        cin>>c1;
        if(c1 != '#')
        {//p左孩子为实结点
            p->lchild = (BiTree)malloc(sizeof(BiTreeNode));
            p->lchild->data = c1;
            p->lchild->parent = p;
            p->lchild->lchild = NULL;
            p->lchild->rchild = NULL;
            EnQueue(Q,p->lchild);   //p的左孩子进队列，等待被赋为实/虚结点
        }
        cin>>c1;
        if(c1 != '#')
        {//p右孩子为实结点
            p->rchild = (BiTree)malloc(sizeof(BiTreeNode));
            p->rchild->data = c1;
            p->rchild->parent = p;
            p->rchild->lchild = NULL;
            p->rchild->rchild = NULL;
            EnQueue(Q,p->rchild);   //p的右孩子进队列，等待被赋为实/虚结点
        }
    }
    return(bt);
}//CreatTree

void PreOrderTraverse(BiTree const bt){
    //先序遍历
	if(bt){
		cout<<bt->data;
        if(!bt->ltag)
		    PreOrderTraverse(bt->lchild);
        if(!bt->rtag)
		    PreOrderTraverse(bt->rchild);
	}
}//PreOrderTraverse

void InOrderTraverse(BiTree const bt){
    //中序遍历
	if(bt){
        if(!bt->ltag)
		    InOrderTraverse(bt->lchild);
        cout<<bt->data;
        if(!bt->rtag)
		    InOrderTraverse(bt->rchild);
	}
}//InOrderTraverse

void PostOrderTraverse_Thr(BiTree  const bt){
    //非递归遍历后序线索二叉树
    BiTree p;
    p = bt;
    while(p->lchild)    
        p = p->lchild;      //找到后序遍历第一个被visit的结点
    for(;;)
    {
        cout<<p->data;
        if(p == bt)
        //当p为根结点时，不再有后继，结束循环
            break;
        else if(p->rtag == thread)
        {//若p的右孩子已被线索化，则p直接前往它的后继（它的右孩子）
            p = p->rchild;
            continue;
        }    
        else if(( p->parent->rtag == link && p == p->parent->rchild )//若p为右孩子
                ||             p->parent->rtag == thread          )//或者p为左孩子且p的父结点无右孩子
            p = p->parent;                                         //此时p的后继为其父结点
        else
        {//若p为父结点的左孩子且其父结点有右孩子，则p的后继为其父结点右子树中第一个被visit的结点
            p = p->parent->rchild;
            while(!(p->ltag && p->rtag))    
            {
                if(p->ltag == link)
                    p = p->lchild;
                else 
                    p = p->rchild;
            }
        }
    }
    return;
}//PostOrderTraverse_Thr

BiTree PreNode = NULL;  //全局变量PreNode记录前驱结点的位置
void PostOrderThreading(BiTree  &bt){
    if(!bt)
        return;
    PostOrderThreading(bt->lchild); //线索化左右子树
    PostOrderThreading(bt->rchild);

    if(bt->lchild == NULL)
    {
        bt->lchild = PreNode;
        bt->ltag = thread;
    }
    else
        bt->ltag = link;
    if(PreNode != NULL && PreNode->rchild == NULL)
    {
        PreNode->rchild = bt;
        PreNode->rtag = thread;
    }
    else if(PreNode != NULL)
        PreNode = link;
    
    PreNode =  bt;
    return;  
}//PostOrderThreading

void destroy(BiTree &bt){
	if(bt->ltag == link && bt->lchild != NULL )
		destroy(bt->lchild);
	if(bt->rtag == link && bt->rchild != NULL)
		destroy(bt->rchild);
	free(bt);
	return;
}//destroy

int main(){
    BiTree bt;
    bt = CreatTree();
    PostOrderThreading(bt);     //将构建的二叉树线索化
    PreNode = NULL;
    cout<<"先序遍历如下："<<endl;
    PreOrderTraverse(bt);
    cout<<endl;
    cout<<"中序遍历如下："<<endl;
    InOrderTraverse(bt);
    cout<<endl;
    cout<<"后序遍历如下："<<endl;
    PostOrderTraverse_Thr(bt);
    cout<<endl;
    destroy(bt);
}