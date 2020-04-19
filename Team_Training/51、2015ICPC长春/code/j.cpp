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
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 1010, M = 32;

int n, a[N];
int ne[N * M][2], L, cnt[N * M], rt;

int newnode() {
	cnt[++L] = 0;
	ne[L][0] = ne[L][1] = 0;
	return L;
}
void add(int x, int val) {
	int p = rt;
	per(i, 0, M) {
		int c = x >> i & 1;
		if(!ne[p][c]) ne[p][c] = newnode();
		p = ne[p][c];
		cnt[p] += val;
	}
}
ll go(int x) {
	ll ans = 0;
	int p = rt;
	per(i, 0, M) {
		int c = !(x >> i & 1);
		if(ne[p][c] && cnt[ne[p][c]]) {
			p = ne[p][c];
			ans += pw(i);
		} else {
			p = ne[p][!c];
		}
	}
	return ans;
}
ll solve() {
	cin >> n;
	L = 0; rt = newnode();
	rep(i, 1, n + 1) cin >> a[i], add(a[i], 1);
	ll ans = 0;
	rep(i, 1, n + 1) {
		add(a[i], -1);
		rep(j, i + 1, n + 1) {
			add(a[j], -1);
			ans = max(ans, go(a[i] + a[j]));
			add(a[j], 1);
		}
		add(a[i], 1);
	}
	return ans;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) cout << solve() << endl;
	return 0;
}
