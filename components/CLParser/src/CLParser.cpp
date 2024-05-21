#include <Modelec/CLParser.h>

CLParser::CLParser(int argc, char **argv) : _argc(argc) {
    this->_argv = std::vector<std::string>(argc);
    for (int i = 0; i < argc; i++) {
        this->_argv[i] = argv[i];
    }

    for (int i = 1; i < argc; i++) {
        if (this->_argv[i].rfind("--", 0) == 0) {
            std::string option = this->_argv[i].substr(2);
            if (i + 1 < argc && this->_argv[i + 1].rfind("--", 0) != 0) {
                this->_options[option] = this->_argv[i + 1];
            } else {
                this->_options[option] = "";
            }
        }
    }
}

std::optional<std::string> CLParser::getOption(const std::string &option) const {
    if (!this->hasOption(option)) {
        return std::nullopt;
    }

    return this->_options.at(option);
}

bool CLParser::hasOption(const std::string &option) const {
    return this->_options.find(option) != this->_options.end();
}

std::string CLParser::getOption(const std::string &option, const std::string &defaultValue) const {
    if (!this->hasOption(option)) {
        return defaultValue;
    }

    return this->_options.at(option);
}

bool CLParser::hasPositionalArgument(int index) const {
    return index < this->_argc;
}

std::string CLParser::getPositionalArgument(int index) const {
    if (!this->hasPositionalArgument(index)) {
        return "";
    }

    return this->_argv[index];
}

int CLParser::positionalArgumentsCount() const {
    return this->_argc;
}

CLParser::~CLParser() = default;

CLParser::CLParser(const CLParser &other) = default;