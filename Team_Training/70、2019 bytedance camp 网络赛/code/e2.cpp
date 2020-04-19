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
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 303030, P = 998244353;

int upd(int a, int b) {
	if((a += b) >= P) a -= P;
	return (a < 0) ? a + P : a;
}

int n, a[N], pre[N], dp[N], f[N], sum[N];
pii s[N];

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	int la[N], len[N];
	void up(int rt, int l, int r) {
		if(la[rt]) {
			len[rt] = ::upd(sum[r],  -sum[l - 1]);
		} else {
			len[rt] = (l == r) ? 0 : ::upd(len[ls], len[rs]);
		}
	}
	void upd(int L, int R, int c, int l = 1, int r = n, int rt = 1) {
		if(L <= l && r <= R) {
			la[rt] += c;
			up(rt, l, r);
			return ;
		}
		int mid = l + r >> 1;
		if(L <= mid) upd(L, R, c, l, mid, ls);
		if(R > mid) upd(L, R, c, mid + 1, r, rs);
		up(rt, l, r);
	}
}seg;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n + 1) cin >> a[i], s[i] = mp(-1, -1);
	dp[0] = f[1] = sum[1] = 1;
	rep(i, 1, n + 1) {
		int x = a[i];
		if(s[x].fi != -1) seg.upd(s[x].fi, s[x].se, -1);
		s[x] = mp(pre[x] + 1, i);
		seg.upd(s[x].fi, s[x].se, 1);
		pre[x] = i;
		dp[i] = seg.len[1];
		f[i + 1] = dp[i];
		sum[i + 1] = upd(f[i + 1], sum[i]);
	}
	cout << dp[n] << endl;
	return 0;
}
