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
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 5050, M = 200005, B = 20;
const db eps = 1e-9, inf = 1e16;
db dis[N], w;
bool vis[N], tree[M];
int n, m, S, T, fa[N], st[N], top, u, v;

struct Graph{
	int h[N], ne[M], to[M], e;
	db w[M];
	inline void add(int u, int v, db val){
		ne[++e] = h[u], h[u] = e, to[e] = v, w[e] = val;
	}
} g, rg;

void Dij(){
	rep(i, 1, n+1) dis[i] = inf;
	priority_queue<pair<db, int> > pq;
	pq.push(mp(dis[T] = 0, T));
	while(!pq.empty()){
		int u = pq.top().se; pq.pop();
		if (vis[u]) continue; vis[u] = 1;
		for (int i = rg.h[u]; i; i = rg.ne[i]) {
			int v = rg.to[i];
			if (dis[v] > dis[u] + rg.w[i] + eps) {
				dis[v] = dis[u] + rg.w[i];
				pq.push(mp(-dis[v], v));
			}
		}
	}
}


void dfs(int u){
	st[++top] = u; vis[u] = 1;
	for (int i = rg.h[u]; i; i = rg.ne[i]) {
		int v = rg.to[i];
		if (!vis[v] && fabs(dis[v] - dis[u] - rg.w[i]) <= eps) {
			fa[v] = u; tree[i] = 1;
			dfs(v);
		}
	}
}

int rt[N];

namespace LT{
	int tot;
	struct node{
		int ls, rs, ht, id;
		db val;
		node(db val = 0, int id = 0, int dis = 0) : val(val), id(id), ht(dis), ls(0), rs(0) {}
	} tr[M * B];
	
	inline int merge(int a, int b){
		if(!a || !b) return a|b;
		if(tr[a].val > tr[b].val) swap(a, b);
		int now = ++tot; node &p = tr[now];
		p = tr[a]; p.rs = merge(p.rs, b);
		if(tr[p.ls].ht < tr[p.rs].ht) swap(p.ls, p.rs);
		p.ht = tr[p.rs].ht + 1;
		return now;
	}
	
	inline void ins(int &rt, db val, int id){
		++tot; tr[tot] = node(val, id);
		rt = merge(rt, tot);
	}
}

void build_heap(){
	rep(j, 1, top+1) {
		int u = st[j];
		rt[u] = rt[fa[u]];
		for (int i = g.h[u]; i ; i = g.ne[i]) {
			int v = g.to[i];
			if (!tree[i] && dis[v] < inf) LT::ins(rt[u], dis[v] - dis[u] + g.w[i], v);
		}
	}
}

typedef pair<db, int> pdi;

db E;

inline int calc_K(){
	using namespace LT;
	int ans = 1; E -= dis[S];
	priority_queue<pdi, vector<pdi>, greater<pdi> > pq;
	if (rt[S]) pq.push(mp(dis[S] + tr[rt[S]].val, rt[S]));
	while(!pq.empty()){
		pdi t = pq.top(); pq.pop();
		db w = t.fi; int u = t.se, o = tr[u].id;
		E -= w; if (E >= 0) ++ans; else return ans;
		int ls = tr[u].ls, rs = tr[u].rs;
		if (rt[o]) pq.push(mp(w + tr[rt[o]].val, rt[o]));
		if (ls) pq.push(mp(w + tr[ls].val - tr[u].val, ls));
		if (rs) pq.push(mp(w + tr[rs].val - tr[u].val, rs));
	}
	return ans;
}

int main(){
//	freopen("lx.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> E;
	S = 1; T = n;
	rep(i, 1, m+1) {
		cin >> u >> v >> w;
		g.add(u, v, w);
		rg.add(v, u, w);
	}
	Dij(); 
	rep(i, 1, n+1) vis[i] = 0;
	dfs(T);
	build_heap();
	cout << calc_K() << endl;
	return 0;
}
