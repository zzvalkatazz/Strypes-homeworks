#include<iostream>

bool isPrime(int n)
{
	bool isPrime = true;
	for (int i = 2; i <= sqrt(n); i++)
	{
		if (n % i == 0)
		{
			isPrime = false;
			break;
		}
	}
	return isPrime;
}
int main()
{
	std::cout <<std::boolalpha<<isPrime(5) << std::endl;
	std::cout <<std::boolalpha<<isPrime(39) << std::endl;
}