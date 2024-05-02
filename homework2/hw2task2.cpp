#include<iostream>
#include<cmath>
#include<limits>
//Function to compare two flotaing-point using direct equality comparison
template<typename T>
bool isEqual(T a,T b)
{
    return a==b;
}
//Function to compare two floating-point number using epsilon comparison
template<typename T>
bool isEqualEpsilon(T a,T b,float epsilon=std::numeric_limits<T>::epsilon())
{
    return std::abs(a-b)<epsilon;
}
//Function to compare two floating-point numbers using relative epsilon comparison
template<typename T>
bool isEqualRelativeEpsilon(T a,T b,T epsilon=std::numeric_limits<T>::epsilon())
{
    float difference=std::abs(a-b);
    float maxValue=std::max(std::abs(a),std::abs(b));
    return difference<epsilon*maxValue;
}
//Function to test various comparison methods
template<typename T>
void testComparisonMethods(T a,T b)
{
    std::cout<<"Testing comparison methods for"<<a<<" and "<<b<<":\n";
    //Direct equality comparison
    std::cout<<"Direct equality comparison:"<<(isEqual(a,b) ? "Equal":"Not equal")<<"\n";
    //Epsilon comparison
    std::cout<<"Epsilon comparison:"<<(isEqualEpsilon(a,b)? "Equal":"Not equal")<<"\n";
    //Relative epsilon comparsion
    std::cout<<"Relative Epsilon comparison:"<<(isEqualRelativeEpsilon(a,b)? "Equal":"Not equal")<<"\n";
}
int main()
{
    //Test cases
    float testCases[][2]=
    {
        {1.0f,1.0f},
        {1.0f,1.000000000001f},
        {0.0f,-0.0f},
        {1.0000000000000000000000000000000000f,1.0000000000000000000000000000000001f},
        {std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()},
        {3E-5f,3E-5f},
        {5E-24f,5E-25f},
        {100E-37f,100E-38f},
    };
    int correctCount=0;
    int incorrectCount=0;
    //Perform test
    for(const auto& testCase:testCases)
    {
        float a=testCase[0];
        float b=testCase[1];
        testComparisonMethods(a,b);
        //Update counts
        if(isEqual(a,b))
        {
            correctCount++;
        }
        else
        {
            incorrectCount++;
        }
    }
    //Output results
    std::cout<<"Correct comparisons for float:"<<correctCount<<"\n";
    std::cout<<"Incorrect comparisons for float:"<<incorrectCount<<"\n";

    double testCasesDouble[][2]=
    {
        {1.0,1.0},
        {1.0,1.000000000001},
        {0.0,-0.0},
        {1.0000000000000000000000000000000000,1.0000000000000000000000000000000001},
        {std::numeric_limits<double>::infinity(),std::numeric_limits<double>::infinity()},
        {3E-5,3E-5},
        {5E-24,5E-25},
        {100E-37,100E-38},
    };

    
    int correctCountDouble=0;
    int incorrectCountDouble=0;
    //Perform test
    for(const auto& testCase:testCasesDouble)
    {
        double aDouble=testCase[0];
        double bDouble=testCase[1];
        testComparisonMethods(aDouble,bDouble);
        //Update counts
        if(isEqual(aDouble,bDouble))
        {
            correctCountDouble++;
        }
        else
        {
            incorrectCountDouble++;
        }
    }
    std::cout<<"Correct comparisons for double:"<<correctCountDouble<<"\n";
    std::cout<<"Incorrect comparisons for double:"<<incorrectCountDouble<<"\n";
    return 0;
}
// double {1.0,1.000000000001}, Not equal!!!
// float {1.0f,1.000000000001f},Equal!!!
//float has lower precision compared to double
//3E-5f correct for float incorrect for double
//5E-24,5E-25 epsilon comparison only equal 