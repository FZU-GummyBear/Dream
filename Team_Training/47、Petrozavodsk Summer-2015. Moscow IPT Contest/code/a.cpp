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

const int N = 50505;

int n, m, pre[N];
pii a[N];
vi X, Y;

void gao(vi &V) {
	sort(all(V));
	V.erase(unique(all(V)), V.end());
}
int Find(vi &V, int x) {
	return lower_bound(all(V), x) - V.begin() + 1;
}

int L, R, _ans;
int p, c;

struct Seg {
	static const int N = 6e7;
	int cntn, ls[N], rs[N], cnt[N];
	void upd(int &now, int pre, int l = 1, int r = n) {
		now = ++cntn;
		ls[now] = ls[pre];
		rs[now] = rs[pre];
		cnt[now] = cnt[pre] + c;
		if(l == r) return ;
		int mid = l + r >> 1;
		if(p <= mid) upd(ls[now], ls[pre], l, mid);
		else upd(rs[now], rs[pre], mid + 1, r);
	}
	void qry(int rt, int l, int r) {
		if(!rt) return ;
		if(L <= l && r <= R) return _ans += cnt[rt], void();
		int mid = l + r >> 1;
		if(L <= mid) qry(ls[rt], l, mid);
		if(R > mid) qry(rs[rt], mid + 1, r);
	}
}seg;

struct FW {
#define lb(x) ((x) & -(x))
	unordered_map<int, int> rt[N];
	vi vec[N];
	void add(pii p, int val, int _) {
		int x = p.fi, y = p.se;
		for(int k = y; k <= n; k += lb(k)) {
			int prt = sz(vec[k]) ? rt[vec[k].back()][k] : 0;
			::p = val, ::c = _;
			seg.upd(rt[x][k], prt);
			if(!sz(vec[k]) || vec[k].back() != x) vec[k].pb(x);
		}
	}
	int qry(int tim, int p, int c) {
		_ans = 0;
		for(int k = p; k; k ^= lb(k)) if(sz(vec[k])) {
			int prt = upper_bound(all(vec[k]), tim) - vec[k].begin() - 1;
			if(prt >= 0) {
				prt = vec[k][prt];
				L = c, R = n;
				seg.qry(rt[prt][k], 1, n);
			}
		}
		return _ans;
	}
	int qry(int tim, int L, int R, int c) {
		return qry(tim, R, c) - qry(tim, L - 1, c);
	}
}fw[2];

int main() {
//	de(sizeof(seg) / 1024. / 1024.);
	// read
	scanf("%d", &n);
	rep(i, 1, n + 1) scanf("%d%d", &a[i].fi, &a[i].se), X.pb(a[i].fi), Y.pb(a[i].se);
	//
	gao(X); gao(Y);
	rep(i, 1, n + 1) {
		a[i].fi = Find(X, a[i].fi);
		a[i].se = Find(Y, a[i].se);
	}
	// init
	sort(a + 1, a + 1 + n);
	fill_n(pre + 1, n, 0);
	rep(i, 1, n + 1) {
		if(pre[a[i].se]) fw[0].add(a[i], pre[a[i].se], -1);
		fw[0].add(a[i], a[i].fi, 1);
		pre[a[i].se] = a[i].fi;
	}

	rep(i, 1, n + 1) swap(a[i].fi, a[i].se);
	sort(a + 1, a + 1 + n);
	fill_n(pre + 1, n, 0);
	rep(i, 1, n + 1) {
		if(pre[a[i].se]) fw[1].add(a[i], pre[a[i].se], -1);
		fw[1].add(a[i], a[i].fi, 1);
		pre[a[i].se] = a[i].fi;
	}
	// solve
	scanf("%d", &m);
	while(m--) {
		int lx, ly, rx, ry;
		scanf("%d%d%d%d", &lx, &ly, &rx, &ry);
		lx = Find(X, lx);
		ly = Find(Y, ly);
		rx = upper_bound(all(X), rx) - X.begin();
		ry = upper_bound(all(Y), ry) - Y.begin();
		if(lx > rx || ly > ry) {
			printf("0 0\n");
			fflush(stdout);
			continue;
		}
		int ansy = fw[0].qry(rx, ly, ry, lx);
		int ansx = fw[1].qry(ry, lx, rx, ly);
		printf("%d %d\n", ansx, ansy);
		fflush(stdout);
	}
	return 0;
}
