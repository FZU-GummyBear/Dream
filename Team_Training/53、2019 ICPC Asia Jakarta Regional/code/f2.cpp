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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 4040, P1 = 1e9 + 21, P2 = 1e9 + 9, P3 = 1e9 + 9, P4 = 1e9 + 7;

int n, sz[N], ha1[N], ha2[N], mx[N];
bool ban[N];
vi g[N];
bool o; vi vec;

void dfs(int u, int fa) {
	sz[u] = 1; if(o) vec.pb(u);
	for(auto v : g[u]) if(v != fa && !ban[v]) dfs(v, u), sz[u] += sz[v];
}
void dfs2(int u, int fa) {
	ha1[u] = 15777;
	ha2[u] = 23333;
	for(auto v : g[u]) if(v != fa && !ban[v]) {
		dfs2(v, u);
		ha1[u] = ha1[u] * 1ll * (ha1[v] ^ P3) % P1;
		ha2[u] = ha2[u] * 1ll * (ha2[v] ^ P4) % P2;
	}
}
ll gao(int rt) {
	dfs2(rt, 0);
	return ha1[rt] * 1ll * P2 + ha2[rt];
}
pair<ll, ll> gao(int rt, int fa) {
	o = 1; vec.clear(); dfs(rt, fa);
	int mi = N;
	for(auto u : vec) {
		mx[u] = sz[rt] - sz[u];
		for(auto v : g[u]) if(!ban[v] && sz[v] < sz[u]) mx[u] = max(mx[u], sz[v]);
		mi = min(mi, mx[u]);
	}
	ll r1 = 0, r2 = 0;
	for(auto u : vec) if(mx[u] == mi) {
		if(r1 == 0) r1 = gao(u);
		else r2 = gao(u);
	}
	if(r1 > r2) swap(r1, r2);
	return mp(r1, r2);
}
bool check(int rt) {
	o = 0; dfs(rt, 0);
	int t = -1;
	for(auto u : g[rt]) {
		if(~t) {
			if(sz[u] != t) return 0;
		} else {
			t = sz[u];
		}
	}
	ban[rt] = 1;
	pair<ll, ll> tt = mp(-1, -1);
	for(auto u : g[rt]) {
		auto k = gao(u, rt);
		if(~tt.fi) {
			if(k != tt) return 0;
		} else {
			tt = k;
		}
	}
	ban[rt] = 0;
	return 1;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n) {
		int u, v; cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	int ans = -1;
	rep(i, 1, n + 1) if(sz(g[i]) > 1 && check(i)) ans = max(ans, sz(g[i]));
	cout << ans << endl;
	return 0;
}
