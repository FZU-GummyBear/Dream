#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(c) cout << #c << " = " << c << endl
#define dd(c) cout << #c << " = " << c << " "
#define endl '\n'
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef double db;
typedef pair<ll, int> pii;
typedef vector<int> vi;

const int N = 2e5 + 10;
priority_queue<pii, vector<pii>, greater<pii> > q;
vi t1, t2;
int n, k, x, m, S, kk;
ll w, ans[N];

void solve(vi &t, int k) {
	kk = 0;
	sort(all(t));
	while (!q.empty()) {
		pii u = q.top(); q.pop();
		ans[++kk] = u.fi; //dd(u.fi), de(u.se);
		if (kk == k) break;
		if (u.se && u.se < sz(t)) {
			//de(u.fi - t[u.se-1] + t[u.se]);
			q.push(mp(u.fi - t[u.se-1] + t[u.se], u.se+1));
		}
		//de(u.fi + t[u.se]);
		if (u.se < sz(t)) q.push(mp(u.fi + t[u.se], u.se+1));
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> k;
	rep(i, 1, n+1) {
		cin >> x;
		if (x < 0) t1.pb(x);
		else t2.pb(x);
	}
	if (sz(t1) >= 18) {
		rep(i, 0, sz(t1)) t1[i] *= -1, w += t1[i];
		q.push(mp(0, 0));
		solve(t1, k);
		rep(i, 1, k+1) ans[i] = w - ans[i], ans[i] = -ans[i];
		sort(ans+1, ans+k+1);
		while (!q.empty()) q.pop();
		rep(i, 1, k+1) q.push(mp(ans[i], 0));
	}else {
		m = sz(t1);
		S = pw(m) - 1;
		rep(i, 0, S+1) {
			ll t = 0;
			rep(j, 0, m) if (pw(j) & i) t += t1[j];
			q.push(mp(t, 0));
		}
	}
		solve(t2, k+1);
		//rep(i, 1, k+2) de(ans[i]);
		sort(ans+1, ans+k+2);
		rep(i, 1, k+2) if (ans[i] == 0) {
			rep(j, i+1, k+2) ans[j-1] = ans[j];
			break;
		}
	
	rep(i, 1, k+1) cout << ans[i] << endl;
	return 0;
}
