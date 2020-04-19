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

const int N = 30303, M = 2;

int n;
vector<pair<ll, int> > ans;

int L, ne[N * 33][M], rt;
bool tg[N * 33];

void init() {
	rep(i, 0, L + 1) ne[i][0] = ne[i][1] = tg[i] = 0;
	L = 0;
	rt = ++L;
}
void add(ll val, int len) {
	int p = rt;
	per(i, 32 - len, 32) {
		int c = val >> i & 1;
		if(!ne[p][c]) ne[p][c] = ++L;
		p = ne[p][c];
	}
	tg[p] = 1;
}

void dfs(int p, int dep, ll val) {
	if(tg[p] || dep > 31) return ;
	rep(c, 0, 2) {
		if(ne[p][c]) {
			dfs(ne[p][c], dep + 1, val + c * pw(31 - dep));
		} else {
			ans.pb(mp(val + c * pw(31 - dep), dep + 1));
		}
	}
}

void solve() {
	cin >> n;
	if(!n) {
		cout << 1 << endl;
		cout << "0.0.0.0/0" << endl;
		return ;
	}
	init(); ans.clear();
	rep(i, 1, n + 1) {
		char s[33]; cin >> s;
		vector<string> vec;
		for(char * p = strtok(s, "./"); p; p = strtok(NULL, "./")) vec.pb(p);
		if(sz(vec) == 4) vec.pb("0");
		ll x = 0, p = 0;
		rep(j, 0, 5) {
			ll y = 0;
			rep(t, 0, sz(vec[j])) y = y * 10 + vec[j][t] - '0';
			if(j < 4) x = x * 256 + y;
			else p = y;
		}
		add(x, p);
	}
	dfs(rt, 0, 0);
	cout << sz(ans) << endl;
	for(auto u : ans) {
		ll x = u.fi; int y = u.se, c;
		c = 0; per(i, 24, 32) c = c * 2 + (x >> i & 1); cout << c << ".";
		c = 0; per(i, 16, 24) c = c * 2 + (x >> i & 1); cout << c << ".";
		c = 0; per(i, 8, 16) c = c * 2 + (x >> i & 1); cout << c << ".";
		c = 0; per(i, 0, 8) c = c * 2 + (x >> i & 1); cout << c << "/";
		cout << y << endl;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	rep(i, 1, T + 1) {
		cout << "Case #" << i << ":" << endl;
		solve();
	}
	return 0;
}
