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
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 303030;

int n, m, jc[N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	jc[0] = 1;
	rep(i, 1, n + 1) jc[i] = jc[i - 1] * 1ll * i % m;
	int ans = 0;
	rep(len, 1, n + 1) {
		int res = (n - len + 1) * 1ll * jc[len] % m * jc[n - len + 1] % m;
		if((ans += res) >= m) ans -= m;
	}
	cout << ans << endl;
	return 0;
}
