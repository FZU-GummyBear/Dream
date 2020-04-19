#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll << (x))
#define endl '\n'
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 101010;

int n, q;
ll a[N];
ull ans[N << 1];
string str;
vi Q[N << 1];
vi g[N << 1];
int sz[N << 1], rig[N << 1];

struct Node {
	static const int M = 64;
	ll a[M], v[M];
	ull sum;
	void init() {
		fill_n(a, M, 0);
		sum = 0;
	}
	void ins(ll x) {
		ll val = x;
		per(i, 0, M) if(x >> i & 1) {
			if(a[i]) {
				if(v[i] < val) {
					sum += val - v[i];
					swap(a[i], x);
					swap(v[i], val);
				}
				x ^= a[i];
			} else {
				a[i] = x, v[i] = val;
				sum += val;
				break;
			}
		}
	}
}nd[N << 1];

void dfs(int u, int tp) {
	nd[tp].ins(a[rig[u]]);
	for(auto v : g[u]) dfs(v, tp);
}

void dfs(int u) {
	int s = -1;
	for(auto v : g[u]) {
		dfs(v);
		if(s == -1 || sz[v] > sz[s]) s = v;
	}
	if(u == 1) {
		assert(sz(Q[u]) == 0);
		return ;
	}
	if(~s) {
		nd[u] = nd[s];
		nd[u].ins(a[rig[u]]);
		for(auto v : g[u]) if(v != s) dfs(v, u);
	} else {
		nd[u].ins(a[rig[u]]);
	}
	for(auto k : Q[u]) ans[k] = nd[u].sum;
}

struct SAM {
	static const int N = ::N << 1, M = 26, K = 20;
	int par[N], l[N], ne[N][M], rt, last, L;
	int cnt[N], cur[N], pre[K][N], go[N];
	void add(int c) {
		int p = last, np = ++L;
		fill(ne[np], ne[np] + M, 0);
		l[np] = l[p] + 1;
		last = np;
		while(p && !ne[p][c]) ne[p][c] = np, p = par[p];
		if(!p) par[np] = rt;
		else {
			int q = ne[p][c];
			if(l[q] == l[p] + 1) par[np] = q;
			else {
				int nq = ++L;
				l[nq] = l[p] + 1;
				copy(ne[q], ne[q] + M, ne[nq]);
				par[nq] = par[q];
				par[q] = par[np] = nq;
				while(p && ne[p][c] == q) ne[p][c] = nq, p = par[p];
			}
		}
	}
	void ini() {
		rt = last = L = 1;
		fill(ne[rt], ne[rt] + M, 0);
		l[0] = -1;
	}
	void build() {
		rep(i, 0, L + 1) cnt[i] = rig[i] = 0, Q[i].clear(), sz[i] = 1, g[i].clear(), nd[i].init();
		rep(i, 1, L + 1) ++cnt[l[i]];
		rep(i, 1, L + 1) cnt[i] += cnt[i - 1];
		rep(i, 1, L + 1) cur[cnt[l[i]]--] = i;
		int p = rt;
		rep(i, 1, n + 1) {
			int c = str[i - 1] - 'a';
			go[i] = p = ne[p][c];
			++rig[p];
		}
		per(i, 1, L + 1) {
			int u = cur[i];
			rig[par[u]] += rig[u];
			sz[par[u]] += sz[u];
		}
		rep(i, 1, L + 1) pre[0][i] = par[i], g[par[i]].pb(i);
		rep(i, 1, K) rep(j, 1, L + 1) pre[i][j] = pre[i - 1][pre[i - 1][j]];
		cin >> q;
		rep(i, 1, q + 1) {
			int st, r; cin >> st >> r;
			int u = go[r], len = r - st + 1;
			per(t, 0, K) if(l[pre[t][u]] >= len) u = pre[t][u];
			Q[u].pb(i);
		}
	}
}sam;

void solve() {
	cin >> n >> str;
	rep(i, 1, n + 1) cin >> a[i];
	sam.ini();
	rep(i, 0, n) sam.add(str[i] - 'a');
	sam.build();
	dfs(sam.rt);
	rep(i, 1, q + 1) cout << ans[i] << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
