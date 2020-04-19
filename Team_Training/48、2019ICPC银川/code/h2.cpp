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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 50000 + 11;

int n, x, y, st, pre[N], deg[N], S, dis[N], inf;
bool ok[N];
vector<pii> g[N];
vi G[N];
vi hav[N];
struct Node {
	int u, v, w;
	Node() {}
	Node(int u, int v, int w) : u(u), v(v), w(w) {}
}nd[N];

int find(int x) {
	return (x == pre[x]) ? x : (pre[x] = find(pre[x]));
}
void join(int x, int y) {
	x = find(x), y = find(y);
	pre[x] = y;
}
void gao(int U) {
	priority_queue<pii> que;
	for(auto u : hav[U]) if(dis[u] != inf) que.push(mp(-dis[u], u));
	while(!que.empty()) {
		auto u = que.top(); que.pop();
		if(-u.fi != dis[u.se]) continue;
		for(auto v : g[u.se]) {
			int t = dis[u.se] + v.se;
			if(dis[v.fi] > t) {
				dis[v.fi] = t;
				que.push(mp(-t, v.fi));
			}
		}
	}
}
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	// read pre dag
	cin >> n >> x >> y >> st;
	rep(i, 1, n + 1) pre[i] = i;
	rep(i, 1, x + 1) {
		int u, v, w; cin >> u >> v >> w;
		g[u].pb(mp(v, w));
		g[v].pb(mp(u, w));
		join(u, v);
	}
	rep(i, 1, n + 1) hav[find(i)].pb(i);
	S = find(st);
	rep(i, 1, y + 1) {
		int u, v, w; cin >> u >> v >> w;
		int U = find(u), V = find(v);
		nd[i] = Node(u, v, w);
		G[U].pb(V);
	}
	// init dis
	memset(dis, 0x3f, sizeof(dis));
	inf = dis[0];
	dis[st] = 0;

	// ok
	vi que; que.pb(S);
	ok[S] = 1;
	rep(i, 0, sz(que)) {
		int u = que[i];
		for(auto v : G[u]) if(!ok[v]) {
			ok[v] = 1;
			que.pb(v);
		}
	}


	// build dag
	rep(i, 1, n + 1) G[i].clear();
	rep(i, 1, y + 1) {
		int u = nd[i].u, v = nd[i].v, w = nd[i].w;
		int U = find(u), V = find(v);
		if(ok[U] && ok[V]) {
			G[U].pb(i);
			++deg[V];
		}
	}

	// solve
	que.clear(); que.pb(S);
	rep(i, 0, sz(que)) {
		int U = que[i];
		gao(U);
		for(auto t : G[U]) {
			int V = find(nd[t].v);
			--deg[V];
			int u = nd[t].u, v = nd[t].v;
			if(dis[u] != inf && dis[v] > dis[u] + nd[t].w) {
				dis[v] = dis[u] + nd[t].w;
			}
			if(deg[V] == 0) que.pb(V);
		}
	}
	rep(i, 1, n + 1) {
		if(dis[i] == inf) {
			cout << "NO PATH" << endl;
		} else {
			cout << dis[i] << endl;
		}
	}
	return 0;
}
