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
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(a) a.begin(), a.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int P = 1e9 + 7, N = 2e5 + 7;

int now, ans, pw2[N], k[N], n, m, ma, vis[N], b[N], cc, use[N];
vi tmp, tmp2, a[N];
int p, cnt[N], pos[N];

int add(int a, int b) {
	if ((a += b) >= P) a -= P;
	return a < 0 ? a + P : a;
}

struct FW {
#define lb(x) ((x) & (-x))
	static const int N = ::N;
	ll a[N], n;
	void init(int _n) {
		n = _n;
		fill_n(a, n + 1, 0);
	}
	void upd(int p, ll c) {
		for( ; p <= n; p += lb(p)) a[p] = add(a[p], c);
	}
	ll qry(int p) {
		ll res = 0;
		for( ; p; p ^= lb(p)) res = add(res, a[p]);
		return res;
	}
	ll qry(int l, int r) {
		return add(qry(r), -qry(l-1));
	}
} fw;

int main() {
	//freopen("a.in", "r", stdin);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	pw2[0] = 1;
	rep(i, 1, 200001) pw2[i] = 1ll * pw2[i-1] * 2 % P;
	while (cin >> n >> m) {
		tmp.clear();
		ans = now = 0;
		ma = 0; cc = 0;
		rep(i, 1, n+1) {
			a[i].clear();
			int x;
			cin >> k[i];
			rep(j, 1, k[i] + 1) cin >> x, a[i].pb(x);
			ma = max(ma, k[i]);
			tmp.pb(i);
		}
		rep(i, 1, m+1) cin >> b[i], pos[i] = 0, vis[i] = 0;
		rep(i, 1, ma+1) {
			cnt[i] = 0; use[i] = 0;
			for (auto u : tmp) {
				if (!vis[a[u][i-1]]) {
					vis[a[u][i-1]] = 1;
					pos[a[u][i-1]] = i;
					cnt[i]++;
				}
				if (i < sz(a[u])) tmp2.pb(u);
			}
			tmp = tmp2;
			tmp2.clear();
		}
		fw.init(ma);
		rep(i, 1, ma+1) now = add(now, pw2[cnt[i]] - 1), fw.upd(i, pw2[cnt[i]] - 1);//, de(cnt[i]);
		now = add(now, 1);
		ans = now; 
		rep(i, 1, m+1) {
			if (pos[b[i]] == 0) ans = add(ans, now);
			else {
				int p = pos[b[i]];
				fw.upd(p, -(pw2[cnt[p]] - 1));
				cnt[p]--;
				fw.upd(p, pw2[cnt[p]] - 1);
				now = add(fw.qry(1, ma), 1); 
				ans = add(ans, add(now, -add(fw.qry(p, ma), 1)));
			}
		}
		cout << ans << endl;
	}
	return 0;
}
