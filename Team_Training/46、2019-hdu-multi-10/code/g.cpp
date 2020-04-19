#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll << (x))
#define endl '\n'
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 10101, MX = N, D = 80;
const db eps = 1e-8, pi = acos(-1);

int sign(db x) {
	return (x > eps) - (x < -eps);
}

struct P {
	db x, y;
	P(db x = 0, db y = 0) : x(x), y(y) {}
	void read() { scanf("%lf%lf", &x, &y); }
	P operator + (const P &c) const {
		return P(x + c.x, y + c.y);
	}
	P operator - (const P &c) const {
		return P(x - c.x, y - c.y);
	}
	P operator * (const db &c) const {
		return P(x * c, y * c);
	}
	P operator / (const db &c) const {
		return P(x / c, y / c);
	}
	db len2() {
		return x * x + y * y;
	}
	db len() {
		return sqrt(len2());
	}
	P rot(db a) {
		return P(cos(a) * x - sin(a) * y, cos(a) * y + sin(a) * x);
	}
	bool operator < (const P &c) const {
		return x < c.x;
	}
};
struct L {
	P a, b;
	L() {}
	L(P a, P b) : a(a), b(b) {}
	void read() { a.read(); b.read(); }
	bool operator < (const L &c) const {
		return a < c.a;
	}
	void rot(P p, db ang) {
		a = (a - p).rot(ang) + p;
		b = (b - p).rot(ang) + p;
		if(b < a) swap(a, b);
	}
};
db dot(P a, P b) {
	return a.x * b.x + a.y * b.y;
}
db det(P a, P b) {
	return a.x * b.y - a.y * b.x;
}
db dot(P o, P a, P b) {
	return dot(a - o, b - o);
}
db det(P o, P a, P b) {
	return det(a - o, b - o);
}
db disToL(L l, P p) {
	return fabs(det(l.a, p, l.b) / (l.b - l.a).len());
}
db disToS(L l, P p) {
	return sign(dot(l.a, p, l.b)) * sign(dot(l.b, p, l.a)) == 1 ? disToL(l, p) : min((p - l.a).len(), (p - l.b).len());
}
db disSS(L a, L b) {
	return min(min(disToS(b, a.a), disToS(b, a.b)), min(disToS(a, b.a), disToS(a, b.b)));
}

int n;
L l[N];

db work() {
	db res = 1e18;
	sort(l, l + n);
	rep(i, 1, n) {
		rep(j, max(i - D, 0), i) {
			res = min(res, disSS(l[i], l[j]));
		}
	}
	return res;
}

void solve() {
	cin >> n;
	rep(i, 0, n) l[i].read();
	db ans = 1e18;
	if(n > 1000) {
		rep(i, 0, 5) {
			db ang = (db)(rand() % MX) / MX * 2 * pi;
			P poi(rand() % MX - MX / 2., rand() % MX - MX / 2.);
			rep(j, 0, n) l[i].rot(poi, ang);
			ans = min(work(), ans);
		}
	} else {
		rep(i, 0, n) rep(j, i + 1, n) ans = min(ans, disSS(l[i], l[j]));
	}
	printf("%.10f\n", ans);
}

int main() {
	srand(time(0));
	int T; scanf("%d", &T);
	while(T--) solve();
	return 0;
}
