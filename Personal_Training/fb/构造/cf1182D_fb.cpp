//#pragma GCC optimize(3)
//#pragma GCC optimize("unroll-loops")
//#pragma GCC target("sse2")
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

const int N = 1e5 + 7, se1 = 23333, se2 = 1e9 + 31;
int du[N], d[N], pre[N], u, v, n, ha[N], son[N];
vi g[N];

void dfs(int u, int fa) {
	for (auto v : g[u]) if (v != fa){
		d[v] = d[u] + 1;
		pre[v] = u;
		dfs(v, u);
	}
}

bool check(int u, int fa) {
	for (auto v : g[u]) if (v != fa) {
		d[v] = d[u] + 1;
		if (!check(v, u)) return 0;
		if (du[d[v]] == 0) du[d[v]] = sz(g[v]);
		else if (du[d[v]] != sz(g[v])) return 0;
	}
	return 1;
}

void dfs2(int u, int fa) {
	son[u] = u; ha[u] = se1;
	for (auto v : g[u]) if (v != fa) {
		dfs2(v, u);
		son[u] = son[v];
		ha[u] = mul(ha[u], se2 ^ ha[v]);
	} 
}

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	rep(i, 1, n) {
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	dfs(1, 0);
	int root = max_element(d+1, d+n+1) - d;
	d[root] = 0;
	dfs(root, 0);
	int len = *max_element(d+1, d+n+1);
	int now = max_element(d+1, d+n+1) - d;
	bool ok = 0;
	memset(du, 0, sizeof(du));
	d[root] = 0; 
	ok |= check(root, 0); if (ok) {cout << root << endl; return 0;}
	memset(du, 0, sizeof(du));
	d[now] = 0;
	ok |= check(now, 0); if (ok) {cout << now << endl; return 0;}
	if (len % 2 == 0) {
		memset(du, 0, sizeof(du));
		rep(i, 0, len / 2) now = pre[now];
		d[now] = 0;
		ok |= check(now, 0);
		if (ok) {cout << now << endl; return 0;}
		dfs2(now, 0); 
		//for (auto v : g[now]) de(siz[v]);
		int tmp = -1;
		for (auto v : g[now]) if (tmp == -1 || tmp != ha[v]) {
			memset(du, 0, sizeof(du));
			d[son[v]] = 0;
			ok |= check(son[v], 0);
			if (ok) {cout << son[v] << endl; return 0;}
			if (tmp == -1) tmp = ha[v];else break;
		}
	}
	cout << -1 << endl;
	return 0;
}


