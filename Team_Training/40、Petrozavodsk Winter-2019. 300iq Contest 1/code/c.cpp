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
#define endl '\n'
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

ll s, k, n, pos, x;
const int N = 3e5 + 7;
const ll B = 1e6, inf = 1e18;
ll a[N], b[N], p[N], ok;
vector<ll> tmp, V;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> k;
	s = 1ll * n * (n - 1) / 2; 
	rep(i, 1, n+1) {
		cin >> x;
		a[x] = B * i;
	}
	if (s == k) ok = 1;
	rep(i, 1, n+1) cin >> p[i];
	per(i, 1, n+1) {
		x = p[i];
		if (ok) b[x] = inf + n - i;
		else {
			if (s - (x - 1) > k) s -= x - 1, b[x] = -inf + n - i;
			else {
				rep(j, 1, x) tmp.pb(a[j]);
				sort(all(tmp));
				pos = s - k;
			  b[x] = tmp[sz(tmp) - pos] - 1;              
				ok = 1;
			}
		}
	}
	rep(i, 1, n+1) V.pb(a[i]), V.pb(b[i]);
	sort(all(V));
	V.erase(unique(all(V)), V.end());
	rep(i, 1, n+1) {
		a[i] = lower_bound(all(V), a[i]) - V.begin();
		b[i] = lower_bound(all(V), b[i]) - V.begin();
		a[i] -= n;
		b[i] -= n;
	}
	rep(i, 1, n+1) b[i] *= -1;
	cout << "Yes" << endl; 
	rep(i, 1, n+1) cout << a[i] << " \n"[i == n];
	rep(i, 1, n+1) cout << b[i] << " \n"[i == n];
	return 0;
}