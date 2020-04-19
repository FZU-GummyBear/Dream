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
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 101010;

int n, m;

struct Seg { 
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	ll sum[N], la[N];
	void gao(int l, int r, int rt, ll c) {
		la[rt] += c;
		sum[rt] += c;
	}
	void down(int l, int r, int mid, int rt) {
		if(la[rt]) {
			gao(l, mid, ls, la[rt]);
			gao(mid + 1, r, rs, la[rt]);
			la[rt] = 0;
		}
	}
	void up(int rt) {
		sum[rt] = max(sum[ls], sum[rs]);
	}
	void upd(int L, int R, int l = 1, int r = n, int rt = 1) {
		if(L <= l && r <= R) {
			gao(l, r, rt, 1);
			return ;
		}
		int mid = l + r >> 1;
		down(l, r, mid, rt);
		if(L <= mid) upd(L, R, l, mid, ls);
		if(R > mid) upd(L, R, mid + 1, r, rs);
		up(rt);
	}
	ll qry(int L, int R, int l = 1, int r = n, int rt = 1) {
		if(L <= l && r <= R) return sum[rt];
		int mid = l + r >> 1; ll ans = 0;
		down(l, r, mid, rt);
		if(L <= mid) ans = max(ans, qry(L, R, l, mid, ls));
		if(R > mid) ans = max(ans, qry(L, R, mid + 1, r, rs));
		up(rt);
		return ans;
	}
}seg[4];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	while(m--) {
		string s; int l, r, c;
		cin >> s >> l >> r;
		if(s[1] == 'U') {
			cin >> c;
			while(c % 2 == 0) seg[0].upd(l, r), c /= 2;
			while(c % 3 == 0) seg[1].upd(l, r), c /= 3;
			while(c % 5 == 0) seg[2].upd(l, r), c /= 5;
			while(c % 7 == 0) seg[3].upd(l, r), c /= 7;
		} else {
			ll ans = 0;
			rep(i, 0, 4) ans = max(ans, seg[i].qry(l, r));
			cout << "ANSWER " << ans << endl;
		}
	}
	return 0;
}
