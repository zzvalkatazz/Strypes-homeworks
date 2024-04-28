#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	//a)
	int mass;
	cout << "insert mass:" << endl;
	cin >> mass;
	float height;
	cout << "insert height:" << endl;
	cin >> height;
	float bmi;
	bmi = mass / (height * height);
	cout <<"bmi:"<< bmi << endl;
	//б)
	float newBmi;
	newBmi = (1.3 / sqrt(height)) * bmi;
	cout <<"New bmi:"<< newBmi << endl;
	float newBmi1;
	newBmi1 = (1.3 * mass) / (pow(height, 2.5));
	cout << "New bmi1:" << newBmi1 << endl;
	return 0;
}
