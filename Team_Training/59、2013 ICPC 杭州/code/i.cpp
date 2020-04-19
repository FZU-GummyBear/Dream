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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define endl '\n'
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 55;
int m, n, w, k[N], col[N][N], cc[N], f[1 << 21], S, x, cnt[N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while (cin >> m >> n >> w) {
		if (m == 0 && n == 0 && w == 0) break;
		rep(i, 0, n) {
			cc[i] = 0; rep(j, 0, m) col[i][j] = 0;
			cin >> k[i];
			rep(j, 0, k[i]) {
				cin >> x; x--;
				col[i][x]++;
			}
			rep(j, 0, m) {
				cc[i] += col[i][j] / w;
				col[i][j] %= w;
			}
		}
		S = pw(n);
		memset(f, -10, sizeof(f));
		f[0] = 0;

		rep(i, 1, S) {
			rep(l, 0, m) cnt[l] = 0;
			rep(j, 0, n) if (!((i >> j) & 1)) {
				rep(l, 0, m) cnt[l] += col[j][l];
			}
			rep(l, 0, m) cnt[l] %= w;
			rep(j, 0, n) if ((i >>  j) & 1) {
				int t = cc[j];
				rep(l, 0, m) t += (col[j][l] + cnt[l]) >= w;
				if (t > 0) f[i] = max(f[i], f[i ^ (1 << j)] + t);
				else f[i] = max(f[i], -f[i ^ (1 << j)] + t);
			}
		}
	//	rep(i, 0, S) dd(i), de(f[i]);
		cout << f[S - 1] << endl;
	}
	return 0;
}
