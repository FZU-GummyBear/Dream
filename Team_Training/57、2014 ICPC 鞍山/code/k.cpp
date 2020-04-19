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

const int N = 3030, P = 1e9 + 7;

int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a;
}
int mul(int a, int b) { return 1ll * a * b % P; }

int kpow(int a, int b) {
	int r = 1;
	while(b) {
		if(b & 1) r = mul(r, a);
		a = mul(a, a);
		b >>= 1;
	}
	return r;
}

struct Po {
	int x, y, i;
	Po(int x = 0, int y = 0) : x(x), y(y) {}
	Po(int x, int y, int i) : x(x), y(y), i(i) {}
	Po rot() { return Po(-y, x, i); }
	bool operator < (const Po &c) const { 
		if(x != c.x) return x < c.x;
		return y < c.y;
	}
	void print() { dd(x), dd(y), de(i); }
	Po operator - (const Po &c) const { return Po(x - c.x, y - c.y); }
	bool operator != (const Po &c) const { return x != c.x || y != c.y; }
};

int n, m, c;
Po p[N], np[N];
bool g[N][N];

int pre[N];

int find(int x) { return x == pre[x] ? x : pre[x] = find(pre[x]); }
void join(int x, int y) { pre[find(x)] = find(y); }

pii check() {
	sort(np + 1, np + 1 + n);
//	rep(i, 1, n + 1) p[i].print(); cout << endl;
//	rep(i, 1, n + 1) np[i].print(); cout << endl;
	pii ans = mp(0, 0);
	Po det = p[1] - np[1];
	rep(i, 2, n + 1) if((p[i] - np[i]) != det) return ans;
//	de(1);
	rep(i, 1, n + 1) rep(j, 1, n + 1) if(g[p[i].i][p[j].i] != g[np[i].i][np[j].i]) return ans;
	rep(i, 1, n + 1) pre[i] = i;
	rep(i, 1, n + 1) join(p[i].i, np[i].i);
	rep(i, 1, n + 1) if(find(i) == i) ++ans.se;
	ans.fi = kpow(c, ans.se);
	ans.se = 1;
	return ans;
}

void solve() {
	cin >> n >> m >> c;
	rep(i, 1, n + 1) cin >> p[i].x >> p[i].y, p[i].i = i, np[i] = p[i];
	rep(i, 1, n + 1) rep(j, 1, n + 1) g[i][j] = 0;
	rep(i, 1, m + 1) {
		int u, v; cin >> u >> v;
		g[u][v] = g[v][u] = 1;
	}
	sort(p + 1, p + 1 + n);
	int fz = kpow(c, n), fm = 1;
	rep(o, 0, 3) {
		rep(i, 1, n + 1) np[i] = np[i].rot();
		pii t = check();
		if(t.se) fz += t.fi, fm++;//, de(t.se);
	}
	cout << mul(fz, kpow(fm, P - 2)) << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
