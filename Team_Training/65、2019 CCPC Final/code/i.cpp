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

const int N = 202;

pii a[N], b[N];

void solve() {
	int n; cin >> n;
	rep(i, 1, n + 1) {
		rep(j, 1, i + 1) {
			cout << j << " " << i;
			cout << " " << b[j].fi << " " << b[j].se << " " << n - i;
			cout << " " << a[j].fi << " " << a[j].se << " " << n - i;
			cout << endl;
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	a[1] = mp(0, 0);
	b[1] = mp(0, 1);
	a[2] = mp(1, 0);
	b[2] = mp(2, 0);
	rep(i, 3, N) {
		a[i] = a[i - 2];
		b[i] = b[i - 2];
		a[i].fi++;
		a[i].se++;
		b[i].fi++;
		b[i].se++;
	}
	int T; cin >> T;
	rep(i, 1, T + 1) {
		cout << "Case #" << i << ":" << endl;
		cout << "YES" << endl;
		solve();
	}
	return 0;
}
