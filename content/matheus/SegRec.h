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