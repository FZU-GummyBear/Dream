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
typedef long double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 10101;
const db eps = 1e-8, pi = acos(-1);

int sign(db x) {
	return (x > eps) - (x < -eps);
}

int n;
pair<ll, ll> a[N];
db r[N], d[N];
db calc(db st) {
	r[1] = st; rep(i, 2, n + 1) r[i] = d[i - 1] - r[i - 1];
	db ans = 0; rep(i, 1, n + 1) ans += r[i] * r[i];
	return ans * pi;
}
bool solve() {
	scanf("%d", &n);
	rep(i, 1, n + 1) {
		int x, y; scanf("%d%d", &x, &y);
		a[i] = mp(x, y);
	}
	rep(i, 1, n + 1) {
		int j = (i == n ? 1 : i + 1);
		ll dx = a[i].fi - a[j].fi;
		ll dy = a[i].se - a[j].se;
		d[i] = sqrt(dx * dx + dy * dy);
	}
	if(n & 1) {
		r[1] = 0;
		rep(i, 1, n + 1) {
			if(i & 1) r[1] += d[i];
			else r[1] -= d[i];
		}
		r[1] /= 2;
		rep(i, 2, n + 1) r[i] = d[i - 1] - r[i - 1];
		rep(i, 1, n + 1) if(r[i] < 0) return 0;
		return 1;
	} else {
		db t = 0, st = 0, ed = d[1];
		rep(i, 1, n + 1) {
			if(i & 1) {
				t += d[i];
				ed = min(ed, t);
			} else {
				t -= d[i];
				st = max(st, t);
			}
		}
		if(sign(t) || st > ed) return 0;
			while(sign(ed - st)) {
			db m1 = st + (ed - st) / 3;
			db m2 = st + (ed - st) * 2 / 3;
			if(calc(m1) < calc(m2)) {
				ed = m2;
			} else {
				st = m1;
			}
		}
		r[1] = st; rep(i, 2, n + 1) r[i] = d[i - 1] - r[i - 1];
		return 1;
	}
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		if(solve()) {
			printf("%.2f\n", (double)calc(r[1]));
			rep(i, 1, n + 1) printf("%.2f\n", (double)r[i]);
		} else {
			printf("IMPOSSIBLE\n");
		}
	}
	return 0;
}
