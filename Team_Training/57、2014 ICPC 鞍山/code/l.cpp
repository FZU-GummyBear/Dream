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
typedef pair<ll, ll> pii;
typedef vector<int> vi;

const int N = 101010, M = 26;

int n, ne[N][M], fail[N], dfn, st[N], ed[N], dep[N], pre[22][N];
vi g[N];

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	ll a[N], b[N], ma[N];
	void build(int l = 1, int r = n, int rt = 1) {
		a[rt] = b[rt] = ma[rt] = 0;
		if(l == r) return ;
		int mid = l + r >> 1;
		build(l, mid, ls);
		build(mid + 1, r, rs);
	}
	pii qry(int p, int l = 1, int r = n, int rt = 1) {
		if(l == r) return mp(a[rt], b[rt]);
		int mid = l + r >> 1;
		if(p <= mid) {
			auto t = qry(p, l, mid, ls);
			return mp(t.fi + a[rt], t.se + b[rt]);
		}
		auto t = qry(p, mid + 1, r, rs);
		return mp(t.fi + a[rt], t.se + b[rt]);
	}
	ll qma(int p, int l = 1, int r = n, int rt = 1) {
		if(l == r) return ma[rt];
		int mid = l + r >> 1;
		if(p <= mid) return max(ma[rt], qma(p, l, mid, ls));
		else return max(ma[rt], qma(p, mid + 1, r, rs));
	}
	void upd(int L, int R, ll c1, ll c2, ll c3, int l = 1, int r = n, int rt = 1) {
		if(L <= l && r <= R) {
			a[rt] += c1;
			b[rt] += c2;
			ma[rt] = max(ma[rt], c3);
			return ;
		}
		if(l == r) return ;
		int mid = l + r >> 1;
		if(L <= mid) upd(L, R, c1, c2, c3, l, mid, ls);
		if(R > mid) upd(L, R, c1, c2, c3, mid + 1, r, rs);
	}
}seg;

void dfs(int u) {
	st[u] = ++dfn;
	for(auto v : g[u]) {
		pre[0][v] = u;
		rep(i, 1, 22) pre[i][v] = pre[i - 1][pre[i - 1][v]];
		dep[v] = dep[u] + 1, dfs(v);
	}
	ed[u] = dfn;
}
int lca(int x, int y) {
	if(dep[x] > dep[y]) swap(x, y);
	per(i, 0, 22) if(dep[x] <= dep[pre[i][y]]) y = pre[i][y];
	per(i, 0, 22) if(pre[i][x] != pre[i][y]) x = pre[i][x], y = pre[i][y];
	if(x == y) return x;
	return pre[0][x];
}
bool cmp(int i, int j) {
	return st[i] < st[j];
}
void solve() {
	memset(ne, 0, sizeof(ne));
	memset(fail, 0, sizeof(fail));
	cin >> n;
	rep(i, 0, n + 1) g[i].clear();
	rep(v, 2, n + 1) {
		int u; string s;
		cin >> u >> s;
		ne[u - 1][s[0] - 'a'] = v - 1;
	}
	fail[0] = N - 1;
	vi v; v.pb(0);
	rep(i, 0, sz(v)) {
		int c = v[i];
		rep(i, 0, M) ne[c][i] ? 
			v.pb(ne[c][i]), fail[ne[c][i]] = ne[fail[c]][i] : 
			ne[c][i] = ne[fail[c]][i];
	}
	rep(i, 1, n) g[fail[i]].pb(i);
	dfn = 0;
	dfs(0);
	seg.build();
	int m; cin >> m;
	rep(tim, 1, m + 1) {
		int o, k; 
		cin >> o >> k; 
		vi vec(k);
		rep(i, 0, k) cin >> vec[i], vec[i]--;
		sort(all(vec), cmp);
		if(o == 1) {
			for(auto u : vec) {
				if(seg.qma(st[u]) == tim) continue;
				seg.upd(st[u], ed[u], 1, dep[u] - 1, tim);
			}
		} else {
			ll ans = 0;
			rep(i, 0, k) {
				int u = vec[i];
				auto t = seg.qry(st[u]);
				ans += t.fi * dep[u] - t.se;
				if(i == 0) continue;
				u = lca(u, vec[i - 1]);
				t = seg.qry(st[u]);
				ans -= t.fi * dep[u] - t.se;
			}
			cout << ans << endl;
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
