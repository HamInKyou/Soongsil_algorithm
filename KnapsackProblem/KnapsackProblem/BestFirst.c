#include<stdio.h>
#include<stdlib.h>
#define MAX 100

typedef struct node {
	int level;
	int profit;
	int weight;
	int bound;
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
	int i = 0, j = 0;
	for (i = front; i <= rear - 1; i++) {
		for (j = i + 1; j <= rear; j++) {
			if (queue[j].bound > queue[i].bound) {
				node tmp;
				tmp = queue[j];
				queue[j] = queue[i];
				queue[i] = tmp;
			}
		}
	}
}
node dequeue() {
	return queue[front++];
}

void knapsack();
int bound(node m);

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
	int dequeueCnt;

	//루트 노드 정보
	v.level = 0;
	v.profit = 0;
	v.weight = 0;
	v.bound = bound(v);
	enqueue(v);

	while (!isEmpty()) {
		v = dequeue();
		if (v.bound > maxprofit) {
			printf("DEQUEUE한 노드 정보 : ", v.level);
			printf("protfit = %2d, weight = %2d, bound = %2d\n", v.profit, v.weight, bound(v));
			u.level = v.level + 1;
			u.profit = v.profit + p[u.level];
			u.weight = v.weight + w[u.level];
			if ((u.weight <= W) && (u.profit > maxprofit))
				maxprofit = u.profit;

			u.bound = bound(u);
			if (u.bound > maxprofit)
				enqueue(u);

			u.weight = v.weight;
			u.profit = v.profit;
			u.bound = bound(u);
			if (u.bound > maxprofit)
				enqueue(u);
		}
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