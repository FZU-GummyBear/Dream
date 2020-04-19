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
#define all(x) x.begin(), x.end()
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

int T, n;

struct Min_25{
	static const int N = 1e6 + 8;
	int Sqr, m, p[N], id1[N], id2[N], tot, cntp;
	ll g[N], sp1[N], sp2[N][2], h[N][2], n, w[N];
	bool isp[N];
	
	int calc1(int n) { return n - 1; }

	ll F(int p, int e) {if (p % 4 == 1) return e * 3 + 1; else return 1;}
	
	void prime(int n) {
		cntp = 0; isp[1] = 1;
		rep(i, 2, n+1) {
			if (!isp[i]) p[++cntp]  = i;
			for (int j = 1; j <= cntp && i * p[j] <= n; j ++) {
				isp[i * p[j]] = 1;
				if (i % p[j] == 0) break;
			}
		}
		rep(i, 1, cntp+1) {
			sp1[i] = sp1[i-1] + 1;
			sp2[i][0] = sp2[i-1][0] + (p[i] % 4 == 1);
			sp2[i][1] = sp2[i-1][1] + (p[i] % 4 == 3);
		}
		p[++cntp] = INT_MAX;
	}

	ll S(ll x, int y) {
		if (x <= 1 || p[y] > x) return 0;
		int k = (x <= Sqr ? id1[x] : id2[n / x]);
		ll ret = g[k] + h[k][0] * 3 - sp1[y-1] - sp2[y-1][0] * 3; 
		for (int i = y; i <= tot && 1ll * p[i] * p[i] <= x; i ++) {
			ll t1 = p[i], t2 = 1ll * p[i] * p[i];
			for (int e = 1; t2 <= x; e++, t1 = t2, t2 *= p[i]) {
				if (F(p[i], e)) ret += S(x / t1, i + 1) * F(p[i], e);
				ret += F(p[i], e+1);
			}
		}
		return ret;
	}

	ll solve(ll _n) {
		n = _n; if (n == 0) return 0;
		m = 0; Sqr = sqrt(n);
		tot = upper_bound(p + 1, p + cntp + 1, Sqr) - (p + 1);
		for (ll i = 1, j; i <= n; i = j + 1) {
			j = n / (n / i);
			w[++m] = n / i;
			g[m] = calc1(w[m]);
			h[m][0] = (w[m] - 1) / 4;
			h[m][1] = w[m] >= 3 ? (w[m] - 3) / 4 + 1 : 0;
			w[m] <= Sqr ? id1[w[m]] = m : id2[j] = m;
		}
		rep(j, 1, tot+1) 
			for (int i = 1; i <= m && 1ll * p[j] * p[j] <= w[i]; i++) {
				ll t = w[i] / p[j];
				int k = t <= Sqr ? id1[t] : id2[n / t];
				g[i] -= (g[k] - sp1[j - 1]);
				if (p[j] % 4 == 1) {
					h[i][0] -= (h[k][0] - sp2[j - 1][0]);
					h[i][1] -= (h[k][1] - sp2[j - 1][1]);
				}
				if (p[j] % 4 == 3) {
					h[i][0] -= (h[k][1] - sp2[j - 1][1]);
					h[i][1] -= (h[k][0] - sp2[j - 1][0]);
				}
			}
		return S(n, 1) + 1;
	}

} _U;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	_U.prime(1e5);
	rep(cas, 0, T) {
		cin >> n;
		cout << _U.solve(n) << endl;
	}
	return 0;
}
