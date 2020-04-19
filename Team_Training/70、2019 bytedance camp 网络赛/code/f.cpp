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

const int N = 303030, M = 1e6 + 1;

int n, a[N], cnt[N], f[N], b[M];
vi ans;

bool gao1() {
	rep(i, 1, n + 1) {
		int x = a[i], c = 0;
		while(x % 2 == 0) x >>= 1, ++c;
		f[i] = c;
		++cnt[c];
	}
	rep(i, 0, N) if(cnt[i] >= (n + 2) / 3) {
		rep(j, 1, n + 1) if(f[j] == i) ans.pb(j);
		return 1;
	}
	return 0;
}
bool gao2(int k) {
	int cnt[11] = {0};
	rep(i, 1, n + 1) ++cnt[a[i] % k];
	rep(i, 1, k) if(cnt[i] >= (n + 2) / 3) {
		rep(j, 1, n + 1) if(a[j] % k == i) ans.pb(j);
		return 1;
	}
	return 0;
}
bool gao2() {
	return gao2(3);
}

bool gao3() {
	rep(i, 1, n + 1) ++b[a[i]];
	rep(i, 1, M) b[i] += b[i - 1];
	rep(i, 1, M) {
		int j = min(M, i * 2) - 1;
		if(b[j] - b[i - 1] >= (n + 2) / 3) {
			rep(k, 1, n + 1) if(i <= a[k] && a[k] <= j) ans.pb(k);
			return 1;
		}
	}
	return 0;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n + 1) cin >> a[i];
	if(!gao1() && !gao2() && !gao3()) {
		assert(0);
	}
	cout << sz(ans) << endl;
	rep(i, 0, sz(ans)) cout << a[ans[i]] << " \n"[i == sz(ans) - 1];
	return 0;
}
