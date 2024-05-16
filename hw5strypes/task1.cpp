#include<iostream>
#include<cmath>
#ifndef Math_PI
#define Math_PI 3.14159265358979323846
#endif
double circleArea(double R)
{
	return R * R *Math_PI;
}
int main()
{
  std::cout << circleArea(5);
}
