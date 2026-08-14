/**
 * Author: Bruno Emanoel
 * Date: 2026-08-13
 * License: Nao
 * Source: eu
 * Description: wrapper para operações módulo
 * Time: O(1),
 * Status: na fé
 */
struct Mint {
  ll x=0;
  Mint() = default;
  Mint(ll a): x{((a%mod)+mod)%mod} {}
  Mint(ll p, ll q): Mint((((p%mod)+mod)%mod)*binexpo(q,mod-2)) {}
  Mint operator+(const Mint &a) const { return (x+a.x); }
  Mint operator-() const { return (mod-x); }
  Mint operator-(const Mint &a) const { return operator+(-a); }
  Mint operator*(const Mint &a) const { return (x*a.x); }
  Mint operator/(const Mint &a) const { return operator*(binexpo(a.x,mod-2)); }
  Mint operator^(const Mint &a) const { return (binexpo(x,a.x)); }
  Mint &operator+=(const Mint &a) { return *this = operator+(a); }
  Mint &operator-=(const Mint &a) { return *this = operator-(a); }
  Mint &operator*=(const Mint &a) { return *this = operator*(a); }
  Mint &operator/=(const Mint &a) { return *this = operator/(a); }
  Mint &operator^=(const Mint &a) { return *this = operator^(a); }
};