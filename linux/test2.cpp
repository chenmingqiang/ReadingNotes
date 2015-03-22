#include <iostream>

class Test {
  public:
    Test() { std::cout << "constructor" << std::endl;}
    ~Test() { std::cout << "destructor" << std::endl;}
};


int main(int argc, char *argv[])
{
    Test t;
    exit(0);
}
