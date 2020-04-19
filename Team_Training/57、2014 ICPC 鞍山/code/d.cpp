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
typedef long double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1e5 + 7;
db s1[N], s2[N], ans;
int a[N], len, o, n, T, k;

db cal(db x, int l, int r) {
	db t1 = s1[r] - s1[l-1], t2 = s2[r] - s2[l-1];
	return x * x * (r - l + 1) - 2 * t1 * x + t2;
}

int main() {
	scanf("%d", &T);
	rep(cas, 0, T) {
		scanf("%d%d", &n, &k);
		rep(i, 1, n+1) scanf("%d", &a[i]);
		sort(a + 1, a + n + 1);
		ans = 1e18;
		if (n == k) ans = 0;
		else {
			//len = (n - k) / 2; o = (n - k) & 1;
			rep(i, 1, n+1) s1[i] = s1[i-1] + a[i], s2[i] = s2[i-1] + 1ll * a[i] * a[i];
			rep(i, 1, k+2) {
				db x; int l = i, r = i + n - k - 1;
				x = (s1[r] - s1[l - 1]) / (r - l + 1);
				//if (o) x = a[i + len];else x = (a[i + len] + a[i + len - 1]) / 2.; 
				ans = min(ans, cal(x, i, i + n - k - 1));
			}
		}
		printf("%.10f\n", (double)ans);
	}
	return 0;
}
