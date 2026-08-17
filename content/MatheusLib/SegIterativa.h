/**
 * Author: Matheus Dias Queiroz
 * Date: 13-08-2027
 * License: no
 * Source: folklore
 * Description: Calculates a valid assignment to boolean variables a, b, c,... to a 2-SAT problem,
 * so that an expression of the type $(a||b)\&\&(!a||c)\&\&(d||!b)\&\&...$
 * becomes true, or reports that it is unsatisfiable.
 * Negated variables are represented by bit-inversions (\texttt{\tilde{}x}).
 * Usage:
 *  TwoSat ts(number of boolean variables);
 *  ts.either(0, \tilde3); // Var 0 is true or var 3 is false
 *  ts.setValue(2); // Var 2 is true
 *  ts.atMostOne({0,\tilde1,2}); // <= 1 of vars 0, \tilde1 and 2 are true
 *  ts.solve(); // Returns true iff it is solvable
 *  ts.values[0..N-1] holds the assigned values to the vars
 * Time: O(N+E), where N is the number of boolean variables, and E is the number of clauses.
 * Status: stress-tested
 */
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
    void point_update(int p, int val){ //ESSA PORRA NAO FUNCIONA, EH PARA SER ADAPTADO APENAS
        int idx = p + n;
        segtree[idx] = Node(val);
        for (idx >>= 1; idx > 0; idx >>= 1) {
            segtree[idx] = segtree[idx << 1] + segtree[idx << 1 | 1];
        }
    }
};