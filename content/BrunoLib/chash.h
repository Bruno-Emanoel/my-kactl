/**
 * Author: Bruno Emanoel
 * Date: 2026-08-13
 * License: Nao
 * Source: eu
 * Description: hash customizado
 * Time: O(1),
 * Status: na fe
 */
struct customHash {
  static unsigned ll splitmix64(unsigned ll x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(unsigned ll x) const {
    static const unsigned ll FIXED_RANDOM =
      chrono::steady_clock::now().time_since_epoch().count()
      ^ (ull)(std::make_unique<char>().get());
    return splitmix64(x ^ FIXED_RANDOM);
  }
};

namespace std {
  template<>
  struct hash<pll> {
    size_t operator()(const pll &a) const {
      return customHash()(a.first+ (((ll)a.second)<<31));
    }
  };
};
