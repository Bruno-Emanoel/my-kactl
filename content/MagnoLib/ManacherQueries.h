/**
 * Author: Magno
 * Date: 2026-08-21
 * License: CC0
 * Description: Consultas de palindromos utilizando a estrutura p gerada pelo algoritmo de Manacher.
 *  is-palindrome: verifica se a substring s[l...r] (0-indexada) e palindromo em O(1).
 *  get-max-len: retorna o tamanho do maior palindromo centrado em (l, r) em O(1).
 * Time: O(1) por consulta
 * Status: Tested
 */
#pragma once

bool is_palindrome(const array<vi, 2>& p, int l, int r) {
	if (l > r) return true;
	int len = r - l + 1;
	if (len % 2 != 0) {
		int mid = (l + r) / 2;
		return p[1][mid] >= len / 2;
	} else {
		int mid = (l + r + 1) / 2;
		return p[0][mid] >= len / 2;
	}
}

int get_max_len(const array<vi, 2>& p, int l, int r) {
	if (l == r) {
		return 2 * p[1][l] + 1;
	} else {
		return 2 * p[0][r];
	}
}
