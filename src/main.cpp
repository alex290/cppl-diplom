#include <iostream>
#include "main_parser.h"



int main()
{
    setlocale(LC_ALL, "Russian"); // Русская локализация консоли
    ini_parser parser("file.ini");
    auto value = parser.get_value<int>("Section2.var1");
    auto value1 = parser.get_value<double>("Section1.var1");
    auto value2 = parser.get_value<std::string>("Section1.var2");
    // auto value3 = parser.get_value<char>("section.value");

    std::cout << value << "; " << value1 << "; " << value2 << std::endl;

    return 0;
}
