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
typedef vector<int> vi;
typedef pair<int, int> pii;

const db eps = 1e-8, pi = acos(-1);
int sign(db x) { return (x > eps) - (x < -eps); }

struct P {
	db x, y;
	P(db x = 0, db y = 0) : x(x), y(y) {}
	P operator - (const P &c) const { return P(x - c.x, y - c.y); }
	db len2() { return x * x + y * y; }
	db len() { return sqrt(len2()); }
	void read() { int a, b; scanf("%d%d", &a, &b); x = a, y = b; }
};
struct C {
	P o; db r;
	C() {}
	C(P o, db r) : o(o), r(r) {}
};

db jiao(C c1, C c2) {
	db d = (c1.o - c2.o).len();
	if(sign(d - (c1.r + c2.r)) >= 0) return 0;
	if(sign(d - fabs(c1.r - c2.r)) <= 0) {
		db r = min(c1.r, c2.r);
		return r * r * pi;
	}
	db x = (d * d + c1.r * c1.r - c2.r * c2.r) / (2 * d);
	db t1 = acos(x / c1.r), t2 = acos((d - x) / c2.r);
	return c1.r * c1.r * t1 + c2.r * c2.r * t2 - d * c1.r * sin(t1);
}

db solve() {
	int R, r; P a, b;
	scanf("%d%d", &r, &R);
	a.read(); b.read();
	C Ra(a, R);
	C Rb(b, R);
	C ra(a, r);
	C rb(b, r);
	return jiao(Ra, Rb) + jiao(ra, rb) - jiao(ra, Rb) - jiao(Ra, rb);
}

int main() {
	int T; scanf("%d", &T);
	rep(i, 1, T + 1) printf("Case #%d: %.6f\n", i, solve());
	return 0;
}
