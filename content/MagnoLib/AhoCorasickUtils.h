/**
 * Author: Magno
 * Date: 2026-08-21
 * License: CC0
 * Description: Automato Aho-Corasick com utilitarios:
 *  findFirstLast: calcula os indices de inicio [L, R] da primeira e ultima aparicao de cada padrao no texto.
 *  countEachPattern: conta exatamente quantas vezes cada padrao ocorre no texto sem degradar em textos repetitivos via ordenacao topologica na Fail Tree (Anti-TLE).
 *  countTotalMatches: calcula a soma total de todas as ocorrencias de todos os padroes no texto em tempo linear.
 *  containsAny: verifica se o texto contem pelo menos um dos padroes, parando no primeiro casamento (early exit).
 *  maxNonOverlappingMatches: encontra a quantidade maxima de ocorrencias dos padroes que podem ser selecionadas sem sobreposicao de caracteres (interval scheduling / guloso).
 * Time: O(N + M) para countEachPattern (Fail Tree), O(N) para countTotalMatches e containsAny.
 * Status: Tested
 */
#pragma once

struct AhoCorasick {
	enum {alpha = 26, first = 'a'};
	struct Node {
		int back, next[alpha], start = -1, end = -1, nmatches = 0;
		Node(int v) { memset(next, v, sizeof(next)); }
	};
	vector<Node> N;
	vi backp, pat_node;

	void insert(string& s, int j) {
		assert(!s.empty());
		int n = 0;
		for (char c : s) {
			int& m = N[n].next[c - first];
			if (m == -1) { n = m = sz(N); N.emplace_back(-1); }
			else n = m;
		}
		if (N[n].end == -1) N[n].start = j;
		backp.push_back(N[n].end);
		N[n].end = j;
		N[n].nmatches++;
		pat_node.push_back(n);
	}

	AhoCorasick(vector<string>& pat) : N(1, -1) {
		rep(i,0,sz(pat)) insert(pat[i], i);
		N[0].back = sz(N);
		N.emplace_back(0);

		queue<int> q;
		for (q.push(0); !q.empty(); q.pop()) {
			int n = q.front(), prev = N[n].back;
			rep(i,0,alpha) {
				int &ed = N[n].next[i], y = N[prev].next[i];
				if (ed == -1) ed = y;
				else {
					N[ed].back = y;
					(N[ed].end == -1 ? N[ed].end : backp[N[ed].start])
						= N[y].end;
					N[ed].nmatches += N[y].nmatches;
					q.push(ed);
				}
			}
		}
	}

	vector<pii> findFirstLast(const vector<string>& pat, const string& word) {
		int m = sz(pat);
		vector<pii> pos(m, {-1, -1});
		int n = 0;
		rep(i, 0, sz(word)) {
			n = N[n].next[word[i] - first];
			int ind = N[n].end;
			while (ind != -1) {
				int start_idx = i - sz(pat[ind]) + 1;
				if (pos[ind].first == -1) pos[ind].first = start_idx;
				pos[ind].second = start_idx;
				ind = backp[ind];
			}
		}
		return pos;
	}

	vi countEachPattern(const vector<string>& pat, const string& word, const vi& p_node = {}) {
		const vi& pnode = p_node.empty() ? pat_node : p_node;
		int num_nodes = sz(N);
		vi visits(num_nodes, 0), in_deg(num_nodes, 0);
		int curr = 0;
		for (char c : word) {
			curr = N[curr].next[c - first];
			visits[curr]++;
		}
		rep(i, 1, num_nodes - 1) in_deg[N[i].back]++;
		queue<int> q;
		rep(i, 0, num_nodes - 1) if (in_deg[i] == 0) q.push(i);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			int p = N[u].back;
			if (p >= 0 && p < num_nodes - 1) {
				visits[p] += visits[u];
				if (--in_deg[p] == 0) q.push(p);
			}
		}
		vi ans(sz(pat));
		rep(i, 0, sz(pat)) ans[i] = visits[pnode[i]];
		return ans;
	}

	long long countTotalMatches(const string& word) {
		int n = 0;
		long long total = 0;
		for (char c : word) {
			n = N[n].next[c - first];
			total += N[n].nmatches;
		}
		return total;
	}

	bool containsAny(const string& word) {
		int n = 0;
		for (char c : word) {
			n = N[n].next[c - first];
			if (N[n].nmatches > 0) return true;
		}
		return false;
	}

	int maxNonOverlappingMatches(const vector<string>& pat, const string& word) {
		int n = 0, count = 0, last_end = -1;
		rep(i, 0, sz(word)) {
			n = N[n].next[word[i] - first];
			int ind = N[n].end;
			while (ind != -1) {
				int start_idx = i - sz(pat[ind]) + 1;
				if (start_idx > last_end) {
					count++;
					last_end = i;
					break;
				}
				ind = backp[ind];
			}
		}
		return count;
	}
};
