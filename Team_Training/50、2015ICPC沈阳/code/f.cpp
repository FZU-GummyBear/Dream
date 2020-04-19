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

const int N = 1e5 + 7;
__int128 f[N], ans;
int a[N], m, T, n, vis[N], tim;

vi tmp;
unordered_map<int, int> M;

ll cal(int x) {
	int len = m / x;
	return 1ll * (len - 1) * len / 2 * x;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m;
		rep(i, 1, n+1) cin >> a[i];
		int s = sqrt(m);
		tmp.clear(); M.clear(); tim = 0; ans = 0;
		rep(i, 1, s+1) if (m % i == 0) {
			tmp.pb(i);
			if (i * i != m) tmp.pb(m / i);
		}
		sort(all(tmp));
		for (auto u : tmp) M[u] = ++tim;
		rep(i, 1, tim+1) vis[i] = 0;
		rep(i, 1, n+1) vis[M[__gcd(a[i], m)]] = 1;
		rep(i, 1, tim+1) f[i] = 0;
		per(i, 1, tim+1) {
			f[i] = cal(tmp[i-1]);
			rep(j, i+1, tim+1) if (tmp[j-1] % tmp[i-1] == 0) {
				f[i] -= f[j];
				if (vis[i]) vis[j] = 1;
			}	
			//dd(i), dd(tmp[i-1]), de((ll)f[i]);
		}

		rep(i, 1, tim+1) if (vis[i]) ans += f[i]; 
		cout << "Case #" << cas + 1 << ": " << (ll)ans << endl;
	}
	return 0;
}
