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
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

void Assert(int o) {
	//if(!o) while(1);
}

const int N = 1e3 + 7;
ll a[N], b[N], c[N], n, k, T, d[N];
vector<pair<ll, ll> > ans;
int solve(ll n, ll m, ll w) {
	w -= n * (k - 1);
	if (m < 0) return 0;
	if (w < 0) return 0;
	if (n < m) return 0;
	if (m == 0) {
		if (n != 0 || w != 0) return 0;
		return 2;
	}
	if (m == 1) {
		if (w % n == 0) {
			ans.pb(mp(w / n + k - 1, n));
			return 2;
		}else return 0;
	}
	ll t = 0;
	rep(i, 1, m+1) {
		t += i;
		if (i == 1) t += n - m;
		if (i > 1) ans.pb(mp(k - 1 + i, 1));
		else ans.pb(mp(k, 1 + n - m));
	}
	if (t == w) return 2;

	if (t > w) return 0;
	if (t == w - 1) {
		if (n > m) return 1;
		if (n == m) {
			ans.back().fi++;
			return 2;
			//dd(n), dd(m), de(w);
		}
	}
	if (m >= 3) return 1;
	int cnt = 0;
	rep(a, 1, n) {
		ll b = n - a;
		for (ll x = 1; a * x < w; x++) {
			if ((w - a * x) % b != 0) continue;
			ll y = (w - a * x) / b;
			if (x < y) {
				cnt++;
				ans.pop_back();
				ans.pop_back();
				ans.pb(mp(x + k - 1, a));
				ans.pb(mp(y + k - 1, b));
				if (cnt > 1) return 1;
			}
		}
	}
	if (cnt == 0) return 0;
	return 2;
}

int solve1() {
	rep(i, 1, k+1) {
		b[i] = a[i-1] - a[i];
		if (b[i] < 0) {
			return 0;
		}
	}
	ll w = a[0];
	rep(i, 1, k) {
		c[i] = b[i] - b[i+1];
		if (c[i] < 0) {
			return 0;
		}
		w -= c[i] * i;
		if (c[i] > 0) n--, ans.pb(mp(i, c[i]));
	}
	c[k] = b[k];
	int ok = solve(c[k], n, w);
	return ok;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> k;
		int nn = n;
		ans.clear();
		rep(i, 0, k+1) cin >> a[i];
		cout << "Case #" << cas + 1 << ":" << endl;
		int ok = solve1(); 
		if (ok == 0) cout << "No Solution";
		else if (ok == 1) cout << "Multiple Solutions";
		else cout << "Unique Solution";
		cout << endl;
		if (ok == 2) {
			Assert(sz(ans) == nn);
			rep(i, 0, k+1) {
				d[i] = 0;
				rep(j, 0, sz(ans)) d[i] += max(ans[j].fi - i, 0ll) * ans[j].se;
				Assert(d[i] == a[i]);
			}
			rep(i, 0, sz(ans) - 1) Assert(ans[i].fi < ans[i+1].fi);
			rep(i, 0, sz(ans)) cout << ans[i].fi << " " << ans[i].se << endl;
		}
	}
	return 0;
}
