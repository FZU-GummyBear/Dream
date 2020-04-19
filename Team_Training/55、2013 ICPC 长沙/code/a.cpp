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

const int N = 1e5 + 20;
ll lim[N], p[N], s[N], ans, x;
int pos, n, m, T;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m;
		rep(i, 1, n+1) {
			cin >> lim[i] >> p[i];
			s[i] = lim[i] * p[i];
		}
		s[n+1] = pw(62);
		per(i, 1, n+1) s[i] = min(s[i], s[i+1]);
		rep(i, 1, m+1) {
			cin >> x;
			pos = lower_bound(lim+1, lim+n+1, x) - lim;
			ans = s[pos];
			ans = min(ans, p[pos - 1] * x);
			cout << ans << endl;
		}
	}
	return 0;
}
