#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl '\n'
#define pw(x) (1ll << (x))
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1010, P = 1e9 + 7;

int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a;
}
int mul(int a, int b) {
	return 1ll * a * b % P;
}

int n, m, va[N][N], vb[N][N];

struct HM {
	static const int INF = pw(18) - 1, N = 8e5;
	int hd[INF + 1], ne[N], s[N], L, f[N], h[N];
	void ini0() {
		memset(hd, -1, sizeof(hd));
		L = 0;
	}
	void init() {
		rep(i, 0, L) hd[s[i] & INF] = -1;
		L = 0;
	}
	void upd(int u, int v, int w) {
		int p = u & INF;
		for(int i = hd[p]; ~i; i = ne[i]) if(s[i] == u) {
			if(v < f[i]) {
				f[i] = v;
				h[i] = w;
			} else if(v == f[i]) {
				h[i] = add(h[i], w);
			}
			return ;
		}
		s[L] = u; f[L] = v; h[L] = w; ne[L] = hd[p]; hd[p] = L++;
	}
}hm[2];

void solve() {
	cin >> n >> m;
	rep(i, 1, n + 1) rep(j, 1, m) cin >> va[i][j];
	rep(i, 1, n) rep(j, 1, m + 1) cin >> vb[i][j];
	int o = 0; hm[o].init(); hm[o].upd(0, 0, 1);
	rep(i, 1, n + 1) rep(j, 1, m + 1) {
		o ^= 1; hm[o].init();
		rep(k, 0, hm[o ^ 1].L) {
			int sta = hm[o ^ 1].s[k], ssta = sta;
			int cnt[11] = {0};
			int a[11] = {0}; rep(t, 1, m + 1) a[t] = sta % 8, sta /= 8, ++cnt[a[t]];
//			rep(t, 0, m + 1) cout << a[t] << " "; cout << endl;
			int sx = 0, tx = 1;
			int sy = 0, ty = 1;
			if(a[j - 1] == 0) tx = 0;
			if(a[j] == 0)     ty = 0;
			if(i > 1 && cnt[a[j]] == 1) sy = 1;
			//dd(sx), dd(tx), dd(sy), de(ty);
			rep(x, sx, tx + 1) rep(y, sy, ty + 1) {
				//dd(x), de(y);
				int ta[11]; rep(t, 1, m + 1) ta[t] = a[t];
				int F, H;
				if(x == 0 && y == 0) {
					ta[j] = 8;
					F = 0, H = 1;
				} else if(x == 0 && y == 1) {
					hm[o].upd(ssta, hm[o ^ 1].f[k] + vb[i - 1][j], hm[o ^ 1].h[k] * 2ll % P);
					continue;
				} else if(x == 1 && y == 0) {
					ta[j] = ta[j - 1];
					F = va[i][j - 1], H = 2;
				} else {
					if(a[j - 1] == a[j]) continue;
					rep(t, 1, m + 1) if(ta[t] == a[j]) ta[t] = a[j - 1];
					F = va[i][j - 1] + vb[i - 1][j];
					H = 3;
				}
				int L = 0, vis[11] = {0};
				rep(t, 1, m + 1) if(ta[t]) {
					if(vis[ta[t]]) {
						ta[t] = vis[ta[t]];
					} else {
						ta[t] = vis[ta[t]] = ++L;
					}
				}
				int ns = 0;
				per(t, 1, m + 1) ns = ns * 8 + ta[t];
				hm[o].upd(ns, hm[o ^ 1].f[k] + F, hm[o ^ 1].h[k] * 1ll * H % P);
			}
		}
	}
	int sta = 0;
	rep(i, 1, m + 1) sta = sta * 8 + 1;
	rep(i, 0, hm[o].L) if(hm[o].s[i] == sta) {
		cout << hm[o].f[i] << " " << hm[o].h[i] << endl;
		return ;
	}
	de(0);
	//assert(0);
}

int main() {
//	std::ios::sync_with_stdio(0);
//	std::cin.tie(0);
	hm[0].ini0();
	hm[1].ini0();
	int T; cin >> T;
	rep(ca, 1, T + 1) {
		cout << "Case #" << ca << ": ";
		solve();
	}
	return 0;
}
