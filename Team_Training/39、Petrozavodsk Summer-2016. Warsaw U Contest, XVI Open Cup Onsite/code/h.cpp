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
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 505050;

int n, m, a[N];
ll pre[N];

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	ll sum[N], a[N], b[N], ma[N];
	// a add b fugai
	void gao(int rt, int l, int r, ll t1, ll t2) {
		//dd(rt), dd(l), dd(r), dd(t1), de(t2);
		if(~t2) {
			sum[rt] = (r - l + 1) * t2;
			a[rt] = 0;
			b[rt] = t2;
			ma[rt] = t2;
		}
		if(t1) {
			sum[rt] += t1 * (pre[r] - pre[l - 1]);
			a[rt] += t1;
			ma[rt] += t1 * ::a[r];
		}
	}
	void down(int rt, int l, int r, int mid) {
		gao(ls, l, mid, a[rt], b[rt]);
		gao(rs, mid + 1, r, a[rt], b[rt]);
		a[rt] = 0; b[rt] = -1;
	}
	void init() {
		memset(b, -1, sizeof(b));
	}
	void add(ll c) {
		gao(1, 1, n, c, -1);
	}
	void up(int rt) {
		sum[rt] = sum[ls] + sum[rs];
		ma[rt] = max(ma[ls], ma[rs]);
	}
	void upd(int L, int R, ll c, int l = 1, int r = n, int rt = 1) {
		if(L > R) return ;
		if(L <= l && r <= R) {
			gao(rt, l, r, 0, c);
			return ;
		}
		int mid = l + r >> 1;
		down(rt, l, r, mid);
		if(L <= mid) upd(L, R, c, l, mid, ls);
		if(R > mid) upd(L, R, c, mid + 1, r, rs);
		up(rt);
	}
	int qry(ll c, int l = 1, int r = n, int rt = 1) {
		if(ma[rt] <= c) return n + 1;
		if(l == r) return l;
		int mid = l + r >> 1;
		down(rt, l, r, mid);
		if(ma[ls] > c) return qry(c, l, mid, ls);
		return qry(c, mid + 1, r, rs);
	}
}seg;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, n + 1) cin >> a[i];
	sort(a + 1, a + 1 + n);
	rep(i, 1, n + 1) pre[i] = pre[i - 1] + a[i];
	ll pre = 0;
	seg.init();
	rep(i, 1, m + 1) {
		ll d, b; cin >> d >> b;
		seg.add(d - pre);
		int p = seg.qry(b);
		ll ans = seg.sum[1];
		if(p <= n) seg.upd(p, n, b);
		cout << ans - seg.sum[1] << endl;
		pre = d;
	}
	return 0;
}
