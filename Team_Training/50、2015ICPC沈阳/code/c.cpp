#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl '\n'
#define pw(x) (1ll << (x))
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 101010;

int n, m, deg[N];
bool leaf[N];
pii e[N];
int par[N];
vi g[N];

void dfs(int u, int fa) {
	par[u] = fa;
	for(auto v : g[u]) if(v != fa) dfs(v, u);
}

int solve() {
	cin >> n >> m;
	rep(i, 1, n + 1) g[i].clear(), deg[i] = 0;
	rep(i, 1, n) {
		int u, v; cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	rep(i, n, m + 1) {
		int u,v; cin >> u >> v;
		++deg[u], ++deg[v];
		e[i] = mp(u, v);
	}
	dfs(1, 0);
	rep(i, 2, n + 1) leaf[i] = (sz(g[i]) == 1);
	int ans = m;
	rep(i, 1, n + 1) if(leaf[i]) {
		int u = par[i];
		ans = min(ans, deg[i]);
		if(u != 1 && sz(g[u]) == 2) ans = min(ans, min(deg[i], deg[u]));
	}
	rep(i, n, m + 1) {
		int u =e[i].fi, v = e[i].se;
		if(leaf[u] && leaf[v] && deg[u] == 1 && deg[v] == 1) ans = 0;
	}
	return ans + 2;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	rep(ca, 1, T + 1) {
		cout << "Case #" << ca << ": " << solve() << endl;
	}
	return 0;
}
