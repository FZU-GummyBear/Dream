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

const int N = 202020;

vi pri[N];
int n, m, w[N], tmp[N], ans[N];

int top;
struct Node {
	int t, x, y, i;
	bool o, ty;
	Node() {}
	Node(int t, int x, int y, bool o, int i = 0) : t(t), x(x), y(y), o(o), i(i) {}
	bool operator < (const Node &c) const {
		if(t != c.t) return t < c.t;
		return o < c.o;
	}
}nd[N * 3], tt[N * 3];

void init() {
	int n = 2e5;
	rep(i, 2, n + 1) if(!sz(pri[i])) {
		for(int j = i; j <= n; j += i) pri[j].pb(i);
	}
}
struct FW {
#define lb(x) (x & -x)
	int a[N], tot;
	void init(int p) {
		tot = 0;
		for( ; p <= n; p += lb(p)) {
			if(!a[p]) break;
			a[p] = 0;
		}
	}
	void upd(int p, int c) {
		tot += c;
		for( ; p <= n; p += lb(p)) a[p] += c;
	}
	int qry(int p) {
		p = p - 1;
		int ans = tot;
		for( ; p; p ^= lb(p)) ans -= a[p];
		return ans;
	}
}fw;
void solve(int l, int r) {
	if(l >= r) return ;
	int m = l + r >> 1;
	solve(l, m); solve(m + 1, r);
	rep(i, l, r + 1) nd[i].ty = i > m;
	int p = l, q = m + 1, k = l;
	while(p <= m && q <= r) {
		if(nd[p].x < nd[q].x) tt[k++] = nd[p++];
		else tt[k++] = nd[q++];
	}
	while(p <= m) tt[k++] = nd[p++];
	while(q <= r) tt[k++] = nd[q++];
	rep(i, l, r + 1) nd[i] = tt[i];
	rep(i, l, r + 1) {
		if(nd[i].ty == 0) {
			if(nd[i].o == 0) {
				fw.upd(nd[i].y - 1, 1);
			}
		} else {
			if(nd[i].o == 1) {
				int t = abs(nd[i].i);
				int res = fw.qry(nd[i].y);
				if(nd[i].i > 0) ans[t] += res;
				else ans[t] -= res;
			}
		}
	}
	rep(i, l, r + 1) if(nd[i].ty == 0 && nd[i].o == 0) fw.init(nd[i].y - 1);
}

void solve() {
	rep(i, 1, n + 1) cin >> w[i];
	top = 0;
	rep(i, 1, m + 1) {
		int l, r; cin >> l >> r;
		ans[i] = 0;
		nd[++top] = Node(r    , l, r, 1,  i);
		nd[++top] = Node(l - 1, l, r, 1, -i);
	}
	rep(i, 1, n + 1) nd[++top] = Node(i, 0, 0, 0);
	// a[i]
	rep(i, 1, n + 1) for(auto j : pri[w[i]]) tmp[j] = 0;
	rep(i, 1, n + 1) {
		int &a = nd[i + 2 * m].x = 0;
		for(auto j : pri[w[i]]) a = max(a, tmp[j]);
		for(auto j : pri[w[i]]) tmp[j] = i;//, dd(i), de(j);
	}
	// b[i]
	rep(i, 1, n + 1) for(auto j : pri[w[i]]) tmp[j] = n + 1;
	per(i, 1, n + 1) {
		int &b = nd[i + 2 * m].y = n + 1;
		for(auto j : pri[w[i]]) b = min(b, tmp[j]);
		for(auto j : pri[w[i]]) tmp[j] = i;
	}
	// nd
	sort(nd + 1, nd + 1 + top);
	solve(1, top);
	rep(i, 1, m + 1) cout << ans[i] << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	init();
	
	db x = 0;// x = sizeof(pri);
	x += sizeof(tt) * 2;
	x += sizeof(tmp) * 9;
	x += sizeof(fw);
	de(x / 1024);
	
	while(cin >> n >> m) {
		if(!n && !m) break;
		solve();
	}
	return 0;
}
