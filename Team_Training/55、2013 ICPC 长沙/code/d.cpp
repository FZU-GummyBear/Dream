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
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

//int a[2][2], b[2][2], e;
ull n;

struct HM {
	static const int INF = pw(18) - 1, N = 8e5;
	int hd[INF + 1], ne[N], L, f[N];
	ll s[N], sav[N];
	void ini0() { memset(hd, -1, sizeof(hd)); }
	void init() { rep(i, 0, L) hd[sav[i] & INF] = -1; L = 0; }
	void upd(ll u, int v) {
		int p = u & INF;
		for(int i = hd[p]; ~i; i = ne[i]) if(u == s[i]) {
			//f[i] = min(f[i], v);
			f[i] = v;
			return;
		}
		s[L] = sav[L] = u; f[L] = v; ne[L] = hd[p]; hd[p] = L++;
	}
	int find(ll u) {
		int p = u & INF;
		for(int i = hd[p]; ~i; i = ne[i]) if(u == s[i]) {
			return f[i];
		}
		return -1;
	}
}hm;

const uint P = 4e9 + 11, Q = P - 4;

struct mat {
	ull a[2][2];
	mat () {memset(a, 0, sizeof(a)); }
	mat operator * (const mat &c) const {
		mat r;
		rep(i, 0, 2) rep(j, 0, 2) rep(k, 0, 2) r.a[i][j] = (r.a[i][j] + a[i][k] * c.a[k][j] % n) % n;
		return r;
	}
	bool operator == (const mat &c) const{
		rep(i, 0, 2) rep(j, 0, 2) if (a[i][j] != c.a[i][j]) return 0;
		return 1;
	}
	bool operator < (const mat &c) const{
		rep(i, 0, 2) rep(j, 0, 2) if (a[i][j] != c.a[i][j]) return a[i][j] < c.a[i][j];
		return 0;
	}
	ull val() {
		ull res = 0;
		rep(i, 0, 2) rep(j, 0, 2) res = (res * Q  + a[i][j] + 1) % P;
		return res;
	}
} e, b, invb;

mat kpow(mat a, ll b) {
	mat res = e;
	while (b) {
		if (b & 1) res = res * a;
		a = a * a;
		b >>= 1;
	}
	return res;
}

struct Bsgs{
	ll bsgs(ll n) {
		mat t = b;
		rep(i, 1, 51) {
			if (t == e) return i;
			t = t * b;
		}
		ll sq = sqrtl(n); t = b;// M.clear();
		//de(sq);
		hm.init();
		rep(i, 1, sq+1) {
			if (hm.find(t.val()) != -1) break;
			hm.upd(t.val(), i);
			t = t * b;
		}
		mat res = e;
		ll len = n / sq; mat sa = kpow(invb, sq);
		rep(i, 0, len+1) {
			if (i > 0 && res == e) return i * sq;
			ll r = hm.find(res.val());
			if (r != -1) return i * sq + r; else res = res * sa;
		}
		assert(0);
	}
} B;

/*ll solve(int P) {
	rep(i, 0, 2) rep(j, 0, 2) a[i][j] = 1; a[1][1] = 2 % P;
	rep(i, 0, 2) rep(j, 0, 2) b[i][j] = (i == j);
	for(int k = 1; ; k++) {
		int c[2][2] = {0};
		rep(i, 0, 2) rep(j, 0, 2) rep(t, 0, 2) c[i][j] = (c[i][j] + b[i][t] * a[t][j]) % P;
		bool ok = 1;
		rep(i, 0, 2) rep(j, 0, 2) if(c[i][j] != (i == j)) ok = 0;
		rep(i, 0, 2) rep(j, 0, 2) b[i][j] = c[i][j];
		if(ok) return k;
	}
}

void tes() {
	rep(n, 2, 110) dd(n), de(solve(n));
}*/

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	//tes();
	e.a[0][0] = e.a[1][1] = 1;
	b.a[0][0] = b.a[0][1] = b.a[1][0] = 1; b.a[1][1] = 2;
	hm.ini0();
	while (cin >> n) {
		if (n == 2) {
			cout << 3 << endl;
			continue;
		}
		invb.a[0][0] = 2;
		invb.a[0][1] = invb.a[1][0] = n-1;
		invb.a[1][1] = 1;
		cout << B.bsgs(n * 5) << endl;
	}
	return 0;
}
