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
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 51;

int sg[N][N][N][N];

inline int gao(int x) {
	if(x <= 4) return x;
	if(x & 1) return 3;
	return 4;
}
void Assert(bool o) {
	if(!o) while(1) ;
}
int dfs(int a, int b, int c, int d) {
	if(~sg[a][b][c][d]) return sg[a][b][c][d];
	if(a && dfs(a - 1, b, c, d) == 0) return sg[a][b][c][d] = 1;
	if(b && dfs(a + 1, b - 1, c, d) == 0) return sg[a][b][c][d] = 1;
	if(c && dfs(a, b + 1, c - 1, d) == 0) return sg[a][b][c][d] = 1;
	if(d && dfs(a, b, c + 1, d - 1) == 0) return sg[a][b][c][d] = 1;
	int cnt[] = {0, a, b, c, d};
	rep(i, 1, 5) if(cnt[i]) {
		--cnt[i];
		rep(j, i, 5) if(cnt[j]) {
			--cnt[j];
			int k = gao(i + j);
			++cnt[gao(k)];
			if(dfs(cnt[1], cnt[2], cnt[3], cnt[4]) == 0) return sg[a][b][c][d] = 1;
			--cnt[gao(k)];
			++cnt[j];
		}
		++cnt[i];
	}
	return sg[a][b][c][d] = 0;
}
void solve() {
	int n;
	int cnt[5] = {0};
	cin >> n;
	rep(i, 1, n + 1) {
		int x; cin >> x;
		++cnt[gao(x)];
	}
	if(dfs(cnt[1], cnt[2], cnt[3], cnt[4])) cout << "Alice" << endl;
	else cout << "Bob" << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	memset(sg, -1, sizeof(sg));
	rep(i, 1, T + 1) {
		cout << "Case #" << i << ": ";
		solve();
	}
	return 0;
}
