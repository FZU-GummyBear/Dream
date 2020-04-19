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

const int N=1005;

int n,a[N][N],cnt=0,now=-1,p[N],c[N];

void print(){
    printf("%d\n",cnt);
    rep(i,0,cnt) {
        rep(j,1,n+1) printf("%d",a[i][j]);
        printf("\n");
    }
}

bool cmp(int x,int y) { return p[x]>p[y]; }

int main() {
//    file_put();
    
    scanf("%d",&n);
    rep(i,1,n+1) scanf("%d",&p[i]),c[i]=i;
    sort(c+1,c+n+1,cmp);
    rep(j,1,n+1) {
        ++now;
        for (int i=now,k=1; k<=p[c[j]]; k++,++i,i=i%(n+1),cnt=max(cnt,i+1)) a[i][c[j]]=1; 
    }
    print();
    
	return 0;
}

