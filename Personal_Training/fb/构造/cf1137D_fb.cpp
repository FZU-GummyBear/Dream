//#pragma GCC optimize(3)
//#pragma GCC optimize("unroll-loops")
//#pragma GCC target("sse2")
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) (a).begin(), (a).end()
#define pw(x) (1ll<<(x))
#define lb(x) ((x) & -(x))
#define endl "\n"
#define FI(x) freopen(#x".in","r",stdin)
#define FO(x) freopen(#x".out","w",stdout)
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
//typedef uniform_int_distribution<ll> RR;
//mt19937 gen(998244353);
//ll rnd(ll l, ll r) { RR dis(l, r); return dis(gen); }
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 22;
int n, id[N], now[N], lim[N], len, ok, c, t;
string s;



void read() {
	cin >> n; 
	rep(k, 1, n+1) {
		cin >> s;
		for (auto u : s) id[u - '0'] = k;
	}
}


void print(vi ans) {
	sort(all(ans));
	cout << "next ";
	rep(i, 0, sz(ans)) now[ans[i]]++, cout << ans[i] << " \n"[i == sz(ans) - 1];
	fflush(stdout);
	read();
}

bool check() {
	rep(i, 0, 10) if (now[i] < lim[i]) return 1;
	return 0;
}

int main() {
	//FI(a);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	vi ans;
	while (1) {
		ans.clear();
		ans.pb(0); ans.pb(1);
		print(ans);
		ans.clear();
		ans.pb(0);
		print(ans);
		if (id[0] == id[1]) break;
	}
	while (1) {
		vi ans;
		rep(i, 0, 10) ans.pb(i);
		print(ans);
		if (id[0] == id[2]) break;
	}
 	cout << "done" << endl;
	fflush(stdout);
	return 0;
}


