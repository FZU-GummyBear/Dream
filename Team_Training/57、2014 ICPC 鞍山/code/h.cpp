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
typedef pair<int, int> pii;
typedef vector<int> vi;

int ans[] = {0, 4, 5, 2, 5, 2, 6, 3, 6, 7, 3, 4, 3, 4, 3, 0, 5, 2, 6, 3, 6, 3, 8, 6, 7, 7, 6, 4, 6, 4, 6, 3, 6, 7, 3, 4, 7, 7, 6, 4, 7, 8, 4, 5, 7, 7, 4, 4, 3, 4, 3, 0, 6, 4, 6, 3, 7, 7, 4, 4, 4, 6, 5, 3, 6, 7, 7, 7, 3, 4, 6, 4, 7, 8, 7, 7, 4, 5, 4, 4, 3, 4, 6, 4, 3, 0, 6, 3, 7, 7, 4, 6, 4, 4, 5, 3, 7, 8, 7, 7, 7, 7, 4, 6, 10, 8, 7, 8, 7, 8, 7, 7, 4, 5, 4, 4, 4, 4, 5, 3, 7, 8, 7, 7, 7, 7, 7, 6, 7, 8, 8, 8, 8, 8, 9, 8, 4, 6, 5, 5, 5, 5, 6, 5, 8, 8, 9, 8, 9, 8, 9, 9, 6, 5, 6, 6, 6, 6, 8, 6, 4, 6, 5, 5, 6, 5, 6, 6, 4, 5, 1, 2, 5, 5, 3, 2, 5, 5, 6, 5, 6, 6, 8, 6, 5, 5, 3, 2, 6, 6, 6, 5, 4, 6, 6, 5, 5, 5, 6, 6, 4, 5, 5, 5, 1, 2, 3, 2, 5, 5, 6, 6, 6, 5, 8, 6, 5, 5, 6, 6, 3, 2, 6, 5, 4, 5, 5, 5, 5, 5, 6, 6, 7, 8, 4, 5, 4, 5, 1, 4, 1, 2, 3, 2, 3, 2, 6, 5, 4, 5, 1, 4, 1, 4, 3, 0
};

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) {
		string s; cin >> s;
		int x = 0;
		for(auto u : s) x = x * 2 + u - '0';
		cout << ans[x] + 1 << endl;
	}
	return 0;
}
