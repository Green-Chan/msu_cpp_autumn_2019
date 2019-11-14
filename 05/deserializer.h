#pragma once

#include <cinttypes>
#include <istream>
#include <string>
#include "error.h"

class Deserializer
{
    static constexpr char Separator = ' ';
    std::istream& in_;
public:
    explicit Deserializer(std::istream& in)
        : in_(in)
    {
    }

    template <class T>
    Error load(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(std::forward<ArgsT>(args)...);
    }

private:
    template <class T>
    Error process(T&& val)
    {
        return scan(val);
    }

    template <class T, class... Args>
    Error process(T&& val, Args&&... args)
    {
        if (scan(val) == Error::CorruptedArchive ||
                process(std::forward<Args>(args)...) == Error::CorruptedArchive) {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

    Error scan(uint64_t &num) {
        std::string text;
        in_ >> text;
        if (!text.size() || text[0] == '-') {
            return Error::CorruptedArchive;
        }
        size_t last;
        num = std::stoull(text, &last, 10);
        if (last != text.size()) {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

    Error scan(bool &value) {
        std::string text;
        in_ >> text;
        if (text == "true")
            value = true;
        else if (text == "false")
            value = false;
        else
            return Error::CorruptedArchive;
        return Error::NoError;
    }
};
