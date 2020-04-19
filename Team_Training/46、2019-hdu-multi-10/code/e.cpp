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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll << (x))
#define endl '\n'
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 101010;

int n;
ll suf[N], ans;
pair<ll, ll> a[N];


void solve() {
	cin >> n;
	rep(i, 1, n + 1) cin >> a[i].fi >> a[i].se;
	sort(a + 1, a + 1 + n);
	ans = 1e18 + 1;
	set<ll> st;
	int j = 0;
	suf[n] = a[n].se;
	suf[n + 1] = -ans;
	per(i, 1, n) suf[i] = max(suf[i + 1], a[i].se);
	rep(i, 1, n + 1) {
		if(i == n || a[i].fi != a[i + 1].fi) {
			if(i - j > 1) {
				rep(k, j + 1, i + 1) st.insert(a[k].se);
			}
			ans = min(ans, abs(suf[i + 1] - a[i].fi));
			auto p = st.lower_bound(a[i].fi);
			if(p != st.end()) 
			ans = min(ans, abs(max(*p, suf[i + 1]) - a[i].fi));
			if(p != st.begin()) 
			ans = min(ans, abs(max(*(--p), suf[i + 1]) - a[i].fi));
			if(i - j == 1) {
				st.insert(a[i].se);
			} 
			j = i;
		}
	}
	cout << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
