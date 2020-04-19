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

const int N=200005;
int B[N][5],n,m=0,k;

void I(int k,int a,int b,int c) {
    ++m,B[m][0]=k,B[m][1]=a,B[m][2]=b,B[m][3]=c;
}

void I(int k,int a,int b,int c,int d) {
    ++m,B[m][0]=k,B[m][1]=a,B[m][2]=b,B[m][3]=c,B[m][4]=d;
}

void add(int x,int y) {
    I(3,1,x,y);
    rep(i,1,n) I(4,x,i,y,i+1);
    I(3,n,x,y);
    n+=2;
}

void print() {
    printf("%d\n",m);
    rep(i,1,m+1) {
       printf("%d ",B[i][0]); 
       rep(j,1,B[i][0]+1) printf("%d%c",B[i][j]," \n"[j==B[i][0]]); 
    }
}

int main() {
//    file_put(); 
    
    scanf("%d",&k);
    if (k&1) n=3,I(3,1,2,3),I(3,1,2,3); else {
        n=4;
        rep(i,1,5) {
            int x=(i+1==5)?1:i+1,y=(i-1==0)?4:i-1;
            I(3,i,x,y);
        }
    }
    while (n<k) add(n+1,n+2);
    print();
    
	return 0;
}

