#include<iostream>
#include<vector>
#include<set>
using namespace std;
class dsu{
    private:
        int n;
        vector<int>parent;
        vector<int>size;
    public:
        dsu(int n=0){
            parent.assign(n,0);
            size.assign(n,1);
            for(int i=0;i<n;i++)parent[i]=i;
        }
        int findParent(int v){
            if(parent[v]==v)return v;
            return parent[v]=findParent(parent[v]);
        }
        void unionBySize(int a,int b){
            a=findParent(a);
            b=findParent(b);
            if(size[a]>size[b]){
                int temp=a;
                a=b;
                b=temp;
            }
            //size[a]<=size[b]
            if(is_connected(a,b))return;
            size[a]+=size[b];
            parent[b]=a;
        }
        bool is_connected(int a,int b){
            return findParent(a)==findParent(b);
        }
        int get_size(int a){
            return size[a];
        }
};
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    dsu mst(n);
    set<pair<int,int>>comp;
    for(int i=0;i<n;i++)comp.insert({mst.get_size(i),i});
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        a--;b--;
        a=mst.findParent(a);b=mst.findParent(b);
        comp.erase({mst.get_size(a),a});
        comp.erase({mst.get_size(b),b});
        mst.unionBySize(a,b);
        comp.insert({mst.get_size(mst.findParent(a)),mst.findParent(a)});
        cout<<comp.size()<<' '<<(--comp.end())->first<<'\n';
    }
}
