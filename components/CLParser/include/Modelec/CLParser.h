#pragma once

#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

#include <Modelec/CLParser/Type.h>

class CLParser {

public:
    CLParser(int argc, char** argv);

    CLParser(const CLParser& other);

    [[nodiscard]] bool hasOption(const std::string& option) const;

    template <typename T>
    [[nodiscard]] T getOption(const std::string& option, T defaultValue) const {
        if (!hasOption(option)) {
            return defaultValue;
        }

        T value = T();
        parseString(_options.at(option), ParameterTypeTraits<T>::type, static_cast<void *>(&value));
        return value;
    }

    template <typename T>
    [[nodiscard]] std::optional<T> getOption(const std::string& option) const {
        if (!hasOption(option)) {
            return std::nullopt;
        }

        T value = T();
        parseString(_options.at(option), ParameterTypeTraits<T>::type, static_cast<void *>(&value));
        return value;
    }

    [[nodiscard]] bool hasPositionalArgument(int index) const;

    [[nodiscard]] std::string getPositionalArgument(int index) const;

    template <typename T>
    [[nodiscard]] T getPositionalArgument(int index) const {
        if (!hasPositionalArgument(index)) {
            return T();
        }

        T value = T();
        parseString(_argv[index], ParameterTypeTraits<T>::type, static_cast<void *>(&value));
        return value;
    }

    [[nodiscard]] int positionalArgumentsCount() const;

    ~CLParser();

protected:
    static void parseString(const std::string& str, ParameterType type, void* value) ;

private:
    std::vector<std::string> _argv;
    int _argc;

    std::map<std::string, std::string> _options;
};
