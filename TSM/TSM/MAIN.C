#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int** W;  //������� �Է°�
int** D;  //�ִܰ�� ����迭
int** P;   //P[Vi][A] = D[Vi][A]�� �ִܰ�η� ���� ó������ ����
int* subset;   //�� �κ������̸�, ���Ұ����� �����Ѵ�.

int max;     //�κ� ���� �ִ� ���� ����
int node_EA;   //������ ���� 


void mininum(int i, int A) {
	int j, s;                
	//A�� �κ� ���� 
	D[i][A] = 1000; // ��(1000)�� �ʱ�ȭ
	for (j = 0; j < node_EA; j++) {
		s = (int)pow(2, j);  //pow�Լ��� ������ ���ϱ� 2^j
		if ((A & s) != 0) {  //Vj�� A�� ���� ���
			if (D[i][A] > W[i][j] + D[j][A - s]) {
				D[i][A] = W[i][j] + D[j][A - s];
				P[i][A] = j;   //j�� �ּҰ� ����
			}
		}
	}
}

int travel() {     //��� ���ϱ�
	int i, k, A;
	int minlength; //���� ��� ����

	for (i = 0; i < node_EA; i++)
		D[i][0] = W[i][0];

	for (k = 1; k <= node_EA - 2; k++)
	{
		for (A = 0; A < max; A++)
		{     //subset A�� �ڽ��� �� ������ k���� ������ ������ �κ�����
			if (subset[A] == k && (A & 1) == 0)
			{
				for (i = 0; i < node_EA; i++)
				{
					if (A & (int)pow(2, i)) 
						continue;
					mininum(i, A); //Vi�� A�� ���� ��� ������ ���ϱ�
				}
			}
		}
	}
	mininum(0, max - 2);
	minlength = D[0][max - 2];
	return minlength;
}



void path(int i, int A)  //��θ� ��� �ϴ� �Լ� 
{
	int j = P[i][A];
	printf("V%d -> ", i + 1);
	if (A - pow(2, j) != 0)
		path(j, (int)A - pow(2, j));
	else
		printf("V%d -> V%d\n", j + 1, 1);
}

void print(int min_lenth) //ȭ�鿡 ��� ��� �Լ�
{
	int i, j, a;

	if (min_lenth >= 1000)
		printf("�Ұ����� ����Դϴ�.");
	else
	{
		printf("\n���\n");
		printf("�ּ� ��� : ");               //������
		path(0, max - 2);
		printf("\n����� �Ÿ� : %d \n\n", min_lenth); //�ּҺ�� ���
	}
}

int main()
{
	int i, j;      //for���� ���Ǵ� ���� 
	int tmp, middle_max, subset_count;   //�κ����� ���� ���ϱ����� �ʿ��� ����
	int min_lenth;  //�ִ� ���� ���



	printf("������ ������ �Է��Ͻʽÿ� : ");
	scanf_s("%d", &node_EA);

	max = (int)pow(2, node_EA);      //�κ����� �ִ� ���� 

	W = (int**)malloc(node_EA * sizeof(int));   //�� �迭�� �޸� �Ҵ� 
	D = (int**)malloc(node_EA * sizeof(int));
	P = (int**)malloc(node_EA * sizeof(int));
	subset = (int*)malloc(max * sizeof(int));

	for (i = 0; i < node_EA; i++)
	{
		D[i] = (int*)malloc(max * sizeof(int));
		P[i] = (int*)malloc(max * sizeof(int));
		for (j = 0; j < max; j++)
		{
			D[i][j] = P[i][j] = 0;    //�迭 D,P �ʱ�ȭ 
		}
	}

	printf("\n��������� �Է��Ͻʽÿ�.\n");
	for (i = 0; i < node_EA; i++)
	{
		W[i] = (int*)malloc(node_EA * sizeof(int));
		for (j = 0; j < node_EA; j++)
		{ //���Ϸ� ���� ����ġ �о �迭 W�� ����
			scanf_s("%d", &W[i][j]);
		}
	}


	for (i = 0; i < max; i++)        //�� ���������� �κ����� ���� ���ϱ� 
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

	min_lenth = travel();//�ּ� ��� ã�� 


	print(min_lenth);   //��� ���


	for (i = 0; i < node_EA; i++)     //�� �迭�� �޸� �Ҵ� ���� �ϱ� 
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