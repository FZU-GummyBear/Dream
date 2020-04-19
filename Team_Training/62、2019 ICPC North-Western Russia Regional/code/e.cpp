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
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 3e5 + 7;
int n, m, u, v, ok, ans, f[N], dis[N], a[N], t2;
vi g[N];

void dfs(int u, int fa) {
	f[u] = fa;
	dis[u] = dis[fa] + 1;
	for (auto v : g[u]) if (v != fa) {
		dfs(v, u);
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, n) {
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	ok = 1;
	rep(i, 1, m+1) cin >> a[i];
	if (m == 1) {
		ans = 1;
	}else {
		dfs(a[1], 0);
		int ma = -1, t = 0;
		rep(i, 1, m+1) {
			if (dis[a[i]] > ma) ma = dis[a[i]], t = a[i];
		}
		dfs(t, 0);
		ma = -1, t2 = 0;
		rep(i, 1, m+1) {
			if (dis[a[i]] > ma) ma = dis[a[i]], t2 = a[i];
		}
		ma--;
		if (ma & 1) ok = 0;
		else {
			rep(i, 0, ma / 2) t2 = f[t2];		
		}
		dfs(t2, 0);
		rep(i, 1, m) if (dis[a[i+1]] != dis[a[i]]) ok = 0;
		ans = t2;
	}
	if (ok) cout << "YES" << endl << ans << endl;
	else cout << "NO" << endl;
	return 0;
}
