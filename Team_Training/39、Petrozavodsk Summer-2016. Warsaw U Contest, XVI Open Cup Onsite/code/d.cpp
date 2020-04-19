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
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 2e5 + 76;
vi g[N], tmp, ans;
int du[N], u, v, n, m, d, vis[N];
queue<int> q;

void dfs(int u) {
	vis[u] = 1;
	tmp.pb(u);
	for (auto v : g[u]) if (!vis[v]) dfs(v);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m >> d;
	rep(i, 1, m+1) {
		cin >> u >> v;
		du[u]++;
		du[v]++;
		g[u].pb(v);
		g[v].pb(u);
	}
	rep(i, 1, n+1) if (du[i] < d) q.push(i), vis[i] = 1;
	while (!q.empty()) {
		u = q.front(); q.pop();
		for (auto v : g[u]) {
			du[v]--;
			if (du[v] < d && !vis[v]) vis[v] = 1, q.push(v);
		}
	}
	rep(i, 1, n+1) if (!vis[i]) {
		tmp.clear();
		dfs(i);
		if (sz(tmp) > sz(ans))  ans = tmp;
	}
	if (sz(ans) == 0) cout << "NIE" << endl;
	else {
		sort(all(ans));
		cout << sz(ans) << endl;
		rep(i, 0, sz(ans)) cout << ans[i] << " \n"[i == sz(ans) - 1];
	}
	return 0;
}
