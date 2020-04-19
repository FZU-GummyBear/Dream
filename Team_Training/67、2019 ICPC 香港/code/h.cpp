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
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1e6 + 4;

struct Node {
	int o, l, r, h, t, x, ans;
	Node() {}
	Node(int o, int l, int r, int h, int t) : o(o), l(l), r(r), h(h), t(t) {}
	Node(int o, int x, int h, int t) : o(o), x(x), h(h), t(t) {}
	bool operator < (const Node &c) const { 
		if(h != c.h) return h < c.h; 
		return o < c.o;
	}
};

int n, m, ans[N];
Node nd[N], tmp[N];

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	int ma[N];
	inline void init(int l = 1, int r = n, int rt = 1) {
		ma[rt] = -1;
		if(l == r) return ;
		int mid = l + r >> 1;
		if(ma[ls] != -1) init(l, mid, ls);
		if(ma[rs] != -1) init(mid + 1, r, rs);
	}
	inline void build() {
		memset(ma, -1, sizeof(ma));
	}
	inline void upd(int p, int c, int l = 1, int r = n, int rt = 1) {
		ma[rt] = max(ma[rt], c);
		if(l == r) return ;
		int mid = l + r >> 1;
		if(p <= mid) upd(p, c, l, mid, ls);
		else upd(p, c, mid + 1, r, rs);
	}
	inline void qry(int L, int R, int &ans, int l = 1, int r = n, int rt = 1) {
		if(L <= l && r <= R) return ans = max(ans, ma[rt]), void(); 
		int mid = l + r >> 1;
		if(ma[ls] > ma[rs]) {
			if(L <= mid && ans < ma[ls]) qry(L, R, ans, l, mid, ls);
			if(R > mid && ans < ma[rs]) qry(L, R, ans, mid + 1, r, rs);
		} else {
			if(R > mid && ans < ma[rs]) qry(L, R, ans, mid + 1, r, rs);
			if(L <= mid && ans < ma[ls]) qry(L, R, ans, l, mid, ls);
		}
	}
}seg;
bool cmp(const Node &a, const Node &b) { return a.t < b.t; }
void cdq(int l, int r) {
	if(l >= r) return ;
	if(l + 20 >= r) {
		rep(i, l, r + 1) if(nd[i].o == 1) {
			rep(j, l, i) if(nd[j].o == 0 && nd[j].t < nd[i].t && nd[i].l <= nd[j].x && nd[j].x <= nd[i].r) {
				nd[i].ans = max(nd[i].ans, nd[j].h);
			}
		}
		sort(nd + l, nd + r + 1, cmp);
		return ;
	}
	int m = l + r >> 1;
	cdq(l, m); cdq(m + 1, r);
	int pos = l;
	rep(i, m + 1, r + 1) {
		while(pos <= m && nd[pos].t < nd[i].t) {
			if(nd[pos].o == 0) seg.upd(nd[pos].x, nd[pos].h);
			pos++;
		}
		if(nd[i].o == 1) seg.qry(nd[i].l, nd[i].r, nd[i].ans);
	}
	seg.init();
	if(l == 1 && r == m) return ;
	int p = l, q = m + 1, k = l;
	while(p <= m && q <= r) {
		if(nd[p].t < nd[q].t) {
			tmp[k++] = nd[p++];
		} else {
			tmp[k++] = nd[q++];
		}
	}
	while(p <= m) tmp[k++] = nd[p++];
	while(q <= r) tmp[k++] = nd[q++];
	rep(i, l, r + 1) nd[i] = tmp[i];
}

void solve() {
	scanf("%d%d", &n, &m);
	rep(i, 1, m + 1) {
		int o; scanf("%d", &o);
		if(o == 0) {
			int x, y; scanf("%d%d", &x, &y);
			nd[i] = Node(o, x, y, i);
			ans[i] = -2;
		} else {
			int l, r, y; scanf("%d%d%d", &l, &r, &y);
			nd[i] = Node(o, l, r, y, i);
			ans[i] = -1;
		}
	}
	sort(nd + 1, nd + 1 + m);
	rep(i, 1, m + 1) nd[i].ans = -1;
	cdq(1, m);
	rep(i, 1, m + 1) if(~nd[i].ans) ans[nd[i].t] = nd[i].h - nd[i].ans;

	rep(i, 1, m + 1) nd[i].h = 1e9 + 1 - nd[i].h;
	sort(nd + 1, nd + 1 + m);
	rep(i, 1, m + 1) nd[i].ans = -1;
	cdq(1, m);
	rep(i, 1, m + 1) if(~nd[i].ans) {
		int k = nd[i].t;
		if(ans[k] == -1 || ans[k] > nd[i].h - nd[i].ans) ans[k] = nd[i].h - nd[i].ans;
	}
	rep(i, 1, m + 1) if(ans[i] != -2) cout << ans[i] << endl; 
}

int main() {
	seg.build();
	int T; scanf("%d", &T);
	while(T--) solve();
	return 0;
}
