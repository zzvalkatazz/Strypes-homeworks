#include<iostream>
unsigned long fib(int n)
{
	int prev;
	int previous = 0;
	int curr = 1;
	for (int i = 1; i < n; i++)
	{
		prev = previous;
		previous = curr;
		curr = previous + prev;
	}
	return curr;
}
//���� �� �� ����� � ��������,������ ������ ����� �����
int main()
{
	std::cout << fib(7) << std::endl;
	std::cout << fib(69) << std::endl;
}