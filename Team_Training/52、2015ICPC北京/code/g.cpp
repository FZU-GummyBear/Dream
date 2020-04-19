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

pii a[4], b[4];

bool solve(pii a[]) {
	sort(a, a + 4);
	if(a[0].fi == a[2].fi || a[1].fi == a[3].fi) return 1;
	rep(i, 0, 4) rep(j, i + 1, 4) if(a[i].se == a[j].se) {
		rep(k, 0, 4) if(k != i && k != j) if(a[k].fi == a[i].fi + a[j].fi) return 1;
	}
	return 0;
}

bool solve() {
	rep(i, 0, 4) cin >> a[i].fi >> a[i].se;
	rep(msk, 0, 16) {
		rep(i, 0, 4) b[i] = a[i];
		rep(i, 0, 4) if(msk >> i & 1) swap(b[i].fi, b[i].se);
		if(solve(b)) return 1;
	}
	return 0;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) cout << (solve() ? "Yes" : "No") << endl;
	return 0;
}
