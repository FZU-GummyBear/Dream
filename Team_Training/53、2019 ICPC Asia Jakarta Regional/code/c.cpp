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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1e5 + 10;
int n, q, l1[N], l2[N], r1[N], r2[N], R[N], C[N], a, b, c, d;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> q;
	l1[0] = l2[0] = 0;
	r1[n+1] = r2[n+1] = n+1;
	rep(i, 1, n+1) {
		cin >> R[i]; R[i] %= 2;
		if (R[i-1] == R[i]) l1[i] = l1[i-1];
		else l1[i] = i - 1;
	}
	per(i, 1, n+1) {
		if (R[i] == R[i+1]) r1[i] = r1[i+1];
		else r1[i] = i + 1;
	}
	rep(i, 1, n+1) {
		cin >> C[i]; C[i] %= 2;
		if (C[i-1] == C[i]) l2[i] = l2[i-1];
		else l2[i] = i - 1;
	}
	per(i, 1, n+1) {
		if (C[i] == C[i+1]) r2[i] = r2[i+1];
		else r2[i] = i + 1;
	}
	rep(cas, 0, q) {
		cin >> a >> b >> c >> d;
		if ((R[a] + C[b]) % 2 != (R[c] + C[d]) % 2) {
			cout << "NO" << endl;
		}else {
			if (c > l1[a] && c < r1[a] && d > l2[b] && d < r2[b]) {
				cout << "YES" << endl;
			}else cout << "NO" << endl;
		}
	}
	return 0;
}
