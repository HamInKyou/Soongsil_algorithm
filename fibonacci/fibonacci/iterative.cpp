//iterative방식으로 구현한 fibonacci algorithm 입니다.
#include<iostream>
#include<Windows.h>
using namespace std;

int main() {
	LARGE_INTEGER frequency; 
	LARGE_INTEGER beginTime;
	LARGE_INTEGER endTime;  
	__int64 elapsed;         
	double duringTime;       

	QueryPerformanceFrequency(&frequency);

	int i, n;
	unsigned long long* fibonacciList = new unsigned long long[201]; // 0~200까지, 201칸짜리 배열을 만든다.
	cout << "몇번째 수를 구하고 싶으신가요? :";
	cin >> n;
	QueryPerformanceCounter(&beginTime); // 시간측정 시작
	fibonacciList[0] = 0; //0번째 초기화
	if (n > 0) {
		fibonacciList[1] = 1; //1번째 초기화
		for (i = 2; i <= n; i++) { //계산해서 n번째까지 채우는 과정
			fibonacciList[i] = fibonacciList[i - 1] + fibonacciList[i - 2]; 
		}
	}
	
	QueryPerformanceCounter(&endTime); // 시간측정 끝
	elapsed = endTime.QuadPart - beginTime.QuadPart;
	duringTime = (double)elapsed / (double)frequency.QuadPart;
	duringTime *= 1000;

	cout << n << "번째 수는 " << fibonacciList[n] << "입니다." << endl;
	cout << "처리속도 : " << duringTime << "ms" << endl;
	delete []fibonacciList; // 할당된 배열 풀어준다.
}