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

template<class T>
struct Dinic{
	const static int N = 10101, M = N * 10;
	int s, t, n, h[N], cur[N], lv[N], q[N], e, ne[M], to[M];
	T cap[M], flow;
	void liu(int u, int v, T w) {to[e] = v; ne[e] = h[u]; cap[e] = w; h[u] = e++;}
	void link(int u, int v, T w) {liu(u, v, w); liu(v, u, 0);}
	void ini(int _n = N) {fill(h, h+(n = _n), -1); e = 0;}
	bool bfs() {
		int L = 0, R = 0;
		fill(lv, lv + n, -1);
		lv[q[R++] = s] = 0;
		while (L < R && !~lv[t]) {
			int c = q[L++];
			for (int k = h[c]; ~k; k = ne[k]) 
				if (cap[k] > 0 && !~lv[to[k]])
					lv[q[R++] = to[k]] = lv[c] + 1;
		}
		return ~lv[t];
	}
	T dfs(int c, T mx) {
		if (c == t) return mx;
		T ret = 0;
		for (int &k = cur[c]; ~k; k = ne[k]) {
			if (lv[to[k]] == lv[c] + 1 && cap[k] > 0) {
				T flow = dfs(to[k], min(mx, cap[k]));
				ret += flow; cap[k] -= flow; cap[k ^ 1] += flow; mx -= flow;
				if (!mx) return ret;
			}
		}
		lv[c] = -1;
		return ret;
	}
	T run(int _s, int _t) {
		s = _s; t = _t;
		flow = 0;
		while (bfs()) {
			copy(h, h + n, cur);
			flow += dfs(s, ~0U>>1);
		}
		return flow;
	}
};
Dinic<int> G;
const int N = 1e4 + 7;
int p[N][2], lim[N], val[N], w[N][2], an[N], col[N], s, t, n, m, ans, x, T;
vi g[N];
void dfs(int u, int o) {
	col[u] = o;
	for (auto v : g[u]) if (col[v] == -1) dfs(v, o ^ 1);
}


int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m;
		int s1 = pw(n), s2 = pw(m);


		rep(i, 0, s1) cin >> lim[i];
		rep(i, 0, s1) cin >> val[i];
		rep(i, 0, s1) w[i][0] = w[i][1] = -pw(30), col[i] = -1, g[i].clear(), p[i][0] = p[i][1] = 0;
		rep(i, 0, s1) rep(j, 0, s2) {
			cin >> x;
			if (j < lim[i]) {
				if (w[i][0] < x) w[i][0] = x, p[i][0] = j;
			}else {	
				if (w[i][1] < x) w[i][1] = x, p[i][1] = j;
			}
		}

		G.ini(s1+10); s = G.n - 5; t = s + 1;
		rep(i, 0, s1) {
			if (w[i][0] <= w[i][1]) p[i][0] = p[i][1]; 
			w[i][0] = max(w[i][0], w[i][1]), ans += w[i][0];
		}
		rep(i, 0, s1) rep(j, i+1, s1) if (__builtin_popcount(i ^ j) == 1){
			ans += val[i] ^ val[j];
			g[i].pb(j);
			g[j].pb(i);
			//G.link(i, j, val[i] ^ val[j]);
		}
		rep(i, 0, s1) if (col[i] == -1) dfs(i, 0);
		rep(i, 0, s1) if (col[i] == 0) for (auto j : g[i]) G.link(i, j, val[i] ^ val[j]);
		rep(i, 0, s1) if (col[i] == 0) G.link(s, i, w[i][0] - w[i][1]);else G.link(i, t, w[i][0] - w[i][1]);
		G.run(s, t);
		rep(i, 0, s1) if (G.lv[i] != -1) {
			an[i] = col[i];
		}else {
			an[i] = col[i] ^ 1;
		}
		rep(i, 0, s1) cout << p[i][an[i]] << " \n"[i == s1 - 1];
	}
	return 0;
}
