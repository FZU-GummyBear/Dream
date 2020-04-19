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

const int N = 2e6 + 10;
bool ok;
int mi, T, n, a[N], b[N], m;
ll ans, sum;

int main() {
	//std::ios::sync_with_stdio(0);
	//std::cin.tie(0);
	//cin >> T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		scanf("%d", &n); m = 0;
		rep(i, 1, n+1) a[i] = 0;
		int x;
		rep(i, 1, n+1) scanf("%d", &x), a[x]++;
		ans = 0;
		rep(i, 1, n+1) if (a[i]) b[++m] = a[i];
		mi = pw(30);
		rep(i, 1, m+1) ans += b[i], mi = min(mi, b[i]);
		rep(i, 2, mi+2) {
			if (mi / (i - 1) * i < mi) continue;
			ok = 1; sum = 0;
			rep(j, 1, m+1) {
				if (b[j] / (i - 1) * i < b[j]) {
					ok = 0;
					break;
				}
				sum += b[j] / i;
				if (b[j] % i != 0) sum++;
			}
			if (ok) ans = min(ans, sum);
		}
		cout << ans << endl;
	}
	return 0;
}
