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

const int N = 2020;

int n, m;
int a[N], b[N], ans;

bool check(int x) {
	map<int, int> cnt;
	rep(i, 1, n + 1) cnt[b[i]]++;
	rep(i, 1, n + 1) {
		int y = (a[i] + x) % m;
		if(!cnt[y]) return 0;
		cnt[y]--;
	}
	return 1;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, n + 1) cin >> a[i];
	rep(i, 1, n + 1) cin >> b[i];
	ans = m;
	rep(i, 1, n + 1) {
		int x = (b[i] - a[1] + m) % m;
		if(check(x)) ans = min(ans, x);
	}
	cout << ans << endl;
	return 0;
}
