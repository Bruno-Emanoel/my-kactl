#include <bits/stdc++.h>
using namespace std;
#define v vector
#define int long long
#define pb push_back
#define ll long long
#define INF LLONG_MAX
#define NINF LLONG_MIN
#define full(a) a.begin(),a.end()
#define get(a) for(int i=0; i<a.size(); i++){cin>>a[i];}
#define db long double
#define debugm(a) for(int i =0; i<a.size(); i++){for(int j = 0; j<a[i].size(); j++){cout<<a[i][j]<<" ";}cout<<endl;}cerr<<endl; 
#define debugl(a) for(int i =0; i<a.size(); i++){cout<<a[i]<<" ";} cerr<<endl;
#define vi vector<int>
#define sz(a) (int)a.size()
#define rep(i,s,n) for(int i =s; i<n; i++)
#define all(a) a.begin(),a.end()

struct node{
    int val;
    int toadd;
    bool tozero;
    node() : val(0), toadd(0), tozero(false) {}
    node(int valor) : val(valor),toadd(0),tozero(false) {}
    node operator+(const node &other){
        return node(val+other.val);
    }
};

class segmae{

    public: int n;

    v<node> segtree;

    segmae(int n){
        this->n =n;
        this->segtree = v<node>(4*n);
    }
    void propagate(int i,int left, int right){
        if(left==right) return;
        int mid = (left + (right-left)/2);
        if(segtree[i].tozero){
            segtree[2*i+1].tozero=true;
            segtree[2*i+1].toadd=segtree[2*i+1].val=0;
            segtree[2*i].tozero=true;
            segtree[2*i].toadd=segtree[2*i].val=0;
            segtree[i].tozero=false;
        }
        segtree[2*i+1].toadd+=segtree[i].toadd;
        segtree[2*i+1].val+=(segtree[i].toadd)*(right-mid);
        segtree[2*i].toadd+=segtree[i].toadd;
        segtree[2*i].val+=segtree[i].toadd*(mid-left+1);
        segtree[i].toadd=0;
    }

    void rangeadd(int lq, int rq, int left, int right, int i, int val=1){
        if(lq > right || rq < left){
            return;
        }
        if(lq <= left && rq >= right){
            segtree[i].toadd+=val;
            segtree[i].val+=(right-left+1)*val;
            return;
        }
        int mid = left+(right-left)/2;
        propagate(i,left,right);
        rangeadd(lq,rq,left,mid,2*i,val);
        rangeadd(lq,rq,mid+1,right,2*i+1,val);
        segtree[i] = segtree[2*i] + segtree[2*i+1];
    }

    void rangezero(int lq, int rq, int left, int right, int i){
        if(lq > right || rq < left){
            return;
        }
        if(lq <= left && rq >= right){
            segtree[i].tozero=true;
            segtree[i].val=segtree[i].toadd=0;
            return;
        }
        int mid = left + (right-left)/2;
        propagate(i,left,right);
        rangezero(lq,rq,left,mid,2*i);
        rangezero(lq,rq,mid+1,right,2*i+1);
        segtree[i] = segtree[2*i] + segtree[2*i+1];
    }

    int query(int lq, int rq, int left, int right, int i){
        if(lq > right || rq < left){
            return 0;
        }
        if(lq <=left && rq >=right){
            return segtree[i].val;
        }
        int mid = left + (right-left)/2;
        propagate(i,left,right);
        return query(lq,rq,left,mid,2*i) + query(lq,rq,mid+1,right,2*i+1);
    }

    void rangeadd(int lq, int rq,int val=1){
        rangeadd(lq,rq,0,n-1,1,val);
    }
    void rangezero(int lq,int rq){
        rangezero(lq,rq,0,n-1,1);
    }
    int query(int lq,int rq){
        return query(lq,rq,0,n-1,1);
    }
};