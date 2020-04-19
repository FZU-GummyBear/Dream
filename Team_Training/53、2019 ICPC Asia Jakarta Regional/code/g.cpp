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
#define pw(x) (1ll << (x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 101010;

int n, m, q, a[N];
vi vec[N];
ll S[N], Y[N], x[N];

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	ll mi[N], la[N];
	void up(int rt) { mi[rt] = min(mi[ls], mi[rs]); }
	void build(int l = 1, int r = m, int rt = 1) {
		if(l == r) return mi[rt] = Y[l] - S[l], void();
		int mid = l + r >> 1;
		build(l, mid, ls), build(mid + 1, r, rs);
		up(rt);
	}
	void gao(int rt, ll c) {
		mi[rt] += c;
		la[rt] += c;
	}
	void down(int rt) {
		if(la[rt]) {
			gao(ls, la[rt]);
			gao(rs, la[rt]);
			la[rt] = 0;
		}
	}
	void upd(int L, int R, ll c, int l = 1, int r = m, int rt = 1) {
		if(L > R) return ;
		if(L <= l && r <= R) return gao(rt, c), void();
		int mid = l + r >> 1;
		down(rt);
		if(L <= mid) upd(L, R, c, l, mid, ls);
		if(R > mid) upd(L, R, c, mid + 1, r, rs);
		up(rt);
	}
}seg;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m >> q;
	rep(i, 1, n + 1) cin >> a[i];
	rep(i, 1, m + 1) {
		int k; cin >> k; vec[i].pb(0);
		while(k--) { int x; cin >> x; vec[i].pb(x); }
	}
	rep(i, 2, n + 1) x[0] += (a[i] < a[1]);
	x[0]++; Y[1] = x[0];
	rep(i, 1, m) {
		rep(j, 1, sz(vec[i])) x[i] += (vec[i][j] < a[1]);
		Y[i + 1] = Y[i] + x[i];
	}
	rep(i, 1, m + 1) S[i] = S[i - 1] + sz(vec[i]) - 1;
	seg.build();
	while(q--) {
		int x, y, z; cin >> x >> y >> z;
		int c = -(vec[x][y] < a[1]) + (z < a[1]);
		vec[x][y] = z;
		seg.upd(x + 1, m, c);
		cout << (seg.mi[1] > 0) << endl;
	}
	return 0;
}
