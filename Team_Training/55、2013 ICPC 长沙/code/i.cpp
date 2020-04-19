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

const int N = 1e5 + 8;
int flag, x, a[N], f[N][2], n, w[2], col[N], t1[N], t2[N];
vi g[N];

void dfs(int u) {
	flag ^= t1[u];
	col[u] = flag ^ t2[u];
	if (col[u]) a[u] = -a[u];
	int t00 = -w[t1[u]] - a[u];
	int t01 = a[u];
	int t10 = -w[t1[u]] + a[u];
	int t11 = -a[u];
	//if (u == 2) dd(a[u]), dd(t00);//dd(flag), dd(col[u]), de(t01);
	for (auto v : g[u]) {
		dfs(v);
		t00 += f[v][1];
		t01 += f[v][0];
		t10 += f[v][0];
		t11 += f[v][1];
	}
	if (u == 0) f[u][0] = t01;else f[u][0] = max(t00, t01);
	f[u][1] = max(t10, t11);
	flag ^= t1[u];
}

int main() {
	freopen("a.in", "r", stdin);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while (cin >> n >> w[0] >> w[1]) {
		rep(i, 0, n+1) g[i].clear();
		rep(i, 1, n+1) {
			cin >> a[i] >> x >> t1[i] >> t2[i]; g[x].pb(i);
		}
		flag = 0;
		dfs(0);
		//de(f[2][0]); 
		if (f[0][0] < 0) cout << "HAHAHAOMG" << endl;
		else cout << f[0][0] << endl;
	}
	return 0;
}
