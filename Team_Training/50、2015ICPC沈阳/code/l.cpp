#include<bits/stdc++.h>
using namespace std;
const int MAXN=2000010;
const int INF=~0U>>2;
int tt;
int n,m,s,t;
int vex[MAXN],g[MAXN],nextt[MAXN],cost[MAXN],cap[MAXN],tot=1;
int dis[6000],vis[6000],fa[6000],pos[6000];
int num;
queue <int>Q;

void addin(int u,int v,int e,int c) {
	tot++;
	vex[tot]=v;
	nextt[tot]=g[u];
	cap[tot]=e;
	cost[tot]=c;
	g[u]=tot;
	tot++;
	vex[tot]=u;
	nextt[tot]=g[v];
	cap[tot]=0;
	cost[tot]=-c;
	g[v]=tot;
}
bool bfs() {
	memset(vis,0,sizeof(vis));
	for(int i=1; i<=t; i++) dis[i]=INF;
	vis[s]=1;
	dis[s]=0;
	Q.push(s);
	while(Q.size()) {
		int u=Q.front();
		Q.pop();
		for(int p=g[u]; p; p=nextt[p])
			if(cap[p]&&dis[vex[p]]>dis[u]+cost[p]) {
				dis[vex[p]]=dis[u]+cost[p];
				fa[vex[p]]=u;
				pos[vex[p]]=p;
				if(!vis[vex[p]]) Q.push(vex[p]),vis[vex[p]]=1;
			}
		vis[u]=0;
	}
	return dis[t]<INF;
}
int mincflow() {
	int fl=0,co=0;
	while(bfs()) {
		int delt=INF;
		for(int i=t; i-s; i=fa[i])
			delt=min(delt,cap[pos[i]]);
		fl+=delt;
		co+=dis[t]*delt;
		for(int i=t; i-s; i=fa[i])
			cap[pos[i]]-=delt,cap[pos[i]^1]+=delt;
	}
	if(fl<num) co=-1;
	return co;
}
int cal(int x,int y) {
	return (x-1)*m+y;
}
int main() {
	scanf("%d",&tt);
	for(int cnt=1; cnt<=tt; cnt++) {
		tot=1;
		memset(g,0,sizeof g);
		memset(nextt,0,sizeof nextt);
		num=0;
		int c1 = 0, c2 = 0;
		scanf("%d%d",&n,&m);
		s=n*m*2+1,t=s+1;
		for(int i=1; i<=n; i++)
			for(int j=1; j<=m; j++) {
				int x;
				scanf("%d",&x);
				if(x==0) addin(s,cal(i,j),1,0),addin(m*n+cal(i,j),t,1,0),num++;
				else if(x&1) addin(s,cal(i,j),1,0),num++, c1++;
				else addin(n*m+cal(i,j),t,1,0), c2++;
			}
		for(int i=1; i<=n-1; i++)
			for(int j=1; j<=m; j++) {
				int x;
				scanf("%d",&x);
				addin(cal(i,j),n*m+cal(i+1,j),1,x);
				addin(cal(i+1,j),n*m+cal(i,j),1,x);
			}
		for(int i=1; i<=n; i++)
			for(int j=1; j<=m-1; j++) {
				int x;
				scanf("%d",&x);
				addin(cal(i,j),n*m+cal(i,j+1),1,x);
				addin(cal(i,j+1),n*m+cal(i,j),1,x);
			}
		int t = mincflow(); if (c1 != c2) t = -1; 
		printf("Case #%d: %d\n",cnt,t);
	}
	return 0;
}

