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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 505050;

int n, cntn;
vi g[N];
pii ans[N];

void dfs(int u, int fa) {
	per(i, 0, sz(g[u])) if(g[u][i] != fa) dfs(g[u][i], u);
	ans[u].fi = ++cntn;
	for(auto v : g[u]) if(v != fa) ans[v].se = ++cntn;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n) {
		int u, v; cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	dfs(1, 0);
	ans[1].se = ++cntn;
	rep(i, 1, n + 1) cout << ans[i].fi << " " << ans[i].se << endl;
	return 0;
}
