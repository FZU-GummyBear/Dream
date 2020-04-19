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
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 606060, P = 998244353;

int n, m;
vi g[N];
int pw[N], sb[N];

int cnt[N];
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
				while(st[--_st] != t) dcc[st[_st]].pb(_);
				dcc[c].pb(_); dcc[t].pb(_++);
			} 
		}
		else if(dfn[t] != dfn[c] - 1 || cc++) {
			low[c] = min(low[c], dfn[t]);
		}
	}
}
int solve(int n, const vi g[]) {
	rep(i, 0, n) if(!dfn[i]) dfs(i, 1, g);
	rep(i, 0, n) if(sz(dcc[i]) == 0) dcc[i].pb(_++);
	return _;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	pw[0] = 1;
	sb[0] = 0;
	rep(i, 1, n + 1) {
		pw[i] = pw[i - 1] * 2ll % P;
		sb[i] = pw[i] - 1;
		if(sb[i] < 0) sb[i] += P;
	}
	rep(i, 1, m + 1) {
		int u, v; cin >> u >> v; --u, --v;
		g[u].pb(v), g[v].pb(u);
	}
	int _ = solve(n, g);
	rep(i, 0, n) for(auto j : dcc[i]) ++cnt[j];
	int ans = 1;
	int c = 0;
	rep(j, 0, _) if(cnt[j] > 1) {
		if(cnt[j] == 2) {
			++c;
		} else {
			ans = ans * 1ll * sb[cnt[j]] % P;
		}
	}
	ans = ans * 1ll * pw[c] % P;
	cout << ans << endl;
	return 0;
}
