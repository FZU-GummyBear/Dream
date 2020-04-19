#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl '\n'
#define pw(x) (1ll << (x))
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	rep(ca, 1, T + 1) {
		cout <<	"Case #" << ca << ": ";
		ll n, a, b; cin >> n >> a >> b;
		ll d = __gcd(a, b);
		ll ans = n / d - 2;
		if(ans & 1) cout << "Yuwgna" << endl;
		else cout << "Iaka" << endl;
	}
	return 0;
}
