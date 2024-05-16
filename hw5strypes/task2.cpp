#include<iostream>
unsigned long factorial(int n)
{
	if (n > 1)
	{
		return n* factorial(n - 1);
	}
	return 1;
}

int main()
{
	std::cout << factorial(25) << std::endl;
}