#include<iostream>
#include<fstream>
#include<cctype>
#include<string>

int main(int argc,char** argv)
{
    if(argc!=2)
    {
        std::cerr<<"using:"<<argv[0]<<"filename";
        return 1;
    }
    std::ifstream file(argv[1]);
    if(!file)
    {
        std::cerr<<"error opening:"<<argv[1]<<"\n";
        return 1;
    }
    int lines=0,words=0,chars=0;
    std::string line;
    while(std::getline(file,line))
    {
        lines++;
        chars+=line.length()+1;//symbol of new line
        bool in_word=false;
        for(char ch:line)
        {
            if(std::isspace(ch))
            {
                in_word=false;
            }
            else if(!in_word)
            {
                in_word=true;
                words++;
            }
        }
    }
    std::cout<<lines<<" "<<words<<" "<<chars<<" "<<argv[1]<<std::endl;
    return 0;
}
//tee ff
//33
//44
//55
//ctrl+D
//Lines:3
//Words:3
//Characters:9
