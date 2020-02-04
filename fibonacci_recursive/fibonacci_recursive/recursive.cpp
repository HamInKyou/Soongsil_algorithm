//recursive������� ������ fibonacci algorithm �Դϴ�.
#include<iostream>
#include<Windows.h>
using namespace std;

unsigned long long fibonacci(int n); //�Լ�����

int main() {
	LARGE_INTEGER frequency;
	LARGE_INTEGER beginTime;
	LARGE_INTEGER endTime;
	__int64 elapsed;
	double duringTime;
	QueryPerformanceFrequency(&frequency);

	int n; //���°�� ���� ���ϴ��� �����ϴ� ����
	unsigned long long result; //�ش��ϴ� ������ ���� �����ϴ� ����

	cout << "���° ���� ���ϰ� �����Ű���? :";
	cin >> n;
	QueryPerformanceCounter(&beginTime); //�Է��ϰ� �� ��, ��������
	result = fibonacci(n);

	QueryPerformanceCounter(&endTime); //result ����������, �����Ϸ�
	elapsed = endTime.QuadPart - beginTime.QuadPart;
	duringTime = (double)elapsed / (double)frequency.QuadPart;
	duringTime *= 1000;

	cout << n << "��° ���� " << result << "�Դϴ�." << endl;
	cout << "ó���ӵ� : " << duringTime << "ms" << endl;
}

//recursive����� ���� fibonacci �Լ�
//�μ� n : ���ϰ����ϴ� index
unsigned long long fibonacci(int n) { 
	if (n <= 1) //n�� 1������ ��� ����� ���� �����Ƿ� n �� ��ü return
		return n; 
	else //n�� 1���� Ŭ ��� ��������� fibonacci�� �ҷ����� ������ݴϴ�.
		return fibonacci(n - 1) + fibonacci(n - 2);
}