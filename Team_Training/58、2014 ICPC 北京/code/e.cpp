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

const int N = 200 + 7;

int n, mx, my;
struct Node { int x, y; }nd[N * N];

int rig[N][N], up[N][N], ini[N][N];
ll sum[N][N], yb[N][N][N], jb[N][N][N];
bool vis[N][N];

ll solve() {
	cin >> n; mx = my = 0;
	rep(i, 1, n + 1) {
		cin >> nd[i].x >> nd[i].y;
		mx = max(mx, nd[i].x);
		my = max(my, nd[i].y);
	}
	rep(i, 1, mx + 1) rep(j, 1, my + 1) vis[i][j] = 0;
	rep(i, 1, n + 1) vis[nd[i].x][nd[i].y] = 1;
	per(i, 1, mx + 1) per(j, 1, my + 1) {
		if(vis[i][j]) {
			rig[i][j] = (i == mx ? 0 : rig[i + 1][j]) + 1;
			 up[i][j] = (j == my ? 0 :  up[i][j + 1]) + 1;
		} else {
			rig[i][j] = up[i][j] = 0;
		}
	}
	rep(i, 1, mx + 1) rep(j, 1, my + 1) {
		if(rig[i][j]) --rig[i][j];
		if( up[i][j]) -- up[i][j];
	}
	per(i, 1, mx + 1) per(j, 1, my + 1) {
		if(i == mx || j == my) {
			sum[i][j] = 0;
		} else {
			sum[i][j] = sum[i + 1][j] + sum[i][j + 1] - sum[i + 1][j + 1];
			if(vis[i][j]) {
				rep(a, 1, rig[i][j] + 1) sum[i][j] += ini[a][up[i][j]];
			}
		}
//		dd(i), dd(j), dd(up[i][j]), dd(rig[i][j]), de(sum[i][j]);
	}
	rep(y, 1, my + 1) per(i, 1, mx + 1) per(j, 1, my + 1) {
		if(i == mx || j == my) {
			jb[y][i][j] = 0;
		} else {
			jb[y][i][j] = jb[y][i + 1][j] + jb[y][i][j + 1] - jb[y][i + 1][j + 1];
			if(vis[i][j] && 1 <= y - 1 - j && y - 1 - j <= up[i][j]) {
				jb[y][i][j] += ini[y - 1 - j][rig[i][j]];
			}
		}
		if(y == 1) {
			yb[y][i][j] = 0;
		} else {
			yb[y][i][j] = yb[y - 1][i][j] + jb[y][i][j];
		}
	}
	ll ans = 0;
	rep(i, 1, n + 1) {
		int x = nd[i].x, y = nd[i].y;
		rep(a, 1, rig[x][y] + 1) {
			ll A = ini[a][up[x][y]];
			ll B = 0;
			if(x + 1 <= mx && y + 1 <= my) B += sum[x + 1][y + 1];
			if(x + a + 1 <= mx) B += sum[x + a + 1][1];
			if(x + a + 1 <= mx && y + 1 <= my) B -= sum[x + a + 1][y + 1];
			int lx = x, rx = x + a + 1;
			int ly = 1, ry = y - 2 + 1;
			if(lx <= mx && ly <= my) B += yb[y][lx][ly];
			if(rx <= mx && ry <= my) B += yb[y][rx][ry];
			if(lx <= mx && ry <= my) B -= yb[y][lx][ry];
			if(rx <= mx && ly <= my) B -= yb[y][rx][ly];
			ans += A * B;
		}
	}
	return ans * 2;
}

void init() {
	rep(a, 1, N) {
		ini[a][1] = 1;
		rep(B, 2, N) ini[a][B] = ini[a][B - 1] + (__gcd(a, B) == 1);
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
//	db x = sizeof(jb) * 2. / 1024;
//	de(x);
	init();
	int T; cin >> T;
	rep(i, 1, T + 1) cout << "Case #" << i << ": " << solve() << endl;
	return 0;
}
