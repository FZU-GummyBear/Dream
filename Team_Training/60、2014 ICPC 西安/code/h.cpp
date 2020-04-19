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

const int N = 111;

int n, m, dp[N][N][2], deg[N], du[N][N][2];
vi g[N];
bool vis[N][N][2];

struct Node {
	int x, y, o;
	Node() {}
	Node(int x, int y, int o) : x(x), y(y), o(o) {}
};

bool solve() {
	cin >> n >> m;
	rep(i, 1, n + 1) {
		g[i].clear(), deg[i] = 0;
		rep(j, 1, n + 1) rep(o, 0, 2) dp[i][j][o] = -1, vis[i][j][o] = 0;
	}
	rep(i, 1, m + 1) {
		int u, v; cin >> u >> v;
		g[v].pb(u);
		++deg[u];
	}
	vector<Node> que;
	rep(i, 1, n + 1) rep(j, 1, n + 1) {
		du[i][j][0] = deg[i];
		du[i][j][1] = deg[j];
	}
	rep(i, 1, n + 1) {
		que.pb(Node(i, i, 0));
		que.pb(Node(i, i, 1));
		dp[i][i][0] = 0;
		dp[i][i][1] = 1;
		vis[i][i][0] = vis[i][i][1] = 1;
	}
	rep(i, 1, n + 1) rep(j, 1, n + 1) rep(o, 0, 2) if(!vis[i][j][o] && !du[i][j][o]) {
		vis[i][j][o] = 1;
		dp[i][j][o] = 0;
		que.pb(Node(i, j, o));
	}
	rep(i, 0, sz(que)) {
		auto u = que[i];
		int f = dp[u.x][u.y][u.o];
		if(u.o == 0) {
			for(auto v : g[u.y]) if(!vis[u.x][v][1]) {
				if(!f) {
					dp[u.x][v][1] = 1;
					vis[u.x][v][1] = 1;
					que.pb(Node(u.x, v, 1));
				} else {
					--du[u.x][v][1];
					if(!du[u.x][v][1]) {
						dp[u.x][v][1] = 0;
						vis[u.x][v][1] = 1;
						que.pb(Node(u.x, v, 1));
					}
				}
			}
		} else {
			for(auto v : g[u.x]) if(!vis[v][u.y][0]) {
				if(!f) {
					dp[v][u.y][0] = 1;
					vis[v][u.y][0] = 1;
					que.pb(Node(v, u.y, 0));
				} else {
					--du[v][u.y][0];
					if(!du[v][u.y][0]) {
						dp[v][u.y][0] = 0;
						vis[v][u.y][0] = 1;
						que.pb(Node(v, u.y, 0));
					}
				}
			}
		}
	}
	int x, y; cin >> x >> y;
	return dp[x][y][0] != 0;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	rep(i, 1, T + 1) {
		cout << "Case #" << i << ": ";
		cout << (solve() ? "Yes" : "No") << endl;
	}
	return 0;
}
