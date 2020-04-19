#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll << (x))
#define endl '\n'
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int P = 1e9 + 7, N = 1e5 + 7;
int f[N][3], a[N], u, v, T, n, x;
vi g[N];


int add(int a, int b) {
	if ((a += b) >= P) a -= P;
	return a < 0 ? a + P : a;
}

int mul(int a, int b) {
	return 1ll * a * b % P;
}

void dfs(int u, int fa) {
	rep(j, 0, 3) f[u][j] = 0;
	int tmp[6][3], m = 0, b[6];
	for (auto v : g[u]) if (v != fa) {
		dfs(v, u);
		rep(j, 0, 3) tmp[m][j] = f[v][j];
		b[m] = a[v];
		m++;
	}
	if (m == 0) {
		f[u][0] = f[u][1] = 1;
		f[u][2] = a[u] + a[fa] >= 0;
		return;
	}
	f[u][0] = 1;
	rep(i, 0, m) f[u][0] = mul(f[u][0], add(tmp[i][0], tmp[i][1]));
	int S = pw(m);
	rep(i, 0, S) {
		if (a[u] >= 0) {
			int t = 0, tt = 1;
			rep(j, 0, m) if ((i >> j) & 1) {
				if (b[j] < 0) t += b[j];
				tt = mul(tt, tmp[j][1]);
			} else tt = mul(tt, tmp[j][0]);
			if (t + a[u] >= 0) f[u][1] = add(f[u][1], tt);
			if (t + a[u] + a[fa] >= 0) f[u][2] = add(f[u][2], tt);
		}else {
			int t = 1, tt = 1;
			rep(j, 0, m) if ((i >> j) & 1) {
				if (b[j] < 0) t = 0;
				tt = mul(tt, tmp[j][2]);
			} else tt = mul(tt, tmp[j][0]);
			if (t) f[u][1] = add(f[u][1], tt);
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> x;
		rep(i, 1, n+1) g[i].clear();
		rep(i, 1, n+1) cin >> a[i], a[i] = x - a[i];
		rep(i, 1, n) {
			cin >> u >> v;
			g[u].pb(v);
			g[v].pb(u);
		}
		dfs(1, 0);
		cout << add(f[1][0], f[1][1]) << endl;
	}
	return 0;
}
