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

int n, m, k;
map<pii, int> W;
vi G[N], vec[N], g[N];
ll val[N], f[N], h[N];

void add(int u, int v) {
//	dd(u), de(v);
	g[u].pb(v);
	g[v].pb(u);
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
	//dd(u), dd(f[u]), de(h[u]);
}

namespace DCC {
	const int N = 202020;
	vi key, dcc[N];
	int dfn[N], low[N], st[N], _st, _;
	void dfs(int c, int dep, const vi g[]) {
		int cc = 0, out = 1 < dep; st[_st++] = c;
		dfn[c] = low[c] = dep;
		for(auto t : g[c]) {
			if(!dfn[t]) {
				dfs(t, dep + 1, g);
				low[c] = min(low[c], low[t]);
				if(low[t] >= dfn[c]) {
					if(++out == 2) key.pb(c);
					vec[_].pb(c); 
					while(st[--_st] != t) dcc[st[_st]].pb(_), vec[_].pb(st[_st]);
					vec[_].pb(t);
					dcc[c].pb(_); dcc[t].pb(_++);
				}
			} else if(dfn[t] != dfn[c] - 1 || cc++) {
				low[c] = min(low[c], dfn[t]);
			}
		}
	}
	int solve(int n, const vi g[]) {
		rep(i, 0, n) if(!dfn[i]) dfs(i, 1, g);
		rep(i, 0, n) if(sz(dcc[i]) == 0) dcc[i].pb(_++);
		return _;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, m + 1) {
		int u, v, w; cin >> u >> v >> w;
		G[u - 1].pb(v - 1);
		G[v - 1].pb(u - 1);
		W[mp(u, v)] = w;
		W[mp(v, u)] = w;
	}
	k = n;
	int _ = DCC::solve(n, G);
	rep(i, 0, _) {
		if(sz(vec[i]) == 2) {
			add(vec[i][0] + 1, vec[i][1] + 1);
		} else {
			++k;
			int pre = vec[i].back() + 1;
			for(auto t : vec[i]) {
				add(k, t + 1);
				val[k] += W[mp(pre, t + 1)];
				pre = t + 1;
			}
		}
	}
	//rep(i, 1, k+1) dd(i), de(val[i]);
	dfs(1, 0);
	cout << h[1] << endl;
	return 0;
}
