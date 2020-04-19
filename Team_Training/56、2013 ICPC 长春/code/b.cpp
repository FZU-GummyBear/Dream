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
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 205;
__uint128_t f[N], now;
int T, n, vis[N], l, r;

void print(__uint128_t t) {
	vi tmp;
	while (t) tmp.pb(t % 10), t /= 10;
	reverse(all(tmp));
	for (auto v : tmp) cout << v;
	cout << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	n = 186;
	f[1] = f[2] = 1;
	rep(i, 3, n+1) {
		f[i] = f[i-1] + f[i-2];
		//print(f[i]);
	}

	while (cin >> n) {
		now = n * f[93];
		rep(i, 1, 187) vis[i] = 0;
		per(i, 1, 186) if (now >= f[i]) now -= f[i], vis[i] = 1;
		r = 187;
		while (r > 93 && !vis[r]) r--;
		per(i, 93, r+1) cout << vis[i];
		l = 1;
		while (l < 93 && !vis[l]) l++;
		if (l < 93) {
			cout << ".";
			per(i, l, 93) cout << vis[i];
		}
		cout << endl;
		//print(now);
		//de(r - l + 1);
	}
	return 0;
}
