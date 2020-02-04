#include <stdio.h>
#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 10	//정점 총 개수
#define INF 999 //경로가 없는 경우 표현

//인접행렬 초기화
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

int selected[MAX_VERTICES]; //방문 나타내기 위한 Array
int distance[MAX_VERTICES]; //한 정점에서 인접한 정점까지의 거리를 나타내는 Array

//제일 최소 거리인 vertex return 하는 함수
int get_min_vertex(int n)
{
	int v, i;

	//distance[]비교하기 위해 처음 발견한 미탐사정점으로 v 초기화
	for (i = 0; i < n; i++)
	{
		if (selected[i] == FALSE) {
			v = i;
			break;
		}
	}

	//최소거리 정점 찾기
	for (i = 0; i < n; i++)
	{
		if (selected[i] == FALSE && (distance[i] < distance[v]))
			v = i;
	}

	//최소거리 정점 리턴
	return(v);
}

//prim 알고리즘, s는 출발정점, n은 모든 정점 개수
void prim(int s, int n)
{
	int i, u, v;

	//초기화과정
	for (u = 0; u < n; u++)
	{
		distance[u] = INF;
		selected[u] = FALSE;
	}
	distance[s] = 0;

	//모든 정점에서 실행
	for (i = 0; i < n; i++)
	{
		u = get_min_vertex(n); //최소 거리 정점 찾기
		selected[u] = TRUE; //방문했다고 표시

		if (distance[u] == INF) return; //갈데 없는 경우 중간에 끝내기

		printf(" < V%d >", u+1); //현재 방문한 정점 출력

		for (v = 0; v < n; v++)
		{		
			if (W[u][v] != INF) //v가 인접한 정점일 경우
			{
				// 아직 선택되지 않았으며
				// 해당 변(weight[u][v])의 길이가 기존의 dist[v] 값보다 작다면
				if (selected[v] == FALSE && W[u][v] < distance[v])
					distance[v] = W[u][v]; //정점u에 대한 인접거리로 재설정
			}
		}
	}
}

void main()
{
	printf("prim알고리즘을 사용하여 찾은 최소비용 신장트리 경로\n\n");
	// 정점 개수가 10개인 그래프에서 0번 정점을 출발하여 얻을 수 있는 최소비용신장트리를 찾아라.
	prim(9, MAX_VERTICES);
	printf("\n");
}