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

const int N = 3e3 + 7;
int tmp[N], t[N], a[N], n, T;

void kpow(int *a, int b) {
	rep(i, 0, n-1) t[i] = a[i];
	a[0] = 0; rep(i, 1, n - 1) a[i] = -pw(30);
	while (b) {
		if (b & 1) {
			rep(i, 0, n-1) tmp[i] = a[i], a[i] = 0;
			rep(i, 0, n-1) {
				for (int j = 0; j + i <= n - 2; j++) a[i + j] = max(a[i + j], tmp[i] + t[j]);
			}
			//rep(i, 0, n-1) dd(t[i]), dd(tmp[i]), de(a[i]);
			//cout << endl;
		}
		rep(i, 0, n-1) tmp[i] = t[i], t[i] = 0;
		rep(i, 0, n-1) {
			for (int j = 0; j + i <= n - 2; j++) t[i + j] = max(t[i + j], tmp[i] + tmp[j]);
		}
		b >>= 1;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n;
		rep(i, 0, n - 1) cin >> a[i];
		kpow(a, n);
	//	rep(i, 0, n - 1) de(a[i]);
		cout << a[n - 2] << endl;
	}
	return 0;
}
