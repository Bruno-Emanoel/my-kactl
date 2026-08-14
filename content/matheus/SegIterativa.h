#include <bits/stdc++.h>
using namespace std;
 
#define int long long
#define pb push_back
#define v vector
#define get(a) for(int i =0; i<a.size(); i++){cin>>a[i];}
#define INF 1000000000000000000
#define NINF -1*1000000000000000000
#define ll long long
#define full(a) a.begin(),a.end()
#define sz(x) (int)x.size()
#define loop(nome,s,e) for(int nome = s; nome<e; nome++)
const int mod = 1e9+7;

struct Node {
    int sum;
    int toadd;
    Node(){
        sum=0;
        toadd=0;
    }
    Node(int val){
        sum=val;
        toadd=0;
    }
    Node operator+(const Node& other) const {
        return Node(this->sum + other.sum);
    }
};
class segmae {
private:
    int n;
    std::vector<Node> segtree;
public:
    segmae(int size) {
        n = 1;
        while( n < size){
            n <<= 1;
        }
        segtree.assign(2 * n, Node());
    }
    segmae(v<int> &lista) {
        n=1;
        while(n < lista.size()){
            n<<=1;
        }
        segtree.assign(2 * n, Node());
        for (int i = 0; i < lista.size(); i++) {
            segtree[n + i] = Node(lista[i]);
        }
        for (int i = n - 1; i > 0; --i) {
            segtree[i] = segtree[i << 1] + segtree[i << 1 | 1];
        }
    }
    void apply(int p, int value, int lenght) {
        segtree[p].sum += value * lenght;
        if (p < n) {
            segtree[p].toadd += value;
        }
    }
    void pull(int p, int lenght){
        Node aux = segtree[p << 1] + segtree[p << 1 |1];
        segtree[p].sum=aux.sum;
        segtree[p].sum +=segtree[p].toadd*lenght;
    }
    void push(int p, int lenght){
        apply(2*p,segtree[p].toadd, lenght >> 1);
        apply(2*p | 1,segtree[p].toadd, lenght >> 1);
        segtree[p].toadd=0;
    }
    void update(int L, int R,int val){
        int l =L+n;
        int r = R+n;
        int h = __builtin_ctz(n);
        for(int s = h; s>0; s--){
            push(l >> s, 1 << s);
            push(r >> s, 1 << s);
        }
        int lc = l;
        int rc = r;
        int len = 1;
        for(; l<=r; l>>=1, r>>=1, len<<=1){
            if (l & 1) apply(l++,val,len);
            if (!(r & 1)) apply(r--,val,len);
        }
        len = 2;
        for(l = lc >> 1; l>0; l>>=1, len <<=1){
            pull(l,len);
        }
        len=2;
        for(r = rc>>1; r>0; r>>=1, len <<=1){
            pull(r,len);
        }
    }
    int rangequery(int l, int r) {
        l+=n;
        r+=n;
        int h = __builtin_ctz(n);
        for(int s = h; s>0; s--){
            push(l >> s, 1 << s);
            push(r >> s, 1 << s);
        }
        Node ansL;
        Node ansR;
        for(; l<=r; l>>=1, r>>=1){
            if(l & 1) ansL= ansL + segtree[l++];
            if(!(r & 1)) ansR= segtree[r--] + ansR;
        }
        return (ansL + ansR).sum;
    }
    void point_update(int p, int val){ //ESSA PORRA NÃO FUNCIONA, É PARA SER ADAPTADO APENAS
        int idx = p + n;
        segtree[idx] = Node(val);
        for (idx >>= 1; idx > 0; idx >>= 1) {
            segtree[idx] = segtree[idx << 1] + segtree[idx << 1 | 1];
        }
    }
};