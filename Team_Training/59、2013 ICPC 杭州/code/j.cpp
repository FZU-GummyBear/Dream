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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define endl '\n'
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int P = 1e9 + 7;

const int N = 405;
int ans, g[N][N][N], n, m, k, c[N][N], inv2[N], jc[N], T, q, p, inv[N];

int add(int a, int b) {
	if ((a += b) >= P) a -= P;
	return a;
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

void upd(int &x, int y) {
	x = add(x, y);
}
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	n = m = 200;
	rep(i, 0, n+1) {
		c[i][0] = 1;
		rep(j, 1, i+1) {
			c[i][j] = add(c[i-1][j], c[i-1][j-1]);
	 	}
	}
	jc[0] = 1;
	rep(i, 1, n+1) jc[i] = mul(jc[i-1], i);
	inv[n] = kpow(jc[n], P - 2);
	per(i, 0, n) inv[i] = mul(inv[i+1], i+1);
	inv2[0] = 1; inv2[1] = (P + 1) / 2;
	rep(i, 2, n+1) inv2[i] = mul(inv2[i-1], inv2[1]);
	rep(i, 0, n+1) rep(j, 0, m+1) {
		for (int a = 0; a * 2 <= i && a <= j; a++)
			for (int b = 0; a * 2 + b <= i && a + b * 2 <= j; b++) {
				int t1 = mul(jc[2 * a + b], inv2[a]);
				int t2 = mul(jc[2 * b + a], inv2[b]);
				t1 = mul(t1, inv[a]);
				t2 = mul(t2, inv[b]);
				upd(g[i][j][(a + b) * 2], mul(mul(c[i][2 * a + b], c[j][2 * b + a]), mul(t1, t2))); 
			}
	}
	rep(i, 0, n+1) rep(j, 0, m+1) rep(k, 1, n * 2 + 1) upd(g[i][j][k], g[i][j][k-1]);
	//de(g[1][1][0]);
	//de(g[0][0][1]);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m >> q >> p;
		ans = 0;
		rep(k, 0, p+q+1) {
			if (k > n || k > m) break;
			int t1 = mul(c[n][k], c[m][k]);
			t1 = mul(jc[k], t1);
			rep(i, 0, k+1) {
				if (i > q) break;
				if (k - i > p) continue;
				//dd(k), dd(i), dd(ans);
				upd(ans, mul(g[n - k][m - k][q - i], mul(t1, c[k][i])));
				//de(ans);
			}
		}
		cout << add(ans , P - 1) << endl;
	}
	return 0;
}
