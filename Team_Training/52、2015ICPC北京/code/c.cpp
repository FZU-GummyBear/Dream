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
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

int dis[36 * 6 * 36 * 6 + 11];
vi que; 

void init() {
	memset(dis, 0x3f, sizeof(dis));
	int s = 0; rep(i, 0, 6) s = s * 6 + i;
	que.pb(s); dis[s] = 0;
	rep(i, 0, sz(que)) {
		auto u = que[i];
		int a[6], x = u;
		per(j, 0, 6) a[j] = x % 6, x /= 6;
		bool vis[6] = {0};
		rep(j, 0, 6) if(!vis[a[j]]) {
			vis[a[j]] = 1;
			rep(k, 0, 6) if(a[j] != k) {
				int v = 0;
				rep(t, 0, 6) v = v * 6 + (a[t] == a[j] ? k : a[t]);
				if(dis[v] > dis[u] + 1) {
					dis[v] = dis[u] + 1;
					que.pb(v);
				}
			}
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	init();
	string s, t;
	while(cin >> s >> t) {
		int ans = sz(t);
		for(auto u : que) {
			int res = dis[u];
			int a[6], x = u; per(i, 0, 6) a[i] = x % 6, x /= 6;
			rep(i, 0, sz(s)) {
				int k = t[i] - '1';
				int c = a[k];
				char tk = c + '1';
				res += (s[i] != tk);
			}
			ans = min(ans, res);
		}
		cout << ans << endl;
	}
	return 0;
}
