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

const int N = 111;

db jc[N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	jc[0] = 1;
	rep(i, 1, N) jc[i] = jc[i - 1] * i;
	rep(i, 1, N / 2) dd(i), de(2 * jc[i] * jc[i] / jc[2 * i]);
	return 0;
}
