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
int n,m,a[N],x,y; set <pii> V;

void work() {
    random_shuffle(a+1,a+n+1);
}

bool check() {
    rep(i,1,m+1) {
        int x=a[i],y=a[(i==n)?1:i+1];
        if (x>y) swap(x,y);
        if (V.count(mp(x,y))) return 0;
    }
    return 1;
}

int print() {
    rep(i,1,m+1) {
        int x=a[i],y=a[(i==n)?1:i+1];
        if (x>y) swap(x,y);
        printf("%d %d\n",x,y);
    }
}

int main() {
//    file_put();
    
    scanf("%d%d",&n,&m);
    rep(i,1,n+1) a[i]=i;
    rep(i,1,m+1) {
        scanf("%d%d",&x,&y);
        if (x>y) swap(x,y);
        V.insert(mp(x,y));
    }
    rep(i,1,101) {
        work();
        if (check()) return 0*print();
    }
    printf("-1\n");
    
	return 0;
}

