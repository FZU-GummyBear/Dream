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
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

ll f(ll x) {
	ll res = 0;
	while(x) {
		ll c = x % 10; x /= 10;
		res += c * c;
	}
	return res;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	ll k, a, b;
	cin >> k >> a >> b;
	ll ans = 0, to = min(2020ll, b / k);
	rep(i, 1, to + 1) {
		ll n = i * k;
		if(n < a || n > b) continue;
		if(k * f(n) == n) ++ans;
	}
	cout << ans << endl;
	return 0;
}
