#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) (a).begin(), (a).end()
#define pw(x) (1ll<<(x))
#define lb(x) ((x) & -(x))
#define endl "\n"
#define FI(x) freopen(#x".in","r",stdin)
#define FO(x) freopen(#x".out","w",stdout)
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
//typedef uniform_int_distribution<ll> RR;
//mt19937 gen(998244353);
//ll rnd(ll l, ll r) { RR dis(l, r); return dis(gen); }
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----
 
const int N = 1e6 + 7;
 
int n, k, a[N], l, r, mid, p, t1, t2, f[N], now, g[N];
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
 
void upd(pii &x, pii  y) {
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
 
pii qry(int l) {
	while (now < l) pop(), now++;
	if (r1 && r2) {
		return mp(max(q1[r1].fi, q2[r2].fi), min(q1[r1].se, q2[r2].se));
	}else if (r1) return q1[r1];
	else return q2[r2];
}
int cal(pii a) {
    return a.fi - a.se;
}
 
int get(int l, int r) {
	int ma = a[l], mi = a[l];
	rep(i, l+1, r+1) ma = max(ma, a[i]), mi = min(mi, a[i]);
	return ma - mi;
}
 
int main() {
	FI(a);
	srand(time(0));
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> k; 
	p = k; now = 1; pii t;
	int ma = -pw(30), mi = pw(30);
	q1[0] = q2[0] = t = mp(ma, mi);int pre = 0, pp = 0;
	rep(i, 1, n+1) {
		//cin >> a[i]; 
		a[i] = rand() % 100100; //de(a[i]);
		//a[i] ^= f[i-1];
		push(a[i]); 
		ma = max(ma, a[i]), mi = min(mi, a[i]);
		if (i < k) f[i] = 0;
		else if (i < 2 * k) g[i] = f[i] = ma - mi;
		else {
			g[i] = ma - mi;
			rep(j, k, i - k+1) {
				if (g[i] >= max(g[j], get(j + 1, i))) pp = j, de(pp);
				g[i] = min(g[i], max(g[j], get(j + 1, i))); 
			}
			if (now > p + 1) upd(t, mp(a[i], a[i]));else t = qry(p + 1);
			f[i] = ma - mi;
			r = i - k; 
			while (p + 1 <= r && f[p + 1] <= cal(qry(p + 2))) t = qry(p + 2), p++;
			//de(p), dd(f[p]), dd(r1), dd(r2), dd(q1[r1].fi), dd(q1[r1].se),dd(q2[r2].fi), dd(q2[r2].se),de(t);
			f[i] = min(max(f[p], t.fi - t.se), f[i]);
			if (p + 1 <= r) f[i] = min(max(f[p + 1], cal(qry(p + 2))), f[i]);	
			//de(p); if (i == 6) dd(f[p + 1]), dd(qry(p + 2).fi), de(qry(p + 2). se); 
			dd(f[i]), de(g[i]);
			assert(pp >= pre);
			pre = pp;
			//assert(f[i] == g[i]);
			/*if (f[i] != g[i]) {
				dd(i);
				rep(j, 1, i+1) de(a[j]);
				return 0;
			}*/
		}
		cout << f[i] << endl;
	}
	return 0;
}
