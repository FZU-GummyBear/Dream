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

const int N = 3e5 + 10;
int a[N], now, n, cnt;
ll ans;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n+1) cin >> a[i], ans += a[i] / 2, a[i] %= 2;
	cnt = 0;
	rep(i, 1, n+1) if (a[i] == 1) {
		if (cnt == 0) cnt = 1, now = i;
		else {
			if ((i - now) & 1) ans++, cnt = 0;
			else now = i;
		}
	}
	cout << ans << endl;
	return 0;
}
