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

const int N = 22;

int n, m, t[N];
char s[N][N];

struct HM {
	static const int INF = pw(18) - 1, N = 8e5;
	int hd[INF + 1], ne[N], s[N], L, f[N], sav[N];
	void ini0() { memset(hd, -1, sizeof(hd)); }
	void init() { rep(i, 0, L) hd[sav[i] & INF] = -1; L = 0; }
	void upd(int u, int v) {
		int p = u & INF;
		for(int i = hd[p]; ~i; i = ne[i]) if(u == s[i]) {
			f[i] = min(f[i], v);
			return ;
		}
		s[L] = sav[L] = u; f[L] = v; ne[L] = hd[p]; hd[p] = L++;
	}
}hm[2];

int solve() {
	rep(i, 1, n + 1) cin >> (s[i] + 1);
	rep(i, 1, n + 1) {
		rep(l, 1, m + 1) if(s[i][l] == 'L') {
			rep(r, l + 1, m + 1) if(s[i][r] == 'W') return -1;
		}
	}
	rep(i, 1, n + 1) {
		bool o = 0;
		rep(j, 1, m + 1) {
			if(s[i][j] == 'L') o = 1;
			else if(o) s[i][j] = '#';
		}
		o = 0;
		per(j, 1, m + 1) {
			if(s[i][j] == 'W') o = 1;
			else if(o) s[i][j] = '#';
		}
		rep(j, 1, m + 1) if(s[i][j] == 'L' || s[i][j] == 'W') s[i][j] = '#';
	}
	if(n == 1) {
		int mi = 10;
		rep(j, 1, m + 1) if(s[1][j] != '#') mi = min(mi, s[1][j] - '0');
		if (mi == 10) mi = -1;
		return mi;
	}
	int o = 0; hm[o].init(); hm[o].upd(0, 0);
	int ans = INT_MAX;
	rep(i, 1, n + 1) {
		rep(j, 0, hm[o].L) hm[o].s[j] <<= t[1];
		rep(j, 1, m + 1) {
			o ^= 1; hm[o].init();
			rep(k, 0, hm[o ^ 1].L) {
				int x = hm[o ^ 1].s[k], y = hm[o ^ 1].f[k];
				if(x >> t[m + 1]) continue;
				int p = x >> t[j - 1] & 3, q = x >> t[j] & 3;
				int tx = x ^ (p << t[j - 1]) ^ (q << t[j]);
				if(s[i][j] == '#') {
					if(!p && !q) hm[o].upd(x, y);
				} else {
					int c = s[i][j] - '0';
					if(!p && !q) {
						hm[o].upd(x | (1 << t[j - 1]) | (2 << t[j]), y + c);
						if(i == 1) hm[o].upd(x | (3 << t[j - 1]), y + c);
						hm[o].upd(x, y);
					} else if(!p || !q) {
						int k = max(p, q);
						hm[o].upd(x, y + c);
						hm[o].upd(x ^ (k << t[j - 1]) ^ (k << t[j]), y + c);
						if(k == 3) {
							if(!tx && i == n) ans = min(ans, y + c);
						} else {
							/*
							int now = 1, nx = tx;
							int tc = c;
							for(int _ = k == 1 ? j + 1 : j - 2; ; k == 1 ? ++_ : --_) {
								int c = x >> t[_] & 3;
								if(c == k) ++now;
								if(c == (k ^ 3)) --now;
								if(!now) {
									hm[o].upd(nx ^ (k << t[_]), y + tc);
									break;
								}
							}*/
						}
					} else if(p == 1 && q == 2) {
					} else if(p == 2 && q == 1) {
						hm[o].upd(tx, y + c);
					} else if(min(p, q) <= 2) {
						int k = min(p, q), now = 1, nx = tx;
						int tc = c;
						for(int _ = k == 1 ? j + 1 : j - 2; ; k == 1 ? ++_ : --_) {
							int c = x >> t[_] & 3;
							if(c == k) ++now;
							if(c == (k ^ 3)) --now;
							if(!now) {
								hm[o].upd(nx ^ ((3 ^ p ^ q) << t[_]), y + tc);
								break;
							}
						}
					}
				}
			}
		}
	}
	if(ans == INT_MAX) ans = -1;
	return ans;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	hm[0].ini0();
	hm[1].ini0();
	rep(i, 0, N) t[i] = i + i;
	while(cin >> n >> m) cout << solve() << endl;
	return 0;
}
