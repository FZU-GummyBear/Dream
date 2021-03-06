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

const int N = 1e6 + 7;

int n, f[N];
bool tt[N];
vi g[N];

void dfs(int u) {
	tt[u] = 0;
	for(auto v : g[u]) {
		dfs(v);
		tt[u] |= tt[v];
	}
	if(sz(g[u]) > 1) tt[u] = 1;
	if(sz(g[u]) == 0) {
		f[u] = 2;
	} else if(tt[u] == 0) {
		f[u] = f[g[u][0]] ^ 1;
	} else {
		int cnt[4] = {0};
		for(auto v : g[u]) ++cnt[f[v]];
		if(cnt[3] == 0) {
			f[u] = 2;
		} else if(cnt[2] == 0) {
			f[u] = 3;
		} else {
			f[u] = 2;
		}
	}
}

void solve() {
	cin >> n;
	rep(v, 2, n + 1) {
		int u; cin >> u;
		g[u].pb(v);
	}
	dfs(1);
//	rep(i, 1, n + 1) dd(i), de(f[i]);
	cout << (f[1] == 2 ? "Takeru" : "Meiya") << endl;
	rep(i, 1, n + 1) g[i].clear();
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
