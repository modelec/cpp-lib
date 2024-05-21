#pragma once

#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

class CLParser {

public:
    CLParser(int argc, char** argv);

    CLParser(const CLParser& other);

    [[nodiscard]] bool hasOption(const std::string& option) const;

    [[nodiscard]] std::optional<std::string> getOption(const std::string& option) const;

    [[nodiscard]] std::string getOption(const std::string& option, const std::string& defaultValue) const;

    template <typename T>
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, T> getOption(const std::string& option, T defaultValue) const {
        if (!hasOption(option)) {
            return defaultValue;
        }

        T value;
        std::istringstream iss(_options.at(option));
        iss >> value;

        if (iss.fail() || !iss.eof()) {
            std::cout << "Failed convert" << std::endl;
            return defaultValue;
        }

        return value;
    }

    template <typename T>
    [[nodiscard]] std::optional<std::enable_if_t<std::is_arithmetic_v<T>, T>> getOption(const std::string& option) const {
        if (!hasOption(option)) {
            return std::nullopt;
        }

		T value;
		std::istringstream iss(_options.at(option));
        iss >> value;

        if (iss.fail() || !iss.eof()) {
            return std::nullopt;
        }

        return value;
    }

    [[nodiscard]] bool hasPositionalArgument(int index) const;

    [[nodiscard]] std::string getPositionalArgument(int index) const;

    template <typename T>
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, T> getPositionalArgument(int index) const {
        if (!hasPositionalArgument(index)) {
            return T();
        }

        T value;
        std::istringstream iss(_argv[index]);
        iss >> value;

        if (iss.fail() || !iss.eof()) {
            return T();
        }

        return value;
    }

    [[nodiscard]] int positionalArgumentsCount() const;

    ~CLParser();



private:
    std::vector<std::string> _argv;
    int _argc;

    std::map<std::string, std::string> _options;
};
