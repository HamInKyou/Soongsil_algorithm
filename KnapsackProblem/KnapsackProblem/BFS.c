#include<stdio.h>
#include<stdlib.h>
#define MAX 100

typedef struct node {
	int level;
	int profit;
	int weight;
}node;

int* p;
int* w;
int W;
int n;
int maxprofit = 0;

node queue[MAX];
int front;
int rear;

void init_queue(void) {
	front = rear = 0;
}
int isEmpty() {
	return front == rear;
}
void enqueue(node v) {
	queue[rear++] = v;
}
node dequeue() {
	return queue[front++];
}

void knapsack();
int bound(node u);

int main(void) {

	printf("몇개의 item이 있나요? : ");
	scanf_s("%d", &n);

	p = (int*)calloc(n + 1, sizeof(int));
	w = (int*)calloc(n + 1, sizeof(int));

	printf("<<item의 price와 무게를 차례대로 설정해주세요>>\n");
	for (int i = 1; i <= n; i++) {
		printf("[item%d] ", i);
		scanf_s("%d", &p[i]);
		scanf_s("%d", &w[i]);
	}

	printf("\n가방에 얼만큼의 무게만큼 들어갈 수 있나요? : ");
	scanf_s("%d", &W);

	knapsack();
	printf("\n총 profit = %d\n", maxprofit);

}

void knapsack() {
	init_queue();
	node u, v;

	//루트 노드 정보
	v.level = 0;
	v.profit = 0;
	v.weight = 0;
	enqueue(v);


	while (!isEmpty()) {
		v = dequeue();
		printf("level%d의 유망한 노드 정보 : ", v.level);
		printf("protfit = %2d, weight = %2d, bound = %2d\n", v.profit, v.weight, bound(v));

		u.level = v.level + 1;

		//넣은 경우
		u.profit = v.profit + p[u.level];
		u.weight = v.weight + w[u.level];
		if ((u.weight <= W) && (u.profit > maxprofit))
			maxprofit = u.profit;
		if (bound(u) > maxprofit)
			enqueue(u);

		//넣지 않은 경우
		u.weight = v.weight;
		u.profit = v.profit;

		if (bound(u) > maxprofit)
			enqueue(u);
	}
}

int bound(node m) {
	int j, k;
	int totweight;
	int result;
	if (m.weight >= W)
		return 0;
	else {
		result = m.profit;
		j = m.level + 1;
		totweight = m.weight;
		while ((j <= n) && (totweight + w[j] <= W)) {
			totweight = totweight + w[j];
			result = result + p[j];
			j++;
		}
		k = j;
		if (k <= n)
			result = result + (W - totweight) * (p[k] / w[k]);
		return result;
	}
}