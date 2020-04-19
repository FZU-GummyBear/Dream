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
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 22;

int n, m, ok[N][N], t[N];
char s[N][N];

struct HM {
	static const int INF = pw(18) - 1, N = 8e5;
	int hd[INF + 1], ne[N], s[N], L, f[N], sav[N];
	void ini0() { memset(hd, -1, sizeof(hd)); }
	void init() {
		rep(i, 0, L) hd[sav[i] & INF] = -1;
		L = 0;
	}
	void upd(int u, int v) {
		int p = u & INF;
		for(int i = hd[p]; ~i; i = ne[i]) if(u == s[i]) {
			f[i] = min(f[i], v);
			return ;
		}
		s[L] = sav[L] = u; f[L] = v; ne[L] = hd[p]; hd[p] = L++;
	}
}hm[2];

void gao() {
	per(i, 1, n + 2) per(j, 1, m + 2) {
		ok[i][j] = 1;
		if(s[i - 1][j - 1] == 'o') return ;
	}
}
bool check(int x, int y, int cnt) {
	if(s[x][y] == 'o') return cnt % 2 == 1;
	if(s[x][y] == 'x') return cnt % 2 == 0;
	return 1;
}
int solve() {
	cin >> n >> m;
	rep(i, 0, N) rep(j, 0, N) s[i][j] = ' ';
	rep(i, 1, n + 1) cin >> (s[i] + 1);
	memset(ok, 0, sizeof(ok));
	gao();
	int ans = 1e9, inf = 1e9;
	int o = 0; hm[o].init(); hm[o].upd(0, 0);
	++n, ++m;
	rep(i, 1, n + 1) {
		rep(j, 0, hm[o].L) hm[o].s[j] <<= t[1];
		rep(j, 1, m + 1) {
			o ^= 1; hm[o].init();
			rep(k, 0, hm[o ^ 1].L) {
				int x = hm[o ^ 1].s[k];
				if(x >> t[m + 1]) continue;
				int p = x >> t[j - 1] & 3, q = x >> t[j] & 3;
				int tx = x ^ (p << t[j - 1]) ^ (q << t[j]);
				int y = hm[o ^ 1].f[k];
				int cnt = 0; rep(_, 0, j - 1) cnt += (x >> t[_] & 3) > 0;
				if(!p && !q) {
					if(check(i, j, cnt + 1)) hm[o].upd(x | (1 << t[j - 1]) | (2 << t[j]), y);
					if(check(i, j, cnt)) hm[o].upd(x, y);
				} else if(!p || !q) {
					if(!p) {
						if(check(i, j, cnt)) hm[o].upd(x, y + 1);
						if(check(i, j, cnt + 1)) hm[o].upd(x ^ ((p | q) << t[j - 1]) ^ ((p | q) << t[j]), y + 1);
					} else {
						if(check(i, j, cnt + 1)) hm[o].upd(x, y + 1);
						if(check(i, j, cnt)) hm[o].upd(x ^ ((p | q) << t[j - 1]) ^ ((p | q) << t[j]), y + 1);
					}
				} else if(p == q) {
					int now = 0, nx = tx;
					for(int _ = p == 1 ? j + 1 : j - 2; ; p == 1 ? ++_ : --_) {
						int c = x >> t[_] & 3;
						if(!c) continue;
						c == p ? ++now : --now;
						if(now == -1) {
							if(check(i, j, cnt)) hm[o].upd(nx ^ (3 << t[_]), y + 2);
							break;
						}
					}
				} else if(p == 1 && q == 2) {
					if(ok[i][j] && !tx && check(i, j, cnt)) ans = min(ans, y + 2);
				} else if(p == 2 && q == 1) {
					if(check(i, j, cnt)) hm[o].upd(tx, y + 2);
				}
			}
		}
	}
	if(ans == inf) ans = -1;
	return ans;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	rep(i, 0, N) t[i] = i + i;
	hm[0].ini0();
	hm[1].ini0();
	int T; cin >> T;
	rep(i, 1, T + 1) cout << "Case #" << i << ": " << solve() << endl;
	return 0;
}
