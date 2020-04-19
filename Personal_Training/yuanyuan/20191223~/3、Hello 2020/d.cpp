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

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n + 1) cin >> a[i].fi >> a[i].se >> b[i].fi >> b[i].se;
	rep(i, 1, n + 1) rep(j, i + 1, n + 1) {
		int o = (max(a[i].fi, a[j].fi)) <= (min(a[i].se, a[j].se));
		int t = (max(b[i].fi, b[j].fi)) <= (min(b[i].se, b[j].se));
		if(o != t) de("NO");
	}
	return 0;
}
