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

const int N = 1e6 + 9;

int n, a[N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	int ca = 0;
	while(T--) {
		cin >> n;
		rep(i, 1, n + 1) cin >> a[i];
		int mi = n + 1, ans = 0;
		per(i, 1, n + 1) {
			if(a[i] > mi) ++ans;
			mi = min(mi, a[i]);
		}
		cout << "Case #" << ++ca << ": ";
		cout << ans << endl;
	}
	return 0;
}
