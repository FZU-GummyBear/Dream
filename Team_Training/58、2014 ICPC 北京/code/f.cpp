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

const int P = 1e9 + 7;

int f[2][2][2], g[2][2][2];

int T, n, m, a[100][100], x, ans, k;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m;
		rep(i, 1, m+1) {
			rep(j, 1, n+1) a[i][j] = 0;
			cin >> k;
			rep(j, 0, k) {
				cin >> x;
				a[i][x] = 1;
			}
		}
		ans = 0;
		rep(i, 1, n+1)
			rep(j, 1, n+1)
				rep(k, 1, n+1) {
					memset(f, 0, sizeof(f));
					f[0][0][0] = 1;
					rep(l, 1, m+1) {
						int o1 = a[l][i], o2 = a[l][j], o3 = a[l][k];
						memcpy(g, f, sizeof(f));
						rep(t1, 0, 2) 
							rep(t2, 0, 2)
								rep(t3, 0, 2) (f[t1 ^ o1][t2 ^ o2][t3 ^ o3] += g[t1][t2][t3]) %= P;
					}
					(ans += f[1][1][1]) %= P;
				}
		cout << "Case #" << cas + 1 << ": " << ans << endl;
	}
	return 0;
}
