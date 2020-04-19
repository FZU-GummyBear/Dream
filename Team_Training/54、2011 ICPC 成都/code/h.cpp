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
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 101010;

int n;
vector<pii> g[N];
ll ans;
int sz[N];

void dfs(int u, int fa) {
	sz[u] = 1;
	for(auto v : g[u]) if(v.fi != fa) dfs(v.fi, u), sz[u] += sz[v.fi];
}
void dfs2(int u, int fa) {
	for(auto v : g[u]) if(v.fi != fa) {
		dfs2(v.fi, u);
		ans += v.se * 2ll * min(sz[v.fi], n - sz[v.fi]);
	}
}

ll solve() {
	ans = 0;
	cin >> n;
	rep(i, 1, n + 1) g[i].clear();
	rep(i, 1, n) {
		int u, v, w; cin >> u >> v >> w;
		g[u].pb(mp(v, w));
		g[v].pb(mp(u, w));
	}
	dfs(1, 0);
	dfs2(1, 0);
	return ans;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	rep(i, 1, T + 1) cout << "Case #" << i << ": " << solve() << endl;
	return 0;
}
