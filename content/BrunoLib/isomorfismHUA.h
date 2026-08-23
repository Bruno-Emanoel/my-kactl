/**
 * Author: Bruno Emanoel
 * Date: 2026-08-23
 * License: CC0
 * Description: Checa se duas árvores são iguais utilizando 
 * o algoritmo de HUA. O algoritmo funciona mantendo para cada configuração 
 * de subárvore um número associado a sequência de parentêses que a 
 * representa. O algoritmo associa valores aleatorios a cada sequência,
 * podendo haver colisão. A concatenação de asssinaturas é simulada através da
 * soma módulo 2^{64} - 1. Para um algoritmo determinístico, as sequências
 * são armazenadas mais explicitamente, com um valor distinto para cada sequência.
 * Time: O(n) não determinístico, O(nlogn) determinístico
 */

constexpr ll MAXN = 1;
unordered_map<ull,ull> hsh; 
// map<vll, ll> vecs; para versão determinística em O(nlogn)
struct HUATree {
    vll *t;
    v<ull> sig;
    HUATree(vll *t, ll sz): t(t), sig(sz) {}
    ull getsign(ll u, ll p = -1) {
        sig[u] = 0;
        // vll vec;
        for(auto w:t[u]) if(w!=p) {
            sig[u] += getsign(w,u);
            // vec.emplace_back(getsign(w,u));
        }
        auto it = hsh.find(sig[u]);
        // sort(full(vec)); // garante que isomorfismo seja identificado independente da ordem
        // auto it = vecs.find(vec);
        if(it!=hsh.end()) sig[u] = it->second;
        else {
            ull nsig = uniform(0, ULLONG_MAX); // [0,2^64 - 1]
            hsh[sig[u]] = nsig;
            sig[u] = nsig;
            // vecs[vec] = sig[u] = vecs.size();
        }
        return sig[u];
    }
};

bool check_rooted_isomorfism(vll *t1, ll sz1, ll r1, vll *t2, ll sz2, ll r2) {
    return HUATree(t1,sz1).getsign(r1) == HUATree(t2,sz2).getsign(r2);
}

pll getcentroids(vll *t, ll n); // Retorna {c1,c2} se c1 e c2 são centroids distintos de t ou {c,c} caso exista apenas um

bool check_isomorfism(vll *t1, ll sz1, vll *t2, ll sz2) {
    pll c1 = getcentroids(t1,sz1);
    pll c2 = getcentroids(t2,sz2);
    return  check_rooted_isomorfism(t1,sz1,c1.first,t2,sz2,c2.first) || check_rooted_isomorfism(t1,sz1,c1.second,t2,sz2,c2.first);
}