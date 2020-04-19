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

const int N = 1010;

int x[N], y[N], t[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int n; scanf("%d", &n);
		rep(i, 1, n + 1) scanf("%d%d%d", t + i, x + i, y + i);
		db ans = 0;
		rep(i, 2, n + 1) {
			db dx = x[i] - x[i - 1], dy = y[i] - y[i - 1];
			db dis = sqrt(dx * dx + dy * dy);
			ans = max(ans, dis / (t[i] - t[i - 1]));
		}
		printf("%.10f\n", ans);
	}
	return 0;
}
