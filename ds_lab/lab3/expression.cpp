#include <iostream>
using namespace std;
typedef struct BiTreeNode{
	char data[10];
	BiTreeNode *lchild;
    BiTreeNode *rchild;
}BiTreeNode,*BiTree;

bool if_operator(char* c){
	if(strlen(c)>1)
        return(false);
    switch ( *c ) 
	{
		case '+':
		case '-':
		case '*':
		case '/':return	(true);
		default:
			break;
	}
	return(false);
}//if_operator

int compare(char c1,char c2){
    //若优先级c1>c2，则返回1；若c1=c2，则返回0；若c1<c2,则返回-1
	if(c1 == '+' || c1 == '-')
	{
		if(c2 == '*' || c2 == '/')
			return(-1);
		else
			return(0);
	}	
	else
	{
		if(c2 == '*' || c2 == '/')
			return(0);
		else
			return(1);
	}
}//compare

void CreatTree(BiTree &bt){
	
	bt = new BiTreeNode;
	cin>>bt->data;
	int status = if_operator(bt->data);
	
	if(status)
	{
		
		bt->lchild = bt->rchild = NULL;
		CreatTree(bt->lchild);
		CreatTree(bt->rchild);
	}
	else
		return;
}//CreatTree

void InOrderTraverse(BiTree &bt){
	int status = 0;	//status用于判断是否需要匹配括号
	if(bt != NULL)
	{
		if(if_operator(bt->data) && if_operator(bt->lchild->data))
			if(compare(*bt->data,*bt->lchild->data) == 1)
			{
				cout<<"(";
				status = 1;
			}
		InOrderTraverse(bt->lchild);
		if(status == 1)
		{
			cout<<")";
			status = 0;
		}//匹配括号

		atof(bt->data)<0 ? cout<<"("<<bt->data<<")":cout<<bt->data;

		if(if_operator(bt->data) && if_operator(bt->rchild->data))
			if(compare(*bt->data,*bt->rchild->data) != -1)
			{
				cout<<"(";
				status = 1;
			}
		InOrderTraverse(bt->rchild);
		if(status == 1)
			cout<<")";//匹配括号
	}
	return;
}//InOrderTraverse

void PostOrderTraverse(BiTree &bt){
	if(bt != NULL)
	{
		PostOrderTraverse(bt->lchild);
		PostOrderTraverse(bt->rchild);
		cout<<bt->data<<' ';
	}
	return;
}//PostOrderTraverse

float Operate(float a,float b,char c){
	switch (c)
	{
		case '+':return(a+b);
		case '-':return(a-b);
		case '*':return(a*b);
		case '/':return(a/b);
		default:
			break;
	}
	exit(0);
}//Operate

float calculate(const BiTree bt){
	float a,b;
	if(if_operator(bt->lchild->data))
		a = calculate(bt->lchild);	//递归求左子树的值
	else 
		a = atof(bt->lchild->data);
	if(if_operator(bt->rchild->data))
		b = calculate(bt->rchild);	//递归求右子树的值
	else
		b = atof(bt->rchild->data);
	float result = Operate(a,b,*bt->data);
	return(result);
}//calculate

void destroy(BiTree &bt){
	if(bt->lchild)
		destroy(bt->lchild);
	if(bt->rchild)
		destroy(bt->rchild);
	delete bt;
	return;
}//destroy

int main(){
	BiTree root = NULL;
	CreatTree(root);
	InOrderTraverse(root);
	cout<<endl;
	PostOrderTraverse(root);
	cout<<endl;
	float i = calculate(root);
	cout<<i<<endl;
	destroy(root);
}