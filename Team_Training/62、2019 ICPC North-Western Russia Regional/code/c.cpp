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

const int N = 111, M = 40404;

int n, m, st, L;
char s[N][N];
vector<pii> g[M], ans;
bool vis[M];

pii Get(int u) { return mp(u / (m + 1), u % (m + 1)); }
int id(int x, int y) { return x * (m + 1) + y; }
void add(int u, int v, int o) {
	st = u; ++L;
	g[u].pb(mp(v, o * L));
	g[v].pb(mp(u, o * L));
}
void dfs(int u, int o) {
	for(auto v : g[u]) if(!vis[abs(v.se)] && v.se * o > 0) {
		vis[abs(v.se)] = 1;
		dfs(v.fi, -o);
		ans.pb(Get(v.fi));
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> m >> n;
	rep(i, 0, n) {
		cin >> s[i];
		rep(j, 0, m) if(s[i][j] == 'X') {
			add(id(i, j), id(i + 1, j + 1), 1);
			add(id(i + 1, j), id(i, j + 1), 1);
			add(id(i, j), id(i + 1, j), -1);
			add(id(i, j + 1), id(i + 1, j + 1), -1);
		}
	}
	dfs(st, 1); ans.pb(Get(st));
	reverse(all(ans));
	ans.pop_back();
	cout << sz(ans) - 1 << endl;
	assert(sz(ans) == L);
	for(auto u : ans) cout << u.se << " " << u.fi << endl;
	return 0;
}
