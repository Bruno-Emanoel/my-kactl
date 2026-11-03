/**
 * Author: Bruno Emanoel
 * Date: 2026-08-13
 * License: Nao
 * Source: eu
 * Description: constroi a arvore de centroid
 * Essa arvore tem altura O(logn). é possivel fazer queries de caminho sem update em O(nloglogn).
 * Time: O(Nlogn),
 * Status: testado
 */
vll t[MAXN];
vpll centree[MAXN];
ll sz[MAXN];
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

ll query(ll a, ll b) { // example: distância entre dois nós
  if(a==b)
    return 0;
  if(centree[a].size() > centree[b].size()) // a é mais alto
    swap(a,b);
  if(centree[a].size()!=centree[b].size()) { // a é ancestral
    auto cara = centree[b][centree[a].size()];
    if(cara.first == a)
      return cara.second;
  }
  ll lv = centree[a].size()-1;
  for(ll i = LOGN-1; i >= 0; --i) { // normalmente lOGN é 4 ou 5
    if((1<<i) > lv)
      continue;
    if(centree[a][lv - (1<<i)].first == centree[b][lv - (1<<i)])
      continue;
    lv -= 1<<i;
  }
  return centree[a][lv-1].second + centree[a][lv-1].second;
}