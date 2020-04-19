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

const int N=1e5+5;
int n,w,a[N],s=0,p=1e9; vi ret;

void print() {
    for (auto x: ret) printf("%d ",x);
    printf("\n");
}

int main() {
//    file_put();
    
    scanf("%d%d",&n,&w);
    rep(i,1,n+1) scanf("%d",&a[i]),s+=a[i],p=min(p,a[i]);
    if (w<1 || w>s) return 0*printf("No\n");
    if (w==1) {
        if (p==1) {
            bool ok=0; int k;
            rep(i,1,n+1) if (!ok && a[i]==1) ok=1,k=i; else rep(kk,0,a[i]) ret.pb(i),ret.pb(i);
            ret.pb(k),ret.insert(ret.begin(),k);
            printf("Yes\n");
            print(); return 0;
        } else return 0*printf("No\n"); 
    }
    if (n==1) {
        if (w==a[1]) {
            rep(i,1,2*a[1]+1) ret.pb(1);
            printf("Yes\n"); print();
            return 0;
        } else return 0*printf("No\n");
    }
    a[1]--,a[2]--,w-=2;
//    rep(i,1,3) rep(j,0,2) ret.pb(i);
    for (int i=n; i && w; i--) {
        int k=min(w,a[i]);
        a[i]-=k,w-=k;
        rep(j,0,k) rep(op,0,2) ret.pb(i);
    }
    printf("Yes\n");
    printf("1 ");
    rep(i,0,a[2]) printf("2 2 ");
    rep(i,3,n+1) rep(j,0,a[i]) rep(k,0,2) printf("%d ",i);
    printf("1 2 ");
    rep(i,0,a[1]) printf("1 1 ");
    printf("2 ");
    print();
    
	return 0;
}

