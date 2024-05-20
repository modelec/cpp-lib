#pragma once

#include <vector>
#include <string>
namespace Modelec
{
    #define PI 3.14159265358979323846

    bool startWith(const std::string& str, const std::string& start);

    bool endsWith(const std::string& str, const std::string& end);

    bool contains(const std::string& str, const std::string& sub);

    std::vector<std::string> split(const std::string& str, const std::string& delimiter);

    template<typename T>
    T mapValue(T v, T v_min, T v_max, T v_min_prime, T v_max_prime) {
        return v_min_prime + (((v - v_min) * (v_max_prime - v_min_prime)) / (v_max - v_min));
    }
}