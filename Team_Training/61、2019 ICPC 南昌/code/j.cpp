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

const int P = 998244353;
const int N = 1e5 + 7;
int ans[N], ne[100][100], col[100][100], f[N][65], x, a[100], n, m, tmp[100], tmp2[100], p[N], vis[N];
bool ban[1000], ok[100][100];

bool check(int x, int y) {
	rep(i, 0, 3) a[i] = y % 4, y /= 4;
	reverse(a, a+3);
	rep(i, 3, 6) a[i] = x % 4, x /= 4;
	reverse(a+3, a+6);
	rep(i, 0, 3) {
		int t = 0;
		rep(j, 0, 4) t = t * 4 + a[i + j];
		if (ban[t]) return 0;
	}
	return 1;
}

int kpow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = 1ll * res * a % P;
		a = 1ll * a * a % P;
		b >>= 1;
	}
	return res;
}

struct mat{
	static const int N = 64;
	int a[N][N];
	mat() {memset(a, 0, sizeof(a));}
	mat operator * (const mat & c) {
		mat r;
		rep(k, 0, N) 
			rep(i, 0, N) if (a[i][k]) 
				rep(j, 0, N) if (c.a[k][j]) 
					r.a[i][j] = (r.a[i][j] + 1ll * a[i][k] * c.a[k][j]) % P;
		return r;
	}
} w[20];

void dfs(int d, int lim) {
	if (d == lim) {
		rep(i, lim, 6) a[i] = a[i-lim];
		int ok = 1;
		rep(i, 0, 3) {
			int t = 0;
			rep(j, 0, 4) t = t * 4 + a[i + j];
			if (ban[t]) ok = 0;
		}
		ans[lim] += ok;
		return;
	}
	rep(i, 0, 4) {
		a[d] = i;
		dfs(d+1, lim);
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, m+1) {
		int t = 0;
		rep(j, 0, 4) cin >> x, t = t * 4 + x;
		ban[t] = 1;
	}
	rep(i, 0, 64) rep(j, 0, 4) {
		ne[i][j] = (i * 4 + j) % 64, col[i][j] = i * 4 + j;
		if (!ban[col[i][j]]) w[0].a[ne[i][j]][i]++;
	}
	rep(i, 1, 20) w[i] = w[i-1] * w[i-1];

	vi tt;
	rep(i, 0, 64) rep(j, 0, 64) ok[i][j] = check(i, j); 
	rep(i, 1, n+1) if (n % i == 0) {
		if (i >= 4) tt.pb(i);
		vis[i] = 1;
	}
	per(i, 1, n) if (vis[i+1]) p[i] = i + 1;else p[i] = p[i+1];

	rep(i, 0, 64) {
		memset(f, 0, sizeof(f));
		f[3][i] = 1;
		rep(j, 3, n) {
			if (p[j] - j <= 200) {
				rep(k, 0, 64) if (f[j][k]){
					rep(l, 0, 4) if (!ban[col[k][l]]){
						int &t = f[j+1][ne[k][l]];
						if ((t += f[j][k]) >= P) t -= P;
					}
				}
			}else {
				int d = 0;
				rep(k, 1, 20) if (pw(k) <= p[j] - j) d = k;else break;
				rep(k, 0, 64) tmp[k] = f[j][k], tmp2[k] = 0;
				rep(k, 0, 64) rep(l, 0, 64) tmp2[k] = (tmp2[k] + 1ll * w[d].a[k][l] * tmp[l]) % P;
				rep(k, 0, 64) f[j + (1 << d)][k] = tmp2[k];
				j += (1 << d);
				j --;
			}
		}
			rep(k, 0, 64) if (ok[i][k]){
		//	de(f[4][k]);
			for (auto j : tt) (ans[j] += f[j][k]) %= P;
		}
	}
	dfs(0, 1);
	dfs(0, 2);
	dfs(0, 3);
	//de(ans[3]);
	//ans[1] = 4;
	//ans[2] = 16;
	//ans[3] = 64;
	//rep(i, 1, n+1) cout << ans[i] << endl;
	int sum = 0;
	rep(i, 1, n+1) (sum += ans[__gcd(i, n)]) %= P;
	cout << 1ll * sum * kpow(n, P - 2) % P << endl;
	return 0;
}
