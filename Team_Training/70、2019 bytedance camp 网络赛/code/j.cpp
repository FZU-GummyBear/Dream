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

const int P = 228228239, N = 2e3 + 9;

int f[N][N][2][2], d[N], tmp[N][N][2][2];
vi g[N], qry[N];
int fa[N], n, x, q, a[N], b[N];

void upd(int &x, int y) {
	x = (x + y) % P;
}

void dfs(int u) {
	
	f[u][0][0][0] = 1;
	rep(i, 1, d[u]+1) f[u][i][0][0] = f[u][i][1][0] = 1;
	int t = -1, ma = -1;
	for (auto v : qry[u]) if (ma < d[v]) ma = d[v], t = v;
	if (t != -1) {
		rep(i, d[u] - d[t], d[u]+1) f[u][i][0][1] = f[u][i][1][1] = 1;
	}
	
	for (auto v : g[u]) {
		d[v] = d[u] + 1, dfs(v);
		rep(i, 0, d[u]+1) rep(j, 0, 2) rep(k, 0, 2) rep(l, 0, 2) {
			//if (i == 0) upd(tmp[u][i][j][(k+l)%2], 1ll * f[u][i][j][k] * f[v][i+1][j^1][l] % P);
			upd(tmp[u][i][j][(k+l)%2], 1ll * f[u][i][j][k] * f[v][i+1][j][l] % P);
		}

		memcpy(f[u], tmp[u], sizeof(tmp[u]));
		memset(tmp[u], 0, sizeof(tmp[u]));
	}
	//de(f[3][0][0][0]);
	//	rep(i, 0, d[u]+1) rep(j, 0, 2) rep(k, 0, 2) dd(u), dd(i), dd(j), dd(k), de(f[u][i][j][k]);
	//	cout << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 2, n+1) {
		cin >> x;
		fa[i] = x;
		g[x].pb(i);
	}
	cin >> q;
	rep(i, 1, q+1) {
		cin >> a[i] >> b[i];
		qry[b[i]].pb(a[i]);
	} 
	dfs(1);
	de(f[1][0][0][1]);
	cout << f[1][0][0][1] - f[1][0][0][0] << endl;
	return 0;
}
