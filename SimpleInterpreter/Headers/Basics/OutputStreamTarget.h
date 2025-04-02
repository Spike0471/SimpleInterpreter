#pragma once
#include <string>
class OutputStreamTarget
{
public:
    virtual ~OutputStreamTarget() = default;
    virtual std::string toString() const = 0;

    friend std::ostream &operator<<(std::ostream &os, const OutputStreamTarget &obj)
    {
        os << obj.toString();
        return os;
    }
};