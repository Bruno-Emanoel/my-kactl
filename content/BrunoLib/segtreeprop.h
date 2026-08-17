/**
 * Author: Bruno Emanoel
 * Date: 2026-08-13
 * License: Nao
 * Source: eu
 * Description: segtree com lazy propagation
 * Time: O(1),
 * Status: na fe
 */
struct node{
    ll val = 0;
    ll tosum=0;
    bool tozero=false;
    node() = default;
    node(ll x): val(x) {}
    ll value() const {
        return (val+tosum)*(1-tozero);
    }
    node operator+(const node &a) {
        return node(value()+a.value());
    }
    void zera() {
        val =  tosum = 0;
        tozero = true;
    }
};
 
struct Seg{
    ll n;
    v<node> nodes;
    Seg(ll n) : n(n), nodes(2*n) {}
    void propaga(ll i, ll l, ll r) {
        if(nodes[i].tozero&&l!=r) {
            ll mid = l +(r-l)/2;
            nodes[i+1].zera();
            nodes[i+2*(mid-l+1)].zera();
            nodes[i] = nodes[i+1] + nodes[i+2*(mid-l+1)];
        }
        if(nodes[i].tozero&&l==r) 
            nodes[i] = node();
    }
    void propsum(ll i, ll l, ll r) {
        if(nodes[i].tosum) {
            ll mid = l+(r-l)/2;
            if(l!=r) {
                propaga(i+1,l,mid);
                propaga(i+2*(mid-l+1),mid+1,r);
                ll numupd = nodes[i].tosum/(r-l+1);
                nodes[i+1].tosum += numupd*(mid-l+1);
                nodes[i+2*(mid-l+1)].tosum += numupd*(r-mid);
                nodes[i] = nodes[i+1] + nodes[i+2*(mid-l+1)];
            }else {
                nodes[i] = nodes[i].value();
            }
        }
    }
    node query(ll i, ll lef, ll rig, ll l, ll r) {
        if(r<lef||rig<l||nodes[i].tozero) return node();
        if(l>=lef&&r<=rig) return nodes[i];
        ll mid = l + (r-l)/2;
        propsum(i,l,r);
        return query(i+1,lef,rig,l,mid) + query(i+2*(mid-l+1),lef,rig,mid+1,r);
    }
    ll operator()(ll l, ll r) {
        return query(0,max(0LL,l),min(r,n-1),0,n-1).value();
    }
    node zera(ll i, ll lef, ll rig, ll l, ll r) {
        if(r<lef||rig<l||nodes[i].tozero) return nodes[i];
        if(lef<=l&&r<=rig) {
            nodes[i].zera();
            return nodes[i];
        }
        ll mid = l +(r-l)/2;
        propsum(i,l,r);
        return nodes[i] = zera(i+1,lef,rig,l,mid) + zera(i+2*(mid-l+1),lef,rig,mid+1,r); 
    }
    void zera(ll l, ll r) {
        zera(0,max(0LL,l),min(r,n-1),0,n-1);
    }
    node update(ll i, ll lef, ll rig, ll l, ll r) {
        if(r<lef||rig<l) return nodes[i];
        propaga(i,l,r);
        if(lef<=l&&r<=rig) {
            nodes[i].tosum += r-l+1;
            return nodes[i];
        }
        ll mid = l+(r-l)/2;
        propsum(i,l,r);
        return nodes[i] = update(i+1,lef,rig,l,mid) + update(i+2*(mid-l+1),lef,rig,mid+1,r);
    }
    void upd(ll l ,ll r) {
        update(0,max(0LL,l),min(r,n-1),0,n-1);
    }
};