
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

const int N = 2020;
bitset<N> g[N];
int n, m, dis[N], k, u, v, w, l, r, q[N];
ll ans;
void bfs(int s) {
	l = r = 0;
	rep(i, 1, n+1) dis[i] = n; dis[s] = 0; 
	q[r++] = s; bitset<N> vis;
	vis.set();
	vis.reset(s-1);
	while (l < r) {
		int u = q[l]; l++;
		bitset<N> ok = vis & g[u];
		for (int i = ok._Find_first(); i < sz(ok); i = ok._Find_next(i)) {
			dis[i+1] = dis[u] + 1;
			vis.reset(i);
			q[r++] = i+1;
		}
	}
	rep(i, 1, n+1) ans += dis[i] * dis[i];
}
string s;
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n+1) {
		cin >> s;
		rep(j, 0, n) {
			if (s[j] == '1') g[i].set(j); 
		}
	}
	rep(i, 1, n+1) bfs(i);
	cout << ans << endl;
	return 0;
}
