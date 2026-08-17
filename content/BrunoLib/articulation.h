/**
 * Author: Bruno Emanoel
 * Date: 2026-08-13
 * License: Nao
 * Source: eu
 * Description: acha pontos de articulacao
 * Time: O(N+E),
 * Status: na fe
 */
constexpr ll MAXN = 10;
vll g[MAXN];
ll tin[MAXN], low[MAXN];
bool vis[MAXN];
ll now = 0;
vll articulation;

// Find Articulation points of the graph in O(N+M) in the dfs
// Articulation points are vertices that when removed will increase the number of connected components
void find_articulation(ll u = 0, ll p = -1) {
  vis[u] = true;
  tin[u] = low[u] = now++;
  int child = 0;
  foreach(w,g[u]) if(w!=p) {
    if(vis[w]) {
      low[u]= min(low[u],tin[w]);
    }else {
      find_articulation(w,u);
      low[u]=min(low[u],low[w]);
      if(low[w]>=tin[u]&&p!=-1)
        articulation.emplace_back(u);
      child++;
    }
  }
  if(p==-1&&child>1)
    articulation.emplace_back(u);
}