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

int n, k, now, ok;
string s, s2;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> k;
	cin >> s;
	now = 0;
	rep(i, 0, n) s2 += s[now], now = (now + 1) % k;
	if (s2 >= s) {
		cout << n << endl;
		cout << s2 << endl;
	}else {
		ok = 1;
		rep(i, 0, k) ok &= s[i] == '9';
		s2 = "";
		now = 0;
		if (ok) {
			n++;
			s[0] = '1';
			rep(i, 1, k) s[i] = '0';
			rep(i, 0, n) s2 += s[now], now = (now + 1) % k;
		}else {
			s[k-1]++;
			per(i, 0, k) if (s[i] > '9') s[i] -= 10, s[i-1] ++;else break;
			now = 0;
			rep(i, 0, n) s2 += s[now], now = (now + 1) % k;
		}
		cout << n << endl;
		cout << s2 << endl;
	}
	return 0;
}
