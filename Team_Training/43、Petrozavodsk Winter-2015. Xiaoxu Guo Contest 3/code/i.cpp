#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(c) cout << #c << " = " << c << endl
#define dd(c) cout << #c << " = " << c << " "
#define endl '\n'
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 202020;

int n, q;
string s[N], t[N];
int st[N], ed[N], ans[N];

int root[N];

struct Seg {
	static const int N = ::N * 20;
	int ls[N], rs[N], L, sum[N];
	void up(int rt) {
		sum[rt] = sum[ls[rt]] + sum[rs[rt]];
	}
	void upd(int &rt, int p, int l = 1, int r = n) {
		if(!rt) rt = ++L;
		if(l == r) {
			sum[rt] = 1;
			return ;
		}
		int mid = l + r >> 1;
		if(p <= mid) upd(ls[rt], p, l, mid);
		else upd(rs[rt], p, mid + 1, r);
		up(rt);
	}
	int qry(int rt, int L, int R, int l = 1, int r = n) {
		if(!rt) return 0;
		if(L <= l && r <= R) return sum[rt];
		int mid = l + r >> 1, ans = 0;
		if(L <= mid) ans += qry(ls[rt], L, R, l, mid);
		if(R > mid) ans += qry(rs[rt], L, R, mid + 1, r);
		return ans;
	}
	int merge(int x, int y, int l = 1, int r = n) {
		if(x && y) {
			if(l == r) {
				sum[x] |= sum[y];
				return x;
			} else {
				int mid = l + r >> 1;
				ls[x] = merge(ls[x], ls[y], l, mid);
				rs[x] = merge(rs[x], rs[y], mid + 1, r);
				up(x);
				return x;
			}
		} else return x + y;
	}
}seg;

struct SAM {
	static const int N = ::N << 1, M = 2;
	vi vec[N], Q[N];
	int cnt[N], cur[N];
	int par[N], l[N], ne[N][M];
	int rt, last, L;
	void solve() {
		per(i, 2, L + 1) {
			int u = cur[i];
			for(auto c : vec[u]) {
				seg.upd(root[u], c);
			}
			for(auto j : Q[u]) {
				ans[j] = seg.qry(root[u], st[j], ed[j]);
			}
			root[par[u]] = seg.merge(root[par[u]], root[u]);
		}
	}
	void add(int c) {
		int p = last;
		if(ne[p][c] && l[ne[p][c]] == l[p] + 1) {
			last = ne[p][c];
			return ;
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
	void build() {
		rep(i, 1, n + 1) {
			int p = rt;
			for(auto j : s[i]) {
				p = ne[p][j - 'a'];
				vec[p].pb(i);
			}
		}
		rep(i, 1, L + 1) ++cnt[l[i]];
		rep(i, 1, L + 1) cnt[i] += cnt[i - 1];
		rep(i, 1, L + 1) cur[cnt[l[i]]--] = i;
	}
	void go(int i) {
		int p = rt;
		for(auto j : t[i]) {
			p = ne[p][j - 'a'];
			if(!p) return ;
		}
		Q[p].pb(i);
	}
}sam;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	sam.ini();
	cin >> n >> q;
	rep(i, 1, n + 1) {
		cin >> s[i];
		sam.last = 1;
		for(auto j : s[i]) sam.add(j - 'a');
	}
	sam.build();
	rep(i, 1, q + 1) {
		cin >> st[i] >> ed[i] >> t[i];
		sam.go(i);
	}
	sam.solve();
	rep(i, 1, q + 1) cout << ans[i] << endl;
	return 0;
}
