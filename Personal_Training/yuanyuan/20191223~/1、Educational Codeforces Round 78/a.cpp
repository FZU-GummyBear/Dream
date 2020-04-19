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

bool solve() {
	string p, h; cin >> p >> h;
	if(sz(p) > sz(h)) return 0;
	for(int i = 0, j = sz(p); j <= sz(h); ++i, ++j) {
		int cnt[26] = {0};
		for(auto u : p) ++cnt[u - 'a'];
		rep(k, i, j) --cnt[h[k] - 'a'];
		bool ok = 1;
		rep(k, 0, 26) if(cnt[k]) ok = 0;
		if(ok) return 1;
	}
	return 0;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) cout << (solve() ? "YES" : "NO") << endl;
	return 0;
}
