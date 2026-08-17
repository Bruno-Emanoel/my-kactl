/**
 * Author: Bruno Emanoel
 * Date: 2026-08-13
 * License: Nao
 * Source: eu
 * Description: diz se existe subset cujo xor = cara
 * Time: O(1),
 * Status: na fe
 */
namespace XorBasis {
  constexpr ll LOGN = 20;
  using Vec = unsigned;
  using Basis = array<Vec,LOGN>;
  
  inline void insert(Basis &a, Vec vec) { // O(logn)
    if(!vec)
      return;
    loop(i,0,LOGN) {
      if(!getBit(vec,i)) continue;
      if(!getBit(a[i],i)) {
        a[i] = vec;
        return;
      }
      vec^=a[i];
    }
  }
  inline bool contains(const Basis&a,Vec vec) { // O(logn)
    loop(i,0,LOGN) {
      if(!getBit(vec,i)) continue;
      if(!getBit(a[i],i))
        return false;
      vec^=a[i];
    }
    return vec==0;
  }
  inline void operator+=(Basis&a, const Basis&b) { // O(log^2(n))
    loop(i,0,LOGN)
      insert(a,b[i]);
  } 
};