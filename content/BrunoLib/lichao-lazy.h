/**
 * Author: Bruno Emanoel
 * Date: 2026-08-13
 * License: Nao
 * Source: eu
 * Description: li chao tree onde podemos colocar uma reta em um range e fazer query de minimo
 * Time: O(log²n),
 * Status: na fe
 */
struct node {
  Line line = {0,INF};
  ll min = INF, mini = -1;
  ll l = -1, r = -1;
  node() = default;
  node(ll i): l(i), r(i) {};
  ll operator()(ll x) { return line(x); }
  bool operator<(const node &a) const { 
    return (min<a.min);
  }
  node combine(node a, node b) {
    if(a.l!=-1)
      l = a.l;
    else
      l = b.l;
    if(b.r!=-1)
      r = b.r;
    else
      r = a.r;
    if(l!=-1) {
      if(line(l)<line(r)) {
        mini = l;
        min = line(l);
      }else {
        mini = r;
        min = line(r);
      }
    }else
      mini = -1, min = INF;
    if(std::min(a.min,b.min)<min) {
      if(a.min<b.min)
        min = a.min, mini = a.mini;
      else
        min = b.min, mini = b.mini;
    }
    return *this;
  }
};

class LiChao {
  public:
  ll n;
  v<node> nodes;
  LiChao(ll n): n(n), nodes(2*n) {
    build(0,0,n);
  }
  void build(ll i, ll l, ll r) {
    if(r-l==1) {
      nodes[i] = node(l);
      return;
    }
    ll m = l + (r-l)/2;
    nodes[i].l = l;
    nodes[i].r = r-1;
    build(i+1,l,m);
    build(i+2*(m-l),m,r);
  }
  node add(ll i, ll l, ll r, Line line) {
    ll m = l + (r-l)/2;
    bool lef = line(l) < nodes[i](l);
    bool mid = line(m) < nodes[i](m);
    if(mid)
      swap(nodes[i].line,line);
    if(r-l==1) {
      if(nodes[i].l!=-1) {
        nodes[i].min = nodes[i](l);
        nodes[i].mini = l;
      }
      return nodes[i];
    }
    if(lef!=mid)
      add(i+1,l,m,line);
    else
      add(i+2*(m-l),m,r,line);
    return nodes[i].combine(nodes[i+1],nodes[i+2*(m-l)]);
  }
  node add(ll i, ll l, ll r, ll lef, ll rig, Line line) {
    if(rig<=l||r<=lef) return nodes[i];
    if(lef<=l&&r<=rig) return add(i,l,r,line);
    ll m = l + (r-l)/2;
    // propaga
    add(i+1,l,m,nodes[i].line);
    add(i+2*(m-l),m,r,nodes[i].line);
    // continua adicionando
    add(i+1,l,m,lef,rig,line);
    add(i+2*(m-l),m,r,lef,rig,line);
    nodes[i].line = {0,INF};
    return nodes[i].combine(nodes[i+1],nodes[i+2*(m-l)]);
  }
  void add(ll l, ll r, ll k, ll b) {
    Line lin(k,b);
    add(0,0,n,l,r+1,lin);
  }
  node next(){return nodes[0]; }
  node use(ll i, ll l, ll r, ll x) {
    if(x<l||x>=r) return nodes[i];
    if(r-l==1) {
      nodes[i].l = nodes[i].r = -1;
      nodes[i].mini = -1;
      nodes[i].min = INF;
      return nodes[i];
    }
    ll m = l + (r-l)/2;
    return nodes[i].combine(
      use(i+1,l,m,x),
      use(i+2*(m-l),m,r,x)
    );
  }
  void use(ll x) { use(0,0,n,x); }
};
constexpr ll MAXN = 1e5;
v<tuple<ll,ll,ll,ll>> g[MAXN];
