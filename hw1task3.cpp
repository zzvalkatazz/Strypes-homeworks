#include<iostream>
#include<cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
using namespace std;
double findHorizontalCylinderArea(double r, double h)
{
	double result;
	double number =(r - h) * sqrt(2 * r * h - h * h);
	double arccos = acos((r - h) / r);
	if (number < 0 || r == 0)
	{
		cout << "invalid result" << endl;;
	}
	else
	{
		result = arccos * r*r -number;
	}
	return result;
}
void LadditionVolume()
{
	double R, H, L;
	cout << "á)Insert R ,L  and H" << endl;
	cin >> R;
	cin >> L;
	cin >> H;
	if (2 * R < H)
	{
		return;
	}

	double pi = M_PI;
	
	double water_area=findHorizontalCylinderArea(R,H);
	double water_volume = water_area * L;
	cout << water_volume << endl;
}
int main()
{
	//a)
	double R, H;
	double pi = M_PI;
	cout << "a)Insert R and H" << endl;
	cin >> R;
	cin >> H;
	double water_volume = pi*R*R*H;
	cout << water_volume << endl;
	//á)
	LadditionVolume();
	return 0;
}