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

const int inf = 1e9;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int n; cin >> n;
	int lx = inf, rx = -inf, ly = inf, ry = -inf;
	rep(i, 1, n + 1) {
		int x, y, h; cin >> x >> y >> h;
		lx = min(lx, x - h);
		rx = max(rx, x + h);
		ly = min(ly, y - h);
		ry = max(ry, y + h);
	}
	cout << (lx + rx) / 2 << " " << (ly + ry) / 2 << " " << max((rx - lx + 1) / 2, (ry - ly + 1) / 2) << endl;
	return 0;
}
