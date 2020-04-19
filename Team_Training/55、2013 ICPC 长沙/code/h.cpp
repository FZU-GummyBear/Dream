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

const db pi = acos(-1);

int main() {
	int R, r, H, F, S;
	while(~scanf("%d%d%d%d%d", &R, &r, &H, &F, &S)) {
		db h = H * 1. / F;
		db d = (R - r) * 1. / (F);
		db ans = 0;
		db k1 = S / 2. / h;
		rep(i, 1, F + 1) {
			db tr = r + (i - 1) * d;
			ll l = 3, r = 1e18, x = 0;
			db k2 = k1 / tr;
			while(l <= r) {
				ll mid = l + r >> 1;
				if(tan(pi / mid) >= k2) {
					x = mid, l = mid + 1;
				} else {
					r = mid - 1;
				}
			}
			ans += x * tan(pi / x) * tr;
		}
		ans *= 2 * h;
		printf("%.3f\n", ans);
	}
	return 0;
}
