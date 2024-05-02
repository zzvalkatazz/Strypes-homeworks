#include<iostream>
#include<fstream>
#include<queue>
#include<string>

int main(int argc,char** argv)
{
    if(argc!=2)
    {
        std::cerr<<"Using:"<<argv[0]<<"<filename> <N>\n";
        return 1;
    }
    std::ifstream file(argv[1]);
    if(!file)
    {
        std::cerr<<"Error opening file:"<<argv[1]<<"\n";
        return 1;
    }
    std::queue<std::string> lines;
    std::string line;
    
    while(std::getline(file,line))
    {
        lines.push(line);
        if(lines.size()>10)
        {
            lines.pop();
        }
    }
    while(!lines.empty())
    {
        std::cout<<lines.front()<<std::endl;
        lines.pop();
    }
    return 0;
}
// fg contains numbers from 1 to 13
//g++ -o tail hw2task4.cpp
// ./tail fg
//4
//5
//6
//7
//8
//9
//10
//11
//12
//13