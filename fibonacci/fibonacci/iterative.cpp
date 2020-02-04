//iterative������� ������ fibonacci algorithm �Դϴ�.
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
	unsigned long long* fibonacciList = new unsigned long long[201]; // 0~200����, 201ĭ¥�� �迭�� �����.
	cout << "���° ���� ���ϰ� �����Ű���? :";
	cin >> n;
	QueryPerformanceCounter(&beginTime); // �ð����� ����
	fibonacciList[0] = 0; //0��° �ʱ�ȭ
	if (n > 0) {
		fibonacciList[1] = 1; //1��° �ʱ�ȭ
		for (i = 2; i <= n; i++) { //����ؼ� n��°���� ä��� ����
			fibonacciList[i] = fibonacciList[i - 1] + fibonacciList[i - 2]; 
		}
	}
	
	QueryPerformanceCounter(&endTime); // �ð����� ��
	elapsed = endTime.QuadPart - beginTime.QuadPart;
	duringTime = (double)elapsed / (double)frequency.QuadPart;
	duringTime *= 1000;

	cout << n << "��° ���� " << fibonacciList[n] << "�Դϴ�." << endl;
	cout << "ó���ӵ� : " << duringTime << "ms" << endl;
	delete []fibonacciList; // �Ҵ�� �迭 Ǯ���ش�.
}