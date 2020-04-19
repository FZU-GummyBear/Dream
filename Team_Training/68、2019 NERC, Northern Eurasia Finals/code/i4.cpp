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

int dp[N][N];

int qry(int a, int b) {
	if(~dp[a][b]) return dp[a][b];
	printf("? %d %d\n", a, b);
	fflush(stdout);
	char s[4]; scanf("%s", s);
	dp[a][b] = s[0] == '>';
	return dp[a][b];
}

struct Node {
	int i;
	bool operator < (const Node &c) const {
		return qry(i, c.i) == 0;
	}
};

int n1, n2, n3;
Node nd[N];
bool cmp(int a, int b, int c) {
	if(b > c) return 1;
	return qry(nd[a].i, nd[b].i) == 0;
}
void solve() {
	memset(dp, -1, sizeof(dp));
	int n; scanf("%d", &n);
	rep(i, 1, n + n + 1) nd[i].i = i;
	n *= 2;
	n1 = n / 3, n2 = (n - n1) / 2, n3 = n - n1 - n2;
	n /= 2;
	sort(nd + 1, nd + 1 + n1);
	sort(nd + 1 + n1, nd + 1 + n1 + n2);
	sort(nd + 1 + n1 + n2, nd + 1 + n1 + n2 + n3);
	int a = 1, b = 1 + n1, c = 1 + n1 + n2, k = 1;
	while(k <= n) {
		if(a <= n1 && cmp(a, b, n1 + n2) && cmp(a, c, n * 2)) ++a;
		else if(b <= n1 + n2 && cmp(b, a, n1) && cmp(b, c, n * 2)) ++b;
		else ++c;
		++k;
	}
	printf("!\n");
	fflush(stdout);
}

int main() {
	int T; scanf("%d", &T);
	while(T--) solve();
	return 0;
}
