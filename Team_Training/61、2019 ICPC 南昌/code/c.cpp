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

const int P = 1e9 + 7, N = 1e5 + 7;
int dp[N], T, a[N], n;
string s;
int dfs(int pos, bool lim2) {
	if (pos == 0) return 1;
	if (!lim2 && dp[pos] != -1) return dp[pos];
	int res = 0, up = a[pos];
	rep(i, 0, up+1)
		if (i == 0) {
			int up2 = lim2 ? 0 : 1;
			rep(j, 0, up2+1) {
				(res += dfs(pos - 1, lim2 & (j == i))) %= P;
			}
		}else {
			rep(j, 0, 1) {
				(res += dfs(pos - 1, 0)) %= P;
			}
		}
	if (!lim2) dp[pos] = res;
	return res;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> s;
		n = sz(s);
		reverse(all(s));
		memset(dp, -1, sizeof(dp));
		rep(i, 1, n+1) a[i] = s[i-1] - '0';
		//n = 0000;
		//rep(i, 1, n+1) a[i] = rand() % 2;
		cout << dfs(n, 1) << endl;;
	}
	return 0;
}
