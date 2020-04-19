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

inline int find(int x) { 
	while(x != pre[x]) x = pre[x];
	return x;
}

void dfs(int u) {
	int a = nd[u].a, b = nd[u].b;
	int tdel = 0, ty = 0, tcnt = 0, tx = 0, tpre = 0, cx = 0, ta = 0, tid = 0, tty = 0;
	int f = 0;
	if(u) {
		if(nd[u].o == 1) {
			if(!del[a] && !del[b]) {
				int x = find(id[a]), y = find(id[b]);
				if(x != y) {
					f = 1;
					if(rk[x] > rk[y]) swap(x, y);
					if(rk[x] == rk[y]) ++rk[y], ty = y;
					tcnt = cnt[y]; cnt[y] += cnt[x]; tty = y;
					tx = x, tpre = pre[x], pre[x] = y;
				}
			} 
		} else if(nd[u].o == 2) {
			if(!del[a]) {
				f = 2;
				int x = find(id[a]);
				cx = x; --cnt[x];
				tdel = del[a]; del[a] = 1;
			}
		} else if(nd[u].o == 3) {
			if(!del[a] && !del[b]) {
				int x = find(id[a]), y = find(id[b]);
				if(x != y) {
					f = 3;
					cx = x; --cnt[x];
					ta = a, tid = id[a], id[a] = ++L;
					x = id[a];
					if(rk[x] == rk[y]) ++rk[y], ty = y;
					tcnt = cnt[y]; cnt[y] += cnt[x]; tty = y;
					tx = x, tpre = pre[x], pre[x] = y;
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
	if(u) {
		if(f == 1) {
			--rk[ty];
			cnt[tty] = tcnt;
			pre[tx] = tpre;
		} else if(f == 2) {
			++cnt[cx];
			del[a] = tdel;
		} else if(f == 3) {
			--rk[ty];
			cnt[tty] = tcnt;
			pre[tx] = tpre;
			++cnt[cx];
			id[ta] = tid;
		}
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
		else if(nd[i].o == 5) printf("%d\n",ans[i]);//cout << ans[i] << endl;
//		if(nd[i].o == 4) cout << (ans[i] ? "Yes" : "No") << endl;
//		else if(nd[i].o == 5) cout << ans[i] << endl;
	}
}

int main() {
	solve();
	return 0;
}


