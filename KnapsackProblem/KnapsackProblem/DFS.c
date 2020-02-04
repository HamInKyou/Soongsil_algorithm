#include<stdio.h>
#include<stdlib.h>

int* p;
int* w;
int* include;
int* bestset;

int W;
int n;
int maxprofit = 0;

void knapsack(int i, int profit, int weight);
int promising(int i, int profit, int weight);
void print();

int main(void) {

	printf("몇개의 item이 있나요? : ");
	scanf_s("%d", &n);
	
	p = (int*)calloc(n+1, sizeof(int));
	w = (int*)calloc(n+1, sizeof(int));
	include = (int*)calloc(n + 1, sizeof(int));
	bestset = (int*)calloc(n + 1, sizeof(int));

	printf("<<item의 price와 무게를 차례대로 설정해주세요>>\n");
	for (int i = 1; i <= n; i++) {
		printf("[item%d] ", i);
		scanf_s("%d", &p[i]);
		scanf_s("%d", &w[i]);
	}

	printf("\n가방에 얼만큼의 무게만큼 들어갈 수 있나요? : ");
	scanf_s("%d", &W);

	knapsack(0, p[0], w[0]);
	printf("<<가방안의 item 목록>>\n");
	print();
	printf("총 profit : %d", maxprofit);

	free(p);
	free(w);
	free(include);
	free(bestset);
}

void knapsack(int index, int profit, int weight) {
	if (weight <= W && profit > maxprofit) {
		maxprofit = profit;
		for (int i = 0; i <= n; i++) {
			bestset[i] = include[i];
		}
	}

	if (promising(index,profit,weight)) {
		include[index + 1] = 1;
		knapsack(index + 1, profit + p[index + 1], weight + w[index + 1]);
		include[index + 1] = 0;
		knapsack(index + 1, profit, weight);
	}
}

int promising(int index, int profit, int weight) {
	int j, k;
	int totweight;
	float bound;

	if (weight >= W) {
		return 0;
	}
	else {
		j = index + 1;
		bound = profit;
		totweight = weight;
		while ((j <= n) && (totweight + w[j] <= W)) {
			totweight = totweight + w[j];
			bound = bound + p[j];
			j++;
		}

		k = j;
		
		if (k <= n) {
			bound = bound + (W - totweight) * (p[k] / w[k]);
		}
		if (bound > maxprofit)
			return 1;
		else
			return 0;
	}
}

void print() {
	for (int i = 1; i <= n; i++) {
		if (bestset[i] == 1) {
			printf("[item%d], p = $%d, w = %d\n", i, p[i], w[i]);
		}
	}
}