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

const int P = 998244353;

ll add(ll a, ll b) {
	 (a += b) %= P;
	 return a < 0 ? a + P : a;
}

ll mul(ll a, ll b) {
	a %= P;
	b %= P;
	return a * b % P;
}

ll kpow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b & 1) res = mul(res, a);
		a = mul(a, a);
		b >>= 1;
	}
	return res;
}

int N, ok;

ll n, inv6, ans;

ll S(ll n) {
	ll t = mul(n, mul(n + 1, n + 2));
	t = mul(t, inv6);
	return add(t, -n);
} 

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	inv6 = kpow(6, P - 2);
	N = 63 - __builtin_clzll(n);
	ans = 0;
	rep(i, 2, N+1) {
		rep(a, 2, n+1) {
			ll t = 1; ok = 1;
			rep(j, 1, i+1) {
				t = t * a;
				if (t >= n + 1) {ok = 0; break;}
			}
			if (!ok) break;
			ans = add(ans, mul(i, mul(a, max(0ll, min(t * a, n + 1) - t))));
		}
	}
	if (N >= 1) {
		rep(a, 2, n+1) {
			if (1ll * a * a <= n + 1) {
				ans = add(ans, mul(a, add(mul(a, a), -a)));
				ans = add(ans, -mul(a, n + 1 - a));
			}else break;
		}
		ans = add(ans, S(n));
	}
	cout << ans << endl;
	return 0;
}
