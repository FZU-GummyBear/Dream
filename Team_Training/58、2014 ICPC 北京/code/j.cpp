#pragma GCC optimize(3)
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse2")
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
typedef vector<int> vi;
typedef pair<int, int> pii;

const int P = 1e9 + 7, N = 205;

int f[N][N], vf[N][N]; // 根能选且选 
int g[N][N], vg[N][N]; // 根能选不选 
int h[N][N], vh[N][N]; // 根不能选 

vi gg[N];

int C[220][220], siz[N], u, v, T, n;

inline int add(int a, int b) {
	if ((a += b) >= P) a -= P;
	return a;
}

inline int mul(int a, int b) {
	return 1ll * a * b % P;
}

inline void upd(int &x, int y) {
	x = add(x, y);
}

inline int solve(int a, int b, int c, int o, int n, int m) {
	if (o == 1) a = n + 1 - a, b = m + 1 - b, c = n + m - c + 1;
	assert(n + m <= 200);
	int res = 0, t1 = a + b - c - 1; 
	if (c - 1 < a - 1 || t1 < 0) return 0;
	rep(d, max(a + b, c+1) , n+b+1) res = add(res, mul(C[d - c - 1][t1], C[n + m - d][m - b]));
	res = mul(res, C[c-1][a-1]);
	return res;
}

int ftmp[N], vftmp[N];
int gtmp[N], vgtmp[N];
int htmp[N], vhtmp[N];

void dfs(int u, int fa) {
	vf[u][1] = f[u][1] = 1;
	vg[u][1] = 0; g[u][1] = 1;
	vh[u][1] = h[u][1] = 0;
	siz[u] = 1;
	for (auto v : gg[u]) if (v != fa) dfs(v, u); 
	for (auto v : gg[u]) if (v != fa) {
		int n = siz[u], m = siz[v];
		rep(a, 1, n+1) {
			rep(b, 1, m+1) {
				rep(c, 1, n+m+1) {
					int w1 = solve(a, b, c, 0, n, m);
					int w2 = solve(a, b, c, 1, n, m);
					int w = add(w1, w2);
					if (w) {
					upd(ftmp[c], mul(mul(f[u][a], h[v][b]), w));  
					upd(vftmp[c], mul(mul(vf[u][a], h[v][b]), w));
					upd(vftmp[c], mul(mul(vh[v][b], f[u][a]), w));

					upd(gtmp[c], mul(mul(g[u][a], h[v][b]), w));
					upd(vgtmp[c], mul(mul(vg[u][a], h[v][b]), w));
					upd(vgtmp[c], mul(mul(vh[v][b], g[u][a]), w));
					
					upd(htmp[c], mul(mul(h[u][a], h[v][b]), w));
					upd(vhtmp[c], mul(mul(vh[u][a], h[v][b]), w));
					upd(vhtmp[c], mul(mul(vh[v][b], h[u][a]), w));
					
					upd(htmp[c], mul(mul(h[u][a], f[v][b]), w));
					upd(vhtmp[c], mul(mul(vh[u][a], f[v][b]), w));
					upd(vhtmp[c], mul(mul(h[u][a], vf[v][b]), w));
					}
					if (w1) {
					upd(ftmp[c], mul(mul(f[u][a], g[v][b]), w1));
					upd(vftmp[c], mul(mul(vf[u][a], g[v][b]), w1));
					upd(vftmp[c], mul(mul(f[u][a], vg[v][b]), w1));

					upd(gtmp[c], mul(mul(g[u][a], f[v][b]), w1));
					upd(vgtmp[c], mul(mul(vg[u][a], f[v][b]), w1));
					upd(vgtmp[c], mul(mul(g[u][a], vf[v][b]), w1));
					}
					if (w2) {
					upd(htmp[c], mul(mul(g[u][a], f[v][b]), w2));
					upd(vhtmp[c], mul(mul(vg[u][a], f[v][b]), w2));
					upd(vhtmp[c], mul(mul(g[u][a], vf[v][b]), w2));
					}
				}	
			}
		}
		siz[u] += siz[v];
		n += m;
		rep(i, 1, n+1) {
			f[u][i] = ftmp[i]; ftmp[i] = 0;
			vf[u][i] = vftmp[i]; vftmp[i] = 0;
			g[u][i] = gtmp[i]; gtmp[i] = 0;
			vg[u][i] = vgtmp[i]; vgtmp[i] = 0;
			h[u][i] = htmp[i]; htmp[i] = 0;
			vh[u][i] = vhtmp[i]; vhtmp[i] = 0;
		}
	}	
}

int main() {
	freopen("a.in", "r", stdin);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T; 
	n = 205;
	C[0][0] = 1;
	rep(i, 1, n+1) {
		C[i][0] = 1;
		rep(j, 1, i+1) C[i][j] = add(C[i-1][j], C[i-1][j-1]);
	}
	rep(cas, 0, T) {
		cin >> n; 
		rep(i, 1, n+1) gg[i].clear();
		memset(f, 0, sizeof(f));
		memset(g, 0, sizeof(f));
		memset(h, 0, sizeof(f));
		memset(vf, 0, sizeof(f));
		memset(vg, 0, sizeof(f));
		memset(vh, 0, sizeof(f));
		rep(i, 1, n) {
			cin >> u >> v;
			gg[u].pb(v);
			gg[v].pb(u);
		}
		dfs(1, 0);
		int ans = 0;
		rep(i, 1, n+1) ans = add(ans, vf[1][i]), ans = add(ans, vh[1][i]);
		cout << "Case #" << cas + 1 << ": " << ans << endl;
	}
	return 0;
}
