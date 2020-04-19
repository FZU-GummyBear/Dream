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
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

struct node{
	int u, ms;//, ms2;
	node(int a = 0, int b = 0) { u = a; ms = b;}
	//int val() {return (ms1 << 8) + ms2;}
};

const int N = 1 << 16;
int tt[2][55][10], nn, x,  has[55], col[55], T, dis[51][N], u, v, w, n, m, k, ans;
vector<pii> g[55];
bool vis[51][N];
queue<node> q;


int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	//db xx = sizeof(dis);
	//de(xx / 1024);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m >> k;
		rep(i, 1, n+1) {
			g[i].clear();
			has[i] = col[i] = 0;
		}
		rep(i, 0, m) {
			cin >> u >> v >> w;
			g[u].pb(mp(v, w));
			g[v].pb(mp(u, w));
		}
		rep(i, 0, k) {
			cin >> u; cin >> tt[0][u][i] >> tt[1][u][i] >> nn;
			tt[1][u][i] = min(tt[1][u][i], tt[0][u][i]);
			rep(j, 0, nn) cin >> x, col[x] |= pw(i);
			has[u] |= pw(i);
		}
		memset(dis, 0x3f, sizeof(dis));
		dis[1][col[1]] = 0;
		vis[1][col[1]] = 1;
		q.push(node(1, col[1]));
		while (!q.empty()) {
			node t = q.front(); q.pop(); vis[t.u][t.ms] = 0;
			//dd(t.u), dd(t.ms1), de(t.ms2);
			rep(i, 0, k) if (pw(i) & has[t.u]) {
				node nx = t; nx.ms |= pw(i) << 8;
				if (dis[nx.u][nx.ms] > dis[t.u][t.ms] + tt[(t.ms >> i) & 1][t.u][i]) {
					dis[nx.u][nx.ms] = dis[t.u][t.ms] + tt[(t.ms >> i) & 1][t.u][i];
					if (!vis[nx.u][nx.ms]) {
						q.push(nx);
						vis[nx.u][nx.ms] = 1;
					}
				}
			}
			for (auto v : g[t.u]) {
				node nx = t; nx.u = v.fi; nx.ms |= col[v.fi];
				if (dis[nx.u][nx.ms] > dis[t.u][t.ms] + v.se) {
					dis[nx.u][nx.ms] = dis[t.u][t.ms] + v.se;
					if (!vis[nx.u][nx.ms]) {
						q.push(nx);
						vis[nx.u][nx.ms] = 1;
					}
				}
			}
		}
		ans = pw(30);
		rep(i, 0, pw(k)) ans = min(ans, dis[1][((pw(k) - 1) << 8) + i]);
		cout << "Case #" << cas + 1 << ": " << ans << endl;
	}
	return 0;
}
