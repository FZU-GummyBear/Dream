#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl '\n'
#define pw(x) (1ll << (x))
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const db PI = acos(-1);
const int M = 1 << 18 << 1, P = 1e9 + 7;
int na, nb, a[M], b[M];

struct vir{
	db r, i;
	vir (db r = 0.0, db i = 0.0) : r(r), i(i) {}
	inline vir operator + (const vir &c) { return vir(r + c.r, i + c.i); }
	inline vir operator - (const vir &c) { return vir(r - c.r, i - c.i); }
	inline vir operator * (const vir &c) { return vir(r * c.r - i * c.i, r * c.i + i * c.r); }
	inline vir operator ! () { return vir(r, -i); }
};

struct FFTMOD{
	static const int M = 1 << 18 << 1;
	int N, L, MASK;
	vir w[M], A[M], B[M], C[M], D[M];
	void FFT(vir p[], int n) {
		for (int i = 1, j = 0; i < n - 1; ++ i) {
			for (int s = n; j ^= s >>= 1, ~j & s;);
			if (i < j) swap(p[i], p[j]);
		}
		for (int d = 0; (1 << d) < n; ++ d) {
			int m = 1 << d, m2 = m * 2, rm = n >> (d + 1);
			for (int i = 0; i < n; i += m2) {
				for (int j = 0; j < m; ++ j) {
					vir &p1 = p[i + j + m], &p2 = p[i + j];
					vir t = w[rm * j] * p1;
					p1 = p2 - t, p2 = p2 + t;
				}
			}
		}
	}
	void doit(int *a, int *b, int na, int nb) {
		for (N = 1; N < na + nb - 1; N <<= 1);
		rep(i, 0, na) a[i] = (a[i] % P + P) % P; rep(i, na, N) a[i] = 0;
		rep(i, 0, nb) b[i] = (b[i] % P + P) % P; rep(i, nb, N) b[i] = 0;
		L = 15; MASK = (1 << L) - 1;
		rep(i, 0, N) w[i] = vir(cos(2 * i * PI / N), sin(2 * i * PI / N));
		rep(i, 0, N) {
			A[i] = vir(a[i] >> L, a[i] & MASK);
			B[i] = vir(b[i] >> L, b[i] & MASK);
		}
		mul(a);
	}
	void mul(int *a) {
		FFT(A, N); FFT(B, N);
		rep(i, 0, N) {
			int j = (N - i) % N;
			vir da = (A[i] - !A[j]) * vir(0, -0.5),
					db = (A[i] + !A[j]) * vir(0.5, 0),
					dc = (B[i] - !B[j]) * vir(0, -0.5),
					dd = (B[i] + !B[j]) * vir(0.5, 0);
			C[j] = da * dd + da * dc * vir(0, 1);
			D[j] = db * dd + db * dc * vir(0, 1);
		}
		FFT(C, N), FFT(D, N);
		rep(i, 0, N) {
			ll da = (ll) (C[i].i / N + 0.5) % P;
			ll db = (ll) (C[i].r / N + 0.5) % P;
			ll dc = (ll) (D[i].i / N + 0.5) % P;
			ll dd = (ll) (D[i].r / N + 0.5) % P;
			a[i] = ((dd << (L * 2)) + ((db + dc) << L) + da) % P;
		}
	}
} fft;

const int m = 5, N = 5e4 + 7;

int jc[N], inv[N], n, T, cnt[10], ans;

int add(int a, int b) {
	return (a + b) % P;
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

int solve() {
	rep(i, 0, n+1) a[i] = mul(i <= cnt[0], inv[i]);
	rep(i, 1, m) {
		rep(j, 0, n+1) b[j] = mul(j <= cnt[i], inv[j]);
		fft.doit(a, b, n+1, n+1);
	}
	return mul(a[n], jc[n]);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	n = 20000;
	jc[0] = 1; rep(i, 1, n+1) jc[i] = mul(jc[i-1], i);
	inv[n] = kpow(jc[n], P - 2);
	per(i, 0, n) inv[i] = mul(inv[i+1], i+1);
	rep(cas, 0, T) {
		cin >> n;
		rep(i, 0, m) {
			cin >> cnt[i];
		} 
		ans = solve();
		if (cnt[0]) n--, cnt[0]--, ans = add(ans, -solve());
		if (ans < 0) ans += P;
		cout << "Case #" << cas + 1 << ": " << ans << endl;
	}
	return 0;
}
