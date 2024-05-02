#include<iostream>
#include<fstream>
#include<string>

int main(int argc,char** argv)
{
    if(argc!=2)
    {
        std::cerr<<"Using:"<<argv[0] <<" <filename> <N> \n";
        return 1;
    }
    std::ifstream file(argv[1]);
    if(!file)
    {
        std::cerr<<"Error opening file:"<<argv[1]<<"\n";
        return 1;
    }
    std::string line;
    int count=0;
    while(std::getline(file,line) && count<10)
    {
        std::cout<<line<<std::endl;
        count++;
    }
    return 0;
}
// fg contains numbers from 1 to 13
//g++ -o head hw2task3.cpp
// ./head fg
//1
//2
//3
//4
//5
//6
//7
//8
//9
//10