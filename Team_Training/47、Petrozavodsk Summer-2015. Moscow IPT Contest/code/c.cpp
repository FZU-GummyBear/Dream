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
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 4e5 + 7, inf = 2e9 + 10;
int x[N], l[N], r[N], q[N], n, m;
vi V;
struct SegGraph{
#define ls (rt << 1)
#define rs (ls | 1)
	static const int N = :: N << 2, M = N << 1;
	int id[N][2], p[::N], tim, dis[M];
	bool vis[M];
	vector<pair<int, bool> > g[M];
	priority_queue<pii> q;
	void init() {rep(i, 0, tim) g[i].clear(); tim = 0;}
	void liu(int u, int v, int w) {g[u].pb(mp(v, w));}
	void build(int l, int r, int rt) {
		int *t = id[rt], *fa = id[rt / 2], mid = l + r >> 1;
		t[0] = ++tim, t[1] = ++tim, liu(t[0], t[1], 0);
		if (rt / 2) liu(fa[0], t[0], 0), liu(t[1], fa[1], 0);
		if (l == r) {p[l] = t[0]; return;}
		build(l, mid, ls);
		build(mid+1, r, rs);
	}
	void link(int l, int r, int rt, int L, int R, int w, int o) {
		int *t = id[rt], mid = l + r >> 1;
		if (L <= l && R >= r) {
			if (o) liu(t[o], tim, w);
			else liu(tim, t[o], w);
			return;
		}
		if (L <= mid) link(l, mid, ls, L, R, w, o);
		if (R > mid) link(mid+1, r, rs, L, R, w, o);
	}
	void link(int l1, int r1, int l2, int r2, int w, int n) {
		++tim;
		link(1, n, 1, l2, r2, 0, 0);
		link(1, n, 1, l1, r1, w, 1);
	}
	void run(int s) {
		assert(tim < M);
		rep(i, 0, tim+1) dis[i] = inf; 
		dis[s] = 0; q.push(mp(0, s));
		while (!q.empty()) {
			pii u = q.top(); q.pop(); 
			if (vis[u.se]) continue;
			vis[u.se] = 1;
			for (auto v : g[u.se]) if (dis[v.fi] > dis[u.se] + v.se) {
				dis[v.fi] = dis[u.se] + v.se;
				q.push(mp(-dis[v.fi], v.fi));
			}
		}
	}
} G;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int k = 8;
	de(pow(1.0 * (pw(k) - k) / pw(k), 100));
	de(10000 * (1 - pow(0.5, 1. /100)));
	//de(sizeof(G) / 1024. / 1024.);
	cin >> n;
	rep(i, 1, n+1) {
		cin >> x[i] >> l[i] >> r[i];
		V.pb(x[i]);
	}
	cin >> m;
	rep(i, 1, m+1) cin >> q[i], V.pb(q[i]);
	V.pb(-inf);
	sort(all(V));
	V.erase(unique(all(V)), V.end());
	G.init();
	G.build(1, sz(V) - 1, 1);
	rep(i, 1, n+1) {
		int l1, r1, l2, r2;
		l1 = lower_bound(all(V), x[i] - r[i]) - V.begin();
		r1 = upper_bound(all(V), x[i] - l[i]) - V.begin() - 1;

		l2 = lower_bound(all(V), x[i] + l[i]) - V.begin();
		r2 = upper_bound(all(V), x[i] + r[i]) - V.begin() - 1;

		x[i] = lower_bound(all(V), x[i]) - V.begin();
		if (l1 <= r1) G.link(x[i], x[i], l1, r1, 1, sz(V) - 1);	
		if (l2 <= r2) G.link(x[i], x[i], l2, r2, 1, sz(V) - 1);	
	}
	G.run(G.p[x[1]]);
	
	rep(i, 1, m+1) {
		int p = lower_bound(all(V), q[i]) - V.begin();
		p = G.p[p];
		if (G.dis[p] != inf) cout << G.dis[p];
		else cout << -1;
		cout << " \n"[i == m];
	}
	return 0;
}
