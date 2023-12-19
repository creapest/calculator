#include <iostream>
#include <string>

int main()
{

    long double a = 38597;
    long double b = 2969;
    long double c = 27304 + 8732 - 71 + 19865 * 7 - 219 + 30958 + 24344;
    c *= 6;
    long double h = a / b + c + 9842;
    std::string s = "1390480";
    std::cout << std::fixed << h << std::endl;
    std::cout << stold(s) << std::endl;
    long double o = stold(s);
    std::string S = std::to_string(h);
    std::cout << std::to_string(h) << std::endl;
    return 0;
}