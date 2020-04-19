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

const ll tmp = 101010;
const __int128 ttmp = 1e15;
const db eps = 1e-8;

int sign(db x) { return (x > eps) - (x < -eps); }

int n, m;
int dx[] = {1, -1, -1, 1};
int dy[] = {1, 1, -1, -1};

struct P {
	int x, y, dir; 
	P(int x = 0, int y = 0, int dir = 0) : x(x), y(y), dir(dir) {}
	void read() { 
		scanf("%d%d", &x, &y); dir = 0; 
		int nx = x + 1, ny = y + 1;
		if(nx > n || ny > m) {
			if(nx > n) dir ^= 1;
			if(ny > m) dir = 3 - dir;
		}
	}
	inline ll id() { return (dir + 1) * tmp * tmp + (x + 1) * tmp + y + 1; }
	int tim() {
		int ans = 101010;
		if(dir == 0 || dir == 3) ans = min(ans, n - x);
		else ans = min(ans, x);
		if(dir == 0 || dir == 1) ans = min(ans, m - y);
		else ans = min(ans, y);
		return ans;
	}
	P go(int t) {
		assert(t);
		int nx = x + t * dx[dir];
		int ny = y + t * dy[dir];
		int ndir = dir;
		int tx = nx + dx[dir], ty = ny + dy[dir];
		if(tx < 0 || tx > n) ndir ^= 1;
		if(ty < 0 || ty > m) ndir = 3 - ndir;
		return P(nx, ny, ndir);
	}
	P operator - (const P &c) const { return P(x - c.x, y - c.y); }
	void print() { dd(x), dd(y), de(dir); }
}a, b;
struct L {
	P a, b;
	L() {}
	L(P a, P b) : a(a), b(b) {}
};
ll det(P a, P b) { return 1ll * a.x * b.y - 1ll * a.y * b.x; }
ll dot(P a, P b) { return 1ll * a.x * b.x + 1ll * a.y * b.y; }

map<__int128, bool> vis;
bool check(db x, db y, L l) {
	l.a.x *= 2; l.a.y *= 2;
	l.b.x *= 2; l.b.y *= 2;
	P p(x * 2 + 0.5, y * 2 + 0.5);
	return det(p - l.a, l.b - l.a) == 0 && dot(p - l.a, p - l.b) <= 0;
}
bool check(L l1, L l2) {
	ll s1 =  det(l2.b - l2.a, l1.a - l2.a);
	ll s2 = -det(l2.b - l2.a, l1.b - l2.a);
	if(s1 + s2 == 0) return 0;
	db x = (l1.a.x * 1. * s2 + l1.b.x * 1. * s1) / (s1 + s2);
	db y = (l1.a.y * 1. * s2 + l1.b.y * 1. * s1) / (s1 + s2);
	if(check(x, y, l1) && check(x, y, l2) && sign(fabs(l1.a.x - x) - fabs(l2.a.x - x)) == 0) {
		printf("%.1f %.1f\n", x, y);
		return 1;
	}
	return 0;
}
bool check0(P a, P b) {
	int t = min(abs(a.x - b.x), abs(a.y - b.y));
	if(a.x + dx[a.dir] * t == b.x && a.y + dy[a.dir] * t == b.y && abs(a.dir - b.dir) == 2) return 1;
	return 0;
}
void solve() {
	scanf("%d%d", &n, &m);
	a.read(); b.read();
	vis.clear();
	while(1) {
		__int128 ha = a.id() * ttmp + b.id();
		if(vis.count(ha)) {
			printf("Collision will not happen.\n");
			return ;
		}
		vis[ha] = 1;
		if(check0(a, b)) {
			int x = a.x + b.x;
			int y = a.y + b.y;
			printf("%.1f %.1f\n", x / 2., y / 2.);
			return ;
		}
		int t = min(a.tim(), b.tim());
		P na = a.go(t);
		P nb = b.go(t);
		if(check(L(a, na), L(b, nb))) return ;
		a = na, b = nb;
	}
}

int main() {
	int T; scanf("%d", &T);
	rep(i, 1, T + 1) {
		printf("Case #%d:\n", i);
		solve();
	}
	return 0;
}

