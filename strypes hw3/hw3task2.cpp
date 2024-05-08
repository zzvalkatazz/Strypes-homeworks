#include<iostream>
using namespace std;
bool F1(bool a, bool b, bool c)
{
	return ((!a && !b && !c) || (!a && b && !c) || (!a && b && c) || (a && b && c));
}
bool F0(bool a, bool b, bool c)
{
	return ((a || b || !c) && (!a || b || c) && (!a || b || !c) && (!a || !b || c));
}
bool FMin(bool a, bool b, bool c)
{
	return (b && c) || (!a && !c);
}
int main()
{
	bool a, b, c;
	cin >> a >> b >> c;
	//с логически израз ссинтезиран по 1
	cout  << F1(a, b, c) << endl;
	//с логически израз синтезиран по 0
	cout << F0(a, b, c) << endl;
	//минимален израз
	cout << FMin(a, b, c) << endl;
	return 0;
}
//Minimization
//!a!b!c+!ab!c+!abc+abc
//bc(!a+a)+!a!c(b+!b)
//(a+!a)==(b+!b)==1
//bc+!a!c