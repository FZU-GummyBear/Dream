/*
let x=f[n]
f[i-1]-f[i]<=0 i -> i-1 0
f[i]-f[i-1]<=1 i-1 -> i 1
f[l-1]-f[r]<=-k r -> l-1 -k
f[r]-f[l-1]<=-k+x l-1 -> r -k+x
f[n]-f[0]<=x 0 -> n x
f[0]-f[n]<=-x n -> 0 -x
for each cycle whose cost is A+Bx, we have A+Bx>=0 -> x>=(-A/B)
so find a cycle with minimum average cost
*/
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef pair<int,int>P;
const int N=3010,M=3010,inf=1000000000;
int Case,n,m1,m2,i,j,k,x,y,z,f[N][N],h[N],ans,nu,nd,tu,td,cnt[N<<1];
vector<P>g[N];
struct E {
	int u,v,w;
} e[M];
inline void up(int&a,int b) {
	a>b?(a=b):0;
}
inline void cal(int u,int d) {
	if(u>=0)return;
	u=-u;
	u=u/d+((u%d)>0);
	if(u>ans)ans=u;
}
inline void solve() {
	int i,j,x,y,base;
	for(i=n; i>1; i--) up(h[i-1], h[i]);
	for(i=1; i<n; i++) up(h[i+1], h[i] + 1);
	base = h[n];
	//h[n] is stable now
	//h[i]=h[i+1] or h[i+1]-1
	//h[n]-h[i] in [0..n]
	//h[n]-h[i]+i in [0..2n]
	for(i=1; i<=n; i++)cnt[base-h[i]+i]++;
	for(i=n; i; i--) {
		cnt[base-h[i]+i]--;
		if(i<n) {
			up(h[i],h[i+1]);
			if(cnt[base-h[i+1]+i+1])h[i]=h[i+1]-1;
		}
		for(j=0; j<g[i].size(); j++) {
			x=g[i][j].first;
			y=h[i]+g[i][j].second;
			if(h[x]>y) {
				cnt[base-h[x]+x]--;
				h[x]=y;
				cnt[base-h[x]+x]++;
			}
		}
	}
}

int main() {
	scanf("%d",&Case);
	while(Case--) {
		scanf("%d%d%d",&n,&m1,&m2); // 1 -> n + 1 
		n++;
		for(i=1; i<=n; i++) g[i].clear();
		while(m1--)scanf("%d%d%d",&x,&y,&z),g[y+1].push_back(P(x,-z));
		for(i=1; i<=m2; i++) {
			scanf("%d%d%d",&x,&y,&z);
			e[i].u=x;
			e[i].v=y+1;
			e[i].w=-z;
		}
		e[++m2].u=1;
		e[m2].v=n;
		e[m2].w=0;
		ans=0;
		//case 1: not passed the edge n -> 0 -x
		for(i=0; i<=n; i++)for(j=1; j<=n; j++)f[i][j]=inf;
		f[0][1]=0; // 走0条到 1号点的最短距离 
		for(i = 0; i <= n; i++) {
			for(j=1; j<=n; j++) h[j] = f[i][j];
			solve(); 
			for(j=1; j<=n; j++) f[i][j] = h[j];
			if(i < n) for(j = 1; j <= m2; j++) up(f[i+1][e[j].v], f[i][e[j].u] + e[j].w);
		}
		for(i=1; i<=n; i++) {
			nu=-inf,nd=1;
			for(j=0; j<n; j++) {
				tu=f[n][i]-f[j][i],td=n-j;
				if(1LL*nu*td<1LL*tu*nd)nu=tu,nd=td;
			}
			cal(nu,nd);
		}
		//case 2: passed the edge n -> 0 -x
		for(i=2; i<=n; i++)cal(f[i][n],i-1);
		printf("%d\n",ans);
	}
}
