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

const int N = 101010;

int n, k, v[N], dep[N];
vi g[N];
vector<pii> V;

pair<int*, int> sta[N * 100];
int top;

void dfs(int u) {
	V.pb(mp(v[u], dep[u]));
	for(auto v : g[u]) {
		dep[v] = dep[u] + 1;
		dfs(v);
	}
}
void add(int &a) { sta[++top] = mp(&a, a); }
struct FW {
#define lb(x) (x & -x)
	int cnt[N];
	void upd(int p) {
		for( ; p <= n; p += lb(p)) {
			add(cnt[p]);
			cnt[p]++;
		}
	}
	int _qry(int p) {
		if(p <= 0) return 0;
		int ans = 0;
		for( ; p; p ^= lb(p)) ans += cnt[p];
		return ans;
	}
	int qry(int L, int R) { return _qry(R) - _qry(L - 1); }
}fw;

int F(pii x) { return lower_bound(all(V), x) - V.begin() + 1; }
// id starts with 1
int sz[N] , wson[N] , par[N];
void dfs(int c,int fa,vi g[]){
	sz[c]=1;par[c]=fa;int &s=wson[c]=0;
	for(auto t:g[c]) if(t!=fa) dfs(t,c,g),sz[c]+=sz[t],(sz[t]>=sz[s])&&(s=t);
}
ll ans;
vi vec;
int tmp, tmp2;
void dfs2(int u) {
	vec.pb(u);
	int l = F(mp(tmp2 - v[u], 0));
	int r = F(mp(tmp2 - v[u], k + tmp - dep[u] + 1)) - 1;
	if(l <= r) ans += fw.qry(l, r);
	for(auto v : g[u]) dfs2(v);
}
void solve(int c,int fa,bool iswson,vi g[]){
	int ttop = top;
	for(auto t : g[c]) if(t != wson[c] && t != fa) solve(t , c , false , g);
	if(wson[c]) solve(wson[c] , c , true , g);
	tmp = 2 * dep[c];
	tmp2 = 2 * v[c];
	for(auto t : g[c]) if(t != wson[c] && t != fa) {
		vec.clear();
		dfs2(t);
		for(auto k : vec) fw.upd(F(mp(v[k], dep[k])));
	}
	fw.upd(F(mp(v[c], dep[c])));
	if(!iswson) {
		while(top > ttop) *sta[top].fi = sta[top].se, --top;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> k;
	rep(i, 1, n + 1) cin >> v[i];
	rep(v, 2, n + 1) {
		int u; cin >> u;
		g[u].pb(v);
	}
	dfs(1);
	sort(all(V));
	V.erase(unique(all(V)), V.end());
	dfs(1,0,g);
	solve(1, 0, 1, g);
	cout << ans * 2 << endl;
	return 0;
}
