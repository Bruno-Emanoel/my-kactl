/**
 * Author: Bruno Emanoel
 * Date: 2026-08-13
 * License: Nao
 * Source: eu
 * Description: automato do kmp com suporte para push e pop
 * Time: O(cada operacao),
 * Status: na fe
 */
constexpr ll RAN = 'z'-'a'+1;
class KMPAuth {
  public:
  ll n = 0;
  string P = "";
  v<array<ll,RAN>> neighbor = {array<ll,RAN>{0}}; 
  vll ans = {0};
  vpll st;
  KMPAuth(ll m) {
    P.reserve(m);
    neighbor.reserve(m);
    ans.reserve(m);
    st.reserve(m);
  }
  KMPAuth(string S): KMPAuth(S.size()) { foreach(c,s) push(c); }
  void push(char c) {
    P.push_back(c);
    ll neigh= neighbor.back()[c-'a'];
    ++n;
    st.emplace_back(c-'a',neigh);
    neighbor[n-1][c-'a'] = n;
    neighbor.push_back(neighbor[neigh]);
    ans.push_back((n-neigh) == ans[neigh] ? ans[neigh] : n);
  }
  void pop() {
    --n;
    P.pop_back();
    neighbor.pop_back();
    neighbor.back()[st.back().first] = st.back().second;
    st.pop_back();
    ans.pop_back();
  }
};