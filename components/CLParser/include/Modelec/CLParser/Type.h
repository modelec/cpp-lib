#pragma once
#include <string>

enum ParameterType
{
    STRING,
    INT,
    FLOAT,
    BOOL,
    DOUBLE,
    LONG,
    SHORT,
    CHAR,
    CHAR_PTR,
    CONST_CHAR_PTR
};

template<typename T> struct ParameterTypeTraits {};

template<> struct ParameterTypeTraits<std::string> {
    static constexpr ParameterType type = STRING;
};

template<> struct ParameterTypeTraits<int> {
    static constexpr ParameterType type = INT;
};

template<> struct ParameterTypeTraits<float> {
    static constexpr ParameterType type = FLOAT;
};

template<> struct ParameterTypeTraits<bool> {
    static constexpr ParameterType type = BOOL;
};

template<> struct ParameterTypeTraits<double> {
    static constexpr ParameterType type = DOUBLE;
};

template<> struct ParameterTypeTraits<long> {
    static constexpr ParameterType type = LONG;
};

template<> struct ParameterTypeTraits<short> {
    static constexpr ParameterType type = SHORT;
};

template<> struct ParameterTypeTraits<char> {
    static constexpr ParameterType type = CHAR;
};

template<> struct ParameterTypeTraits<char*> {
    static constexpr ParameterType type = CHAR_PTR;
};

template<> struct ParameterTypeTraits<const char*> {
    static constexpr ParameterType type = CONST_CHAR_PTR;
};
