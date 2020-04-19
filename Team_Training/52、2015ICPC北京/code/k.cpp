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
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1e5 + 7;
ll f[100][N], n, ans[N];
int a[1000], P, po[1000], len, T, now;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> P;
		len = 0;
		while (n) {
			a[++len] = n % 2;
			n /= 2;
		}
		f[0][0] = 1; po[0] = 1;
		rep(i, 1, len+1) {
			po[i] = po[i-1] * 3 % P;
			rep(j, 0, P) f[i][j] = f[i-1][j];
			rep(j, 0, P) f[i][(j + po[i-1]) % P] += f[i-1][j];
		}
		now = 0;
		rep(i, 0, P) ans[i] = 0;
		per(i, 1, len+1) {
			if (a[i]) {
				rep(k, 0, P) ans[(k + now) % P] += f[i-1][k];
			}
			if (a[i]) {
				now += po[i-1];
				now %= P;
			}
		}
		ans[now]++;
		ans[0]--;
		ll an = 0;
		rep(i, 0, P) an ^= ans[i];
		cout << an << endl;
	}
	return 0;
}
