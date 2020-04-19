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

const int N = 1e5 + 78;
int T, n, u[N], a[N];
vi d[N];
ll ans, cnt[N], l[N], r[N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	n = 100000;
	u[1] = 1;
	rep(i, 1, n+1) {
		for (int j = i; j <= n; j += i) d[j].pb(i);
		for (int j = i + i; j <= n; j += i) u[j] -= u[i];
	}
//	rep(i, 1, 50) de(u[i]);
	rep(cas, 0, T) {
		cin >> n;
		rep(i, 1, n+1) cin >> a[i];
		sort(a + 1, a + n + 1);
		rep(i, 0, a[n]+1) cnt[i] = 0;
		rep(i, 1, n+1) {
			ll t = 0;
			for (auto v : d[a[i]]) t += cnt[v] * u[v];
			for (auto v : d[a[i]]) cnt[v]++; //t += cnt[v] * u[i / v];
			//de(t);	
			l[i] = i - t - 1;
		}
		rep(i, 0, a[n]+1) cnt[i] = 0;
		per(i, 1, n+1) {
			ll t = 0;
			for (auto v : d[a[i]]) t += cnt[v] * u[v];
			for (auto v : d[a[i]]) cnt[v]++; //t += cnt[v] * u[i / v];
			r[i] = n - i - t;
		}
		//rep(i, 1, n+1) dd(l[i]), de(r[i]);
		ans = 1ll * n * (n - 1) * (n - 2) / 6;
		//de(ans);
		rep(i, 1, n+1) ans += l[i] * r[i], ans += l[i] * (l[i] - 1) / 2, ans += r[i] * (r[i] - 1) / 2;
		rep(i, 1, n+1) ans -= l[i] * (n - 2);	
		cout << ans << endl;
	}
	return 0;
}
