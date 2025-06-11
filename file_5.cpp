#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define int int64_t
#define MAX 1000000007
class CurrencySorter{
    public:
        void operator()(vector<int>&arr){
            //in-place sorting
            quick_sort(arr,0,arr.size()-1);
            // sort(arr.begin(),arr.end());
        }
        void quick_sort(vector<int>&arr,int l,int r){
            int pivot=arr[l];
            //pivot will be chosen randomly
            int i=partition(arr,pivot,l,r);
            if(i>l)quick_sort(arr,l,i-1);
            if(i<r)quick_sort(arr,i+1,r);
        }
        int partition(vector<int>&arr,int pivot,int l,int r){
            int i=l,pin=l;
            for(int k=l;k<=r;k++){
                if(arr[k]<pivot)i++;
            }
            int temp=arr[i];
            arr[i]=arr[pin];
            arr[pin]=temp;
            //pivot is placed in the index i
            if(i==l||i==r)return i;
            int p1=l,p2=i+1;
            while(p1<i&&p2<=r){
                if(arr[p1]>pivot&&arr[p2]<=pivot){
                    //swap them
                    int temp=arr[p1];
                    arr[p1]=arr[p2];
                    arr[p2]=temp;
                    p1++;p2++;
                }else if(arr[p1]<=pivot&&arr[p2]<=pivot){
                    p1++;
                }else if(arr[p1]>pivot&&arr[p2]>pivot){
                    p2++;
                }else {
                    p1++;p2++;
                }
            }
            return i;
        }
};
class matrix2_2{
    private:
        int a,b,c,d;
    public:
        matrix2_2(int aa=0,int bb=0,int cc=0,int dd=0){
            a=aa;
            b=bb;
            c=cc;
            d=dd;    
        }
        void operator*(matrix2_2&m2){
            int ta=(a*m2.a%MAX+b*m2.c%MAX)%MAX;
            int tb=(a*m2.b%MAX+b*m2.d%MAX)%MAX;
            int tc=(c*m2.a%MAX+d*m2.c%MAX)%MAX;
            int td=(c*m2.b%MAX+d*m2.d%MAX)%MAX;
            a=ta;
            b=tb;
            c=tc;
            d=td;
        }
        void set(int i,int j,int num){
            if(i==0){
                if(j==0)a=num;
                else b=num;
            }else{
                if(j==0)c=num;
                else d=num;
            }
        }
        int get(int i,int j){
            if(i==0){
                if(j==0)return a;
                else return b;
            }else{
                if(j==0)return c;
                else return d;
            }return 0;
        }
};
class FibonacciGenerator{
    public:
        int operator()(int i){
            matrix2_2 r(1,1,1,0);
            i--;
            matrix2_2 r_i_1(1,0,0,1);
            while(i!=0){
                if(i%2==1)r_i_1*r;
                r*r;
                i=i/2;
            }
            return r_i_1.get(0,0);
        }
};
vector<bool>is_prime;
vector<int>primes;
class PrimeCalculator{
    public:
        PrimeCalculator(){
            is_prime.assign(1e6+1,true);
            int r=1e6+1;
            is_prime[0]=false;
            is_prime[1]=false;
            for(int i=2;i*i<r+1;i++){
                if(is_prime[i]){
                    for(int j=i*i;j<r+1;j=j+i){
                        is_prime[j]=false;
                    }
                }
            }
            for(int i=0;i<1e6+1;i++){
                if(is_prime[i])primes.push_back(i);
            }
        }
        void printPrimes(int l,int r){
            if(l==1)l++;
            vector<bool> isprime(r-l+1,true);
            for(int k:primes){
                int num=k*k;
                if(num<l){
                    num=(l/k);
                    num*=k;
                    if(l%k!=0)num+=k;
                }
                for(;num<=r;num+=k){isprime[num-l]=false;}
            }
            for(int i=0;i<r-l+1;i++){
                if(isprime[i]) cout<<(i+l)<<' ';
            }
            cout<<'\n';
        }
        int printPrimeSum(int l,int r){
            if(l==1)l++;
            int result=0;
            vector<bool> isprime(r-l+1,true);
            for(int k:primes){
                int num=k*k;
                if(num<l){
                    num=(l/k);
                    num*=k;
                    if(l%k!=0)num+=k;
                }
                for(;num<=r;num+=k){isprime[num-l]=false;}
            }
            for(int i=0;i<r-l+1;i++){
                if(isprime[i])result+=i+l;
            }
            return result;
        }
};
class NumberAnalyzer{
    public:
        NumberAnalyzer(){
            is_prime.assign(1e6+1,true);
            int r=1e6+1;
            is_prime[0]=false;
            is_prime[1]=false;
            for(int i=2;i*i<r+1;i++){
                if(is_prime[i]){
                    for(int j=i*i;j<r+1;j=j+i){
                        is_prime[j]=false;
                    }
                }
            }
            for(int i=0;i<1e6+1;i++){
                if(is_prime[i])primes.push_back(i);
            }
        }
        bool isSquareFree(int x){
            if(x<1e6+1){if(is_prime[x])return true;}
            for(int k:primes){
                if(k*k>x)break;
                if(x%k==0){
                    x=x/k;
                    if(x%k==0)return false;
                    else x=x*k;
                }
            }
            return true;
        }
        int countDivisors(int x){
            int num_divisors=0;
            int i=1;
            for(;i*i<x;i++){
                num_divisors+=2*(x%i==0);
            }if(x==i*i)num_divisors++;
            return num_divisors;
        }
        int sumOfDivisors(int x){
            int sum=0;
            int i=1;
            for(;i*i<x;i++){
                if(x%i==0)sum+=i+x/i;
            }if(x==i*i)sum+=i;
            return sum;
        }
};
int32_t main(){
    int type;
    cin>>type;
    if(type==1){
        CurrencySorter sorter;
        int t;
        cin>>t;
        while(t--){
            int n;
            cin>>n;
            vector<int>arr(n);
            for(int&i:arr)cin>>i;
            sorter(arr);
            for(int i:arr)cout<<i<<' ';
            cout<<'\n';
        }
    }
    else if(type==2){
        int t;
        cin>>t;
        FibonacciGenerator fib;
        while(t--){
            int i;
            cin>>i;
            cout<<fib(i)<<'\n';
        }
    }
    else if(type==3){
        int t;
        cin>>t;
        PrimeCalculator prime_cal;
        while(t--){
            string s;
            cin>>s;
            int l,r;
            cin>>l>>r;
            if(s=="printPrimes"){prime_cal.printPrimes(l,r);}
            else cout<<prime_cal.printPrimeSum(l,r)<<'\n';
        }
    }
    else if(type==4){
        int t;
        cin>>t;
        NumberAnalyzer analysis;
        while(t--){
            string s;
            cin>>s;
            int x;
            cin>>x;
            if(s=="isSquareFree"){
                if(analysis.isSquareFree(x))cout<<"yes\n";
                else cout<<"no\n";
            }else if(s=="countDivisors"){
                cout<<analysis.countDivisors(x)<<'\n';
            }else{cout<<analysis.sumOfDivisors(x)<<'\n';}
        }
    }
    else cout<<"invalid type\n";
}
