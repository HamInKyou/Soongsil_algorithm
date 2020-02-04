#include <stdio.h>
#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 10	//���� �� ����
#define INF 999 //��ΰ� ���� ��� ǥ��

//������� �ʱ�ȭ
int W[MAX_VERTICES][MAX_VERTICES] = {
	{  0, 32,INF, 17,INF,INF,INF,INF,INF,INF},
	{ 32,  0,INF,INF, 45,INF,INF,INF,INF,INF},
	{INF,INF,  0, 18,INF,INF,  5,INF,INF,INF},
	{ 17,INF, 18,  0, 10,INF,INF,  3,INF,INF},
	{INF, 45,INF, 10,  0, 28,INF,INF, 25,INF},
	{INF,INF,INF,INF, 28,  0,INF,INF,INF,  6},
	{INF,INF,  5,INF,INF,INF,  0, 59,INF,INF},
	{INF,INF,INF,  3,INF,INF, 59,  0,  4,INF},
	{INF,INF,INF,INF, 25,INF,INF,  4,  0, 12},
	{INF,INF,INF,INF,INF,  6,INF,INF, 12,  0},
};

int selected[MAX_VERTICES]; //�湮 ��Ÿ���� ���� Array
int distance[MAX_VERTICES]; //�� �������� ������ ���������� �Ÿ��� ��Ÿ���� Array

//���� �ּ� �Ÿ��� vertex return �ϴ� �Լ�
int get_min_vertex(int n)
{
	int v, i;

	//distance[]���ϱ� ���� ó�� �߰��� ��Ž���������� v �ʱ�ȭ
	for (i = 0; i < n; i++)
	{
		if (selected[i] == FALSE) {
			v = i;
			break;
		}
	}

	//�ּҰŸ� ���� ã��
	for (i = 0; i < n; i++)
	{
		if (selected[i] == FALSE && (distance[i] < distance[v]))
			v = i;
	}

	//�ּҰŸ� ���� ����
	return(v);
}

//prim �˰���, s�� �������, n�� ��� ���� ����
void prim(int s, int n)
{
	int i, u, v;

	//�ʱ�ȭ����
	for (u = 0; u < n; u++)
	{
		distance[u] = INF;
		selected[u] = FALSE;
	}
	distance[s] = 0;

	//��� �������� ����
	for (i = 0; i < n; i++)
	{
		u = get_min_vertex(n); //�ּ� �Ÿ� ���� ã��
		selected[u] = TRUE; //�湮�ߴٰ� ǥ��

		if (distance[u] == INF) return; //���� ���� ��� �߰��� ������

		printf(" < V%d >", u+1); //���� �湮�� ���� ���

		for (v = 0; v < n; v++)
		{		
			if (W[u][v] != INF) //v�� ������ ������ ���
			{
				// ���� ���õ��� �ʾ�����
				// �ش� ��(weight[u][v])�� ���̰� ������ dist[v] ������ �۴ٸ�
				if (selected[v] == FALSE && W[u][v] < distance[v])
					distance[v] = W[u][v]; //����u�� ���� �����Ÿ��� �缳��
			}
		}
	}
}

void main()
{
	printf("prim�˰����� ����Ͽ� ã�� �ּҺ�� ����Ʈ�� ���\n\n");
	// ���� ������ 10���� �׷������� 0�� ������ ����Ͽ� ���� �� �ִ� �ּҺ�����Ʈ���� ã�ƶ�.
	prim(9, MAX_VERTICES);
	printf("\n");
}