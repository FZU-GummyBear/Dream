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
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1e4 + 10;
int ans, x[N], y[N], l1[N], l2[N], T, n, R;
ll s[1010101], now;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> R >> n;
		rep(i, 1, R+1) s[i] = 0;
		rep(i, 1, n+1) {
			cin >> x[i] >> y[i] >> l1[i] >> l2[i];
			s[x[i] + 1] += l2[i];
			s[x[i] + l1[i] + 1] -= l2[i];
		}
		rep(i, 1, R+1) {
			now += s[i];
			s[i] = s[i-1] + now;
		}
		rep(i, 1, R+1) if (s[i] + s[i] >= s[R]) {
			rep(j, i, R+1) if (s[j] == s[i]) ans = j; else break;
			break;
		}
		cout << ans << endl;
	}
	return 0;
}
