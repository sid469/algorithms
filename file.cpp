#include<iostream>
#include<vector>
#include<stack>
using namespace std;
stack<int>order;
vector<vector<int>>edge_list;
vector<vector<int>>d;
vector<bool>visited;
vector<int>answer;
int n,m;
void dfs1(int v){
    visited[v]=true;
    for(int i:edge_list[v]){
        if(!visited[i])dfs1(i);
    }
    order.push(v);
}
int index;
void dfs2(int v){
    visited[v]=true;
    answer[v]=index;
    for(int i:d[v]){
        if(!visited[i])dfs2(i);
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    edge_list.resize(n);
    d.resize(n);
    visited.assign(n,false);
    answer.assign(n,-1);
    index=1;
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        a--;b--;
        edge_list[a].push_back(b);
        d[b].push_back(a);
    }
    for(int i=0;i<n;i++){
        if(!visited[i])dfs1(i);
    }visited.assign(n,false);
    while(!order.empty()){
        int top=order.top();
        if(visited[top]==false){
            dfs2(top);
            index++;
        }
        order.pop();
    }
    cout<<index-1<<'\n';
    for(int i:answer)cout<<i<<' ';cout<<'\n';
}
