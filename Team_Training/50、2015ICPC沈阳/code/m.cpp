#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl '\n'
#define pw(x) (1ll << (x))
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const ll inf = pw(60);
const int N = 2e5 + 7;
ll dis[N], ans, dis1[N], dis2[N];
int n, m, nn, T, u, t, k;
bool vis[N];
vi tmp;
vector<pii> g[N];

void dij(int s) {
	rep(i, 1, n+1) dis[i] = inf, vis[i] = 0; dis[s] = 0;
	priority_queue<pair<ll, int> > q; 
	q.push(mp(0, s));
	while (!q.empty()) {
		auto u = q.top(); q.pop();
		if (vis[u.se]) continue;
		vis[u.se] = 1;
		for (auto v : g[u.se]) if (dis[v.fi] > dis[u.se] + v.se){
			dis[v.fi] = dis[u.se] + v.se;
			q.push(mp(-dis[v.fi], v.fi));
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m; nn = n;
		rep(i, 1, n+m+1) g[i].clear();
		rep(i, 1, m+1) {
			cin >> t >> k; ++n;
			rep(j, 1, k+1) {
				cin >> u;
				g[u].pb(mp(n, t));
				g[n].pb(mp(u, t));
			}
		}
		dij(1);
		rep(i, 1, n+1) dis1[i] = dis[i] / 2;
		dij(nn);
		rep(i, 1, n+1) dis2[i] = dis[i] / 2;
		ans = inf; tmp.clear();
		rep(i, 1, nn+1) {
			if (max(dis1[i], dis2[i]) < ans) {
				ans = max(dis1[i], dis2[i]);
				tmp.clear();
				tmp.pb(i);
			}else if (max(dis1[i], dis2[i]) == ans) {
				tmp.pb(i);
			}
		}
		cout << "Case #" << cas + 1 << ": " ;
		if (ans <= pw(55)) {
			cout << ans << endl;
			rep(i, 0, sz(tmp)) cout << tmp[i] << " \n"[i == sz(tmp) - 1];
		}else {
			cout << "Evil John" << endl;
		}

	}
	return 0;
}
