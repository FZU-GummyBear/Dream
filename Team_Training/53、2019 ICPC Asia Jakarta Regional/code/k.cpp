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

const int N = 101010, P = 1e9 + 7;

int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a;
}
int mul(int a, int b) {
	return 1ll * a * b % P;
}

int n, m;
string s;

struct Node {
	int k1, k2, k3, k4;
	Node() {}
	Node(int k1, int k2, int k3, int k4) : k1(k1), k2(k2), k3(k3), k4(k4) {}
	void ini(int o) {
		k1 = k2 = k3 = k4 = 1;
		(o == 0) ? k3 = 0 : k2 = 0;
	}
	void ini() { k1 = k4 = 1; k2 = k3 = 0; }
	void rev() { swap(k1, k4); swap(k2, k3); }
	Node operator + (const Node &c) const {
		Node r;
		r.k1 = add(mul(c.k1, k1), mul(c.k2, k3));
		r.k2 = add(mul(c.k1, k2), mul(c.k2, k4));
		r.k3 = add(mul(c.k3, k1), mul(c.k4, k3));
		r.k4 = add(mul(c.k3, k2), mul(c.k4, k4));
		return r;
	}
}ans;

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	bool la[N]; Node nd[N];
	void up(int rt) {
		nd[rt] = nd[ls] + nd[rs];
	}
	void build(int l = 1, int r = n, int rt = 1) {
		if(l == r) return nd[rt].ini(s[l - 1] == 'B'), void();
		int mid = l + r >> 1;
		build(l, mid, ls);
		build(mid + 1, r, rs);
		up(rt);
	}
	void gao(int rt) {
		la[rt] ^= 1;
		nd[rt].rev();
	}
	void down(int rt) {
		if(la[rt]) {
			gao(ls); gao(rs);
			la[rt] = 0;
		}
	}
	void upd(int L, int R, int l = 1, int r = n, int rt = 1) {
		if(L <= l && r <= R) return gao(rt), void();
		int mid = l + r >> 1;
		down(rt);
		if(L <= mid) upd(L, R, l, mid, ls);
		if(R > mid) upd(L, R, mid + 1, r, rs);
		up(rt);
	}
	void qry(int L, int R, int l = 1, int r = n, int rt = 1) {
		if(rt == 1) ans.ini();
		if(L <= l && r <= R) return ans = ans + nd[rt], void();
		int mid = l + r >> 1;
		down(rt);
		if(L <= mid) qry(L, R, l, mid, ls);
		if(R > mid) qry(L, R, mid + 1, r, rs);
		up(rt);
	}
}seg;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m >> s;
	seg.build();
	while(m--) {
		int o, l, r; cin >> o >> l >> r;
		if(o == 1) {
			seg.upd(l, r);
		} else {
			seg.qry(l, r);
			int a, b; cin >> a >> b;
			int A = add(mul(ans.k1, a), mul(ans.k2, b));
			int B = add(mul(ans.k3, a), mul(ans.k4, b));
			cout << A << " " << B << endl;
		}
	}
	return 0;
}
