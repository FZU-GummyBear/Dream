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
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

static const int N = 3030, P = 998244353;

int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a < 0 ? a + P : a;
}
int mul(int a, int b) {
	return 1ll * a * b % P;
}
int kpow(int a, int b) {
	int r = 1;
	while(b) {
		if(b & 1) r = mul(r, a);;
		a = mul(a, a);
		b >>= 1;
	}
	return r;
}

int n, m, in[N], a[N][N], cnt[N], b[N][N], p[N];
vi g[N];

namespace GI {
	int x[N];
	int free[N], fnum, k, col, p;
	int solve(int equ, int var) {
		for(k = col = 0; k < equ && col < var; ++k, ++col) {
			p = k; rep(i, k, equ) if(a[i][col]) { p = i; break; }
			if(p != k) rep(j, col, var + 1) swap(a[p][j], a[k][j]);
			if(!a[k][col]) {k--; continue; }
			int inv = kpow(a[k][col], P - 2);
			rep(i, col, var + 1) a[k][i] = mul(a[k][i], inv);
			rep(i, k + 1, equ) if(a[i][col]) {
				int t = a[i][col];
				rep(j, col, var + 1) a[i][j] = add(a[i][j], -mul(a[k][j], t));
			}
		}
		//rep(i, k, equ) if(a[i][var]) return -1;
		int ret = 0;
		per(i, 0, var) {
			int t = a[i][var];
			rep(j, i + 1, var) if(a[i][j]) t = add(t, -mul(a[i][j], x[j]));
			x[i] = t;
			ret = add(ret, x[i]);
		}
		ret = add(ret, -1);
		cout << ret << endl;
		return 0;
	}
}
bool cmp(int i, int j) {
	return cnt[i] > cnt[j];
}
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n + 1) {
		int x, y; cin >> x >> y;
	}
	cin >> m;
	rep(i, 1, m + 1) {
		int u, v; cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	rep(i, 1, n + 1) sort(all(g[i]));
	rep(i, 1, n + 1) in[i] = kpow(i, P - 2);
	rep(i, 1, n + 1) {
		if(i == 1) a[i - 1][n] = P - 1, ++cnt[i - 1];
		a[i - 1][i - 1] = P - 1, ++cnt[i - 1];
		for(auto j : g[i]) if(j != n) a[i - 1][j - 1] = in[sz(g[j])], ++cnt[i - 1];
	}
	rep(i, 0, n) p[i] = i;
	sort(p, p + n, cmp);
	rep(i, 0, n) rep(j, 0, n + 1) b[i][j] = a[p[i]][j];

	rep(i, 0, n) p[i] = i, cnt[i] = 0;
	rep(j, 0, n) rep(i, 0, n) if(b[i][j]) cnt[j] = i;
	sort(p, p + n, cmp);
	p[n] = n;
	rep(i, 0, n) rep(j, 0, n + 1) a[i][j] = b[i][p[j]];

	GI::solve(n, n);
	return 0;
}