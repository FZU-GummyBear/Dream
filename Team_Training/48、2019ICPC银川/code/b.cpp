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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 1e3 + 8;
int n, a[N][N], x, y;

bool check(int x, int y) {
	return 1 <= x && x <= n && 1 <= y && y <= n;
}


int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n+1) {
		rep(j, 1, n+1) {
			cin >> a[i][j];
			if (a[i][j] == -1) {
				x = i, y = j;
			}
		}
	}
		if (check(x - 1, y - 1)) {
			cout << a[x-1][y] + a[x][y-1] - a[x-1][y-1];
			return 0;
		}

		if (check(x - 1, y + 1)) {
			cout << a[x-1][y] + a[x][y+1] - a[x-1][y+1];
			return 0;
		}

		if (check(x + 1, y - 1)) {
			cout << a[x+1][y] + a[x][y-1] - a[x+1][y-1];
			return 0;
		}

		if (check(x + 1, y + 1)) {
			cout << a[x+1][y] + a[x][y+1] - a[x+1][y+1];
			return 0;
		}

	return 0;
}
