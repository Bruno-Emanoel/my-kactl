/**
 * Author: Bruno Emanoel
 * Date: 2026-08-13
 * License: Nao
 * Source: eu
 * Description: constroi a arvore de centroid
 * Essa arvore tem altura O(logn). e possivel fazer queries em range sem update.
 * Time: O(Nlogn),
 * Status: na fe
 */
vll t[MAXN];
vpll centree[MAXN];
ll ans[MAXN], sz[MAXN];
bitset<MAXN> removed;

ll get_sz(ll u, ll p) {
  sz[u] = 1;
  for(auto w:t[u]) if(w!=p&&!removed[w])
    sz[u] += get_sz(w,u);
  return sz[u];
}

ll get_centroid(ll u, ll p, ll n) {
  for(auto w:t[u])
    if(w!=p&&!removed[w]&&sz[w]*2>n)
      return get_centroid(w,u,n);
  return u;
}

void next_level(ll u, ll p, ll cent, ll d = 1) {
  centree[u].emplace_back(cent,d);
  for(auto w:t[u]) if(w!=p&&!removed[w])
    next_level(w,u,cent,d+1);
}

void decompose(ll u) {
  get_sz(u,u);
  ll centroid = get_centroid(u,u,sz[u]);
  removed[centroid] = true;
  for(auto w:t[centroid])
    if(!removed[w]) {
      next_level(w,centroid,centroid);
      decompose(w);
    }
}