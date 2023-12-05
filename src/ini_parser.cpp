#include "ini_parser.h"


ini_parser::ini_parser(std::string file_name) : file_name_(file_name)
{
    file_open();
    std::cout << text_ << std::endl;
}

ini_parser::~ini_parser()
{
}
void ini_parser::file_open()
{
    std::ifstream file;
    file.open(file_name_);
    text_ = "";
    std::string new_text;

    if (file.is_open())
    {
        while (file)
        {
            std::getline(file, new_text);
            Trim(new_text);
            if (new_text[0] == ';') // Комментарий
            {
            }
            else if (new_text[0] == '[' && new_text[new_text.size() - 1] == ']') // Если секция
            {
                new_text.erase(new_text.begin());
                new_text.erase(new_text.begin() + new_text.size() - 1);

                // std::cout << "SECTION " << new_text << std::endl;

                section_name = new_text;

                auto sec = std::find_if(root_.begin(), root_.end(), [&new_text](ini_parser::data &a)
                                        { return a.section_name == new_text; });
                if (sec == root_.end())
                {
                    ini_parser::data new_sect;
                    new_sect.section_name = new_text;
                    root_.push_back(new_sect);
                }
            }
            else if (new_text.size() > 2) // Если строка не пустая
            {
                const char delim = '=';
                std::vector<std::string> out;

                std::stringstream ss(new_text);

                std::string s;
                while (std::getline(ss, s, delim))
                {
                    out.push_back(s);
                }

                // std::cout << out.size() << std::endl;

                std::string name;
                std::string val;

                if (out.size() == 1)
                {
                    name = out[0];
                    val = "";
                }
                else if (out.size() > 1)
                {
                    name = out[0];
                    val = out[1];

                    // Очищаем значение от комментария
                    const char del = ';';
                    out.clear();
                    ss = std::stringstream(val);
                    while (std::getline(ss, s, del))
                    {
                        out.push_back(s);
                    }
                    val = "";
                    if (out.size() > 0)
                    {
                        val = out[0];
                        Trim(val); // Удаляем пробелы в начале и в конце
                    }
                }

                if (name.size() > 1)
                {
                    // std::cout << name << "; " << val << std::endl;

                    std::string sec_name = section_name;

                    auto sec = std::find_if(root_.begin(), root_.end(), [&sec_name](ini_parser::data &a)
                                            { return a.section_name == sec_name; });

                    if (sec != root_.end())
                    {
                        sec->param[name] = val;
                    }
                }

                // for (auto &s : out)
                // {
                //     std::cout << s << std::endl;
                // }
            }

            // std::cout << new_text << std::endl;
        }
    }
    else
    {
        std::cout << "Couldn't open file\n";
    }

    // Проверяем данные
    /*
    if (!root_.empty())
    {
        for (auto &s : root_)
        {
            std::cout << "[" << s.section_name << "]" << std::endl;
            if (!s.param.empty())
            {
                for (auto &val : s.param)
                {
                    std::cout << val.first << "; " << val.second << std::endl;
                }
            }
        }
    }
    */
}

void ini_parser::Trim(std::string &text)
{
    text.erase(0, text.find_first_not_of("\t\n\v\f\r ")); // left trim
    text.erase(text.find_last_not_of("\t\n\v\f\r ") + 1); // right trim
}


int ini_parser::get_int_value(std::string param)
{

    // std::cout << param << std::endl;
    int numb = 0;
    try
    {
        numb = std::stoi(from_value(param));
    }
    catch (const std::exception &e)
    {
        throw e.what();
    }

    return numb;
};

double ini_parser::get_double_value(std::string param)
{

    // std::cout << param << std::endl;
    double numb = 0;
    try
    {
        numb = std::stod(from_value(param));
    }
    catch (const std::exception &e)
    {
        throw e.what();
    }

    return numb;
};

std::string ini_parser::get_string_value(std::string param) {
    std::string text = "";
    try
    {
        text = from_value(param);
    }
    catch (const std::exception &e)
    {
        throw e.what();
    }

    return text;
}


std::string ini_parser::from_value(std::string param)
{

    std::string val;
    std::string sec_name;

    const char delim = '.';
    std::vector<std::string> out;

    std::stringstream ss(param);

    std::string s;
    while (std::getline(ss, s, delim))
    {
        out.push_back(s);
    }
    if (out.size() == 2)
    {
        sec_name = out[0];
        val = out[1];
    }
    else
    {
        throw "Invalid parameter!";
    }

    // std::cout << sec_name << std::endl;

    auto sec = std::find_if(root_.begin(), root_.end(), [&sec_name](ini_parser::data &a)
                            { return a.section_name == sec_name; });

    if (sec != root_.end())
    {
        auto par = sec->param.find(val);
        if (par == sec->param.end())
        {
            throw "The variable does not exist!";
        }
        else
        {
            // std::cout << par->second << std::endl;
            return par->second;
        }
    }
    else
    {
        throw "There is no such section!";
    }

    return "";
}