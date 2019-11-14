#pragma once

#include <cinttypes>
#include <ostream>
#include "error.h"

class Serializer
{
    static constexpr char Separator = ' ';
    std::ostream& out_;
public:
    explicit Serializer(std::ostream& out)
        : out_(out)
    {
    }

    template <class T>
    Error save(T& object)
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
        return print(val);
    }

    template <class T, class... Args>
    Error process(T&& val, Args&&... args)
    {
        print(val);
        return process(std::forward<Args>(args)...);
    }

    Error print(uint64_t num) {
        out_ << num << Separator;
        return Error::NoError;
    }

    Error print(bool val) {
        if (val) {
            out_ << "true" << Separator;
        } else {
            out_ << "false" << Separator;
        }
        return Error::NoError;
    }
};
