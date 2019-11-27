#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    int num;    
    struct Node *next;
};


struct Node* Init_linklist(struct Node* head,int n,int* input){
    //利用命令行传递的参数，及刚刚申请的头指针创建链表(尾插法)，并且返回尾指针
    struct Node *p, *s;
    p = head;
    int i;
    for (i = 1; i <= n; i++)
    {
        s = (struct Node *)malloc(sizeof(struct Node));
        s->data = input[i-1];    
        if (s->data <= 0)
        {
            printf("输入错误\n");
            return (NULL);
        }
        s->num = i;
        p->next = s;
        p = s;
    }
    p->next = head->next;	//此时p恰为循环表的尾指针 
    return(p);
}


int *yoseph(struct Node *p, int n, int m)
{//	传入循环链表的尾指针p，人数n，初始报数间隔m 每个人对应的密码已在链表中置好,返回一个int型数组output
    if (!p)
        return (NULL);
    struct Node *s;
    s = p->next;
    int counter;	//counter记录被删去的人数 
    int *output = (int *)malloc(n * sizeof(int)); 
	int i;
    for (counter = 0; counter < n; counter++)
    {
    	m= m%(n-counter) == 0 ? (n-counter):m%(n-counter);	//化简m		n-counter为表中现有人数 
        for (i = 1; i < m; i++)
        {
            p = p->next;
            s = s->next;
        }
        m = s->data;
        output[counter] = s->num;
        p->next = s->next;
        free(s);
        if (p)
            s = p->next;
    }
    return (output);
}
int main(int argc, char *argv[])
{
	//初始化n,m
    int n;
    int m;
    if(argc == 1){
        printf("请输入参数n,m:");
        scanf("%d",&n);
        scanf("%d",&m);
        printf("\n");
    }
    else{
        n = atoi(argv[1]);
        m = atoi(argv[2]);
    }
    struct Node *head = (struct Node *)malloc(sizeof(struct Node));
    if (!head)
        return (-1);
    int i;
    if (n <= 0 || m <= 0 || (n!=argc-3&&argc!=1))	///////////////argc<n+3 
    {
        printf("输入错误\n");
        return (-1);
    }
    int input[n];
    int *output = NULL;
    if(argc>1)
    {
        int k;
        for(k = 0;k<n;k++)      
            input[k] = atoi(argv[i+3]);
        output = yoseph(Init_linklist(head,n,input), n, m);
    }
    else
    {
        int k = 0;
        printf("请依次输入%d个人的密码：",n);
        for(;k<n;k++)
        {
            printf("\n第%d个人的密码是：",k+1);
            scanf("%d",input+k);
        }
        output = yoseph(Init_linklist(head,n,input), n, m);
    }
    for (i = 0; i < n; i++)     //输出output
        printf("%d ", output[i]);
	//将output写入文件"output00.txt"中 
	FILE *fp = fopen("output00.txt","w");
    if(fp == NULL){
        printf("文件打开错误\n");
    	exit(-1);
    }
    for (i = 0; i < n; i++)
        fprintf(fp ,"%d ",output[i]);	
    fclose(fp);
    getchar();
}