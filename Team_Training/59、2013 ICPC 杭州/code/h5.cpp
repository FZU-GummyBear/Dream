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
int n, m, w[N], ans[N];

int top;
struct Node {
	int t, x, y, i;
	Node() {}
	Node(int t, int x, int y, int i = 0) : t(t), x(x), y(y), i(i) {}
	bool operator < (const Node &c) const {
		if(t != c.t) return t < c.t;
		return abs(i) < abs(c.i);
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
	int tot;
	void init(int p) {
		tot = 0;
		for( ; p <= n; p += lb(p)) {
			//if(!w[p]) break;
			w[p] = 0;
		}
	}
	void upd(int p, int c) {
		tot += c;
		for( ; p <= n; p += lb(p)) w[p] += c;
	}
	int qry(int p) {
		p = p - 1;
		int ans = tot;
		for( ; p; p ^= lb(p)) ans -= w[p];
		return ans;
	}
	void init() {
		tot = 0;
		fill_n(w + 1, n, 0);
		//memset(w, 0, sizeof())
	}
}fw;
int p, q, k, t, res;

inline bool cmp(const Node &a, const Node &b) {
	return a.x < b.x; 
}

void solve(int l, int r) {
	if(l >= r) return ;
	int m = l + r >> 1;
	solve(l, m); solve(m + 1, r);
	//rep(i, l, r + 1) nd[i].ty = i > m;
	p = l;
	rep(i, m+1, r+1) {
		while (p <= m && nd[p].x < nd[i].x) {
			if (nd[p].i == 0) fw.upd(nd[p].y - 1, 1);
			p++;
		}
		if (nd[i].i) {
			t = abs(nd[i].i);
			res = fw.qry(nd[i].y);
			if(nd[i].i > 0) ans[t] += res;
			else ans[t] -= res;
		}
	}
	if (l == 1 && r == top) return;	
	rep(i, l, p) if(nd[i].i == 0) fw.init(nd[i].y - 1);
	p = l; q = m + 1; k = l;
	while(p <= m && q <= r) {
		if(nd[p].x < nd[q].x) tt[k++] = nd[p++];
		else tt[k++] = nd[q++];
	}
	while(p <= m) tt[k++] = nd[p++];
	while(q <= r) tt[k++] = nd[q++];
	rep(i, l, r + 1) nd[i] = tt[i];
	//sort(nd + l, nd + r + 1, cmp);
}

void solve() {
	rep(i, 1, n + 1) cin >> w[i];
	top = 0;
	rep(i, 1, m + 1) {
		int l, r; cin >> l >> r;
		nd[++top] = Node(r    , l, r, i);
		nd[++top] = Node(l - 1, l, r, -i);
	}
	rep(i, 1, n + 1) nd[++top] = Node(i, 0, 0, 0);
	// a[i]
	rep(i, 1, n + 1) for(auto j : pri[w[i]]) ans[j] = 0;
	rep(i, 1, n + 1) {
		int &a = nd[i + 2 * m].x = 0;
		for(auto j : pri[w[i]]) a = max(a, ans[j]);
		for(auto j : pri[w[i]]) ans[j] = i;
	}
	// b[i]
	rep(i, 1, n + 1) for(auto j : pri[w[i]]) ans[j] = n + 1;
	per(i, 1, n + 1) {
		int &b = nd[i + 2 * m].y = n + 1;
		for(auto j : pri[w[i]]) b = min(b, ans[j]);
		for(auto j : pri[w[i]]) ans[j] = i;
	}
	// nd
	fw.init();
	fill_n(ans + 1, m, 0);
	sort(nd + 1, nd + 1 + top);
	solve(1, top);
	rep(i, 1, m + 1) cout << ans[i] << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	init();
	
	/*db x = sizeof(ans) * 8;//sizeof(pri);
	x += sizeof(tt) * 2;
	x += sizeof(ans) * 2;
	de(x / 1024);
	*/
	while(cin >> n >> m) {
		if(!n && !m) break;
		solve();
	}
	return 0;
}
