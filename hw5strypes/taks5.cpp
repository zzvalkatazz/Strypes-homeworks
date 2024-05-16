#include<iostream>
unsigned int reverse(int n)
{
	unsigned reversedNum = 0;
	while (n != 0)
	{
		unsigned int lastDigit = n % 10;
		reversedNum *= 10;
		reversedNum += lastDigit;
		n /= 10;
	}
	return reversedNum;
}
bool isPalindrome(unsigned int n)
{
	if (n == reverse(n))
	{
		return true;
	}
	return false;
}
int main()
{
	std::cout <<std::boolalpha<< isPalindrome(2221) << std::endl;
	std::cout <<std::boolalpha<< isPalindrome(1221) << std::endl;
}