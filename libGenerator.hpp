#pragma once
#include <string>
class LibGenerator
{
    std::string m_libPath;
public:
    LibGenerator(std::string const &path, std::string const& code);
    ~LibGenerator();
};