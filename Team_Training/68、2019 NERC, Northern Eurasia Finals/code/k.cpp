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
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

void tes() {
	ll x = 1e18;
	for(int i = 2; x; ++i) {
		x /= i;
		dd(i), de(x);
	}
}

int cnt[22], pre[22];
ll jc[22];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	jc[0] = 1; rep(i, 1, 22) jc[i] = jc[i - 1] * i;
	int T; cin >> T;
	while(T--) {
		ll k; cin >> k;
		int n = 0;
		memset(cnt, 0, sizeof(cnt));
		for(int i = 2; k; i++) {
			++n;
			cnt[k % i]++;
			k /= i;
		}
		pre[0] = cnt[0];
		rep(i, 1, 22) pre[i] = pre[i - 1] + cnt[i];
		ll ans = 1;
		rep(i, 1, n + 1) {
			ans *= pre[i] - i + 1;
		}
		rep(i, 0, 22) ans /= jc[cnt[i]];
		if(cnt[0]) {
			ll res = 1;
			--cnt[0]; rep(i, 0, 22) --pre[i];
			rep(i, 1, n) res *= max(0, pre[i] - i + 1);
			rep(i, 0, 22) res /= jc[cnt[i]];
			ans -= res;
		}
		cout << ans - 1 << endl;
	}
	return 0;
}
