#pragma once

#include "ini_parser.h"

template <>
std::string ini_parser::get_value<std::string>(std::string param)
{
    
    return get_string_value(param);
}
