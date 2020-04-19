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


const int N = 1e6 + 10, M = 2e5 + 10;

int a[M], ans[M], q, ne[N], pos[N], cnt, mx, n, p, np;
pii t[M];
bool vis[N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n+1) {
		cin >> a[i];
		a[i] += a[i-1];
		pos[a[i]] = i;
		vis[a[i]] = 1;
	}
	pos[1000000 + 1] = n + 1;
	vis[1000000 + 1] = 1;
	per(i, 0, 1e6 + 3) if (vis[i]) ne[i] = i;else ne[i] = ne[i+1];
	//rep(i, 1, 100) de(ne[i]);
	//de(pos[ne[9]]);
	cin >> q;
	rep(i, 1, q+1) {
		cin >> t[i].fi; t[i].se = i;
	}
	sort(t + 1, t + q + 1);
	mx = pw(30); cnt = 0;
	per(i, 1, q+1) {
		if (mx > t[i].fi) {
			p = 0;cnt = 0;mx = 0;
			while (p < n) {
				if (a[p] + t[i].fi + 1 > 1000000) np = n;
				else np = pos[ne[a[p] + t[i].fi + 1]] - 1;
				//dd(p), de(np);
				if (np == p) {
					cnt = -1; mx = -1;
					break;
				}
				cnt++;
				mx = max(a[np] - a[p], mx);
				p = np;
			}
			ans[t[i].se] = cnt;
		}else ans[t[i].se] = cnt;
	}
	rep(i, 1, q+1) if (ans[i] >= 0) cout << ans[i] << endl;else cout << "Impossible" << endl; 
	return 0;

}
