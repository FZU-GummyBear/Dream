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
 
typedef uniform_int_distribution<ll> RR;
mt19937 gen(998244353);
ll rd(ll l, ll r) { RR dis(l, r); return dis(gen); } 
 
const int P = 1e9 + 7;
const int N = 1e5 + 10;
int T, n, m, u, v, rnd[N], can[N], vis[N], w;
vector<pii> g[N];
vi revg[N];
int kpow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = 1ll * res  * a % P;
		a = 1ll * a * a % P;
		b >>= 1;
	}
	return res;
}
 
void dfs(int u) {
	can[u] = 1;
	for (auto v : revg[u]) if (can[v] == -1) dfs(v); 
}
 
unordered_map<int, int> M;
 
int get(vi &tmp) {
	int res = 0;
	for (auto v : tmp) res ^= rnd[v];
	return res;
}
 
int main() {
	freopen("a.in", "r", stdin); 
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	srand(time(0));
	rep(i, 0, 100000) rnd[i] = rd(1, 1e9);
	cin >> T;
	rep(cas, 0, T) {
		M.clear();
		cin >> n >> m;
		rep(i, 0, n) g[i].clear(), revg[i].clear();
		rep(i, 0, m) {
			cin >> u >> v >> w;
			g[u].pb(mp(v, w));
			revg[v].pb(u);
		}
		vi ans;
		memset(can, -1, sizeof(can));
		dfs(1);
		vi t1, t2;
		t1.pb(0);
		bool ok = 0;
		vi cir;
		while (1) {
			for (auto v : t1) vis[v] = 0;
			for (auto v : t1) if (v == 1) {
				ok = 1; 
				break;
			}
			if (ok) break;
			int ha = get(t1);
			if (M.count(ha)) {
				int d = M[ha];
				rep(i, d, sz(ans)) cir.pb(ans[i]);
				break;
			}
			M[ha] = sz(ans);
			t2.clear();
			int x = pw(30);
			for (auto v : t1) for (auto u : g[v]) if (can[u.fi] == 1) x = min(x, u.se);
			ans.pb(x);
			for (auto v : t1) for (auto u : g[v]) if (can[u.fi] == 1 && u.se == x) {
				if (!vis[u.fi]) vis[u.fi] = 1, t2.pb(u.fi);
			}
			t1 = t2;
		}
		ll an = 0;
		int inv10 = kpow(10, P - 2);
		per(i, 0, sz(ans)) an = an * inv10 + ans[i], an %= P;
		an = an * inv10; an %= P;
		ll tmp = 1;
		rep(i, 0, sz(cir)) tmp = tmp * 10 % P;
		tmp--;
		tmp = kpow(tmp, P - 2);
		ll fz = 0;
		rep(i, 0, sz(cir)) fz = fz * 10 + cir[i], fz %= P;
		fz = fz * tmp % P;
		rep(i, 0, sz(ans)) fz = fz * inv10, fz %= P;
		an += fz;
		an %= P;
		if (an < 0) an += P;
		cout << "Case #" << cas + 1 << ": " << an << endl;
	}
	return 0;
}
