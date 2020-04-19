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

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

const int N=2005,P=1e9+7;
int n,w[N],f[N][N][2],h[N],g[N];

void Add(int &x,int y) { if ((x+=y)>=P) x-=P; }
int add(int x,int y) { return (x+y)%P; } 
int mul(int x,int y) { return (ll)x*y%P; }

int main() {
//    file_put();
    
    while (scanf("%d",&n)!=EOF){
        rep(i,0,n+2) rep(j,0,n+2) rep(k,0,2) f[i][j][k]=0;
        rep(i,1,n+1) scanf("%d",&w[i]);
        rep(j,1,n+1) f[2][j][0]=1,f[2][j][1]=j;
        rep(i,2,n+1) {
            fill_n(h,n+3,0),fill_n(g,n+3,0);
            rep(j,1,n+1) h[j]=add(mul(f[i][j][0],j-1),f[i][j][1]),
                         g[j-1]=mul(f[i][j][0],w[j]);
            rep(j,2,n+1) Add(h[j],h[j-1]);
            per(j,1,n) Add(g[j],g[j+1]);
            rep(j,1,n+1) f[i+1][j][0]=add(mul(f[i][j][1],w[j]),g[j]),
                         f[i+1][j][1]=add(mul(h[j],w[j]),mul(g[j],j)); 
        }
        printf("%d\n",h[n]);
    } 
    
	return 0;
}

