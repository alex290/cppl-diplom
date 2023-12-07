#include <iostream>
#include "main_parser.h"

int main()
{
    setlocale(LC_ALL, "Russian");  // Русская локализация консоли
    ini_parser parser("file.ini");
    try
    {
        auto value = parser.get_value<int>("Section2.var1");
        std::cout << "value: "
                  << "; " << value << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "value: " << e.what() << '\n';
    }

    try
    {
        auto value1 = parser.get_value<double>("Section1.var1");
        std::cout << "value1: "
                  << "; " << value1 << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "value1: " << e.what() << '\n';
    }

    try
    {
        auto value2 = parser.get_value<std::string>("Section1.var2");
        std::cout << "value2: "
                  << "; " << value2 << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "value2: " << e.what() << '\n';
    }

    // auto value3 = parser.get_value<char>("section.value");

    return 0;
}
