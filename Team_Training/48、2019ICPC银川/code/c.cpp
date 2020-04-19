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

const int N = 1e6 + 7;

int n, k, a[N], l, r, mid, p, t1, t2, f[N], now;
/*namespace ST {
	static const int N = ::N, M = 21;
	int ma[M][N], mi[M][N], n, Log[N];
	inline void init() {
		n = 0;
		Log[0] = -1, Log[1] = 0;
		rep(i, 2, N) Log[i] = Log[i >> 1] + 1;
	}
	inline void ins(int x) {
		ma[0][++n] = x;
		mi[0][n] = x;
		rep(i, 1, M) if((1 << i) <= n) {
			ma[i][n] = max(ma[i - 1][n], ma[i - 1][n - (1 << (i - 1))]);
			mi[i][n] = min(mi[i - 1][n], mi[i - 1][n - (1 << (i - 1))]);
		}
	}
	inline int qry(int l, int r) {
		int t = Log[r - l + 1];
		return max(ma[t][r], ma[t][l + (1 << t) - 1]) - min(mi[t][r], mi[t][l + (1 << t) - 1]);
	}
}*/

int r1, r2, a1[N];
pii q1[N], q2[N];

void upd(pii &x, pii & y) {
	x.fi = max(x.fi, y.fi);
	x.se = min(x.se, y.se);
}


inline void push(int x) {
	q1[++r1] = mp(x, x);
	upd(q1[r1], q1[r1-1]);
	a1[r1] = x;
}

inline void pop() {
	if (r2 == 0) {
		per(i, 1, r1+1) q2[++r2] = mp(a1[i], a1[i]), upd(q2[r2], q2[r2-1]);
		r1 = 0;
	}
	r2--;
}

inline int qry(int l) {
	while (now < l) pop(), now++;
	if (r1 && r2) {
		return max(q1[r1].fi, q2[r2].fi) - min(q1[r1].se, q2[r2].se);
	}else if (r1) return q1[r1].fi - q1[r1].se;
	else return q2[r2].fi - q2[r2].se;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> k; 
	p = k; now = 1; int t = 0;
	int ma = -pw(30), mi = pw(30);
	q1[0] = q2[0] = mp(ma, mi);
	rep(i, 1, n+1) {
		cin >> a[i]; 
		a[i] ^= f[i-1];
		push(a[i]); 
		ma = max(ma, a[i]), mi = min(mi, a[i]);
		if (i == k + 1) t = qry(p + 1);
		if (i < k) f[i] = 0;
		else if (i < 2 * k) f[i] = ma - mi;
		else {
			t = qry(p + 1);
			f[i] = ma - mi;
			r = i - k; 
			while (p + 1 <= r && f[p + 1] <= qry(p + 2)) t = qry(p + 2), p++;
			//de(p), dd(f[p]), dd(r1), dd(r2), dd(q1[r1].fi), dd(q1[r1].se),dd(q2[r2].fi), dd(q2[r2].se),de(t);
			f[i] = min(max(f[p], t), f[i]);	
		}
		cout << f[i] << endl;
	}
	return 0;
}
