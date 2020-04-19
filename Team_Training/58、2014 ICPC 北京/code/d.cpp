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

const int N = 250;
int a[N], b[N], n, T;
ll f[N][N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n;
		rep(i, 1, n+1) cin >> a[i];
		rep(i, 1, n+1) cin >> b[i];
		b[0] = b[n + 1] = 0;
		rep(i, 0, n+2) rep(j, 0, n+2) f[i][j] = pw(60);
		rep(len, 2, n+3) {
			rep(l, 0, n+2) {
				int r = l + len - 1;
				if (r > n + 1) break;
				if (len == 2) f[l][r] = 0;
				else {
					rep(k, l+1, r) {
						f[l][r] = min(f[l][r], f[l][k] + f[k][r] + a[k] + b[l] + b[r]);
					}
				}
			}
		}
		cout << "Case #" << cas + 1 << ": " << f[0][n+1] << endl;
	}
	return 0;
}
