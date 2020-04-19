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

int a, b, n;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> a >> b >> n;
	int t = b - a;
	int ans = (n - a) / t + ((n - a) % t != 0) + (n - b) / t + ((n - b) % t != 0);
	cout << ans << endl;
	return 0;
}
