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

const int N = 3e5 + 78;
int n, a[N], b[N], x[N], y[N], l, r, m;
pii q[N];

bool check(pii a, pii b, pii c) {
	return 1ll * (b.se - a.se) * (c.fi - b.fi) > 1ll * (c.se - b.se) * (b.fi - a.fi);
}

bool check2(pii a, pii b, int x, int y) {
	return 1ll * (b.se - a.se) * x < 1ll * y * (b.fi - a.fi);
}
 
pii get(int x, int y) {
	pii res = q[r-1];
	int l1 = 0, r1 = r - 2;
	while (l1 <= r1) {
		int mid = l1 + r1 >> 1;
		if (check2(q[mid], q[mid+1], x, y)) res = q[mid], r1 = mid-1;
		else l1 = mid+1;
	}
	return res;
}

int main() {
	//std::ios::sync_with_stdio(0);
	//std::cin.tie(0);
	//cin >> n;
	scanf("%d", &n);
	rep(i, 1, n+1) {
		scanf("%d%d%d", &a[i], &x[i], &y[i]);
	}
	l = r = 0;
	rep(i, 1, n+1) {
		if (m == 0 || b[m] <= a[i]) {
			b[++m] = a[i];
			pii now = mp(m, b[m]);
			while (r - l >= 2 && !check(q[r-2], q[r-1], now)) r--;
			q[r++] = now;
		}
		//dd(q[0].fi);de(q[0].se);
		//dd(q[1].fi);de(q[1].se);
		pii t = get(x[i], y[i]);
		//dd(t.fi), de(t.se);
		cout << -1ll * b[m] * x[i] + 1ll * (m + 1) * y[i] - 1ll * t.fi * y[i] + 1ll * t.se * x[i] << endl;
	}
	return 0;
}
