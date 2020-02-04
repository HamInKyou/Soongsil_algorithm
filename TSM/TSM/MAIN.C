#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int** W;  //인접행렬 입력값
int** D;  //최단경로 저장배열
int** P;   //P[Vi][A] = D[Vi][A]의 최단경로로 갈때 처음가는 원소
int* subset;   //각 부분집합이며, 원소갯수를 저장한다.

int max;     //부분 집합 최대 원소 갯수
int node_EA;   //정점의 갯수 


void mininum(int i, int A) {
	int j, s;                
	//A는 부분 집합 
	D[i][A] = 1000; // ∞(1000)로 초기화
	for (j = 0; j < node_EA; j++) {
		s = (int)pow(2, j);  //pow함수로 지수승 구하기 2^j
		if ((A & s) != 0) {  //Vj가 A에 있을 경우
			if (D[i][A] > W[i][j] + D[j][A - s]) {
				D[i][A] = W[i][j] + D[j][A - s];
				P[i][A] = j;   //j의 최소값 저장
			}
		}
	}
}

int travel() {     //경로 구하기
	int i, k, A;
	int minlength; //최적 경로 길이

	for (i = 0; i < node_EA; i++)
		D[i][0] = W[i][0];

	for (k = 1; k <= node_EA - 2; k++)
	{
		for (A = 0; A < max; A++)
		{     //subset A는 자신을 뺀 나머지 k개의 정점을 포함한 부분집합
			if (subset[A] == k && (A & 1) == 0)
			{
				for (i = 0; i < node_EA; i++)
				{
					if (A & (int)pow(2, i)) 
						continue;
					mininum(i, A); //Vi가 A에 없을 경우 최적값 구하기
				}
			}
		}
	}
	mininum(0, max - 2);
	minlength = D[0][max - 2];
	return minlength;
}



void path(int i, int A)  //경로를 출력 하는 함수 
{
	int j = P[i][A];
	printf("V%d -> ", i + 1);
	if (A - pow(2, j) != 0)
		path(j, (int)A - pow(2, j));
	else
		printf("V%d -> V%d\n", j + 1, 1);
}

void print(int min_lenth) //화면에 결과 출력 함수
{
	int i, j, a;

	if (min_lenth >= 1000)
		printf("불가능한 경로입니다.");
	else
	{
		printf("\n결과\n");
		printf("최소 경로 : ");               //경로출력
		path(0, max - 2);
		printf("\n경로의 거리 : %d \n\n", min_lenth); //최소비용 출력
	}
}

int main()
{
	int i, j;      //for문에 사용되는 변수 
	int tmp, middle_max, subset_count;   //부분집합 개수 구하기위해 필요한 변수
	int min_lenth;  //최단 길이 경로



	printf("정점의 개수를 입력하십시오 : ");
	scanf_s("%d", &node_EA);

	max = (int)pow(2, node_EA);      //부분집합 최대 갯수 

	W = (int**)malloc(node_EA * sizeof(int));   //각 배열들 메모리 할당 
	D = (int**)malloc(node_EA * sizeof(int));
	P = (int**)malloc(node_EA * sizeof(int));
	subset = (int*)malloc(max * sizeof(int));

	for (i = 0; i < node_EA; i++)
	{
		D[i] = (int*)malloc(max * sizeof(int));
		P[i] = (int*)malloc(max * sizeof(int));
		for (j = 0; j < max; j++)
		{
			D[i][j] = P[i][j] = 0;    //배열 D,P 초기화 
		}
	}

	printf("\n인접행렬을 입력하십시오.\n");
	for (i = 0; i < node_EA; i++)
	{
		W[i] = (int*)malloc(node_EA * sizeof(int));
		for (j = 0; j < node_EA; j++)
		{ //파일로 부터 가중치 읽어서 배열 W에 저장
			scanf_s("%d", &W[i][j]);
		}
	}


	for (i = 0; i < max; i++)        //각 정점에서의 부분집합 갯수 구하기 
	{
		tmp = i;
		middle_max = max / 2;
		subset_count = 0;
		while (tmp > 0)
		{
			if (tmp - middle_max >= 0)
			{
				tmp = tmp - middle_max;
				subset_count++;
			}
			middle_max = middle_max / 2;
		}
		subset[i] = subset_count;
	}

	min_lenth = travel();//최소 경로 찾기 


	print(min_lenth);   //결과 출력


	for (i = 0; i < node_EA; i++)     //각 배열들 메모리 할당 해제 하기 
	{
		free(W[i]);
		free(D[i]);
		free(P[i]);
	}

	free(D);
	free(P);
	free(subset);
	free(W);
	return 0;
}