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

const int N = 2020, P = 2017;

int n, a[N], f[N];
ll c[N][N];

int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return (a < 0 ? a + P : a);
}
int mul(int a, int b) {
	return a * b % P;
}

int C(int n, int m) {
	if(n < m) return 0;
	n %= 2017;
	return c[n][m];
}

int G(int x, int y) {
	return C(x + y, x);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	rep(i, 0, N) c[i][0] = c[i][i] = 1;
	rep(i, 0, N) rep(j, 1, i) c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
	ll ans = 0;
	rep(k, 16, 31) {
		rep(i, 0, 31 - k) {
			ans += c[k][i];
		}
	}
	de(ans);
	cin >> n;
	rep(i, 1, n + 1) cin >> a[i];
	a[n + 1] = a[n]; ++n;
	per(i, 1, n) a[i] = min(a[i], a[i + 1]);
	f[1] = 1;
	rep(i, 2, n + 1) {
		f[i] = G(i - 1, a[i]);
		int t = 0;
		rep(j, 1, i) {
			t = add(t, mul(G(i - j, a[i] - a[j] - 1), f[j]));
		}
		f[i] = add(f[i], -t);
	}
	cout << f[n] << endl;
	return 0;
}
