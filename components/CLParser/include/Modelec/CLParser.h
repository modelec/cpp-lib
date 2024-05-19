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

    [[nodiscard]] bool hasPositionalArgument(int index) const;

    [[nodiscard]] std::string getPositionalArgument(int index) const;

    [[nodiscard]] int positionalArgumentsCount() const;

    ~CLParser();

private:
    std::string* _argv;
    int _argc;

    std::map<std::string, std::string> _options;
};
