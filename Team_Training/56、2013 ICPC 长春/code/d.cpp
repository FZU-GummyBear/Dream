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
typedef double db;
typedef vector<int> vi;

const int N = 202020;
const db eps = 1e-8;

int n, L, x[N], y[N], d;
db pre[N];

struct P {
	db x, y;
	P(db x = 0, db y = 0) : x(x), y(y) {}
};
struct Line {
	P a, b;
	db k, c;
	Line() {}
	Line(P a, P b) : a(a), b(b) {
		k = (b.y - a.y) / (b.x - a.x);
		c = a.y - k * a.x;
	}
};

ll det(pii a, pii b) { return 1ll * a.fi * b.se - 1ll * a.se * b.fi; }
db calc(db k, int l) {
	db s = y[l] - (y[l] - y[l - 1]) * k / (x[l] - x[l - 1]);
	return (s + y[l]) * k / 2;
}
db check(db l, int a, int b) {
	db r = l + d;
	db ans = 0;
	if(a <= b) {
		ans = pre[b + 1] - pre[a];
		ans += calc(x[a] - l, a);
		ans -= calc(x[b + 1] - r, b + 1);
	} else {
		ans = calc(x[a] - l, a) - calc(x[a] - r, a);
	}
	return ans;
}

db solve(int l1, int r1) {
	int l2 = l1 + d, r2 = r1 + d;
	if(l2 > L) return 0;
	if(r2 > L) {
		int kk = r2 - L; 
		r2 -= kk, r1 -= kk;
	}
	int a = lower_bound(x + 2, x + 1 + n, r1) - x;
	int b = lower_bound(x + 2, x + 1 + n, r2) - x;
	P a1 = P(x[a - 1], y[a - 1]);
	P a2 = P(x[a], y[a]);
	P b1 = P(x[b - 1], y[b - 1]);
	P b2 = P(x[b], y[b]);
	db ans = 0;
	if(det(pii(y[a] - y[a - 1], x[a] - x[a - 1]), pii(y[b] - y[b - 1], x[b] - x[b - 1])) == 0) {
		ans = max(ans, check(l1, a, b - 1));
		ans = max(ans, check(r1, a, b - 1));
	} else {
		Line L1 = Line(a1, a2);
		Line L2 = Line(b1, b2);
		db x0 = (d / 2. * (L1.k + L2.k) + L2.c - L1.c) / (L1.k - L2.k) - d / 2.;
		if(x0 < l1) x0 = l1;
		if(x0 > r1) x0 = r1;
		ans = check(x0, a, b - 1);
		ans = max(ans, check(l1, a, b - 1));
		ans = max(ans, check(r1, a, b - 1));
	}
	return ans;
}

db solve() {
	scanf("%d%d", &n, &L);
	int ma = 0;
	rep(i, 1, n + 1) scanf("%d%d", x + i, y + i), ma = max(ma, y[i]);
	scanf("%d", &d); d <<= 1;
	if(d == 0) return ma;
	rep(i, 2, n + 1) pre[i] = pre[i - 1] + (y[i - 1] + y[i]) * 1. * (x[i] - x[i - 1]) / 2;
	vi vec;
	rep(i, 1, n + 1) {
		vec.pb(x[i]);
		if(x[i] - d > 0) vec.pb(x[i] - d);
	}
	sort(all(vec));
	vec.erase(unique(all(vec)), vec.end());
	db ans = 0;
	rep(i, 1, sz(vec)) ans = max(ans, solve(vec[i - 1], vec[i]));
	return ans / d;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) printf("%.3f\n", solve());
	return 0;
}
