#include <stdio.h>
#include "graphics.h"
#include <fstream>
struct ToaDo{
	int x,y;
};
int n,k=0,d=0,alone[1001],cal=0;
int matrix[1001][1001];
bool visited[1001];
int Q[1001],father[1001],result[1001];
void Init()
{	
	FILE *fi;
    fi= fopen("data.txt","rt");
    fscanf(fi,"%d",&n);
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            fscanf(fi,"%d",&matrix[i][j]);
        }
        visited[i] = false;
    }
    fclose(fi);
    for(int i=0;i<1001;i++){
    	Q[i]=NULL;
	}
}

void push(int Q[],int u){
	Q[k]=u;
	k++;
}

void pop(int Q[]){
	if(k==1){
		Q[0]=NULL;
		k--;
	}else{
		for(int i=0;i<k-1;i++){
			Q[i]=Q[i+1];
		}
		Q[k-1]=NULL;
		k--;
	}
}

void BFS(int u)
{
    printf("BFS (%d):\n",u);
    push(Q,u);
    visited[u] = true;
    father[u]=0;
    while(k!=0)
    {	
        int s = Q[0];
        pop(Q);
        result[d]=s;
        d++;
        for(int t = 1; t <= n; t++)
        {
            if(visited[t] == false && matrix[s][t] == 1)
            {	
            	father[t]=s;
                push(Q,t);
                visited[t] = true;
            }
        }	
    }
    for(int t = 1; t <= n; t++){
    	if(visited[t] == false){
    		alone[cal]=t;
    		cal++;
		}
	}
}

void graphic(){
	char c[20],t=1;
	int haveFather[n];
	for(int i = 0; i < n; i++) haveFather[i] = 0;
	ToaDo td[n];
	initwindow(1400,800);
    settextstyle(DEFAULT_FONT,0,2);
	sprintf(c,"%d",result[0]);  
	outtextxy(30,500,c);
	setcolor(9);
	circle(38,510,25);
	td[result[0]].x=38; td[result[0]].y=510; 
	int xt=0,yt=0,k=1,a=0,lv[n];
	lv[result[0]]=0;
	for(int i=0;i<d;i++){
		for(int j=i+1;j<d;j++){
			if(father[result[j]]==result[i]){
				lv[result[j]]=lv[result[i]]+1;
			}
		}
	}
	for(int i=1;i<d;i++){
		if(a!=lv[result[i]]){
			a=lv[result[i]];
			xt=a*100+38;
			yt=510-a*100;
		}else yt+=100;
		sprintf(c,"%d",result[i]);
		setcolor(15);
		outtextxy(xt-8,yt-10,c);
		setcolor(9);
		circle(xt,yt,25); 
		td[result[i]].x=xt; td[result[i]].y=yt; 
	}
		xt=a*100+138;
		yt=510-a*100;
	for(int i=0; i<cal;i++){
		yt-=100;
		sprintf(c,"%d",alone[i]);
		setcolor(15);
		outtextxy(xt-8,yt-10,c);
		setcolor(9);
		circle(xt,yt,25); 
	}
	for(int i=0;i<d-1;i++){
		for(int j=i+1;j<d;j++){
			if(lv[result[i]]==lv[result[j]]) continue;
			if(haveFather[result[j]] == true) continue;
			if(matrix[result[i]][result[j]] == 1) {
	        	line(td[result[i]].x,td[result[i]].y,td[result[j]].x,td[result[j]].y);
				haveFather[result[j]] = true;
	   		}
		}
	}
	while(!kbhit()) delay(1);
	
}
int main()
{
    int u;
    Init();
    printf("Chon dinh bat dau :");
    scanf("%d",&u);
    BFS(u);
    graphic();
    return 0;
}



