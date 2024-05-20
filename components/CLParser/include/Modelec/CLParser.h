#pragma once

#include <map>
#include <optional>
#include <string>

class CLParser {

public:
    CLParser(int argc, char** argv);

    CLParser(const CLParser& other);

    [[nodiscard]] bool hasOption(const std::string& option) const;

    [[nodiscard]] std::optional<std::string> getOption(const std::string& option) const;

    [[nodiscard]] std::string getOption(const std::string& option, const std::string& defaultValue) const;

    template <typename T>
    [[nodiscard]] typename std::enable_if<std::is_arithmetic<T>::value, T>::type getOption(const std::string& option, T defaultValue) const {
        if (!hasOption(option)) {
            return defaultValue;
        }

        try {
            return static_cast<T>(std::stod(_options.at(option)));
        } catch (std::exception& e) {
            return defaultValue;
        }
    }

    template <typename T>
    [[nodiscard]] std::optional<typename std::enable_if<std::is_arithmetic<T>::value, T>::type> getOption(const std::string& option) const {
        if (!hasOption(option)) {
            return std::nullopt;
        }

        try {
            return static_cast<T>(std::stod(_options.at(option)));
        } catch (std::exception& e) {
            return std::nullopt;
        }
    }

    [[nodiscard]] bool hasPositionalArgument(int index) const;

    [[nodiscard]] std::string getPositionalArgument(int index) const;

    template <typename T>
    [[nodiscard]] typename std::enable_if<std::is_arithmetic<T>::value, T>::type getPositionalArgument(int index) const {
        if (!hasPositionalArgument(index)) {
            return T();
        }

        try {
            return static_cast<T>(std::stod(_argv[index]));
        } catch (std::exception& e) {
            return T();
        }
    }

    [[nodiscard]] int positionalArgumentsCount() const;

    ~CLParser();

private:
    std::string* _argv;
    int _argc;

    std::map<std::string, std::string> _options;
};
