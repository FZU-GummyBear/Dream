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

const int N = 1e5 + 7;
int n, m, u, v, f[N], f1[N], len, vis[N];
vi g[N];
vector<pii> tmp, an;
pii ans[N];
int get(int x) {
	return x == f[x] ? x : f[x] = get(f[x]);
}

int dfs(int u) {
	vis[u] = 1;
	int ma = 0;
	for (auto v : g[u]) if (!vis[v]) {
		ma = max(ma, dfs(v) + 1);
	} 
	return ma;
}

void dfs2(int u, int fa) {
	f1[u] = 0;
	for (auto v : g[u]) if (v != fa) {
		dfs2(v, u);
		len = max(len, f1[u] + f1[v] + 1);
		f1[u] = max(f1[u], f1[v] + 1);
	}
}

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m;
	rep(i, 1, n+1) f[i] = i;
	rep(i, 1, m+1) {
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
		u = get(u), v = get(v);
		f[u] = v;
	} 
	rep(i, 1, n+1) ans[i] = mp(pw(30), 0);
	rep(i, 1, n+1) {
		memset(vis, 0, sizeof(vis));
		int w = dfs(i);
		ans[get(i)] = min(ans[get(i)], mp(w, i)); 
	}
	rep(i, 1, n+1) if (get(i) == i) tmp.pb(ans[i]);
	sort(all(tmp));
	int x = tmp.back().se;
	rep(i, 0, sz(tmp)-1) {
		an.pb(mp(tmp[i].se, x));
		g[x].pb(tmp[i].se);
		g[tmp[i].se].pb(x);
	}
	dfs2(1, 0);
	cout << len << endl;
	for (auto u : an) cout << u.fi << " " << u.se << endl;
 	return 0;
}


