//recursive방식으로 구현한 fibonacci algorithm 입니다.
#include<iostream>
#include<Windows.h>
using namespace std;

unsigned long long fibonacci(int n); //함수선언

int main() {
	LARGE_INTEGER frequency;
	LARGE_INTEGER beginTime;
	LARGE_INTEGER endTime;
	__int64 elapsed;
	double duringTime;
	QueryPerformanceFrequency(&frequency);

	int n; //몇번째의 수를 원하는지 저장하는 변수
	unsigned long long result; //해당하는 차례의 수를 저장하는 변수

	cout << "몇번째 수를 구하고 싶으신가요? :";
	cin >> n;
	QueryPerformanceCounter(&beginTime); //입력하고 난 뒤, 측정시작
	result = fibonacci(n);

	QueryPerformanceCounter(&endTime); //result 저장했으니, 측정완료
	elapsed = endTime.QuadPart - beginTime.QuadPart;
	duringTime = (double)elapsed / (double)frequency.QuadPart;
	duringTime *= 1000;

	cout << n << "번째 수는 " << result << "입니다." << endl;
	cout << "처리속도 : " << duringTime << "ms" << endl;
}

//recursive방식을 위한 fibonacci 함수
//인수 n : 구하고자하는 index
unsigned long long fibonacci(int n) { 
	if (n <= 1) //n이 1이하일 경우 계산할 것이 없으므로 n 그 자체 return
		return n; 
	else //n이 1보다 클 경우 재귀적으로 fibonacci를 불러내어 계산해줍니다.
		return fibonacci(n - 1) + fibonacci(n - 2);
}