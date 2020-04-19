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

const int N = 333;

int n, a[N][3], b[N][3];
int ans[N];
vector<pii> e;
vi vec[8];
bool vis[8];
int nd[8];

bool solve() {
	// init ans
	rep(i, 1, n + 1) ans[i] = 1;
	// set vec
	rep(i, 1, n + 1) {
		int x = 0; rep(j, 0, 3) x = x * 2 + a[i][j];
		vec[x].pb(i);
	}
	// init que
	vi que; 
	rep(i, 1, sz(vec[7])) e.pb(mp(1, vec[7][i]));
	for(auto i : vec[7]) que.pb(i);
	// init vis
	vis[7] = vis[0] = 1;
	// solve
	rep(_, 0, sz(que)) {
		int i = que[_];
		int x = 0;
		rep(j, 0, 3) x = x * 2 + (a[i][j] & b[i][j]);
		if(!vis[x]) {
			vis[x] = 1;
			for(auto j : vec[x]) e.pb(mp(i, j)), que.pb(j);
			nd[x] = i;
		}
	}
	rep(i, 0, 8) if(!vis[i]) {
		int cc = 0;
		rep(j, 0, 3) cc += i >> j & 1; 
		if(cc == 1) {
			if(sz(vec[i])) return 0;
			continue;
		}
		if(sz(vec[i]) == 0) continue;
		int u = i & (-i), v = i ^ u;
		if(vis[u] && vis[v]) {
			int tu = nd[u], tv = nd[v];
			int k = vec[i][0];
			ans[k] = 0;
			e.pb(mp(tu, k));
			e.pb(mp(tv, k));
			rep(j, 1, sz(vec[i])) e.pb(mp(k, vec[i][j]));
		} else {
			return 0;
		}
	}
	return 1;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n + 1) rep(j, 0, 3) cin >> a[i][j];
	rep(i, 1, n + 1) rep(j, 0, 3) cin >> b[i][j];
	if(solve()) {
		cout << "Possible" << endl;
		rep(i, 1, n + 1) cout << ans[i] << " \n"[i == n];
		cout << sz(e) << endl;
		for(auto u : e) cout << u.fi << " " << u.se << endl;
	} else {
		cout << "Impossible" << endl;
	}
	return 0;
}
