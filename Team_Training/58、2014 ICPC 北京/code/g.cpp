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
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 101010, M = 18, inf = 1e9;

int n, m, q, deg[N];
ll dp[N];
vector<pii> g[N];
vi ng[N];

namespace DAG {
	const int N = ::N, M = 18, lim = 1e9;
	bool sp[N]; ll dp[N]; // init
	int ne[M][N]; ll cnt[M][N]; vector<ll> pre[N];

	void build(vector<pii> g[]) {
		rep(i, 1, n + 1) {
			ne[0][i] = 0; ll md = -1; int col = 0;
			for(auto j : g[i]) if(dp[j.se] > md) md = dp[j.se], ne[0][i] = j.se, col = j.fi;
			cnt[0][i] = sp[i]; pre[i] = vector<ll>(sz(g[i]));
			rep(j, 0, sz(pre[i])) {
				pii t = g[i][j];
				pre[i][j] = (j == 0 ? sp[i] : pre[i][j - 1]) + dp[t.se];
				if(t.fi < col) cnt[0][i] = min((ll)lim, cnt[0][i] + dp[t.se]);
			}
		}
		rep(i, 1, M) rep(j, 1, n + 1) {
			int t = ne[i - 1][j];
			ne[i][j] = ne[i - 1][t];
			cnt[i][j] = min((ll)lim, cnt[i - 1][j] + cnt[i - 1][t]);
		}
	}
	int qry(int k) {
		int ans = 0, u = 1;
		while(1) {
			per(i, 0, M) if(ne[i][u] && cnt[i][u] < k && k <= cnt[i][u] + dp[ne[i][u]]) {
				ans += pw(i);
				k -= cnt[i][u];
				u = ne[i][u];
			}
			if(k == 1 && sp[u]) break;
			int p = lower_bound(all(pre[u]), k) - pre[u].begin();
			k -= (p == 0 ? sp[u] : pre[u][p - 1]);
			u = g[u][p].se;
			++ans;
		}
		return ans;
	}
}

void solve() {
	// read
	cin >> n >> m >> q;
	dp[1] = 0; rep(i, 2, n + 1) cin >> dp[i], DAG::sp[i] = dp[i];
	rep(i, 1, n + 1) g[i].clear(), ng[i].clear(), deg[i] = 0;
	rep(i, 1, m + 1) {
		int u, v, w; cin >> u >> v >> w;
		g[u].pb(mp(w, v));
		ng[v].pb(u);
		++deg[u];
	}
	rep(i, 1, n + 1) sort(all(g[i]));
	// get dp
	vi que; rep(i, 1, n + 1) if(!deg[i]) que.pb(i);
	rep(i, 0, sz(que)) {
		int u = que[i];
		for(auto v : ng[u]) {
			dp[v] = min((ll)inf, dp[v] + dp[u]);
			--deg[v];
			if(!deg[v]) que.pb(v);
		}
	}
	rep(i, 1, n + 1) DAG::dp[i] = dp[i];
	DAG::build(g);
	while(q--) {
		int k; cin >> k;
		if(k > dp[1]) {
			cout << -1 << endl;
			continue;
		}
		cout << DAG::qry(k) << endl;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	rep(i, 1, T + 1) {
		cout << "Case #" << i << ":" << endl;
		solve();
	}
	return 0;
}
