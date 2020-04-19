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
const int inf = 1e9 + 7;
int u, v, w, n, m, x, T, ss, tt;

template<class T>
struct Dinic {
	const static int N = 10101, M = N * 10;
	int s, t, n, h[N], cur[N], lv[N], q[N], e, ne[M], to[M];
	T cap[M], flow;
	void liu(int u, int v, T w) {
		to[e] = v; ne[e] = h[u]; cap[e] = w; h[u] = e++;
	}
	void link(int u, int v, T w) {
		liu(u, v, w);
		liu(v, u, 0);
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
		s = _s; t = _t;
		flow = 0;
		while(bfs()) {
			copy(h, h + n, cur);
			flow += dfs(s, ~0U >> 1);
		}
		return flow;
	}
};
Dinic<int> G;
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m >> x;
		G.ini(n * 2 + 10);
		ss = G.n - 5, tt = ss + 1;
		rep(i, 1, m+1) {
			cin >> u >> v >> w;
			G.link(u + n, v, w);
		}
		rep(i, 1, n+1) cin >> w, G.link(ss, i, w);
		rep(i, 1, n+1) cin >> w, G.link(i, i + n, w);
		G.link(x + n, tt, inf);
		cout << G.run(ss, tt) << endl;
	
	}
	return 0;
}
