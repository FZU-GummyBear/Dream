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

const int N = 1 << 21, S = 1 << 20;
ll f[N], g[N], ans;
int n, m, T, x;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m;
		rep(j, 0, S) f[j] = 0;
		f[0] = 1; ans = 0;
		rep(i, 1, n+1) {
			cin >> x;
			rep(j, 0, S) g[j] = f[j];
			rep(j, 0, S) if (f[j]) g[j ^ x] += f[j]; 
			rep(j, 0, S) f[j] = g[j];
		}
		rep(j, m, S) ans += f[j];
		cout << "Case #" << cas + 1 << ": " << ans << endl;
	}
	return 0;
}
