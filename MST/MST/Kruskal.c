#include <stdio.h>
#include <stdlib.h> // 정렬하기 위한 qsrot 함수가 선언된 헤더 파일
#define MAX_VERTICES 10 // 정점의 수
#define INF 999 //간선이 없음을 표현

typedef struct { // 간선의 집합을 만들기 위한 구조체
	int key; // 간선의 가중치
	int u; // 정점 1
	int v; // 정점 2
}element;

int parent[MAX_VERTICES]; // 부모 노드
int totalEdge_num = 0; // 간선의 개수

 // 오름차순 비교 함수 구현
int compare(const void* a, const void* b) {
	element* m = (element*)a;
	element* n = (element*)b; 
	if (m->key < n->key) return -1; // a가 b보다 작을 때는 -1 반환
	if (m->key > n->key) return 1; // a가 b보다 클 때는 1 반환
	return 0; // a와 b가 같을 때는 0 반환 
}

int find_set(int v) { // v가 속하는 집합을 반환
	while (parent[v] >= 0) {
		v = parent[v]; // 루트 노드까지 반복
	}
	return v; // 집합의 대표 원소를 반환
}

// 두 개의 원소가 속한 집합을 합친다.
void union_set(int n1, int n2) { 
	int temp; // parent 배열의 원소를 루트 노드로 바꾸게 되면 그 정점의 개수가 사라지기 때문에 정점의 개수를 저장해둘 변수
	int i;

	// 따로 원소의 개수가 있는 배열을 만들지 않고
	// parent 배열에서 양수인 인덱스는 루트노드를 나타내고,
	// 음수는 루트노드로써 인덱스의 절대값은 원소의 개수를 나타내므로 음수와 양수일 때를 구분한다.

	if (parent[n1] < 0 && parent[n2] < 0) { // 두 정점이 전부 루트 노드일 때
		if (parent[n1] <= parent[n2]) { // n1의 원소의 개수가 n2보다 작거나 같다면
			temp = parent[n2]; // n2의 개수를 저장
			parent[n2] = n1; // n2의 루트를 n1으로 저장
			parent[n1] += temp; // n1에 n2의 개수를 더함
		}
		else { // n1의 원소의 개수가 n2보다 크다면
			temp = parent[n1]; // n1의 개수를 저장
			parent[n1] = n2; // n1의 루트를 n2으로 저장
			parent[n2] += temp; // n2에 n1의 개수를 더함
		}
	}
	// 한 정점만 루트 노드일 때(n1이 루트 노드)
	else if (parent[n1] < 0 && parent[n2] >= 0) { 
		temp = parent[n1]; // n1의 개수를 저장
		parent[n1] = parent[n2]; // n1의 루트를 n2의 루트로 설정
		parent[parent[n2]] += temp; // n2의 루트에 n1의 개수를 저장
	}
	// 한 정점만 루트 노드일 때(n2가 루트 노드)
	else if (parent[n1] >= 0 && parent[n2] < 0) {
		temp = parent[n2]; // n2의 개수를 저장
		parent[n2] = parent[n1]; // n2의 루트를 n1의 루트로 설정
		parent[parent[n1]] += temp; // n1의 루트에 n2의 개수를 저장
	}
	// 두 정점 모두 루트 노드가 아닐 때
	else { 
		temp = parent[n1]; // n1의 루트가 어디인지 저장
		parent[n1] = parent[n2]; // n1의 루트를 n2의 루트로 설정
		parent[temp] = parent[n2]; // n1의 루트의 루트를 n2의 루트로 설정
	}

	printf("(%2d - %2d ) union two sets\n", n1 + 1, n2 + 1);
}

// 간선 배열과, 정점의 총개수
void krustkal(element edge_set[], int n) {
	int i, u, v;
	int edge_EA = 0; // 최소 비용을 구하는데 선택된 간선의 수

	// 간선집합을 간선 가중치 낮은 순으로 정렬한다.
	qsort(edge_set, totalEdge_num, sizeof(element), compare); 
	
	// 정점의 개수만큼 parent 배열을 초기화
	for (i = 0; i < n; ++i) 
		parent[i] = -1;
	
	// 간선의 개수가 n-1이 될 때까지 간선 추가
	for (i = 0; edge_EA < n - 1; ++i) { 
		u = edge_set[i].u;
		v = edge_set[i].v;

		// 각 정점 u와 v가 같은 집합에 없다면 사이클이 발생하지 않으므로
		if (find_set(u) != find_set(v)) { 
			edge_EA++; // 선택된 간선의 개수를 증가
			union_set(u, v); // 정점 u와 v를 유니온
		}
		//사이클 발생하는 경우
		else {
			printf("(%2d - %2d ) makes Cycle = pass\n", u+1, v+1);
		}
	}
}
int main() {
	int W[MAX_VERTICES][MAX_VERTICES] = 
	{	// 인접행렬
		{  0, 32,INF, 17,INF,INF,INF,INF,INF,INF},
		{ 32,  0,INF,INF, 45,INF,INF,INF,INF,INF},
		{INF,INF,  0, 18,INF,INF,  5,INF,INF,INF},
		{ 17,INF, 18,  0, 10,INF,INF,  3,INF,INF},
		{INF, 45,INF, 10,  0, 28,INF,INF, 25,INF},
		{INF,INF,INF,INF, 28,  0,INF,INF,INF,  6},
		{INF,INF,  5,INF,INF,INF,  0, 59,INF,INF},
		{INF,INF,INF,  3,INF,INF, 59,  0,  4,INF},
		{INF,INF,INF,INF, 25,INF,INF,  4,  0, 12},
		{INF,INF,INF,INF,INF,  6,INF,INF, 12,  0} 
	};

	//간선은 많아봤자 MAX_VERTICES*(MAX_VERTICES-1)/2개 존재한다.
	element edge_set[MAX_VERTICES*(MAX_VERTICES-1)/2];

	//초기화
	int i, j;
	for (i = 0; i < MAX_VERTICES; ++i) {
		for (j = i; j < MAX_VERTICES; ++j) {
			// 인접행렬을 읽어 간선을 간선집합에 추가한다.
			if (W[i][j] != INF && W[i][j] != 0) { 
				edge_set[totalEdge_num].key = W[i][j];
				edge_set[totalEdge_num].u = i;
				edge_set[totalEdge_num].v = j;
				++totalEdge_num; // 간선이 하나 늘음
			}
		}
	}
	printf("Kruskal 알고리즘을 이용한 최소신장트리 만들기 순서\n");
	krustkal(edge_set, MAX_VERTICES);
}