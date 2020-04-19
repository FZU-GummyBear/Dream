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

const int N = 2e6 + 11;

struct Node {
	int o, k, a, b;
};

int n, m, ans[N], pre[N], cnt[N], del[N], id[N], L, rk[N];
Node nd[N];
vi g[N];
pair<int*, int> sta[N * 5];
int top;

inline int find(int x) { 
	while(x != pre[x]) x = pre[x];
	return x;
}
void add(int &a) { sta[++top] = mp(&a, a); }
// assert x == pre[x] && y == pre[y] && x != y
inline void join(int x, int y) {
	if(rk[x] > rk[y]) swap(x, y);
	if(rk[x] == rk[y]) add(rk[y]), ++rk[y];
	add(cnt[y]); cnt[y] += cnt[x]; 
	add(pre[x]); pre[x] = y;
}
void dfs(int u) {
	int a = nd[u].a, b = nd[u].b;
	int ttop = top;
	if(u) {
		if(nd[u].o == 1) {
			if(!del[a] && !del[b]) {
				int x = find(id[a]), y = find(id[b]);
				if(x != y) join(x, y);
			} 
		} else if(nd[u].o == 2) {
			if(!del[a]) {
				int x = find(id[a]);
				add(cnt[x]); --cnt[x];
				add(del[a]); del[a] = 1;
			}
		} else if(nd[u].o == 3) {
			if(!del[a] && !del[b]) {
				int x = find(id[a]), y = find(id[b]);
				if(x != y) {
					add(cnt[x]); --cnt[x];
					add(id[a]); id[a] = ++L;
					x = id[a];
					join(x, y);
				}
			}
		} else if(nd[u].o == 4) {
			if(del[a] || del[b]) ans[u] = 0;
			else ans[u] = (find(id[a]) == find(id[b]));
		} else {
			if(del[a]) ans[u] = 0;
			else ans[u] = cnt[find(id[a])];
		}
	}
	for(auto v : g[u]) dfs(v);
	while(top > ttop) {
		*sta[top].fi = sta[top].se;
		--top;
	}
}

void solve() {
	scanf("%d%d", &n, &m);
	rep(i, 0, m + 1) g[i].clear(), ans[i] = 0;
	rep(i, 0, n + m + 1) pre[i] = i, cnt[i] = 1, rk[i] = 0;
	rep(i, 0, n + 1) del[i] = 0, id[i] = i; 
	L = n;
	rep(i, 1, m + 1) {
		scanf("%d%d%d", &nd[i].o, &nd[i].k, &nd[i].a);
		if(nd[i].o != 2 && nd[i].o != 5) scanf("%d", &nd[i].b);
		g[nd[i].k].pb(i);
	}
	dfs(0);
	rep(i, 1, m + 1) {
		if(nd[i].o == 4) printf("%s\n", ans[i] ? "Yes" : "No");
		else if(nd[i].o == 5) printf("%d\n",ans[i]);
	}
}

int main() {
	solve();
	return 0;
}


