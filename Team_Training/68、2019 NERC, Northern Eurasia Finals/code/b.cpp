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
string s;
int a[N], b[N], r, ans, ok;
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> s;
	for (auto u : s) {
		if (r == 0) {
			a[++r] = u;
			b[r] = 1;
		}else {
			if (a[r] == u) b[r]++;
			else {
				a[++r] = u;
				b[r] = 1;
			}
		}
	}
	if (r & 1) {
		ok = 1;
		int p = (r + 1) / 2;
		rep(i, 1, p) ok &= (b[i] + b[r - i + 1] >= 3), ok &= a[i] == a[r - i + 1];
		ok &= b[p] >= 2;
		if (ok) ans = b[p]  + 1;
	}
	cout << ans << endl;
	return 0;
}
