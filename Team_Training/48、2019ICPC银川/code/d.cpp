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

const int phi = 642 * 93256, N = 1e5 + 7, P = 59964251;
int T, mu[N], m, d, k, ok, t, ans, h[N], sk[N], kk[N];
string s;

int add(int a, int b) { 
	if ((a += b) >= P) a -= P;
	return a < 0 ? a + P : a;
}

int mul(int a, int b) {
	return 1ll * a * b % P;
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

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	mu[1] = 1;
	rep(i, 1, N) for (int j = i + i; j < N; j += i) mu[j] -= mu[i];
	rep(cas, 0, T) {
		cin >> s >> m >> d >> k;
		ok = 0; t = 0; ans = 0;
		rep(i, 0, sz(s)) {
			t = t * 10 + s[i] - '0';
			if (t >= phi) ok = 1;
			t %= phi;
		} 
		m = m / d;
		rep(i, 1, m+1) kk[i] = kpow(i, k);
		rep(i, 1, m+1) sk[i] = add(kk[i], sk[i-1]);
		rep(i, 1, m+1) h[i] = mul(kpow(kk[i], ok * phi + t), kpow(sk[m / i], ok * phi + t));
		rep(i, 1, m+1) ans = add(ans, mul(mu[i], h[i]));
		ans = mul(ans, kpow(kpow(d, k), t + ok * phi));
		cout << ans << endl;
	}
	return 0;
}
