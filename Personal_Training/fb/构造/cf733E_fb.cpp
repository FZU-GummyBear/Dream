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

const int N = 1e6 + 10;
int n, l, cntd, cntu;
ll sumd, sumu, ans[N];
string s;

void solve(string s, int o) {
	queue<int> q;
	if (o) {
		reverse(all(s));
		rep(i, 0, n) if (s[i] == 'D') s[i] = 'U';else s[i] = 'D';
	}
	//de(s);
	l = n; cntd = sumd = cntu = sumu = 0;
	per(i, 1, n+1) if (s[i-1] == 'U') {
		
		while (l >= 1 && cntu < cntd + 1) {
			if (s[l-1] == 'U') cntu++, sumu += l;
			l--;
		}
		while (cntu < cntd) cntd--, sumd -= q.front(), q.pop();
		//dd(sumu), dd(cntu), dd(sumd), de(cntd);
		int p = o ? n - i + 1 : i;
		if (cntd == cntu) {
			ans[p] = sumd * 2 - sumu * 2 + i;
		}else {
			ans[p] = sumd * 2 - sumu * 2 + i + n + 1;
		}  
		cntu--; sumu -= i;
	}else {
		sumd += i; 
		cntd++;
		q.push(i);
	}
}

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	cin >> s;
	solve(s, 0);
	solve(s, 1);
	rep(i, 1, n+1) cout << ans[i] << " \n"[i == n];
	return 0;
}


