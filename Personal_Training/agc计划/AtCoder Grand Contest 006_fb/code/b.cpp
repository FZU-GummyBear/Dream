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
const int P = 1e9 + 7;
//ll rnd(ll l, ll r) { mt19937 gen(rand()); RR dis(l, r); return dis(gen); }
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 3e5 + 7;
int a[N], p, n, m, ans, u, v; 

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> p;
	if (p == 1 || p == n * 2 - 1) {
		cout << "No" << endl;
		return 0;
	} 
	cout << "Yes" << endl;
	a[n] = p;
	int x = p;
	per(i, 1, n) {
		p--;
		if (p == 0) p = n * 2 - 1;
		a[i] = p;
	}
	rep(i, n+1, n*2) {
		x++;
		if (x == n * 2) x = 1;
		a[i] = x;
	}
	rep(i, 1, n * 2) cout << a[i] << " \n"[i == n * 2 - 1];
	return 0;
}


