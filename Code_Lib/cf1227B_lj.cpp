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
int n,T,q[N],p[N],now,x; bool v[N];

int main() {
//    file_put();
    
    scanf("%d",&T);
    while (T--) {
        scanf("%d",&n),fill(v,v+n+1,0),now=1,x=0;
        rep(i,1,n+1) scanf("%d",&q[i]);
        rep(i,1,n+1) if (q[i]>q[i-1]) v[p[i]=q[i]]=1; else {
            for (; v[now]; now++); v[p[i]=now]=1;
        }
        bool ok=1;
        rep(i,1,n+1) {
            x=max(x,p[i]);
            if (x!=q[i]) {
                ok=0;
                break;
            }
        }
        if (!ok) {
            printf("-1\n");
            continue;
        }
        rep(i,1,n+1) printf("%d%c",p[i]," \n"[i==n]);
    } 
    
	return 0;
}
