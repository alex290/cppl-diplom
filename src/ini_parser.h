#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <typeinfo>

class ini_parser
{
public:
    struct data
    {
        std::string section_name;
        std::map<std::string, std::string> param;
    };

    ini_parser(std::string file_name);
    ~ini_parser();

    template <typename T>
    T get_value(std::string param)
    {
        T t_val;

        if (typeid(t_val) == typeid(int)) // Если тип INT
        {
            t_val = get_int_value(param);
        }
        else if (typeid(t_val) == typeid(double)) // Если тип DOUBLE
        {
            t_val = get_double_value(param);
        }
        else
        {
            throw "Unknown data type!";
        }

        return t_val;
    }

private:
    std::string file_name_;
    std::string text_;
    void file_open();

    std::string section_name;

    void Trim(std::string &text);        // Убираем пробелы
    std::vector<ini_parser::data> root_; // Данные

    std::string from_value(std::string param);

    int get_int_value(std::string param);

    double get_double_value(std::string param);

    std::string get_string_value(std::string param);
};
