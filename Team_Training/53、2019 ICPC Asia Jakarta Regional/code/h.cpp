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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 101010;

int n;
pii a[N];
pair<pii, int> b[N << 1];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	int m = 0;
	ll ans = 0;
	rep(i, 1, n + 1) {
		cin >> a[i].fi >> a[i].se;
		b[++m] = mp(a[i], i);
		swap(a[i].fi, a[i].se);
		b[++m] = mp(a[i], i);
		ans = max(ans, a[i].fi * 1ll * a[i].se);
	}
	sort(b + 1, b + 1 + m);
	int ma = 0, ma2 = 0, i1 = 0, i2 = 0;
	per(i, 1, m + 1) {
		if(i1 && b[i].se != i1) {
			ans = max(ans, 2ll * b[i].fi.fi * min(ma, b[i].fi.se));
		} else if(i2 && b[i].se != i2) {
			ans = max(ans, 2ll * b[i].fi.fi * min(ma2, b[i].fi.se));
		}
		if(b[i].fi.se > ma) {
			if(ma > ma2) ma2 = ma, i2 = i1;
			ma = b[i].fi.se, i1 = b[i].se;
		} else if(b[i].fi.se > ma2) {
			ma2 = b[i].fi.se, i2 = b[i].se;
		}
	}
	if(ans & 1) {
		cout << ans / 2 << ".5" << endl;
	} else {
		cout << ans / 2 << ".0" << endl;
	}
	return 0;
}
