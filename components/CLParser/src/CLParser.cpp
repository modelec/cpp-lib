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

bool CLParser::hasOption(const std::string &option) const {
    return this->_options.find(option) != this->_options.end();
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

void CLParser::parseString(const std::string &str, ParameterType type, void *value) {
    try {
        switch (type) {
            case ParameterType::STRING:
                *static_cast<std::string *>(value) = str;
                break;
            case ParameterType::INT:
                *static_cast<int *>(value) = std::stoi(str);
                break;
            case ParameterType::FLOAT:
                *static_cast<float *>(value) = std::stof(str);
                break;
            case ParameterType::DOUBLE:
                *static_cast<double *>(value) = std::stod(str);
                break;
            case ParameterType::BOOL:
                *static_cast<bool *>(value) = str == "true";
                break;
            case ParameterType::LONG:
                *static_cast<long *>(value) = std::stol(str);
                break;
            case ParameterType::SHORT:
                *static_cast<short *>(value) = static_cast<short>(std::stoi(str));
                break;
            case ParameterType::CHAR:
                *static_cast<char *>(value) = str[0];
                break;
            case ParameterType::CHAR_PTR:
                *static_cast<char **>(value) = const_cast<char *>(str.c_str());
                break;
            case ParameterType::CONST_CHAR_PTR:
                *static_cast<const char **>(value) = str.c_str();
                break;
            default:
                throw std::runtime_error("Invalid type");
        }
    } catch (const std::exception &e) {
        throw std::runtime_error("Invalid value for value : " + str);
    }
}
