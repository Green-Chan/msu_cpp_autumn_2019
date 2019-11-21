#pragma once

#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>

void form_vector(std::vector<std::string>& vect) {
    return;
}

template <class T, class... Args>
void form_vector(std::vector<std::string>& vect, const T& val, const Args&... args) {
    std::stringstream out;
    out << val;
    vect.push_back(out.str());
    form_vector(vect, args...);
}

template <class... Args>
std::string format(const std::string& fmt, const Args&... args) {
    std::vector<std::string> vect;
    form_vector(vect, args...);
    std::stringstream out;
    for (size_t i = 0; i < fmt.size(); i++) {
        if (fmt[i] == '{') {
            i++;
            if (!isdigit(fmt[i])) {
                throw std::runtime_error("expected number after \'{\'");
            }
            size_t off = 0;
            unsigned long long num = std::stoull(&fmt[i], &off, 10);
            i += off;
            size_t idx = num;
            if (i >= fmt.size() || fmt[i] != '}') {
                throw std::runtime_error("expected \'}\' after number");
            }
            if (idx != num || idx >= vect.size()) {
                throw std::runtime_error("not enough arguments");
            }
            out << vect[idx];
        } else {
            out << fmt[i];
        }
    }
    return out.str();
}

