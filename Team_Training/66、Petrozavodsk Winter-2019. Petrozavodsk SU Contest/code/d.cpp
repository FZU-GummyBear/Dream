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
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;
/*
int cc(int x) {
	return 1ll * x * (x - 1) / 2;
}

int calc(int a) {
	if(a < 2 || a > 28) return cc(max(a, 30 - a));
	return cc(a) + cc(30 - a);
}
void tes() {
	rep(a, 0, 31) {
		dd(a), dd(calc(a));
		dd(calc(a) - 354);
		dd(cc(a) - 374);
		de(cc(a) + a * (30 - a) - 374);
	}
}*/
ll calc(ll x) {
	return x * (x - 1) / 2;
}
ll solve(ll a, ll n) {
	return calc(a) + calc(n - a);
}
bool check(ll b, ll c, db &l, db &r) {
	ll det = b * b - 4 * c;
	if(det < 0) return 0;
	l = (- b - sqrt(det)) / 2;
	r = (- b + sqrt(det)) / 2;
	//dd(l), de(r);
	return 1;
}
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	ll n, k; cin >> n >> k;
	db l1, l2, r1, r2;
	if(!check(-1, -2 * k, l1, r1) || !check(1 - 2 * n, 2 * k, l2, r2)) cout << -1 << endl;
	else {
		ll l = ceil(max(l1, l2));
		ll r = floor(min(r1, r2));
		if(l > r) cout << -1 << endl;
		else cout << max(solve(l, n), solve(r, n)) << endl;
	}
	return 0;
}
