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

const int N = 111;

int n, m, a[N][N];
pii t[N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	vi ans;
	rep(i, 1, m + 1) ans.pb(i);
	rep(i, 1, m + 1) rep(j, 1, n + 1) cin >> a[i][j];
	rep(i, 1, n) {
		rep(j, 1, m + 1) t[j] = mp(a[j][i] - a[j][n], j);
		sort(t + 1, t + 1 + m);
		reverse(t + 1, t + 1 + m);
		ll sum = 0, cnt = 0;
		rep(j, 1, m + 1) {
			sum += t[j].fi;
			if(sum < 0) break;
			++cnt;
		}
		if(m - cnt < sz(ans)) {
			ans.clear();
			rep(j, cnt + 1, m + 1) ans.pb(t[j].se);
		}
	}
	cout << sz(ans) << endl;
	rep(i, 0, sz(ans)) cout << ans[i] << " \n"[i == sz(ans) - 1];
	return 0;
}
