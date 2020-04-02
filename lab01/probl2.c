#include <stdio.h>
#include <stdlib.h>

int main() {
	int n, m;
	int **mat;
	int max = 0, xor_c;

	scanf("%d%d", &n, &m);

	mat = (int**) malloc(n * sizeof(int*));
	for (int i = 0; i < n; ++i) {
		mat[i] = (int*) malloc(m * sizeof(int));
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			scanf("%d", &mat[i][j]);
		}
	}

	for (int i = 0; i < n; ++i) {

		xor_c = mat[i][0];

		for (int j = 0; j < m - 1; ++j) {
			xor_c = xor_c ^ mat[i][j + 1];
		}
		if (xor_c > max) {
			max = xor_c;
		}
	}

	printf("%d\n", max);

	for (int i = 0; i < n; ++i) {
		free (mat[i]);
	}

	free(mat);
 
	return 0;
}