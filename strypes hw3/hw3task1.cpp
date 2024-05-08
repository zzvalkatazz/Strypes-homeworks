#include<iostream>
using namespace std;
bool XOR(bool a,bool b)
{
    return(a && !b) || (!a && b);
}
int main()
{
    bool num1,num2;
    cin>>num1;
    cin>>num2;
    bool result=XOR(num1,num2);
    cout<<result<<endl;
}
//Terminal
// tee numbers.txt
//1
//1
//g++ -o hw3task1 hw3task1.cpp
// ./hw3task1 < numbers.txt
// Output:
//0