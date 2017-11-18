#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int **mat1,**mat2,**ans;
int *ival,*jval,*kval;
int nthread=0,s_mat1, s_mat2;
void *work(void *);

int main(void)
{
    pthread_t id;    
    int i,j,m,k;    

    ival=(int *)malloc(sizeof(int)*(s_mat1*s_mat1*s_mat1));
    jval=(int *)malloc(sizeof(int)*(s_mat1*s_mat1*s_mat1));
    kval=(int *)malloc(sizeof(int)*(s_mat1*s_mat1*s_mat1));
    
    printf("Enter The Size of First Matrix");
    scanf("%d",&s_mat1);
    printf("Enter The Size of Second matrix");
    scanf("%d",&s_mat2);
    mat1=(int **)malloc(sizeof(int)*s_mat1);
    for(i=0;i<s_mat1;i++)
    {
        mat1[i]=(int *)malloc(sizeof(int)*s_mat1);
    }
    mat2=(int **)malloc(sizeof(int)*s_mat2);
    for(i=0;i<s_mat2;i++)
    {
        mat2[i]=(int *)malloc(sizeof(int)*s_mat2);
    }
    
    ans=(int **)malloc(sizeof(int)*s_mat1);
    for(i=0;i<s_mat1;i++)
    {
        ans[i]=(int *)malloc(sizeof(int)*s_mat1);
    }
    printf("\nEnter The Element for the Matrix 1:");
    for(i=0;i<s_mat1;i++)
    {
        for(j=0;j<s_mat1;j++)
        {
            scanf("%d",&mat1[i][j]);
        }
    }
    printf("\nEnter the Element for the Matrix 2:");
    
    for(i=0;i<s_mat2;i++)
    {
        for(j=0;j<s_mat2;j++)
        {
            scanf("%d",&mat2[i][j]);
        }
    }
    printf("Matrix 1\n");
    for(i=0;i<s_mat1;i++)
    {
        for(j=0;j<s_mat1;j++)
        {
            printf("%d\t",mat1[i][j]);
        }
        printf("\n");
    }    
    printf("Matrix 2\n");
    for(i=0;i<s_mat2;i++)
    {
        for(j=0;j<s_mat2;j++)
        {
            printf("%d\t",mat2[i][j]);
        }
        printf("\n");
    }

    printf("OK done");
    m=0;
    for(i=0;i<s_mat1;i++)
    {
        for(j=0;j<s_mat1;j++)
        {
            for(k=0;k<s_mat1;k++)
            {
                ival[m]=i;
                jval[m]=j;
                kval[m]=k;
                m=m+1;
            }
        }
    }        

    printf("\n\n");
    printf("Enter The No Of Thread");
    scanf("%d",&nthread);
    for(i=0;i<nthread;i++)
    {
        if(0==pthread_create(&id,NULL,work,(void *)&i))
        {
            continue;
        }
        else
        {
            printf("Problem In Thread Creation");
        }
    }
    pthread_join(id,NULL);
    printf("\n\nANSWER IS\n:");
    for(i=0;i<s_mat2;i++)
    {
        for(j=0;j<s_mat2;j++)
        {
            printf("%d\t",ans[i][j]);
        }
    }
}

void *work(void *i)
{
    int *tid;
    int ind1,ind2,ind3,k,j;
    int **res;
    printf("Thread");
    tid=(int *)i;
    
    printf("TID:%d",*tid);
    res=(int**)malloc(sizeof(int)*s_mat1);
    for(j=0;j<s_mat1;j++)
    {
        res[j]=(int *)malloc(sizeof(int)*s_mat1);
    }
    
    for(j=*tid;j<(s_mat1*s_mat1*s_mat1);j+=nthread)
    {
        ind1=ival[j];
        ind2=jval[j];
        ind3=kval[j];
        res[ind1][ind2]+=mat1[ind1][ind3]*mat2[ind3][ind2];
    }
    for(k=0;k<s_mat1;k++)
    {
        for(j=0;j<s_mat1;j++)
        {
            ans[k][j]=ans[k][j]+res[k][j];
        }
    }
    return(0);
}