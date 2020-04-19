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

const int N = 2020;

int n, a[N];

void solve() {
	cin >> n;
	rep(i, 1, n + 1) cin >> a[i];
	ll ans = 0;
	unordered_map<int, int> cnt;
	per(j, 1, n + 1) {
		rep(i, 1, j) {
			int k = 2 * a[j] - a[i];
			if(cnt.count(k)) ans += cnt[k];
		}
		++cnt[a[j]];
	}
	cout << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
