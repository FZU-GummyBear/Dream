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
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, now, x, cnt;
string s;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while (cin >> n) {
		now = 0; cnt = 0; 
		rep(i, 1, n+1) {
			cin >> s;
			if (s[0] != 'S') cin >> x;
			if (s[0] == 'S') cnt++; 
			else if (x == 1) cnt++;
		}
		cout << cnt << endl;
	}
	return 0;
}
