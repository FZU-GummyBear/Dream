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

const int N = 2020;

int n, m, q, ans;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
bool del[N][N];

bool check(int x, int y) {
	if(x < 1 || x > n || y < 1 || y > m) return 0;
	if(del[x][y]) return 0;
	return (del[x - 1][y] || del[x + 1][y]) && (del[x][y - 1] || del[x][y + 1]);
}

void gao(int x, int y) {
	if(del[x][y]) return ;
	++ans; del[x][y] = 1;
	rep(i, 0, 4) {
		int nx = x + dx[i], ny = y + dy[i];
		if(check(nx, ny)) gao(nx, ny);
	}
}

void solve() {
	cin >> n >> m >> q;
	rep(i, 0, n + 2) rep(j, 0, m + 2) del[i][j] = 0;
	while(q--) {
		ans = 0; int x, y; cin >> x >> y;
		gao(x, y);
		cout << ans << endl;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
