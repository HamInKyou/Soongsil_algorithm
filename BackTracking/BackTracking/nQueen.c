#include<stdio.h>
#include<malloc.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

#define TRUE 1;
#define FALSE 0;

int promising(int i, int col[]);

int estimate_n_queens(int n, int col[]);

int main(void) {
	srand((unsigned)time(NULL));

	int i, n;
	int* col;

	int monte[20];
	int sum = 0;

	printf("몇개의 Queen으로 시도하시겠습니까? > ");
	scanf_s("%d", &n);

	col = (int*)calloc(n + 1, sizeof(int));
	for (i = 0; i < 20; i++) {
		monte[i] = estimate_n_queens(n, col);
		printf("%2d번째 시도 : %d\n", i + 1, monte[i]);
		sum += monte[i];
	}

	printf("\n평균값 : %2d\n", sum / 20);

	free(col);
	return 0;
}

int promising(int i, int col[]) {
	int k;
	int promisingSwitch;

	k = 1;
	promisingSwitch = TRUE;
	while (k < i && promisingSwitch) {
		if (col[i] == col[k] || abs(col[i] - col[k]) == abs(i - k))
			promisingSwitch = FALSE;
		k++;
	}
	return promisingSwitch;
}

int estimate_n_queens(int n, int col[]) {
	int i, j, z;
	int m, mprod, numnodes;

	int* prom_children = (int*)calloc(n + 1, sizeof(int));

	int index = 0;
	int flag = 0;

	i = 0;
	numnodes = 1;
	m = 1;
	mprod = 1;

	while (m != 0 && i != n) {
		mprod = mprod * m;
		numnodes = numnodes + mprod * n;
		i++;
		m = 0;

		for (z = 1; z <= n; z++)
			prom_children[z] = 0;

		for (j = 1; j <= n; j++) {
			col[i] = j;
			if (promising(i, col)) {
				m++;
				for (z = 1; z <= n; z++) {
					if (prom_children[z] == 0) {
						prom_children[z] = j;
						break;
					}
				}
			}
		}
		if (m != 0) {
			for (z = 1; z <= n; z++) {
				if (prom_children[z] != 0)
					index++;
			}

			flag = (rand() % index) + 1;
		
			j = prom_children[flag];

			col[i] = j;
			index = 0;
		}
	}

	return numnodes;
}
