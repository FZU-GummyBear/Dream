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
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define pw(x) (1ll << (x))
#define endl '\n'
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 404040, INF = 2e9 + 55;

struct P {
	int x, y;
	P(int x = 0, int y = 0) : x(x), y(y) {}
	void print() {
	}
};
struct Node {
	int lx, ly, rx, ry;
	vector<P> ps;
	void read() { 
		scanf("%d%d%d%d", &lx, &ly, &rx, &ry); 
		ps = vector<P>(4);
		ps[0] = P(lx, ly);
		ps[1] = P(lx, ry);
		ps[2] = P(rx, ly);
		ps[3] = P(rx, ry);
	}
	void gao() {
		lx = rx = ps[0].x;
		ly = ry = ps[0].y;
		for(auto p : ps) {
			lx = min(lx, p.x);
			ly = min(ly, p.y);
			rx = max(rx, p.x);
			ry = max(ry, p.y);
		}
	}
};

int n;
vector<Node> vec, tmp;
vector<pair<pii, int> > ans;
vi xs, ys;
vector<pii> kl[N], kr[N];
ll rd[N];

int F(int x, const vi &v) {
	return lower_bound(all(v), x) - v.begin();
}

bool check() {
	xs.clear(); ys.clear();
	for(auto u : vec) {
		for(auto v : u.ps) {
			xs.pb(v.x);
			ys.pb(v.y);
		}
	}
	for(auto u : tmp) {
		for(auto v : u.ps) {
			xs.pb(v.x);
			ys.pb(v.y);
		}
	}
	sort(all(xs));
	xs.erase(unique(all(xs)), xs.end());
	sort(all(ys));
	ys.erase(unique(all(ys)), ys.end());
	rep(i, 0, sz(xs)) kl[i].clear(), kr[i].clear();
	for(auto u : vec) {
		kl[F(u.lx, xs)].pb(mp(F(u.ly, ys), F(u.ry, ys)));
		kl[F(u.rx, xs)].pb(mp(F(u.ly, ys), F(u.ry, ys)));
	}
	for(auto u : tmp) {
		kr[F(u.lx, xs)].pb(mp(F(u.ly, ys), F(u.ry, ys)));
		kr[F(u.rx, xs)].pb(mp(F(u.ly, ys), F(u.ry, ys)));
	}
	ll xx = 0, yy = 0;
	rep(i, 0, sz(xs)) {
		for(auto u : kl[i]) xx ^= rd[u.fi] ^ rd[u.se];
		for(auto u : kr[i]) yy ^= rd[u.fi] ^ rd[u.se];
		if(xx != yy) return 0;
	}
	return 1;
}

P gao(P p, ll a, ll b, ll c) {
	if(a == 0) {
		return P(p.x, 2 * c / b - p.y);
	} else if(b == 0) {
		return P(2 * c / a - p.x, p.y);
	} else if(a > 0 && b > 0) {
		ll A = 2 * c - a * p.x - b * p.y;
		ll B = p.x - p.y;
		ll y = (A - a * B) / (a + b);
		return P(y + B, y);
	} else {
		ll A = 2 * c - a * p.x - b * p.y;
		ll B = p.x + p.y;
		ll y = (a * B - A) / (a - b);
		return P(B - y, y);
	}
}
void gao(int a, int b) {
	ll ma = -INF, mi = INF;
	for(auto u : vec) {
		for(auto v : u.ps) {
			ll t = a * v.x + b * v.y;
			ma = max(ma, t);
			mi = min(mi, t);
		}
	}
	ll c = ma + mi;
	if(c & 1) {
		a *= 2; b *= 2;
	} else {
		c /= 2;   
	}
	rep(i, 0, n) {
		rep(j, 0, 4) {
			tmp[i].ps[j] = gao(vec[i].ps[j], a, b, c);
		}
		tmp[i].gao();
	}
	if(check()) ans.pb(mp(mp(a, b), c));
}

void solve() {
	scanf("%d", &n);
	vec = vector<Node>(n);
	tmp = vector<Node>(n);
	ans.clear();
	for(auto &u : tmp) u.ps = vector<P>(4);
	rep(i, 0, n) vec[i].read();
	gao(1, 0);
	gao(0, 1);
	gao(1, 1);
	gao(1, -1);
	sort(all(ans));
	reverse(all(ans));
	cout << sz(ans) << endl;
	rep(i, 0, sz(ans)) {
		auto u = ans[i];
		printf("%d %d %d%c", u.fi.fi, u.fi.se, u.se, " \n"[i == sz(ans) - 1]);
	}
	if(!sz(ans)) cout << endl;
}

int main() {
	srand(time(0));
	rep(i, 0, N) {
		rd[i] = rand() * 1ll * rand();
		if(i) rd[i] ^= rd[i - 1];
	}
	int T; scanf("%d", &T);
	while(T--) solve();
	return 0;
}
