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

const int N = 202020;

string s, t;
struct Node {
	int x, y, val, ty;
	Node(int x, int y, int val, int ty) : x(x), y(y), val(val), ty(ty) {}
	bool operator < (const Node &c) const {
		if(x != c.x) return x < c.x;
		return ty > c.ty;
	}
};
vector<Node> nd;

struct SAM {
	static const int N = ::N << 2, M = 26;
	int par[N], l[N], ne[N][M], rt, last, L;
	int cnt[N], cur[N], mis[N], mit[N];
	void add(int c) {
		int p = last;
		if(ne[p][c] && l[ne[p][c]] == l[p] + 1) {
			last = ne[p][c]; return ;
		}
		int np = ++L;
		fill(ne[np], ne[np] + M, 0);
		l[np] = l[p] + 1;
		last = np;
		while(p && !ne[p][c]) ne[p][c] = np, p = par[p];
		if(!p) par[np] = rt;
		else {
			int q = ne[p][c];
			if(l[q] == l[p] + 1) par[np] = q;
			else {
				int nq = ++L;
				l[nq] = l[p] + 1;
				copy(ne[q], ne[q] + M, ne[nq]);
				par[nq] = par[q];
				par[q] = par[np] = nq;
				while(p && ne[p][c] == q) ne[p][c] = nq, p = par[p];
			}
		}
	}
	void ini() {
		rt = last = L = 1;
		fill(ne[rt], ne[rt] + M, 0);
		l[0] = -1;
	}
	void build(int o) {
		rep(i, 0, L + 1) cnt[i] = 0, mis[i] = mit[i] = N;
		rep(i, 1, L + 1) ++cnt[l[i]];
		rep(i, 1, L + 1) cnt[i] += cnt[i - 1];
		rep(i, 1, L + 1) cur[cnt[l[i]]--] = i;
		int p = rt;
		rep(i, 0, sz(s)) {
			p = ne[p][s[i] - 'a'];
			mis[p] = min(mis[p], i + 1);
		}
		p = rt;
		rep(i, 0, sz(t)) {
			p = ne[p][t[i] - 'a'];
			mit[p] = min(mit[p], i + 1);
		}
		per(i, 1, L + 1) {
			int v = cur[i], u = par[v];
			if(l[v] && mis[v] != N && mit[v] != N) {
				if(o == 0) nd.pb(Node(mis[v], mit[v], l[v], 0));
				else nd.pb(Node(sz(s) - mis[v] + 1, sz(t) - mit[v] + 1, l[v], 1));
			}
			mis[u] = min(mis[u], mis[v]);
			mit[u] = min(mit[u], mit[v]);
		}
	}
}sam;

int n;

struct FW {
#define lb(x) (x & -x)
	int y[N], len[N];
	void upd(int p, int c) {
		int ty = p;
		for( ; p <= n; p += lb(p)) {
			if(c > len[p]) {
				y[p] = ty;
				len[p] = c;
			}
		}
	}
	pii qry(int p) {
		pii ans = mp(0, 0);
		for( ; p; p ^= lb(p)) {
			if(ans.se < len[p]) ans = mp(y[p], len[p]);
		}
		return ans;
	}
}fw;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> s >> t;
	n = max(sz(s), sz(t));

	sam.ini();
	for(auto u : s) sam.add(u - 'a');
	sam.last = 1;
	for(auto u : t) sam.add(u - 'a');
	sam.build(0);

	reverse(all(s));
	reverse(all(t));
	sam.ini();
	for(auto u : s) sam.add(u - 'a');
	sam.last = 1;
	for(auto u : t) sam.add(u - 'a');
	sam.build(1);

	reverse(all(s));
	reverse(all(t));
	sort(all(nd));
	int ans = 0, l1 = 0, r1 = -1, l2 = 0, r2 = -1;
	for(auto u : nd) {
		if(u.ty == 0) {
			fw.upd(u.y, u.val);
		} else {
			auto res = fw.qry(u.y - 1);
			if(res.se + u.val > ans) {
				ans = res.se + u.val;
				l1 = res.fi - res.se + 1;
				r1 = res.fi;
				l2 = u.y;
				r2 = u.y + u.val - 1;
			}
		}
	}
	rep(i, l1, r1 + 1) cout << t[i - 1]; cout << endl;
	rep(i, l2, r2 + 1) cout << t[i - 1]; cout << endl;
	return 0;
}
