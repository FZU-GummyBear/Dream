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

const int N = 222;

int dp[N][N], a[N];

int qry(int a, int b) {
	if(~dp[a][b]) return dp[a][b];
	printf("? %d %d\n", a, b);
	fflush(stdout);
	char s[4]; scanf("%s", s);
	dp[a][b] = s[0] == '>';
	return dp[a][b];
}
bool check() {
}
void solve() {
	memset(dp, -1, sizeof(dp));
	memset(a, 0, sizeof(a));
	int n; scanf("%d", &n);
	rep(i, 1, n + 1) {
		int t = qry(i, i + n);
		if(t == 1) ++a[i];
		else ++a[i + n];
	}
	rep(i, 1, n + n + 1) if(a[i] > 1 && check(i)) break;
	printf("!\n"); fflush(stdout);
}

int main() {
	int T; scanf("%d", &T);
	while(T--) solve();
	return 0;
}
