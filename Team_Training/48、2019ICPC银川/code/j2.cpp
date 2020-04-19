#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define pw(x) (1ll << (x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 201010;

int n, m, k, par[N], vis[N];
map<pii, int> W;
map<pii, int> ban;
vi G[N], vec[N], g[N];
ll val[N], f[N], h[N];
pii e[N];

void add(int u, int v) {
	g[u].pb(v);
	g[v].pb(u);
}

void df(int u, int fa) {
	dd(u), de(fa);
	vis[u] = 1;
	par[u] = fa;
	for(auto v : G[u]) if(v != fa) {
		if(vis[v]) {
			k++;
			int pre = v;
			int t = u;
			while(1) {
				val[k] += W[mp(pre, t)];
				ban[mp(pre, t)] = 1;
				add(k, t);
				if(t == v) break;
				pre = t;
				t = par[t];
			}
		} else {
			df(v, u);
		}
	}
}


void dfs(int u, int fa) {
	f[u] = h[u] = 0;
	ll mi = 0;
	for(auto v : g[u]) if(v != fa) {
		if(v <= n) {
			dfs(v, u);
			int w = W[mp(u, v)];
			f[u] += 2ll * w + f[v];
			mi = min(mi, w + h[v] - (2ll * w + f[v]));
		} else {
			for(auto t : g[v]) if(t != u) {
				dfs(t, v);
				f[u] += f[t];
			}
			f[u] += val[v];
		}
	}
	h[u] = f[u] + mi;
}

int main() {
//	std::ios::sync_with_stdio(0);
//	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, m + 1) {
		int u, v, w; cin >> u >> v >> w;
		e[i] = mp(u, v);
		G[u].pb(v);
		G[v].pb(u);
		W[mp(u, v)] = w;
		W[mp(v, u)] = w;
	}
	k = n;
	de(1);
	df(1, 0);
	rep(i, 1, m + 1) {
		int u = e[i].fi, v = e[i].se;
		if(ban[mp(u, v)] == 0) add(u, v);
	}
	dfs(1, 0);
	cout << h[1] << endl;
	return 0;
}
