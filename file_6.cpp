#include<iostream>
#include<vector>
#define int long long int
using namespace std;
int n,q;
vector<vector<int>>misnomar;
int everday(int x,int exp){
    if(misnomar[exp][x]!=-1)return misnomar[exp][x];
    int prev=everday(x,exp-1);
    return misnomar[exp][x]=everday(prev,exp-1);
}
int kth_ancestor(int x,int k){
        int i=0;
        while(k!=0){
            if(k%2==1)x=everday(x,i);
            i++;k=k/2;
        }
        return x;
}
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>q;
    misnomar.assign(18,vector<int>(n,-1));
    vector<int>dist(n,0);
    misnomar[0][0]=0;
    for(int i=1;i<n;i++){
        cin>>misnomar[0][i];
        misnomar[0][i]--;//zero indexing
        dist[i]=dist[misnomar[0][i]]+1;
    }
    while(q--){
        int a,b;
        cin>>a>>b;
        a--;b--;
        if(a>b){
            int t=b;
            b=a;
            a=t;
        }//a<=b
        if(a==b){cout<<a+1<<'\n';continue;}
        int gap;
        if(dist[b]>dist[a]){
            gap=dist[b]-dist[a];
            b=kth_ancestor(b,gap);
        }else{
            gap=dist[a]-dist[b];
            a=kth_ancestor(a,gap);
        }
        if(a==b){cout<<a+1<<'\n';continue;}
        int start=0;
        int ans=0;
        int end=dist[a];
        while(start<=end){
            int shift=0;
            while(start+shift<=end){
                //checking for 1<<shift
                if(everday(a,shift)==everday(b,shift)){
                    if(dist[ans]<dist[everday(a,shift)])ans=everday(a,shift);
                    break;
                }else{shift++;}
            }
            if(shift==0)break;
            a=everday(a,shift-1);
            b=everday(b,shift-1);
            end=start+(1<<shift);
            start=start+(1<<(shift-1));
        }cout<<ans+1<<'\n';
    }    
}
