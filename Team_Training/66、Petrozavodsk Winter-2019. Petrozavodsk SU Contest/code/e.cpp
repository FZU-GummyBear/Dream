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
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 202020;

int n, m, st, ed, lim;
pii e[N];
vector<pii> g[N];
int c1[N][4], c2[N][4];

void gao(int a, int b, int c[][4]) {
	rep(i, 1, n + 1) c[i][0] = 0;
	for(auto k : g[a]) if(k.se <= lim && k.fi != b) {
		for(auto u : g[k.fi]) if(u.se <= lim && u.fi != b && u.fi != a && c[u.fi][0] < 3) {
			c[u.fi][++c[u.fi][0]] = k.fi;
		}
	}
}

bool check(int mid) {
	lim = mid;
	gao(st, ed, c1);
	gao(ed, st, c2);
	rep(_, 1, mid + 1) {
		int u = e[_].fi, v = e[_].se;
		rep(i, 1, c1[u][0] + 1) if(c1[u][i] != v) {
			rep(j, 1, c2[v][0] + 1) if(c2[v][j] != u && c2[v][j] != c1[u][i]) return 1;
		}
		swap(u, v);
		rep(i, 1, c1[u][0] + 1) if(c1[u][i] != v) {
			rep(j, 1, c2[v][0] + 1) if(c2[v][j] != u && c2[v][j] != c1[u][i]) return 1;
		}
	}
	return 0;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, m + 1) {
		int u, v; cin >> u >> v;
		g[u].pb(mp(v, i));
		g[v].pb(mp(u, i));
		e[i] = mp(u, v);
	}
	cin >> st >> ed;
	int l = 5, r = m, ans = -1;
	while(l <= r) {
		int mid = l + r >> 1;
		if(check(mid)) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	cout << ans << endl;
	return 0;
}
