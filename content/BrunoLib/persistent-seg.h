/**
 * Author: Bruno Emanoel
 * Date: 2026-08-13
 * License: Nao
 * Source: eu
 * Description: seg tree que guarda versões anteriores
 * Time: O(cada operacao),
 * Status: na fe
 */

struct node {
  ll x;
  ll l = -1, r = -1;
  node(ll a) : x(a) {}
  node &combine(const node &a, const node &b) {
    x = a.x + b.x;
    return *this;
  }
};

struct segper {
  v<node> nodes;
  vll ver;
  ll n;
  segper(const vll &a): n((ll)a.size()) {
    ver.emplace_back(build(0,n-1,a));
  }
  void combine(ll i) {
    nodes[i].combine(nodes[nodes[i].l],nodes[nodes[i].r]);
  }
  ll build(ll l, ll r, const vll &a) {
    ll i = nodes.size();
    nodes.emplace_back(a[l]);
    if(l!=r) {
      ll mid = l + (r-l)/2;
      nodes[i].l = build(l,mid,a);
      nodes[i].r = build(mid+1,r,a);
      combine(i);
    }
    return i;
  }
  ll query(ll i, ll l, ll r, ll lef, ll rig) {
    if(l>rig||r<lef) return 0;
    if(lef<=l&&r<=rig) return nodes[i].x;
    ll mid = l + (r-l)/2;
    return query(nodes[i].l,l,mid,lef,rig) + query(nodes[i].r,mid+1,r,lef,rig);
  }
  ll get(ll vr, ll l, ll r) {
    return query(ver[vr],0,n-1,l,r);
  }
  ll update(ll i, ll l, ll r, ll pos, ll x) {
    ll now = nodes.size();
    nodes.emplace_back(nodes[i]);
    if(l==r) {
      nodes[now].x = x;
    }else {
      ll mid = l + (r-l)/2;
      if(pos<=mid) {
        nodes[now].l = update(nodes[now].l,l,mid,pos,x);
      }else {
        nodes[now].r = update(nodes[now].r,mid+1,r,pos,x);
      }
      combine(now);
    }
    return now;
  }
  void set(ll vr, ll i, ll x) {
    ver[vr] = update(ver[vr],0,n-1,i,x);
  }
  void save(ll vr) {
    ver.emplace_back(ver[vr]);
  } 
};