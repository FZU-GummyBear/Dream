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

const int N = 202020;

int n, ans[N], rt[N], sz[N];
vi g[N];

struct Seg {
	static const int N = ::N * 20;
	int ls[N], rs[N], cnt[N];
	bool tl[N], tr[N];
	int cntn;
	void up(int rt) {
		cnt[rt] = cnt[ls[rt]] + cnt[rs[rt]];
		if(tr[ls[rt]] && tl[rs[rt]]) ++cnt[rt];
		tl[rt] = tl[ls[rt]];
		tr[rt] = tr[rs[rt]];
	}
	void upd(int pre, int &now, int p, int l = 1, int r = n) {
		now = ++cntn;
		ls[now] = ls[pre];
		rs[now] = rs[pre];
		cnt[now] = cnt[pre];
		tl[now] = tl[pre];
		tr[now] = tr[pre];
		if(l == r) {
			tl[now] = tr[now] = 1;
			return ;
		}
		int mid = l + r >> 1;
		if(p <= mid) upd(ls[pre], ls[now], p, l, mid);
		else upd(rs[pre], rs[now], p, mid + 1, r);
		up(now);
	}
	int merge(int x, int y, int l = 1, int r = n) {
		if(x && y) {
			if(l == r) {
				assert(0);
			} else {
				int mid = l + r >> 1;
				ls[x] = merge(ls[x], ls[y], l, mid);
				rs[x] = merge(rs[x], rs[y], mid + 1, r);
				up(x);
				return x;
			}
		} else return x + y;
	}
}seg;

void dfs(int u, int fa) {
	seg.upd(0, rt[u], u);
	sz[u] = 1;
	for(auto v : g[u]) if(v != fa) {
		dfs(v, u);
		rt[u] = seg.merge(rt[u], rt[v]);
		sz[u] += sz[v];
	}
	ans[u] = sz[u] - seg.cnt[rt[u]];
}

void solve() {
	seg.cntn = 0;
	cin >> n;
	rep(i, 1, n + 1) g[i].clear();
	rep(i, 1, n) {
		int u, v; cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	dfs(1, 0);
	rep(i, 1, n + 1) cout << ans[i] << " \n"[i == n];
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	rep(i, 1, T + 1) {
		cout << "Case #" << i << ": ";
		solve();
	}
	return 0;
}
