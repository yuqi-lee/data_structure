#include<stdio.h>
#include<stdlib.h>
typedef int status;     //status的值是函数结果状态码

//传入的p是约瑟夫环顺序表，n即为人数，m为初始报数间隔
int *yoseph(int* p,int n,int m){
    int i ;  //i用于判断是否达到了要求的间隔
    int j = 0;  //j作为p的偏移量
    int counter;
    int *output = (int *)malloc(n*sizeof(int));
    if(!output){
    	printf("申请空间失败！\n");
    	return(NULL);
	}
    for(counter = 0;counter<n;counter++){
        m= m%(n-counter) == 0 ? (n-counter):m%(n-counter);	//化简m         
        for(i = 0;i<m;){
        	j%=n;					//此时j的范围是0到(n-1)，p[j]有效 
            if(p[j])  {i++;j++;}
            else    j++;    
            
        }
        //此时j的范围是1到n ，p[j-1]有效 
		output[counter] = j;
        m = p [j-1];
        p[j-1] = 0;
    	
    	
    }
    
    return (output);
}

status init_ring(int* p,int n,char* s[]){
    int i = 0;
    for(;i<n;i++){
        p[i] = atoi(s[i+3]);
        if(p[i]<=0) return(-1);
    }
    return(1);
}

int main(int argc,char *argv[]){
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    if (n <= 0 || m <= 0 || n!=argc-3)	 
    {
        printf("输入错误\n");
        return (-1);
    }
    int ring[n];
    
   
  	if(-1 == init_ring(ring,n,argv))
    {
        printf("输入错误\n");
        return(0);
    }
    int i;
    int* output = yoseph(ring,n,m);
    
    for(i = 0;i<n;i++)  printf("%d ",output[i]);
    
    //将output写入文件"output01.txt"中 
	FILE *fp = fopen("output01.txt","w");
    if(fp == NULL){
        printf("文件打开错误\n");
    	exit(-1);
    }
    for (i = 0; i < n; i++)
        fprintf(fp ,"%d ",output[i]);	
    fclose(fp);
	getchar();
}