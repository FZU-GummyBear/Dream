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
typedef vector<int> vi;
typedef double db;

ll n , m, k;
int T, ans;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m >> k;
		ans = 0;
		rep(i, 0, 100) if (pw(i) >= n) { ans += i; break;}
		rep(i, 0, 100) if (pw(i) >= m) { ans += i; break;}
		rep(i, 0, 100) if (pw(i) >= k) { ans += i; break;}
		cout << "Case #" << cas + 1 << ": " << n * m * k - 1 << " " << ans << endl;
	}
	return 0;
}
