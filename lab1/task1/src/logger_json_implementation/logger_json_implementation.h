#ifndef JSON_H
#define JSON_H
#include "forJson/single_include/nlohmann/json.hpp"
#include "../logger/logger.h"

class json
{
public:
    virtual logger *build() const = 0;

    virtual ~json();
};

#endif //JSON_H
