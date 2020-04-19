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

const int N = 202020;

int n, a[N];

void solve() {
	cin >> n;
	rep(i, 1, n * 2 + 1) cin >> a[i];
	map<int, int> st;
	st[0] = 0; int now = 0;
	rep(i, 1, n + 1) {
		if(a[i] == 1) ++now;
		else --now;
		st[now] = i;
	}
	int ans = st[0]; now = 0;
	per(i, n + 1, n * 2 + 1) {
		if(a[i] == 1) --now;
		else ++now;
		if(st.count(now)) ans = max(ans, st[now] + n * 2 - i + 1);
	}
	cout << 2 * n - ans << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
