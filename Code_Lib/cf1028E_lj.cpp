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
typedef vector<int> vi;
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

const int N=500005;
const ll P=1e8,M=1e8;
int n,k; ll a[N],b[N],c[N],ret[N],v; set<ll> S; 

int main() {
//    file_put();
    
    scanf("%d",&n);
    rep(i,0,n) scanf("%lld",&a[i]),S.insert(a[i]);
    if (sz(S)==1) {
        if (!*S.begin()) {
            printf("YES\n");
            rep(i,0,n) printf("1 ");
            printf("\n");
        } else printf("NO\n");
        return 0;
    }
    v=*--S.end();
    rep(i,0,n) if (a[i]<a[(i+1)%n] && a[(i+1)%n]==v) { k=(i+1)%n; break; }
    for (int i=k,j=n-1; j>=0; --j,i=(i-1+n)%n) c[j]=a[i];
    swap(a,c);
    b[n-1]=a[n-1];
    per(i,0,n-1) {
        b[i]=b[i+1]+a[i];
        if (!a[i] && b[i]<P) b[i]*=M;
    }
    rep(i,0,n) ret[(i+k+1)%n]=b[i];
    printf("YES\n");
    rep(i,0,n) printf("%lld ",ret[i]);
    printf("\n"); 
    
	return 0;
}

