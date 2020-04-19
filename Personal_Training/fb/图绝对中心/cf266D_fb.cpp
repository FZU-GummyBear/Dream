#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) (a).begin(), (a).end()
#define pw(x) (1ll<<(x))
#define lb(x) ((x) & -(x))
#define endl "\n"
#define FI(x) freopen(#x".in","r",stdin)
#define FO(x) freopen(#x".out","w",stdout)
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
//typedef uniform_int_distribution<ll> RR;
//mt19937 gen(998244353);
//ll rnd(ll l, ll r) { RR dis(l, r); return dis(gen); }
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

// id : 0 .. n - 1
// time : O(n ^ 3)
// g[i][i] should be 0

const int N = 1e3 + 7, inf = 1e9 + 7;
int n, m, g[N][N], u, v, w;

pii GraphCenter(int n, int g[][N]) {
	static int rk[N][N], d[N][N];
	rep(i, 0, n) rep(j, 0, n) d[i][j] = g[i][j], rk[i][j] = j;
	rep(k, 0, n) rep(i, 0, n) rep(j, 0, n) 
		d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
	rep(i, 0, n) sort(rk[i], rk[i] + n, [&](int a, int b) {return d[i][a] < d[i][b];});
	int ret = inf, s1 = -1, s2 = -1;
	db ds1 = 0, ds2 = 0;
	rep(u, 0, n) {
		if (d[u][rk[u][n - 1]] * 2 < ret) {
			ret = d[u][rk[u][n - 1]] * 2;
			s1 = s2 = u;
			ds1 = ds2 = 0;
		}
		rep(v, 0, n) if (g[u][v] != inf) {
			for (int k = n - 1, i = n - 2; i >= 0; --i) {
				int x = rk[u][i], y = rk[u][k]; 
				if (d[v][x] > d[v][y]) {
					int tmp = d[u][x] + d[v][y] + g[u][v];
					if (tmp < ret) {
						ret = tmp, s1 = u, s2 = v;
						ds1 = 0.5 * tmp - d[u][x];
						ds2 = g[u][v] - ds1;
					}
					k = i;
				}
			}
		}
	}
	cout << ret / 2.0 << endl;
	return mp(s1, s2);
}


int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(10);
	cin >> n >> m;
	rep(i, 0, n) rep(j, 0, n) g[i][j] = inf;
	rep(i, 0, n) g[i][i] = 0;
	rep(i, 0, m) {
		cin >> u >> v >> w;
		u--; v--;
		g[u][v] = g[v][u] = w;
	}
	GraphCenter(n, g);
	return 0;
}
