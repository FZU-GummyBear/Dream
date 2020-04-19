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

const int N = 1e5 + 10;
int T, m;
ll p[N], n;
unsigned long long s1, s2, t, t2;
bool isp[N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	n = 1e5 + 7;
	rep(i, 2, n+1) {
		if (!isp[i]) {
			p[++m] = i;
			for (int j = i + i; j <= n; j += i) isp[j] = 1;
		}
	} 
	rep(cas, 0, T) {
		cin >> n; int nn = n;
		s1 = s2 = 1;
		rep(i, 1, m+1) if (p[i] * p[i] <= n) {
			if (n % p[i] == 0) {
				int cnt = 0;
				while (n % p[i] == 0) n /= p[i], cnt++;
				s1 *= (cnt + 1);
				t = 0; t2 = 1; 
				rep(j, 0, cnt+1) {
					t += t2;
					t2 *= p[i] * p[i];
				} 
				s2 *= t;
			}
		}	else break;
		if (n > 1) {
			s1 *= (1 + 1);
			t = 0; t2 = 1; 
			rep(j, 0, 1+1) {
				t += t2;
				t2 *= n * n;
			} 
			s2 *= t;
		}
		cout << s2 - s1 * nn << endl;
	}
	return 0;
}
