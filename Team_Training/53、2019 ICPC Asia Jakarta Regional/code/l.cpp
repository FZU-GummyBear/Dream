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

template<class T>
struct Dinic {
	const static int N = 20101, M = 1e6;
	int s, t, n, h[N], cur[N], lv[N], q[N], e, ne[M], to[M];
	T cap[M], flow;
	void liu(int u, int v, T w) {
		to[e] = v; ne[e] = h[u]; cap[e] = w; h[u] = e++;
	}
	void link(int u, int v, T w) {
		liu(u, v, w); liu(v, u, 0);
	}
	void ini(int _n = N) {
		fill(h, h + (n = _n), -1); e = 0;
	}
	bool bfs() {
		int L = 0, R = 0;
		fill(lv, lv + n, -1);
		lv[q[R++] = s] = 0;
		while(L < R && !~lv[t]) {
			int c = q[L++];
			for(int k = h[c]; ~k; k = ne[k]) {
				if(cap[k] > 0 && !~lv[to[k]]) {
					lv[q[R++] = to[k]] = lv[c] + 1;
				}
			}
		}
		return ~lv[t];
	}
	T dfs(int c, T mx) {
		if(c == t) return mx;
		T ret = 0;
		for(int &k = cur[c]; ~k; k = ne[k]) {
			if(lv[to[k]] == lv[c] + 1 && cap[k] > 0) {
				T flow = dfs(to[k], min(mx, cap[k]));
				ret += flow; cap[k] -= flow, cap[k ^ 1] += flow; mx -= flow;
				if(!mx) return ret;
			}
		}
		lv[c] = -1;
		return ret;
	}
	T run(int _s, int _t) {
		s = _s, t = _t;
		flow = 0;
		while(bfs()) {
			copy(h, h + n, cur);
			flow += dfs(s, ~0U >> 1);
		}
		return flow;
	}
};

unordered_map<int, int> M;
int cnt;

int id(int x) {
	if (M.count(x)) return M[x];
	else return M[x] = ++cnt;
}

const int N = 2e3 + 10;
int tim, dfn[N], fa[N], uu[N], vv[N], u, v, x, an[N], n, k, incir[N], S, T, t1, t2, m, p[N];
vi cir, a[N * 10], tmp1, tmp2, road[N * 10], people[N * 10];
vector<pii> g[N];


void dfs(int u, int pre) {
	dfn[u] = ++tim;
	rep(i, 0, sz(g[u])) {
		if (g[u][i].se == pre) continue;
		int v = g[u][i].fi;
		if (dfn[v] && dfn[v] <= dfn[u]) {
			int p = u; cir.pb(p);
			if (p != v) {
				do { p = fa[p]; cir.pb(p); }
					while (p != v);
			}
			continue;
		}
		if (!dfn[v]) {fa[v] = u; dfs(v, g[u][i].se); }
	}
}

Dinic<int> G;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> k;
	rep(i, 1, n+1) {
		cin >> v;
		u = i;
		g[u].pb(mp(v, i));
		g[v].pb(mp(u, i));
		cin >> m;
		rep(j, 0, m) cin >> x, a[id(x)].pb(i);
		uu[i] = i; vv[i] = v;
	}
	rep(i, 1, k+1) cin >> x, p[i] = id(x);
	dfs(1, 0);
	G.ini(n + k + cnt + 10);
	S = G.n - 5; T = S + 1, t1 = T + 1, t2 = T + 2;
	G.link(S, t1, sz(cir) - 1);
	G.link(S, t2, n - sz(cir));
	for (auto v : cir) G.link(t1, v, 1), incir[v] = 1;
	//de(sz(cir));
	
	rep(i, 1, n+1) if (!incir[i]) G.link(t2, i, 1);
	rep(i, 1, cnt+1) {
		for (auto v : a[i]) G.link(v, i + n, 1), tmp1.pb(G.e - 2);
	}
	rep(i, 1, k+1) {
		G.link(p[i] + n, i + n + cnt, 1), tmp2.pb(G.e - 2);
		G.link(i + n + cnt, T, 1);
	}
	int ans = G.run(S, T);
	if (ans != n - 1) cout << -1 << endl;
	else {
		for (auto i : tmp1) if (G.cap[i] == 0) {
			int u = G.to[i ^ 1], v = G.to[i] - n; // u road  v col
			road[v].pb(u);
		}
		for (auto i : tmp2) if (G.cap[i] == 0) {
			int u = G.to[i ^ 1] - n, v = G.to[i] - n - cnt; // u col  v people
			people[u].pb(v);
		}
		rep(i, 1, cnt+1) {
			//assert(sz(road[i]) == sz(people[i]));
			rep(j, 0, sz(road[i])) an[people[i][j]] = road[i][j];
		}
		rep(i, 1, k+1) if (an[i] == 0) cout << "0 0" << endl;
		else cout << uu[an[i]] << " " << vv[an[i]] << endl;
	}
	return 0;
}
