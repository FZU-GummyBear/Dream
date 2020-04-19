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
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 4040;

struct P {
	ll x, y;
	P() {}
	P(ll x, ll y) : x(x), y(y) {}
	P operator + (const P &c) const { return P(x + c.x, y + c.y); }
	P operator - (const P &c) const { return P(x - c.x, y - c.y); }
	void read() { cin >> x >> y; }
	inline bool operator < (const P &c) const {
		if(x != c.x) return x < c.x;
		return y < c.y;
	}
};

int n, q, ans[N], sum[N];
P p[N], a[N], b[N];
pair<P, int> c[N];

inline ll det(P a, P b) {
	return a.x * b.y - a.y * b.x;
}
ll dot(P a, P b) {
	return a.x * b.x + a.y * b.y;
}

inline bool cmp(const P &a, const P &b) {
	int o = P(0, 0) < a, t = P(0, 0) < b;
	if(o != t) return o < t;
	return det(a, b) > 0;
}
inline bool cmp2(const pair<P, int> &a, const pair<P, int> &b) {
	return cmp(a.fi, b.fi) > 0;
}
bool check(P a, P b) {
	return dot(a, b) > 0 && det(a, b) >= 0;
}
bool che(P a, P b) {
	return dot(a, b) == 0 && det(a, b) > 0;
}
void solve(int _) {
	ll ans = 0;
	P &o = b[_]; o.x = rand(), o.y = rand();
	rep(i, 0, n) a[i] = p[i] - o;
	sort(a, a + n, cmp);
	vector<pii> vec;
	int pre = 0;
	rep(i, 1, n + 1) {
		if(i == n || !(det(a[i], a[i - 1]) == 0 && dot(a[i], a[i - 1]) > 0)) {
			vec.pb(mp(pre, i - 1));
			pre = i;
		}
	}
	int j = 0;
	if(sz(vec) > 1) rep(i, 0, sz(vec)) {
		while(check(a[vec[i].fi], a[vec[j].fi])) j = (j + 1) % sz(vec);
		if(che(a[vec[i].fi], a[vec[j].fi])) ans += (vec[i].se - vec[i].fi + 1) * 1ll * (vec[j].se - vec[j].fi + 1);
	}
	::ans[_] = ans;
}
int qry(int l, int r) {
	if(l) return sum[r] - sum[l - 1];
	return sum[r];
}
void gao(int _) {
	rep(i, 0, n) c[i] = mp(p[i] - p[_], i);
	rep(i, 0, q) c[i + n] = mp(b[i] - p[_], i + n);
	int m = n + q - 1;
	swap(c[_], c[m]);
	sort(c, c + m, cmp2);
	sum[0] = c[0].se < n;
	rep(i, 1, m) sum[i] = sum[i - 1] + (c[i].se < n);
	vector<pii> vec;
	int pre = 0;
	rep(i, 1, m + 1) {
		if(i == m || !(det(c[i].fi, c[i - 1].fi) == 0 && dot(c[i].fi, c[i - 1].fi) > 0)) {
			vec.pb(mp(pre, i - 1));
			pre = i;
		}
	}
	int j = 0;
	if(sz(vec) > 1) rep(i, 0, sz(vec)) {
		while(check(c[vec[i].fi].fi, c[vec[j].fi].fi)) j = (j + 1) % sz(vec);
		if(che(c[vec[i].fi].fi, c[vec[j].fi].fi)) {
			int k = qry(vec[j].fi, vec[j].se);
			rep(t, vec[i].fi, vec[i].se + 1) {
				if(c[t].se >= n) {
					int o = c[t].se - n;
					ans[o] += k;
				}
			}
			/*
			swap(i, j);
			k = qry(vec[j].fi, vec[j].se);
			rep(t, vec[i].fi, vec[i].se + 1) {
				if(c[t].se >= n) {
					int o = c[t].se - n;
					ans[o] += k;
				}
			}
			swap(i, j);
			*/
		}
	}
}
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	n = q = 2000;
	rep(i, 0, n) p[i].x = rand(), p[i].y = rand();
	rep(i, 0, q) solve(i);
	rep(i, 0, n) gao(i);
	rep(i, 0, n) gao(i);
	rep(i, 0, q) cout << ans[i] << endl;
	return 0;
}
