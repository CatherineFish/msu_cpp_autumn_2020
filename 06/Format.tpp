#include <stdexcept>

#include <sstream>

template < class...ArgsT > std::string format(const std::string & str_, const ArgsT & ...args) {
    std::string result;
    std::string in_str = str_;
    size_t in_start;
    size_t in_end;
    size_t pos = 0;
    while (!in_str.empty()) {
        in_start = in_str.find("{");
        in_end = in_str.find("}");
        if (in_start != std::string::npos && in_end != std::string::npos && in_start < in_end) {
            if (in_start) {
                result += in_str.substr(0, in_start);
            }
            try {
                size_t search_pos = std::stoull(in_str.substr(in_start + 1, in_end - 1));
                result += search_elem(search_pos, args...);
            } catch (const std::logic_error & exp) {
                throw IncorrectBracketSequence(pos + in_start);
            }
        } else if ((in_start != std::string::npos || in_end != std::string::npos) && in_end > in_start) {
            throw IncorrectBracketSequence(pos + in_start);
        } else if (in_start > in_end) {
            throw IncorrectBracketSequence(pos + in_end);
        } else {
            break;
        }
        in_str = in_str.substr(in_end + 1, std::string::npos);
        pos += in_end + 1;
    }
    result += in_str;
    return result;
}

template < class T, class...ArgsT >
    std::string search_elem(size_t search_pos, const T & val, const ArgsT & ...args) {
        if (search_pos) {
            return search_elem(search_pos - 1, args...);
        }
        std::stringstream result;
        result << val;
        return result.str();
    }

template < class T >
    std::string search_elem(size_t search_pos, const T & val) {
        if (search_pos) {
            throw TooFewArguments();
        }
        std::stringstream result;
        result << val;
        return result.str();
    }