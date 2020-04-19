#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll << (x))
#define endl '\n'
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1e4 + 7;
int T, n;
db a[N], ans, t;


int main() {
//	std::ios::sync_with_stdio(0);
//	std::cin.tie(0);
	//cin >> T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		cin >> n;
		rep(i, 1, n+1) scanf("%lf", &a[i]);//cin >> a[i];
		sort(a+1, a+n+1);
		ans = 0, t = 1;
		per(i, 1, n+1) if (ans < t) {
			ans = ans * (1 - a[i]) + a[i] * t;
			t *= (1 - a[i]);
		}
		printf("%.10f\n", ans);
	}
	return 0;
}
