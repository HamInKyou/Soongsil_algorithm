#include<stdio.h>

int minMult(int n, const int* d, int* P);
void order(int* P, int n, int i, int j);

int main(void) {
	int n = 5;
	int* d = (int*)calloc(n + 1, sizeof(int)); //동적할당 n+1크기 (1~n)쓰기 위해
	int* P = (int*)calloc((n + 1) * (n + 1), sizeof(int)); //동적할당 (n+1)x(n+1)크기 - (1~n)x(1~n)쓰기 위해 

	d[0] = 10;
	d[1] = 4;
	d[2] = 5;
	d[3] = 20;
	d[4] = 2;
	d[5] = 50;

	//최적값 찾는 과정
	printf("\n   최적의 곱 횟수는 : %d 번\n\n", minMult(n, d, P));
	
	printf("   행렬들의 곱셈 순서는 다음과 같습니다.\n  ");
	order(P, n, 1, n);
	
}

//chained Matrix 최적값 찾기위한 Matrix M 과 P 출력해주고, 최적값 리턴해주는 함수
int minMult(int n, const int* d, int* P) {
	int i, j, k, diagonal, min, minK;
	int* M = (int*)calloc((n+1) * (n+1), sizeof(int)); //0행, 0열 제외
	for (i = 1; i <= n; i++)
		M[(i * (n+1)) + (i+1)] = 0; //M[i][i] = 0;
	for (diagonal = 1; diagonal <= n - 1; diagonal++) {
		for (i = 1; i <= n - diagonal; i++) {
			j = i + diagonal;
			min = M[(i * (n + 1)) + i] + M[((i + 1) * (n + 1)) + j] + d[i - 1] * d[i] * d[j];
			minK = i;

			//min 찾아내는 루프
			for (k = i + 1; k <= j - 1; k++) {
				if (min > M[(i * (n + 1)) + k] + M[((k + 1) * (n + 1)) + j] + d[i - 1] * d[k] * d[j]){
					min = M[(i * (n + 1)) + k] + M[((k + 1) * (n + 1)) + j] + d[i - 1] * d[k] * d[j];
					minK = k;
				}
			}
			M[(i * (n + 1)) + j] = min;
			P[(i * (n + 1)) + j] = minK;
		}
	}

	printf("\n   Matrix M 출력\n");
	for (int l = 1; l < n + 1; l++) {
		for (int m = 1; m < n + 1; m++) {
			printf("%4d ", M[(l * (n + 1)) + m]);
		}
		printf("\n");
	}
	printf("\n   Matrix P 출력\n");
	for (int l = 1; l < n + 1; l++) {
		for (int m = 1; m < n + 1; m++) {
			printf("%4d ", P[(l * (n + 1)) + m]);
		}
		printf("\n");
	}

	return M[1*(n+1) + n];
}

//행렬의 곱셈 순서 표현해주는 함수
void order(int* P, int n, int i, int j) {
	if (i == j)
		printf("A%d", i);
	else {
		int k = P[(i * (n + 1)) + j];
		printf("(");
		order(P, n, i, k);
		order(P, n, k + 1, j);
		printf(")");
	}
}

