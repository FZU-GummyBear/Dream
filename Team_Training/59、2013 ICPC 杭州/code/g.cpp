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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define endl '\n'
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 1e5 + 7, M = 61;

int n;
vector<pair<int, ll> > g[N];
ll val[N];
int ne[N * (M + 1)][2], cnt[N * (M + 1)], ed[N * (M + 1)], L, rt[N];

int m, k, Q[N]; 
ll ans[202020];

struct Node {
	ll val; int L, R, i, j;
	Node() {}
	Node(ll val, int L, int R, int i, int j) : val(val), L(L), R(R), i(i), j(j) {}
	bool operator < (const Node &c) const { return val < c.val; }
};

priority_queue<Node> que;

void dfs(int u, int fa) {
	for(auto v : g[u]) if(v.fi != fa) {
		val[v.fi] = val[u] ^ v.se;
		dfs(v.fi, u);
	}
}

void add(int &now, int pre, ll val, int ind, int dep = M - 1) {
	now = ++L;
	ne[now][0] = ne[pre][0];
	ne[now][1] = ne[pre][1];
	cnt[now] = cnt[pre] + 1;
	ed[now] = ed[pre];
	if(dep == -1) return ed[now] = ind, void();
	int c = val >> dep & 1;
	add(ne[now][c], ne[pre][c], val, ind, dep - 1);
}

int qry(int L, int R, ll val) {
	per(i, 0, M) {
		int c = val >> i & 1;
		if(cnt[ne[R][c ^ 1]] - cnt[ne[L][c ^ 1]]) c ^= 1;
		R = ne[R][c], L = ne[L][c];
	}
	return ed[R];
}


void add(int L, int R, int i) {
	if(L > R) return ;
	int j = qry(rt[L - 1], rt[R], val[i]);
	que.push(Node(val[i] ^ val[j], L, R, i, j));
}

void solve() {
	rep(i, 1, n + 1) g[i].clear();
	rep(i, 1, n) {
		int u, v; ll w; cin >> u >> v >> w;
		g[u].pb(mp(v, w));
		g[v].pb(mp(u, w));
	}
	dfs(1, 0);
	L = 0; rep(i, 1, n + 1) add(rt[i], rt[i - 1], val[i], i);
	while(!que.empty()) que.pop();
	rep(i, 2, n + 1) add(1, i - 1, i);
	int mak = 0;
	cin >> m;
	rep(i, 1, m + 1) cin >> Q[i], mak = max(mak, Q[i]);
	k = 0;
	while(!que.empty() && k < mak) {
		auto u = que.top(); que.pop();
		ans[++k] = u.val;
		ans[++k] = u.val;
		add(u.L, u.j - 1, u.i);
		add(u.j + 1, u.R, u.i);
	}
	rep(i, 1, m + 1) {
		if(Q[i] > k) cout << -1 << endl;
		else cout << ans[Q[i]] << endl;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while(cin >> n) {
		if(!n) break;
		solve();
	}
	return 0;
}
