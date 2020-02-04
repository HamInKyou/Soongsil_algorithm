#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

//교환
void change(float* A, float* B) {
	float temp;
	temp = *A;
	*A = *B;
	*B = temp;
}

//배열 출력
void printArr(int arraySize, float* Arr) {
	for (int i = 0; i < arraySize; i++) {
		printf("[%.3f]", Arr[i]);
	}
	printf("\n");
}

//원본의 배열 복사한 복사본 만들기
void makeSameArr(int arraySize, float* beforeArr, float* tempArr) {
	for (int i = 0; i < arraySize; i++) {
		tempArr[i] = beforeArr[i];
	}
}
void exchangeSort(int arraySize, float* beforeArr); //교환정렬
void insertionSort(int arraySize, float* beforeArr); //삽입정렬
void MergeSort(int arraySize, float* beforeArr); //합병정렬
void merge(int h, int m, const float* U, const float* V, float* S);
void QuickSort(float* beforeArr, int p, int r); //퀵정렬
int partition(float* arr, int p, int r);

int main(void) {
	LARGE_INTEGER frequency;
	LARGE_INTEGER beginTime;
	LARGE_INTEGER endTime;
	__int64 elapsed;
	double duringTime;

	float* inputArray;
	float* tempArray;
	int arraySize;


	QueryPerformanceFrequency(&frequency);
	srand(time(NULL));

	for (int menu = 0; menu <= 1; menu++) {
		if (menu == 0) {
			arraySize = 10;
			inputArray = (float*)calloc(arraySize, sizeof(float));
			tempArray = (float*)calloc(arraySize, sizeof(float));

			for (int i = 0; i < arraySize; i++) {
				inputArray[i] = rand() / (float)RAND_MAX * 2 - 1;
			}
			printf("크기 10의 배열을 생성하고 각각의 방법으로 정렬합니다.\n\n");

			//정렬하기 전 배열 출력
			printf("정렬 전 : ");
			printArr(arraySize, inputArray);

			//결과 출력
			printf("<exchangeSort>\n");
			printf("정렬 후 : ");
			makeSameArr(arraySize, inputArray, tempArray);
			exchangeSort(arraySize, tempArray);
			printArr(arraySize, tempArray);

			printf("<InsertionSort>\n");
			printf("정렬 후 : ");
			makeSameArr(arraySize, inputArray, tempArray);
			insertionSort(arraySize, tempArray);
			printArr(arraySize, tempArray);

			printf("<MergeSort>\n");
			printf("정렬 후 : ");
			makeSameArr(arraySize, inputArray, tempArray);
			MergeSort(arraySize, tempArray);
			printArr(arraySize, tempArray);

			printf("<QuickSort>\n");
			printf("정렬 후 : ");
			makeSameArr(arraySize, inputArray, tempArray);
			QuickSort(tempArray, 0, arraySize - 1);
			printArr(arraySize, tempArray);

			free(inputArray);
			free(tempArray);
		}

		else {
			printf("\n\n배열의 크기를 변경시키면서 실행시간을 측정합니다.\n\n");
			for (int i = 0; i < 12; i++) {
				switch (i)
				{
				case 0:
					arraySize = 100;
					break;
				case 1:
					arraySize = 200;
					break;
				case 2:
					arraySize = 300;
					break;
				case 3:
					arraySize = 400;
					break;
				case 4:
					arraySize = 500;
					break;
				case 5:
					arraySize = 750;
					break;
				case 6:
					arraySize = 1000;
					break;
				case 7:
					arraySize = 1500;
					break;
				case 8:
					arraySize = 2000;
					break;
				case 9:
					arraySize = 3000;
					break;
				case 10:
					arraySize = 4000;
					break;
				case 11:
					arraySize = 5000;
					break;
				}
				printf("배열의 크기가 %d 일 때\n", arraySize);
				inputArray = (float*)calloc(arraySize, sizeof(float));
				tempArray = (float*)calloc(arraySize, sizeof(float));
				for (int i = 0; i < arraySize; i++) {
					inputArray[i] = rand() / (float)RAND_MAX * 2 - 1;
				}
				for (int i = 0; i < 4; i++) {
					makeSameArr(arraySize, inputArray, tempArray);

					QueryPerformanceCounter(&beginTime);

					switch (i)
					{
					case 0:
						printf("┌ <exchangeSort> : ");
						exchangeSort(arraySize, tempArray);
						break;
					case 1:
						printf("│ <InsertionSort> : ");
						insertionSort(arraySize, tempArray);
						break;
					case 2:
						printf("│ <MergeSort> : ");
						MergeSort(arraySize, tempArray);
						break;
					case 3:
						printf("└ <QuickSort> : ");
						QuickSort(tempArray, 0, arraySize - 1);
						break;
					}

					QueryPerformanceCounter(&endTime);

					elapsed = endTime.QuadPart - beginTime.QuadPart;
					duringTime = (double)elapsed / (double)frequency.QuadPart;
					duringTime *= 1000;

					printf("%f ms\n", duringTime);
				}
				printf("\n");
			}
		}

	}

	return 0;
}

void exchangeSort(int arraySize, float* Arr)
{
	//정렬
	for (int i = 0; i < arraySize - 1; i++) {
		for (int j = i + 1; j < arraySize; j++) {
			if (Arr[j] < Arr[i]) {
				change(&Arr[i], &Arr[j]);
			}
		}
	}
}
void insertionSort(int arraySize, float* Arr)
{
	float big; //큰값 비교하기 위해 넣어둔 변수, 다 -1보다 크니까 초기값 -1로 설정
	int bigIdx = 0; //큰값의 인덱스를 저장하기 위한 변수

	//정렬
	for (int i = arraySize - 1; i > 0; i--) {
		big = -1;
		for (int j = 0; j <= i; j++) {
			if (Arr[j] > big) {
				big = Arr[j];
				bigIdx = j;
			}
		}
		change(&Arr[i], &Arr[bigIdx]);
	}
}

void MergeSort(int arraySize, float* beforeArr)
{
	if (arraySize > 1) {
		const int h = arraySize / 2;
		const int m = arraySize - h;
		float* U = (float*)calloc(h, sizeof(float));
		float* V = (float*)calloc(m, sizeof(float));


		makeSameArr(h, beforeArr, U);
		makeSameArr(m, beforeArr + h, V);

		MergeSort(h, U);
		MergeSort(m, V);

		merge(h, m, U, V, beforeArr);
	}
}

void merge(int h, int m, const float* U, const float* V, float* S)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int rest = 0;




	while (i < h && j < m) {
		if (U[i] < V[j]) {
			S[k] = U[i];
			i++;
		}
		else {
			S[k] = V[j];
			j++;
		}
		k++;
	}


	if (i >= h) {
		rest = m - j;
		makeSameArr(rest, V + j, S + k);

	}
	else {
		rest = h - i;
		makeSameArr(rest, U + i, S + k);
	}


}

void QuickSort(float* beforeArr, int p, int r)
{
	int q;
	if (p < r) {
		q = partition(beforeArr, p, r);
		QuickSort(beforeArr, p, q - 1);
		QuickSort(beforeArr, q + 1, r);
	}
}

int partition(float* arr, int p, int r) {
	int i = p;
	int j = p;

	while (j < r) {
		if (arr[j] < arr[r]) { //기준(arr[r])보다 작으면
			change(&arr[i], &arr[j]);
			i++;
			j++;
		}
		else { //기준(arr[r])보다 크면
			j++;
		}
	}

	change(&arr[i], &arr[j]);
	return i;
}