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

const int P = 1e9 + 7;

int kpow(int a, ll b) {
	int r = 1;
	while(b) {
		if(b & 1) r = r * 1ll * a % P;
		a = a * 1ll * a % P;
		b >>= 1;
	}
	return r;
}
bool check(int n, int m) {
	return n % 8 == 4 && m % 2 == 0;
}
void solve() {
	int n, m; cin >> n >> m;
	int ans = kpow(m, (n - 1) * 1ll * (n - 1) - 1);
	if(check(n, m)) ans = ans * 2ll % P;
	cout << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
