/**
 * Author: Bruno Emanoel
 * Date: 2026-08-13
 * License: Nao
 * Source: eu
 * Description: li chao tree dinamica (com range arbitrária)
 * Time: O(logn),
 * Status: na fe
 */
struct node {
  Line line;
  ll l = -1, r = -1;
  node(): line(0,INF) {}
  node(Line lin): line(lin) {}
  ll operator()(ll x) { return line(x); }
};
node lines[MAXN];
ll sz = 0;
class LiChao {
  public:
  static const ll MIN = -1e5;
  static const ll MAX = 1e5;
  ll root;
  v<Line> raw;
  LiChao() { root = sz++; }
  void add(ll i, ll l, ll r, Line line) {
    ll m = l + (r-l)/2;
    bool lef = line(l) < lines[i](l);
    bool mid = line(m) < lines[i](m);
    if(mid)
      swap(lines[i].line,line);
    if(r-l==1) {
      return;
    }
    if(lef!=mid) {
      if(lines[i].l>=0)
        add(lines[i].l,l,m,line);
      else 
        lines[lines[i].l = sz++].line = line;
    }else {
      if(lines[i].r>=0)
        add(lines[i].r,m,r,line);
      else
        lines[lines[i].r = sz++].line = line;
    }
  }
  /** adds line k*x + b in the tree */
  void add(ll k, ll b) {
    Line l(k,b);
    raw.emplace_back(l);
    add(root,MIN,MAX+1,l);
  }
  ll get(ll i, ll l, ll r, ll x) {
    if(i==-1)
      return INF;
    ll ans = lines[i](x);
    ll m = l + (r-l)/2;
    if(x<m)
      return min(ans,get(lines[i].l,l,m,x));
    return min(ans,get(lines[i].r,m,r,x));
  }
  ll get(ll x) {
    return get(root,MIN,MAX+1,x);
  }
};