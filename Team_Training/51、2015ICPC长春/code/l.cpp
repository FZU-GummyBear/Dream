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
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 55, M = 1010;

int n, m, a[N][N][M];
int dx[] = {0, 0, 1, -1, 0, 0};
int dy[] = {0, 0, 0, 0, 1, -1};
int dz[] = {1, -1, 0, 0, 0, 0};

int solve() {
	cin >> n >> m;
	memset(a, 0, sizeof(a));
	int ans = 0, ma = 0;
	rep(i, 1, n + 1) rep(j, 1, m + 1) {
		int c; cin >> c;
		if(c) --ans;
		ma = max(ma, c);
		rep(k, 1, c + 1) a[i][j][k] = 1;
	}
	rep(i, 1, n + 1) rep(j, 1, m + 1) rep(k, 1, ma + 1) if(a[i][j][k]) {
		ans += 6;
		rep(_, 0, 6) if(a[i + dx[_]][j + dy[_]][k + dz[_]]) --ans;
	}
	return ans;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) cout << solve() << endl;
	return 0;
}
