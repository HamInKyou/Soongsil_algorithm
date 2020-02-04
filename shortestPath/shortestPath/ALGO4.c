#include<stdio.h>
#include<stdlib.h>
#define INF 999

void floyd(const int W[6][6], int D[6][6], int P[6][6]);
void path(const int P[6][6], int q, int r);

//행렬 출력시켜주는 함수
void printArr(const int arr[6][6]) { 
	for (int l = 1; l <= 5; l++) {
		for (int m = 1; m <= 5; m++) {
			if (arr[l][m] == 999)
				printf("INF ");
			else
				printf("%3d ", arr[l][m]);
		}
		printf("\n");
	}
}

int main(void) {
	
	//입력배열 - 1~5 인덱스를 사용할 것이기 때문에 6x6배열을 만들었다.
	int W[6][6] = { { 0,  0,  0,  0,  0,  0},
					{ 0,  0,  4,INF,INF,INF},
					{ 0,  5,  0,  7,INF,INF},
					{ 0,INF,INF,  0, 10,  5},
					{ 0,  1,INF,INF,  0,  2},
					{ 0,  9,  2,INF,  3,  0} };

	int D[6][6] = {0};
	int P[6][6] = {0};

	floyd(W, D, P);
	
	printf("P\n");
	for (int l = 1; l <= 5; l++) {
		for (int m = 1; m <= 5; m++) {
			if (P[l][m] == 999)
				printf("INF ");
			else
				printf("%3d ", P[l][m]);
		}
		printf("\n");
	}
	printf("\n");

	printf("Shortest Path\n");
	printf("a3 -> ");
	path(P, 3, 1);
	printf("a1\n");

}

void floyd(const int W[6][6], int D[6][6], int P[6][6]) {
	int i, j, k = 0;
	for (i = 1; i <= 5; i++) {
		for (j = 1; j <= 5; j++) {
			P[i][j] = 0;
		}
	}
	D = W;
	printf("d_%d\n", k);
	printArr(D);
	printf("\n");

	for (k = 1; k <= 5; k++) {
		for (i = 1; i <= 5; i++) {
			for (j = 1; j <= 5; j++) {
				if (D[i][k] + D[k][j] < D[i][j]) {
					P[i][j] = k;
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
		//d_k 행렬 print
		printf("d_%d\n", k);
		printArr(D);
		printf("\n");
	}
}

void path(const int P[6][6], int q, int r) {
	if (P[q][r] != 0) {
		path(P, q, P[q][r]);
		printf("a%d -> ", P[q][r]);
		path(P, P[q][r], r);
	}
}