#include <stdio.h>
#include <math.h>
#define N 30

typedef struct {
	int x;
	int y;
	int raza;
} cerc;

int distance(cerc a, cerc b) {
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

int main() {
	cerc c[30];
	int n, inter = 0;

	scanf("%d", &n);

	for (int i = 0; i < n; ++i) {
		scanf("%d%d%d", &c[i].x, &c[i].y, &c[i].raza);
	}

	for (int i = 0; i < n - 1; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (c[i].raza + c[j].raza >= distance(c[i], c[j])) {
				inter ++;
				printf("(%d, %d) ", i, j);
			}
		}
	}

	printf("\n%d\n", inter);

	return 0;
}