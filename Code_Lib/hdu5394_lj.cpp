#pragma comment(linker, "/STACK:1024000000000000,1024000000000000")


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

#define mem(a,x) memset(a,x,sizeof(a))
#define rep_it(it,x) for (__typeof((x).begin()) it=(x).begin(); it!=(x).end(); it++)
#define ____ puts("\n_______________\n\n") 
#define debug(x) ____; cout<< #x << " => " << (x) << endl
#define debug_pair(x) cout<<"\n{ "<<(x).fir<<" , "<<(x).sec<<" }\n"
#define debug_arr(x,n) ____; cout<<#x<<":\n"; rep(i,0,n+1) cout<<#x<<"["<<(i)<<"] => "<<x[i]<<endl
#define debug_arr2(x,n,m) ____; cout<<#x<<":\n"; rep(i,0,n+1) rep(j,0,m+1) cout<<#x<<"["<<(i)<<"]["<<(j)<<"]= "<<x[i][j]<<((j==m)?"\n\n":"    ")
#define debug_set(x) ____; cout<<#x<<": \n"; rep_it(it,x) cout<<(*it)<<" "; cout<<endl
#define debug_map(x) ____; cout<<#x<<": \n"; rep_it(it,x) debug_pair(*it)

void file_put() {
    freopen("filename.in", "r", stdin);
    //freopen("filename.out", "w", stdout);
}

const int N=3e6+5;

//const int M=26;
//struct PAM{
//    int s[N],len[N],next[N][M],fail[N],cnt[N],id[N],no[N],pre[N],qlink[N],last,n,p,cur,now; ll ans,dep[N];
//    inline int new_node(int _l) { mem(next[p],0); cnt[p]=dep[p]=0,len[p]=_l; qlink[now]=0; return p++; }
//    inline void Init() { new_node(p=0),new_node(s[0]=-1),fail[last=n=0]=1; ans=0; }
//    inline int get_fail(int x) { for (; s[n-len[x]-1]!=s[n]; x=qlink[x]) if (s[n-len[fail[x]]-1]==s[n]) return fail[x]; return x; }
//    inline void I(int c) { 
//        c-='a',s[++n]=c,cur=get_fail(last);
//        if (!next[cur][c]) {
//            now=new_node(len[cur]+2);
//            fail[now]=next[get_fail(fail[cur])][c];
//            next[cur][c]=now; pre[now]=cur;
//            //dep[now]=dep[fail[now]]+1; //...
//            dep[now]=dep[fail[now]]+len[now];
//            if (len[now]>1) qlink[now]=(s[n-len[fail[now]]]==s[n-len[fail[fail[now]]]]) ? qlink[fail[now]] : fail[fail[now]];
//        }
//        last=next[cur][c],cnt[last]++; id[n]=last; if (!no[last]) no[last]=n; //...
//        ans+=dep[last];
//    }
//    inline void D() { if (p<=1) return; if (!(--cnt[last])) next[pre[last]][s[n]]=0,--p; last=id[--n]; }
//    inline void Insert(char s[],int op=0,int _n=0) { 
//        if (!_n) _n=strlen(s);  if (!op) rep(i,0,_n) I(s[i]); else per(i,0,_n) I(s[i]); 
//    }
//    inline void count() { per(i,0,p) cnt[fail[i]]+=cnt[i]; }
//    inline void Q(){ /*count();*/ }
//};

const int M=26;
struct PAM{
    int s[N],len[N],next[N][M],fail[N],cnt[N],id[N],no[N],pre[N],qlink[N],last,n,p,cur,now; ll ans,dep[N];
    inline int new_node(int _l) { mem(next[p],0); cnt[p]=dep[p]=0,len[p]=_l; qlink[p]=0; return p++; }
    inline void Init() { new_node(p=0),new_node(s[0]=-1),fail[last=n=0]=1; ans=0; }
    inline bool ok(int x,int y,int d=0) { return s[n-len[x]-d]==s[n-len[y]]; }
    inline int get_fail(int x) { for (; !ok(x,0,1); x=qlink[x]) if (ok(fail[x],0,1)) return fail[x]; return x; }
    inline void I(int c) { 
        c-='a',s[++n]=c,cur=get_fail(last);
        if (!next[cur][c]) {
            now=new_node(len[cur]+2);
            fail[now]=next[get_fail(fail[cur])][c];
            next[cur][c]=now; pre[now]=cur;
//            dep[now]=dep[fail[now]]+1; //...
            dep[now]=dep[fail[now]]+len[now]; //...
            if (len[now]>1) qlink[now]=ok(fail[now],fail[fail[now]]) ? qlink[fail[now]] : fail[fail[now]];
        }
        last=next[cur][c],cnt[last]++; id[n]=last,no[last]=n; //...
        ans+=dep[last];
    }
    inline void D() { if (p<=1) return; if (!(--cnt[last])) next[pre[last]][s[n]]=0,--p; last=id[--n]; }
    inline void Insert(char s[],int op=0,int _n=0) { 
        if (!_n) _n=strlen(s);  if (!op) rep(i,0,_n) I(s[i]); else per(i,0,_n) I(s[i]); 
    }
    inline void count() { per(i,0,p) cnt[fail[i]]+=cnt[i]; }
    inline void Q(){ /*count();*/ }
};

PAM T;
int _T;
char s[N];

int head[N],nxt[N],tot=0,e[N];
char v[N],c[3];
int n,p;

void ins(int x,int y) {
    e[++tot]=y;
    nxt[tot]=head[x];
    head[x]=tot;
}

//void dfs(int x){
//    T.I(v[x]);
//    for (int i=head[x]; i; i=nxt[i]) dfs(e[i]);
//    T.D();
//}

int sta[N], h[N], m = 0;
void dfs(int x) {
    sta[++m] = x;
    h[m] = head[x]; //T.I(v[x]);
    while (m > 0) {
        int u = h[m]; 
        if (u == head[sta[m]]) T.I(v[sta[m]]);  
        if (u == 0) {
            T.D(); 
            m--; continue; 
        } 
        h[m] = nxt[h[m]];
        sta[++m] = e[u];
        //T.I(v[e[u]]);
        h[m] = head[e[u]];
    }
}

int main() {
//    file_put();
    
    scanf("%d",&_T);
    while (_T--) {
        scanf("%d",&n);
        T.Init();
        mem(head,0);
        mem(nxt,0);
        mem(v,0);
        mem(e,0);
        tot=0;
        int rt=0; v[0] = 'e';
        rep(i,1,n+1) {
            scanf("%s%d",&c,&p);
            //debug(c[0]);
            v[i]=c[0];
            ins(p,i); //else rt=i;
        }
        dfs(0);
        printf("%lld\n",T.ans - 1); 
    }

    return 0;
}
