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
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1010;
const db pi = acos(-1), eps = 1e-8;

int sign(db x) { return (x > eps) - (x < -eps); }

int n, m, a, r, ans[N];

struct P {
	db x, y; 
	P(db x = 0, db y = 0) : x(x), y(y) {}
	void read() { cin >> x >> y; }
	P rot90() { return P(-y, x); }
	P rot(db a) { return P(cos(a) * x - sin(a) * y, cos(a) * y + sin(a) * x); }
	void print() { dd(x), de(y); }
	P operator + (const P &c) const { return P(x + c.x, y + c.y); }
	P operator - (const P &c) const { return P(x - c.x, y - c.y); }
	P operator * (const db &c) const { return P(x * c, y * c); }
	P operator / (const db &c) const { return P(x / c, y / c); }
	db len2() { return x * x + y * y; }
	db len() { return sqrt(len2()); }
	bool operator < (const P &c) const {
		if(x != c.x) return x < c.x;
		return y < c.y;
	}
};
db det(P a, P b) { return a.x * b.y - a.y * b.x; }
db dot(P a, P b) { return a.x * b.x + a.y * b.y; }
db det(P o, P a, P b) { return det(a - o, b - o); }
db rad(P p1, P p2) { return atan2l(det(p1, p2), dot(p1, p2)); }

struct L {
	P a, b;
	L() {}
	L(P a, P b) : a(a), b(b) {}
};
db disToL(L l, P p) { return det(l.a, p, l.b) / (l.b - l.a).len(); }

struct C {
	P o; db r;
	C() {}
	C(P o, db r) : o(o), r(r) {}
};
bool isCL(C a, L l, P &p1, P &p2) {
  db x = dot(l.a - a.o, l.b - l.a);
  db y = (l.b - l.a).len2();
  db d = x * x - y * ((l.a - a.o).len2() - a.r * a.r);
  if(sign(d) < 0) return 0;
  d = max(d, (db)0);
  P p = l.a - ((l.b - l.a) * (x / y)), det = (l.b - l.a) * (sqrt(d) / y);
  p1 = p - det, p2 = p + det; // dir : l.a -> l.b
  return 1;
}

P o, v, d, p[N], v2;
vector<pair<db, P> > vec;
L l;

void add(P p) { vec.pb(mp(disToL(l, p), p)); }

void check(vector<P> p) {
	if(sign(det(p[1], p[0], p[2])) < 0) reverse(all(p));
	rep(i, 1, n + 1) if(ans[i]) {
		bool in = 1;
		rep(j, 0, 4) {
			if(sign(det(p[j], p[(j + 3) % 4], ::p[i])) < 0) in = 0;
		}
		if(in) ans[i] = 0;
	}
}
void solve() {
	cin >> n >> m >> a >> r;
	o.read();
	v.read(); 
	v2 = v.rot(a * pi / 360);
	v = v.rot(2 * pi - a * pi / 360);
	v = v / v.len() * r;
	v2 = v2 / v2.len() * r;
	d.read();
	rep(i, 1, n + 1) p[i].read(), ans[i] = 1;
	rep(j, 1, n + 1) if(ans[j] && sign((p[j] - o).len() - r) <= 0) {
		db t = rad(v, p[j] - o) * 180 / pi;
		if(sign(t) >= 0 && sign(t - a) <= 0) ans[j] = 0;
	}
	int pt = 0;
	// o, v, v2, d
	rep(i, 1, m + 1) {
		int op, t, b; cin >> op >> t >> b;
		vec.clear(); l = L(o, o + d);
		add(o);
		add(o + v);
		add(o + v2);
		L tl(o, o + d.rot90());
		P p1, p2;
		isCL(C(o, r), tl, p1, p2);
		db k;
		k = rad(v, p1 - o) * 180 / pi; if(sign(k) >= 0 && sign(k - a) <= 0) add(p1);
		k = rad(v, p2 - o) * 180 / pi; if(sign(k) >= 0 && sign(k - a) <= 0) add(p2);
		sort(all(vec));
		p1 = vec[0].se; p2 = vec.back().se;
		P det = d / d.len() * (t - pt);
		P np1 = p1 + det, np2 = p2 + det;
		check({p1, np1, np2, p2});
		o = o + det;
		if(op == 1) {
			v = v.rot(2 * pi - b * pi / 180);
			v2 = v2.rot(2 * pi - b * pi / 180);
			rep(j, 1, n + 1) if(ans[j] && sign((p[j] - o).len() - r) <= 0) {
				db t = rad(v, p[j] - o);
				if(t < 0) t += 2 * pi;
				if(sign(t * 180 / pi - (a + b)) <= 0) ans[j] = 0;
			}
		} else {
			d = d.rot(2 * pi - b * pi / 180);
			rep(j, 1, n + 1) if(ans[j] && sign((p[j] - o).len() - r) <= 0) {
				db t = rad(v, p[j] - o) * 180 / pi;
				if(sign(t) >= 0 && sign(t - a) <= 0) ans[j] = 0;
			}
		}
		pt = t;
	}
	rep(i, 1, n + 1) cout << ans[i];
	cout << endl;
}


int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	rep(i, 1, T + 1) {
		cout << "Case #" << i << ": ";
		solve();
	}
	return 0;
}
