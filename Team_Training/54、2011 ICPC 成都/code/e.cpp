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
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 1e4 + 10;

struct TwoSat {
	static const int N = ::N << 1;
	int dfn[N], low[N], id[N], st[N], _st, _, cc;
	vi g[N];
	int mark[N], n;
	void init(int _n) {
		per(i, 0, (n = _n << 1)) g[i].clear();
	}
	void addedge(int a, int va, int b, int vb) {
		a = a << 1 | va; b = b << 1 | vb;
		g[a].pb(b); g[b ^ 1].pb(a ^ 1);
	}
	void add_set(int a, int va) {
		a = a << 1 | va; g[a ^ 1].pb(a);
	}
	void add_then(int a, int va, int b, int vb) {
		addedge(a, va, b, vb ^ 1);
	}
	void add_or(int a, int va, int b, int vb) {
		addedge(a, va ^ 1, b, vb);
	}
	void add_xor(int a, int va, int b, int vb) {
		addedge(a, va, b, vb);
		addedge(b, vb, a, va);
	}
	void dfs(int c, vi g[]) {
		dfn[c] = low[c] = ++cc;
		st[_st++] = c;
		for(auto t : g[c]) {
			if(!dfn[t]) dfs(t, g), low[c] = min(low[c], low[t]);			
			else if(!id[t]) low[c] = min(low[c], dfn[t]);
		}
		if(low[c] == dfn[c]) {
			++_;
			do { id[st[--_st]] = _; } while(st[_st] != c);
		}
	}
	void find() {
		fill_n(dfn, n, cc = 0);
		fill_n(low, n, _st = 0);
		fill_n(id, n, _ = 0);
		rep(i, 0, n) if(!dfn[i]) dfs(i, g);
		rep(i, 0, n) --id[i];
		return ;
	}
	bool solve() {
		find();
		for(int i = 0; i < n; i += 2) {
			if(id[i] == id[i + 1]) return 0;
			mark[i >> 1] = (id[i] > id[i + 1]);
		}
		return 1;
	}
} G;

int T, n, m, x, y, o, a[N][2];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m;
		G.init(n);
		rep(i, 1, n+1) {
			cin >> x;
			a[i][0] = x, a[i][1] = (x + 1 > 3 ? 1 : x + 1);
		}
		rep(i, 1, m+1) {
			cin >> x >> y >> o;
			rep(j, 0, 2) rep(k, 0, 2) if (a[x][j] == a[y][k]) {
				if (o == 1) G.add_then(x - 1, j, y - 1, k);
			}else {
				if (o == 0) G.add_then(x - 1, j, y - 1, k);
			}
		}
		cout << "Case #" << cas + 1 << ": "; 
		if (G.solve()) cout << "yes"; else cout << "no";
		cout << endl;
	}
	return 0;
}
