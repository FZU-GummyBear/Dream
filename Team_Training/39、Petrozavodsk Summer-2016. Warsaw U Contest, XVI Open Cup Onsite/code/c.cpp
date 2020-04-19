#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
#define MAXN 500001
using namespace std;
typedef pair<int,int> Pair;
vector<int> v[MAXN];
int used[MAXN];
int id[MAXN],c[MAXN],cnt;
pair<int,int> dp[MAXN];
int sum[MAXN];
bool dfs1(int i)
{
        used[i]=1;
        for(int j:v[i]){
                if(used[j]==1){c[0]=j;c[++cnt]=i;return true;}
                if(!used[j]&&dfs1(j)){
                        if(c[cnt]!=c[0])c[++cnt]=i;
                        return true;
                }
        }
        used[i]=2;
        return false;
}
bool findCycle(int n)
{
        memset(used+1,0,sizeof(used));
        for(int i=1;i<=cnt;i++)
                used[c[i]]=2;
        for(int i=1;i<=n;i++){
                if(!used[i]&&dfs1(i)){
                        reverse(c+1,c+cnt+1);
                        for(int i=1;i<=cnt;i++)
                                id[c[i]]=i;
                        return true;
                }
        }
        return false;
}
void update(Pair &p1,Pair p2){
        p1.first=min(p1.first,p2.first);
        p1.second=max(p1.second,p2.second);
}
Pair dfs2(int i)
{
        if(dp[i].first)return dp[i];
        Pair ret={1<<30,0};
        for(int j:v[i]){
                if(id[j])update(ret,{id[j],id[j]});
                else update(ret,dfs2(j));
        }
        return dp[i]=ret;
}
int dfs3(int i,int x)
{
        int ret=0;
        used[i]=1;
        for(int j:v[i]){
                if(id[j]){
                        if(id[j]<=x)ret=max(ret,id[j]);
                }
                else if(!used[j])ret=max(ret,dfs3(j,x));
        }
        return ret;
}
int main()
{
        int n,m,x,y;
        scanf("%d%d",&n,&m);
        for(int i=0;i<m;i++){
                scanf("%d%d",&x,&y);
                v[x].push_back(y);
        }
        if(!findCycle(n))printf("NIE");
        else if(findCycle(n))printf("0");
        else{
                int l=1,r=cnt;
                memset(used+1,0,sizeof(int)*n);
                for(int i=cnt;i;i--){
                        int pos=dfs3(c[i],i);
                        if(pos){l=max(l,pos);r=i;}
                        else if(dfs2(c[i]).first<=i)r=i;
                }
                vector<int> ans;
                for(int i=1;i<=cnt;i++){
                        int t=dfs2(c[i]).second;
                        if(t>i){sum[i+1]++;sum[t]--;}
                }
                for(int i=1;i<=cnt;i++){
                        sum[i]+=sum[i-1];
                        if(sum[i]==0&&i>=l&&i<=r)
                                ans.push_back(c[i]);
                }
                sort(ans.begin(),ans.end());
                printf("%d\n",ans.size());
                for(auto i:ans)
                        printf("%d ",i);
        }
}

