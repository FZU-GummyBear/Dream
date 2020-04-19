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

vi vec;
int ans[256];
bool vis[256];

void dfs(int dp, int x, int y) {
	for(auto u : vec) ans[u] = min(ans[u], dp);
	if(dp > 9) return ;
	int n = sz(vec);
	for(int i = x; i < n; ++i) {
		for(int j = (i == x ? y : 0); j < i; ++j) {
			int c = (~(vec[i] & vec[j])) & 0xff;
			if(!vis[c]) {
				vis[c] = 1;
				vec.pb(c);
				dfs(dp + 1, i, j);
				vis[c] = 0;
				vec.pop_back();
			}
		}
	}
}

int main() {
//	std::ios::sync_with_stdio(0);
//	std::cin.tie(0);
	memset(ans, 0x3f, sizeof(ans));
	vec.pb(0);
	vec.pb(0xff);
	vec.pb(0x0f);
	vec.pb(0x33);
	vec.pb(0x55);
	for(auto u : vec) vis[u] = 1, de(u);
	dfs(0, 0, 0);
	de(ans[19]);
	rep(i, 0, 256) cout << ans[i] << ", ";
	return 0;
}
