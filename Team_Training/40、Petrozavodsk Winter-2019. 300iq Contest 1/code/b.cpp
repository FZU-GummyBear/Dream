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
#define endl '\n'
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 202020;

int n, k, a[N], pre[N], ne[N];
bool del[N];
priority_queue<pair<int, pii> > que;

void Del(int x) {
	del[x] = 1;
	int y = pre[x], z = ne[x];
	que.push(mp(a[y] + a[z], mp(y, z)));
	ne[y] = z; pre[z] = y;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> k;
	rep(i, 1, n + 1) cin >> a[i];
	rep(i, 2, n + 1) pre[i] = i - 1, que.push(mp(a[i - 1]  + a[i], mp(i - 1, i))); 
	pre[1] = n; que.push(mp(a[n] + a[1], mp(n, 1)));
	rep(i, 1, n + 1) ne[pre[i]] = i;
	rep(i, 1, n - k + 1) {
		while(1) {
			auto u = que.top(); que.pop();
			if(del[u.se.fi] || del[u.se.se]) continue;
			int x = u.se.fi, y = u.se.se;
			if(a[x] > a[y]) Del(x); else Del(y);
			break;
		}
	}
	while(1) {
		auto u = que.top(); que.pop();
		if(del[u.se.fi] || del[u.se.se]) continue;
		cout << u.fi << endl;
		break;
	}
	return 0;
}