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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define endl '\n'
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef long double db;
typedef vector<int> vi;

const db eps = 1e-8;

int sign(db x) { return (x > eps) - (x < -eps); }

struct P {
	db x, y;
	P(db x = 0, db y = 0) : x(x), y(y) {}
	P operator + (const P &c) const { return P(x + c.x, y + c.y); }
	P operator - (const P &c) const { return P(x - c.x, y - c.y); }
	P operator * (const db &c) const { return P(x * c, y * c); }
	P operator / (const db &c) const { return P(x / c, y / c); }
	db len2() { return x * x + y * y; }
	db len() { return sqrt(len2()); }
	P rot90() { return P(-y, x); }
	void read() {
		int a, b; scanf("%d%d", &a, &b);
		x = a, y = b;
	}
};
db dot(P a, P b) { return a.x * b.x + a.y * b.y; }
db det(P a, P b) { return a.x * b.y - a.y * b.x; }
struct C {
	P o; db r;
	C() {}
	C(P o, db r) : o(o), r(r) {}
	void read() {
		o.read();
		int x; scanf("%d", &x);
		r = x;
	}
};
struct L {
	P a, b;
	L() {}
	L(P a, P b) : a(a), b(b) {}
	void print() {
		dd(a.x), dd(a.y), dd(b.x), de(b.y);
	}
};
P proj(L l, P p) {
	return l.a + (l.b - l.a) * (dot(p - l.a, l.b - l.a) / (l.b - l.a).len2());
}
bool isCL(C a, L l, P &p1, P &p2) {
	db x = dot(l.a - a.o, l.b - l.a);
	db y = (l.b - l.a).len2();
	db d = x * x - y * ((l.a - a.o).len2() - a.r * a.r);
	if(sign(d) < 0) return 0;
	d = max(d, (db)0);
	P p = l.a - ((l.b - l.a) * (x / y)), det = (l.b - l.a) * (sqrt(d) / y);
	p1 = p - det, p2 = p + det;
	return 1;
}
bool tanCP(C c, P p0, P &p1, P &p2) {
	db x = (p0 - c.o).len2(), d = x - c.r * c.r;
	if(d < eps) return 0;
	P p = (p0 - c.o) * (c.r * c.r / x);
	P det = ((p0 - c.o) * (-c.r * sqrt(d) / x)).rot90();
	p1 = c.o + p + det;
	p2 = c.o + p - det;
	return 1;
}
vector<L> extanCC(C c1, C c2) {
	vector<L> ret;
	if(sign(c1.r - c2.r) == 0) {
		P dir = c2.o - c1.o;
		dir = (dir * (c1.r / dir.len())).rot90();
		ret.pb(L(c1.o + dir, c2.o + dir));
		ret.pb(L(c1.o - dir, c2.o - dir));
	} else {
		P p = (c1.o * -c2.r + c2.o * c1.r) / (c1.r - c2.r);
		P p1, p2, q1, q2;
		if(tanCP(c1, p, p1, p2) && tanCP(c2, p, q1, q2)) {
			if(c1.r < c2.r) swap(p1, p2), swap(q1, q2);
			ret.pb(L(p1, q1));
			ret.pb(L(p2, q2));
		}
	}
	return ret;
}
vector<L> intanCC(C c1, C c2) {
	vector<L> ret;
	P p = (c1.o * c2.r + c2.o * c1.r) / (c1.r + c2.r);
	P p1, p2, q1, q2;
	if(tanCP(c1, p, p1, p2) && tanCP(c2, p, q1, q2)) {
		ret.pb(L(p1, q1));
		ret.pb(L(p2, q2));
	}
	return ret;
}

C cfy;
C c1, c2, c10, c20; P p;
vector<C> ans;

P fy(C c, P p) {
	db d = (c.o - p).len();
	db r = c.r * c.r / d;
	return (p - c.o) * r / d + c.o;
}
C fy(C c) {
	P p1, p2;
	isCL(c, L(p, c.o), p1, p2);
	p1 = fy(cfy, p1);
	p2 = fy(cfy, p2);
	return C((p1 + p2) / 2, (p1 - p2).len() / 2);
}
bool c3(C A, C B) {
	db dis = (A.o - B.o).len();
	return sign(dis - (A.r + B.r)) == 0;
}

void calc(L l) {
	if(!sign(det(p - l.a, p - l.b))) return ;
	P tp = proj(l, p);
	tp = fy(cfy, tp);
	C c((p + tp) / 2, (p - tp).len() / 2);
	if(!c3(c, c10) || !c3(c, c20)) return ;
	ans.pb(c);
}

void solve() {
	c1.read();
	c2.read();
	c10 = c1, c20 = c2;
	p.read();
	cfy = C(p, 1e6);
	c1 = fy(c1);
	c2 = fy(c2);
	ans.clear();
	auto res = extanCC(c1, c2);
	for(auto u : res) calc(u);
	res = intanCC(c1, c2);
	for(auto u : res) calc(u);
	printf("%d\n", sz(ans));
	for(auto u : ans) printf("%.8f %.8f %.8f\n", (double)u.o.x, (double)u.o.y, (double)u.r);
}

int main() {
	int T; scanf("%d", &T);
	while(T--) solve();
	return 0;
}
