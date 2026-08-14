/**
 * Author: Bruno Emanoel
 * Date: 2026-08-13
 * License: Nao
 * Source: eu
 * Description: stack e queue com operações de olhar mínimo/máximo
 * Time: O(1),
 * Status: na fé
 */
struct minStack {
struct node {
  ll val, min, prop;
};
  stack<node> st;
  minStack() {
    st.emplace(INF,INF,0);
  }
  ll minimum() { return st.top().min + st.top().prop; }
  void push(ll x) { st.emplace(x,min(x,st.top().min+st.top().prop), 0); }
  ll pop() {
    ll ret = st.top().val;
    ll prop = st.top().prop;
    st.pop();
    sum(prop);
    return ret + prop;
  }
  bool empty() { return st.top().val == INF; }
  void sum(ll x) {
    if(!empty())
      st.top().prop += x;
  }
  ll size() { return st.size()-1; }
};

struct minQueue {
  minStack S1, S2;
  minQueue() {}
  ll minimum() { return min(S1.minimum(),S2.minimum()); }
  void push(ll x) { S1.push(x); }
  ll pop() {
    if(S2.empty())
      while(!S1.empty())
        S2.push(S1.pop());
    return S2.pop();
  }
  void sum(ll x) {
    S1.sum(x), S2.sum(x);
  }
  bool empty() { return S1.empty()&&S2.empty(); }
  ll size() { return S1.size() + S2.size(); }
};