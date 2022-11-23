#include <iostream>
#include "math.h"
//using namespace std;

int myXOR(int x, int y)
{
    return (x | y) & (~x | ~y);
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    int x=7;
    int y=5;
    std::cout << myXOR(x,y) << std::endl;

    return 0;
}
