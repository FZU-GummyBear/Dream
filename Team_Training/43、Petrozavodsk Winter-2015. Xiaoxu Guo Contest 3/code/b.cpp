#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(c) cout << #c << " = " << c << endl
#define dd(c) cout << #c << " = " << c << " "
#define endl '\n'
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 44, P = 1e9 + 7;

int n, m, g[N][N][4], col[N], cnt[2], tmp[N];
int ans;
vi G[N];

void dfs(int u, int c) {
	col[u] = c; ++cnt[c];
	for(auto v : G[u]) if(col[v] == -1) dfs(v, c ^ 1);
}

int mul(int a, int b) {
	return 1ll * a * b % P;
}
int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a;
}

int gao(int msk) {
//	de(msk);
	rep(i, 1, n + 1) if(!col[i]) {
		tmp[i] = msk & 1;
		msk >>= 1;
	}
	int res = 1;
	bool vis = 0;
	rep(i, 1, n + 1) if(col[i]) {
		int a = 1, b = 1;
		for(auto j : G[i]) if(!col[j]) {
			a = mul(a, g[j][i][tmp[j] << 1]);
			b = mul(b, g[j][i][tmp[j] << 1 | 1]);
			vis = 1;
		}
		res = mul(res, add(a, b));
	}
//	if(!vis) res = 0;
	return res;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, m + 1) {
		int u, v; cin >> u >> v;
		rep(j, 0, 4) cin >> g[u][v][j], g[v][u][j] = g[u][v][j];
		swap(g[v][u][1], g[v][u][2]);
		G[v].pb(u), G[u].pb(v);
	}
	memset(col, -1, sizeof(col));
	rep(i, 1, n + 1) if(col[i] == -1) dfs(i, 0);
	if(cnt[0] > cnt[1]) {
		rep(i, 1, n + 1) col[i] ^= 1;
		swap(cnt[0], cnt[1]);
	}
	ans = 0;
	if(cnt[0]) {
		rep(i, 0, pw(cnt[0])) ans = add(ans, gao(i));
	}
	cout << ans << endl;
	return 0;
}
