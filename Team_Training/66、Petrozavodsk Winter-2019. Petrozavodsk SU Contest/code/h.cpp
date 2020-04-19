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
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int P = 1e9 + 7;
const int N = 1e3 + 7;
int n, c, jc[N], inv[N], ans1[N], ans2[N];
pii a[N];
int add(int a, int b) {
	return (a + b) % P;
}

int mul(int a, int b) {
	return 1ll * a * b % P;
}

int kpow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = mul(res, a);
		a = mul(a, a);
		b >>= 1;
	}
	return res;
}

int C(int n, int m) {
	if (m < 0 || m > n) return 0;
	return mul(jc[n], mul(inv[m], inv[n-m]));
}

void upd(int &x, int y) {x = add(x, y);}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int n = 1000;
	jc[0] = 1;
	rep(i, 1, n+1) jc[i] = mul(jc[i-1], i);
	inv[n] = kpow(jc[n], P - 2);
	per(i, 0, n) inv[i] = mul(inv[i+1], i+1);
	cin >> n >> c;

	rep(i, 1, n+1) cin >> a[i].fi, a[i].se = i;
	sort(a+1, a+n+1);
	rep(i, 1, n+1) {
		rep(j, i+1, n+1) {
			int w = 0;
			rep(k, c-1, n - j+1) {
				int s = n - j;
				int sum = mul(jc[k+1], jc[s - k]);
				sum = mul(sum, C(n, 2 + s));
				sum = mul(sum, jc[n - (2 + s)]);
				sum = mul(sum, C(s, k));	
				//dd(k), dd(s), de(sum);
				upd(ans1[a[i].se], mul(a[j].fi, sum));
				upd(w, sum);
				upd(ans2[a[i].se], sum);
			}
			upd(ans1[a[j].se], mul(a[i].fi, add(jc[n], P - w)));
		}
		//de(ans1[a[i].se]);
		//rep(j, 1, i) upd(ans1[a[i].se], mul(jc[n], mul(kpow(2, P - 2), a[j].fi)));
		upd(ans1[a[i].se], mul(jc[n], a[i].fi));
	}
	//rep(i, 1, n+1) dd(ans1[i]), de(ans2[i]);
	rep(i, 1, n+1) cout << mul(ans1[i], ans2[i]) << " \n"[i == n];
	return 0;
}
