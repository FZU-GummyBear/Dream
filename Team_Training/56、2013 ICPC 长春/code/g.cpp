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
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define ls rt << 1
#define rs ls | 1
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 888;

int n, a[N][N];

struct seg {
	int ma[N << 2], mi[N << 2];
	void up(int rt) {
		ma[rt] = max(ma[ls], ma[rs]);
		mi[rt] = min(mi[ls], mi[rs]);
	}
	void upd(int p, int c, int l = 1, int r = n, int rt = 1) {
		if(l == r) return ma[rt] = mi[rt] = c, void();
		int mid = l + r >> 1;
		if(p <= mid) upd(p, c, l, mid, ls);
		else upd(p, c, mid + 1, r, rs);
		up(rt);
	}
	int qma(int L, int R, int l = 1, int r = n, int rt = 1) {
		if(L <= l && r <= R) return ma[rt];
		int mid = l + r >> 1, ans = -1;
		if(L <= mid) ans = max(ans, qma(L, R, l, mid, ls));
		if(R > mid) ans = max(ans, qma(L, R, mid + 1, r, rs));
		return ans;
	}
	int qmi(int L, int R, int l = 1, int r = n, int rt = 1) {
		if(L <= l && r <= R) return mi[rt];
		int mid = l + r >> 1, ans = 1e9 + 1;
		if(L <= mid) ans = min(ans, qmi(L, R, l, mid, ls));
		if(R > mid) ans = min(ans, qmi(L, R, mid + 1, r, rs));
		return ans;
	}
}tr[N];
struct Seg {
	seg ma[N << 2], mi[N << 2];
	void upd(int x, int y, int c, int l = 1, int r = n, int rt = 1) {
		ma[rt].upd(y, tr[y].qma(l, r));
		mi[rt].upd(y, tr[y].qmi(l, r));
		if(l == r) return ;
		int mid = l + r >> 1;
		if(x <= mid) upd(x, y, c, l, mid, ls);
		else upd(x, y, c, mid + 1, r, rs);
	}
	pii qry(int lx, int rx, int ly, int ry, int l = 1, int r = n, int rt = 1) {
		if(lx <= l && r <= rx) return mp(ma[rt].qma(ly, ry), mi[rt].qmi(ly, ry));
		int mid = l + r >> 1;
		int Ma = -1, Mi = 1e9 + 1;
		if(lx <= mid) {
			pii t = qry(lx, rx, ly, ry, l, mid, ls);
			Ma = max(Ma, t.fi);
			Mi = min(Mi, t.se);
		}
		if(rx > mid) {
			pii t = qry(lx, rx, ly, ry, mid + 1, r, rs);
			Ma = max(Ma, t.fi);
			Mi = min(Mi, t.se);
		}
		return mp(Ma, Mi);
	}
}T;

void solve() {
	cin >> n;
	rep(i, 1, n + 1) rep(j, 1, n + 1) {
		cin >> a[i][j];
		tr[j].upd(i, a[i][j]);
	}
	rep(i, 1, n + 1) rep(j, 1, n + 1) T.upd(i, j, a[i][j]);
	int m; cin >> m;
	while(m--) {
		int x, y, z; cin >> x >> y >> z; z /= 2; 
		int lx = max(1, x - z);
		int rx = min(n, x + z);
		int ly = max(1, y - z);
		int ry = min(n, y + z);
		auto t = T.qry(lx, rx, ly, ry);
		int c = t.fi + t.se >> 1;
	//	dd(t.fi), de(t.se);
		cout << c << endl;
		tr[y].upd(x, c);
		T.upd(x, y, c);
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	rep(i, 1, T + 1) {
		cout << "Case #" << i << ":" << endl;
		solve();
	}
	return 0;
}
