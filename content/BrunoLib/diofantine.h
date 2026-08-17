/**
 * Author: Bruno Emanoel
 * Date: 2026-08-13
 * License: Nao
 * Source: eu
 * Description: encontra solucao para diofantina
 * Time: O(logn),
 * Status: na fe
 */
bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {
    g = itgcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}