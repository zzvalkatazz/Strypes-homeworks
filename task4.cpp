#include<iostream>
using namespace std;

int main()
{
    float num1,num2,num3;
    cout<<"Insert numbers"<<endl;
    cin>>num1>>num2>>num3;
    double maxNum=num1;
    if(num2>maxNum)
    {
        maxNum=num2;
    }
    if(num3>maxNum)
    {
        maxNum=num3;
    }
   cout<<"Max number is:"<<maxNum<<endl;
   return 0;
}

// on TERMINAL 
// first we create numbers.txt
// echo 21.3 22.7 20.5 > numbers.txt
//these are 3 numbers 
// in same directory we save numbers.txt and task4.cpp
// compile : g++ -o task4 task4.cpp
// ./task4<numbers.txt
//output:
//Insert numbers
// Max number is 22.7
