#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;
#define int long long int
#define float long double
class complex{
    private:
        int real;
        int imaginary;
    public:
        complex(int r=0,int i=0){
            real=r;imaginary=i;
        }
        complex operator*(complex&c2){
            complex c;
            c.real=real*c2.real-imaginary*c2.imaginary;
            c.imaginary=imaginary*c2.real+real*c2.imaginary;
            return c;
        }
        complex operator+(complex&c2){
            complex c;
            c.real=real+c2.real;
            c.imaginary=imaginary+c2.imaginary;
            return c;
        }
        complex operator-(complex&c2){
            complex c;
            c.real=real-c2.real;
            c.imaginary=imaginary-c2.imaginary;
            return c;
        }
        void set(int r,int i){
            real=r;
            imaginary=i;
        }
        void print(){
            cout<<real<<" "<<imaginary;
        }
};
istream& operator>>(istream& s,complex& c){
    int a;
    int b;
    s>>a;
    s>>b;
    c.set(a,b);
    return s;
}
ostream& operator<<(ostream& s,complex& c){
    c.print();
    return s;
}
complex operator*(int k,complex&c1){
    //this is written because in the evaluation process this it is multiplied with coeff
    complex c(k,0);
    return c1*c;
}
string operator*(int k,string s){
    //also used in the evaluation
    string ans;
    for(int i=0;i<k;i++)ans+=s;
    return ans;
}
string operator*(string s,int k){
    return k*s;
}
template<typename type>
class evaluation{
    private:
        vector<type>poly;
    public:
        evaluation(vector<type>&p){
            poly=p;
        }
        type evaluate(int t){
            int x_i=1;
            type fx=type();
            int degree=poly.size();
            for(int i=0;i<degree;i++){
                fx=x_i*poly[i]+fx;
                x_i=x_i*t;
            }return fx;
        }
};
template <typename var>
class multiplication{
    private:
        vector<var>poly1;
    public:
        multiplication(vector<var>&p){
            poly1=p;
        }
        vector<var> operator*(vector<var>poly2){
            int degree=max(poly1.size(),poly2.size());
            while((int)poly1.size()<degree){poly1.push_back(0);}
            while((int)poly2.size()<degree){poly2.push_back(0);}
            int newSize = 1;
            while(newSize < max(poly1.size(), poly2.size())) newSize *= 2;
            poly1.resize(newSize, var());
            poly2.resize(newSize, var());
            return karastuba(poly1,poly2);
        }
        vector<var> karastuba(vector<var>&p1,vector<var>&p2){
            if(p1.size()==1){
                vector<var>finale;
                finale.push_back(p1[0]*p2[0]);
                return finale;
            }
            int size=p1.size();
            if(size%2==1){
                size++;
                p1.push_back(var());
                p2.push_back(var());
            }
            vector<var>a;
            vector<var>b;
            for(int i=0;i<p1.size();i++){
                if(i<size/2)a.push_back(p1[i]);
                else b.push_back(p1[i]);
            }
            vector<var>c;
            vector<var>d;
            for(int i=0;i<p2.size();i++){
                if(i<size/2)c.push_back(p2[i]);
                else d.push_back(p2[i]);
            }
            vector<var>a_b;
            for(int i=0;i<(int)a.size();i++)a_b.push_back(a[i]+b[i]);
            vector<var>c_d;
            for(int i=0;i<(int)c.size();i++)c_d.push_back(c[i]+d[i]);
            //ac
            vector<var>ac=karastuba(a,c);
            //bd 
            vector<var>bd=karastuba(b,d);
            //(a+b)(c+d)
            vector<var>abcd=karastuba(a_b,c_d);
            //(a<<n+b)*(c<<n+d)==a*c<<2n+(ad+bc)<<n+bd
            //ad+bc==(a+b)*(c+d)-ac-bd
            vector<var>result(size*2-1);
            for(int i=0;i<(int)ac.size();i++)result[i]=result[i]+ac[i];
            for(int i=0;i<(int)bd.size();i++)result[i+size*2-1-(int)bd.size()]=result[i+size*2-1-(int)bd.size()]+bd[i];
            for(int i=0;i<(int)abcd.size();i++){
                result[i+b.size()]=result[i+b.size()]+abcd[i]-ac[i]-bd[i];
            }
            return result;
        }
};
template<typename kind>
class differentiation{
    private:
        vector<kind>poly;
    public:
        differentiation(vector<kind>&p){
            poly=p;
        }
        vector<kind> derivate(){
            vector<kind>dfx;
            int degree=poly.size();
            for(int i=1;i<degree;i++){
                dfx.push_back(i*poly[i]);
            }
            return dfx;
        }
};
int32_t main(){
    int q;
    cin>>q;
    while(q--){
        int op;
        cin>>op;
        if(op==1){
            //this is multiplication
            string s;
            cin>>s;
            if(s=="integer"){
                int deg1;
                cin>>deg1;
                vector<int>poly1(deg1);
                for(int i=0;i<deg1;i++)cin>>poly1[i];
                int deg2;
                cin>>deg2;
                vector<int>poly2(deg2);
                for(int i=0;i<deg2;i++)cin>>poly2[i];
                multiplication<int>result(poly1);
                vector<int>final=result*poly2;
                int k=0;
                for(int i:final){if(k>=deg1+deg2-1)break;cout<<i<<" ";k++;}
                cout<<"\n";
            }else if(s=="float"){
                int deg1;
                cin>>deg1;
                vector<double>poly1(deg1);
                for(int i=0;i<deg1;i++)cin>>poly1[i];
                int deg2;
                cin>>deg2;
                vector<double>poly2(deg2);
                for(int i=0;i<deg2;i++)cin>>poly2[i];
                multiplication<double>result(poly1);
                vector<double>final=result*poly2;
                int k=0;
                for(double i:final){if(k>=deg1+deg2-1)break;cout<<fixed<<setprecision(6)<<i<<" ";k++;}
                cout<<"\n";
            }else if(s=="complex"){
                int deg1;
                cin>>deg1;
                vector<complex>poly1(deg1);
                for(int i=0;i<deg1;i++)cin>>poly1[i];
                int deg2;
                cin>>deg2;
                vector<complex>poly2(deg2);
                for(int i=0;i<deg2;i++)cin>>poly2[i];
                multiplication<complex>result(poly1);
                vector<complex>final=result*poly2;
                int k=0;
                for(complex i:final){if(k>=deg1+deg2-1)break;cout<<i<<" ";k++;}
                cout<<'\n';
            }
        }else if(op==2){
            //this is  evaluation
            string s;
            cin>>s;
            int deg;
            cin>>deg;
            if(s=="integer"){
                vector<int>poly(deg);
                for(int i=0;i<deg;i++)cin>>poly[i];
                int x;
                cin>>x;
                evaluation<int>result(poly);
                cout<<result.evaluate(x)<<'\n';
            }else if(s=="float"){
                vector<float>poly(deg);
                for(int i=0;i<deg;i++)cin>>poly[i];
                int x;
                cin>>x;
                evaluation<float>result(poly);
                cout<<fixed<<setprecision(6)<<result.evaluate(x)<<'\n';
            }else {
                vector<string>poly(deg);
                for(int i=0;i<deg;i++)cin>>poly[i];
                int x;
                cin>>x;
                evaluation<string>result(poly);
                cout<<result.evaluate(x)<<'\n';
            }
        }else {
            //this is differentiation
            string s;
            cin>>s;
            int deg;
            cin>>deg;
            if(s=="integer"){
                vector<int>poly(deg);
                for(int i=0;i<deg;i++)cin>>poly[i];
                differentiation<int>result(poly);
                vector<int>final=result.derivate();
                for(int i:final)cout<<i<<" ";
                cout<<'\n';
            }else {
                vector<float>poly(deg);
                for(int i=0;i<deg;i++)cin>>poly[i];
                differentiation<float>result(poly);
                vector<float>final=result.derivate();
                for(float f:final)cout<<fixed<<setprecision(6)<<f<<" ";
                cout<<'\n';
            }
        }
    }
}
