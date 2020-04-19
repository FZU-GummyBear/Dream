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

const int N = 101010;

map<pii, int> ss, cnt;
vi g[N];
int tim;
vi ans;

struct Node {
	int a[3];
	void read() {
		rep(i, 0, 3) cin >> a[i];
		sort(a, a + 3);
		rep(i, 0, 3) rep(j, i + 1, 3) {
			pii t = mp(a[i], a[j]);
			++cnt[t];
			if(ss.count(t)) {
				int u = ss[t], v = tim;
				g[u].pb(v), g[v].pb(u);
			} else {
				ss[t] = tim;
			}
		}
	}
};

int n;
Node nd[N];
bool vis[N];
vi res;

void dfs(int u, int fa) {
	vis[u] = 1;
	ans.pb(u);
	for(auto v : g[u]) if(v != fa && !vis[v]) {
		dfs(v, u);
	}
}
void dfs2(int u, int fa) {
	vis[u] = 1;
	res.pb(u);
	for(auto v : g[u]) if(v != fa && !vis[v]) dfs2(v, u);
}
void solve() {
	ss.clear(); cnt.clear();
	cin >> n;
	rep(i, 0, n + 1) g[i].clear();
	ans.clear();
	res.clear();
	memset(vis, 0,sizeof(vis));
	rep(i, 1, n - 2 + 1) tim = i, nd[i].read();
	dfs(1, 0);
	rep(i, 1, n + 1) g[i].clear();
	for(auto u : cnt) if(u.se == 1) {
		int x = u.fi.fi, y = u.fi.se;
		g[x].pb(y); g[y].pb(x);
	}
	memset(vis, 0, sizeof(vis));
	dfs2(1, 0);
	rep(i, 0, n) cout << res[i] << " \n"[i == n - 1];
	reverse(all(ans));
	rep(i, 0, n - 2) cout << ans[i] << " \n"[i == n - 3];
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
