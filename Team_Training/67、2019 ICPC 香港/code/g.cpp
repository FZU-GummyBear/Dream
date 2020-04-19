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

const int N = 101010;

int n;
int c[N], f[N], dp[N];

int dfs(int k) {
	int u = ++n;
	if(k == 1) {
		c[u] = 1;
		dp[u] = 1;
		return u;
	} else {
		int v = dfs(k / 2);
		f[v] = u;
		int t = ++n;
		f[t] = u; c[t] = 2;
		f[++n] = t; c[n] = 1;
		f[++n] = t; c[n] = 1;
		dp[u] = dp[v] + 2;
		c[u] = dp[u] + (k % 2 ^ 1);
		return u;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int k; cin >> k;
	if(k == 1) {
		n = 2;
		c[1] = 100, c[2] = 1;
		f[2] = 1;
	} else {
		dfs(k);
	}
	cout << n << endl;
	rep(i, 2, n + 1) cout << f[i] << " \n"[i == n];
	rep(i, 1, n + 1) cout << c[i] << " \n"[i == n];
	return 0;
}
