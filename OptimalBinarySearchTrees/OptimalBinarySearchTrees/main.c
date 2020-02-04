#include<stdio.h>
#include<stdlib.h>

void optsearchtree(int n, const float* p, float* minavg, int* R);
float sumP(float* p, int i, int j) {
	float sum = 0;
	for (int k = i; k <= j; k++) {
		sum += p[k];
	}
	return sum;
}

int main(void)
{
	int n = 6;
	int* R = (int*)calloc((n + 2) * (n + 1), sizeof(int));//(0~n+1)x(0~n)크기 배열 동적할당
	float* p = (float*)calloc(n + 1, sizeof(float)); //0~n크기 배열 동적할당
	float minavg;
	
	//배열에 확률값 넣어주기
	p[1] = 0.05;
	p[2] = 0.15;
	p[3] = 0.05;
	p[4] = 0.35;
	p[5] = 0.05;
	p[6] = 0.35;

	optsearchtree(n, p, &minavg, R);
}

void optsearchtree(int n, const float* p, float* minavg, int* R)
{
	int i, j, k, mink, diagonal;
	float min;
	float* A = (float*)calloc((n + 2) * (n + 1), sizeof(float));

	for (i = 1; i <= n; i++)
	{
		A[i * (n + 1) + (i - 1)] = 0;
		A[i * (n + 1) + i] = p[i];
		R[i * (n + 1) + i] = i;
		R[i * (n + 1) + (i - 1)] = 0;
	}
	A[(n + 1) * (n + 1) + n] = 0;
	R[(n + 1) * (n + 1) + n] = 0;
	for (diagonal = 1; diagonal <= n - 1; diagonal++)
	{
		for (i = 1; i <= n - diagonal; i++)
		{
			j = i + diagonal;

			//min 초기값
			min = A[i * (n + 1) + (i - 1)] + A[(i + 1) * (n + 1) + j] + sumP(p,i,j);
			mink = i;

			//min 찾는 루프
			for (k = i+1; k <= j; k++)
			{
				if (min > A[i * (n + 1) + (k - 1)] + A[(k + 1) * (n + 1) + j] + sumP(p, i, j))
				{
					min = A[i * (n + 1) + (k - 1)] + A[(k + 1) * (n + 1) + j] + sumP(p, i, j);
					mink = k;
				}
			}
			A[i * (n + 1) + j] = min;
			R[i * (n + 1) + j] = mink;
		}
	}


	printf("print Matrix A\n");
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%.2f  ", A[i * (n + 1) + j]);
		}
		printf("\n");
	}
	
	printf("\nprint Matrix R\n");
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%4d  ", R[i * (n + 1) + j]);
		}
		printf("\n");
	}
	
	*minavg = A[1 * (n + 1) + n];
}