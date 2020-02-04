#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<time.h>

int* w;
int* x;
int W;

int estimate_sum_of_subset(int n);
int promising(int i, int weight, int total);
void print(int n);

int main(void) {
	srand((unsigned)time(NULL));
	int n;
	int sum = 0;
	int result = 0;

	printf("숫자는 총 몇개 있나요? : ");
	scanf_s("%d", &n);

	w = (int*)calloc(n, sizeof(int));
	x = (int*)calloc(n, sizeof(int));

	printf("%d개의 숫자를 입력해주세요 : ", n);
	for (int i = 0; i < n; i++) {
		scanf_s("%d", &w[i]);
	}
	printf("합이 몇이 되는 조합을 찾고 싶으세요? : ");
	scanf_s("%d", &W);

	for (int i = 0; i < 20; i++) {
		result = estimate_sum_of_subset(n);
		printf("%d번째 시도 : %d\n", i+1, result);
		sum += result;
	}
	printf("\n평균치 : %d", sum / 20);
	
}

int estimate_sum_of_subset(int n) {
	int total = 0;
	int i, weight=0;
	int flag;
	int m, mprod, numnodes;
	int leftNodeProm; int rightNodeProm;
	
	for (int i = 0; i < n; i++) {
		total += w[i];
	}
	i = -1; 
	numnodes = 1; 
	m = 1; 
	mprod = 1;

	while (m != 0 && i != n && W!=weight) {
		mprod = mprod * m;
		numnodes = numnodes + mprod * 2;
		m = 0;
		leftNodeProm = promising(i + 1, weight + w[i + 1], total - w[i + 1]);
		rightNodeProm = promising(i + 1, weight, total - w[i + 1]);
		if (leftNodeProm && rightNodeProm) //둘다 유망
			m += 2;
		else if (leftNodeProm) //넣은게 유망
			m++;
		else if (rightNodeProm) //안넣은게 유망
			m++;
		
		if (m != 0) {
			if (m == 2) {
				flag = rand() % 2;
				if (flag) {
					x[i + 1] = w[i + 1];
					weight = weight + w[i + 1];
				}
				else {
					x[i + 1] = 0;
				}
			}
			else if (m == 1) {
				if (leftNodeProm) {
					x[i + 1] = w[i + 1];
					weight = weight + w[i + 1];
				}
				else if (rightNodeProm) {
					x[i + 1] = 0;
				}
			}
			total -= w[i + 1];
		}
		i++;
	}
	return numnodes;
}

int promising(int i, int weight, int total) {
	return (weight + total >= W) && (weight == W || weight + w[i + 1] <= W);
}

void print(int n) {
	for (int i = 0; i < n; i++) {
		if (x[i] != 0)
			printf("w%d = %d, ", i + 1, x[i]);
	}
}
