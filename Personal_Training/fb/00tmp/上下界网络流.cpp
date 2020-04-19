#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) (a).begin(), (a).end()
#define pw(x) (1ll<<(x))
#define lb(x) ((x) & -(x))
#define endl "\n"
#define FI(x) freopen(#x".in","r",stdin)
#define FO(x) freopen(#x".out","w",stdout)
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
//typedef uniform_int_distribution<ll> RR;
//mt19937 gen(998244353);
//ll rnd(ll l, ll r) { RR dis(l, r); return dis(gen); }
const int P = 1e9 + 7;
int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a < 0 ? a + P : a;
}
int mul(int a, int b) {
	return 1ll * a * b % P;
}
int kpow(int a, int b) {
	int r=1;
	for(; b; b>>=1,a=mul(a,a)) {
		if(b&1)r=mul(r,a);
	}
	return r;
}
//----

const int N=110,inf=~0U>>2;
int n,m,i,j,w,t,S,T,SS,TT,h[N],gap[N],maxflow,sum,in[N],id[N];
struct edge {
	int t,f;
	edge*nxt,*pair;
}*g[N],*d[N];
void add(int s,int t,int f) {
	edge *p=new(edge);
	p->t=t;
	p->f=f;
	p->nxt=g[s];
	g[s]=p;
	p=new(edge);
	p->t=s;
	p->f=0;
	p->nxt=g[t];
	g[t]=p;
	g[s]->pair=g[t];
	g[t]->pair=g[s];
}
int sap(int v,int flow,int S,int T) {
	if(v==T)return flow;
	int rec=0;
	for(edge *p=d[v]; p; p=p->nxt)if(h[v]==h[p->t]+1&&p->f) {
			int ret=sap(p->t,min(flow-rec,p->f),S,T);
			p->f-=ret;
			p->pair->f+=ret;
			d[v]=p;
			if((rec+=ret)==flow)return flow;
		}
	d[v]=g[v];
	if(!(--gap[h[v]]))h[S]=TT;
	gap[++h[v]]++;
	return rec;
}
int main() {
	scanf("%d%d%d%d" ,&n,&m,&S,&T);
	for(i=1; i<=n; i++)id[i]=i;
	swap(id[S],id[n-1]),swap(id[T],id[n]);
	S=n-1,T=S+1,SS=T+1,TT=SS+1;
	add(T,S,inf);
	while(m--) {
		scanf("%d%d%d%d",&i,&j,&w,&t);
		i=id[i],j=id[j];
		if(t)in[i]-=w,in[j]+=w;
		else add(i,j,w);
	}
	for(i=1; i<=TT; i++)if(in[i]>0)sum+=in[i],add(SS,i,in[i]);
		else add(i,TT,-in[i]);
	for(gap[i=0]=TT; i++<TT;)d[i]=g[i];
	while(h[SS]<TT)maxflow+=sap(SS,inf,SS,TT);
	if(sum!=maxflow)return puts("-1"),0;
	for(maxflow=i=0; i<=TT; i++)d[i]=g[i],h[i]=gap[i]=0;
	gap[0]=TT;
	while(h[S]<TT)maxflow+=sap(S,inf,S,T);
	printf("%d",maxflow);
}



