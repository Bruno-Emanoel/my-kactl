/**
 * Author: Bruno Emanoel
 * Date: 2026-08-13
 * License: Nao
 * Source: eu
 * Description: algoritmo de euclides extendido
 * Time: O(1),
 * Status: na fe
 */
ll itgcd(ll a, ll b, ll &x, ll &y) {
	ll px = 0, py = 1, p = b, g = a;
	x = 1, y = 0;
	while(p) {
		x-=px*(g/p), y-=py*(g/p);
		swap(x,px); swap(y,py);
		g = p, p = a*px + b*py;
	}
	return g;
}