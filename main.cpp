#include <iostream>
#include "String.h"


int main() {
    String testString("Hello World!");

    std::cout << "Test output: |" << testString.c_str() << "|" << std::endl;
    std::cout << "Length: " << testString.getLength() << std::endl;

    testString.concatenate("+1");

    std::cout << "Test output: |" << testString.c_str() << "|" << std::endl;
    std::cout << "Length: " << testString.getLength() << std::endl;

    testString.concatenate(String(" Test"));

    std::cout << "Test output: |" << testString.c_str() << "|" << std::endl;
    std::cout << "Length: " << testString.getLength() << std::endl;

    return 0;
}