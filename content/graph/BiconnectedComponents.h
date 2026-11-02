/**
 * Author: Simon Lindholm
 * Date: 2017-04-17
 * License: CC0
 * Source: folklore
 * Description: Finds all biconnected components in an undirected graph, and
 *  runs a callback for the edges in each. In a biconnected component there
 *  are at least two internally disjoint paths between any two nodes (a cycle
 *  exists through them). Note that a node can be in several components. An
 *  edge which is not in a component is a bridge, i.e., not part of any cycle.
 * Usage:
 *  int eid = 0; ed.resize(N);
 *  for each edge (a,b) { // We keep the vector of all edges
 *    ed[a].emplace_back(b, eid); // index of the edge
 *    ed[b].emplace_back(a, eid++); }
 *  bicomps([\&](vi::iterator st, vi::iterator en) {...});
 * Time: O(E + V)
 * Status: tested during MIPT ICPC Workshop 2017
 */
#pragma once

vi num, st;
vector<vector<pii>> ed;
int Time;
template<class F>
int dfs(int at, int par, F& f) {
	int me = num[at] = ++Time, top = me;
	for (auto [y, e] : ed[at]) if (e != par) {
		if (num[y]) {
			top = min(top, num[y]);
			if (num[y] < me)
				st.push_back(e);
		} else {
			int si = sz(st);
			int up = dfs(y, e, f);
			top = min(top, up);
			if (up == me) {
				st.push_back(e);
				f(st.begin() + si, st.end());
				st.resize(si);
			}
			else if (up < me) st.push_back(e);
			else { /* e is a bridge */ } // call f({e}) (with iterators) if you want to build the BCT
		}
	}
	return top;
}

template<class F>
void bicomps(F f) {
	num.assign(sz(ed), 0);
	rep(i,0,sz(ed)) if (!num[i]) dfs(i, -1, f);
}

vector<vll> bct; // the block cut tree
// example: building the block cut tree, which condenses vertex in blocks of
// each maximal biconnected componnent
void buildBCT(int n, vpll &edges) {
	bct.assign(n, {});
	vll mark(n,-1);
	auto addBlock = [&](auto st, auto en) {
		ll now = bct.size(); bct.emplace_back();
		for(; st != en; ++st) for(auto u:{edges[*st].first, edges[*st].second}) {
			if(mark[u]!=now) {
				mark[u] = now;
				bct[now].emplace_back(u);
				bct[u].emplace_back(now);
			}
		}
	};
	bicomps(addBlock);
}

vector<vll> bt; vll comp; // bridge tree; comp[v] = nó de v em bt
void buildBT(int n, vpll &edges) {
	vector<bool> br(sz(edges), 1);
	bicomps([&](auto b, auto e) {
		if (e - b > 1) for (; b != e; ++b) br[*b] = 0;
	});
	comp.assign(n, -1); ll c = 0;
	rep(s,0,n) if (comp[s] < 0) {
		vll q{s}; comp[s] = c;
		rep(i,0,sz(q)) for (auto [y, e] : ed[q[i]])
			if (!br[e] && comp[y] < 0) comp[y] = c, q.push_back(y);
		c++;
	}
	bt.assign(c, {});
	rep(e,0,sz(edges)) if (br[e]) {
		ll a = comp[edges[e].first], b = comp[edges[e].second];
		if (a != b) bt[a].push_back(b), bt[b].push_back(a);
	}
}