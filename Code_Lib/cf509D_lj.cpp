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
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vi;
typedef double db;

#define ____ puts("\n_______________\n\n") 
#define debug(x) ____; cout<< #x << " => " << (x) << endl
#define debug_pair(x) cout<<"\n{ "<<(x).fir<<" , "<<(x).sec<<" }\n"
#define debug_arr(x,n) ____; cout<<#x<<":\n"; rep(i,0,n+1) cout<<#x<<"["<<(i)<<"] => "<<x[i]<<endl
#define debug_arr2(x,n,m) ____; cout<<#x<<":\n"; rep(i,0,n+1) rep(j,0,m+1) cout<<#x<<"["<<(i)<<"]["<<(j)<<"]= "<<x[i][j]<<((j==m)?"\n\n":"    ")
#define debug_set(x) ____; cout<<#x<<": \n"; rep_it(it,x) cout<<(*it)<<" "; cout<<endl
#define debug_map(x) ____; cout<<#x<<": \n"; rep_it(it,x) debug_pair(*it)

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

const int N=105;
int n,m; ll w[N][N],p[N],q[N],c,dw[N][N],k=0; vi V;

bool check(ll k) {
    rep(i,1,n+1) rep(j,1,m+1) if (w[i][j]>=k) return 0;
    return 1; 
}

int main() {
//    file_put(); 
    
    scanf("%d%d",&n,&m);
    rep(i,1,n+1) rep(j,1,m+1) scanf("%lld",&w[i][j]); 
    c=w[1][1];
    rep(i,1,n+1) rep(j,1,m) dw[i][j]=w[i][j+1]-w[i][j];
    rep(j,1,m) rep(i,2,n+1) V.pb(dw[i][j]-dw[i-1][j]);
    for (auto x:V) k=__gcd(k,x);
    if (!k) k=1e18; k=abs(k);
//    assert(k>0);
    if (!check(k)) return 0*printf("NO\n");
    rep(j,2,m+1) p[j]=((w[1][j]-w[1][j-1])%k+k)%k;
    rep(i,2,n+1) q[i]=((w[i][1]-w[i-1][1])%k+k)%k;
    p[1]=0,q[1]=c;
    rep(i,2,m+1) p[i]+=p[i-1],p[i]%=k;
    rep(j,2,n+1) q[j]+=q[j-1],q[j]%=k;
    printf("YES\n");
    printf("%lld\n",k);
    rep(i,1,n+1) printf("%lld%c",q[i]," \n"[i==n]);
    rep(j,1,m+1) printf("%lld%c",p[j]," \n"[j==m]);
    
	return 0;
}

