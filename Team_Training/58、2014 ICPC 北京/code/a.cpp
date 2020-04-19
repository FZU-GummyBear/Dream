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
typedef vector<int> vi;
typedef pair<int, int> pii;

db ans;
pii a[101010];
int T, n;

int main() {
	//std::ios::sync_with_stdio(0);
	//std::cin.tie(0);
	scanf("%d", &T);
	rep(cas, 0, T) {
		scanf("%d", &n);
		rep(i, 1, n+1) {
			scanf("%d%d", &a[i].fi, &a[i].se);
		}
		ans = -1e18;
		sort(a+1, a+n+1);
		rep(i, 2, n+1) {
			ans = max(ans, (db)abs(a[i].se - a[i-1].se)/(a[i].fi - a[i-1].fi));
		}
		ans = round(ans * 100) / 100;
		printf("Case #%d: %.2f\n", cas + 1, ans);
	}
	return 0;
}
