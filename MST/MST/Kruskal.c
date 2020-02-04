#include <stdio.h>
#include <stdlib.h> // �����ϱ� ���� qsrot �Լ��� ����� ��� ����
#define MAX_VERTICES 10 // ������ ��
#define INF 999 //������ ������ ǥ��

typedef struct { // ������ ������ ����� ���� ����ü
	int key; // ������ ����ġ
	int u; // ���� 1
	int v; // ���� 2
}element;

int parent[MAX_VERTICES]; // �θ� ���
int totalEdge_num = 0; // ������ ����

 // �������� �� �Լ� ����
int compare(const void* a, const void* b) {
	element* m = (element*)a;
	element* n = (element*)b; 
	if (m->key < n->key) return -1; // a�� b���� ���� ���� -1 ��ȯ
	if (m->key > n->key) return 1; // a�� b���� Ŭ ���� 1 ��ȯ
	return 0; // a�� b�� ���� ���� 0 ��ȯ 
}

int find_set(int v) { // v�� ���ϴ� ������ ��ȯ
	while (parent[v] >= 0) {
		v = parent[v]; // ��Ʈ ������ �ݺ�
	}
	return v; // ������ ��ǥ ���Ҹ� ��ȯ
}

// �� ���� ���Ұ� ���� ������ ��ģ��.
void union_set(int n1, int n2) { 
	int temp; // parent �迭�� ���Ҹ� ��Ʈ ���� �ٲٰ� �Ǹ� �� ������ ������ ������� ������ ������ ������ �����ص� ����
	int i;

	// ���� ������ ������ �ִ� �迭�� ������ �ʰ�
	// parent �迭���� ����� �ε����� ��Ʈ��带 ��Ÿ����,
	// ������ ��Ʈ���ν� �ε����� ���밪�� ������ ������ ��Ÿ���Ƿ� ������ ����� ���� �����Ѵ�.

	if (parent[n1] < 0 && parent[n2] < 0) { // �� ������ ���� ��Ʈ ����� ��
		if (parent[n1] <= parent[n2]) { // n1�� ������ ������ n2���� �۰ų� ���ٸ�
			temp = parent[n2]; // n2�� ������ ����
			parent[n2] = n1; // n2�� ��Ʈ�� n1���� ����
			parent[n1] += temp; // n1�� n2�� ������ ����
		}
		else { // n1�� ������ ������ n2���� ũ�ٸ�
			temp = parent[n1]; // n1�� ������ ����
			parent[n1] = n2; // n1�� ��Ʈ�� n2���� ����
			parent[n2] += temp; // n2�� n1�� ������ ����
		}
	}
	// �� ������ ��Ʈ ����� ��(n1�� ��Ʈ ���)
	else if (parent[n1] < 0 && parent[n2] >= 0) { 
		temp = parent[n1]; // n1�� ������ ����
		parent[n1] = parent[n2]; // n1�� ��Ʈ�� n2�� ��Ʈ�� ����
		parent[parent[n2]] += temp; // n2�� ��Ʈ�� n1�� ������ ����
	}
	// �� ������ ��Ʈ ����� ��(n2�� ��Ʈ ���)
	else if (parent[n1] >= 0 && parent[n2] < 0) {
		temp = parent[n2]; // n2�� ������ ����
		parent[n2] = parent[n1]; // n2�� ��Ʈ�� n1�� ��Ʈ�� ����
		parent[parent[n1]] += temp; // n1�� ��Ʈ�� n2�� ������ ����
	}
	// �� ���� ��� ��Ʈ ��尡 �ƴ� ��
	else { 
		temp = parent[n1]; // n1�� ��Ʈ�� ������� ����
		parent[n1] = parent[n2]; // n1�� ��Ʈ�� n2�� ��Ʈ�� ����
		parent[temp] = parent[n2]; // n1�� ��Ʈ�� ��Ʈ�� n2�� ��Ʈ�� ����
	}

	printf("(%2d - %2d ) union two sets\n", n1 + 1, n2 + 1);
}

// ���� �迭��, ������ �Ѱ���
void krustkal(element edge_set[], int n) {
	int i, u, v;
	int edge_EA = 0; // �ּ� ����� ���ϴµ� ���õ� ������ ��

	// ���������� ���� ����ġ ���� ������ �����Ѵ�.
	qsort(edge_set, totalEdge_num, sizeof(element), compare); 
	
	// ������ ������ŭ parent �迭�� �ʱ�ȭ
	for (i = 0; i < n; ++i) 
		parent[i] = -1;
	
	// ������ ������ n-1�� �� ������ ���� �߰�
	for (i = 0; edge_EA < n - 1; ++i) { 
		u = edge_set[i].u;
		v = edge_set[i].v;

		// �� ���� u�� v�� ���� ���տ� ���ٸ� ����Ŭ�� �߻����� �����Ƿ�
		if (find_set(u) != find_set(v)) { 
			edge_EA++; // ���õ� ������ ������ ����
			union_set(u, v); // ���� u�� v�� ���Ͽ�
		}
		//����Ŭ �߻��ϴ� ���
		else {
			printf("(%2d - %2d ) makes Cycle = pass\n", u+1, v+1);
		}
	}
}
int main() {
	int W[MAX_VERTICES][MAX_VERTICES] = 
	{	// �������
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

	//������ ���ƺ��� MAX_VERTICES*(MAX_VERTICES-1)/2�� �����Ѵ�.
	element edge_set[MAX_VERTICES*(MAX_VERTICES-1)/2];

	//�ʱ�ȭ
	int i, j;
	for (i = 0; i < MAX_VERTICES; ++i) {
		for (j = i; j < MAX_VERTICES; ++j) {
			// ��������� �о� ������ �������տ� �߰��Ѵ�.
			if (W[i][j] != INF && W[i][j] != 0) { 
				edge_set[totalEdge_num].key = W[i][j];
				edge_set[totalEdge_num].u = i;
				edge_set[totalEdge_num].v = j;
				++totalEdge_num; // ������ �ϳ� ����
			}
		}
	}
	printf("Kruskal �˰����� �̿��� �ּҽ���Ʈ�� ����� ����\n");
	krustkal(edge_set, MAX_VERTICES);
}