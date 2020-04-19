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

int T;

ll a, b, ans;

ll gcd(ll a, ll b) {
	if (b == 0) return a;
	ans += a / b;
	return gcd(b, a % b);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> a >> b;
		ans = 0;
		if (a < b) swap(a, b);

		if (b != 0) gcd(a, b);
		else {
			if (a == 0) ans = 0;
			else ans = 1;
		}
		cout << "Case #" << cas + 1 << ": " << ans + 1 << endl;
	}

	return 0;
}
