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
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

ll po[100];
int k, x, T, d, len;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> k >> x;
		po[0] = 1;
		rep(i, 1, 40) po[i] = min(po[i-1] * k, 1ll << 40);
		rep(i, 1, 40) {
			if (po[i] < x) x -= po[i];
			else {
				len = i;
				break;
			}
		}
		vi ans;
		d = 10 - k;
		rep(i, 1, len+1) {
			rep(j, d, 10) {
				if (x > po[len - i]) x -= po[len-i];
				else {
					ans.pb(j); break;
				}
			}
		}
		for (auto  v : ans) cout << v;
		cout << endl;
	}
	return 0;
}
