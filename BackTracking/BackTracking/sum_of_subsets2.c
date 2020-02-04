#include<stdio.h>
#include<malloc.h>

int* w;
int* x;
int W;
int n;
int checknodeNum = 0;
int finish = 0;

void sum_of_subset(int i, int weight, int total);
int promising(int i, int weight, int total);
void print();

int main(void) {
	int total = 0;

	printf("���ڴ� �� � �ֳ���? : ");
	scanf_s("%d", &n);

	w = (int*)calloc(n, sizeof(int));
	x = (int*)calloc(n, sizeof(int));

	printf("%d���� ���ڸ� �Է����ּ��� : ", n);
	for (int i = 0; i < n; i++) {
		scanf_s("%d", &w[i]);
	}
	printf("���� ���� �Ǵ� ������ ã�� ��������? : ");
	scanf_s("%d", &W);

	for (int i = 0; i < n; i++) {
		total += w[i];
	}

	sum_of_subset(-1, 0, total);
	printf("\n%d���� ��� üũ", checknodeNum);
}

void sum_of_subset(int i, int weight, int total) {
	checknodeNum++;
	if (!finish) {
		if (promising(i, weight, total)) {
			if (W == weight){
				print();
				finish = 1;
			}
			else {
				x[i + 1] = w[i + 1];
				sum_of_subset(i + 1, weight + w[i + 1], total - w[i + 1]);
				x[i + 1] = 0;
				sum_of_subset(i + 1, weight, total - w[i + 1]);
			}
		}
	}
}

int promising(int i, int weight, int total) {
	return (weight + total >= W) && (weight == W || weight + w[i + 1] <= W);
}

void print() {
	for (int i = 0; i < n; i++) {
		if (x[i] != 0)
			printf("w%d = %d, ", i + 1, x[i]);
	}
	printf("\n");
}
