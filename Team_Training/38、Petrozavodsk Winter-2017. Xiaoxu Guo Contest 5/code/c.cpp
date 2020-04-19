#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " " 
#define endl '\n'
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 55, M = 2020202, P = 4;

int n, m, f[N][M];
vi g[N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, m + 1) {
		int u, v; cin >> u >> v;
		if(u > v) swap(u, v);
		g[v].pb(u);
	}
	int to = min(13, n);
	int m = 1; rep(i, 0, to) m *= 3;
	f[0][0] = 1;
	rep(i, 0, n) rep(j, 0, m) if(f[i][j]) {
		int col[13], x = j, nj = j * 3 % m;
		rep(k, 0, to) col[k] = x % 3, x /= 3;
		rep(o, 0, 3) {
			bool ok = 1;
			if(o <= 1) {
				for(auto u : g[i + 1]) if(col[i - u] != 2 && col[i - u] != o) { ok = 0; break; }
			}
			if(!ok) continue;
			(f[i + 1][nj + o] += f[i][j]) %= 4;
		}
	}
	int ans = 0;
	rep(j, 0, m) if(f[n][j]) {
	//	int x = j; 
//		rep(i, 0, 3) cout << x % 3 << " ", x /= 3; de(f[n][j]);
		ans += f[n][j];
	}
	--ans;
	assert(ans % 2 == 0);
	cout << (ans % 4 == 2) << endl;
	return 0;
}
