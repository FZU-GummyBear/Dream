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

const int N = 101010;

int n;
pii a[N], b[N];
ll x[N], y[N];
ll rd[N];

ll Rand() {
	return (rand() * 1ll << 32) ^ (rand() * 1ll << 16) ^ rand();
}

struct Node {
	int x, y, i;
}nd[N];
bool cmp1(Node a, Node b) { return a.x < b.x; }
bool cmp2(Node a, Node b) { return a.y < b.y; }

int l[N], r[N];
ll prel[N], prer[N], tot;

void solve(pii a[], ll x[]) {
	rep(i, 1, n + 1) {
		nd[i].x = a[i].fi;
		nd[i].y = a[i].se;
		nd[i].i = i;
	}
	sort(nd + 1, nd + 1 + n, cmp1);
	rep(i, 1, n + 1) l[i] = nd[i].x, prel[i] = prel[i - 1] ^ rd[nd[i].i];
	sort(nd + 1, nd + 1 + n, cmp2);
	rep(i, 1, n + 1) r[i] = nd[i].y, prer[i] = prer[i - 1] ^ rd[nd[i].i];
	rep(i, 1, n + 1) {
		int p = lower_bound(r + 1, r + 1 + n, nd[i].x) - r - 1;
		x[nd[i].i] = prer[p];
		p = upper_bound(l + 1, l + 1 + n, nd[i].y) - l;
		x[nd[i].i] ^= tot ^ prel[p - 1];
	}
}

bool solve() {
	rep(i, 1, n + 1) {
		if(x[i] != y[i]) return 0;
	}
	return 1;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	srand(time(0));
	cin >> n;
	rep(i, 1, n + 1) {
		cin >> a[i].fi >> a[i].se >> b[i].fi >> b[i].se;
		rd[i] = Rand();
		tot ^= rd[i];
	}
	solve(a, x);
	solve(b, y);
	cout << (solve() ? "YES" : "NO") << endl;
	return 0;
}
