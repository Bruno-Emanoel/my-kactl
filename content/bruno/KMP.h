/**
 * Author: Bruno Emanoel
 * Date: 2026-08-13
 * License: Nao
 * Source: eu
 * Description: KMP like an automathon
 * Time: O(n),
 * Status: na fé
 */
class KMP {
  public:
  size_t n;
  string P;
  vector<int> neighbor; // <- lps
  KMP(string p): n{p.size()}, P(p), neighbor(n+1) {
    for(int i = 1; i < n; ++i)
      neighbor[i+1]=nxt(i,P[i]); // proximo estado ativo ao memso tempo que i+1 é o ultimo que avançou com char P[i]
  }
  int nxt(int st, char c) {
    while(st=neighbor[st]) { // avança nos estados até que chegue no estado inicial
      if(P[st]==c) return st+1; // se achou um estado que avança com c, é ele
    }
    return P[0]==c; // vai ficar no estado 0 ou então consegue avançar pro 1
  }
  int match(string &T) {
    size_t count=0,st=0;
    auto f = [&count](int ind) { ++count; }; // Se precisar processar um match muda aqui
    for(size_t i = 0; i < T.size(); ++i) {
      if(T[i]==P[st])st++;  // Lider avança
      else st=nxt(st,T[i]); // Busca proximo estado
      if(st==n){
        f(i);st=neighbor[st]; // processa o match e passa a ohlar pro proximo estado ativo
      }
    }
    return count;
  }
};