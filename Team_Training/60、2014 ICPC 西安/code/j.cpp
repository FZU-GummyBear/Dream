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

const int N = 55;
ll f[N][N][N], tmp[N][N], c[N][N];
vi g[N];
int a[N], T, n, siz[N], x;

db jc[N], s[N * 10][N];

void dfs(int u) {
	memset(f[u], 0, sizeof(f[u]));
	f[u][1][0] = 1;
	f[u][0][1] = 1;
	siz[u] = 1;
	for (auto v : g[u]) dfs(v);
	for (auto v : g[u]) {
		for (int x = 0; x <= siz[u]; x++)
			for (int k = 0; k <= siz[u]; k++)
				for (int y = 0; y <= siz[v]; y++)
					for (int w = 0; w <= siz[v]; w++) {
						int t = max(x, y == 0 ? 0 : y + 1);
						if (x) tmp[t][k + w] += f[u][x][k] * f[v][y][w];
						else tmp[t > a[u] ? t : 0][k + w] += f[u][x][k] * f[v][y][w];
					} 
		siz[u] += siz[v];
		rep(x, 0, siz[u] + 1) rep(k, 0, siz[u] + 1) f[u][x][k] = tmp[x][k], tmp[x][k] = 0;
	}
}

int main() {
//	std::ios::sync_with_stdio(0);
//	std::cin.tie(0);
	cin >> T;
	n = 50;
	rep(i, 0, n+1) {
		c[i][0] = 1;
		rep(j, 1, i+1) c[i][j] = c[i-1][j] + c[i-1][j-1];
	} 
	jc[0] = 1; rep(i, 1, n+1) jc[i] = jc[i-1] * i;
	rep(cas, 0, T) {
		cin >> n;
		rep(i, 1, n+1) cin >> a[i], a[i]++, g[i].clear();
		rep(i, 2, n+1) cin >> x, g[x].pb(i);
		dfs(1);
		db ans = 0;
		rep(k, 1, n) {
			db t3 = 1;
			rep(i, 1, k+1) t3 *= n - i;
			ans += jc[k] * (c[n][k] - f[1][0][k]) / t3; 
		}
		printf("Case #%d: %.10f\n",cas + 1, ans + 1);
	}
	return 0;
}
