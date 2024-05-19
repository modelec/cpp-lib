#pragma once

#include <vector>
#include <string>
namespace Modelec
{
    bool startWith(const std::string& str, const std::string& start);

    bool endsWith(const std::string& str, const std::string& end);

    bool contains(const std::string& str, const std::string& sub);

    std::vector<std::string> split(const std::string& str, const std::string& delimiter);
}