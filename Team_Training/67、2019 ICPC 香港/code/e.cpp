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
#define sz(x) (int) x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1e4 + 7;
int T, a[N], cnt[2], b[N], need, now, ans[N], q[N], r, n, anss[N];

bool ok;

void dfs(vi t, int x) {
	bool oo = 0;
	for (auto u : t) {
		//dd(u);
		if (u == x) oo = 1;
	}
	//cout << endl;
	if (!oo) return;
	if (sz(t) == 1) {
		ok = 1;
		return;
	}
	rep(i, 0, sz(t)-2) {
		vi tmp;
		rep(j, 0, i) tmp.pb(t[j]);
		vi tt;
		tt.pb(t[i]), tt.pb(t[i+1]), tt.pb(t[i+2]);
		sort(all(tt));
		tmp.pb(tt[1]);
		rep(j, i+3, sz(t)) tmp.pb(t[j]);
		dfs(tmp, x);
	}
}


int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	//T = 1;
	rep(cas, 0, T) {
		cin >> n;
		//n = 9;
		//rep(i, 1, n+1) a[i] = i;
		//do { 
		rep(i, 1, n+1) cin >> a[i];
		/*rep(i, 1, n+1) {
			ok = 0;
			vi t;
			rep(j, 1, n+1) t.pb(a[j]);
			dfs(t, a[i]);
			anss[i] = ok;
		}*/
		rep(i, 1, n+1) {
			cnt[0] = cnt[1] = 0;
			rep(j, 1, n+1) b[j] = a[j] < a[i];
			rep(j, 1, n+1) if (j != i) {
				cnt[b[j]]++;
			}
			if (cnt[0] == cnt[1]) {
				ans[i] = 1;
				continue;
			}
			if (cnt[0] < cnt[1]) {
				swap(cnt[0], cnt[1]);
				rep(j, 1, n+1) b[j] ^= 1;
			}
			need = (cnt[0] - cnt[1]) / 2;
			now = 0; r = 0;
			rep(j, 1, i) {
				q[r++] = b[j];
				if (b[j] == 0) {
					if (r >= 3 && q[r-3] == 0 && q[r-2] == 0) now++, r -= 2;
				}else {
					if (r >= 2 && q[r-2] == 0) r -= 2;
				}
			}
			r = 0;
			rep(j, i+1, n+1) {
				q[r++] = b[j];
				if (b[j] == 0) {
					if (r >= 3 && q[r-3] == 0 && q[r-2] == 0) now++, r -= 2;
				}else {
					if (r >= 2 && q[r-2] == 0) r -= 2;
				}
			}
			//if (i == 4) de(now);
			if (now >= need) ans[i] = 1;else ans[i] = 0;
		}

		//rep(i, 1, n+1) cout << anss[i];
		//cout << endl;
		rep(i, 1, n+1) cout << ans[i];
		cout << endl;
			//	rep(i, 1, n+1) if (anss[i] != ans[i]) {
			//rep(j, 1, n+1) cout << a[j] << " ";
			//return 0;
	//	}
	//	}
	//	while (next_permutation(a+1, a+n+1));
	}
	return 0;
}
