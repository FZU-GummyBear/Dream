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

const int N = 5e5 + 7;

struct Node {
	int i, l, r;
	bool operator < (const Node &c) const {
		if(l != c.l) return l < c.l;
		return r < c.r;
	}
};

int n, id[N], tim; 
Node a[N];
vi g[N];

struct Seg {
	static const int N = ::N * 20;
	int ls[N], rs[N], cnt[N], rt[::N], cntn, tg[N];
	void upd(int &now, int pre, int p, int c, int l = 1, int r = 2 * n) {
		now = ++cntn;
		assert(now < N);
		ls[now] = ls[pre];
		rs[now] = rs[pre];
		cnt[now] = cnt[pre] + 1;
		if(l == r) return tg[now] = c, void();
		int mid = l + r >> 1;
		if(p <= mid) upd(ls[now], ls[pre], p, c, l, mid);
		else upd(rs[now], rs[pre], p, c, mid + 1, r);
	}
	int qry(int L, int R, int rt, int l = 1, int r = 2 * n) {
		if(!rt) return 0;
		if(L <= l && r <= R) return cnt[rt];
		int mid = l + r >> 1, ans = 0;
		if(L <= mid) ans += qry(L, R, ls[rt], l, mid);
		if(R > mid) ans += qry(L, R, rs[rt], mid + 1, r);
		return ans;
	}
	void gao(int L, int R, int rt, int l = 1, int r = 2 * n) {
		if(!rt) return ;
		if(l == r) {
			return g[tim].pb(tg[rt]), void();
		}
		int mid = l + r >> 1;
		if(L <= mid && ls[rt]) gao(L, R, ls[rt], l, mid);
		if(R > mid && rs[rt]) gao(L, R, rs[rt], mid + 1, r);
	}
}t1, t2;

bool ok = 1;
bool vis[N];

void dfs(int u, int fa) {
	if(!ok) return ;
	vis[u] = 1;
	tim = u;
	t1.gao(a[u].l, a[u].r, t1.rt[u - 1]);
	t2.gao(a[u].l, a[u].r, t2.rt[id[u]]);
	sort(all(g[u]));
	g[u].erase(unique(all(g[u])), g[u].end());
	for(auto v : g[u]) if(v != fa) {
		dd(u), de(v);
		if(vis[v]) {
			ok = 0;
			return ;
		} else {
			dfs(v, u);
			if(!ok) return ;
		}
	}
}

bool cmp(Node a, Node b) { return a.r > b.r; }
bool solve() {
	int cnt = 0;
	rep(i, 1, n + 1) {
		cnt += t1.qry(a[i].l, a[i].r, t1.rt[i - 1]);
		if(cnt > n - 1) return 0;
		t1.upd(t1.rt[i], t1.rt[i - 1], a[i].r, a[i].i);
	}
	if(cnt != n - 1) return 0;
	sort(a + 1, a + 1 + n, cmp);
	rep(i, 1, n + 1) {
		id[a[i].i] = i - 1;
		t2.upd(t2.rt[i], t2.rt[i - 1], a[i].l, a[i].i);
	}
	sort(a + 1, a + 1 + n);
	dfs(1, 0);
	rep(i, 1, n + 1) if(!vis[i]) return 0;
	return ok;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	db x = sizeof(t1) * 2;
	de(x / 1024 / 1024);
	cin >> n;
	rep(i, 1, n + 1) cin >> a[i].l >> a[i].r;
	sort(a + 1, a + 1 + n); 
	rep(i, 1, n + 1) a[i].i = i;
	cout << (solve() ? "YES" : "NO") << endl;
	return 0;
}
