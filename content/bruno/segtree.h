/**
 * Author: Bruno Emanoel
 * Date: 2026-08-13
 * License: Nao
 * Source: eu
 * Description: segtree
 * Time: O(1),
 * Status: na fé
 */
struct node {
  ll x=0;
  node() = default;
  node(ll a): x{a} {};
  node operator+(const node&a) {
    return x+a.x;
  }
};

class Seg {
  public:
  size_t n, size;
  vector<node> nodes;
  Seg(const vector<ll> &data): n{data.size()}, size{2*n}, nodes(size)  {
    build(0,0,n-1,data);
  }
  node build(ll i, ll l, ll r, const vector<ll> &data) {
    if(l==r) return nodes[i] = node(data[l]);
    ll mid = l+(r-l)/2;
    return nodes[i] = build(i+1,l,mid,data)+build(i+(mid-l+1)*2,mid+1,r,data);
  }
  node query(ll i, ll lef, ll rig, ll l, ll r) {
    if(r<lef||rig<l) return node();
    if(lef<=l&&r<=rig) return nodes[i];
    ll mid = l+(r-l)/2;
    return query(i+1,lef,rig,l,mid)+query(i+2*(mid-l+1),lef,rig,mid+1,r);
  }
  node operator()(ll l, ll r) {
    return query(0,l,r,0,n-1);
  }
  node update(ll i, ll ind, ll val, ll l, ll r) {
    if(l==r&&l==ind) return nodes[i] = node(val);
    ll mid = l+(r-l)/2;
    if(ind<=mid) 
      return nodes[i] = update(i+1,ind,val,l,mid)+nodes[i+2*(mid-l+1)];
    return nodes[i]= nodes[i+1]+update(i+2*(mid-l+1),ind,val,mid+1,r);
  }
  void upd(ll ind, ll val) {
    update(0,ind,val,0,n-1);
  }
};