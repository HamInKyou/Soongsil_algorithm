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

	for (int i = 0; i < n; i++) {
		total += w[i];
	}

	sum_of_subset(-1, 0, total);
	printf("\n%d번의 노드 체크", checknodeNum);
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
