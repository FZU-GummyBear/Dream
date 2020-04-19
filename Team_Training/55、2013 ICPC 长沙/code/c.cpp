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
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const db eps = 1e-8;

int sign(db x) { return (x > eps) - (x < -eps); }

struct P {
	db x, y;
	P() {}
	P(db x, db y) : x(x), y(y) {}
	db len2() { return x * x + y * y; }
	db len() { return sqrt(len2()); }
	P operator + (const P &c) const { return P(x + c.x, y + c.y); }
	P operator - (const P &c) const { return P(x - c.x, y - c.y); }
};
struct L {
	P a, b;
	L() {}
	L(P a, P b) : a(a), b(b) {}
};

db det(P a, P b) {
	return a.x * b.y - a.y * b.x;
}
db det(P o, P a, P b) {
	return det(a - o, b - o);
}
db dot(P a, P b) {
	return a.x * b.x + a.y * b.y;
}

db disToL(L l, P p) {
	return fabs(det(l.a, p, l.b) / (l.b - l.a).len());
}

int r, R, c, x, y, vx, vy;

int main() {
	while(~scanf("%d%d%d%d%d%d%d", &r, &R, &c, &x, &y, &vx, &vy)) {
		db L1 = R + c, L2 = r + c, L3 = disToL(L(P(x, y), P(x + vx, y + vy)), P(0, 0));
		db ans = 0, dis = 0;
		if(sign(L3)) {
			if(L1 <= L3) ans = 0;
			else if(L2 <= L3) {
				dis = sqrt(L1 * L1 - L3 * L3);
			} else {
				dis = sqrt(L1 * L1 - L3 * L3);
				dis -= sqrt(L2 * L2 - L3 * L3);
			}
			ans = dis * 2 / sqrt(vx * vx + vy * vy);
		} else {
			P p = P(x, y), p2 = P(vx, vy);
			if(sign(dot(p, p2)) > 0) {
				ans = 0;
			} else {
				dis = L1 - L2;
				ans = dis * 2 / sqrt(vx * vx + vy * vy);
			}
		}
		printf("%.4f\n", ans);
	} 
	return 0;
}
