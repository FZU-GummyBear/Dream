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
typedef long double db;
typedef vector<int> vi;

const int N = 211;

db a[N][N];
db x[N], sx[N];

vi g[N], ng[N];
int n, m;
bool vis[N];
db px;


namespace GaussDB {
	static const int N = 505;
	int free[N], fnum, k, col, p;
	const db eps = 1e-14;

	int Gauss(int equ, int var) {
		//rep(i, 0, equ) rep(j, 0, var+1) cout << a[i][j] << " \n"[j == var];
		for(k = col = 0; k < equ && col < n; ++k, ++col) {
			p = k; rep(i, k + 1, equ) if(fabs(a[i][col]) > fabs(a[p][col])) p = i;
			if(p != k) rep(j, col, var + 1) swap(a[p][j], a[k][j]);
			if(fabs(a[k][col]) < eps) { k--; continue; }
			rep(i, k + 1, equ) {
				if(fabs(a[i][col]) < eps) continue;
				db t = a[i][col] / a[k][col];
				rep(j, col, var + 1) a[i][j] -= a[k][j] * t;
			}
		}
		rep(i, k, equ) if(fabs(a[i][var]) > eps) return -1;
		if(k < n) return 1;
		rep(i, 0, n - 1) if (!vis[i]) x[i] = a[n-1][var] / a[n-1][i + n];
		x[n-1] = a[n-1][var] / a[n-1][n-1];
		/*per(i, 0, var) {
			db t = a[i][var];
			rep(j, i + 1, var) if(fabs(a[i][j]) > eps) t -= x[j] * a[i][j];
			x[i] = t / a[i][i];
		}*/
		return 0;
	}
};


const db eps = 1e-8;

int sign(db x) {
	return (x > eps) - (x < -eps);
}

int work() {
	int res = -1;
	px = x[n - 1];
	rep(i, 0, n - 1) if(!vis[i]) {
		if (sign(x[i] - px) > 0) px = x[i], res = i;
	}
	return res;
}

void solve() {
	cin >> n >> m;
	rep(i, 0, n) g[i].clear(), ng[i].clear(), vis[i] = 0;
	rep(i, 1, m + 1) {
		int u, v; cin >> u >> v;
		g[u].pb(v);
		ng[v].pb(u);
		if(u == n - 1) vis[v] = 1;
	}
	rep(i, 0, n + 1) rep(j, 0, n + n + 1) a[i][j] = 0;
	rep(j, 0, n + n) a[n][j] = 1;
	rep(i, 0, n) {
		for(auto j : ng[i]) a[i][j] = 1. / sz(g[j]);
		a[i][i] = -1;
	}
	rep(i, 0, n-1) if (!vis[i]) {
		for (auto j : g[n - 1]) a[j][n + i] = 1.0 / (sz(g[n-1]) + 1);
		a[i][n + i] = 1.0 / (sz(g[n-1]) + 1);  
		a[n-1][n + i] = -1;
	}
	
	int res = GaussDB::Gauss(n + 1, n + n - 1);
	if(res != 0) {
		cout << "INF" << endl;
		return ;
	}
	cout << 1 << " ";
	cout << work() << endl;
}

int main() {
	freopen("a.in", "r", stdin);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
