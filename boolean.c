#include<stdio.h>
int andfunc(int,int);
int orfunc(int,int);
int notfunc(int,int);
int nandfunc(int, int);
int norfunc(int,int);
int xorfunc(int,int);
int xnorfunc(int,int);
int main(){
    int x,y;
    printf("Input A:");
    scanf("%d",&x);

    printf("Input B:");
    scanf("%d",&y);
    printf("AND:%d\n", andfunc(x,y));
    printf("OR:%d\n", orfunc(x,y));
    return 0;
}
int andfunc(int x, int y){
    int z;
    if(x==0||y==0){
         z=0;
    }
    else if(x==1&&y==1){
        z = 1;
    }
    else{
        z = 0;
    }
    return z;
}
int orfunc(int x,int y){
    int z;
    if(x==1||y==1){
         z=1;
    }
    else if(x==1&&y==1){
        z = 1;
    }
    else{
        z = 0;
    }
    return z;
}