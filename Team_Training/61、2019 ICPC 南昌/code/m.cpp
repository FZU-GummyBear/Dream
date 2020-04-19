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

const int P = 1e9 + 7, N = 1e5 + 1000;
int n;
ll a[N], M, x, y;
ll add(ll a, ll b) {
	a %= P; b %= P;
	if ((a += b) >= P) a -= P;
	return a < 0 ? a + P : a;
} 

ll mul(ll a, ll b) {
	a %= P; b %= P;
	a = 1ll * a * b % P;
	return a < 0 ? a + P : a;
}
int kpow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = mul(res, a);
		a = mul(a, a);
		b >>= 1;
	}
	return res;
}

int sk(int n, int k) {
	int res = 0;
	rep(i, 1, n+1) res = add(res, kpow(i, k));
	return res;
}

int cal1(int n, int m) {
	int res = 0;
	rep(k, 1, n+1) {
		res = add(res, mul(kpow(2, k), sk(m / 2, k)));
	}
	return res;
}



struct polysum {
	static const int D = 101010;
	ll a[D], fac[D], ifac[D], p1[D], p2[D], h[D][2], C[D];
	void init(int M) {
		fac[0] = 1; rep(i, 1, M + 5) fac[i] = mul(fac[i - 1], i);
		ifac[M + 4] = kpow(fac[M + 4], P - 2);
		per(i, 0, M + 4) ifac[i] = mul(ifac[i + 1], i + 1);
	}
	ll calcn(int d, ll *a, ll n) {
		if(n <= d) return a[n];
		p1[0] = p2[0] = 1;
		rep(i, 0, d + 1) p1[i + 1] = mul(p1[i], (n - i) % P);
		rep(i, 0, d + 1) p2[i + 1] = mul(p2[i], (n - d + i) % P);
		ll ans = 0;
		rep(i, 0, d + 1) {
			ll s1 = mul(p1[i], p2[d - i]);
			ll s2 = mul(ifac[i], ifac[d - i]);
			ll t = mul(mul(s1, s2), a[i]);
			ans = (d - i) & 1 ? add(ans, -t) : add(ans, t);
		}
		return ans;
	}
} poly;

int h(int n, ll m) {
	M = n + 20;
	rep(i, 1, M+1) a[i] = add(a[i-1], mul(mul(2 * i, add(1, -kpow(2 * i, n))), kpow(add(1, -2 * i), P - 2)));//, de(a[i]);
//	dd(M), de(m);
	return poly.calcn(M, a, m / 2);
}


int solve(int n, ll m) {
	int res = 0;
	res = add(res, mul((m + 3) / 4, n));
	res = add(res, mul((m + 1) / 4, n / 2));
	res = add(res, (m + 2) / 4 % P);
	//de(M);
	//de(h(n, m * 10));
	//de(cal1(n, m * 10));
	//return 0;
	return add(res, h(n, m));
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	poly.init(poly.D - 10);
	cin >> n >> x >> y;
	cout << add(solve(n, y), -solve(n, x - 1)) << endl;
	return 0;
}
