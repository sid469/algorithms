#include<iostream>
 
#include<vector>
 
#include<queue>
 
#include<stack>
 
using namespace std;
#define int long long int
#define mod 1000000007
int32_t main(){
 
ios_base::sync_with_stdio(false);
 
cin.tie(0);
 
int n,m;
 
cin>>n>>m;
 
vector<vector<int>>edge_list(n);
 
vector<int>indegree(n,0);
 
vector<int>dist(n,0);
 
vector<int>ancestor(n,n);
 
for(int i=0;i<m;i++){
 
int a,b;
 
cin>>a>>b;
 
a--;b--;
 
indegree[b]++;
 
edge_list[a].push_back(b);
 
}
 
queue<int>q;
 
vector<int>topo_order;
 
for(int i=0;i<n;i++)if(indegree[i]==0)q.push(i);
 
ancestor[0]=0;
 
dist[0]=1;
 
while(!q.empty()){
 
int top=q.front();
 
q.pop();
 
topo_order.push_back(top);
 
for(int j:edge_list[top]){
dist[j]=(dist[j]+ dist[top])%mod;
 
indegree[j]--;
 
if(indegree[j]==0){
 
q.push(j);
 
}
 
}
 
}
 
if(dist[n-1]!=-1){
 
cout<<dist[n-1]<<'\n';
 
 
 
}else{
 
cout<<"IMPOSSIBLE\n";
 
}
 
}
